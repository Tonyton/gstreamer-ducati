/* GStreamer
 *
 * Copyright (C) 2001-2002 Ronald Bultje <rbultje@ronald.bitfreak.net>
 *               2006 Edgard Lima <edgard.lima@indt.org.br>
 *               2009 Texas Instruments, Inc - http://www.ti.com/
 * 		 2011 xuzhi.Tony tonyt@xuzhitech.com
 *
 * gstvoverlaybufferpool.h OVERLAY buffer pool class
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
 * xuzhi.Tony, MA 20110913 , China.
 */


#ifndef __GSTOVERLAYBUFFER_H__
#define __GSTOVERLAYBUFFER_H__

#include <gst/gst.h>
#include <v4l2_utils.h>


G_BEGIN_DECLS


GType gst_overlay_buffer_get_type (void);
#define GST_TYPE_OVERLAY_BUFFER (gst_overlay_buffer_get_type())
#define GST_IS_OVERLAY_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_OVERLAY_BUFFER))
#define GST_OVERLAY_BUFFER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_OVERLAY_BUFFER, GstOverlayBuffer))

GType gst_overlay_buffer_pool_get_type (void);
#define GST_TYPE_OVERLAY_BUFFER_POOL (gst_overlay_buffer_pool_get_type())
#define GST_IS_OVERLAY_BUFFER_POOL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_OVERLAY_BUFFER_POOL))
#define GST_OVERLAY_BUFFER_POOL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_OVERLAY_BUFFER_POOL, GstOverlayBufferPool))

#define GST_OVERLAY_BUFFER_SENTINEL GINT_TO_POINTER(42)


typedef struct _GstOverlayBufferPoolClass GstOverlayBufferPoolClass;
typedef struct _GstOverlayBufferPool GstOverlayBufferPool;
typedef struct _GstOverlayBuffer GstOverlayBuffer;


struct _GstOverlayBufferPool
{
  GstMiniObject parent;
  GstElement *overlayelem;
  GMutex *lock;
  gboolean running;          /* with lock */
  gint num_live_buffers;     /* number of buffers not with driver */
  GAsyncQueue* avail_buffers;/* pool of available buffers, not with the driver and which aren't held outside the bufferpool */
  guint buffer_count;
  GstOverlayBuffer **buffers;
};

struct _GstOverlayBufferPoolClass {
    GstMiniObjectClass    derived_methods;
};


struct _GstOverlayBuffer {
  GstBuffer   buffer;
  GstOverlayBufferPool *pool;
  gint index;
};

void gst_overlay_buffer_pool_destroy (GstOverlayBufferPool * pool);
GstOverlayBufferPool *gst_overlay_buffer_pool_new (GstElement * overlayelem,gint num_buffers, GstCaps * caps);

GstOverlayBuffer *gst_overlay_buffer_pool_get (GstOverlayBufferPool *pool, gboolean blocking);
gboolean gst_overlay_buffer_pool_qbuf (GstOverlayBufferPool *pool, GstOverlayBuffer *buf);
GstOverlayBuffer *gst_overlay_buffer_pool_dqbuf (GstOverlayBufferPool *pool);

gint gst_overlay_buffer_pool_available_buffers (GstOverlayBufferPool *pool);

#define GST_OVERLAY_BUFFER_POOL_LOCK(pool)     g_mutex_lock ((pool)->lock)
#define GST_OVERLAY_BUFFER_POOL_UNLOCK(pool)   g_mutex_unlock ((pool)->lock)

G_END_DECLS

#endif /* __GSTOVERLAYBUFFER_H__ */
