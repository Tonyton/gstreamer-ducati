/* GStreamer
 *
 * Copyright (C) 2001-2002 Ronald Bultje <rbultje@ronald.bitfreak.net>
 *               2006 Edgard Lima <edgard.lima@indt.org.br>
 *               2009 Texas Instruments, Inc - http://www.ti.com/
 * 		 2011 xuzhi.Tony tonyt@xuzhitech.com
 *
 * gstoverlaybufferpool.c OVERLAY buffer pool class
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Tony, MA 20110913, China.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

#include "gst/video/video.h"

#include <gstoverlaybufferpool.h>
#include "gstsurfaceflingersink.h"

/* videodev2.h is not versioned and we can't easily check for the presence
 * of enum values at compile time, but the OVERLAY_CAP_VIDEO_OUTPUT_OVERLAY define
 * was added in the same commit as OVERLAY_FIELD_INTERLACED_{TB,BT} (b2787845) */

static void gst_overlay_buffer_pool_log_init(void);

GST_DEBUG_CATEGORY_EXTERN (gst_surfaceflinger_sink_debug);
#define GST_CAT_DEFAULT gst_surfaceflinger_sink_debug


/*
 * GstOverlayBuffer:
 */

static GstBufferClass *overlaybuffer_parent_class = NULL;

static void
gst_overlay_buffer_finalize (GstOverlayBuffer * buffer)
{
  GstOverlayBufferPool *pool;
  gboolean resuscitated = FALSE;
  gint index = 0;

  pool = buffer->pool;

  index = buffer->index;

  GST_DEBUG_OBJECT (pool->overlayelem, "finalizing buffer %p %d", buffer, index);
  GST_OVERLAY_BUFFER_POOL_LOCK (pool);
  if (pool->running) {
      resuscitated = TRUE;
      /* XXX double check this... I think it is ok to not synchronize this
       * w.r.t. destruction of the pool, since the buffer is still live and
       * the buffer holds a ref to the pool..
       */
      g_async_queue_push (pool->avail_buffers, buffer);
    } else {
	GST_LOG_OBJECT (pool->overlayelem, "the pool is shutting down");
    }
  if (resuscitated) {
    /* FIXME: check that the caps didn't change */
    GST_LOG_OBJECT (pool->overlayelem, "reviving buffer %p, %d", buffer, index);
    gst_buffer_ref (GST_BUFFER (buffer));
    GST_BUFFER_SIZE (buffer) = 0;
    pool->buffers[index] = buffer;
  }
  GST_OVERLAY_BUFFER_POOL_UNLOCK (pool);

  if (!resuscitated) {
    GST_LOG_OBJECT (pool->overlayelem,
        "buffer %p (data %p) not recovered, unmapping",
        buffer, GST_BUFFER_DATA (buffer));
    gst_mini_object_unref (GST_MINI_OBJECT (pool));

    GST_MINI_OBJECT_CLASS (overlaybuffer_parent_class)->finalize (GST_MINI_OBJECT
        (buffer));
  }
}

static void
gst_overlay_buffer_class_init (gpointer g_class, gpointer class_data)
{
  GST_WARNING("gst_overlay_buffer_class_init");
  GstMiniObjectClass *mini_object_class = GST_MINI_OBJECT_CLASS (g_class);

  overlaybuffer_parent_class = g_type_class_peek_parent (g_class);

  mini_object_class->finalize = (GstMiniObjectFinalizeFunction)
      gst_overlay_buffer_finalize;
}

GType
gst_overlay_buffer_get_type (void)
{
  static GType _gst_overlay_buffer_type = 0;

  if (G_UNLIKELY (_gst_overlay_buffer_type == 0)) {
    static const GTypeInfo overlay_buffer_info = {
      sizeof (GstBufferClass),
      NULL,
      NULL,
      gst_overlay_buffer_class_init,
      NULL,
      NULL,
      sizeof (GstOverlayBuffer),
      0,
      NULL,
      NULL,
    };
    _gst_overlay_buffer_type = g_type_register_static (GST_TYPE_BUFFER,
        "GstOverlayBuffer", &overlay_buffer_info, 0);
  }

  return _gst_overlay_buffer_type;
}


static GstOverlayBuffer *
gst_overlay_buffer_new (GstOverlayBufferPool * pool, guint index, GstCaps * caps, 
	guint8 *data,guint32 size)
{
  GstOverlayBuffer *ret;


  ret = (GstOverlayBuffer *) gst_mini_object_new (GST_TYPE_OVERLAY_BUFFER);


  ret->pool =
      (GstOverlayBufferPool *) gst_mini_object_ref (GST_MINI_OBJECT (pool));

  ret->index = index;
  GST_BUFFER_DATA (ret) = data;
  GST_BUFFER_SIZE (ret) = size;

  GST_BUFFER_FLAG_SET (ret, GST_BUFFER_FLAG_READONLY);

  gst_buffer_set_caps (GST_BUFFER (ret), caps);

  GST_DEBUG_OBJECT (pool->overlayelem, "creating buffer %u, %p in pool %p,size %u ,buffer address is %p", index,
      ret, pool, GST_BUFFER_SIZE (ret) ,GST_BUFFER_DATA (ret));

  return ret;
}


/*
 * GstOverlayBufferPool:
 */

static GstMiniObjectClass *buffer_pool_parent_class = NULL;

static void
gst_overlay_buffer_pool_finalize (GstOverlayBufferPool * pool)
{
  g_mutex_free (pool->lock);
  pool->lock = NULL;

  g_async_queue_unref (pool->avail_buffers);
  pool->avail_buffers = NULL;

  if (pool->buffers) {
    g_free (pool->buffers);
    pool->buffers = NULL;
  }

  GST_MINI_OBJECT_CLASS (buffer_pool_parent_class)->finalize (GST_MINI_OBJECT
      (pool));
}

static void
gst_overlay_buffer_pool_init (GstOverlayBufferPool * pool)
{
  pool->lock = g_mutex_new ();
  pool->running = FALSE;
  pool->num_live_buffers = 0;
}

static void
gst_overlay_buffer_pool_class_init (GstOverlayBufferPoolClass *klass)
{
 
    GstMiniObjectClass *mo_class = GST_MINI_OBJECT_CLASS(klass);


    buffer_pool_parent_class = g_type_class_peek_parent(klass);

    mo_class->finalize =
        (GstMiniObjectFinalizeFunction) gst_overlay_buffer_pool_finalize;

}
GType
gst_overlay_buffer_pool_get_type (void)
{
  static GType _gst_overlay_buffer_pool_type = 0;

  if (G_UNLIKELY (_gst_overlay_buffer_pool_type == 0)) {
    static const GTypeInfo overlay_buffer_pool_info = {
      sizeof (GstMiniObjectClass),
      NULL,
      NULL,
      gst_overlay_buffer_pool_class_init,
      NULL,
      NULL,
      sizeof (GstOverlayBufferPool),
      0,
      (GInstanceInitFunc)gst_overlay_buffer_pool_init,
      NULL
    };
    _gst_overlay_buffer_pool_type = g_type_register_static (GST_TYPE_MINI_OBJECT,
        "GstOverlayBufferPool", &overlay_buffer_pool_info, 0);
  }
  return _gst_overlay_buffer_pool_type;

}


/**
 * gst_overlay_buffer_pool_new:
 * @overlayelem:  the overlay element (src or sink) that owns this pool
 * @fd:   the video device file descriptor
 * @num_buffers:  the requested number of buffers in the pool
 * @caps:  the caps to set on the buffer
 * @requeuebuf: if %TRUE, and if the pool is still in the running state, a
 *  buffer with no remaining references is immediately passed back to overlay
 *  (VIDIOC_QBUF), otherwise it is returned to the pool of available buffers
 *  (which can be accessed via gst_overlay_buffer_pool_get().
 *
 * Construct a new buffer pool.
 *
 * Returns: the new pool, use gst_overlay_buffer_pool_destroy() to free resources
 */
GstOverlayBufferPool *
gst_overlay_buffer_pool_new (GstElement * overlayelem, gint num_buffers,
    GstCaps * caps)
{
  GstOverlayBufferPool *pool;
  gint n;
  guint32 size;
  guint8 *data;

  GstSurfaceFlingerSink *surfacesink = GST_SURFACEFLINGERSINK (overlayelem);

  pool = (GstOverlayBufferPool *) gst_mini_object_new (GST_TYPE_OVERLAY_BUFFER_POOL);

  g_return_val_if_fail(pool != NULL, NULL);

  /* first, lets request buffers, and see how many we can get: */
  GST_WARNING_OBJECT (overlayelem, "STREAMING, requesting %d MMAP buffers",
      num_buffers);

  pool->overlayelem = overlayelem;
  pool->buffer_count = num_buffers;
  pool->buffers = g_new0 (GstOverlayBuffer *, num_buffers);
  pool->avail_buffers = g_async_queue_new ();
  /* now, mmap the buffers: */
  for (n = 0; n < num_buffers; n++) {
    size = videoflinger_device_get_overlay_buf_length(surfacesink->videodev);
    data = (guint8 *)videoflinger_device_get_overlay_address(surfacesink->videodev,n);
    pool->buffers[n] = gst_overlay_buffer_new (pool, n, caps,
		data,size);
    if (!pool->buffers[n])
      goto buffer_new_failed;
    pool->num_live_buffers++;
    g_async_queue_push (pool->avail_buffers, pool->buffers[n]);
  }
  return pool;
  /* ERRORS */
buffer_new_failed:
  {
    gint errnosave = errno;

    gst_overlay_buffer_pool_destroy (pool);

    errno = errnosave;
    return NULL;
  }
}

/**
 * gst_overlay_buffer_pool_destroy:
 * @pool: the pool
 *
 * Free all resources in the pool and the pool itself.
 */
void
gst_overlay_buffer_pool_destroy (GstOverlayBufferPool * pool)
{
  gint n;

  GST_OVERLAY_BUFFER_POOL_LOCK (pool);
  pool->running = FALSE;
  GST_OVERLAY_BUFFER_POOL_UNLOCK (pool);

  GST_DEBUG_OBJECT (pool->overlayelem, "destroy pool");

  /* after this point, no more buffers will be queued or dequeued; no buffer
   * from pool->buffers that is NULL will be set to a buffer, and no buffer that
   * is not NULL will be pushed out. */

  /* miniobjects have no dispose, so they can't break ref-cycles, as buffers ref
   * the pool, we need to unref the buffer to properly finalize te pool */
  for (n = 0; n < pool->buffer_count; n++) {
    GstBuffer *buf;

    GST_OVERLAY_BUFFER_POOL_LOCK (pool);
    buf = GST_BUFFER (pool->buffers[n]);
    GST_OVERLAY_BUFFER_POOL_UNLOCK (pool);

    if (buf)
      /* we own the ref if the buffer is in pool->buffers; drop it. */
      gst_buffer_unref (buf);
  }

  gst_mini_object_unref (GST_MINI_OBJECT (pool));
}

/**
 * gst_overlay_buffer_pool_get:
 * @pool:   the "this" object
 * @blocking:  should this call suspend until there is a buffer available
 *    in the buffer pool?
 *
 * Get an available buffer in the pool
 */
GstOverlayBuffer *
gst_overlay_buffer_pool_get (GstOverlayBufferPool * pool, gboolean blocking)
{
  GstOverlayBuffer *buf;
  GstSurfaceFlingerSink *surfacesink = GST_SURFACEFLINGERSINK (pool->overlayelem);

  if (blocking) {
    buf = g_async_queue_pop (pool->avail_buffers);
  } else {
    buf = g_async_queue_try_pop (pool->avail_buffers);
  }

  if (buf && buf != GST_OVERLAY_BUFFER_SENTINEL) {
    GST_OVERLAY_BUFFER_POOL_LOCK (pool);
    GST_BUFFER_SIZE (buf) = videoflinger_device_get_overlay_buf_length(surfacesink->videodev);
    GST_BUFFER_FLAG_UNSET (buf, 0xffffffff);
    GST_OVERLAY_BUFFER_POOL_UNLOCK (pool);
  }

  pool->running = TRUE;

  return buf;
}

/**
 * gst_overlay_buffer_pool_available_buffers:
 * @pool: the pool
 *
 * Check the number of buffers available to the driver, ie. buffers that
 * have been QBUF'd but not yet DQBUF'd.
 *
 * Returns: the number of buffers available.
 */
gint
gst_overlay_buffer_pool_available_buffers (GstOverlayBufferPool * pool)
{
  return pool->buffer_count - pool->num_live_buffers;
}
