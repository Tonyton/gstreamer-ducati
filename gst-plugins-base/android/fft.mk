LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

gst_fft_COPY_HEADERS_TO := gstreamer-0.10/gst/fft
gst_fft_COPY_HEADERS_BASE := \
        gst-libs/gst/fft/gstfft.h \
        gst-libs/gst/fft/gstffts16.h \
        gst-libs/gst/fft/gstffts32.h \
        gst-libs/gst/fft/gstfftf32.h \
        gst-libs/gst/fft/gstfftf64.h	


gst_fft_COPY_HEADERS := $(addprefix ../,$(gst_fft_COPY_HEADERS_BASE))


fft_LOCAL_SRC_FILES :=                      \
        gst-libs/gst/fft/gstfft.c \
        gst-libs/gst/fft/gstffts16.c \
        gst-libs/gst/fft/gstffts32.c \
        gst-libs/gst/fft/gstfftf32.c \
        gst-libs/gst/fft/gstfftf64.c \
        gst-libs/gst/fft/kiss_fft_s16.c \
        gst-libs/gst/fft/kiss_fft_s32.c \
        gst-libs/gst/fft/kiss_fft_f32.c \
        gst-libs/gst/fft/kiss_fft_f64.c \
        gst-libs/gst/fft/kiss_fftr_s16.c \
        gst-libs/gst/fft/kiss_fftr_s32.c \
        gst-libs/gst/fft/kiss_fftr_f32.c \
        gst-libs/gst/fft/kiss_fftr_f64.c

LOCAL_SRC_FILES:= $(addprefix ../,$(fft_LOCAL_SRC_FILES))

LOCAL_MODULE := libgstfft-0.10

LOCAL_C_INCLUDES :=                     \
    $(LOCAL_PATH)/../gst-libs/gst/fft                   \
    $(LOCAL_PATH)/../gst-libs                   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                                       \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
    $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
    external/libxml2/include                        

LOCAL_CFLAGS :=                         \
    -DHAVE_CONFIG_H

LOCAL_SHARED_LIBRARIES := \
        libdl                   \
        libgstreamer-0.10       \
        libgstbase-0.10         \
        libglib-2.0             \
        libgthread-2.0          \
        libgmodule-2.0          \
        libgobject-2.0          \
        libgstinterfaces-0.10   \
        libgstaudio-0.10        \
        libasound

LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_COPY_HEADERS_TO := $(gst_fft_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(gst_fft_COPY_HEADERS)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS = eng optional
include $(BUILD_SHARED_LIBRARY)

