#ifndef __GST_AUDIOFLINGERSINK_H__
#define __GST_AUDIOFLINGERSINK_H__

#include <gst/gst.h>
#include <gst/audio/gstaudiosink.h>
#include "audioflinger_wrapper.h"

G_BEGIN_DECLS

#define GST_TYPE_AUDIOFLINGERSINK            (gst_audioflinger_sink_get_type())
#define GST_AUDIOFLINGERSINK(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_AUDIOFLINGERSINK,GstAudioFlingerSink))
#define GST_AUDIOFLINGERSINK_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_AUDIOFLINGERSINK,GstAudioFlingerSinkClass))
#define GST_IS_AUDIOFLINGERSINK(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_AUDIOFLINGERSINK))
#define GST_IS_AUDIOFLINGERSINK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_AUDIOFLINGERSINK))

typedef struct _GstAudioFlingerSink GstAudioFlingerSink;
typedef struct _GstAudioFlingerSinkClass GstAudioFlingerSinkClass;

struct _GstAudioFlingerSink {
	GstAudioSink    sink;

	AudioFlingerDeviceHandle audioflinger_device;
	gboolean   m_init;
	gint   bytes_per_sample;
	gfloat m_volume;
	gboolean   m_mute;
	gpointer   m_audiosink;
	GstCaps *probed_caps;
};

struct _GstAudioFlingerSinkClass {
	GstAudioSinkClass parent_class;
};

GType gst_audioflinger_sink_get_type(void);

G_END_DECLS

#endif /* __GST_AUDIOFLINGERSINK_H__ */
