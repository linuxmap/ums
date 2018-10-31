#ifndef MODULEMANANGER
#define MODULEMANANGER
/*******************************************************************************
*  ģ����   : �ն�ҵ��                                                        *
*  �ļ���   : modulemananger.h                                                *
*  ����ļ� :                                                                 *
*  ʵ�ֹ��� : ģ�����                                                        *
*  ����     : ����                                                            *
*  �汾     :																  *
*                                                                             *
*    =======================================================================  *
*  �޸ļ�¼:                                                                  *
*    ��  ��      �汾        �޸���      �޸�����                             *
*																			  *
*                                                                             *
 *******************************************************************************/
#include "osp.h"
#include "kdvtype.h"

#define MODULE_MSG_HEADER_LEN 4
#define MAX_MODULE_MSG_LEN 65531

#define ev_module_msg_init OSP_USEREVENT_BASE + 1
#define ev_module_msg_exit OSP_USEREVENT_BASE + 2
#define ev_module_msg_timer OSP_USEREVENT_BASE + 3

#define MAX_TITLE_LEN  32

class CModuleMsg;
class CModuleObject : public CInstance
{
public:
	CModuleObject();
	virtual ~CModuleObject();
	
	friend class CModuleHandler;
	
protected:
	BOOL32    m_bInit;//��ʼ����־
private:
    void DaemonInstanceEntry( CMessage *const pcMsg, CApp* pcApp );							//daemon��Ϣ��ں���
	void InstanceEntry( CMessage *const ptMsg );											//��Ϣ������ں���
protected:
	
	virtual void MessageProc( CModuleMsg *const ptMsg ) {};										//��Ϣ��ں������˺�����Ҫ����
	virtual void DaemonMessageProc( CModuleMsg *const ptMsg,CApp* pcApp ){}					//daemon��Ϣ��ں������˺�����Ҫ����
	
	virtual BOOL32 DaemonObjectInit( u32 wParam, u32 lParam );								//daemon��ʼ����������Ҫ����
	virtual void DaemonObjectExit( void );													//daemon�˳���������Ҫ����
	virtual BOOL32 PreDaemonMessageProc( CMessage *const ptMsg )	{ return FALSE; }		    //daemon��ϢԤ����������Ҫ����
	
protected:
	virtual BOOL32 ObjectInit( u32 wParam, u32 lParam ) = 0;									//object��ʼ����������Ҫ����
	virtual void ObjectExit( void );															//object�˳���������Ҫ����
	
	virtual BOOL32 PreMessageProc( CMessage *const ptMsg )	{ return FALSE; }			    //��ϢԤ����������Ҫ����
	
public:
	void SetLogTitle( s8* title );															//����ģ���ӡǰ׺(ģ����)

	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );

	BOOL32 NotifySelf( CModuleMsg &cMsg );
    
private:
	void*     m_plog;
	BOOL32      m_bShowMsg;
};


class CModuleMsg;
class CModuleHandler
{
protected:
	CModuleObject* m_pcInstance;
public:

	CModuleHandler( CModuleObject* pcObject ){ m_pcInstance = pcObject; }
	~CModuleHandler();

	virtual BOOL32 Handler( CModuleMsg *const ptMsg ) = 0;
	
	virtual BOOL32 Create()	{ return TRUE; }
	virtual void Destroy(){};
	void Error( s8* szFormat, ... );
	void Hint( s8* szFormat, ... );
	void LowHint( s8* szFormat, ... );

protected:

	int SetTimer( u32 nTimer, long nMilliSeconds, u32 nPara=0)
	{
		if( m_pcInstance )
			return m_pcInstance->SetTimer( nTimer ,nMilliSeconds ,nPara );
		return 0;
	};
	
	int KillTimer( u32 nTimerNo )
	{
		if( m_pcInstance )
			return m_pcInstance->KillTimer( nTimerNo );
		return 0;
	};
	
	CModuleObject*   GetInstance(){ return m_pcInstance; }
};

class CModuleMsg
{
protected:
	u16 m_wEvent;
	u16 m_wBodyLen;
	u32 m_dwSrcIId;
	u32 m_dwSrcNode;
	
	u8  *m_pbyMsg;
	s32 m_nXMLIndex;
	
protected:
	enum EmMsgCodeIndex
	{
		CODEC_FLAG			= 0,	//���ֽ� = 0, ��ʾδ����
		CODEC_HOMEPLACE		= 1,	//��ʾ��������
		CODEC_User			= 2,	//��ʾxml����
		CODEC_RESERVER3		= 3,	
		CODEC_BODY			= 4,	

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE			= 0,
		CODEC_XML_MARSHAL	= 2,//���ݾɵ��ն�xml����2��ʼ
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData			= 0 ,//δ��������ԭʼ����
		emCodeData         //������������
	};
	//��Ϣ�Ƿ񾭹�����
	u8 IsMsgCoder()
	{
		return m_pbyMsg[0];
	}

#define INVALID_SIP_XML_INDEX -1

public:
	CModuleMsg()
	{
		m_pbyMsg		= new u8[ MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN ];
        if(NULL == m_pbyMsg)
        {
            OspPrintf(TRUE, FALSE, "CModuleMsg Failed to allocate memory\n");
        }
		Clear();
	}
	CModuleMsg( const CMessage* ptMsg )
	{
        if (NULL == ptMsg)
            return;
		m_pbyMsg		= new u8[ MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN ];
		m_nXMLIndex		= INVALID_SIP_XML_INDEX;
		m_dwSrcIId		= ptMsg->srcid;
		m_dwSrcNode		= ptMsg->srcnode;
		m_wEvent		= ptMsg->event;
		m_wBodyLen		= ptMsg->length - MODULE_MSG_HEADER_LEN;
        if(NULL != m_pbyMsg)
        {
            memcpy(m_pbyMsg, ptMsg->content, ptMsg->length);
        }
	}

	~CModuleMsg()
	{
		if (m_pbyMsg)
		{
			delete[] m_pbyMsg;
			m_pbyMsg = NULL;
		}
	}

	void Clear()
	{
		//memset( this,0,sizeof(CModuleMsg) );
		m_wEvent		= 0;
		m_wBodyLen		= 0;
		m_dwSrcIId		= 0;
		m_dwSrcNode		= 0;
		if (m_pbyMsg)
			memset(m_pbyMsg, 0, MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN);
		m_nXMLIndex		= 0;
	}

	//�����Ϣ��ָ��
	u8*	GetBody(){ return m_pbyMsg+CODEC_BODY; }
	
	//�����Ϣ�峤��
	u16	GetBodyLen() { return m_wBodyLen; }

	//������Ϣ�峤��
	void SetBodyLen(u16 wLen) { m_wBodyLen = wLen; }

	//�����Ϣָ��
	u8*	GetMsg(){ return m_pbyMsg; }
	
	//�����Ϣ����
	u16	GetMsgLen() { return m_wBodyLen + MODULE_MSG_HEADER_LEN; }

	//������Ϣ������
	BOOL32 SetBody(const void* buf ,u16 len )
	{ 
		if( (len > (u16)(MAX_MODULE_MSG_LEN)) || (NULL == m_pbyMsg))
			return FALSE;
		if( NULL == buf || 0 == len )
		{
			m_wBodyLen = 0;
			return TRUE;
		}
		memcpy(m_pbyMsg + CODEC_BODY,buf ,len );
		m_wBodyLen = len;
		return TRUE;
	}

	//�����Ϣ������
	BOOL32 CatBody( const void* buf ,u16 len )
	{
		if( (len + m_wBodyLen > (u16)(MAX_MODULE_MSG_LEN)) || (NULL == m_pbyMsg))
			return FALSE;

		memcpy( m_pbyMsg +CODEC_BODY +m_wBodyLen ,buf ,len );
		m_wBodyLen += len;
		return TRUE;
	}

	void SetEvent(u16 event ) { m_wEvent = event; }
	u16  GetEvent() { return m_wEvent; }

	u32 GetSrcIId(){ return m_dwSrcIId; }
	u32 GetSrcNode(){ return m_dwSrcNode; }

	//��ȡ��Ϣ�ķ�����
	u8   GetHomeplace()
	{
		return m_pbyMsg[CODEC_HOMEPLACE];
	}

	void SetHomeplace( u8 byNode )
	{
		m_pbyMsg[CODEC_HOMEPLACE] = byNode;
	}

	u8   GetUserData()
	{
		return m_pbyMsg[CODEC_User];
	}

	void   SetUserData( u8 byData )
	{
		m_pbyMsg[CODEC_User] = byData;
	}

protected:
    void  DisplayMsgStream( u32 srcid , u32 dstid );
};

typedef struct tagMdlInitParam
{
	s8				achTitle[MAX_TITLE_LEN+1];	//ģ��title����
	u32				wParam;
	u32				lParam;						//�û��Զ���
	SEMHANDLE		hSem;
	
	tagMdlInitParam()
	{
		memset(achTitle, 0, MAX_TITLE_LEN + 1);
		wParam		= 0;
		lParam		= 0;
		hSem		= NULL;
	}
}TMDLInitParam;

#endif
