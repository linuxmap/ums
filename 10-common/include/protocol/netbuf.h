

/*****************************************************************************
ģ����      : NetBuf
�ļ���      : NetBuf.h
����ļ�    : NetBuf.cpp
�ļ�ʵ�ֹ���: CNetBuf Class Define
����        : ����
�汾        : V2.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/03/26  3.0         ����      Create
******************************************************************************/


#ifndef _NETBUF_0601_H_
#define _NETBUF_0601_H_



//ģ��汾��Ϣ�ͱ���ʱ�� �� �����Ŀ�İ汾�ͱ���ʱ��
API void netbufver();


//ģ�������Ϣ �� �����Ŀ�İ�����Ϣ
API void netbufhelp();



#define  NB_NO_ERROR             (u16)0		//NetBuf������ɹ� 
#define  NBERR_BASE_CODE         (u16)22000	//�������׼ֵ

//û�г�ʼ��nb��
#define  NBERR_NOT_INIT_LIB      (u16)(NBERR_BASE_CODE + 1)
//û���ͷ�nb��
#define  NBERR_NOT_RELEASE_LIB   (u16)(NBERR_BASE_CODE + 2)
//�ڴ�������
#define  NBERR_OUTOFMEMORY       (u16)(NBERR_BASE_CODE + 3)

//NetBuf����û�е���CreateNetBuf()
#define  NBERR_NB_NOCREATE       (u16)(NBERR_BASE_CODE+11) 
//CSrcLinker����δ����
#define  NBERR_SL_NOCREATE       (u16)(NBERR_BASE_CODE+12) 
//CDstLinker����δ����
#define  NBERR_DL_NOCREATE       (u16)(NBERR_BASE_CODE+13) 

#define  NBERR_LOOP_BUF_PARAM    (u16)(NBERR_BASE_CODE+21) //���û�״�����������
#define  NBERR_LOOP_BUF_NULL     (u16)(NBERR_BASE_CODE+22) //��״�������Ч���ݿ�
#define  NBERR_LOOP_BUF_FULL     (u16)(NBERR_BASE_CODE+23) //��״�������Ч������ 
#define  NBERR_LOOP_BUF_NOCREATE (u16)(NBERR_BASE_CODE+24) //��״�������û�д���
#define  NBERR_LOOP_BUF_SIZE     (u16)(NBERR_BASE_CODE+25) //��״�����е����ݵ�Ԫ��Ч���ȳ���
#define  NBERR_LOOP_BUF_MEMORY   (u16)(NBERR_BASE_CODE+26) //��״�����е��ڴ��������


#define  NBERR_ADD_CHANNEL_EXIST  (u16)(NBERR_BASE_CODE+31) //ָ�����ӵĽ���ͨ���Ѵ���
#define  NBERR_ADD_CHANNEL_FULL   (u16)(NBERR_BASE_CODE+32) //����ͨ������
#define  NBERR_ADD_CHANNEL_MEMORY (u16)(NBERR_BASE_CODE+33) //����ͨ�������ڴ����ʧ��
#define  NBERR_REMOVE_CHANNEL     (u16)(NBERR_BASE_CODE+34) //�Ƴ�һ·����ͨ�� ����ʧ��


#define  ERROR_SL_RTP_CREATE_SOCK  (u16)(NBERR_BASE_CODE+41) //����Դ��ͨѶ�� ����rtp socket ����ʧ��
#define  ERROR_SL_RTCP_CREATE_SOCK (u16)(NBERR_BASE_CODE+42) //����Դ��ͨѶ�� ����rtcp socket ����ʧ��
#define  ERROR_DL_RTP_CREATE_SOCK  (u16)(NBERR_BASE_CODE+43) //����Դ��ͨѶ�� ����rtp socket ����ʧ��
#define  ERROR_DL_RTCP_CREATE_SOCK (u16)(NBERR_BASE_CODE+44) //����Դ��ͨѶ�� ����rtcp socket ����ʧ��


#define  NBERR_WSA_STARTUP       (u16)(NBERR_BASE_CODE+100) //wsastartup error
#define  NBERR_CREATE_SEMAPORE   (u16)(NBERR_BASE_CODE+101) //create semapore error
#define  NBERR_SOCKET_CALL       (u16)(NBERR_BASE_CODE+102) //����socket() ��������
#define  NBERR_BIND_SOCKET       (u16)(NBERR_BASE_CODE+103) //socket �󶨳���
#define  NBERR_CREATE_THREAD     (u16)(NBERR_BASE_CODE+104) //�����̳߳��� 

//----------------------------------------------------------------------

//�������

typedef struct tagNetAddr
{
	u32   m_dwIP;		//����ip  (������)
	u16   m_wPort;		//����port(������)
}TNetAddr;

typedef struct tagNetLocalAddr
{
	TNetAddr    m_tLocalAddr;
	TNetAddr    m_tRtcpBackAddr;	//Զ��RTCP������Ϣ�Ľ��յ�ַ
}TNetLocalAddr;

typedef struct tagNetFeedbackAddr
{
	TNetAddr    m_tLocalAddr;
	TNetAddr    m_tRtpRemoteAddr;	//Զ��RTP���Ľ��յ�ַ
}TNetFeedbackAddr;


typedef struct tagRSParam
{
    u16  m_wFirstTimeSpan;	 //��һ���ش�����(ms)
	u16  m_wSecondTimeSpan;  //�ڶ����ش�����(ms)
	u16  m_wThirdTimeSpan;   //�������ش�����(ms)
	u16  m_wRejectTimeSpan;  //���ڶ�����ʱ����(ms)
} TRSParam;

/*=============================================================================
������		nbInit
����		��ʼ�� �����ط����� ��,����֮һ�� �ⲿʹ��
�㷨ʵ��	������ѡ�
�������˵����
����ֵ˵���� �ɹ�����FE_OK,  ʧ�ܷ��ش�����
=============================================================================*/
u16 nbInit();


/*=============================================================================
������		nbRelease
����		���� �����ط����� ��,�������ò�������,ֱ���ͷſ⣬����֮һ�� �ⲿʹ��
�㷨ʵ��	������ѡ�
�������˵������
����ֵ˵���� �ɹ�����FE_OK,  ʧ�ܷ��ش�����
=============================================================================*/
u16 nbRelease();


//----------------------------------------------------------------------

class CLinkerObj;

class CNetBuf
{
public:
    CNetBuf();
    ~CNetBuf();

public:
	//��
	u16 CreateNetBuf( TRSParam tRSParam, u16 wSndPort );
	//�ر�
	u16 FreeNetBuf();
	
	//�����뷢�Ͷ��໥�����Ľ��յ�ַ�����ظ����ã����ú��µ�ַȡ���ɵ�ַ, ����NULL������ײ��׽���
	//���ڽ��ա����淢�Ͷ˵�rtp������Ⲣ����rtcp�ش������
	u16 SetLocalAddr( TNetLocalAddr *ptLocalAddr );

	//��������ն��໥�����Ľ��յ�ַ�����ظ����ã����ú��µ�ַȡ���ɵ�ַ, ����NULL������ײ��׽���
	//���ڽ��ս��ն˵�rtcp�ش�����������������󷢳���Ӧrtp��
	u16 SetChannelLocalAddr( TNetAddr *ptChannelLocalAddr );

private:
	CLinkerObj  *m_pcLinkerObj;
	void        *m_hSynSem;     //���ڶ���ĵ��̲߳�����ͬ����
};

//----------------------------------------------------------------------


#endif /////__NETBUF_0601_H_
