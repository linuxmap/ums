#ifndef _UMCOSNT_H_
#define _UMCONST_H_

//�������
#define UM_USER_ERR				(u16)19001
#define UM_PSW_ERR				(u16)19002
#define UM_ACTOR_NOTMATCH		(u16)19003
#define UM_USER_DUPLICATE		(u16)19004
#define UM_USER_NOTEXIST		(u16)19005
#define UM_NOT_ENOUGHMEM		(u16)19006
#define UM_ACTOR_ONLY			(u16)19007
#define UM_OPERATE_NOTPERMIT	(u16)19008
#define UM_MULTILOGIN			(u16)0xffff //�ն˶����һ�����أ��������ظ���¼�Ĵ�����
//���سɹ�
#define UM_OK					0xAA
//���������û���Ŀ
#define MAX_USERNUM				128
#define MAX_CHARLENGTH			64
//�����û����
#define UM_ADMIN				0x01
#define UM_OPERATOR				0x02
//ÿ��UM_MCS_GETALLUSER_NOTIF���ص��û���Ϣ��
#define MAX_USERINFO_PER_MSG	15
//����ļ�������
#define MAX_UMFILENAME_LEN		32

#endif
