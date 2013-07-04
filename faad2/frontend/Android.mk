LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= 		\
		main.c		\
	       	audio.c  	\
	       	$(FAAD2_TOP)/common/faad/getopt.c 		

LOCAL_STATIC_LIBARIES:=		\
	$(FAAD2_TOP)/libfaad/libfaad.la \
        $(FAAD2_TOP)/common/mp4ff/libmp4ff.a	

LOCAL_MODULE:= faad

LOCAL_CFLAGS+= -DUSE_TAGGING=1

LOCAL_C_INCLUDES := 				\
	$(LOCAL_PATH)	
	$(LIBOGG_TOP)/include		\
	$(FAAD2_TOP)/common/faad	\
	$(FAAD2_TOP)/common/mp4ff

include $(BUILD_EXECUTABLE)
