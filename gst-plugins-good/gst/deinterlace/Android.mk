LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES :=				\
	gstdeinterlace.c \
	gstdeinterlacemethod.c \
	tvtime.c		\
	tvtime/tomsmocomp.c \
	tvtime/greedy.c \
	tvtime/greedyh.c \
	tvtime/vfir.c \
	tvtime/weavetff.c \
	tvtime/weavebff.c \
	tvtime/weave.c \
	tvtime/linear.c \
	tvtime/linearblend.c \
	tvtime/scalerbob.c

LOCAL_MODULE := libgstdeinterlace$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(ORC_C_INCLUDES)			\
	$(GST_PLUGINS_GOOD_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

ifeq ($(GST_BUILD_STATIC),true)
GST_PLUGINS_STATIC_LIBRARIES +=			\
	$(LOCAL_MODULE)				\
	$(ORC_STATIC_LIBRARIES)			

LOCAL_CFLAGS +=					\
	-DSTATIC_PLUGIN_NAME=$(LOCAL_MODULE)

include $(BUILD_STATIC_LIBRARY)
else
LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(ORC_SHARED_LIBRARIES)			\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng
include $(BUILD_SHARED_LIBRARY)
endif
