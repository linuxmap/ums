#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../common/linux_build/mbt_build

export MOD_NAME=log4cplus
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_STATICLIB=./log4cplus.mk
export MK_PATH_OF_SHAREDLIB=./log4cplusdll.mk

${BUILD_CMD} "$@"
