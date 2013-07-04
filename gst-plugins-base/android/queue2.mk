LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_ARM_MODE := arm

queue2_LOCAL_SRC_FILES_BASE:= \
	gst/playback/gstqueue2.c  \
    gst/playback/gstplay-marshal.c

LOCAL_SRC_FILES:= $(addprefix ../,$(queue2_LOCAL_SRC_FILES_BASE))


LOCAL_SHARED_LIBRARIES := \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0 			\
	libgstpbutils-0.10

LOCAL_MODULE:= libgstqueue2$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst/playback           \
    $(LOCAL_PATH)/../gst-libs                   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                                       \
    $(LOCAL_PATH)/gst/playback              \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
    $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
    external/libxml2/include

LOCAL_CFLAGS := -DHAVE_CONFIG_H	\
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

#It's a gstreamer plugins, and it must be installed on ..../system/plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins

include $(BUILD_SHARED_LIBRARY)
