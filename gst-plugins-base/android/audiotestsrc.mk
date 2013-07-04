LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

audiotestsrc_LOCAL_SRC_FILES:= \
	gst/audiotestsrc/gstaudiotestsrc.c

LOCAL_SRC_FILES:= $(addprefix ../,$(audiotestsrc_LOCAL_SRC_FILES))

LOCAL_SHARED_LIBRARIES := \
    libgstcontroller-0.10   \
    libgstaudio-0.10        \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0	    \
    libicuuc		    \
    liborc-0.4

LOCAL_MODULE:= libgstaudiotestsrc$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst/audiotestsrc                   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                                       \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
    $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
    external/libxml2/include                        \
    external/icu4c/common


LOCAL_CFLAGS := -DHAVE_CONFIG_H -DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

#It's a gstreamer plugins, and it must be installed on ..../system/plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
