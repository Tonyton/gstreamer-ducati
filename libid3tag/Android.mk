
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	version.c \
	ucs4.c \
	latin1.c \
	utf16.c \
	utf8.c  \
	parse.c \
	render.c \
	field.c \
	frametype.c \
	compat.c  \
	genre.c \
	frame.c \
	crc.c \
	util.c \
	tag.c \
	file.c

LOCAL_SHARED_LIBRARIES := libz 

LOCAL_MODULE:= libid3tag

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    external/zlib

LOCAL_CFLAGS := \
    -DHAVE_CONFIG_H
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)


