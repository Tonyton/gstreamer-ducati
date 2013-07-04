LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

gst_special_COPY_HEADERS_TO := gstreamer-0.10/gst/floatcast
gst_special_COPY_HEADERS_BASE :=        \
        gst-libs/gst/floatcast/floatcast.h

gst_special_COPY_HEADERS := $(addprefix ../,$(gst_special_COPY_HEADERS_BASE))


tcp_LOCAL_SRC_FILES_BASE:= \
	gst/tcp/gsttcpplugin.c  	\
	gst/tcp/gsttcp.c 			\
	gst/tcp/gstmultifdsink.c 	\
	gst/tcp/gsttcpclientsrc.c 	\
	gst/tcp/gsttcpclientsink.c 	\
	gst/tcp/gsttcpserversrc.c 	\
	gst/tcp/gsttcpserversink.c 	\
	android/gst/tcp/gsttcp-enumtypes.c 	\
	android/gst/tcp/gsttcp-marshal.c

LOCAL_SRC_FILES:= $(addprefix ../,$(tcp_LOCAL_SRC_FILES_BASE))

LOCAL_SHARED_LIBRARIES := \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0 			\
	libgstdataprotocol-0.10

LOCAL_MODULE:= libgsttcp$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst/tcp                            \
    $(LOCAL_PATH)/../gst-libs                           \
    $(LOCAL_PATH)/..                                    \
    $(LOCAL_PATH)                                               \
    $(LOCAL_PATH)/gst/tcp                                   \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10    \
    $(TARGET_OUT_HEADERS)/glib-2.0                  \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib     \
    external/libxml2/include

LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_CFLAGS := -DHAVE_CONFIG_H  -DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)

LOCAL_COPY_HEADERS_TO := $(gst_special_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(gst_special_COPY_HEADERS)

#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

#It's a gstreamer plugins, and it must be installed on ..../plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
