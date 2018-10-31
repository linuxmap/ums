/*****************************************************************************
ģ����      : DCMT�ؼ�
�ļ���      : DCMTDefine.h
����ļ�    : 
�ļ�ʵ�ֹ���:  ����DCMTOcx�ؼ�Ҫ�õĳ���,��,��Ϣ��,�ṹ��
����        : �º�� ��С��
�汾        : V3.0  Copyright(C) 2004-2005 KDC, All rights reserved.

-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/12/21  3.0         �º��      ����
******************************************************************************/

#ifndef DCMTDEFINE_H
#define DCMTDEFINE_H 

//�����л�֪ͨ��Ϣ(��Ϣ��: �л�ǰ����������, ����)
#define WM_SWITCH_LANGUAGE         WM_USER + 11

//����������� (��Ϣ��: ���������ն����� CString* , �����ն˱�ʾ long )
#define WM_INVITE_REQUEST          WM_USER + 400
//����������� (��Ϣ��: ���������ն����� CString* , �����ն˱�ʾ long)
#define WM_JOIN_REQUEST            WM_USER + 401  
//�������ȡ�� (����Ϣ��)
#define WM_INVITE_REQUEST_CANCEL   WM_USER + 402
//��������һ���ն� (��Ϣ��: �ն���Ϣ TDcMtInfo*, ����)
#define WM_CONF_ADD_ONE_MT          WM_USER + 403
//����ɾ��һ���ն� (��Ϣ��: �ն�ID int, ����)
#define WM_CONF_REMOVE_ONE_MT       WM_USER + 404
//��������ɹ� (��Ϣ��: �Ƿ񱾵ش����Ļ������ BOOL, ����)
#define WM_CONF_CREATE_SUCCESS      WM_USER + 405
//������� (����Ϣ��)
#define WM_CONF_TERMINATE           WM_USER + 406
//�Ҷϻ��� (����Ϣ��)
#define WM_CONF_HANGUP              WM_USER + 407
//֪ͨ���鲻�ܷ����Ӧ��(��Ϣ��: ���ܷ���Ӧ�õı�ʾ enum, ����)
#define WM_CONF_APP_DISABLE         WM_USER + 408

//���������������ɹ� (����Ϣ��)
#define WM_CAPABILITY_NEGOTIATION_SUCCESS       WM_USER + 410

//���������ն�֪ͨ (��Ϣ��: �μ������ն����� int, �����ն����� TDcMtInfo*)
#define WM_CHAT_MT_UPDATE   WM_USER + 412

//�����ն���Ӧ (��Ϣ��: �Ƿ�����ɹ� BOOL, ����)
#define WM_INVITE_MT_RSP            WM_USER + 500
//���������Ӧ (��Ϣ��: �Ƿ����ɹ� BOOL, ����)
#define WM_JOIN_CONF_RSP            WM_USER + 501
//�������������� (��Ϣ��: �������� CString* , ����)
#define WM_JOIN_CONF_PASSWORD_ERROR WM_USER + 502
//����ʧ�ܣ�˫�����ڻ����� (����Ϣ��)
#define WM_CALL_OUT_FAILED    WM_USER + 503
#define WM_CALL_BOTH_IN_CONF  WM_CALL_OUT_FAILED

//���У��Է��ж��������� (��Ϣ��: ������������б� CStringList* , �������Ƹ���)
#define WM_CALL_OUT_MORE_THAN_ONE_CONF   WM_USER + 504

//�������湲�� (��Ϣ��: ����������ID int , ����)
#define WM_START_DESKTOP_SHARE      WM_USER + 600
//����Ӧ�ù��� (��Ϣ��: ����������ID int , ����)
#define WM_START_APP_SHARE          WM_USER + 601
//ֹͣ���� (��Ϣ��: ����������ID int , ����)
#define WM_STOP_APP_SHARE           WM_USER + 602

//���´����б� (����Ϣ��)
#define WM_UPDATE_WINDOW_LIST       WM_USER + 610
//����Զ�̿���Ȩ�ظ� (��Ϣ��: Զ�̿������� WORD , �Ƿ�õ�����Ȩ�ޣ����߾ܾ���ԭ�� RcConfirmType)
#define WM_CONFIRM_REMOTE_CONTROL   WM_USER + 611
//�����ն˻��Զ�̿���Ȩ (��Ϣ��: ������ID int , ����)
#define WM_OTHER_REMOTE_CONTROL     WM_USER + 612

//���������״,����Ϣֻ�����ڿ��������ն˵Ĺ�������ʱ��
//(����Ϣ��)
#define WM_UPDATE_CURSOR_SHAPE      WM_USER + 615
//�����ն�������Զ�̿���Ȩ (����Ϣ��)
#define WM_REQUEST_REMOTE_CONTRL    WM_USER + 620
//�����ն��ͷ�Զ�̿���Ȩ (����Ϣ��)
#define WM_RELEASE_REMOTE_CONTRL    WM_USER + 621
//�յ�Զ�̿��Ʊ��ش��ڻָ�� (��Ϣ��: �������߷ǹ������ڵ�ID int , ����)
#define WM_RC_RECEIVE_ACTIVE_WINDOW WM_USER + 630
//�յ�Զ�̿��Ʊ��ش��ڼ��� (��Ϣ��: �����ڵ�ID int , ����)
#define WM_RC_ACTIVE_WINDOW         WM_USER + 640
//�л���ʾ������
#define WM_SWITH_SHOW_SHARE_WINDOW         WM_USER + 641

//�յ�������Ϣ (��Ϣ��: ������Ϣ�ṹ TChatReceiveInfo* , ����)
#define WM_RECEIVE_CHAT_PUBLIC_TEXT        WM_USER + 650
//�յ�˽����Ϣ (��Ϣ��: ������Ϣ�ṹ TChatReceiveInfo* , ����)
#define WM_RECEIVE_CHAT_PRIVATE_TEXT WM_USER + 651
//�����ն���������Ӧ�õ�֪ͨ (��Ϣ��: ���������ն�ID int , ����)
#define WM_OTHER_START_CHAT         WM_USER + 660
//�����ն������ļ�����Ӧ�õ�֪ͨ (��Ϣ��: �����ļ������ն�ID int , ����)
#define WM_OTHER_START_MBFT         WM_USER + 661
//�����ն������װ�Ӧ�õ�֪ͨ (��Ϣ��: �����װ��ն�ID int , ����)
#define WM_OTHER_START_SI         WM_USER + 662

//ö�����洰�� (��Ϣ��: ��ǰö�ٵĴ��� HWND , ����)
#define WM_ENUM_DESKTOP_WINDOWS			    WM_USER + 690
//ö�ٴ��� (��Ϣ��: ��ǰö�ٵĴ��� HWND , ����)
#define WM_ENUM_WINDOWS			    WM_USER + 700
//����/�˳����� (��Ϣ��: �Ƿ��ڻ����У��Ƿ������飩 BOOL , ����)
#define WM_CONF_IN_OUT              WM_USER + 701

//��ʼ�����ļ� (����Ϣ��)
#define WM_START_SEND_FILE          WM_USER + 740
//��ʼ�����ļ� (��Ϣ��: �����ļ����ն�ID int , �ļ���С int)
#define WM_START_RECEIVE_FILE       WM_USER + 750
//��ʼ�����ļ����� (��Ϣ��: �ļ����ݳ��� int , �ļ����� BYTE*)
//������͸�CDlgReceiveFile ����Ϣ��:  �ļ��Ƿ���� bool,�ļ����ݳ��� int ��
#define WM_RECEIVE_FILE_DATA        WM_USER + 751
//���յ��ļ�����
#define WM_RECEIVE_FILE_FINISH      WM_USER + 752
//�����ļ��ж�
#define WM_RECEIVE_FILE_TERMINATE   WM_USER + 753


//��ϵͳ�������
const BYTE POINTER_CACHE_SIZE = 25;
//����������ն���
const WORD MAX_CONFERENCE_MT_NUM = 192;

//������Ӧ����
typedef enum
{
    CallRspUserDecide = 0,  //�ϲ��û������Ƿ���ܺ���
    CallRspAutoAccept,      //�Զ����ܺ���
    CallRspRefuse,          //�ܾ������κκ���(�������)
}ECallRsp;

//�ն˲��ܷ����Ӧ��
typedef enum
{
    AppShareDisable = 1,    //���ܷ�����
    AppWhiteboardDisable,   //���ܷ���װ�
    AppFileTransDisable,    //���ܷ����ļ�����
    AppChatDisable          //���ܷ�������
}AppDisable;

//�ڵ�(����ָ�ն�)����
typedef enum
{
	CNPSelf,                //�ն�����
	CNPLocal,               //�����ն�
	CNPRemote               //Զ���ն�
} ConfNodePos;


//�ն���Ϣ�ṹ
struct TDcMtInfo
{
    int     nMtID;          //�ն˺�
    ConfNodePos NodePos;    //�ڵ�λ��
    CString strMtName;      //�ն�����
    CString strMtEmail;     //�ն�E-mail
    CString strMtPhone;     //�ն˵绰
    CString strMtLocation;  //�ն�λ��
    CString strFrom;        //Դ��ַ
};

//���������Ϣ�ṹ
struct TAppShareBaseData
{
	int		nShareID;               //����ID
	CString strShareName;           //�����ն�����
	WORD    wDesktopWidth;          //������������
	WORD    wDesktopHeight;         //����������߶�
};

//�������
enum EPointerType
{
    POINTER_NULL,           //û�й��
    POINTER_SYSTEM,         //ϵͳ���
    POINTER_NO_SYSTEM,      //��ϵͳ���
};

//λͼ��Ϣ�ṹ
struct TBitmapData
{
    BITMAPINFOHEADER m_BitmapInfoHeader;    //λͼ��Ϣͷ
    BYTE    m_byPalette[4*256];             //��ɫ������
    BYTE*   m_pbyBitmapData;                //λͼ����
    TBitmapData::TBitmapData()
    {
        m_BitmapInfoHeader.biSize = 0x00000028;
        m_BitmapInfoHeader.biWidth = 0x00000000;
        m_BitmapInfoHeader.biHeight = 0x00000000;
        m_BitmapInfoHeader.biPlanes = 0x0001;
        m_BitmapInfoHeader.biBitCount = 0x0000;
        m_BitmapInfoHeader.biCompression = 0x00000000;
        m_BitmapInfoHeader.biSizeImage = 0x00000000;
        m_BitmapInfoHeader.biXPelsPerMeter = 0x00000000;
        m_BitmapInfoHeader.biYPelsPerMeter = 0x00000000;
        m_BitmapInfoHeader.biClrUsed = 0x00000000;
        m_BitmapInfoHeader.biClrImportant = 0x00000000;
    
        memset( m_byPalette , 0xf8 , 4*256);
        m_pbyBitmapData = NULL;
    };

    TBitmapData::~TBitmapData()
    {
        if(m_pbyBitmapData != NULL)
        {
            delete [] m_pbyBitmapData;
            m_pbyBitmapData = NULL;
        }
    };
};


//����������Ϣ�ṹ
struct TChatReceiveInfo
{
    TChatReceiveInfo::TChatReceiveInfo()
    {
        nUserID = 0;
        nTextLen = 0;
        strText = _T("");
    };
    int nUserID;        //�ն�ID
    int nTextLen;       //������Ϣ����
    CString strText;    //������Ϣ;

};


//////////////////////////////////////////////////////////////////////////
// �����ǲ������õ��Ķ���

#define DCMT_TEST
#ifdef DCMT_TEST

#define DCMT_TEST_TELNET_PORT 2300
#define DCMT_TEST_LISTEN_PORT 2301

#define DCMT_TEST_APP_ID 235 

//��ѯ�Ƿ����
#define EV_DCMT_TEST_IS_INCONF_QUERY            EV_TEST_DCMT_BGN + 1
//��ѯ�Ƿ����������湲��
#define EV_DCMT_TEST_IS_START_DESKTOP_SHARE     EV_TEST_DCMT_BGN + 2
//��ѯ�Ƿ�������Ӧ�ó�����
#define EV_DCMT_TEST_IS_START_APP_SHARE         EV_TEST_DCMT_BGN + 3
//��ѯ�ն˽��յ��Ĺ�������
#define EV_DCMT_TEST_GET_RECEIVE_SHARE_COUNT    EV_TEST_DCMT_BGN + 4
//��һ�����չ���ID
#define EV_DCMT_TEST_GET_FIRST_RECEIVE_SHARE_ID EV_TEST_DCMT_BGN + 5
//��ѯ�Ƿ�����Զ�̿���
#define EV_DCMT_TEST_IS_ENABLE_REMOTE_CONTROL   EV_TEST_DCMT_BGN + 6
//��ȡ���ͻ�ͼ�������������Ϣ
#define EV_DCMT_TEST_GET_DRAWOBJECT_SEND        EV_TEST_DCMT_BGN + 7
//��ȡ�յ���ͼ�������������Ϣ
#define EV_DCMT_TEST_GET_DRAWOBJECT_RECEIVE     EV_TEST_DCMT_BGN + 8
//Զ���������湲��
#define EV_DCMT_TEST_START_DESKTOP_SHARE        EV_TEST_DCMT_BGN + 9
//Զ��������һ��Ӧ�ó�����
#define EV_DCMT_TEST_START_FIRST_APP_SHARE      EV_TEST_DCMT_BGN + 10
//Զ�̽������еĹ���
#define EV_DCMT_TEST_STOP_ALL_SHARE             EV_TEST_DCMT_BGN + 11
//�������
#define EV_DCMT_TEST_SET_ALLOW_REMOTE_CONTROL   EV_TEST_DCMT_BGN + 12

//��ѯ�Ƿ������˰װ�
#define EV_DCMT_TEST_IS_START_WHITEBOARD        EV_TEST_DCMT_BGN + 20
//��ȡ��ǰ��������ͼ���������Ϣ
#define EV_DCMT_TEST_GET_DRAWOBJECT_COUNT       EV_TEST_DCMT_BGN + 22
//��ѯ�װ嵱ǰ���������㻭ͼ���������
#define EV_DCMT_TEST_GET_DRAWOBJECT_TYPE_TOP    EV_TEST_DCMT_BGN + 23
//��ѯ�װ嵱ǰ�������ײ㻭ͼ���������
#define EV_DCMT_TEST_GET_DRAWOBJECT_TYPE_BOTTOM    EV_TEST_DCMT_BGN + 24
//��ѯ�װ嵱ǰ���������㻭ͼ�������ɫ
#define EV_DCMT_TEST_GET_DRAWOBJECT_COLOR_TOP    EV_TEST_DCMT_BGN + 25
//��ѯ�װ嵱ǰ���������㻭ͼ����ıʿ�
#define EV_DCMT_TEST_GET_DRAWOBJECT_PENWIDTH_TOP    EV_TEST_DCMT_BGN + 26
//��ѯ��ȡ�װ嵱ǰ���������㻭ͼ�������ʼ��(���Ͻ�����)
#define EV_DCMT_TEST_GET_DRAWOBJECT_ANCHOR_POINT_TOP    EV_TEST_DCMT_BGN + 27

//��ȡ��ǰ��������ͼѡ�ж��������Ϣ
#define EV_DCMT_TEST_GET_SELECTOBJECT_COUNT       EV_TEST_DCMT_BGN + 28
//��ѯ�װ嵱ǰ����������ѡ�л�ͼ���������
#define EV_DCMT_TEST_GET_SELECTOBJECT_TYPE_TOP    EV_TEST_DCMT_BGN + 29
//��ѯ�װ嵱ǰ����������ѡ�л�ͼ�������ɫ
#define EV_DCMT_TEST_GET_SELECTOBJECT_COLOR_TOP    EV_TEST_DCMT_BGN + 30
//��ѯ�װ嵱ǰ����������ѡ�л�ͼ����ıʿ�
#define EV_DCMT_TEST_GET_SELECTOBJECT_PENWIDTH_TOP    EV_TEST_DCMT_BGN + 31
////��ѯ�װ屾��ָʾ���Ƿ���ʾ
//#define EV_DCMT_TEST_IS_LOCAL_POINTER_SHOW    EV_TEST_DCMT_BGN + 32
//��ѯ�װ���ʾָʾ��������
#define EV_DCMT_TEST_GET_SHOW_POINTER_NUMBER    EV_TEST_DCMT_BGN + 33
//��ȡָʾ��λ����Ϣ
#define EV_DCMT_TEST_GET_POINTER_POSITION       EV_TEST_DCMT_BGN + 34

//��ȡ����������
#define EV_DCMT_TEST_GET_WORKSPACE_COUNT        EV_TEST_DCMT_BGN + 40
//��ȡ������������Ϣ
#define EV_DCMT_TEST_GET_WORKSPACE_INDEX        EV_TEST_DCMT_BGN + 41

#endif

//////////////////////////////////////////////////////////////////////////

#endif DCMTDEFINE_H
