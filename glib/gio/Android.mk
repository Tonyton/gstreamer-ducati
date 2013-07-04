LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

gdbus_sources = \
	gdbusutils.c                    \
	gdbusaddress.c                  \
	gdbusauthobserver.c             \
	gdbusauth.c                     \
	gdbusauthmechanism.c            \
	gdbusauthmechanismanon.c        \
	gdbusauthmechanismexternal.c    \
	gdbusauthmechanismsha1.c        \
	gdbuserror.c                    \
	gdbusconnection.c               \
	gdbusmessage.c                  \
	gdbusnameowning.c               \
	gdbusnamewatching.c             \
	gdbusproxy.c                    \
	gdbusprivate.c                  \
	gdbusintrospection.c            \
	gdbusmethodinvocation.c         \
	gdbusserver.c                   

settings_sources = \
        gvdb/gvdb-reader.c              \
        gdelayedsettingsbackend.c       \
        gkeyfilesettingsbackend.c       \
        gmemorysettingsbackend.c        \
        gnullsettingsbackend.c          \
        gsettingsbackend.c              \
        gsettingsschema.c               \
        gsettings-mapping.c             \
        gsettings.c
ginotify_sources = \
	inotify/ginotifydirectorymonitor.c  \
	inotify/inotify-diag.c   	\
	inotify/inotify-kernel.c   	\
	inotify/inotify-path.c		\
	inotify/ginotifyfilemonitor.c   \
	inotify/inotify-helper.c  	\
	inotify/inotify-missing.c  	\
	inotify/inotify-sub.c

local_sources = \
        glocaldirectorymonitor.c        \
        glocalfile.c                    \
        glocalfileenumerator.c          \
        glocalfileinfo.c                \
        glocalfileinputstream.c         \
        glocalfilemonitor.c             \
        glocalfileoutputstream.c        \
        glocalfileiostream.c            \
        glocalvfs.c                     \
        gsocks4proxy.c                  \
        gsocks4aproxy.c                 \
        gsocks5proxy.c                  

marshal_sources = \
        android/gio-marshal.c   

unix_sources = \
        gfiledescriptorbased.c  \
        gunixconnection.c       \
        gunixcredentialsmessage.c       \
        gunixfdlist.c           \
        gunixfdmessage.c        \
        gunixmount.c            \
        gunixmounts.c           \
        gunixresolver.c         \
        gunixsocketaddress.c    \
        gunixvolume.c           \
        gunixvolumemonitor.c    \
        gunixinputstream.c      \
        gunixoutputstream.c     

xdgmime_sources = \
	xdgmime/xdgmimealias.c  \
	xdgmime/xdgmimecache.c  \
	xdgmime/xdgmimeicon.c  	\
	xdgmime/xdgmimemagic.c 	\
	xdgmime/xdgmime.c      	\
	xdgmime/xdgmimeglob.c   \
	xdgmime/xdgmimeint.c   	\
	xdgmime/xdgmimeparent.c

libgio_2_0_la_SOURCES =         \
	$(xdgmime_sources)	\
        gappinfo.c              \
        gasynchelper.c          \
        gasynchelper.h          \
        gasyncinitable.c        \
        gasyncresult.c          \
        gbufferedinputstream.c  \
        gbufferedoutputstream.c \
        gcancellable.c          \
        gcontenttype.c          \
        gcharsetconverter.c     \
        gconverter.c            \
        gconverterinputstream.c \
        gconverteroutputstream.c        \
        gcredentials.c          \
        gdatainputstream.c      \
        gdataoutputstream.c     \
        gdrive.c                \
        gdummyfile.c            \
        gdummyproxyresolver.c   \
        gemblem.c               \
        gemblemedicon.c         \
        gfile.c                 \
        gfileattribute.c        \
        gfileenumerator.c       \
        gfileicon.c             \
        gfileinfo.c             \
        gfileinputstream.c      \
        gfilemonitor.c          \
        gfilenamecompleter.c    \
        gfileoutputstream.c     \
        gfileiostream.c         \
        gfilterinputstream.c    \
        gfilteroutputstream.c   \
        gicon.c                 \
        ginetaddress.c          \
        ginetsocketaddress.c    \
        ginitable.c             \
        ginputstream.c          \
        gioerror.c              \
        giomodule.c             \
        gioscheduler.c          \
        giostream.c             \
        gloadableicon.c         \
        gmount.c                \
        gmemoryinputstream.c    \
        gmemoryoutputstream.c   \
        gmountoperation.c       \
        gnativevolumemonitor.c  \
        gnetworkaddress.c       \
        gnetworkservice.c       \
        goutputstream.c         \
        gpermission.c           \
        gpollfilemonitor.c      \
        gproxyresolver.c        \
        gresolver.c             \
        gseekable.c             \
        gsimpleasyncresult.c    \
        gsimplepermission.c     \
        gsocket.c               \
        gsocketaddress.c        \
        gsocketaddressenumerator.c \
        gsocketclient.c         \
        gsocketconnectable.c    \
        gsocketconnection.c     \
        gsocketcontrolmessage.c \
        gsocketinputstream.c    \
        gsocketlistener.c       \
        gsocketoutputstream.c   \
        gproxy.c                \
        gproxyaddress.c         \
        gproxyaddressenumerator.c \
        gsocketservice.c        \
        gsrvtarget.c            \
        gtcpconnection.c        \
        gthreadedsocketservice.c\
        gthemedicon.c           \
        gthreadedresolver.c     \
        gunionvolumemonitor.c   \
        gvfs.c                  \
        gvolume.c               \
        gvolumemonitor.c        \
        gzlibcompressor.c       \
        gzlibdecompressor.c     \
	libasyncns/asyncns.c	\
	gdesktopappinfo.c	\
	gpollableinputstream.c	\
	gioenumtypes.c		\
	gtlsclientconnection.c  \
	gtlsbackend.c		\
	gdummytlsbackend.c	\
	gtlsconnection.c	\
	gtcpwrapperconnection.c \
	gtlscertificate.c	\
	gtlsserverconnection.c  \
	gpollableoutputstream.c \
        $(settings_sources)     \
        $(gdbus_sources)        \
        $(local_sources)        \
        $(marshal_sources)      \
	$(unix_sources)		\
	$(ginotify_sources)
LOCAL_SRC_FILES:= \
	$(libgio_2_0_la_SOURCES)

LOCAL_MODULE := libgio-2.0

LOCAL_MODULE_TAGS := optinal eng
LOCAL_COPY_HEADERS_TO := glib-2.0/gio
LOCAL_COPY_HEADERS := 		\
	gactiongroup.h             gdbusintrospection.h        gfilemonitor.h          gnetworkaddress.h           \
	gsocket.h	gaction.h                  gdbusmessage.h              gfilenamecompleter.h    gnetworkservice.h           \
	gsocketlistener.h	gappinfo.h                 gdbusmethodinvocation.h     gfileoutputstream.h     \
	goutputstream.h             gsocketservice.h	gapplicationcommandline.h  gdbusnameowning.h           \
	gfilterinputstream.h    gpermission.h               gsrvtarget.h	gapplication.h             \
	gdbusnamewatching.h         gfilteroutputstream.h   gpollableinputstream.h      gtcpconnection.h	\
	gasyncinitable.h            gicon.h                 gpollableoutputstream.h     \
	gtcpwrapperconnection.h	  gasyncresult.h              ginetaddress.h          \
	gproxyaddressenumerator.h   gthemedicon.h  gbufferedinputstream.h             \
	ginetsocketaddress.h    gproxyaddress.h             gthreadedsocketservice.h   gbufferedoutputstream.h    \
	ginitable.h             gproxy.h                    	\
	gcancellable.h                       ginputstream.h          gproxyresolver.h           \
	 gtlsbackend.h	gcharsetconverter.h               gioenums.h              gresolver.h                 \
	gtlscertificate.h 	gcontenttype.h             gdbusproxy.h                gioenumtypes.h          \
	gseekable.h                 gtlsclientconnection.h	gconverter.h               gdbusserver.h               \
	gioerror.h              gsettingsbackend.h          gtlsconnection.h	gconverterinputstream.h    \
	gdbusutils.h                gio.h                   gsettings.h                	\
	gconverteroutputstream.h   gdrive.h                    giomodule.h             gsimpleactiongroup.h        \
	gcredentials.h             gemblemedicon.h             gioscheduler.h          \
	gsimpleaction.h            gdatainputstream.h         gemblem.h                   \
	giostream.h             gsimpleasyncresult.h        gdataoutputstream.h        \
	gfileattribute.h            giotypes.h              gsimplepermission.h         gtlsserverconnection.h	\
	gdbusaddress.h             gfileenumerator.h           gloadableicon.h         gsocketaddressenumerator.h  \
	gvfs.h	gdbusauthobserver.h        gfile.h                     gmemoryinputstream.h    gsocketaddress.h            \
	gvolume.h	gdbusconnection.h          gfileicon.h                 gmemoryoutputstream.h   gsocketclient.h             \
	gvolumemonitor.h	gdbuserror.h               gfileinfo.h                 gmount.h                \
	gsocketconnectable.h        gzlibcompressor.h	           gfileinputstream.h          \
	gmountoperation.h       gsocketconnection.h         gzlibdecompressor.h		   \
	gfileiostream.h             gnativevolumemonitor.h  gsocketcontrolmessage.h

LOCAL_C_INCLUDES := 			\
	$(GLIB_TOP)			\
	$(GLIB_TOP)/glib		\
	$(GLIB_TOP)/android		\
	$(GLIB_TOP)/android-internal	\
        $(GLIB_TOP)/gmodule           \
        $(GLIB_TOP)/gobject           \
        $(GLIB_TOP)/gthread           \
        $(GLIB_TOP)/gobject/android   \
	$(GLIB_TOP)/gio			\
	external/zlib			\
	$(LOCAL_PATH)			\
	$(LOCAL_PATH)/android		\
	$(LOCAL_PATH)/libasyncns	

# ./glib private macros, copy from Makefile.am
LOCAL_CFLAGS := \
	-DLIBDIR=\"$(libdir)\"		\
	-DHAVE_CONFIG_H			\
	-DG_LOG_DOMAIN=\"GLib\"		\
	-DPCRE_STATIC			\
	-DG_DISABLE_DEPRECATED		\
	-DGIO_COMPILATION		\
	-DGIO_MODULE_DIR=\"$(libdir)/gio/modules\" \
	-DXDG_PREFIX=_gio_xdg \
	-fPIC

LOCAL_LDLIBS :=				\
		-llog
LOCAL_SHARED_LIBRARIES :=liblog		\
        libglib-2.0                 	\
        libgthread-2.0              	\
        libgmodule-2.0              	\
        libgobject-2.0		   	\
	libz		
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

