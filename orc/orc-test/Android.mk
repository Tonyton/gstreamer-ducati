LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=				\
	orctest.c				\
	orcarray.c				\
	orcrandom.c				\
	orcprofile.c				\

LOCAL_MODULE_TAGS := optinal eng 
LOCAL_MODULE:= liborc-test-$(ORC_MAJORMINOR)

LOCAL_C_INCLUDES :=				\
	$(ORC_TOP)				\
	$(ORC_TOP)/android			\
	$(ORC_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DORC_ENABLE_UNSTABLE_API		\
	-DHAVE_CONFIG_H

LOCAL_SHARED_LIBRARIES := liborc-$(ORC_MAJORMINOR)
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
