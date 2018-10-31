## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,v7A linker.cmd \
  package/cfg/81xxApp_xv7A.ov7A \

linker.cmd: package/cfg/81xxApp_xv7A.xdl
	$(SED) 's"^\"\(package/cfg/81xxApp_xv7Acfg.cmd\)\"$""\"/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/t1-uranus/mpu2/prjlinux/test_config/\1\""' package/cfg/81xxApp_xv7A.xdl > $@
