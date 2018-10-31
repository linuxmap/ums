#!/bin/sh
##########################################################
# Kedacom.
# Linux enviroment Build script
# author: lantianyu@kedacom.com (Tel:8360)
##########################################################
this_file="mk.sh"
this_dir=`pwd`
export topdir=$(cd ../../../;pwd) 
unset CROSS_COMPILE
export PATH=$PATH:/opt/arm/bin:/opt/montavista/pro/devkit/arm/v5t_le/bin:/opt/freescale/usr/local/gcc-4.2.171-eglibc-2.5.171/powerpc-linux-gnu/bin:/opt/CodeSourcery/Sourcery_G++_Lite/bin

export output_path=$topdir/driver-git/compile_output
export release_path=$topdir/10-common

target_cpu=( netra)
ppc8260_boards=(mau kdv7810 cri vri kdv8010 mcu mdsc dri16 kdv8010c kdv8010c1 dri apu kdv8005 vpu dec5 dsc dsi kdv8000b)
ppc8313_boards=(kdv7820 hdu hdmpu)
ppc8377_boards=(mpc2 dri2 cri2)
ppc85xx_boards=(hdsc kdv7620)
davinci_boards=(ts5210 ts6610 ts7210 ts5210l ts6610l)

netra_boards=(h600 h600l h700 h700_2g h800 h900 h900_2g hdu2 hdu2_s mpu2 mpu2ep)
powerpc8377_boards=( apu2 t300 t300_b)

all_boards=( ${netra_boards[@]} ${powerpc8377_boards[@]} )
need_boards=( h600 h600l h700 h700_2g h800 h900 h900_2g hdu2 hdu2_s mpu2 mpu2ep apu2 t300 t300_b) 
################################ Functions ###############################
check()
{
   cd $this_dir || exit 1

    if [ ! -f ./mk_nip.sh ] || [ ! -f ./mk_ios.sh ] || [ ! -f ./mk_platform.sh ] || [ ! -f ./mk_boot.sh ]; then echo "[$this_file]: some shell script missing" && exit 1; fi

		[ ! -x ./mk_boot.sh ] && chmod +x ./mk_boot.sh
    [ ! -x ./mk_nip.sh ] && chmod +x ./mk_nip.sh
    [ ! -x ./mk_ios.sh ] && chmod +x ./mk_ios.sh
    [ ! -x ./mk_platform.sh ] && chmod +x ./mk_platform.sh
    
    if [ -z $1 ]; then echo "[$this_file]: parameter error" && exit 1; fi
} 

build()
{ 		
		case "$1" in
        nip)
            cd $this_dir 
            ./mk_nip.sh $2  
              ;;
        platform)
            cd $this_dir 
             ./mk_platform.sh  
            ;;
        mau|kdv7810|cri|vri|kdv8010|mcu|mdsc|dri16|kdv8010c|kdv8010c1|dri|apu|kdv8005|vpu|dec5|dsc|dsi|kdv8000b|kdv7820|hdu|hdmpu|hdsc|kdv7620|ts5210|ts6610|ts7210|ts5210l|ts6610l|mpc2|dri2|cri2|h600|h600l|h700|h900|hdu2|hdu2_s|h700_2g|h900_2g|mpu2|mpu2ep|apu2|t300|h800|t300_b)
            cd $this_dir
	     ./mk_boot.sh $1
             ./mk_ios.sh $1
	     ./mk_platform.sh
            ;;
        is3-mpc8313)
            ./mk_nip.sh ppc8313 is3-mpc8313
            ./mk_ios.sh is3-mpc8313 
            ;;         
        is3-mpc8548)
            ./mk_nip.sh ppc85xx is3-mpc8548
            ./mk_ios.sh is3-mpc8548
            ;;         
        all)
            cd $this_dir 
            #is3-mpc8548 is3-mpc8313 have their own nip config
            	
            	for board in ${need_boards[@]}
              do
              ./mk_boot.sh $board 
            done 
            	
            	
            for cpu in ${target_cpu[@]}
              do
               ./mk_nip.sh $cpu 
            done	
            	
            for board in ${need_boards[@]}
              do
               ./mk_ios.sh $board
            done     
            ./mk_platform.sh  #dsplink in the platform need davinci_vmlinux.

            ;;
        *)
            echo "[$this_file]: no $1 target build-rule found"
            echo "[$this_file]: this script can only build: nip, platform, ${all_boards[@]}, and all"
            exit 1
            ;;
    esac
}

################### Main Program Start ##################
echo "####### begin $this_file #######"

begin_time_val=`date +%Y/%m/%d_%H:%M:%S`

##clear nip
rm -rf $output_path/nip
##clear platform
rm -rf $output_path/platform

##check
check $1

##build
build $1 $2 
             
end_time_val=`date +%Y/%m/%d_%H:%M:%S`
echo "[$this_file]: ($1) use time: $begin_time_val-$end_time_val"

echo "####### end $this_file #######"
####### End #######
