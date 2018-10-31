

#ifndef _h_tpmsg_h__
#define _h_tpmsg_h__

#include "osp.h"
#include "tpsys.h"


const int   KDV_MAXLEN_MESSAGE       =   65532; //1024*64,  ��Ϣ��󳤶�64K  

#define node_ui    0x001
#define node_mtc   0x002
#define node_peer  0x004  
#define node_pcdualvideo 0x008
#define node_batchconfig 0x010 
#define node_mtautotest  0x012
#define node_agent		 0x040  
#define node_cns		 0x080     


namespace UmsTpmsg {

u8 kdvGetLocalHashType();
u8 kdvGetRemoteHashType();
void kdvSetLocalHashType( u8 byType );
void kdvSetRemoteHashType( u8 byType );

char* GetEventNamebyID( u32 wEvent );

struct TTpMsg
{
protected:
	u16 m_wEvent;
	u16 m_wBodyLen;
	u32 m_dwSrcIId;
	u32 m_dwSrcNode;

	u8  m_abyMsg[KDV_MAXLEN_MESSAGE+4];
	s32 m_nXMLIndex;

	TTpMsg()
	{
		memset(this,0,sizeof(TTpMsg));
		m_nXMLIndex = -1;
	}
};

class CTpMsg : public TTpMsg
{
protected:
	enum EmMsgCodeIndex
	{
		CODEC_FLAG        = 0, //���ֽ� = 0��ʾδ���� = 1��ʾ�������� = 2��ʾxml����
		CODEC_HOMEPLACE   = 1,
		CODEC_User        = 2,
		CODEC_RESERVER3   = 3,
		CODEC_BODY		  = 4,

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE         = 0,
		CODEC_XML_MARSHAL = 2,//���ݾɵ��ն�xml����2��ʼ
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData     = 0 ,//δ��������ԭʼ����
		emCodeData         //������������
	};
		//   ���¼�����Ϊ  wEvent �� buf�����ݽ���ΪCMtMsg
	BOOL Decode(u16 wEvent ,u8* buf ,int len);
	//��Ϣ�Ƿ񾭹�����
	u8 IsMsgCoder()
	{
		return m_abyMsg[0];
	}

public:
	CTpMsg(){};
	CTpMsg(const CMessage* ptMsg )
	{
		m_dwSrcIId  = ptMsg->srcid;
		m_dwSrcNode = ptMsg->srcnode;
		Decode(ptMsg->event ,(u8*)ptMsg->content ,ptMsg->length );
	}

	CTpMsg(u16 wEvent ,void* buf ,int len )
	{
		Decode( wEvent ,(u8*)buf ,len );
	}
	

	//������Ϣ
	int Post(u32 dstid,
		     u32 dstnode =0,	
			 u32 srciid  = MAKEIID(INVALID_APP, INVALID_INS), 
			 u32 srcnode = INVALID_NODE );


	//�����Ϣ��ָ��
	u8*	GetBody(){	return m_abyMsg+CODEC_BODY;}
	
	//�����Ϣ�峤��
	u16	GetBodyLen() {	return m_wBodyLen; 	}

	//�����Ϣָ��
	u8*	GetMsg(){	return m_abyMsg;}
	
	//�����Ϣ����
	u16	GetMsgLen() {	return m_wBodyLen+4; 	}

	//������Ϣ������
	BOOL SetBody(const void* buf ,u16 len )
	{ 
		if( len > (u16)(KDV_MAXLEN_MESSAGE) )
			return FALSE;
		if( NULL == buf || 0 == len )
		{
			m_wBodyLen = 0;
			return TRUE;
		}
		memcpy(m_abyMsg+CODEC_BODY ,buf ,len);
		m_wBodyLen = len;
		return TRUE;
	}

	//�����Ϣ������
	BOOL CatBody(const void* buf ,u16 len )
	{
		if( len + m_wBodyLen > (u16)(KDV_MAXLEN_MESSAGE) )
			return FALSE;

		memcpy( m_abyMsg +CODEC_BODY +m_wBodyLen ,buf ,len);
		m_wBodyLen += len;
		return TRUE;

	}

	void SetEvent(u16 event ) { m_wEvent = event ;}
	u16  GetEvent() { return m_wEvent; }


	u32 GetSrcIId(){ return m_dwSrcIId; }
	u32 GetSrcNode(){ return m_dwSrcNode; }

	//��ȡ��Ϣ�ķ�����
	u8   GetHomeplace()
	{
		return m_abyMsg[CODEC_HOMEPLACE];
	}

	void SetHomeplace( u8 byNode )
	{
		m_abyMsg[CODEC_HOMEPLACE] = byNode;
	}

	u8   GetUserData()
	{
		return m_abyMsg[CODEC_User];
	}

	void   SetUserData(u8 byData)
	{
		m_abyMsg[CODEC_User] = byData;
	}
	
	u8   GetUserData2()
	{
		return m_abyMsg[CODEC_RESERVER3];
	}
	
	void   SetUserData2(u8 byData)
	{
		m_abyMsg[CODEC_RESERVER3] = byData;
	}
protected:
    void  DisplayMsgStream(u32 srcid , u32 dstid);
};


} //namespace UmsTpmsg


#endif//!_h_tpmsg_h__
