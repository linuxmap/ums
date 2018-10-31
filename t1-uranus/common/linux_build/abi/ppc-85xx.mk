CROSS     	:= /opt/ppc_nofpu/bin/ppc_85xx-
CC        	:= $(CROSS)gcc
CPP       	:= $(CROSS)g++
LD        	:= $(CROSS)ld
AR        	:= $(CROSS)ar
NM        	:= $(CROSS)nm
STRIP     	:= $(CROSS)strip
COMPILER	:=

ifeq ($(USEGCC),1)
	COMPILER	:= $(CC)
else
	COMPILER	:= $(CPP)
endif

CFLAGS    += -DARCH=PPC -D_PPC_ -D_PPC_85XX_ -D__ppc__