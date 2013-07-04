LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH:=$(TARGET_OUT)/plugins
LOCAL_SRC_FILES:= \
	gstsouphttpsrc.c

LOCAL_SHARED_LIBRARIES :=	\
	$(GST_SHARED_LIBRARIES)	\
	libglib-2.0		\
	libgthread-2.0		\
	libgmodule-2.0		\
	libgobject-2.0		\
	libz			\
	libgio-2.0		\
	libsoup

LOCAL_MODULE:= libgstsouphttpsrc

LOCAL_C_INCLUDES := 			\
	$(LOCAL_PATH)			\
	$(GST_PLUGINS_GOOD_TOP)/android-internal		\
	$(GSTREAMER_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)/gst-libs \
	external/gst/libsoup

LOCAL_CFLAGS := \
	-DHAVE_CONFIG_H		\
	-DBUILD_WITH_ANDROID

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng
include $(BUILD_SHARED_LIBRARY)
