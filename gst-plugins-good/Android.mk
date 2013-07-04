LOCAL_PATH := $(call my-dir)
GST_MAJORMINOR := 0.10
GST_PLUGINS_GOOD_TOP := $(LOCAL_PATH)

GST_PLUGINS_SUFFIX := -gstplugin-good
ORC_TOP := external/gst/orc
GST_MAJORMINOR := 0.10
ORC_MAJORMINOR := 0.4

GSTREAMER_LIBS_C_INCLUDES :=\
        $(GST_PLUGINS_GOOD_TOP)                \
        $(GST_PLUGINS_GOOD_TOP)/gst            \
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
	$(EXTERNAL_SHARED_LIBRARIES)	
	
	

EXTERNAL_SHARED_LIBRARIES :=	\
	libicuuc

GLIB_SHARED_LIBRARIES :=\
        libglib-2.0                 \
        libgthread-2.0              \
        libgmodule-2.0              \
        libgobject-2.0		    \
	libgio-2.0

include $(CLEAR_VARS)

include $(GST_PLUGINS_GOOD_TOP)/gst/alpha/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/apetag/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/audiofx/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/audioparsers/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/auparse/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/autodetect/Android.mk

include $(GST_PLUGINS_GOOD_TOP)/gst/avi/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/cutter/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/debugutils/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/deinterlace/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/effectv/Android.mk

include $(GST_PLUGINS_GOOD_TOP)/gst/equalizer/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/flv/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/flx/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/id3demux/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/icydemux/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/imagefreeze/Android.mk

include $(GST_PLUGINS_GOOD_TOP)/gst/interleave/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/law/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/level/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/matroska/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/monoscope/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/multifile/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/multipart/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/isomp4/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/replaygain/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/rtp/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/rtpmanager/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/rtsp/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/shapewipe/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/smpte/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/spectrum/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/udp/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/videobox/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/videocrop/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/videofilter/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/videomixer/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/wavenc/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/wavparse/Android.mk
include $(GST_PLUGINS_GOOD_TOP)/gst/y4m/Android.mk

include $(GST_PLUGINS_GOOD_TOP)/ext/soup/Android.mk
#include $(GST_PLUGINS_GOOD_TOP)/ext/taglib/Android.mk

