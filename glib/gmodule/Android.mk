LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=			\
	gmodule.c    

LOCAL_MODULE_TAGS := optinal eng
LOCAL_MODULE := libgmodule-2.0

LOCAL_C_INCLUDES :=			\
	$(LOCAL_PATH)/android-internal	\
	$(GLIB_TOP)/android-internal	\
	$(GLIB_C_INCLUDES)

LOCAL_CFLAGS :=				\
	-DHAVE_CONFIG_H			\
	-DG_LOG_DOMAIN=\"GModule\"	\
	-DG_DISABLE_DEPRECATED 

LOCAL_COPY_HEADERS_TO := glib-2.0
LOCAL_COPY_HEADERS := 	\
	gmodule.h

LOCAL_SHARED_LIBRARIES := libglib-2.0 \
			libdl

LOCAL_LDLIBS :=				\
	-ldl
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
