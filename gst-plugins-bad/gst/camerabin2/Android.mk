LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := \
        gstviewfinderbin.c \
        camerabingeneral.c \
        gstwrappercamerabinsrc.c \
        gstcamerabin2.c \
        gstplugin.c	\
	gstimagecapturebin.c	\
	gstomxcamerabinsrc.c


LOCAL_MODULE := libgstcamerabin2$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_BAD_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

LOCAL_LDFLAGS:=\
        -module\
        -avoid-version\
        -export-symbols-regex\
        -no-undefined


LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		\
	libgstphotography-0.10			\
	libgstasecamerasrc-0.10
	
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng

include $(BUILD_SHARED_LIBRARY)

