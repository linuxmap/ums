#ifndef _NETCBB_WRAPPER_H_
#define _NETCBB_WRAPPER_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_interface.h"
#include "netcbb_dhcpc.h"
#include "netcbb_pppoe.h"
#include "netcbb_sntp.h"
#include "netcbb_webs.h"
#include "netcbb_dhcps.h"
#include "netcbb_ntpc.h"
#include "netcbb_serv.h"
#include "netcbb_e1.h"
/*================================
��������NetInit
���ܣ���ģ��ĳ�ʼ������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK
��ע: ��û�ж���
==================================*/
s32 NetInit(void);

/*================================
��������NetQueryNetcbbVersion
���ܣ��ṩ��ҵ�����õ�os�汾�Ų�ѯ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  pchVer�� ��ȡ�汾���ַ���ָ��
                dwBufLen�����ַ����ĳ���
                pdwVerLen����ȡ�汾��ʵ���ַ������ȣ��ó��ȷ���֮ǰ�����dwBufLen�Ƚ��Ƿ����������ʱ�Ŷ�pVer��ֵ��

����ֵ˵���� OK/ERROR
==================================*/
s32  NetQueryVersion(char *pchVer, u32 dwBufLen);

/*================================
��������NetLogSwitch
���ܣ���ģ���ӡ����(Ĭ�Ϲر�)
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����1 : ��log
              0 : �ر�log
              Ĭ�Ϲرա�
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK
��ע: ��û�ж���
==================================*/
s32 NetLogSwitch(u32 dwSwitch);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_WRAPPER_H_*/

