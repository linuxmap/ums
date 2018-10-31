#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../common/linux_build/mbt_build

export MOD_NAME=log4cplusclient
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_STATICLIB=./log4cplusclient.mk
export MK_PATH_OF_SHAREDLIB=./log4cplusclientdll.mk

${BUILD_CMD} "$@"
