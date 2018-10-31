CROSS     	:= /opt/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-
CC        	:= $(CROSS)gcc
CPP       	:= $(CROSS)g++
LD        	:= $(CROSS)ld
AR        	:= $(CROSS)ar
NM        	:= $(CROSS)nm
STRIP	   	:= $(CROSS)strip
COMPILER	:=

ifeq ($(USEGCC),1)
	COMPILER	:= $(CC)
else
	COMPILER	:= $(CPP)
endif

CFLAGS    += -DARCH=ARM -D_ARM_