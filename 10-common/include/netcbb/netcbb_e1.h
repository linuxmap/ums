#ifndef _NETCBB_E1_H_
#define _NETCBB_E1_H_
#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */




  
/*TBrdE1MultiLinkChanInfo�ṹ����dwProtocolType�����궨�� */
#define INTERFACE_PROTOCOL_PPP       0 /* �ӿ�Э��PPP */
#define INTERFACE_PROTOCOL_HDLC      1 /* �ӿ�Э��HDLC */

/* TBrdE1MultiLinkChanInfo�ṹ����dwAuthenticationType�����궨�� */
#define MP_AUTHENTICATION_NONE      0  /* ��������֤���� */
#define MP_AUTHENTICATION_PAP       1  /* PPP���ӵ���֤����PAP */
#define MP_AUTHENTICATION_CHAP      2  /* PPP���ӵ���֤����CHAP */

/* TBrdE1MultiLinkChanInfo�ṹ����dwFragMinPackageLen ������Χ�궨�� */
#define MP_FRAG_MIN_PACKAGE_LEN_MIN_VAL  20
#define MP_FRAG_MIN_PACKAGE_LEN_MAX_VAL  1500

#define E1_TS0_MASK        0x00000001


/* TBrdE1SerialInfo�ṹ����dwEchoInterval dwEchoMaxRetry �������ֵ�궨�� */
#define E1_SERIAL_ECHO_MAX_VAL           256

/* dwFragMinPackageLen dwSerialId dwE1ChanGroupId �����Զ����ú궨�� */
#define E1_PARAM_AUTO_CONFIG            0xffffffff

/* ���� wBufLength ��Χ���� */
#define E1_TRANS_BUF_MAX_LEN   (u32)8000 /* ���������������BUF�ĳ���,��λ�ֽ� */
#define E1_TRANS_BUF_MIN_LEN   (u32)800  /* ��������������СBUF�ĳ���,��λ�ֽ� */
#define E1_TRANS_CHAN_MAX_NUM  (u8)16    /* ���֧�ֵ�E1͸������ͨ���ĸ�����һ��ͨ������Ӧ��һ������E1��· */

/* E1ģ�鷵��ֵ�������붨�� */
#define E1_ERR_UNKNOWN                         (NET_E1_BASE_ERROR+0)   /* δ֪���� */
#define E1_ERR_PARAM_EXCEPTION                 (NET_E1_BASE_ERROR+1)   /* �����쳣 */
#define E1_ERR_SERIAL_ID_INVALID               (NET_E1_BASE_ERROR+2)   /* SERIALͬ���ӿں���Ч */
#define E1_ERR_E1_ID_INVALID                   (NET_E1_BASE_ERROR+3)   /* E1�ӿں���Ч */
#define E1_ERR_E1_TSMASK_INVALID               (NET_E1_BASE_ERROR+4)   /* E1ʱ϶������Ч */
#define E1_ERR_E1_CHANGROUP_ID_INVALID         (NET_E1_BASE_ERROR+5)   /* E1ʱ϶�������ڵı������Ч */
#define E1_ERR_SERIAL_PROTOCOL_TYPE_INVALID    (NET_E1_BASE_ERROR+6) /* �ӿ�Э���װ������Ч */
#define E1_ERR_SERIAL_ECHO_INTERVAL_INVALID    (NET_E1_BASE_ERROR+7) /* ͬ���ӿڵ�echo����ʱ������Ч */
#define E1_ERR_SERIAL_ECHO_MAXRETRY_INVALID    (NET_E1_BASE_ERROR+8) /* ͬ���ӿڵ�echo����ط�������Ч */
#define E1_ERR_STRING_LEN_OVERFLOW             (NET_E1_BASE_ERROR+9) /* �ַ���������� */
#define E1_ERR_NIP_OPT_ERR                     (NET_E1_BASE_ERROR+10)/* nip�ӿڵ���ʧ�� */
#define E1_ERR_CHAN_NOT_CONF                   (NET_E1_BASE_ERROR+11)/* ָ����ͨ����δ��ʹ�� */
#define E1_ERR_CHAN_CONFLICT                   (NET_E1_BASE_ERROR+12)/* ͨ���ų�ͻ��ָ����ͨ�����ѱ�ʹ�� */
#define E1_ERR_MP_AUTHEN_TYPE_INVALID          (NET_E1_BASE_ERROR+13)/* PPP���ӵ���֤����������Ч */
#define E1_ERR_MP_FRAG_MIN_PACKAGE_LEN_INVALID (NET_E1_BASE_ERROR+14)/* ��С��Ƭ������Ч */

#define E1_PARAM_CHECK_ERROR			NET_E1_BASE_ERROR +15
#define E1_PARAM_CONFLICT 			NET_E1_BASE_ERROR +16




#define MP_STRING_MAX_LEN            NET_DEF_STR_LEN  /* TNetE1MultiLinkChanInfo�ṹ�����ַ�����󳤶� */
/* E1��·NIP��װ�ӿ���غ궨�� */
#define E1_SINGLE_LINK_CHAN_MAX_NUM  8 /* ���֧�ֵ�E1����·serialͬ���ӿڸ��� */
#define E1_MULTI_LINK_CHAN_MAX_NUM   8 /* ���֧�ֵ�E1����·��������ͨ��(��virtual����ģ��ӿ�)���� */

/*E1��صĽṹ����*/
/* E1��·����serial�ӿڲ����ṹ */
typedef struct{
    u32 dwUsedFlag;                  /* ��ǰserialͬ���ӿ�ʹ�ñ�־,��1ʹ�ã����������Ч��0��ʹ�ã����������Ч */
    u32 dwSerialId;                  /* serialͬ���ӿڱ�ţ�e1��·��16��ʼ����Ч��Χ16~62,���ɳ�ͻ */
    u32 dwE1Id;                      /* ��serialͬ���ӿڶ�Ӧ��e1��ţ������÷�Χ0~E1_MAXNUM-1, E1_MAXNUMȡ������ӦӲ��֧�ֵ�e1����,��kdv8010�ն� #define BRD_MT_E1_MAXNUM 4 */
    u32 dwE1TSMask;                  /* E1ʱ϶����˵��,����� */
    u32 dwE1ChanGroupId;             /* E1ʱ϶�������ڵı���ţ������÷�Χ0~7,��������һ��E1ʹ�õĻ���0�������ֵĻ������ÿ��ʱ϶�ν������α�� */
    u32 dwProtocolType;		/* �ӿ�Э���װ����,����ǵ�E1���ӿ���ָ��PPP/HDLC������Ƕ�E1�������ӱ�����PPPЭ�� */
    u32 dwEchoInterval;		/* ��Ӧserialͬ���ӿڵ�echo����ʱ��������Ϊ��λ����Ч��Χ0-256����Ĭ��ֵ2���� */
    u32 dwEchoMaxRetry;		/* ��Ӧserialͬ���ӿڵ�echo����ط���������Ч��Χ0-256����Ĭ��ֵ5���� */
}TNetE1SerialInfo;
/******************************************************************************
* dwE1TSMaskʱ϶���䲹��˵����
*    ʱ����������룬��Ts31 Ts30...Ts0����32λ���룬TSxΪ1ʱ��ʾʹ�ø�ʱ϶��Ϊ0ʱ��ʹ��
* Ts0��Ϊͬ���źţ��û�����ʹ��, 0x0��0x1���ǷǷ��Ĳ�������Ч��Χ��0x2~0xfffffffe��
* ��: ʹ��TS1~TS5 5��ʱ϶ʱdwE1TSMask = 0x0000003e,ע��:Ts0=0; ��ʱ����= 64x5 = 320kbit
      ʹ��TS1~TS3,TS30~31 5��ʱ϶ʱdwE1TSMask = 0xc000000e,ע��:Ts0=0; ��ʱ����= 64x5 = 320kbit
******************************************************************************/

/* ��E1��·����ͨ�������ṹ */
typedef struct{
    u32 dwUsedFlag;                  /* ��ǰE1����·����ͨ��ʹ�ñ�־,��1ʹ�ã����������Ч��0��ʹ�ã����������Ч */
    u32 dwIpAdrs;                    /* ip��ַ�������� */
    u32 dwIpMask;                    /* ���룬������ */
    TNetE1SerialInfo tE1SerialInfo;     /* ��Ӧserialͬ���ӿ���·���� */
}TNetE1SingleLinkChanInfo;

/* ��E1��·��������ͨ�������ṹ */
typedef struct{
    u32 dwUsedFlag;                      /* ��ǰE1����·��������ͨ��ʹ�ñ�־,��1ʹ�ã����������Ч��0��ʹ�ã����������Ч */
    u32 dwIpAdrs;                        /* ip��ַ�������� */
    u32 dwIpMask;                        /* ���룬������ */
    u32 dwAuthenticationType;            /* PPP���ӵ���֤����PAP/CHAP,Ĭ����MP_AUTHENTICATION_PAP */
    u32 dwFragMinPackageLen;             /* ��С��Ƭ�������ֽ�Ϊ��λ����Χ20~1500��Ĭ����20 */
    char  chSvrUsrName[MP_STRING_MAX_LEN]; /* ������û����ƣ�������֤�Զ˵����� */
    char  chSvrUsrPwd[MP_STRING_MAX_LEN];  /* ������û����룬������֤�Զ˵����� */
    char  chSentUsrName[MP_STRING_MAX_LEN];/* �ͻ����û����ƣ��������Զ���֤ */
    char  chSentUsrPwd[MP_STRING_MAX_LEN]; /* �ͻ����û����룬�������Զ���֤ */
    TNetE1SerialInfo tE1SerialInfo[E1_SINGLE_LINK_CHAN_MAX_NUM];/* ÿ���������serialͬ���ӿ���·���� */
}TNetE1MultiLinkChanInfo;

/*================================
��������BrdGetE1Bandwidth
���ܣ���ȡָ��E1�ӿڴ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�������
�������˵����ifname: ָ���ӿ����� ifunit:ָ���ӿں�
����ֵ˵���� �ɹ�:dwBandWidth/ʧ��:0
==================================*/
u32 NetGetE1Bandwidth(char *ifname , int ifunit);

/*================================
��������BrdSetE1Clock
���ܣ����dce����dte
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����e1ΪE1�ӿں�
              clockΪ("dce"��"dte")
����ֵ˵���� ���󷵻�ERROR���ɹ�, ����OK
==================================*/
s32 NetSetE1Clock(int e1,char *clock);

/*================================
��������BrdOpenE1SingleLinkChan
���ܣ�����һ��E1����·����ͨ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwChanID: ����·����ͨ���ţ���Χ0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1����ID����Ψһ�ԣ�������ʶÿ������·����ͨ�������ɳ�ͻ��һ��ͨ�������ظ��򿪣������ȹر�
              ptChanParam:����·����ͨ�������ṹָ��
����ֵ˵���� E1_RETURN_OK/ERRCODE
==================================*/
s32 NetOpenE1SingleLinkChan(u32 dwChanID, TNetE1SingleLinkChanInfo *ptChanParam);

/*====================================================================
������      : BrdCloseE1SingleLinkChan
����        ���ر�ָ����E1����·����ͨ��
�㷨ʵ��    ����
����ȫ�ֱ�������
�������˵����dwChanID: ����·����ͨ���ţ���Χ0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1��
            ��ID����Ψһ�ԣ�������ʶÿ������·����ͨ�������ɳ�ͻ��
            ��ͨ���������Ѿ��򿪳ɹ��ģ����δ���򷵻�E1_ERR_CHAN_NOT_CONF;
����ֵ˵��  ��E1_RETURN_OK/ERRCODE��
====================================================================*/
s32 NetCloseE1SingleLinkChan(u32 dwChanID);

/*====================================================================
������      : BrdOpenE1MultiLinkChan
����        ������һ��E1����·��������ͨ��
�㷨ʵ��    ������·�����ṩ��nipģ��Ľӿڡ�
����ȫ�ֱ�������
�������˵����dwChanID: ����·��������ͨ���ţ���Χ0~ dwMultiLinkChanNum -1��
            ��ID����Ψһ�ԣ�������ʶÿ������·����ͨ�������ɳ�ͻ��һ��ͨ�������ظ��򿪣�
            �����ȹر�;
             ptChanParam:����·��������ͨ�������ṹָ��.
����ֵ˵��  ��E1_RETURN_OK/ERRCODE��
====================================================================*/
s32 NetOpenE1MultiLinkChan(u32 dwChanID, TNetE1MultiLinkChanInfo *ptMpParam);

/*====================================================================
������      : BrdCloseE1MultiLinkChan
����        ���ر�ָ����E1����·��������ͨ��
�㷨ʵ��    ����
����ȫ�ֱ�������
�������˵����dwChanID: ����·��������ͨ���ţ���Χ0~ dwMultiLinkChanNum -1��
            ��ID����Ψһ�ԣ�������ʶÿ������·��������ͨ�������ɳ�ͻ��
            ��ͨ���������Ѿ��򿪳ɹ��ģ����δ���򷵻�E1_ERR_CHAN_NOT_CONF;
����ֵ˵��  ��E1_RETURN_OK/ERRCODE��
====================================================================*/
s32 NetCloseE1MultiLinkChan(u32 dwChanID);

/*================================
��������NetGetE1Remoteip
���ܣ���ȡָ��E1�ӿ�Զ��ip
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�������
�������˵����ifname: ָ���ӿ����� ifunit:ָ���ӿں�
����ֵ˵���� ���󷵻�ERROR���ɹ�, ����OK
==================================*/
u32 NetGetE1Remoteip(char *ifname , int ifunit);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */
#endif
