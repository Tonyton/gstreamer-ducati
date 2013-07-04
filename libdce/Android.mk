# only include if running on an omap4 platform
ifeq ($(TARGET_BOARD_PLATFORM),omap4)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
		dce.c \


LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/packages/codec_engine/ \
	$(LOCAL_PATH)/packages/xdais/ \
        $(LOCAL_PATH)/packages/xdctools/ \
	hardware/ti/syslink/syslink/api/include/ \
	hardware/ti/syslink/syslink/api/include/ti/ipc/ \
	hardware/ti/tiler/ 	


#LOCAL_CFLAGS += -pipe -fomit-frame-pointer -Wall  -Wno-trigraphs -Werror-implicit-function-declaration  -fno-strict-aliasing -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -msoft-float -Uarm -DMODULE -D__LINUX_ARM_ARCH__=7  -fno-common -DLINUX -fpic

#add by kelvinji
LOCAL_CFLAGS += -DCLIENT

LOCAL_SHARED_LIBRARIES += \
	libtimemmgr \
	libipcutils \
	libipc \
	libnotify \
	librcm \
	libsysmgr \
	
LOCAL_MODULE    := libdce
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := test.c 
LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/ \
        $(LOCAL_PATH)/packages/codec_engine \
        $(LOCAL_PATH)/packages/xdais \
        $(LOCAL_PATH)/packages/xdctools/ \
        hardware/ti/syslink/syslink/api/include/ \
        hardware/ti/syslink/syslink/api/include/ti/ipc/ \
        hardware/ti/tiler/ \
	
LOCAL_SHARED_LIBRARIES += \
	libdce \
        libtimemmgr \
        libipcutils \
        libipc \
        libnotify \
        librcm \
        libsysmgr \

LOCAL_MODULE := dcetest
LOCAL_MODULE_TAGS := optional tests
include $(BUILD_EXECUTABLE)

endif
