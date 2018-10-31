#!usr/bin/perl
#
# Perl Source File -- Created with SAPIEN Technologies PrimalScript 3.1
#
# NAME: module build process
#
# AUTHOR: chenhuiren , xuping ,pengjing
# DATE  : 
#
# PURPOSE: 
#
# =====================================================================================================================
print "\n=======================================================================\n";
print "\n                            INT BUILD START                            \n";
print "\n=======================================================================\n";
# У��ű��������
$place = "Validate_Script_Para";
print "\n$module - $place......\n";
# def 3
for ( my $i = 0 ; $i < @ARGV; $i++ )
{
	if ( $ARGV[$i] =~ /^-/ ) # "-"��ʶoptions
	{
		if ( $intoptions eq "" )
		{
			$intoptions = $ARGV[$i];
			$intoptions =~ s/^-//g; # ȥ��������ʶ��'-'֮����д���
			if ( $intoptions eq "" )
			{
				print "Invalid Option '$ARGV[$i]' !\n";
				exit 1; # �����Ĺؼ�����ȻΪ�����˳���������
			}
			$intoptions = lc($intoptions); # ������ת��ΪСд
			if (( $intoptions ne "a" ) && ( $intoptions ne "s" ))
			{
				print "Invalid Option '$ARGV[$i]' !\n";
				exit 1; # �����Ĺؼ�����ȻΪ�����˳���������
			}
		}
		else
		{
			print "ReDefine Options '$ARGV[$i]' after '$intoptions' !\n";
			exit 1; # ������������ȷ���˳���������
		}
	}
	elsif ( $version eq "" ) # ��һ������Ϊ�汾��
	{
		$version = $ARGV[$i];
	}
	elsif (( $intspecRP eq "" ) && ( $ARGV[$i] =~ /^[\\\/]+/ )) # ����������Ϊָ������·��
	{
		$intspecRP = $ARGV[$i];
	}
	else
	{
		print "Redundant ARGVmeters '$ARGV[$i]' !\n";
		exit 1; # ������������ȷ���˳���������
	}
}
undef($i);
if ( $version eq "" )
{
	print "Lost 'Version' ARGVmeters in '@ARGV' !\n";
	exit 1; # ȱ�ٹؼ�����
}
if (( $intoptions eq "a" ) && ( $intspecRP ne "" ))
{
	print "Not Match options '$intoptions' and specRP '$intspecRP' in '@ARGV' !\n";
	exit 1; # ȱ�ٹؼ�����
}
require ("common.pl");





# =====================================================================================================================
# ��ȡģ���б�
$place = "Get_Module_List";
print "\n$module - $place......\n";
if ( !open (MODULES,$workpath."$version.ini") )
{
	&printerror(0,"Failed Open File '$workpath$version".".ini' !\n");
	&command("pause");
	exit 1;
}
@modulefile = <MODULES>;
close(MODULES);
chomp(@modulefile);
if ( $OS )
{
	@modulelines = &getline(2,"l",@modulefile);
}
else
{
	@modulelines = &getline(2,"w",@modulefile);
}
undef(@modulefile);
if ( @modulelines == 0 )
{
	&printerror(0,"Failed Found Modules Group in '$workpath$version".".ini' !\n");
	&command("pause");
	exit 1; # �Ҳ����汾����ģ�����˳���������
}
# def 3
foreach $moduleline (@modulelines)
{
	my @part = &getvalue(" ",$moduleline); # 0����ϵͳ 1С�鸺�����ʼ� 2�����ؼ����б� 3ģ���б�
	if ( @part < 4 )
	{
		&printerror(0,"Wrong Format in '$moduleline' !\n");
		&command("pause");
		exit 1; # ģ���б��ʽ�������˳���������
	}
	$part[1] = $CMOM if ( $part[1] =~ /^-*$/ );
	$part[2] = $defenv if ( $part[2] =~ /^-*$/ );
	push(@groupowner,$part[1]);
	push(@envkeylist,$part[2]);
	push(@modulelist,$part[3]);
}
undef($moduleline);
undef(@part);
undef(@modulelines);
# ��ȫ��ģ��д��allmodules.log�ļ�
for ( my $i = 0 ; $i < @modulelist ; $i++ )
{
	my @part = &getvalue(",",$modulelist[$i]);
	&writelog($verworkP."allmodules.log","@part"." ");
}
undef(@part);
undef($i);
# =====================================================================================================================
if ( $OS && $ISM )
{
	&printerror(1,"Linux SourceCode is mounted , Skip Mkbl Setcs and Update View !\n");
}
else
{
	# ��ȡ���� , ����Դ��
	$place = "Access_SnapshotView_Path";
	print "\n$module - $place......\n";
	if ( !chdir($SnapviewP) ) # ���뾲̬��ͼ����·�� , ����޷����� , �򱨴� , ���˳�
	{
		&printerror(0,"Failed Access Snapshot View Path '$SnapviewP' !\n");
		&command("pause");
		exit 1;
	}
	# ����� , ���Ƽ����� , ��ȡ�Ƽ����� , ���������д����򱨴� , �����˳�
	$place = "Make_Baseline";
	print "\n$module - $place......\n";
	&cleanerror;
	####&command("mkbl");  #hanjian 20120810 svn don't need clearcase command
###	if ( !&geterror )
###	{
###		$place = "Change_Stream";
###		print "\n$module - $place......\n";
###		&cleanerror;
###		&command("chstream");
###		if ( !&geterror )
###		{
###			$place = "Get_BaseLine";
###			print "\n$module - $place......\n";
###			&cleanerror;
###			$baseline = &command("lsstream"); # ȡ��̬��ͼ��Ӧ���Ƽ����ߵ��б�
###			if ( !&geterror )
###			{
###				$baseline =~ s/\s/\n/g; # �ַ��������еĿո��ûس��滻
###				&writelog($verworkP."baseline.log",$baseline."\n");
###				print $baseline;
###			}
###			else
###			{
###				&printerror(0,"@errors");
###			}
###			undef($baseline);
###		}
###		else
###		{
###			&printerror(0,"@errors");
###		}
###	}
###	else
###	{
###		&printerror(0,"@errors");
###	}
	# ��ͼͬ���͸���Դ��֮ǰ , Windows����ϵͳ����Ҫ���û�������
	if ( !$OS )
	{
		$place = "Set_Update_Env";
		print "\n$module - $place......\n";
		&getenv("GROUPS");
	}
	# ��ͼͬ���͸���Դ�� , ���������д��� , �򱨴� , ���˳�
	###$place = "Synchronize_View";
	$place = "Update all of the code:";
	
	print "\n$module - $place......\n";
	&cleanerror;
	###&command("setcs");
	###&command("setcs"); # chenhuiren 090610 #hanjian20120810 svn don't need clearcase cpmmand
	if ( &geterror )
	{
		&printerror(0,"@errors");
		&command("pause");
		exit 1;
	}
	$place = "Update_All";
	print "\n$module - $place......\n";
	&cleanerror;
	$SnapviewP1 = $SnapviewP;
	chop($SnapviewP1);
	print "$SnapviewP1 !!!!!!!!!!!******\n";
	&command("update",$SnapviewP1,$verworkP."all-code_".$builddatetime."_update.log");
	undef($SnapviewP1);

	if ( &geterror )
	{
		&printerror(0,"@errors");
		&command("pause");
		exit 1;
	}
	# ����update LOG ??
	# �ص�����·��
	$place = "Backto_Script_Path";
	&printerror(0,"Warnning:Failed Back to Work Path '$workpath' !\n") if ( !chdir($workpath) );
	# =====================================================================================================================
	# ȥ��Դ��ֻ������
	$place = "DisReadonly_SourceCode";
	print "\n$module - $place......\n";
	&cleanerror;
	&command("disreadonly",$SnapviewP); # ���ø���Դ��������������Ϣ��error.log��
	&printerror(0,"@errors") if ( &geterror );
}
# =====================================================================================================================



# ���뿪ʼ֮ǰ��Ԥ����
&preprocess("b");


# ����git����
my @git_projects = qw(
    kernel/netra-2.6.37    nip   
    platform  uboot
);
foreach my $project_name(@git_projects) {
    my $git_dir = $SnapviewP.$project_name;
    &command("update",$git_dir);
}


#======================================================================================================================
# �������֮ǰɾ��������Ϣ�ļ����У����оɵı�����Ϣ
# add by hanjian 20120824
 #&deletecompileinfo;

#======================================================================================================================

# ���뿪ʼ , ������
$place = "Module_Process_Compile";
print "\n$module - $place......\n";
for ( my $i = 0 ; $i < @modulelist ; $i++ )
{
	my @intmodules = &getvalue(",",$modulelist[$i]);
	&module("b",$envkeylist[$i],@intmodules);
}
undef(@intmodules);
undef($i);
# ����֮��������� , ����У�� , ���� , ֪ͨȫ����������������
# =====================================================================================================================
# У�� , ���� , ֪֮ͨǰ��Ԥ����
&preprocess("crni");
# ����windows��linuxЭͬ����ʱ�ķ���λ��
$RP = &revisepath(1,$ReleaseP.$builddatetime); # ���ݷ��������ڷ���·�������ǰ�ļ���/��ǰʱ���ļ���������ÿ�η���
my $sharefile = $ReleaseP."share.txt";
my $D = 0; # ���share.txt�Ѿ�����,Ĭ��ɾ�����ļ�
my $C = 0; # ���share.txt�Ѿ�����,Ĭ�ϲ������µ�share�ļ�
if ( $intoptions eq "a" )
{
	$place = "Build_Together";
	print "\n$module - $place......\n";
	print "\nSearching Share...\n";
	if ( -e $sharefile && open (SHARE,$sharefile) )
	{
		print "\nGetting Share...\n";
		my $line = <SHARE>;
		close(SHARE);
		$D = 1; # Share�ļ��Ѿ�����,�����Ҫɾ�����ļ�
		my @value = &getvalue(":",$line);
		if ( @value == 2 )
		{
			my @OSstr = ("Windows","Linux");
			my $str = $OSstr[!$OS];
			my $str1 = $OSstr[$OS];
			if ( $value[0] =~ /^$str$/i ) # ���뵱share.txt�еĲ���ϵͳ��ʶ�뵱ǰ����ϵͳ�෴ʱ,��ȷ����ֵ������Ч.
			{
				if ( $WF && ( $value[0] =~ /^Linux$/i ))
				{
					&printerror(0,"Wrong OS of '$value[1]' in '$sharefile' when Windows Build First !\n");
				}
				else
				{
					if ( $value[1] =~ /^\d{8}-\d{4}$/ ) # ���ڷ���yyyymmdd-hhmm��ʽ
					{
						use Time::Local;
						my $dis = &difftime($builddatetime,$value[1]);
						$dis = abs($dis);
						$RP = &revisepath(1,$ReleaseP.$value[1]) if ( $dis <= $TS ); # Эͬ���� , ��ȡ�����ļ��еĹ�����·��
						no Time::Local;
					}
					else
					{
						&printerror(0,"Wrong Format Datetime of '$value[1]' in '$sharefile' !\n");
					}
				}
			}
			elsif ( $value[0] =~ /^$str1$/i )
			{
				if ( $WF && $OS )
				{
					&printerror(1,"$place : Don't Create Share when Windows Build First !\n");
				}
				else
				{
					$C = 1; # ͬ����ϵͳ�±�����,��Ҫ���´���share�ļ�
				}
			}
			else
			{
				&printerror(0,"Wrong Format OS of '$value[0]' in '$sharefile' !\n");
			}
		}
		else
		{
			&printerror(0,"Wrong Format of '$line' in '$sharefile' !\n");
		}
	}
	elsif ( !-e $sharefile ) # ���share�ļ������� , �򴴽����ļ��ṩ��Эͬ���빲��
	{
		if ( $WF && $OS )
		{
			&printerror(1,"$place : Don't Create Share when Windows Build First !\n");
		}
		else
		{
			$C = 1;
		}
	}
	else # share�ļ����ڵ��޷���
	{
		$D = 1;
	}
}
elsif ( $intoptions eq "s" )
{
	$place = "Build_Single";
	print "\n$module - $place......\n";
	$RP = &revisepath(1,$intspecRP) if ( $intspecRP ne "" );
	if ( -e $sharefile )
	{
		$D = 1; # ���share�ļ��Ѿ����� , ��ɾ�����ļ�
	}
}
if ( $D )
{
	print "\nDeleting Share...\n";
	&cleanerror;
	&command("del","f",$sharefile); # ��ȡ��������·����ɾ�������ļ�
	if ( &geterror )
	{
		&printerror(0,"Failed Del ShareFile '$sharefile' !\n");
		&command("pause");
		exit 1; # �Ҳ����汾����ģ�����˳���������
	}
	else
	{
		&printerror(1,"$place : Successfully Delete ShareFile '$sharefile' !\n");
	}
}
if ( $C )
{
	print "\nCreating Share...\n";
	if ( open (SHARE,">$sharefile") )
	{
		print SHARE "$OSstring : $builddatetime";
		close(SHARE);
		&printerror(1,"$place : Successfully Create ShareFile '$sharefile' !\n");
	}
	else # ����share�ļ�ʧ��
	{
		&printerror(0,"Failed Create ShareFile '$sharefile' !\n");
	}
}
undef($D);
undef($C);
undef($sharefile);
undef($intoptions);
undef($intspecRP);
&printerror(1,"\n$place : ReleasePlace : $RP\n");
# =====================================================================================================================
# У�� , ���� , ֪ͨ
$place = "Module_Process_Check_Release_Notify";
print "\n$module - $place......\n";
for ( my $i = 0 ; $i < @modulelist ; $i++ )
{
	my @intmodules = &getvalue(",",$modulelist[$i]);
	$gownerM = $groupowner[$i];
	&module("crni","-",@intmodules);
}
undef(@intmodules);
undef($i);
# У�� , ���� , ֪֮ͨ���������
&afterprocess("bcrni");
# =====================================================================================================================
# �رձ��������Ϣ�ļ�
close(BUILDERROR);
print "\n================================= END =================================\n";
sub difftime
{
	my ($s,$d) = @_;
	my $sd = 1441;
	if (( $s !~ /^\d{8}-\d{4}$/ ) || ( $d !~ /^\d{8}-\d{4}$/ ))
	{
		&printerror(0,"Wrong Format of '$s' or '$d' !\n");
	}
	else
	{
		my @tm = ("",$s,$s,$s,$s,$s); # ����($sec,$min,$hour,$mday,$mon,$year)����
		$tm[1] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$5/g; # ��ȡ'min'
		$tm[2] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$4/g; # ��ȡ'hour'
		$tm[3] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$3/g; # ��ȡ'mday'
		$tm[4] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$2/g; # ��ȡ'mon'
		$tm[4] = $tm[4]-1; # timelocal���±�����"0~11"��Χ��
		$tm[5] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$1/g; # ��ȡ'year'
		my $st = timelocal(@tm);
		my @tm = ("",$d,$d,$d,$d,$d); # ����($sec,$min,$hour,$mday,$mon,$year)����
		$tm[1] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$5/g; # ��ȡ'min'
		$tm[2] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$4/g; # ��ȡ'hour'
		$tm[3] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$3/g; # ��ȡ'mday'
		$tm[4] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$2/g; # ��ȡ'mon'
		$tm[4] = $tm[4]-1; # timelocal���±�����"0~11"��Χ��
		$tm[5] =~ s/(\d{4})(\d{2})(\d{2})-(\d{2})(\d{2})/$1/g; # ��ȡ'year'
		my $dt = timelocal(@tm);
		$sd = $st-$dt;
	}
	return $sd;
}
# End
