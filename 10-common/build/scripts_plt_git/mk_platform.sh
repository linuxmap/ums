#!/bin/sh
##########################################################
# Kedacom.
# Linux enviroment Build script
# author: lantianyu@kedacom.com (Tel:8360)
##########################################################
this_file="mk_platform.sh"
this_dir=`pwd`

unset CROSS_COMPILE
export PATH=$PATH:/opt/ppc/bin:/opt/ppc_nofpu/bin:opt/arm/bin:/opt/montavista/pro/devkit/arm/v5t_le/bin:/opt/CodeSourcery/Sourcery_G++_Lite/bin:/opt/freescale/usr/local/gcc-4.2.171-eglibc-2.5.171/powerpc-linux-gnu/bin


wapper_dir=$topdir/driver-git/platform
brdwrapper_dir=$wapper_dir/20-cbb/platform/brdwrapper
nipwrapper_dir=$wapper_dir/20-cbb/platform/nipwrapper
vpssm3server_dir=$wapper_dir/20-cbb/platform/netra/hdvpss/hdvpss_01_00_01_37
vpssm3_output_dir=$topdir/10-common/version/release/linux_arm_dm81xx
dsplink_dir=$wapper_dir/20-cbb/platform/dvevm/dsplink

#output_path=$topdir/compile_output

#check param and input folder
check()
{
    if [ ! -d $brdwrapper_dir ] || [ ! -d $nipwrapper_dir ] || [ ! -d $vpssm3server_dir ]
     then
        echo "[$this_file]: platform directory missing." && exit 1
    fi
}

# build all
build()
{
    if cd $vpssm3server_dir ; then
        echo "[$this_file]: Building vpss-M3 server..."
        [ ! -x ./compile ] && chmod +x ./compile
        ./compile
        cd - >/dev/null 2>&1
    fi

    if cd $nipwrapper_dir ; then
        echo "[$this_file]: Building nipwrapper..."
        [ ! -x ./compile_linux ] && chmod +x ./compile_linux
        ./compile_linux
        cd - >/dev/null 2>&1
    fi

    if cd $brdwrapper_dir ; then
        echo "[$this_file]: Building brdwrapper lib..."
        [ ! -x ./compile_lib ] && chmod +x ./compile_lib
        ./compile_lib
        cd - >/dev/null 2>&1
    fi



}

#copy compile result to $output_path/platform
coyp_result()
{
    cd $wapper_dir || exit 1
    
    dst_wrapper=$output_path/platform
    if [ ! -d $dst_wrapper ]; then mkdir -p $dst_wrapper; fi

    mkdir -p $dst_wrapper/10-common/lib/cbb/platform
    mkdir -p $dst_wrapper/10-common/lib/cbb/dvevm
    mkdir -p $dst_wrapper/10-common/version
    cp -rfd 10-common/lib/cbb/platform/* $dst_wrapper/10-common/lib/cbb/platform
    cp -rfd 10-common/lib/cbb/dvevm/* $dst_wrapper/10-common/lib/cbb/dvevm
    cp -rfd 10-common/version/* $dst_wrapper/10-common/version
    cp -rfd 10-common/version/cbb/platform/release/*.xem3 $vpssm3_output_dir
    cp -rfd 10-common/version/cbb/platform/release/*.xem3 $vpssm3_output_dir/../os_linux/mpu2ep
}

#copy to relative path
copy_to()
{
  source_path=$output_path/platform/10-common/lib/cbb/platform/${4}/linux_${2} 
  release_dir=${release_path}/lib/${4}/linux_${3}/

	if [ ! -d $release_dir ] ; then
			mkdir -p $release_dir;
	fi		
	
	#copy file
	cp  -rf ${source_path}/$1 $release_dir  ;
}

#release to target path
release()
{  		
		##netra
		copy_to  libnipwrapper.a 	arm_dm81xx   arm_dm81xx	 release
		copy_to  libbrdwrapper.a 	arm_dm81xx   arm_dm81xx	 release
		copy_to  libsyslink.a 	arm_dm81xx   arm_dm81xx	 release
		copy_to  libvpssctrl.a 	arm_dm81xx  arm_dm81xx	 release
		copy_to  libdm_audio.a 	arm_dm81xx   arm_dm81xx	 release
		copy_to  libdspcci.a 	arm_dm81xx   arm_dm81xx	 release
		copy_to  libmca.a 	arm_dm81xx   arm_dm81xx	 release
		
		##powerpc8377
		copy_to  libnipwrapper.a 	ppc_8377_2637   ppc_8377_2637	 release
		copy_to  libbrdwrapper.a 	ppc_8377_2637   ppc_8377_2637	 release
		copy_to  libmca.a 	ppc_8377_2637   ppc_8377_2637	 release		
		copy_to  libmsnd_audio.a 	ppc_8377_2637   ppc_8377_2637	 release		
}


################### Main Program Start ##################
echo "####### begin $this_file #######"

begin_time_val=`date +%Y/%m/%d_%H:%M:%S`

##check
check

##build
build
echo "[$this_file]: make platform ok."

##copy_to
coyp_result

##release
release

end_time_val=`date +%Y/%m/%d_%H:%M:%S`
echo "[$this_file]: use time: $begin_time_val-$end_time_val"

echo "####### end $this_file #######"
####### End #######
