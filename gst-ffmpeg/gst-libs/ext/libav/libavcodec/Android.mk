LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

include $(LOCAL_PATH)/../av.mk

LOCAL_SRC_FILES := $(FFFILES)

LOCAL_C_INCLUDES :=		\
	$(LOCAL_PATH)		\
	$(LOCAL_PATH)/..	\
	external/zlib

LOCAL_CFLAGS += $(FFCFLAGS)

LOCAL_ARM_MODE := arm
LOCAL_LDFLAGS +=  -lc -lm -ldl  -mfpu=neon -mfloat-abi=softfp
LOCAL_SHARED_LIBRARIES := libz libavutil 
##gale
##LOCAL_STATIC_LIBRARIES := $(FFLIBS)
LOCAL_PRELINK_MODULE :=false
LOCAL_MODULE := libavcodec
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
