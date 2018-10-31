/*****************************************************************************
   ģ����      : GKCUI3.0
   �ļ���      : GKCInteTestMacro.h
   ����ļ�    : ��
   �ļ�ʵ�ֹ���: GKConsole���ɲ��Գ�������
   ����		   : �º��
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾     �޸���      �޸�����
   2004/09/10  1.0      �º��      ����
******************************************************************************/
#ifndef GKC_TEST_MACRO_H_
#define GKC_TEST_MACRO_H_

#include "eventid.h"

#define GKC_INTE_TEST_APP_ID 234
//��ȡ��ע��ʵ������
OSPEVENT( GKC_INTE_REG_ENDPOINT_COUNT_QUERY , EV_TEST_GKC_BGN + 1 );
//��ȡĳ����ע��ʵ���ͷ��Ϣ
OSPEVENT( GKC_INTE_REG_ENDPOINT_HEAD_QUERY ,  EV_TEST_GKC_BGN + 2 );
//��ȡĳ����ע��ʵ��ı�����Ϣ
OSPEVENT( GKC_INTE_REG_ENDPOINT_ALIAS_QUERY ,  EV_TEST_GKC_BGN + 3 );
//��ȡĳ����ע��ʵ��ĺ��е�ַ��Ϣ
OSPEVENT( GKC_INTE_REG_ENDPOINT_CALLADDR_QUERY ,  EV_TEST_GKC_BGN + 4 );
//��ȡʵ����е�����
OSPEVENT( GKC_INTE_CALL_COUNT_QUERY , EV_TEST_GKC_BGN + 5 );
//��ȡĳ��ʵ����еľ�����Ϣ
OSPEVENT( GKC_INTE_CALL_ITEM_QUERY , EV_TEST_GKC_BGN + 6 );
//�ж�ĳ����ע��ʵ���Ƿ����(����ƥ��)
OSPEVENT( GKC_INTE_IS_REG_ENDPOINT_EXIST_QUERY_BY_ALIAS , EV_TEST_GKC_BGN + 7 );
//�ж�ĳ����ע��ʵ���Ƿ����(Ras��ַƥ��)
OSPEVENT( GKC_INTE_IS_REG_ENDPOINT_EXIST_QUERY_BY_RAS_ADDR , EV_TEST_GKC_BGN + 8 );
//�ж�ĳ��ʵ������Ƿ����
OSPEVENT( GKC_INTE_IS_CALL_EXIST_QUERY, EV_TEST_GKC_BGN + 9 );

//��ȡǰ׺�����ţ�����
OSPEVENT( GKC_INTE_PREFIX_COUNT_QUERY , EV_TEST_GKC_BGN + 11 );
//��ȡĳ��ǰ׺�����ţ��ľ�����Ϣ
OSPEVENT( GKC_INTE_PREFIX_ITEM_QUERY , EV_TEST_GKC_BGN + 12 );
//��ȡ�ٽ�GK����������
OSPEVENT( GKC_INTE_NEIGHBOR_GK_COUNT_QUERY , EV_TEST_GKC_BGN + 13 );
//��ȡĳ���ٽ�GK�������ľ�����Ϣ
OSPEVENT( GKC_INTE_NEIGHBOR_GK_ITEM_QUERY , EV_TEST_GKC_BGN + 14 );
//��ȡGKע����֤����
OSPEVENT( GKC_INTE_AUTH_METHOD_QUERY , EV_TEST_GKC_BGN + 15 );
//���ĳ��ǰ׺�����ţ��Ƿ����
OSPEVENT( GKC_INTE_IS_PREFIX_EXIST_QUERY , EV_TEST_GKC_BGN + 16);
//����ٽ�GK�������Ƿ����
OSPEVENT( GKC_INTE_IS_NEIGHBOR_GK_EXIST_QUERY , EV_TEST_GKC_BGN + 17);
//���GKע����֤�����Ƿ�ƥ��
OSPEVENT( GKC_INTE_IS_AUTH_METHOD_MATCH_QUERY , EV_TEST_GKC_BGN + 18);

//��ȡ���δ�������
OSPEVENT( GKC_INTE_BANDWIDTH_COUNT_QUERY , EV_TEST_GKC_BGN + 21 );
//��ȡĳ�����δ���ľ�����Ϣ
OSPEVENT( GKC_INTE_BANDWIDTH_ITEM_QUERY , EV_TEST_GKC_BGN + 22 );
//���ĳ�����δ����Ƿ����
OSPEVENT( GKC_INTE_IS_BANDWIDTH_EXIST_QUERY , EV_TEST_GKC_BGN + 23 );

//��ȡ��֤Ip��Χ����
OSPEVENT( GKC_INTE_IP_RANGE_COUNT_QUERY , EV_TEST_GKC_BGN + 26 );
//��ȡĳ����֤Ip��Χ��Ϣ
OSPEVENT( GKC_INTE_IP_RANGE_ITEM_QUERY , EV_TEST_GKC_BGN + 27 );
//���ĳ����֤Ip��Χ�Ƿ����
OSPEVENT( GKC_INTE_IS_IP_RANGE_EXIST_QUERY , EV_TEST_GKC_BGN + 28 );

//��ȡ��֤ʵ���������
OSPEVENT( GKC_INTE_ENDPOINT_ALIAS_COUNT_QUERY , EV_TEST_GKC_BGN + 31);
//��ȡĳ����֤ʵ�����������Ϣ
OSPEVENT( GKC_INTE_ENDPOINT_ALIAS_ITEM_QUERY , EV_TEST_GKC_BGN + 32 );
//���ĳ����֤ʵ������Ƿ����
OSPEVENT( GKC_INTE_IS_ENDPOINT_ALIAS_EXIST_QUERY , EV_TEST_GKC_BGN + 33 );

//��ȡ�û�����
OSPEVENT( GKC_INTE_USER_COUNT_QUERY , EV_TEST_GKC_BGN + 41);
//��ȡĳ���û�������Ϣ
OSPEVENT( GKC_INTE_USER_ITEM_QUERY , EV_TEST_GKC_BGN + 42 );
//���ĳ���û��Ƿ����,����֤�û�����(������Ա�û���¼��Ч)
OSPEVENT( GKC_INTE_IS_USER_EXIST_QUERY , EV_TEST_GKC_BGN + 43 );
//���ĳ���û���Ϣ�Ƿ�ƥ��,��Ҫ��֤�û����ƺ�����(������Ա�û���¼��Ч)
OSPEVENT( GKC_INTE_IS_USER_MATCH_QUERY , EV_TEST_GKC_BGN + 44 );

//�Ƿ��¼Gkc
OSPEVENT( GKC_INTE_IS_GKC_LOGIN_QUERY , EV_TEST_GKC_BGN + 46 );
//��ȡ��ǰ��¼���û����ƺ�����
OSPEVENT( GKC_INTE_GET_LOGIN_USER_QUERY , EV_TEST_GKC_BGN + 47 );

#endif //GKC_INTE_TEST_MACRO_H_