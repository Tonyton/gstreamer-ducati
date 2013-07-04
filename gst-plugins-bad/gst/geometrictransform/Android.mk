LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := \
        plugin.c \
        gstgeometrictransform.c \
        gstcirclegeometrictransform.c \
        geometricmath.c \
        gstcircle.c \
        gstdiffuse.c \
        gstkaleidoscope.c \
        gstmarble.c \
        gstpinch.c \
        gstrotate.c \
        gstsphere.c \
        gsttwirl.c \
        gstwaterripple.c \
        gststretch.c \
        gstbulge.c \
        gsttunnel.c \
        gstsquare.c \
        gstmirror.c \
        gstfisheye.c


LOCAL_MODULE := libgstgeometrictransform$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_BAD_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		
	
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng

include $(BUILD_SHARED_LIBRARY)

