CROSS     	:= /opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le-
CC        	:= $(CROSS)gcc
CPP       	:= $(CROSS)g++
LD       	:= $(CROSS)ld
AR       	:= $(CROSS)ar
NM        	:= $(CROSS)nm
STRIP     	:= $(CROSS)strip
COMPILER	:=

ifeq ($(USEGCC),1)
	COMPILER	:= $(CC)
else
	COMPILER	:= $(CPP)
endif

CFLAGS    += -DARCH=ARM -D_ARM_