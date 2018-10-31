LOCAL_PATH        := $(call my-dir)

#[1]name
MODULE            := protobuf

#[2]Install path
LIB_INSTALL_PATH	:= $(LOCAL_PATH)/../../../10-common/lib
#EXE_INSTALL_PATH    := 

#[3]lib path
#LIB_PATH          := 

#[4]include path				  
INC_PATH          := $(LOCAL_PATH)/../include \
			         $(LOCAL_PATH)/../../../10-common/include/tp/protobuf-2.5.0			 

SRC_CFILES	      := $(wildcard $(LOCAL_PATH)/../source/*.c)
SRC_CPPFILES	  := $(wildcard $(LOCAL_PATH)/../source/*.cpp)
SRC_CCFILES	      := $(wildcard $(LOCAL_PATH)/../source/*.cc)
SRC_CCFILES_X86	  := $(wildcard $(LOCAL_PATH)/../source/x86_gcc/*.cc)

#[5]src files
SRCS              := $(SRC_CFILES) $(SRC_CPPFILES) $(SRC_CCFILES) $(SRC_CCFILES_X86)

#[6]lib names
#LIBS              += 
#DLLS              += 

#[7]build param
#LDFLAGS           +=
CFLAGS            +=

#[8]use gcc or g++
USEGCC = 0		

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)