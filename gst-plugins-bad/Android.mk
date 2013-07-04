LOCAL_PATH := $(call my-dir)
GST_MAJORMINOR := 0.10
GST_PLUGINS_BAD_TOP := $(LOCAL_PATH)

GST_PLUGINS_SUFFIX := -gstplugin-bad
ORC_TOP := external/gst/orc
GST_MAJORMINOR := 0.10
ORC_MAJORMINOR := 0.4

GSTREAMER_LIBS_C_INCLUDES :=\
        $(GST_PLUGINS_BAD_TOP)                \
        $(GST_PLUGINS_BAD_TOP)/gst-libs                \
        $(GST_PLUGINS_BAD_TOP)/gst            \
        $(TARGET_OUT_HEADERS)/glib-2.0  \
        $(TARGET_OUT_HEADERS)/glib-2.0/glib  \
        $(TARGET_OUT_HEADERS)/gstreamer-0.10  \
        $(GSTREAMER_TOP)/libs           \
        $(ORC_C_INCLUDES)		\
	external/libxml2/include	\
	external/icu4c/common

ORC_C_INCLUDES :=                               \
        $(ORC_TOP)                              \
        $(ORC_TOP)/android                      \
        $(ORC_TOP)/orc

ZLIB_C_INCLUDES := external/zlib

GST_PLUGINS_BASE_LIBS_C_INCLUDES :=             \
        $(GSTREAMER_LIBS_C_INCLUDES)            \
	$(ZLIB_C_INCLUDES)

ORC_SHARED_LIBRARIES :=                         \
        liborc-$(ORC_MAJORMINOR)                \
        liborc-test-$(ORC_MAJORMINOR)

GST_SHARED_LIBRARIES :=                 \
        libgstreamer-$(GST_MAJORMINOR)  \
	libgstbase-$(GST_MAJORMINOR)	\
	libgstcontroller-$(GST_MAJORMINOR)	\
	libgsttag-0.10			\
	libgstaudio-0.10		\
	libgstvideo-0.10		\
	libgstfft-0.10			\
	libgstpbutils-0.10		\
	libgstriff-0.10			\
	libgstrtp-0.10			\
	libgstrtsp-0.10			\
	libgstnetbuffer-0.10		\
	libgstsdp-0.10			\
	libgstinterfaces-0.10		\
	libgstapp-0.10			\
	$(EXTERNAL_SHARED_LIBRARIES)	\
	$(ORC_SHARED_LIBRARIES)	
	
	

EXTERNAL_SHARED_LIBRARIES :=	\
	libicuuc

GLIB_SHARED_LIBRARIES :=\
        libglib-2.0                 \
        libgthread-2.0              \
        libgmodule-2.0              \
        libgobject-2.0		    \
	libgio-2.0

include $(CLEAR_VARS)


include $(GST_PLUGINS_BAD_TOP)/gst-libs/gst/interfaces/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst-libs/gst/basecamerabinsrc/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/h264parse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/audiobuffer/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/autoconvert/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/bayer/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/camerabin2/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/adpcmdec/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/adpcmenc/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/aiff/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/asfmux/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/videoparsers/Android.mk
include $(GST_PLUGINS_BAD_TOP)/ext/faad/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/sdp/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/hls/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/jp2kdecimator/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/segmentclip/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/dtmf/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mpeg4videoparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/siren/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/dataurisrc/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/rawparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/videomaxrate/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/tta/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/videosignal/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/coloreffects/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/scaletempo/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/jpegformat/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/freeze/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/geometrictransform/Android.mk

include $(GST_PLUGINS_BAD_TOP)/gst/librfb/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/vmnc/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/interlace/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mxf/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/cdxaparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mpegpsmux/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/legacyresample/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/gaudieffects/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/liveadder/Android.mk
#include $(GST_PLUGINS_BAD_TOP)/gst/nsf/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/dvdspu/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mpegvideoparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mpegtsdemux/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/debugutils/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/subenc/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/id3tag/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/frei0r/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/patchdetect/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/speed/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/sdi/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/festival/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/y4m/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/rtpmux/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/pcapparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/nuvdemux/Android.mk

include $(GST_PLUGINS_BAD_TOP)/gst/colorspace/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/pnm/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mve/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/videomeasure/Android.mk
#include $(GST_PLUGINS_BAD_TOP)/gst/invtelecine/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/hdvparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/stereo/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/rtpvp8/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/mpegdemux/Android.mk
include $(GST_PLUGINS_BAD_TOP)/gst/ivfparse/Android.mk
include $(GST_PLUGINS_BAD_TOP)/ext/libmms/Android.mk
