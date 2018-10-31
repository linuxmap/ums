## 82xx环境编译 ##

1. 进入源码目录：cd ntp-4.2.6p5
2. **备注1：ntp.conf的默认路径是/etc/ntp.conf，通过修改源码中宏定义CONFIG_FILE，改为/usr/conf/ntp.conf**
2. 创建82xx版本的安装目录：mkdir /usr/local82xx/ntp
2. 配置编译环境：./configure  --prefix=/usr/local82xx/ntp/ --exec-prefix=/usr/local82xx/ntp/ --host=ppc-linux CC=/opt/ppc/bin/ppc_82xx-gcc --with-yielding-select=yes
3. 生成makefile：./config.status
4. **备注2：注释config.h中的HAVE_SIGACTION宏定义，否则编译出的ntpd在板卡上开机启动存在问题**
4. 编译：make
5. 安装：make install
6. /usr/local82xx/ntp下即为编译出的82xx版本ntp


## 85xx环境编译 ##

1. 进入源码目录：cd ntp-4.2.6p5
2. **备注1：ntp.conf的默认路径是/etc/ntp.conf，通过修改源码中宏定义CONFIG_FILE，改为/usr/conf/ntp.conf**
2. 创建85xx版本的安装目录：mkdir /usr/local85xx/ntp
2. 配置编译环境：./configure  --prefix=/usr/local82xx/ntp/ --exec-prefix=/usr/local82xx/ntp/ --host=ppc-linux CC=/opt/ppc_nofpu/bin/ppc_85xx-gcc
4. **备注2：注释config.h中的HAVE_SIGACTION宏定义，否则编译出的ntpd在板卡上开机启动存在问题**
4. 编译：make
5. 安装：make install
6. /usr/local85xx/ntp下即为编译出的85xx版本ntp


## 相关命令 ##

- ntpd -c /usr/conf/ntp.conf & 说明：-c 指定ntp.conf的路径，这里的路径必须用绝对路径
- ntpd -d & 说明：-d ntpd以debug方式运行，此运行方式会输出相关打印，有助于定位问题
- ntpdate -d 172.16.236.3 & 说明：-d 同上，ntpdate命令向指定ip的ntp同步一次时间，同步完成后，进程自行结束
- ntpd -p /usr/bin/ntp.pid & 说明：-p 将ntpd的pid信息输出到指定文件
- 帮助命令：man ntpd和man ntp.conf，在已安装ntp服务的linux机器上可用


