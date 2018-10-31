#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /mnt/hgfs/D/code/20131028_TPS/Professional_VOB/t1-uranus/mpu2/prjlinux;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/cgt6x_7_2_0;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdais_7_21_00_01/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/framework-components_3_21_00_13/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/sysbios_6_31_04_27/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/linuxutils_3_21_00_02/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/syslink_02_00_00_67_whole/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/syslink_02_00_00_67_whole;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/ipc_1_22_03_23_whole/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/osal_1_21_00_05/packages;/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x;/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/server_package
override XDCROOT = /opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /mnt/hgfs/D/code/20131028_TPS/Professional_VOB/t1-uranus/mpu2/prjlinux;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/cgt6x_7_2_0;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdais_7_21_00_01/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/framework-components_3_21_00_13/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/sysbios_6_31_04_27/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/linuxutils_3_21_00_02/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/syslink_02_00_00_67_whole/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/syslink_02_00_00_67_whole;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/ipc_1_22_03_23_whole/packages;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/osal_1_21_00_05/packages;/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x;/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/server_package;/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages;..
HOSTOS = Linux
endif
