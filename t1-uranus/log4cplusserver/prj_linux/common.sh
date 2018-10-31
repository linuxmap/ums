#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../common/linux_build/mbt_build

export MOD_NAME=log4cplusserver
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_EXEC=./log4cplusserver.mk

${BUILD_CMD} "$@"
