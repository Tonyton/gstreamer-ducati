LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := \
        mxf.c \
        mxful.c \
        mxftypes.c \
        mxfmetadata.c \
        mxfessence.c \
        mxfquark.c \
        mxfmux.c \
        mxfdemux.c \
        mxfaes-bwf.c \
        mxfmpeg.c \
        mxfdv-dif.c \
        mxfalaw.c \
        mxfjpeg2000.c \
        mxfd10.c \
        mxfup.c \
        mxfvc3.c \
        mxfdms1.c


LOCAL_MODULE := libgstmxf$(GST_PLUGINS_SUFFIX)

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

