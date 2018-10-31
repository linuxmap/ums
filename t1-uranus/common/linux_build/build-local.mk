###############################################################################
#
# The entry makefile of MBT build tools
#
# Author: ryg
# Date  : 2015/05/05
# 
###############################################################################
MBT_ROOT := $(dir $(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST)))
MBT_ROOT := $(subst \,/,$(MBT_ROOT))
MBT_ROOT := $(MBT_ROOT:%/=%)
ifeq ($(MBT_ROOT),)
    # for the case when we're invoked from the MBT install path
    MBT_ROOT := .
endif

include $(MBT_ROOT)/definitions.mk

BUILD_STATIC_LIBRARY := $(MBT_ROOT)/build-static-library.mk
BUILD_SHARED_LIBRARY := $(MBT_ROOT)/build-shared-library.mk
BUILD_EXECUTABLE     := $(MBT_ROOT)/build-executable.mk

include $(MK_PATH)