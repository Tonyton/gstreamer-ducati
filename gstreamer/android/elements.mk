LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE_TAGS := optional

GST_MAJORMINOR:= 0.10

elements_LOCAL_SRC_FILES:= \
	plugins/elements/gstcapsfilter.c 	\
	plugins/elements/gstelements.c   	\
	plugins/elements/gstfakesrc.c  		\
	plugins/elements/gstfakesink.c 		\
	plugins/elements/gstfdsrc.c 		\
	plugins/elements/gstfdsink.c 		\
	plugins/elements/gstfilesink.c 		\
	plugins/elements/gstfilesrc.c 		\
	plugins/elements/gstidentity.c 		\
	plugins/elements/gstqueue.c 		\
	plugins/elements/gstqueue2.c 		\
	plugins/elements/gsttee.c 			\
	plugins/elements/gsttypefindelement.c \
	plugins/elements/gstmultiqueue.c	\
	plugins/elements/gstfunnel.c		\
	plugins/elements/gstinputselector.c		\
	plugins/elements/gstoutputselector.c		\
	plugins/elements/gstvalve.c		
	

LOCAL_SRC_FILES:= $(addprefix ../,$(elements_LOCAL_SRC_FILES))


LOCAL_SHARED_LIBRARIES := \
    libgstbase-0.10       \
    libgstreamer-0.10     \
    libglib-2.0           \
    libgthread-2.0        \
    libgmodule-2.0        \
    libgobject-2.0

LOCAL_MODULE:= libgstcoreelements
#It's a gstreamer plugins, and it must be installed on ..../plugins
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/..       				\
    $(LOCAL_PATH)/../libs 				\
    $(LOCAL_PATH)/../gst				\
    $(LOCAL_PATH)/ 						\
	$(LOCAL_PATH)/gst 					\
	$(LOCAL_PATH)/gst/parse				\
	$(TARGET_OUT_HEADERS)/glib-2.0 		\
    $(TARGET_OUT_HEADERS)/glib-2.0/glib \
	external/libxml2/include

LOCAL_SHARED_LIBRARIES += libicuuc 
LOCAL_C_INCLUDES += external/icu4c/common

LOCAL_CFLAGS := -DHAVE_CONFIG_H			
#
# define LOCAL_PRELINK_MODULE to false to not use pre-link map
#
LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)
