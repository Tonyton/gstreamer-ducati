#ifndef  GST_METADATARETRIEVER_DRIVER_INC
#define  GST_METADATARETRIEVER_DRIVER_INC

#include <gst/gst.h>
#include <utils/List.h>
#include <utils/Log.h>
#include <media/mediametadataretriever.h>

namespace android {

typedef enum {
        GST_AUTOPLUG_SELECT_TRY,
        GST_AUTOPLUG_SELECT_EXPOSE,
        GST_AUTOPLUG_SELECT_SKIP
} GstAutoplugSelectResult;

class GstMetadataRetrieverDriver
{
public:
	GstMetadataRetrieverDriver();
	~GstMetadataRetrieverDriver();

	void 	setup(int mode);
	void 	setDataSource(const char* url);
	void 	setFdDataSource(int fd, gint64 offset, gint64 length);
	void 	prepareSync();
	void 	seekSync(gint64 p);
	void 	quit();
	gint64 	getPosition();
	gint64 	getDuration();
	int	getStatus();
	void 	getVideoSize(int* width, int* height);
	void 	endOfData();
	gchar* 	getMetadata(gchar* tag);
	void 	getCaptureFrame(guint8 **data);
	void 	getAlbumArt(guint8 **data, guint64 *size);
	void 	getFrameRate(int* framerate);

private:
	GstElement* 		mPipeline;
	GstElement* 		mAppsrc;


	gchar*			mUri;

	static GstBusSyncReply bus_message(GstBus *bus, GstMessage * msg, gpointer data);
	
	GstTagList *		mTag_list;

	void			parseMetadataInfo();

	guint64			mFdSrcOffset_min;
	guint64			mFdSrcOffset_max;
	guint64			mFdSrcOffset_current;
	gint			mFd;
	

	static gboolean have_video_caps (GstElement * uridecodebin, GstCaps * caps);
	static gboolean are_audio_caps (GstElement * uridecodebin, GstCaps * caps);
	static gboolean are_video_caps (GstElement * uridecodebin, GstCaps * caps);

	static gboolean autoplug_continue (GstElement* object, GstPad* pad, GstCaps* caps, GstMetadataRetrieverDriver* ed);

	static void		source_changed_cb (GObject *obj, GParamSpec *pspec, GstMetadataRetrieverDriver* ed);
	static void		need_data (GstElement * object, guint size, GstMetadataRetrieverDriver* ed);
	static gboolean	seek_data (GstElement * object, guint64 offset, GstMetadataRetrieverDriver* ed);

	int			mState;

	gboolean		mHaveStreamVideo;

	GstBuffer		*mAlbumArt;

	void			init_gstreamer();
	GstClockTime    	mGst_info_start_time;
	static void		debug_log (GstDebugCategory * category, GstDebugLevel level,
							const gchar * file, const gchar * function, gint line,
							GObject * object, GstDebugMessage * message, gpointer data);

	int			mMode;
	

    	static GstAutoplugSelectResult autoplug_select_cb (GstElement *bin, GstPad *pad, 
          						GstCaps *caps, GstElementFactory *factory, gpointer user_data);
};

}; // namespace android

#endif   /* ----- #ifndef GST_METADATARETRIEVER_DRIVER_INC  ----- */

