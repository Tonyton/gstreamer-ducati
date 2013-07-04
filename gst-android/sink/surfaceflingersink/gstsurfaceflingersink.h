#ifndef __GST_SURFACEFLINGERSINK_H__
#define __GST_SURFACEFLINGERSINK_H__

#include <gst/gst.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/video.h>
#include "surfaceflinger_wrap.h"
#include "gstoverlaybufferpool.h"
//#include "gstoverlaybufferpooltest.h"

G_BEGIN_DECLS

#define GST_TYPE_SURFACEFLINGERSINK \
  (gst_surfaceflinger_sink_get_type())
#define GST_SURFACEFLINGERSINK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_SURFACEFLINGERSINK,GstSurfaceFlingerSink))
#define GST_SURFACEFLINGERSINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_SURFACEFLINGERSINK,GstSurfaceFlingerSinkClass))
#define GST_IS_SURFACEFLINGERSINK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SURFACEFLINGERSINK))
#define GST_IS_SURFACEFLINGERSINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SURFACEFLINGERSINK))


typedef struct _GstSurfaceFlingerSink GstSurfaceFlingerSink;
typedef struct _GstSurfaceFlingerSinkClass GstSurfaceFlingerSinkClass;

struct _GstSurfaceFlingerSink {
	GstVideoSink videosink;
	GstOverlayBufferPool *pool;
	gpointer isurface;
	gint pixel_format;
	VideoFlingerDeviceHandle videodev;
	int width, height;
	int fps_n, fps_d;
	guint32 num_buffers;
	guint32 min_queued_bufs;
	guint8 state;
	gboolean setcaps;
	
};

struct _GstSurfaceFlingerSinkClass {
	GstBaseSinkClass parent_class;
};

/*
 * State values
 */
enum
{
  STATE_OFF = 0,
  STATE_PENDING_STREAMON,
  STATE_STREAMING
};

GType gst_surfaceflinger_sink_get_type(void);


G_END_DECLS

#endif /* __GST_SURFACEFLINGERSINK_H__ */
