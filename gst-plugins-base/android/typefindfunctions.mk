LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

typefindfunctions_LOCAL_SRC_FILES:= \
	gst/typefind/gsttypefindfunctions.c

LOCAL_SRC_FILES:= $(addprefix ../,$(typefindfunctions_LOCAL_SRC_FILES))

LOCAL_SHARED_LIBRARIES :=   \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libgstpbutils-0.10	    \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0	    \
    libgio-2.0

LOCAL_MODULE:= libgsttypefindfunctions$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES := 				\
    $(LOCAL_PATH)/../gst/typefind               \
    $(LOCAL_PATH)/../gst-libs                   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                               \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 	\
    $(TARGET_OUT_HEADERS)/glib-2.0          	\
    $(TARGET_OUT_HEADERS)/glib-2.0/glib 	\
    external/libxml2/include


LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_CFLAGS := -DHAVE_CONFIG_H	 -DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

#It's a gstreamer plugins, and it must be installed on ..../plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
