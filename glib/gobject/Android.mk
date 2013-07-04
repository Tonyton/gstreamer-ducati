LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES	:=			\
	gatomicarray.c			\
	gbinding.c			\
	gboxed.c			\
	gclosure.c			\
	genums.c			\
	gobject.c			\
	gparam.c			\
	gparamspecs.c			\
	gsignal.c			\
	gsourceclosure.c		\
	gtype.c				\
	gtypemodule.c			\
	gtypeplugin.c			\
	gvalue.c			\
	gvaluearray.c			\
	gvaluetransform.c		\
	gvaluetypes.c

LOCAL_MODULE_TAGS := optinal eng
LOCAL_MODULE := libgobject-2.0


LOCAL_COPY_HEADERS_TO := glib-2.0/gobject
LOCAL_COPY_HEADERS :=	\
	gbinding.h  gclosure.h    gobjectnotifyqueue.c  \
	gparamspecs.h  gsourceclosure.h  gtypemodule.h  gvaluearray.h   \
	gvalue.h  gboxed.h    genums.h    gobject.h   gparam.h       \
	gsignal.h      gtype.h           gtypeplugin.h  gvaluecollector.h  gvaluetypes.h \
	gmarshal.h


LOCAL_C_INCLUDES :=			\
	$(LOCAL_PATH)			\
	$(LOCAL_PATH)/android		\
	$(LOCAL_PATH)/android/gobject	\
	$(LOCAL_PATH)/android-internal	\
	$(GLIB_TOP)/android-internal	\
	$(GLIB_C_INCLUDES)

LOCAL_CFLAGS :=				\
	-DHAVE_CONFIG_H			\
	-DG_LOG_DOMAIN=\"GLib-GObject\"	\
	-DGOBJECT_COMPILATION		\
	-DG_DISABLE_CONST_RETURNS	\
	-DG_DISABLE_DEPRECATED 

LOCAL_SHARED_LIBRARIES := libglib-2.0 libgthread-2.0
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
