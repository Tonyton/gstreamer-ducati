LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	surfaceflinger_wrap.cpp \
	gstoverlaybufferpool.c  \
	gstsurfaceflingersink.c

	
LOCAL_SHARED_LIBRARIES := \
	libgstreamer-0.10       \
	libglib-2.0             \
	libgthread-2.0          \
	libgmodule-2.0          \
	libgobject-2.0          \
	libgstbase-0.10         \
	libgstvideo-0.10	\
	libcutils               \
	libutils                \
	libui			\
	libsurfaceflinger 	\
	libsurfaceflinger_client \
	libbinder

LOCAL_MODULE:= libgstsurfaceflinger-plugins


LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)  		\
	$(LOCAL_PATH)/../../ 	\
	frameworks/base/include	\
        $(LOCAL_PATH)/../../gstplayer                \
        $(TARGET_OUT_HEADERS)/glib-2.0  \
        $(TARGET_OUT_HEADERS)/glib-2.0/glib  \
        $(TARGET_OUT_HEADERS)/gstreamer-0.10  \
        external/libxml2/include        \
        external/icu4c/common           \
        frameworks/base/include/media           \
        frameworks/base/media/libmediaplayerservice	\
	hardware/ti/omap3/liboverlay


LOCAL_CFLAGS := -DANDROID_USE_GSTREAMER \
	-DHAVE_CONFIG_H  -DGETTEXT_PACKAGE

LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins/
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := eng debug

include $(BUILD_SHARED_LIBRARY)
