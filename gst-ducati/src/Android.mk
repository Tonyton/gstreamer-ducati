LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH:=$(TARGET_OUT)/plugins
LOCAL_SRC_FILES:= \
        gstducatirvdec.c \
        gstducativp7dec.c \
        gstducativp6dec.c \
        gstducativc1dec.c \
        gstducatimpeg2dec.c \
        gstducatimpeg4dec.c \
        gstducatih264dec.c \
        gstducatividdec.c \
        gstducatibufferpool.c \
        gstducati.c 

LOCAL_SHARED_LIBRARIES :=	\
	$(GST_SHARED_LIBRARIES)	\
	$(GLIB_SHARED_LIBRARIES)\
	libz			\
	libtimemmgr		\
	libdce

LOCAL_MODULE:= libgstducati

LOCAL_C_INCLUDES := 			\
	$(LOCAL_PATH)			\
	$(GST_PLUGINS_GOOD_TOP)/android-internal		\
	$(GSTREAMER_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)/gst-libs 

LOCAL_CFLAGS := \
	-DHAVE_CONFIG_H		\
	-DBUILD_WITH_ANDROID

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng
include $(BUILD_SHARED_LIBRARY)
