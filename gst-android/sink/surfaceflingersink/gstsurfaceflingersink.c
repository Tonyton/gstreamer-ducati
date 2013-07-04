#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include <unistd.h>

#include "gstsurfaceflingersink.h"

GST_DEBUG_CATEGORY (gst_surfaceflinger_sink_debug);
#define GST_CAT_DEFAULT gst_surfaceflinger_sink_debug
#define PROP_DEF_QUEUE_SIZE         12


/* elementfactory information */
static const GstElementDetails gst_surfaceflinger_sink_details =
GST_ELEMENT_DETAILS ("android's surface flinger sink",
    "Sink/Video",
    "A linux framebuffer videosink",
    "Tony <tonyt@xuzhitech.com>");


static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE (
    "sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS
    (
    "video/x-raw-yuv, "
         "format=(fourcc)I420, "
         "framerate=(fraction)[ 0, MAX ], "
         "width=(int)[ 1, MAX ], "
         "height=(int)[ 1, MAX ];"
    "video/x-raw-yuv, "
         "format=(fourcc)NV12, "
         "framerate=(fraction)[ 0, MAX ], "
         "width=(int)[ 1, MAX ], "
         "height=(int)[ 1, MAX ];"
    "video/x-raw-yuv-strided,"
         "format=(fourcc)NV12, "
         "framerate=(fraction)[ 0, MAX ], "
         "width=(int)[ 1, MAX ], "
         "height=(int)[ 1, MAX ], "
	 "rowstride=(int)[ 1, MAX ]"
    )
);

enum
{
    ARG_0,
    PROP_SURFACE,
};


static void gst_surfaceflinger_sink_base_init (gpointer g_class);
static void gst_surfaceflinger_sink_class_init (GstSurfaceFlingerSinkClass * klass);
static void gst_surfaceflinger_sink_get_times (GstBaseSink * basesink,
    GstBuffer * buffer, GstClockTime * start, GstClockTime * end);

static gboolean gst_surfaceflinger_sink_setcaps (GstBaseSink * bsink, GstCaps * caps);

static gboolean gst_surfaceflinger_sink_event (GstBaseSink * bsink, GstEvent * event);
static GstFlowReturn gst_surfaceflinger_sink_buffer_alloc (GstBaseSink * bsink,
    guint64 offset, guint size, GstCaps * caps, GstBuffer ** buf);

static GstFlowReturn gst_surfaceflinger_sink_render (GstBaseSink * bsink,
    GstBuffer * buff);
static gboolean gst_surfaceflinger_sink_start (GstBaseSink * bsink);
static gboolean gst_surfaceflinger_sink_stop (GstBaseSink * bsink);

static void gst_surfaceflinger_sink_init (GstSurfaceFlingerSink * surfacesink);
static void gst_surfaceflinger_sink_finalize (GObject * object);
static void gst_surfaceflinger_sink_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_surfaceflinger_sink_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);
static GstStateChangeReturn
gst_surfaceflinger_sink_change_state (GstElement * element, GstStateChange transition);

static GstCaps *gst_surfaceflinger_sink_getcaps (GstBaseSink * bsink);

static GstVideoSinkClass *parent_class = NULL;


static void release_overlaybuffer_callback(const void *buf,void *ssink) {
#if 0
    int i ;
    GstSurfaceFlingerSink *surfacesink = (GstSurfaceFlingerSink *)ssink;
    for (i = 0 ;i < pool->buffer_count ;i++) {
	//GST_WARNING("GST_BUFFER_DATA(pool->buffers[i] %p ,i = [%d]",pool->buffers[i],i);
	if (GST_BUFFER_DATA(pool->buffers[i]) == buf) {
	    gst_buffer_unref (GST_BUFFER (pool->buffers[i]));
	    break;
	}	
    }
#endif
}

static void gst_surfaceflinger_sink_base_init (gpointer g_class)
{
    GstElementClass *element_class = GST_ELEMENT_CLASS (g_class);
    GstSurfaceFlingerSinkClass *gstsurfacesink_class = GST_SURFACEFLINGERSINK_CLASS (g_class);
    gst_element_class_add_pad_template (element_class,
		gst_static_pad_template_get (&sink_factory));

    gst_element_class_set_details (element_class, &gst_surfaceflinger_sink_details);
}


static void gst_surfaceflinger_sink_get_times (GstBaseSink * basesink, GstBuffer * buffer,
    GstClockTime * start, GstClockTime * end)
{
    GstSurfaceFlingerSink *surfacesink;

    surfacesink = GST_SURFACEFLINGERSINK (basesink);

    if (GST_BUFFER_TIMESTAMP_IS_VALID (buffer)) {
	*start = GST_BUFFER_TIMESTAMP (buffer);
	if (GST_BUFFER_DURATION_IS_VALID (buffer)) {
	    *end = *start + GST_BUFFER_DURATION (buffer);
	} else {
	    if (surfacesink->fps_n > 0) {
		*end = *start +
		gst_util_uint64_scale_int (GST_SECOND, surfacesink->fps_d,
					surfacesink->fps_n);
	    }
	}
    }
}

static GstCaps * gst_surfaceflinger_sink_getcaps (GstBaseSink * bsink)
{
    GstSurfaceFlingerSink *surfacesink;
    GstCaps *caps;

    surfacesink = GST_SURFACEFLINGERSINK (bsink);
    return gst_caps_copy(gst_pad_get_pad_template_caps
			(GST_VIDEO_SINK_PAD(surfacesink)));//change by Xuzhi.Tony for yuv format.
}

static gboolean gst_surfaceflinger_sink_setcaps (GstBaseSink * bsink, GstCaps * vscapslist)
{
    GstSurfaceFlingerSink *surfacesink;
    GstStructure *structure;
    const GValue *fps;
    guint32 fourcc;
    GstQuery *query;

    surfacesink = GST_SURFACEFLINGERSINK (bsink);

    if ( surfacesink->setcaps ) {
        return TRUE;
    }

    query = gst_query_new_buffers (vscapslist);

    if (gst_element_query (GST_ELEMENT (surfacesink), query)) {
	gint min_buffers, min_width, min_height;

	gst_query_parse_buffers_count (query, &min_buffers);

	GST_DEBUG_OBJECT (surfacesink, "min_buffers=%d", min_buffers);
	/* XXX need to account for some buffers used by queue, etc.. probably
	 * queue should handle query, pass on to sink pad, and then add some
	 * number of buffers to the min, so this value is dynamic depending
	 * on the pipeline?
	 */
	if (min_buffers != -1) {
	    min_buffers += 3 + NUM_BUFFERS_TO_BE_QUEUED_FOR_OPTIMAL_PERFORMANCE;
	}

	if (min_buffers > surfacesink->num_buffers) {
		surfacesink->num_buffers = min_buffers;
	}
    }
    gst_query_unref (query);

    GST_INFO_OBJECT (surfacesink, "caps after linked: %s",  gst_caps_to_string(vscapslist));

    structure = gst_caps_get_structure (vscapslist, 0);

    fps = gst_structure_get_value (structure, "framerate");
    surfacesink->fps_n = gst_value_get_fraction_numerator (fps);
    surfacesink->fps_d = gst_value_get_fraction_denominator (fps);

    gst_structure_get_int (structure, "width", &surfacesink->width);
    gst_structure_get_int (structure, "height", &surfacesink->height);
    gst_structure_get_fourcc (structure, "format", &fourcc);
    switch (fourcc) {
        case GST_MAKE_FOURCC ('I', '4', '2', '0'):
	    surfacesink->pixel_format = VIDEO_FLINGER_I420; 
            break;
        case GST_MAKE_FOURCC ('N', 'V', '1', '2'):   
	    surfacesink->pixel_format = VIDEO_FLINGER_NV12;
            break;
        default:
	    surfacesink->pixel_format = VIDEO_FLINGER_NV12;
	    break;	
    }

    GST_DEBUG_OBJECT (surfacesink, "framerate=%d/%d", surfacesink->fps_n, surfacesink->fps_d);
    GST_DEBUG_OBJECT (surfacesink, "register framebuffers: width=%d,  height=%d,  pixel_format=%d",  
			surfacesink->width, surfacesink->height, surfacesink->pixel_format);
    /* register frame buffer */
    videoflinger_device_register_framebuffers(
	surfacesink->videodev, surfacesink->width, 
	surfacesink->height, surfacesink->pixel_format,surfacesink->num_buffers);
    videoflinger_device_set_callback(surfacesink->videodev,release_overlaybuffer_callback,surfacesink);
    GST_DEBUG_OBJECT (surfacesink, "gst_surfaceflinger_sink_setcaps return true");
    surfacesink->setcaps = TRUE;
    return TRUE;
}

static gboolean
gst_surfaceflinger_sink_event (GstBaseSink * bsink, GstEvent * event)
{

    GstSurfaceFlingerSink *surfacesink = GST_SURFACEFLINGERSINK (bsink);
    GstEventType type = GST_EVENT_TYPE (event);

    GST_DEBUG_OBJECT (surfacesink, "event %" GST_PTR_FORMAT, event);

    switch (type) {
        case GST_EVENT_CROP:{
            gint top, left, width, height;
            gst_event_parse_crop (event, &top, &left, &width, &height);
            GST_DEBUG_OBJECT(surfacesink,"gst_event_parse_crop top,%d,left,[%d],width,[%d],height [%d]",top,left,width,height);
            if (top >=0 && left >=0 && width >=0 && height >=0)
      	        videoflinger_device_overlay_setcrop(surfacesink->videodev,left,top,width,height);
            return TRUE;
        }
        case GST_EVENT_LIVE_FLUSH:
            g_async_queue_push (surfacesink->pool->avail_buffers, GST_OVERLAY_BUFFER_SENTINEL);
            return TRUE;
        default:{
            if (GST_BASE_SINK_CLASS (parent_class)->event) {
                return GST_BASE_SINK_CLASS (parent_class)->event (bsink, event);
            } else {
            return TRUE;
            }
        }
    }

}

static GstFlowReturn gst_surfaceflinger_sink_render (GstBaseSink * bsink, GstBuffer * buf)
{
    GstSurfaceFlingerSink *surfacesink;
    surfacesink = GST_SURFACEFLINGERSINK (bsink);

    if (buf->parent &&
        (GST_BUFFER_DATA (buf) == GST_BUFFER_DATA (buf->parent)) &&
        (GST_BUFFER_SIZE (buf) == GST_BUFFER_SIZE (buf->parent))) {
        GST_WARNING_OBJECT (surfacesink, "I have a sub-buffer!");
	videoflinger_device_post(surfacesink->videodev, GST_BUFFER_DATA (buf->parent), GST_BUFFER_SIZE (buf->parent));
	return GST_FLOW_OK;
    }
    /* post frame buffer */
    videoflinger_device_post(surfacesink->videodev, GST_BUFFER_DATA (buf), GST_BUFFER_SIZE (buf));

    return GST_FLOW_OK;
}

static gboolean gst_surfaceflinger_sink_start (GstBaseSink * bsink)
{
    GstSurfaceFlingerSink *surfacesink;

    surfacesink = GST_SURFACEFLINGERSINK (bsink);

    /* release previous video device */
    if (surfacesink->videodev != NULL) {
	videoflinger_device_release ( surfacesink->videodev);
	surfacesink->videodev = NULL;
    }

    /* create a new video device */
    GST_DEBUG_OBJECT (surfacesink, "ISurface = %p", surfacesink->isurface);
    surfacesink->videodev = videoflinger_device_create(surfacesink->isurface);
    if ( surfacesink->videodev == NULL) {
	GST_ERROR_OBJECT (surfacesink, "Failed to create video device.");
	return FALSE;
    }    

    GST_DEBUG_OBJECT (surfacesink, "gst_surfaceflinger_sink_start return TRUE");
    return TRUE;
}

static gboolean gst_surfaceflinger_sink_stop (GstBaseSink * bsink)
{
    GstSurfaceFlingerSink *surfacesink;
   
    surfacesink = GST_SURFACEFLINGERSINK (bsink);

    if (surfacesink->videodev != NULL) {
	videoflinger_device_release ( surfacesink->videodev);
	surfacesink->videodev = NULL;
    }

    return TRUE;
}

static void gst_surfaceflinger_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
    GstSurfaceFlingerSink *surfacesink;

    surfacesink = GST_SURFACEFLINGERSINK (object);

    switch (prop_id) {
	case PROP_SURFACE:
	    surfacesink->isurface = g_value_get_pointer(value);
	    GST_DEBUG_OBJECT (surfacesink, "set property: ISureface = %p",  surfacesink->isurface);
	    break;

	default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	    break;
    }
}


static void gst_surfaceflinger_sink_get_property (GObject * object, guint prop_id, GValue * value,
    GParamSpec * pspec)
{
    GstSurfaceFlingerSink *surfacesink;

    surfacesink = GST_SURFACEFLINGERSINK (object);

    switch (prop_id) {
	case PROP_SURFACE:
	    g_value_set_pointer (value, surfacesink->isurface);
	    GST_DEBUG_OBJECT (surfacesink, "get property: ISurface = %p.",  surfacesink->isurface);
	    break;

	default:
	    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	    break;
    }
}

/* TODO: delete me later */
static GstStateChangeReturn gst_surfaceflinger_sink_change_state (GstElement * element, GstStateChange transition)
{
    GstSurfaceFlingerSink *surfacesink;
    GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;

    g_return_val_if_fail (GST_IS_SURFACEFLINGERSINK (element), GST_STATE_CHANGE_FAILURE);
    surfacesink = GST_SURFACEFLINGERSINK (element);

    ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

    switch (transition) {
	default:
	break;
    }
    return ret;
}
static gboolean plugin_init (GstPlugin * plugin)
{
    GST_DEBUG_CATEGORY_INIT (gst_surfaceflinger_sink_debug, "surfaceflingersink",
		0, "Video sink plugin");

    if (!gst_element_register (plugin, "surfaceflingersink", GST_RANK_PRIMARY,
				GST_TYPE_SURFACEFLINGERSINK)) {//upgrade the RANK to use surfaceflingersink default.Xuzhi.Tony
	return FALSE;
    }
    return TRUE;


}
static void gst_surfaceflinger_sink_class_init (GstSurfaceFlingerSinkClass * klass)
{
    GObjectClass *gobject_class;
    GstElementClass *gstelement_class;
    GstBaseSinkClass *gstvs_class;

    gobject_class = (GObjectClass *) klass;
    gstelement_class = (GstElementClass *) klass;
    gstvs_class = (GstBaseSinkClass *) klass;

    parent_class = g_type_class_peek_parent (klass);

    gobject_class->set_property = gst_surfaceflinger_sink_set_property;
    gobject_class->get_property = gst_surfaceflinger_sink_get_property;
    gobject_class->finalize = gst_surfaceflinger_sink_finalize;

    gstelement_class->change_state =
	    GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_change_state);

    g_object_class_install_property (gobject_class, PROP_SURFACE,
		    g_param_spec_pointer("surface", "Surface",
			    "The pointer of ISurface interface", (GParamFlags)(G_PARAM_READWRITE)));

    gstvs_class->set_caps = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_setcaps);
    gstvs_class->buffer_alloc = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_buffer_alloc);
    gstvs_class->event = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_event);
    gstvs_class->get_caps = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_getcaps);
    gstvs_class->get_times = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_get_times);
    gstvs_class->preroll = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_render);
    gstvs_class->render = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_render);
    gstvs_class->start = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_start);
    gstvs_class->stop = GST_DEBUG_FUNCPTR (gst_surfaceflinger_sink_stop);
}

static GstFlowReturn
gst_surfaceflinger_sink_buffer_alloc (GstBaseSink * bsink, guint64 offset, guint size,
    GstCaps * caps, GstBuffer ** buf)
   
{
    
    GstSurfaceFlingerSink *surfacesink = GST_SURFACEFLINGERSINK (bsink);
   
    GstOverlayBuffer *overlaybuf;

    /* initialize the buffer pool if not initialized yet (first buffer): */
    if ((!surfacesink->pool)) {
      /* set_caps() might not be called yet.. so just to make sure: */
        if (!gst_surfaceflinger_sink_setcaps (bsink, caps)) {
		
            return GST_FLOW_ERROR;
        }
        surfacesink->num_buffers = videoflinger_device_get_overlay_buf_count(surfacesink->videodev);

        if (!(surfacesink->pool = gst_overlay_buffer_pool_new (GST_ELEMENT(surfacesink),
                  surfacesink->num_buffers, caps))) {
            return GST_FLOW_ERROR;
        }

        surfacesink->state = STATE_PENDING_STREAMON;

        if (surfacesink->num_buffers != surfacesink->pool->buffer_count) {
            surfacesink->num_buffers = surfacesink->pool->buffer_count;
            g_object_notify (G_OBJECT (surfacesink), "queue-size");
        }
    }
    overlaybuf = gst_overlay_buffer_pool_get (surfacesink->pool, TRUE);
    if (G_LIKELY (overlaybuf)) {
        GST_DEBUG_OBJECT (surfacesink, "allocated buffer: %p", overlaybuf);
        *buf = GST_BUFFER (overlaybuf);
        return GST_FLOW_OK;
    } else {
        return GST_FLOW_ERROR;
    }
}
static void gst_surfaceflinger_sink_init (GstSurfaceFlingerSink * surfacesink)
{
    surfacesink->isurface = NULL;
    surfacesink->videodev = NULL;

    surfacesink->fps_n = 0;
    surfacesink->fps_d = 1;
    surfacesink->width = 720;
    surfacesink->height = 480;
    surfacesink->pixel_format = -1;
    surfacesink->state = 0;
    surfacesink->min_queued_bufs = NUM_BUFFERS_TO_BE_QUEUED_FOR_OPTIMAL_PERFORMANCE;
    surfacesink->num_buffers = PROP_DEF_QUEUE_SIZE;
    surfacesink->setcaps = FALSE;

}
static void gst_surfaceflinger_sink_finalize (GObject * object)
{
    GstSurfaceFlingerSink *surfacesink = GST_SURFACEFLINGERSINK (object);

    G_OBJECT_CLASS (parent_class)->finalize (object);
}


GType gst_surfaceflinger_sink_get_type (void)
{
    static GType surfacesink_type = 0;

    if (surfacesink_type == 0) {
	static const GTypeInfo surfacesink_info = {
		sizeof (GstSurfaceFlingerSinkClass),
		gst_surfaceflinger_sink_base_init,
		NULL,
		(GClassInitFunc) gst_surfaceflinger_sink_class_init,
		NULL,
		NULL,
		sizeof (GstSurfaceFlingerSink),
		0,
		(GInstanceInitFunc) gst_surfaceflinger_sink_init,
		NULL
	};

	surfacesink_type =
	    g_type_register_static (GST_TYPE_BASE_SINK, "GstSurfaceFlingerSink",
					&surfacesink_info, (GTypeFlags)0);
    }
	return surfacesink_type;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR, GST_VERSION_MINOR, 
    "surfaceflingersink", "android surface flinger sink", 
    plugin_init, VERSION,"LGPL","GStreamer","http://gstreamer.net/")


