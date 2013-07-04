LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= 		\
 		mp4ff.c 	\
		mp4atom.c 	\
		mp4meta.c 	\
		mp4sample.c 	\
		mp4util.c 	\
		mp4tagupdate.c
	
LOCAL_MODULE:= libmp4ff

LOCAL_CFLAGS+= -DUSE_TAGGING=1

LOCAL_C_INCLUDES := 				\
	$(LOCAL_PATH)	\
	$(FAAD2_TOP)/include	

include $(BUILD_STATIC_LIBRARY)
