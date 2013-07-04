LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH :=$(TARGET_OUT)/plugins

LOCAL_SRC_FILES:= 		\
	gstffmpeg.c	\
	gstffmpegprotocol.c	\
	gstffmpegcodecmap.c	\
	gstffmpegutils.c	\
	gstffmpegenc.c	\
	gstffmpegdec.c	\
	gstffmpegcfg.c	\
	gstffmpegdemux.c	\
	gstffmpegmux.c    \
	gstffmpegdeinterlace.c	\
	gstffmpegaudioresample.c     

LOCAL_SHARED_LIBRARIES := \
	libgstreamer-0.10	 \
	libgstcontroller-0.10	\
	libgstbase-0.10		\
        libgsttag-0.10                  \
        libgstaudio-0.10                \
        libgstvideo-0.10                \
        libgstfft-0.10                  \
        libgstpbutils-0.10              \
        libgstriff-0.10                 \
        libgstrtp-0.10                  \
        libgstrtsp-0.10                 \
        libgstnetbuffer-0.10            \
        libgstsdp-0.10                  \
        libgstinterfaces-0.10           \
        libgstapp-0.10                  \
	libglib-2.0		   \
	libgthread-2.0		\
	libgmodule-2.0		\
	libgobject-2.0		\
	libz		\
	libicuuc		\
        libavutil       \
        libavformat	\
	libavcodec
	

		

LOCAL_MODULE:= libgstffmpeg

LOCAL_C_INCLUDES := 			\
	$(GST_FFMPEG_TOP)/android-internal\
        $(TARGET_OUT_HEADERS)/glib-2.0  \
        $(TARGET_OUT_HEADERS)/glib-2.0/glib  \
        $(TARGET_OUT_HEADERS)/gstreamer-0.10  \
	$(GST_FFMPEG_TOP)/gst-libs/ext/libav/libavutil\
	$(GST_FFMPEG_TOP)/gst-libs/ext/libav/libavformat\
	$(GST_FFMPEG_TOP)/gst-libs/ext/libav/libavcodec\
	$(GST_FFMPEG_TOP)/gst-libs/ext/libav\
	external/libxml2/include	\
	external/icu4c/common

LOCAL_CFLAGS := \
	-DHAVE_CONFIG_H  			
LOCAL_PRELINK_MODULE :=false

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
