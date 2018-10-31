CC         	:= gcc
CPP        	:= g++
LD         	:= ld
AR         	:= ar
NM         	:= nm
STRIP      	:= strip
COMPILER	:=

ifeq ($(USEGCC),1)
	COMPILER	:= $(CC)
else
	COMPILER	:= $(CPP)
endif
	
CFLAGS    += -DARCH=X86 -D_X86_