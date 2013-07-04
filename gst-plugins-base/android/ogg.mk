LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional


LOCAL_ARM_MODE := arm

alsa_LOCAL_SRC_FILES:= \
	ext/ogg/dirac_parse.c     \
	ext/ogg/gstogg.c       	\
	ext/ogg/gstoggmux.c    \
	ext/ogg/gstoggstream.c  \
	ext/ogg/vorbis_parse.c	\
	ext/ogg/gstoggaviparse.c  \
	ext/ogg/gstoggdemux.c  \
	ext/ogg/gstoggparse.c  \
	ext/ogg/gstogmparse.c


LOCAL_SRC_FILES:= $(addprefix ../,$(alsa_LOCAL_SRC_FILES))

LOCAL_SHARED_LIBRARIES := \
	libdl                   \
    	libgstreamer-0.10       \
    	libgstbase-0.10         \
    	libglib-2.0             \
    	libgthread-2.0          \
    	libgmodule-2.0          \
    	libgobject-2.0 		\
	libgstinterfaces-0.10   \
	libgstaudio-0.10	\
	libasound		\
	libogg			\
	libgsttag-0.10		\
	libgstriff-0.10

LOCAL_MODULE:= libgstogg$(GST_PLUGINS_SUFFIX)

#LOCAL_WHOLE_STATIC_LIBRARIES := libasound

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../ext/ogg                   \
    $(LOCAL_PATH)/..                            \
    $(LOCAL_PATH)                                       \
    $(TARGET_OUT_HEADERS)/gstreamer-0.10 \
    $(TARGET_OUT_HEADERS)/glib-2.0          \
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
    external/libxml2/include                        \
    external/gst/libogg/include

LOCAL_C_INCLUDES += external/icu4c/common
LOCAL_SHARED_LIBRARIES += libicuuc


LOCAL_CFLAGS := -DHAVE_CONFIG_H		\
	-DGSTREAMER_BUILT_FOR_ANDROID 	\
	-D_POSIX_SOURCE			\
	$(GST_PLUGINS_BASE_CFLAGS)
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

#It's a gstreamer plugins, and it must be installed on ..../plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins


$(TARGET_OUT)/lib/libgstogg$(GST_PLUGINS_SUFFIX).so:

ALL_PREBUILT += $(TARGET_OUT)/lib/libgstogg$(GST_PLUGINS_SUFFIX).so

include $(BUILD_SHARED_LIBRARY)
