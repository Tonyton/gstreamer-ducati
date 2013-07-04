LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ./libcharset/localcharset.c \
    garray.c        \
    gasyncqueue.c   \
    gatomic.c       \
    gbacktrace.c    \
    gbase64.c       \
    gbitlock.c      \
    gbookmarkfile.c \
    gbuffer.c       \
    gcache.c        \
    gchecksum.c     \
    gcompletion.c   \
    gconvert.c      \
    gdataset.c      \
    gdate.c         \
    gdatetime.c     \
    gdir.c          \
    gerror.c        \
    gfileutils.c    \
    ghash.c         \
    ghook.c         \
    ghostutils.c    \
    giochannel.c    \
    gkeyfile.c      \
    glist.c         \
    gmain.c         \
    gmappedfile.c   \
    gmarkup.c       \
    gmem.c          \
    gmessages.c     \
    gnode.c         \
    goption.c       \
    gpattern.c      \
    gpoll.c         \
    gprimes.c       \
    gqsort.c        \
    gqueue.c        \
    grel.c          \
    grand.c         \
    gregex.c        \
    gscanner.c      \
    gsequence.c     \
    gshell.c        \
    gslice.c        \
    gslist.c        \
    gstdio.c        \
    gstrfuncs.c     \
    gstring.c       \
    gtestutils.c    \
    gthread.c       \
    gthreadpool.c   \
    gtimer.c        \
    gtimezone.c     \
    gtree.c         \
    guniprop.c      \
    gutf8.c         \
    gunibreak.c     \
    gunicollate.c   \
    gunidecomp.c    \
    gurifuncs.c     \
    gutils.c        \
    gvariant.c      \
    gvariant-core.c \
    gvariant-parser.c \
    gvariant-serialiser.c \
    gvarianttypeinfo.c \
    gvarianttype.c  \
    gprintf.c       \
    giounix.c       \
    gspawn.c

LOCAL_MODULE_TAGS := optinal eng
LOCAL_MODULE := libglib-2.0

LOCAL_COPY_HEADERS_TO := glib-2.0/glib
LOCAL_COPY_HEADERS :=	\
	galloca.h      gbitlock.h       gdataset.h    ghash.h       gkeyfile.h     \
	gmem.h       gprimes.h  gregex.h     gslist.h      gthread.h      gunicode.h	\
	garray.h       gbookmarkfile.h  gdate.h       ghook.h       glist.h        \
	gmessages.h  gprintf.h  grel.h       gspawn.h      gthreadpool.h  gurifuncs.h	\
	gasyncqueue.h  gcache.h         gdatetime.h   ghostutils.h  gmacros.h      gnode.h      \
	gqsort.h   gscanner.h   gstdio.h      gtimer.h       gutils.h	gatomic.h      \
	gchecksum.h      gdir.h        gi18n.h       gmain.h        goption.h    gquark.h   \
	gsequence.h  gstrfuncs.h   gtimezone.h    gvariant.h	gbacktrace.h   gcompletion.h    \
	gerror.h      gi18n-lib.h   gmappedfile.h  gpattern.h   gqueue.h   gshell.h     gstring.h     \
	gtree.h        gvarianttype.h	gbase64.h      gconvert.h       gfileutils.h  giochannel.h  \
	gmarkup.h      gpoll.h      grand.h    gslice.h     gtestutils.h  gtypes.h       gwin32.h	\
	glib.h glib-object.h ../android/glibconfig.h

#LOCAL_COPY_HEADERS_TO := glib-2.0
#LOCAL_COPY_HEADERS :=	\
	glib.h  glib-object.h  \
	../android/glibconfig.h
	

LOCAL_C_INCLUDES := 			\
	$(GLIB_TOP)			\
	$(GLIB_TOP)/android		\
	$(GLIB_TOP)/android-internal	\
	$(LOCAL_PATH)/android-internal	\
	$(LOCAL_PATH)/libcharset       	\
	$(LOCAL_PATH)/gnulib           	\
	$(LOCAL_PATH)/pcre

# ./glib private macros, copy from Makefile.am
LOCAL_CFLAGS := \
	-DLIBDIR=\"$(libdir)\"		\
	-DHAVE_CONFIG_H			\
	-DG_LOG_DOMAIN=\"GLib\"		\
	-DPCRE_STATIC			\
	-DG_DISABLE_DEPRECATED		\
	-DGLIB_COMPILATION

LOCAL_STATIC_LIBRARIES := libpcre
LOCAL_LDLIBS :=				\
		-llog 
LOCAL_SHARED_LIBRARIES :=liblog libiconv libc
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/pcre/Android.mk
