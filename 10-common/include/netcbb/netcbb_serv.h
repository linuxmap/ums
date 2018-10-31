/*************************************************************************
    > File Name: Netcbb_serv.h
    > Author: zengmengqiu
    > Mail: zengmengqiu@kedacom.com 
    > Created Time: Thu 19 Jun 2014 09:38:52 AM CST
 ************************************************************************/
#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#define NETSERVICE_TELNETD	"telnetd" 	//�궨��telnetd  
#define NETSERVICE_FTPD	    "ftpd"  	//�궨��ftpd
#define NETSERVICE_TFTPD	"tftpd"		//�궨��tftpd
#define NETSERVICE_HTTPD	"httpd"		//�궨��httpd

#define NETPROTO_TCP "tcp"
#define NETPROTO_UDP "udp"


typedef struct {
	s8  *pchServName;//������
	u16  wPort;//����˿ں�
	s8  *pchProto;//Э������
	s8  *pchArgPath;
}TServInfo;


/*�����ӿڶ���*/
/*================================
��������NetServiceStart
���ܣ�����������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����pchServName��������
		                          ptParaM��ָ��TServInfo �Ľṹ��ָ��
����ֵ˵����      OK/ERROR
==================================*/
s32 NetServiceStart(s8 *pchServName, TServInfo * ptParaM);

/*================================
��������NetServiceStop
���ܣ��رշ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵���� OK/ERROR
==================================*/
s32 NetServiceStop(s8 *pchServName);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */
#endif