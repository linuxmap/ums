#!/bin/sh
##########################################################
# Kedacom.
# Linux enviroment Build script
# author: wanglongbo@kedacom.com (Tel:7066)
##########################################################

#########################################################
# Usage:
#    mk_boot.sh 
#########################################################
this_file="mk_boot.sh"
this_dir=`pwd`
#topdir=$(cd ../../../;pwd)

input_path=$topdir/driver-git/uboot
version_path=$input_path/boot_output
#release_path=$topdir/Professional_VOB/10-common

netra_boards=( h600 h600l h700 h700_2g h800 h900 h900_2g hdu2 hdu2_s mpu2 mpu2ep )
ppc8377_boards=( apu2 t300 t300_b )
#ppcp2020_boards =kdv8000i
all_boards=(${netra_boards[@]} ${ppc8377_boards[@]})


#check param and input folder
check()
{
    cd $topdir || exit 1

    #check parameter
    check_ok=0
    for board in ${all_boards[@]}
    do
    if [ "$1" = $board ]; then check_ok=1; fi
done
    if [ "$check_ok" -ne "1" ]; then echo "[$this_file]: (\$1=$1) parameter error" && exit 1; fi
    
    #check directory
    if [ ! -d $input_path ]; then echo "[$this_file]: boot compiler directory missing"; fi
    if [ ! -d $input_path/boot_output ]; then mkdir $input_path/boot_output; fi
}



# build, and copy the result to $output_path/nip/
build()
{	
    cd $input_path/ || exit 1
		
#make distclean
	make distclean
	./make_uboot.sh $1	
 		
		
		   
    #copy_to
		cd $topdir
    
}

copy_to()
{
   release_dir=${release_path}/version/${3}/os_linux/${2}
   
	#check folder
	if [ ! -d $release_dir ] ;then 
				mkdir -p $release_dir;
	fi 
	
	#copy file
	cp  -rf $1 $release_dir;
}

release()
{
		case $1 in
				h600)
					copy_to $version_path/\* mt/h600 $2
						;;
				h700)
					copy_to $version_path/\* mt/h700_small $2
						;;
				h800)
					copy_to $version_path/\* mt/h800 $2
						;;						
				h900)
					copy_to $version_path/\* mt/h900_small $2
						;;
				hdu2)
					copy_to $version_path/\* $1 $2
						;;
				hdu2_s)
                                        copy_to $version_path/\* $1 $2
                                                ;;
				h700_2g)
					copy_to $version_path/\* mt/h700 $2
						;;		
				h900_2g)
					copy_to $version_path/\* mt/h900 $2
						;;
				mpu2)
					copy_to $version_path/\* $1 $2
						;;
				mpu2ep)
					copy_to $version_path/\* $1 $2
						;;							
				apu2)
					copy_to $version_path/\* $1 $2
						;;
				t300)
					copy_to $version_path/\* $1 $2
						;;
				t300_b)
                                        copy_to $version_path/\* $1 $2
                                                ;;													
			*)
					  #echo It is not required to copy!
						;;
   	esac   
}

begin_time_val=`date +%Y/%m/%d_%H:%M:%S`

##check
check $1

##build
build $1
echo "[$this_file]: make $1 uboot ok."

##release
release $1 release

end_time_val=`date +%Y/%m/%d_%H:%M:%S`
echo "[$this_file]: ($1) use time: $begin_time_val-$end_time_val"

echo "####### end $this_file $1#######"
####### End #######
