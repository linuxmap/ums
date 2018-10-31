###############################################################################
#
# Common functions and Macros
#
# Author: ryg
# Date  : 2015/05/05
# 
###############################################################################
RM      := rm -f
INSTALL := install -D -m 644


# -----------------------------------------------------------------------------
#增加.d文件的依赖
#
# Function : ADD_D_DEPENDS
# Arguments: 1 .d文件 2 .c/.cpp/.cc文件
# Returns  : 
# Usage    : $(call ADD_D_DEPENDS, .d, .c/.cpp/.cc)
# -----------------------------------------------------------------------------
define ADD_D_DEPENDS
$1 : $2
	$$(COMPILER) $$(CFLAGS) -MF$$@ -MM -MT$$@ -MT$$(addprefix $$(dir $$@), $$(notdir $$(addsuffix .o, $$(basename $$<)))) $$<
endef

# -----------------------------------------------------------------------------
#增加.o文件的依赖
#
# Function : ADD_O_DEPENDS
# Arguments: 1 .o文件 2 .c/.cpp/.cc文件
# Returns  : 
# Usage    : $(call ADD_D_DEPENDS, .o, .c/.cpp/.cc)
# -----------------------------------------------------------------------------
define ADD_O_DEPENDS
$1 : $2
	$$(COMPILER) -c -o $$@ $(CFLAGS) $$<
endef

# -----------------------------------------------------------------------------
# Macro    : empty
# Returns  : an empty macro
# Usage    : $(empty)
# -----------------------------------------------------------------------------
empty :=

# -----------------------------------------------------------------------------
# Macro    : space
# Returns  : a single space
# Usage    : $(space)
# -----------------------------------------------------------------------------
space  := $(empty) $(empty)

space4 := $(space)$(space)$(space)$(space)

# -----------------------------------------------------------------------------
# Function : last2
# Arguments: a list
# Returns  : the penultimate (next-to-last) element of a list
# Usage    : $(call last2, <LIST>)
# -----------------------------------------------------------------------------
last2 = $(word $(words $1), x $1)

# -----------------------------------------------------------------------------
# Function : last3
# Arguments: a list
# Returns  : the antepenultimate (second-next-to-last) element of a list
# Usage    : $(call last3, <LIST>)
# -----------------------------------------------------------------------------
last3 = $(word $(words $1), x x $1)

# -----------------------------------------------------------------------------
# Function : remove-duplicates
# Arguments: a list
# Returns  : the list with duplicate items removed, order is preserved.
# Usage    : $(call remove-duplicates, <LIST>)
# Note     : This is equivalent to the 'uniq' function provided by GMSL,
#            however this implementation is non-recursive and *much*
#            faster. It will also not explode the stack with a lot of
#            items like 'uniq' does.
# -----------------------------------------------------------------------------
remove-duplicates = $(strip \
  $(eval __uniq_ret :=) \
  $(foreach __uniq_item,$1,\
    $(if $(findstring $(__uniq_item),$(__uniq_ret)),,\
      $(eval __uniq_ret += $(__uniq_item))\
    )\
  )\
  $(__uniq_ret))

# -----------------------------------------------------------------------------
# Macro    : this-makefile
# Returns  : the name of the current Makefile in the inclusion stack
# Usage    : $(this-makefile)
# -----------------------------------------------------------------------------
this-makefile = $(lastword $(MAKEFILE_LIST))


# -----------------------------------------------------------------------------
# Function : assert-defined
# Arguments: 1: list of variable names
# Returns  : None
# Usage    : $(call assert-defined, VAR1 VAR2 VAR3...)
# Rationale: Checks that all variables listed in $1 are defined, or abort the
#            build
# -----------------------------------------------------------------------------
assert-defined = $(foreach __varname,$(strip $1),\
  $(if $(strip $($(__varname))),,\
    $(error $(__varname) is not defined)\
  )\
)

# -----------------------------------------------------------------------------
# Function : clear-vars
# Arguments: 1: list of variable names
#            2: file where the variable should be defined
# Returns  : None
# Usage    : $(call clear-vars, VAR1 VAR2 VAR3...)
# Rationale: Clears/undefines all variables in argument list
# -----------------------------------------------------------------------------
clear-vars = $(foreach __varname,$1,$(eval $(__varname) := $(empty)))


# =============================================================================
#
# Utility functions
#
# =============================================================================

# -----------------------------------------------------------------------------
# Function : parent-dir
# Arguments: 1: path
# Returns  : Parent dir or path of $1, with final separator removed.
# -----------------------------------------------------------------------------
parent-dir = $(patsubst %/,%,$(dir $1))

# -----------------------------------------------------------------------------
# Strip any 'lib' prefix in front of a given string.
#
# Function : strip-lib-prefix
# Arguments: 1: module name
# Returns  : module name, without any 'lib' prefix if any
# Usage    : $(call strip-lib-prefix,$(LOCAL_MODULE))
# -----------------------------------------------------------------------------
strip-lib-prefix = $(1:lib%=%)

# -----------------------------------------------------------------------------
# Macro    : my-dir
# Returns  : the directory of the current Makefile
# Usage    : $(my-dir)
# -----------------------------------------------------------------------------
my-dir = $(call parent-dir,$(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST)))
