LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=				\
	orc.c					\
	orcemulateopcodes.c			\
	orcexecutor.c				\
	orcfunctions.c				\
	orcutils.c				\
	orcrule.c				\
	orccodemem.c				\
	orcprogram.c				\
	orccompiler.c				\
	orcprogram-c.c				\
	orcopcodes.c				\
	orcparse.c				\
	orconce.c				\
	orcdebug.c				\
	orccode.c				\

ifeq ($(ORC_CPU),arm)
LOCAL_SRC_FILES +=				\
	orccpu-arm.c
endif
ifeq ($(ORC_CPU),x86)
LOCAL_SRC_FILES +=				\
	orccpu-x86.c
endif

ifeq ($(ORC_ENABLE_BACKEND_MMX),true)
LOCAL_SRC_FILES +=				\
	orcx86.c				\
	orcmmx.c				\
	orcprogram-mmx.c			\
	orcrules-mmx.c
endif
ifeq ($(ORC_ENABLE_BACKEND_SSE),true)
LOCAL_SRC_FILES +=				\
	orcsse.c				\
	orcprogram-sse.c			\
	orcrules-sse.c
ifneq ($(ORC_ENABLE_BACKEND_MMX),true)
LOCAL_SRC_FILES +=				\
	orcx86.c
endif
endif

ifeq ($(ORC_ENABLE_BACKEND_ARM),true)
LOCAL_SRC_FILES +=				\
	orcarm.c				\
	orcprogram-arm.c			\
	orcrules-arm.c
endif
ifeq ($(ORC_ENABLE_BACKEND_NEON),true)
LOCAL_SRC_FILES +=				\
	orcprogram-neon.c			\
	orcrules-neon.c
ifneq ($(ORC_ENABLE_BACKEND_ARM),true)
LOCAL_SRC_FILES +=				\
	orcarm.c
endif
endif

ifeq ($(ORC_ENABLE_BACKEND_C64X),true)
LOCAL_SRC_FILES += orcprogram-c64x-c.c
endif

LOCAL_MODULE_TAGS :=optinal eng
LOCAL_MODULE:= liborc-$(ORC_MAJORMINOR)

LOCAL_COPY_HEADERS_TO := orc
LOCAL_COPY_HEADERS := 	\
	opcodes.h  orccpuinsn.h  orcemulateopcodes.h  orc.h     \
	orcneon.h  orcparse.h    orcprogram.h  orc-stdint.h  orcx86.h	\
	orcarm.h   orcdebug.h    orcfunctions.h       orcmmx.h  orconce.h  \
	orcpowerpc.h  orcsse.h      orcutils.h    orcx86insn.h


LOCAL_C_INCLUDES :=				\
	$(ORC_TOP)				\
	$(ORC_TOP)/android			\
	$(ORC_TOP)/android-internal

LOCAL_CFLAGS :=					\
	-DORC_ENABLE_UNSTABLE_API		\
	-DHAVE_CONFIG_H
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
