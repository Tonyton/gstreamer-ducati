LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_PATH := $(TARGET_OUT)/plugins
LOCAL_SRC_FILES := 				\
	fnv1hash.c \
	gstrtp.c \
	gstrtpchannels.c \
	gstrtpdepay.c \
	gstrtpac3depay.c \
	gstrtpac3pay.c \
	gstrtpbvdepay.c \
	gstrtpbvpay.c \
	gstrtpceltdepay.c \
	gstrtpceltpay.c \
	gstrtpdvdepay.c \
	gstrtpdvpay.c \
	gstrtpgstdepay.c \
	gstrtpgstpay.c \
	gstrtpilbcdepay.c \
	gstrtpilbcpay.c \
	gstrtpmpadepay.c \
	gstrtpmpapay.c \
	gstrtpmparobustdepay.c \
	gstrtpmpvdepay.c \
	gstrtpmpvpay.c \
	gstrtppcmadepay.c \
	gstrtppcmudepay.c \
	gstrtppcmupay.c \
	gstrtppcmapay.c \
	gstrtpg722depay.c \
	gstrtpg722pay.c \
	gstrtpg723depay.c \
	gstrtpg723pay.c \
	gstrtpg726pay.c \
	gstrtpg726depay.c \
	gstrtpg729pay.c \
	gstrtpg729depay.c \
	gstrtpgsmdepay.c \
	gstrtpgsmpay.c \
	gstrtpamrdepay.c \
	gstrtpamrpay.c \
	gstrtph263pdepay.c \
	gstrtph263ppay.c \
	gstrtph263depay.c \
	gstrtph263pay.c \
	gstrtph264depay.c \
	gstrtph264pay.c \
	gstrtpj2kdepay.c \
	gstrtpj2kpay.c \
	gstrtpjpegdepay.c \
	gstrtpjpegpay.c \
	gstrtpL16depay.c \
	gstrtpL16pay.c \
	gstasteriskh263.c \
	gstrtpmp1sdepay.c \
	gstrtpmp2tdepay.c \
	gstrtpmp2tpay.c \
	gstrtpmp4vdepay.c \
	gstrtpmp4vpay.c \
	gstrtpmp4gdepay.c \
	gstrtpmp4gpay.c \
	gstrtpmp4adepay.c \
	gstrtpmp4apay.c \
	gstrtpqcelpdepay.c \
	gstrtpqdmdepay.c \
	gstrtpsirenpay.c \
	gstrtpsirendepay.c \
	gstrtpspeexdepay.c \
	gstrtpspeexpay.c \
	gstrtpsv3vdepay.c \
	gstrtptheoradepay.c \
	gstrtptheorapay.c \
	gstrtpvorbisdepay.c \
	gstrtpvorbispay.c  \
	gstrtpvrawdepay.c  \
	gstrtpvrawpay.c 

LOCAL_MODULE:= libgstrtp$(GST_PLUGINS_SUFFIX)

LOCAL_C_INCLUDES :=				\
	$(GST_PLUGINS_BASE_LIBS_C_INCLUDES)	\
	$(GST_PLUGINS_GOOD_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DHAVE_CONFIG_H

ifeq ($(GST_BUILD_STATIC),true)
GST_PLUGINS_STATIC_LIBRARIES +=			\
	$(LOCAL_MODULE)				

LOCAL_CFLAGS +=					\
	-DSTATIC_PLUGIN_NAME=$(LOCAL_MODULE)

include $(BUILD_STATIC_LIBRARY)
else
LOCAL_SHARED_LIBRARIES :=			\
	$(GLIB_SHARED_LIBRARIES)		\
	$(GST_SHARED_LIBRARIES)			\
	$(GST_BASE_SHARED_LIBRARIES)		
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional eng
include $(BUILD_SHARED_LIBRARY)
endif
