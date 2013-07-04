LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := \
	gstmad.c
LOCAL_MODULE := libgstmad$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_UGLY_TOP)/android-internal \
	external/gst/libmad			\
	external/gst/libid3tag

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

#LOCAL_STATIC_LIBRARIES :=\
	libmad

LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		\
	libiconv				\
	libid3tag				\
	libmad
	
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng

include $(BUILD_SHARED_LIBRARY)

