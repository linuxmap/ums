### linux 82xx 版本apache编译 ###

	1. apr-1.5.2编译

		./configure --host=ppc-linux CC=/opt/ppc/bin/ppc_82xx-gcc CPP=/opt/ppc/bin/ppc_82xx-cpp CXX=/opt/ppc/bin/ppc_82xx-g++ --prefix=/usr/local82xx/apr ac_cv_file__dev_zero=yes ac_cv_func_setpgrp_void=yes ac_cv_sizeof_struct_iovec=8
		备注：出现cannot run test program while cross compiling，到configure注释掉相关解决
		make
		备注：出现tools/gen_test_char: cannot execute binary file，编译一次本机环境的apache，将gen_test_char拿过来，修改makefile，改用运行本机环境的gen_test_char解决
		make install
		
	2. apr-util-1.5.4编译

		./configure --host=ppc-linux CC=/opt/ppc/bin/ppc_82xx-gcc CPP=/opt/ppc/bin/ppc_82xx-cpp CXX=/opt/ppc/bin/ppc_82xx-g++ --prefix=/usr/local82xx/apr-util --with-apr=/usr/local82xx/apr
		make
		make install
		
	3. pcre-8.39编译
	
		./configure --host=ppc-linux CC=/opt/ppc/bin/ppc_82xx-gcc CPP=/opt/ppc/bin/ppc_82xx-cpp CXX=/opt/ppc/bin/ppc_82xx-g++ --prefix=/usr/local82xx/pcre
		make
		make install
		备注：不能使用pcre2
		
	4. httpd-2.4.25编译
	
		./configure --host=ppc-linux CC=/opt/ppc/bin/ppc_82xx-gcc CPP=/opt/ppc/bin/ppc_82xx-cpp CXX=/opt/ppc/bin/ppc_82xx-g++ --prefix=/usr/local82xx/apache ap_cv_void_ptr_lt_long=no --enable-module=so --with-apr=/usr/local82xx/apr --with-apr-util=/usr/local82xx/apr-util --with-pcre=/usr/local82xx/pcre LDFLAGS=-lpthread
		make
		备注：出现./gen_test_char: cannot execute binary file，编译一次本机环境的apache，将gen_test_char拿过来，修改/server/makefile，改用运行本机环境的gen_test_char解决
		make install

	5. /usr/local82xx/apache即为编译出的82xx版本apache


