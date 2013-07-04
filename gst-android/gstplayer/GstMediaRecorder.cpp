#define LOG_NDEBUG 0

#undef LOG_TAG
#define LOG_TAG "GstMediaRecorder"

#include <sys/ioctl.h>
#include <alsa/asoundlib.h>

#include "GstMediaRecorder.h"
#include <utils/Log.h>
#include <camera/CameraParameters.h>
#include <utils/Errors.h>
#include <media/AudioSystem.h>
#include <surfaceflinger/ISurface.h>
#include <camera/ICamera.h>
#include <camera/Camera.h>
#include <fcntl.h>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappbuffer.h>
#include <binder/MemoryBase.h>
#include <cutils/properties.h>
#include <sys/time.h>

//gale
#define USE_TI_ENCODER  1

//#define AUDIO_ENCODER_LAME  1

//#define USE_SOFT_ENCODER  1

#ifdef USE_SOFT_ENCODER
#undef USE_TI_ENCODER
#endif

#define AUDIO_RATE      44100
#define VIDEO_FRAME_RATE     12
#define VIDEO_DIV            1
//#define DEBUG_GST_WARNING //gst debug flag xuzhi.Tony

using namespace android;

GstMediaRecorder::GstMediaRecorder()
{
	LOGV("GstMediaRecorder constructor");
	mCamera = NULL;
	mSurface = NULL;
	mFlags = 0;
	
	mVideoBin = NULL;
	mAudioBin = NULL;
	mPipeline = NULL;
	
	mUse_video_src = FALSE;
	mUse_audio_src = FALSE;
	
	mVideoSrc = NULL;
	mAudioSrc = NULL;

	mOutFilePath = NULL;

	mMaxDuration = -1;
	mMaxFileSize = -1;
	mCurrentFileSize = 0;
	mTimer = NULL;

	//default init
	mFps = VIDEO_FRAME_RATE;
	mWidth = 176;
	mHeight = 144;
	mOutput_format = OUTPUT_FORMAT_DEFAULT;
	mVideo_encoder = VIDEO_ENCODER_DEFAULT;
	mAudio_encoder = AUDIO_ENCODER_DEFAULT;
	mAudio_source  = AUDIO_SOURCE_MIC;
	frame_count = 0;

	mAudioSampleRate = AUDIO_RATE;
	mAudioChannels = 2;
	mAudioBitrate = 192000;
	mVideoBitrate = 786432;
	mVTMode = 0;
	mIPeriod = 0;
	mIMBRefreshMode = 0;
	if (!g_thread_supported ()) {
		LOGV("GstMediaRecorder GLib thread init");
		g_thread_init (NULL);
	}

	// setup callback listener
	mCameraListener = new AndroidGstCameraListener(this);
	/* create and init the EOS mutex now */
	mEOSlock = g_mutex_new ();
	g_mutex_lock (mEOSlock);
	mIsEos = FALSE;

}

GstMediaRecorder::~GstMediaRecorder()
{
	LOGV("GstMediaRecorder destructor");
	if (mCamera != NULL) {
		mCamera->setListener(NULL);
		if ((mFlags & FLAGS_HOT_CAMERA) == 0) {
			LOGV("GstMediaRecorder camera was cold when we started, stopping preview");
			mCamera->stopPreview();
		}
		/* FIXME:gale */		
#if 1		
		if (mFlags & FLAGS_SET_CAMERA) {
			LOGV("GstMediaRecorder unlocking camera to return to app");
			mCamera->unlock();
		//gale add			
		//	mCamera->disconnect();
		} else {
			LOGV("GstMediaRecorder disconnect from camera");
			mCamera->disconnect();
		}
		mCamera.clear();
#endif		
	}
	mFlags = 0;
	// don't send eos but release the pipeline
	release_pipeline();
	if(mOutFilePath) {
		g_free(mOutFilePath);
	}
	mCameraListener.clear();
	// free mutex
	g_mutex_free (mEOSlock);
	mEOSlock = NULL;
	// free timer
	g_timer_destroy(mTimer);
	mTimer = NULL;
//gale
/*
	if(mHwdep_handle) {
		snd_hwdep_close(mHwdep_handle);
	}
*/	

}

status_t GstMediaRecorder::init()
{
	LOGV("GstMediaRecorder init");
	return OK;
}

status_t GstMediaRecorder::setAudioSource(audio_source as)
{
	mAudio_source = as;
	mUse_audio_src = TRUE;
	switch (as)
	{
	case AUDIO_SOURCE_DEFAULT:
		LOGV("GstMediaRecorder setAudioSource DEFAULT (MIC)");
		// the default value is equal to AUDIO_SOURCE_MIC	
		mAudio_source = AUDIO_SOURCE_MIC;
		break;
	case AUDIO_SOURCE_MIC:
		LOGV("GstMediaRecorder setAudioSource MIC");
		break;		
	default:
		break;
	}
	return OK;
}

status_t GstMediaRecorder::setVideoSource(video_source vs)
{
	LOGV("GstMediaRecorder setVideoSource %s", (vs==VIDEO_SOURCE_DEFAULT)?"VIDEO_SOURCE_DEFAULT":"VIDEO_SOURCE_CAMERA");
	switch (vs) 
	{
	case VIDEO_SOURCE_DEFAULT:
		// the default value is equal to VIDEO_SOURCE_CAMERA
		mUse_video_src = TRUE;
		break;
	case VIDEO_SOURCE_CAMERA:
		mUse_video_src = TRUE;
		break;
	default: 
		mUse_video_src = FALSE;
		break;
	}
	return OK;
}

status_t GstMediaRecorder::setOutputFormat(output_format of)
{
	LOGV("GstMediaRecorder setOutputFormat %d", of);
	mOutput_format = of;
	switch(of)
	{
	case OUTPUT_FORMAT_DEFAULT:
		LOGV("GstMediaRecorder setOutputFormat DEFAULT (3GPP)");
		mOutput_format = OUTPUT_FORMAT_THREE_GPP;
		break;
	}
	return OK;
}

status_t GstMediaRecorder::setAudioEncoder(audio_encoder ae)
{
	
	/* FIXME:gale */
        LOGV("gst recorder only support mp3 encoder now! And remeber to changed your app about the file Suffix ");
        mAudio_encoder = AUDIO_ENCODER_MP3;
	return OK;
}

status_t GstMediaRecorder::setVideoEncoder(video_encoder ve)
{
	mVideo_encoder = VIDEO_ENCODER_MPEG_4_SP;
	return OK;
}

status_t GstMediaRecorder::setVideoSize(int width, int height)
{
	LOGV("GstMediaRecorder setVideoSize width=%d height=%d", width, height);
	mWidth = width;
	mHeight = height;
	return OK;
}

status_t GstMediaRecorder::setVideoFrameRate(int frames_per_second)
{
	LOGV("GstMediaRecorder setVideoFrameRate %d fps", frames_per_second);
	mFps = frames_per_second;
	if(mFps != VIDEO_FRAME_RATE)
	   mFps = VIDEO_FRAME_RATE;
	return OK;
}

status_t GstMediaRecorder::setCamera(const sp<ICamera>& camera)
{
	LOGV("GstMediaRecorder setCamera");
	
	mFlags &= ~ FLAGS_SET_CAMERA | FLAGS_HOT_CAMERA;
	if (camera == NULL) {
		LOGV("camera is NULL");
		return OK;
	}

	// Connect our client to the camera remote
	mCamera = Camera::create(camera);
	if (mCamera == NULL) {
		LOGV("Unable to connect to camera");
		return OK;
	}

	LOGV("Connected to camera");
	mFlags |= FLAGS_SET_CAMERA;
	if (mCamera->previewEnabled()) {
		mFlags |= FLAGS_HOT_CAMERA;
		LOGV("camera is hot");
	}
	mUse_video_src = TRUE;
	return OK;
}

status_t GstMediaRecorder::setPreviewSurface(const sp<ISurface>& surface)
{
	LOGV("GstMediaRecorder setPreviewSurface");
	mSurface = surface;
	return OK;
}

status_t GstMediaRecorder::setOutputFile(const char *path)
{
	LOGV("GstMediaRecorder setOutputFile %s", path);
	mOutFilePath = g_strdup_printf("file://%s", path);
		mOutFilePath_fd = -1;
	return OK;
}
status_t GstMediaRecorder::setOutputFile(int fd, int64_t offset, int64_t length)
{
	LOGV("GstMediaRecorder setOutputFile for fd : fd=%d offset=%lld length=%lld", fd, offset, length);
	GST_UNUSED(offset);
	GST_UNUSED(length);
	mOutFilePath = g_strdup_printf("fd://%d",fd);
		mOutFilePath_fd = fd;
	return OK;
}

status_t GstMediaRecorder::setParameters(const String8& params)
{
	LOGV("GstMediaRecorder setParameters");

	if(strstr(params, "max-duration") != NULL) {
		sscanf(params,"max-duration=%lld", &mMaxDuration);
	}
	if(strstr(params, "max-filesize") != NULL) {
		sscanf(params,"max-filesize=%lld", &mMaxFileSize);
	}
	if(strstr(params, "audio-param-sampling-rate") != NULL) {
		sscanf(params,"audio-param-sampling-rate=%lld", &mAudioSampleRate);
			if ( (mAudioSampleRate < 8000) || (mAudioSampleRate > 48000) )
			mAudioSampleRate = 48000;
	}
    //gale add	
    if(mAudioSampleRate != AUDIO_RATE)
    	mAudioSampleRate = AUDIO_RATE;
		
	if(strstr(params, "audio-param-number-of-channels") != NULL) {
		sscanf(params,"audio-param-number-of-channels=%lld", &mAudioChannels);
		if ( (mAudioChannels < 0) || (mAudioChannels > 2) )
			mAudioChannels = 2;
	}
	if(strstr(params, "audio-param-encoding-bitrate") != NULL) {
		sscanf(params,"audio-param-encoding-bitrate=%lld", &mAudioBitrate);
		if ( (mAudioBitrate < 0) || (mAudioBitrate > 192000) )
			mAudioBitrate = 128000;
	}

	if(strstr(params, "video-param-encoding-bitrate") != NULL) {
		sscanf(params,"video-param-encoding-bitrate=%lld", &mVideoBitrate);
		if ( (mVideoBitrate < 0) || (mVideoBitrate > 786432) )
			mVideoBitrate = 360000;
	} 

	if(strstr(params, "vt-mode") != NULL) {
		sscanf(params,"vt-mode=%d", &mVTMode);
	}
	if(strstr(params, "i-mb-refresh") != NULL) {
		sscanf(params,"i-mb-refresh=%d", &mIMBRefreshMode);
	}
	if(strstr(params, "i-period") != NULL) {
		sscanf(params,"i-period=%d", &mIPeriod);
	}
	if(strstr(params, "video-bitrate") != NULL) {
		sscanf(params,"video-bitrate=%lld", &mVideoBitrate);
	}
	//gale
	if (mCamera != NULL) {
	//send the parameters to the camera to set specific effect or others parameters
	//	mCamera->setParameters(params);
	//	mCamera->setParameters(String8("preview-format=yuv422i-yuyv"));
	}
	LOGV("GstMediaRecorder  max duration %lld max file size %lld", mMaxDuration, mMaxFileSize);
	return OK;

}

status_t GstMediaRecorder::setListener(const sp<IMediaPlayerClient>& listener)
{
	LOGV("GstMediaRecorder setListener");
	mListener = listener;
	return OK;
}

status_t GstMediaRecorder::prepare()
{
	LOGV("GstMediaRecorder prepare");
	// create a camera if the app didn't supply one
	if ((mCamera == 0) && (mUse_video_src == TRUE)) {
		mCamera = Camera::connect();
	}

	if (mCamera != NULL && mSurface != NULL) {
		LOGV("GstMediaRecorder set preview display surface");
		mCamera->setPreviewDisplay(mSurface);
	}
	
	if (mCamera != NULL) {
		LOGV("GstMediaRecorder set camera parameters width=%d height=%d fps=%d", mWidth, mHeight, mFps);
		String8 s = mCamera->getParameters();
		CameraParameters p(s);
		p.setPreviewSize(mWidth, mHeight);

		if (mCamera->previewEnabled()) {
			s = p.flatten();
			mCamera->setParameters(s);
			mFlags |= FLAGS_HOT_CAMERA;
			LOGV("GstMediaRecorder preview camera already enabled");
		}else {
			p.setPreviewFrameRate(mFps + 5);
			s = p.flatten();
			mCamera->setParameters(s);
			mCamera->startPreview();
			mFlags &= ~FLAGS_HOT_CAMERA;
		}
	}
	
	return build_record_graph();
}

GstStateChangeReturn GstMediaRecorder::wait_for_set_state(int timeout_msec)
{
	GstMessage *msg;
	GstStateChangeReturn ret = GST_STATE_CHANGE_FAILURE;

	/* Wait for state change */
	msg = gst_bus_timed_pop_filtered (GST_ELEMENT_BUS(mPipeline),
			timeout_msec * GST_MSECOND, /* in nanosec */
			(GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_ASYNC_DONE));

	if (msg) {
		if ((GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ASYNC_DONE))
			ret = GST_STATE_CHANGE_SUCCESS;

		gst_message_unref(msg);
	}

	return ret;
}

status_t GstMediaRecorder::start()
{
	GstStateChangeReturn ret;
	LOGV("GstMediaRecorder start recording");

	if(mPipeline == NULL) {
		LOGV("GstMediaRecorder start pipeline not created");
		return OK;
	}

	ret = gst_element_set_state (mPipeline, GST_STATE_PLAYING);
	
	// set the audio source device, open micro
//gale	
/*	
	const sp<IAudioFlinger>& audioFlinger = AudioSystem::get_audio_flinger();
	if (audioFlinger != 0) {
		LOGV("GstMediaRecorder start recording: unmute the microphone");	
		audioFlinger->setMicMute(FALSE);
	}
*/
	if (mCamera != NULL) {
		mCamera->setListener(mCameraListener);
		mCamera->startRecording();
	}

	if( ret == GST_STATE_CHANGE_ASYNC) {
		ret = wait_for_set_state(2000); // wait 2 second for state change
	}

	if(ret != GST_STATE_CHANGE_SUCCESS) {
		goto bail;
	}
	
	LOGV("GstMediaRecorder pipeline is in playing state");
	return OK;

bail:

	LOGV("GstMediaRecorder start failed");

	if (mCamera != NULL) {
		mCamera->stopRecording();
	}

	release_pipeline();

	return OK; // return OK to avoid execption in java
}

status_t GstMediaRecorder::stop()
{
	LOGV("GstMediaRecorder stop recording");
	if(mPipeline == NULL) {
		LOGV("GstMediaRecorder stop pipeline not created");
		return OK;
	}

	frame_count = 0;
	if (mCamera != NULL) {	
		mCamera->stopRecording();
		mCamera->setListener(NULL);
	}
	/* Send audio & video Eos */
	sendEos();
	
	if (mIsEos)	 
      	g_mutex_lock (mEOSlock);
//gale add      	
	if (mCamera != NULL) {
		mCamera->setListener(NULL);
		if ((mFlags & FLAGS_HOT_CAMERA) == 0) {
			LOGV("GstMediaRecorder camera was cold when we started, stopping preview");
			mCamera->stopPreview();
		}
/* FIXME :gale */
#if 0		
		if (mFlags & FLAGS_SET_CAMERA) {
			LOGV("GstMediaRecorder unlocking camera to return to app");
			mCamera->unlock();
//gale add			
			mCamera->disconnect();
		} else {
			LOGV("GstMediaRecorder disconnect from camera");
			mCamera->disconnect();
		}
		mCamera.clear();
#endif		
	}      	
	// EOS has been receive now release the pipeline 
	return release_pipeline();

}

status_t GstMediaRecorder::release_pipeline()
{
	if(mPipeline == NULL) {
		return OK;
	}

	LOGV("GstMediaRecorder change pipeline state to NULL");
	gst_element_set_state (mPipeline, GST_STATE_NULL);
	gst_element_get_state (mPipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
	LOGV("GstMediaRecorder unref pipeline");
	gst_object_unref(mPipeline);
	mPipeline = NULL;
	mVideoBin = NULL;
	mAudioBin = NULL;
	mVideoSrc = NULL;

	if (mOutFilePath_fd > -1) {
		::close(mOutFilePath_fd);
		mOutFilePath_fd = -1;
	}
	LOGV("GstMediaRecorder stop exit");
	return OK;
}

status_t GstMediaRecorder::close()
{
	LOGV("GstMediaRecorder close");
	return OK;
}

status_t GstMediaRecorder::reset()
{
	LOGV("GstMediaRecorder reset");
	release_pipeline();
	return OK;
}

status_t GstMediaRecorder::getMaxAmplitude(int *max)
{
//    *max = 5;
    return OK;
}

// create a video bin appsrc->icbvideoenc->capsfilter
GstElement* GstMediaRecorder::create_video_bin()
{
	GstElement *vbin;
	GstElement *video_src, *ffmpegcolorspace;
	GstElement *video_encoder, *video_format_filter, *video_src_queue;
	GstElement *video_queue;
	GstPad *pad;

	video_queue = NULL;

	if(mUse_video_src == FALSE) {
		// nothing the create in this case
		return NULL;
	}

	LOGV("GstMediaRecorder create video appsrc");
	
	video_src = gst_element_factory_make("appsrc", "videosrc");
	
	if(!video_src) {
		LOGV("GstMediaRecorder can't create video src");
		return NULL;
	}


	g_object_set(G_OBJECT(video_src),"is-live", TRUE, NULL); // it is a pseudo live source
	g_object_set(G_OBJECT(video_src),"max-bytes", (guint64)mWidth*mHeight*3, NULL); // max byte limit equal to 2 frames
	g_object_set(G_OBJECT(video_src),"format", 2, NULL); // byte format 
	g_object_set(G_OBJECT(video_src),"block", TRUE, NULL); // Block push-buffer when max-bytes are queued
	g_object_set(G_OBJECT(video_src),"do-timestamp", TRUE, NULL);
	

	LOGV("GstMediaRecorder setting video appsrc");
	g_object_set(G_OBJECT(video_src) ,"caps", 
			gst_caps_new_simple ("video/x-raw-yuv", 
					     "format", GST_TYPE_FOURCC, GST_MAKE_FOURCC('I','4','2','0'),						
					     "width", G_TYPE_INT, mWidth,
					     "height", G_TYPE_INT, mHeight,	 
					     "framerate", GST_TYPE_FRACTION, mFps / VIDEO_DIV, 1,
					      NULL),
			NULL);

	switch(mVideo_encoder)
	{
		case VIDEO_ENCODER_DEFAULT:
		case VIDEO_ENCODER_MPEG_4_SP:		
			LOGV("GstMediaRecorder set video caps: video/mpeg, width=%d, height=%d, framerate=%d/1", mWidth, mHeight, mFps);
			
#ifdef USE_TI_ENCODER
			video_encoder = gst_element_factory_make("dmaienc_h264",NULL);
			//	g_object_set(G_OBJECT(video_encoder), "maxbitrate", 1000000, NULL);
			g_object_set(G_OBJECT(video_encoder), "intraframeinterval", 1, NULL);
			g_object_set(G_OBJECT(video_encoder), "encodingpreset", 1, NULL);
			g_object_set(G_OBJECT(video_encoder), "targetbitrate", 2000000, NULL);
			//	g_object_set(G_OBJECT(video_encoder), "engineName", "codecServer", NULL);
			//	g_object_set(G_OBJECT(video_encoder), "codecName", "h264enc", NULL);	
			//	g_object_set(G_OBJECT(video_encoder), "genTimeStamps", TRUE, NULL);
			//	g_object_set(G_OBJECT(video_encoder), "frameRate", mFps / VIDEO_DIV, NULL);

#endif

#ifdef USE_SOFT_ENCODER
			video_encoder = gst_element_factory_make("ffenc_mpeg4",NULL);
#endif			
			if(!video_encoder) {
				LOGE("GstMediaRecorder can't create video encoder");
				goto remove_video_src;
			}

			video_format_filter = gst_element_factory_make("capsfilter",NULL);

#if 0			
			g_object_set(G_OBJECT(video_format_filter) , "caps",
						gst_caps_new_simple ("video/mpeg", 
							"width", G_TYPE_INT, mWidth,
							"height", G_TYPE_INT, mHeight,	 
							"framerate", GST_TYPE_FRACTION, mFps, 1,
							"mpegversion", G_TYPE_INT, 4,
							NULL),		
							NULL);
			break;
#endif 

			g_object_set(G_OBJECT(video_format_filter) , "caps",
						gst_caps_new_simple ("video/x-h264", 
							"width", G_TYPE_INT, mWidth,
							"height", G_TYPE_INT, mHeight,	 
							"framerate", GST_TYPE_FRACTION, mFps / VIDEO_DIV, 1,
							NULL),		
							NULL);
			break;			
	}
	
	
	/* VT support */
	{
	
		GValue framerate = { 0 };
		int framerate_num = mFps;
		int framerate_denom = 1;
		int bitrate = mVideoBitrate;
		int i_period = mIPeriod;
		int i_mb_refresh = mIMBRefreshMode;
		int vt_mode = mVTMode;





		/* ! take care of framerate because of fraction type, 
		   use g_object_set_property with a gvalue instead g_object_set */
		g_value_init (&framerate, GST_TYPE_FRACTION);
		gst_value_set_fraction (&framerate, framerate_num, framerate_denom);




#ifdef USE_SOFT_ENCODER		
		g_object_set(G_OBJECT(video_encoder) , "caps",
				gst_caps_new_simple (   "video/mpeg",
					"width", G_TYPE_INT, mWidth,
					"height", G_TYPE_INT, mHeight,
					"framerate", GST_TYPE_FRACTION, mFps / VIDEO_DIV, 1,
					"mpegversion", G_TYPE_INT, 4,
					NULL),
				NULL );

#endif
        	LOGV("GstMediaRecorder set video encoder caps: video/mpeg, width=%d, height=%d, framerate=%d/1, mpegversion=%d,", mWidth, mHeight, mFps, 4);                                                 

		g_value_unset(&framerate);
	}

	video_queue = gst_element_factory_make("queue", NULL);

	vbin = gst_bin_new("vbin");
	if(!vbin) {
		LOGE("GstMediaRecorder can't create vbin");
		goto remove_video_format_filter;
	}
	
	ffmpegcolorspace = gst_element_factory_make("ffmpegcolorspace", NULL);

	gst_bin_add_many (GST_BIN_CAST(vbin), video_src, ffmpegcolorspace, video_encoder,  video_format_filter, video_queue, NULL);
	
	LOGV("GstMediaRecorder link video_src->->queue->video_encoder->video_format_filter->queue");
	if(!gst_element_link_many(video_src , ffmpegcolorspace, video_encoder, video_format_filter, video_queue, NULL)) {	
	
		LOGE("GstMediaRecorder can't link elements");
		goto remove_vbin;
	}

	LOGV("GstMediaRecorder create src ghost pad in vbin");

	pad = gst_element_get_static_pad (video_queue, "src");
	gst_element_add_pad (vbin, gst_ghost_pad_new ("src", pad));
	gst_object_unref (pad);
	mVideoSrc = video_src;

	return vbin;

remove_vbin:
	gst_object_unref(vbin);
remove_video_format_filter:
	gst_object_unref(video_format_filter);
	gst_object_unref(video_queue);
remove_video_encoder:
	gst_object_unref(video_encoder);
remove_video_src:
	gst_object_unref(video_src);
	return NULL;
}


// create a audio bin icbaudiosrc->icbaudioenc->capsfilter
GstElement*	GstMediaRecorder::create_audio_bin()
{
	GstElement *abin;
	GstElement *audio_src, *audio_enc, *audio_format_filter;
	GstElement *audio_queue;
	GstPad *pad;
	gint buffer_time = 0;
	gint recordsrc;
	if(mUse_audio_src == FALSE) {
		return NULL;
	}
	LOGV("GstMediaRecorder create_audio_bin");

	LOGV("GstMediaRecorder create audio src");
	audio_src = gst_element_factory_make("alsasrc","alsasrc0"); // modify by xuzhi.Tony 
	g_object_set(G_OBJECT(audio_src), "provide-clock", FALSE, NULL);
	g_object_set(G_OBJECT(audio_src), "slave-method", 2, NULL);
	g_object_set(G_OBJECT(audio_src), "do-timestamp", TRUE, NULL);
	//    g_object_set(G_OBJECT(audio_src), "blocksize", (gint)(4604), NULL);

	buffer_time = GST_SECOND / (AUDIO_RATE * 2 / 4096);
	g_object_set(G_OBJECT(audio_src), "buffer-time", 4096 * GST_SECOND/AUDIO_RATE, NULL);
	//    g_object_set(G_OBJECT(audio_src), "latency-time", 10000, NULL);

	if(!audio_src) {
		LOGE("GstMediaRecorder can't create audio source");
		return NULL;
	}
	
#ifdef AUDIO_ENCODER_LAME	
	audio_enc = gst_element_factory_make("lame", NULL);	
		if(!audio_enc) {
		LOGE("GstMediaRecorder can't create audio encoder");
		goto remove_audio_src;
	}
//	g_object_set(G_OBJECT(audio_enc), "bitrate", (gint64)(16000), "freq", (gint)AUDIO_RATE, (gchar*)NULL); 
    	g_object_set(G_OBJECT(audio_enc), "bitrate", 128, NULL);
	g_object_set(G_OBJECT(audio_enc), "vbr", "new", NULL);
	g_object_set(G_OBJECT(audio_enc), "strict-iso", TRUE);
	
	audio_format_filter = gst_element_factory_make("capsfilter",NULL);
        g_object_set(G_OBJECT(audio_format_filter) , "caps",
                     gst_caps_new_simple ("audio/mpeg",
                                          "rate", G_TYPE_INT, AUDIO_RATE,
                                           "channels", G_TYPE_INT, 2,
					   					   "mpegversion",G_TYPE_INT, 1,
					   					   "layer",G_TYPE_INT, 3,
                                            NULL),
                                            NULL);
#else		
	LOGV("GstMediaRecorder create audio encoder");
	audio_enc = gst_element_factory_make("ffenc_mp2", "ffenc_mp20"); // xuzhi.Tony :use mp3 enc
	

	if(!audio_enc) {
		LOGE("GstMediaRecorder can't create audio encoder");
		goto remove_audio_src;
	}
	mAudio_encoder = AUDIO_ENCODER_MP3;// xuzhi.Tony: set the AUDIO_ENCODER_MP3 for mp3 recoder only
	// configure audio encoder
	LOGV("GstMediaRecorder set properties to audio encoder");

	audio_format_filter = gst_element_factory_make("capsfilter",NULL);
        g_object_set(G_OBJECT(audio_format_filter) , "caps",
                     gst_caps_new_simple ("audio/mpeg",
                                          "rate", G_TYPE_INT, AUDIO_RATE,
                                           "channels", G_TYPE_INT, 2,
					   						"mpegversion",G_TYPE_INT,1,
					   						"layer",G_TYPE_INT,2,
                                            NULL),
                                            NULL);

#endif
	audio_queue =  gst_element_factory_make("queue", "audio_queue");
	g_object_set(G_OBJECT(audio_queue), "max-size-time", 2000000000, NULL);

	LOGV("GstMediaRecorder create audio bin");
	abin = gst_bin_new("abin");

	if(!abin) {
		LOGE("GstMediaRecorder can't create abin");
		goto remove_audio_enc;
	}
	

	LOGV("GstMediaRecorder add element to audio bin");
	gst_bin_add_many (GST_BIN_CAST(abin), audio_src, audio_enc, audio_format_filter, audio_queue, NULL);

	LOGV("GstMediaRecorder link audio_src->audio_enc");
	if(!gst_element_link_many(audio_src, audio_enc, audio_format_filter, audio_queue, NULL)) {
		LOGE("GstMediaRecorder can't link audio_src->audio_enc");
		goto remove_abin;
	}	

	LOGV("GstMediaRecorder create src ghost pad in abin");
	pad = gst_element_get_static_pad (audio_queue, "src");
	gst_element_add_pad (abin, gst_ghost_pad_new ("src", pad));
	gst_object_unref (pad);

	mAudioSrc = audio_src;
	return abin;

remove_abin:
	gst_object_unref(abin);
remove_audio_enc:
	gst_object_unref(audio_format_filter);
	gst_object_unref(audio_queue);
	gst_object_unref(audio_enc);
remove_audio_src:
	gst_object_unref(audio_src);
	return NULL;
}

/*static*/ 
GstBusSyncReply GstMediaRecorder::bus_message(GstBus *bus, GstMessage * msg, gpointer data)
{
	GstMediaRecorder *mediarecorder = (GstMediaRecorder*)data;
	if(bus)	{
		// do nothing except remove compilation warning
	}
	

	switch(GST_MESSAGE_TYPE(msg)) {
		case GST_MESSAGE_EOS: {
			LOGV("GstMediaRecorder bus receive message EOS");
			/* unlock mutex  */
			g_mutex_unlock (mediarecorder->mEOSlock);
			break;
		}
		case GST_MESSAGE_ERROR: {
			GError* err;
			gchar* debug;

			gst_message_parse_error(msg, &err, &debug);
			LOGE("GstMediaRecorder bus receive message ERROR %d: %s from %s", err->code, err->message, debug);
				
			if (mediarecorder->mListener != NULL) {
				mediarecorder->mListener->notify(MEDIA_RECORDER_EVENT_ERROR, MEDIA_RECORDER_ERROR_UNKNOWN,err->code);
			}
			g_error_free(err);
			g_free(debug);
			break;
		}
		default:
			// do nothing
			break;
	}

	return GST_BUS_PASS;
}

void GstMediaRecorder::sendEos()
{ 
      if(!mIsEos) {
		LOGV("GstMediaRecorder : forcing EOS");
  		// only sen EOS once
		mIsEos = TRUE;
		/* stop audio recording */
		if (mAudioSrc != NULL) {			
			/* send EOS */
			//g_object_set(G_OBJECT(mAudioSrc), "eos", TRUE, NULL);
			/* xuzhi.Tony: mAudioSrc don't have property name eos . replace with this line. */
			gst_element_send_event (mAudioBin, gst_event_new_eos ());
	   		
			/* reset mAudioSrc (will avoid to send another eos upon stop request */
			mAudioSrc = NULL;
		}
		        
		/* stop video recording */
		if (mVideoSrc != NULL) {
			/* send EOS */		
			gst_app_src_end_of_stream(GST_APP_SRC(mVideoSrc));		
	    	gst_element_send_event(mVideoSrc,gst_event_new_eos ());
			/* reset mVideoSrc (will avoid to send another eos upon stop request */
			mVideoSrc = NULL;
		}		        
	}    
}


/*static*/ void	GstMediaRecorder::handoff(GstElement* object, GstBuffer* buffer, gpointer user_data)
{
	GstMediaRecorder *mediarecorder = (GstMediaRecorder*)user_data;
	gulong microsecond;
	int sizeMargin=0;
	mediarecorder->mCurrentFileSize += GST_BUFFER_SIZE(buffer);
	
	if(mediarecorder->mTimer == NULL) {
		mediarecorder->mTimer = g_timer_new();
	}

//	LOGE("GstMediaRecorder handoff current file size %lld duration %lld", mediarecorder->mCurrentFileSize, (gint64)g_timer_elapsed(mediarecorder->mTimer, &microsecond)*1000);

	if((mediarecorder->mMaxDuration != -1) && (mediarecorder->mMaxDuration <= (gint64)(g_timer_elapsed(mediarecorder->mTimer, &microsecond)*1000) )) {
		LOGV("GstMediaRecorder reached recording time limit");
		if(mediarecorder->mListener != NULL) {
			mediarecorder->mListener->notify(MEDIA_RECORDER_EVENT_INFO, MEDIA_RECORDER_INFO_MAX_DURATION_REACHED, 0);
		}
		/* Send audio & video Eos */
		mediarecorder->sendEos();

		g_object_set(object, "signal-handoffs", FALSE, NULL);
		return;
	}

	/* consider a margin before stopping (because we will still get data to flush the pipeline */
	if (mediarecorder->mAudioSrc != NULL)
   	      sizeMargin+=3000; /* 3kB for Audio recording */

	if (mediarecorder->mVideoSrc != NULL)
   	      sizeMargin+=50000; /* 50kB for video recording */

	if((mediarecorder->mMaxFileSize != -1) && (mediarecorder->mMaxFileSize <= mediarecorder->mCurrentFileSize + sizeMargin)) {
		LOGV("GstMediaRecorder reached recording size limit");
		if(mediarecorder->mListener != NULL) {
			mediarecorder->mListener->notify(MEDIA_RECORDER_EVENT_INFO, MEDIA_RECORDER_INFO_MAX_FILESIZE_REACHED, 0);
		}
		/* Send audio & video Eos */
		mediarecorder->sendEos();

		g_object_set(object, "signal-handoffs", FALSE, NULL);
		return;
	}
}

/*static*/ void GstMediaRecorder::debug_log (GstDebugCategory * category, GstDebugLevel level,
							const gchar * file, const gchar * function, gint line,
							GObject * object, GstDebugMessage * message, gpointer data)
{
	gint pid;
	GstClockTime elapsed;
	GstMediaRecorder* mediarecorder = (GstMediaRecorder*)data;

	GST_UNUSED(file);
	GST_UNUSED(object);

	if (level > gst_debug_category_get_threshold (category))
		return;

	pid = getpid ();

	elapsed = GST_CLOCK_DIFF (mediarecorder->mGst_info_start_time,
	  gst_util_get_timestamp ());


	g_printerr ("%" GST_TIME_FORMAT " %5d %s %s %s:%d %s\r\n",
		GST_TIME_ARGS (elapsed),
		pid,
		gst_debug_level_get_name (level),
		gst_debug_category_get_name (category), function, line,
		gst_debug_message_get (message));
}



status_t GstMediaRecorder::build_record_graph ()
{
	GstElement *muxer, *identity, *sink;
	GstBus *bus;
	GError *err = NULL;
	int argc=3;
	char **argv;
	char str0[] =  "";
	//char str1[] =  "";
	char str2[] =  "";
	char trace[PROPERTY_VALUE_MAX];
		  
	argv = (char **)malloc(sizeof(char *) * argc);
	argv[0] = (char *) malloc( sizeof(char) * (strlen(str0) + 1));
	argv[2] = (char *) malloc( sizeof(char) * (strlen(str2) + 1));
	strcpy( argv[0], str0);
	strcpy( argv[2], str2);

	char value[PROPERTY_VALUE_MAX];
	property_get("persist.gst.debug", value, "0");
	LOGV("persist.gst.debug property %s", value);
	argv[1] = (char *) malloc( sizeof(char) * (strlen(value) + 1));
	strcpy( argv[1], value);  

	property_get("persist.gst.trace", trace, "/dev/console");
	LOGV("persist.gst.trace property %s", trace);
	LOGV("route the trace to %s", trace);
	int fd_trace = open(trace, O_RDWR);
	if(fd_trace != 1) {
		dup2(fd_trace, 0);
		dup2(fd_trace, 1);
		dup2(fd_trace, 2);
		::close(fd_trace);
	}

	mGst_info_start_time = gst_util_get_timestamp ();
#ifdef DEBUG_GST_WARNING  //debug for gst
  	gst_debug_set_default_threshold(GST_LEVEL_WARNING);
  	gst_debug_add_log_function (gst_debug_log_default,NULL);
#else
  	gst_debug_remove_log_function (debug_log);
  	gst_debug_add_log_function (debug_log, this);
  	gst_debug_remove_log_function (gst_debug_log_default);
#endif

	LOGV("GstMediaRecorder gstreamer init check");
	// init gstreamer 	
	if(!gst_init_check (&argc, &argv, &err)) {
		LOGE ("GstMediaRecorder Could not initialize GStreamer: %s\n", err ? err->message : "unknown error occurred");
		if (err) {
			g_error_free (err);
		}
	}

	LOGV("GstMediaRecorder create pipeline");
	mPipeline = gst_pipeline_new (NULL);
	if(!mPipeline) {
		LOGE("GstMediaRecorder can't create pipeline");
		goto bail;
	}

	// verbose info (as gst-launch -v)
	// Activate the trace with the command: "setprop persist.gst.verbose 1"
	property_get("persist.gst.verbose", value, "0");
	LOGV("persist.gst.verbose property = %s", value);
	if (value[0] == '1') {
		LOGV("Activate deep_notify");
		g_signal_connect (mPipeline, "deep_notify",
				G_CALLBACK (gst_object_default_deep_notify), NULL);
	}

	LOGV("GstMediaRecorder register bus callback");	
	bus = gst_pipeline_get_bus(GST_PIPELINE (mPipeline));
	gst_bus_set_sync_handler (bus, bus_message, this);
	gst_object_unref (bus);

	if((mOutput_format == OUTPUT_FORMAT_RAW_AMR) && (mUse_video_src == FALSE) ) {
		// in RAW AMR format don't use any muxer
		LOGV("GstMediaRecorder use identity as muxer in RAW_AMR format");
		muxer = gst_element_factory_make("identity", NULL);
	} 
	else {

#ifdef USE_TI_ENCODER
		LOGV("GstMediaRecorder use avimux");
		muxer = gst_element_factory_make("ffmux_avi", NULL);
#else
		LOGV("GstMediaRecorder use ffmux_avi");		
		muxer = gst_element_factory_make("ffmux_avi", NULL);
#endif
//matroskamux		
	}

	if(!muxer) {
		LOGE("GstMediaRecorder can't create muxer");
		goto bail1;
	}

	gst_bin_add (GST_BIN_CAST(mPipeline), muxer);

	LOGV("GstMediaRecorder create sink from uri %s", mOutFilePath);
	sink = gst_element_make_from_uri(GST_URI_SINK, mOutFilePath, NULL);
	if(!sink) {
		LOGE("GstMediaRecorder can't create sink %s", mOutFilePath);
		goto bail1;
	}

	g_object_set(G_OBJECT(sink), "async", FALSE, NULL);

	gst_bin_add (GST_BIN_CAST(mPipeline), sink);
	
	LOGV("GstMediaRecorder create identity");
	identity = gst_element_factory_make("identity", NULL);

	if(!identity) {
		LOGE("GstMediaRecorder can't identity element");
		goto bail1;
	}
	gst_bin_add (GST_BIN_CAST(mPipeline), identity);
	
	mCurrentFileSize = 0;
	g_signal_connect (identity, "handoff", G_CALLBACK (handoff), this);
	g_object_set(G_OBJECT(identity), "signal-handoffs", TRUE, NULL);
        mAudioBin = create_audio_bin();
        if(mAudioBin) {
                gst_bin_add (GST_BIN_CAST(mPipeline),mAudioBin);
                LOGV("GstMediaRecorder link abin to muxer");
                if(!gst_element_link(mAudioBin, muxer)) {
                        LOGE("GstMediaRecorder can't link abin to muxer");
                }
        }

	
	mVideoBin = create_video_bin();
	if(mVideoBin) {
		gst_bin_add (GST_BIN_CAST(mPipeline),mVideoBin); 
		LOGV("GstMediaRecorder link vbin to muxer");
		if(!gst_element_link(mVideoBin, muxer)) {
			LOGE("GstMediaRecorder can't link vbin to muxer");
		}
	}

	if(!mAudioBin && !mVideoBin)
	{
		LOGE("GstMediaRecorder both audiobin and videobin are NULL !!!!!");
		goto bail1;
	}
	LOGV("GstMediaRecorder link muxer->identity->sink");
	if(!gst_element_link_many(muxer, identity, sink, NULL)) {
		LOGE("GstMediaRecorder can't link muxer->identity->sink");
	}


	gst_element_set_state (mPipeline, GST_STATE_READY);
	gst_element_get_state (mPipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
	return OK;

bail1:
	LOGV("GstMediaRecorder change pipeline state to NULL");
	gst_element_set_state (mPipeline, GST_STATE_NULL);
	gst_element_get_state (mPipeline, NULL, NULL, GST_CLOCK_TIME_NONE);
	LOGV("GstMediaRecorder  unref pipeline");
	gst_object_unref(mPipeline);
bail:
	mPipeline = NULL;
	mVideoBin = NULL;
	mAudioBin = NULL;
	mVideoSrc = NULL;
	return UNKNOWN_ERROR;
}

static struct timeval time_tmp;


void GstMediaRecorder::postDataTimestamp(nsecs_t timestamp, int32_t msgType, const sp<IMemory>& dataPtr)
{
  
	ssize_t offset = 0;
	size_t size = 0;
	GstBuffer* buffer;
	GstClockTime duration;
	GST_UNUSED(timestamp);
	GST_UNUSED(msgType);
	GstFlowReturn ret;

//	LOGV("postDataTimestamp");
	if(mVideoSrc == NULL) {
		LOGE(" record_callback the videosrc don't exist");
		mCamera->stopRecording();
		return ;
	}


	//gale add
     
    	size = mWidth * mHeight *  3 / 2; 
	gchar *tmp = (gchar*)g_malloc0 (size);
    	memcpy(tmp, dataPtr->pointer(), size);
	//YUV420SP conver to YUV420P
	{
		int i, j, k, l;
		i = mWidth * mHeight;
		k = i / 2;
		l = i / 4;
		gchar * tmp1 = (gchar *)g_malloc(k);
		for(j = 0; j < l; j ++)
		{
		  memcpy(tmp1 + j, tmp + i + 2 * j, 1);
		  memcpy(tmp1 + l + j, tmp + i + j * 2 + 1, 1);		
		}
		memcpy(tmp + i, tmp1, k);
		g_free(tmp1);
	
	}    	
    	buffer = gst_app_buffer_new (tmp, size, (GstAppBufferFinalizeFunc)g_free, tmp); 
     
    	mCamera->releaseRecordingFrame(dataPtr); 
    	    
	GST_BUFFER_SIZE(buffer) = size; //needed to build correct timestamp in basesrc
	
	GstClock *clock;
	GstClockTime global_time;
	frame_count++;
	duration = gst_util_uint64_scale_int (1, GST_SECOND,  mFps );				
	if ((clock = GST_ELEMENT_CLOCK (mVideoSrc))) {
     	 	/* we have a clock, get base time and ref clock */
      		timestamp = GST_ELEMENT (mVideoSrc)->base_time;
      		gst_object_ref (clock);
    	} else {
     	 /* no clock, can't set timestamps */
      		timestamp = GST_CLOCK_TIME_NONE;
    	}
    	
    	if (G_LIKELY (clock)) {
      		/* the time now is the time of the clock minus the base time */
      		timestamp = gst_clock_get_time (clock) - timestamp;
//      	LOGV("--------------------------base time is %lld-----------clock is %lld", \
		      GST_ELEMENT (mVideoSrc)->base_time,gst_clock_get_time (clock));
//      	timestamp = gst_clock_get_time (clock);
		
		global_time = gst_clock_get_time (clock);
		gst_pipeline_set_new_stream_time((GstPipeline *)mPipeline, global_time);
      		gst_object_unref (clock);

      		/* if we have a framerate adjust timestamp for frame latency */
      		if (GST_CLOCK_TIME_IS_VALID (duration)) {
        		if (timestamp > duration)
         	 		timestamp -= duration;
        		else
          			timestamp = 0;
     	 	}
	}
	GST_BUFFER_TIMESTAMP (buffer) = timestamp;
	GST_BUFFER_DURATION (buffer) = duration;
//	LOGV("++++++++++++++++++++++++++++++++++++++++timastamp is %lld, duration is %lld, frame count is %d",\
		 GST_BUFFER_TIMESTAMP (buffer), GST_BUFFER_DURATION (buffer), frame_count);
	ret = gst_app_src_push_buffer(GST_APP_SRC(mVideoSrc), buffer);
	
}

// camera callback interface
void AndroidGstCameraListener::postData(int32_t msgType, const sp<IMemory>& dataPtr)
{
	GST_UNUSED(msgType); GST_UNUSED(dataPtr); 
}

void AndroidGstCameraListener::postDataTimestamp(nsecs_t timestamp, int32_t msgType, const sp<IMemory>& dataPtr)
{	
	if ((mRecorder != NULL) && (msgType == CAMERA_MSG_VIDEO_FRAME)) {
		mRecorder->postDataTimestamp(timestamp, msgType, dataPtr);
	}
}

