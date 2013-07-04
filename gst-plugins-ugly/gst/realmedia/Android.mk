LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := \
	asmrules.c  \
	gstrdtbuffer.c  \
	pnmsrc.c  \
	rademux.c  \
	rdtdepay.c  \
	rdtjitterbuffer.c  \
	rdtmanager.c  \
	realhash.c  \
	realmedia.c  \
	rmdemux.c  \
	rmutils.c  \
	rtspreal.c
LOCAL_MODULE := libgstrealmedia$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_UGLY_TOP)/android-internal 

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		\
	libiconv				
	
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng

include $(BUILD_SHARED_LIBRARY)

