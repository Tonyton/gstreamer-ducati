LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= 		\
areadlink.c          c-ctype.c  malloca.c  memmove.c   progreloc.c  relocatable.c   setenv.c       stdio-write.c  xmalloc.c    xstrdup.c\
canonicalize-lgpl.c  error.c    malloc.c   progname.c  readlink.c   relocwrapper.c  strerror.c     xreadlink.c
LOCAL_MODULE:= libmms

LOCAL_SHARED_LIBRARIES :=               \
        libglib-2.0                 \
        libgthread-2.0              \
        libgmodule-2.0              \
        libgobject-2.0

LOCAL_C_INCLUDES := 			\
	$(LOCAL_PATH)			\
	$(ICONV_TOP)/include		\
	$(ICONV_TOP)			\
        external/glib           	\
        external/glib/android           \
        external/glib/glib              \
        external/glib/gmodule           \
        external/glib/gobject           \
        external/glib/gthread           \
        external/glib/gobject/android


LOCAL_CFLAGS:=		\
	-DHAVE_CONFIG_H

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)


