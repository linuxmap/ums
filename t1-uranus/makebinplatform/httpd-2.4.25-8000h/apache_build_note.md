### linux x86 版本apache编译 ###

	1. apr-1.5.2编译
		
		./configure --prefix=/usr/localx86/apr
		make
		make install

	2. apr-util-1.5.4编译
		
		./configure --prefix=/usr/localx86/apr-util --with-apr=/usr/localx86/apr
		make
		make install
		
	3. pcre-8.39编译	备注：不能使用pcre2
	
		./configure --prefix=/usr/localx86/pcre
		make
		make install
		
	4. httpd-2.4.25编译
		
		./configure --prefix=/usr/localx86/apache --with-apr=/usr/localx86/apr --with-apr-util=/usr/localx86/apr-util --with-pcre=/usr/localx86/pcre LDFLAGS=-lpthread
		make
		make install
	
	5. 如果缺失mod_cgi.so
		
		mod_cgi.c位于httpd-2.4.25/modules/generators目录
		/usr/localx86/apache/bin/apxs -i -a -c mod_cgi.c即可编译出mod_cgi.so
		

### fcgi安装 ###

	1. mod_fastcgi-2.4.6编译
	
		patch -p1 <byte-compile-against-apache24.diff 打补丁
		cp Makefile.AP2 makefie
		修改makefile里面的top_dir为/usr/localx86/apache
		make -f makefie
		拷贝cp .libs/mod_fastcgi.so /usr/localx86/apache/modules/
		
	2. fcgi-2.4.0编译(fcgi开发环境)
	
		./configure --prefix=/usr/localx86/fcgi
		make
		make install

