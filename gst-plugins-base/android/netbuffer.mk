LOCAL_PATH:= $(call my-dir)
#----------------------------------------
# include 
gst_netbuffer_COPY_HEADERS_TO := gstreamer-0.10/gst/netbuffer
gst_netbuffer_COPY_HEADERS := \
	../gst-libs/gst/netbuffer/gstnetbuffer.h

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

netbuffer_LOCAL_SRC_FILES:= \
	gst-libs/gst/netbuffer/gstnetbuffer.c

LOCAL_SRC_FILES:= $(addprefix ../,$(netbuffer_LOCAL_SRC_FILES))

LOCAL_SHARED_LIBRARIES := \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0

LOCAL_MODULE:= libgstnetbuffer-0.10

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst-libs/gst/netbuffer \
    $(LOCAL_PATH)/../gst-libs                           \
    $(LOCAL_PATH)/..                                    \
    $(LOCAL_PATH)                                               \
        $(LOCAL_PATH)/../gst/tcp                        \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10    \
        $(TARGET_OUT_HEADERS)/glib-2.0                  \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib     \
        external/libxml2/include

LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_CFLAGS := -DHAVE_CONFIG_H	-DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

LOCAL_COPY_HEADERS_TO := $(gst_netbuffer_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(gst_netbuffer_COPY_HEADERS)
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
