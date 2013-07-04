LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

LOCAL_SRC_FILES :=                      \
	lib/iconv.c  			\
	lib/relocatable.c  		\
	libcharset/lib/localcharset.c	\
	srclib/areadlink.c   		\
	srclib/xstrdup.c 		\
	srclib/error.c 			\
	srclib/malloca.c  		\
	srclib/progname.c  		\
	srclib/xmalloc.c 		\
	srclib/uniwidth/width.c 	\
	srclib/xreadlink.c		\
	src/iconv_no_i18n.c

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libiconv

LOCAL_COPY_HEADERS_TO := libiconv
LOCAL_COPY_HEADERS := include/iconv.h include/export.h

LOCAL_C_INCLUDES :=                     \
	$(LOCAL_PATH)			\
	$(LOCAL_PATH)/android		\
	$(LOCAL_PATH)/include 		\
	$(LOCAL_PATH)/srclib 		\
	$(LOCAL_PATH)/srclib/uniwidth 	

LOCAL_CFLAGS :=                         \
    -DHAVE_CONFIG_H	-DEXEEXT=\"\"

LOCAL_SHARED_LIBRARIES :=    

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

