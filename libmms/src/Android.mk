LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= 		\
	mmsh.c  		\
	mmsx.c  		\
	uri.c			\
	mms.c

LOCAL_MODULE:= libmms

LOCAL_SHARED_LIBRARIES :=               \
        libglib-2.0                 	\
        libgthread-2.0              	\
        libgmodule-2.0              	\
        libgobject-2.0			\
	libiconv			

LOCAL_C_INCLUDES := 			\
	$(LOCAL_PATH)			\
	$(LIBMMS_TOP)/android		\
        $(TARGET_OUT_HEADERS)/glib-2.0  \
        $(TARGET_OUT_HEADERS)/glib-2.0/glib  \
	external/gst/libiconv           	\
        external/gst/libiconv/include           \
        external/gst/libiconv/srclib            \
        external/gst/libiconv/srclib/uniwidth



LOCAL_CFLAGS:=		\
	-DHAVE_CONFIG_H

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)


