
LOCAL_PATH := $(call my-dir)

GST_FFMPEG_TOP := $(LOCAL_PATH)

include $(CLEAR_VARS)

include $(GST_FFMPEG_TOP)/gst-libs/ext/libav/Android.mk
include $(GST_FFMPEG_TOP)/ext/ffmpeg/Android.mk

