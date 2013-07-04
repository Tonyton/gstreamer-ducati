LOCAL_PATH:= $(call my-dir)
#----------------------------------------
# include 
gst_rtsp_COPY_HEADERS_TO := gstreamer-0.10/gst/rtsp
gst_rtsp_COPY_HEADERS_BASE := \
	gst-libs/gst/rtsp/gstrtspbase64.h \
	gst-libs/gst/rtsp/gstrtspdefs.h \
	gst-libs/gst/rtsp/gstrtspconnection.h \
	gst-libs/gst/rtsp/gstrtspextension.h \
	gst-libs/gst/rtsp/gstrtspmessage.h \
	gst-libs/gst/rtsp/gstrtsprange.h \
	gst-libs/gst/rtsp/gstrtsptransport.h \
	gst-libs/gst/rtsp/gstrtspurl.h \
	android/gst-libs/gst/rtsp/gstrtsp-enumtypes.h

gst_rtsp_COPY_HEADERS := $(addprefix ../,$(gst_rtsp_COPY_HEADERS_BASE))

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

rtsp_LOCAL_SRC_FILES_BASE:= \
	gst-libs/gst/rtsp/gstrtspbase64.c \
	gst-libs/gst/rtsp/gstrtspdefs.c \
	gst-libs/gst/rtsp/gstrtspconnection.c \
	gst-libs/gst/rtsp/gstrtspextension.c \
	gst-libs/gst/rtsp/gstrtspmessage.c \
	gst-libs/gst/rtsp/gstrtsprange.c \
	gst-libs/gst/rtsp/gstrtsptransport.c \
	gst-libs/gst/rtsp/gstrtspurl.c  \
	android/gst-libs/gst/rtsp/gstrtsp-marshal.c \
	android/gst-libs/gst/rtsp/gstrtsp-enumtypes.c

LOCAL_SRC_FILES:= $(addprefix ../,$(rtsp_LOCAL_SRC_FILES_BASE))

LOCAL_SHARED_LIBRARIES := \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0

LOCAL_MODULE:= libgstrtsp-0.10

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst-libs/gst/rtsp  \
    $(LOCAL_PATH)/../gst-libs           \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                                       \
    $(LOCAL_PATH)/gst-libs/gst/rtsp     \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
    $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
    external/libxml2/include

LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_CFLAGS := -DHAVE_CONFIG_H -DINET_ADDRSTRLEN=16 -DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false


LOCAL_COPY_HEADERS_TO := $(gst_rtsp_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(gst_rtsp_COPY_HEADERS)
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
