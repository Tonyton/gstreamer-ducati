LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm


audioresample_LOCAL_SRC_FILES:= \
	gst/audioresample/gstaudioresample.c \
	gst/audioresample/resample.c \
	gst/audioresample/speex_resampler_float.c \
	gst/audioresample/speex_resampler_double.c

audioresample_C_INCLUDES := $(LOCAL_PATH)/ \

LOCAL_SRC_FILES := $(addprefix ../,$(audioresample_LOCAL_SRC_FILES))
LOCAL_C_INCLUDES := $(audioresample_C_INCLUDES)
 
LOCAL_SHARED_LIBRARIES := \
    libgstaudio-0.10        \
    libgstreamer-0.10       \
    libgstbase-0.10         \
    libglib-2.0             \
    libgthread-2.0          \
    libgmodule-2.0          \
    libgobject-2.0 			\
    libgstpbutils-0.10		\
    libicuuc		   \
    liborc-0.4		  \
    liborc-test-0.4 

LOCAL_MODULE:= libgstaudioresample$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../gst/audioresample   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)/../gst-libs                   \
    $(LOCAL_PATH)                                       \
        $(LOCAL_PATH)/gst-libs/gst/audio    \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
        $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
        external/libxml2/include	\
	external/icu4c/common		\
	external/gst/orc

LOCAL_CFLAGS := -DFLOATING_POINT -DOUTSIDE_SPEEX -DRANDOM_PREFIX=gst -DDISABLE_ORC -DHAVE_CONFIG_H -DGSTREAMER_BUILT_FOR_ANDROID \
	$(GST_PLUGINS_BASE_CFLAGS)
LOCAL_PRELINK_MODULE := false


#It's a gstreamer plugin so it should be installed in plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
