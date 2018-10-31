###############################################################################
#
# A general Makefile template for building static library
#
# Author: ryg
# Date  : 2015/05/05
# 
###############################################################################
ifeq ($(strip $(LIB_INSTALL_PATH)),)    
    $(error you must specify the LIB_INSTALL_PATH!)
endif

$(MBT_DEBUG) = $(strip $(MBT_DEBUG))
ifeq ($(MBT_DEBUG), 1)
VERSION = debug
else
VERSION = release
endif

$(ABI) = $(strip $(ABI))
ABI_OK = false
ifneq ($(ABI),)
    include $(MBT_ROOT)/abi/$(ABI).mk
else
    $(error you must specify an ABI!)
endif

ifeq ($(ABI), x86)
    PLATFORM =linux
	ABI_OK = true
endif

ifeq ($(ABI), arm-netra)
    PLATFORM =linux_arm_netra
	ABI_OK = true
endif

ifeq ($(ABI), arm-d6446)
    PLATFORM =linux_arm_d6446
	ABI_OK = true
endif

ifeq ($(ABI), ppc-82xx)
    PLATFORM =linux_ppc_82xx
	ABI_OK = true
endif

ifeq ($(ABI), ppc-85xx)
    PLATFORM =linux_ppc_85xx
	ABI_OK = true
endif 

ifneq ($(ABI_OK), true)
    $(error unknown the ABI $(ABI)!)
endif

CFLAGS  += -D_LINUX_ -D_LINUX_P_
CFLAGS  += $(foreach incpath,$(INC_PATH),-I$(incpath))

OBJS += $(patsubst %.c, %.o, $(filter %.c, $(SRCS)))
OBJS += $(patsubst %.cc, %.o, $(filter %.cc, $(SRCS)))
OBJS += $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRCS)))   
OBJS := $(addprefix $(TMP_DIR)/, $(notdir $(OBJS)))


MODULE_NAME = lib$(MODULE).a
target      = $(TMP_DIR)/$(MODULE_NAME)

ifeq ($(MBT_DEBUG), 1)
    CFLAGS += -g -O0
else
    CFLAGS += -O2 -fno-strict-aliasing
endif

CFLAGS += -Wall

$(foreach src, $(filter %.c, $(SRCS)), $(eval $(call ADD_D_DEPENDS, $(TMP_DIR)/$(notdir $(src:.c=.d)), $(src))))
$(foreach src, $(filter %.cc, $(SRCS)), $(eval $(call ADD_D_DEPENDS, $(TMP_DIR)/$(notdir $(src:.cc=.d)), $(src))))
$(foreach src, $(filter %.cpp, $(SRCS)), $(eval $(call ADD_D_DEPENDS, $(TMP_DIR)/$(notdir $(src:.cpp=.d)), $(src))))

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

$(foreach src, $(filter %.c, $(SRCS)), $(eval $(call ADD_O_DEPENDS, $(TMP_DIR)/$(notdir $(src:.c=.o)), $(src))))
$(foreach src, $(filter %.cc, $(SRCS)), $(eval $(call ADD_O_DEPENDS, $(TMP_DIR)/$(notdir $(src:.cc=.o)), $(src))))
$(foreach src, $(filter %.cpp, $(SRCS)), $(eval $(call ADD_O_DEPENDS, $(TMP_DIR)/$(notdir $(src:.cpp=.o)), $(src))))

target : $(DEPS) $(OBJS)	
	$(AR) crus $(target) $(OBJS)	
	$(INSTALL) $(target) $(LIB_INSTALL_PATH)/$(VERSION)/$(PLATFORM)/$(MODULE_NAME)
	
clean :
	$(RM) $(OBJS); $(RM) $(DEPS); $(RM) $(target)

