LOCAL_PATH := $(call my-dir)
GST_MAJORMINOR := 0.10
GST_PLUGINS_DUCATI_TOP := $(LOCAL_PATH)

GST_PLUGINS_SUFFIX := -gstplugin-good
ORC_TOP := external/gst/orc
GST_MAJORMINOR := 0.10
ORC_MAJORMINOR := 0.4

GSTREAMER_LIBS_C_INCLUDES :=\
        $(GST_PLUGINS_DUCATI_TOP)                \
        $(GST_PLUGINS_DUCATI_TOP)/gst            \
        $(TARGET_OUT_HEADERS)/glib-2.0  \
        $(TARGET_OUT_HEADERS)/glib-2.0/glib  \
        $(TARGET_OUT_HEADERS)/gstreamer-0.10  \
        $(GSTREAMER_TOP)/libs           \
        $(ORC_C_INCLUDES)		\
	external/libxml2/include	\
	external/icu4c/common		\
	$(GST_PLUGINS_DUCATI_TOP)/../libdce				\
	$(GST_PLUGINS_DUCATI_TOP)/../libdce/packages/ivahd_codecs	\
	$(GST_PLUGINS_DUCATI_TOP)/../libdce/packages/codec_engine	\
	$(GST_PLUGINS_DUCATI_TOP)/../libdce/packages/xdais		\
	$(GST_PLUGINS_DUCATI_TOP)/../libdce/packages/xdctools		\
	hardware/ti/tiler	
	
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

include $(GST_PLUGINS_DUCATI_TOP)/src/Android.mk

