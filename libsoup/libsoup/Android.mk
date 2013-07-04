LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= 		\
        soup-address.c                  \
        soup-auth.c                     \
        soup-auth-basic.c               \
        soup-auth-digest.c              \
        soup-auth-ntlm.c                \
        soup-auth-domain.c              \
        soup-auth-domain-basic.c        \
        soup-auth-domain-digest.c       \
        soup-auth-manager.c             \
        soup-auth-manager-ntlm.c        \
        soup-connection.c               \
        soup-content-sniffer.c          \
        soup-cookie.c                   \
        soup-cookie-jar.c               \
        soup-cookie-jar-text.c          \
        soup-date.c                     \
        soup-form.c                     \
        soup-gnutls.c                   \
        soup-headers.c                  \
        soup-logger.c                   \
        soup-message.c                  \
        soup-message-body.c             \
        soup-message-client-io.c        \
        soup-message-headers.c          \
        soup-message-io.c               \
        soup-message-queue.c            \
        soup-message-server-io.c        \
        soup-method.c                   \
        soup-misc.c                     \
        soup-multipart.c                \
        soup-nossl.c                    \
        soup-password-manager.c         \
        soup-path-map.c                 \
        soup-proxy-resolver.c           \
        soup-proxy-resolver-static.c    \
        soup-proxy-uri-resolver.c       \
        soup-server.c                   \
        soup-session.c                  \
        soup-session-async.c            \
        soup-session-feature.c          \
        soup-session-sync.c             \
        soup-socket.c                   \
        soup-status.c                   \
        soup-uri.c                      \
        soup-value-utils.c              \
        soup-xmlrpc.c			\
	soup-enum-types.c		\
	soup-marshal.c
LOCAL_MODULE:= libsoup

LOCAL_SHARED_LIBRARIES :=               \
        libglib-2.0                 	\
        libgthread-2.0              	\
        libgmodule-2.0              	\
        libgobject-2.0			\
	libicuuc			\
	libgio-2.0
LOCAL_STATIC_LIBRARIES :=		\
	libxml2
LOCAL_C_INCLUDES := 			\
	$(LIBSOUP_TOP)			\
	$(LOCAL_PATH)			\
	$(LIBSOUP_TOP)/android		\
	$(TARGET_OUT_HEADERS)/glib-2.0 	\
	$(TARGET_OUT_HEADERS)/glib-2.0/glib 	\
        external/libxml2/include	\
        external/icu4c/common



LOCAL_CFLAGS:=		\
	-DHAVE_CONFIG_H

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng
include $(BUILD_SHARED_LIBRARY)


