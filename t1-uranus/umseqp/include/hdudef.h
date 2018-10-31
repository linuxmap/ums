//HDU ��ز�������

#ifndef  _hdu_def_h__
#define	 _hdu_def_h__
#include "mcudef.h"

//HDU ����״̬
enum EmRunState
{
	emhduidle,
	emhduMonitorIng,
	emhduMonitored,
};

#define     HDU_OUTPUTMODE_NONE               0   //�����ģʽ
#define     HDU_OUTPUTMODE_AUDIO              1   //��Ƶ���ģʽ
#define     HDU_OUTPUTMODE_VIDEO              2   //��Ƶ���ģʽ
#define     HDU_OUTPUTMODE_BOTH               3   //����Ƶ���ģʽ

//  [1/8/2010 pengjie] Modify
// HDU �ӻ������ʱ��ʾģʽ
// HDU����ͨ����ʾΪ��ɫ
#define HDU_SHOW_BLACK_MODE           0
// HDU����ͨ����ʾ���һ֡
#define HDU_SHOW_LASTFRAME_MODE       1 
// HDU����ͨ����ʾĬ��ͼƬ��1280*720
#define HDU_SHOW_DEFPIC_MODE          2
// HDU����ͨ����ʾ�û��Զ���ͼƬ
#define HDU_SHOW_USERDEFPIC_MODE      3

//HDUҵ����Ϣ
const u16    EV_UMS_HDU_BGN = 26441;
OSPEVENT( UMS_HDU_REG_REQ,			    EV_UMS_HDU_BGN );		//ҵ��ע��
OSPEVENT( UMS_HDU_REG_ACK,			    EV_UMS_HDU_BGN + 1 );	//ҵ��ע��ACK
OSPEVENT( UMS_HDU_REG_NACK,			    EV_UMS_HDU_BGN + 2 );	//ҵ��ע��NACK

//����
OSPEVENT( UMS_HDU_START_PLAY_REQ,		EV_UMS_HDU_BGN + 3);	//��������
OSPEVENT( UMS_HDU_PLAY_ACK,				EV_UMS_HDU_BGN + 4);
OSPEVENT( UMS_HDU_PLAY_NACK,			EV_UMS_HDU_BGN + 5);

//ͨ��ֹͣ����
OSPEVENT( UMS_HDU_STOP_PLAY_REQ,		EV_UMS_HDU_BGN + 6 );
OSPEVENT( UMS_HDU_STOP_PLAY_ACK,		EV_UMS_HDU_BGN + 7 );
OSPEVENT( UMS_HDU_STOP_PLAY_NACK,		EV_UMS_HDU_BGN + 8 );

//��������״̬
OSPEVENT( UMS_HDU_GETSTATUS_REQ,		    EV_UMS_HDU_BGN + 9 );  // hdu2������
OSPEVENT( HDU_UMS_GETSTATUS_ACK,		    EV_UMS_HDU_BGN + 10 ); // hdu2������
OSPEVENT( HDU_UMS_GETSTATUS_NACK,		    EV_UMS_HDU_BGN + 11 ); // hdu2������
OSPEVENT( HDU_UMS_STATUS_NOTIF,			    EV_UMS_HDU_BGN + 12 );

//--------����ؼ�֡-------
OSPEVENT( HDU_UMS_NEEDIFRAME_CMD,		    EV_UMS_HDU_BGN + 13 );
//--------��������---------
//��Ϣ�壺FIXME���漰chnlid,vol
OSPEVENT( UMS_HDU_SETCHNNLVOL_CMD,			EV_UMS_HDU_BGN + 14 ); // hdu2������
//ĳͨ������֪ͨ��Ϣ
OSPEVENT( HDU_UMS_CHNNLVOL_NOTIF,			EV_UMS_HDU_BGN + 15 ); // hdu2������
//ͨ��״̬֪ͨ
OSPEVENT( HDU_UMS_CHNNLSTATUS_NOTIF,		EV_UMS_HDU_BGN + 16 ); // 

//�ı����������ʽ����ʾ����֪ͨ
OSPEVENT( UMS_HDU_CHANGEMODEPORT_NOTIF,		EV_UMS_HDU_BGN + 17 ); 

// ����������С����
OSPEVENT( UMS_HDU_CHANGEVOLUME_CMD,		    EV_UMS_HDU_BGN + 19 ); 

// ���ģʽ
OSPEVENT( UMS_HDU_CHANGEMODE_CMD,		    EV_UMS_HDU_BGN + 20 ); // hdu2������

//ͨ��������ʾ���Ա��
OSPEVENT( UMS_HDU_CHANGEPLAYPOLICY_NOTIF,   EV_UMS_HDU_BGN + 21 ); 

//HDUͨ��ģʽ�л�(�໭���ͨ��)
OSPEVENT( UMS_HDU_CHGHDUVMPMODE_REQ,		EV_UMS_HDU_BGN + 22 ); // hdu2֧�֣�umsδ����
OSPEVENT( HDU_UMS_CHGHDUVMPMODE_ACK,		EV_UMS_HDU_BGN + 23 ); // hdu2֧�֣�umsδ����
OSPEVENT( HDU_UMS_CHGHDUVMPMODE_NACK,		EV_UMS_HDU_BGN + 24 ); // hdu2֧�֣�umsδ����

//ˢ����Ƶ�غ�
OSPEVENT( UMS_HDU_FRESHAUDIO_PAYLOAD_CMD, 	EV_UMS_HDU_BGN + 25 );  // hdu2֧�֣�umsδ����

//֪ͨ����ǽ������Կ ����
OSPEVENT(UMS_HDU_MEDIAKEY_NTY,              EV_UMS_HDU_BGN + 30 );

const u16	 EV_UMS_HDU_END	= UMS_HDU_MEDIAKEY_NTY;	//HDUҵ����Ϣ��������������һ������ֵ���

#define		QT_MAX_MEDIAKEY_LEN		1024
struct TQTMediaKeyInfo
{
	u32		m_dwChnlNo;
	u32		m_dwHandle;
	u16		m_wIndex;
	s8      m_szAlias[TP_MAX_ALIAS_LEN + 1];
	u8		m_szMediaKey1[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey2[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey3[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey4[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u32     m_dwKeyLen;//������Կʵ�ʳ���
	u32		m_dwKeyFrequency;//(0:һ��һ��; 1:һ��һ��; 2:һ��һ��)
	u32		m_dwQtFlag;
	
	TQTMediaKeyInfo()
	{
		memset(this, 0, sizeof(TQTMediaKeyInfo));
	}
	
	void clear()
	{
		memset(this, 0, sizeof(struct TQTMediaKeyInfo));
		m_dwHandle = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX ;
		m_dwKeyLen = 0;
		m_dwKeyFrequency = 2;//2:һ��һ��
		m_dwQtFlag = 0;
		m_dwChnlNo = 0;
	}
	
	void SetChnlNo(u32 dwChnlNo) { m_dwChnlNo = htonl(dwChnlNo); }
	u32 GetChnlNo(){ return ntohl(m_dwChnlNo); }
	
	void SetHandle(u32 dwHandle) { m_dwHandle = htonl(dwHandle); }
	u32 GetHandle(){ return ntohl(m_dwHandle); }
	
	void SetIndex(u16 wIndex) { m_wIndex = htons(wIndex); }
	u16 GetIndex(){ return ntohs(m_wIndex); }
	
	void SetKeyLen(u32 dwLen) { m_dwKeyLen = htonl(dwLen); }
	u32 GetKeyLen(){ return ntohl(m_dwKeyLen); }
	
	void SetKeyFrequency(u32 dwFreq) { m_dwKeyFrequency = htonl(dwFreq); }
	u32 GetKeyFrequency(){ return ntohl(m_dwKeyFrequency); }
	
	void SetQtFlag(u32 dwFlag) { m_dwQtFlag = htonl(dwFlag); }
	u32 GetQtFlag(){ return ntohl(m_dwQtFlag); }
	
	void GetAlias(s8* pszBuf, u16 wLen) 
	{
		memcpy(pszBuf, m_szAlias, min( TP_MAX_ALIAS_LEN, wLen)); 
	}
	
	void GetKey(u8* pszBuf, u16 wLen)
	{
		if ( wLen < QT_MAX_MEDIAKEY_LEN )
		{
			return ;
		}
		memcpy(pszBuf, m_szMediaKey1, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + QT_MAX_MEDIAKEY_LEN/4, m_szMediaKey2, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + QT_MAX_MEDIAKEY_LEN/2, m_szMediaKey3, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + 3*QT_MAX_MEDIAKEY_LEN/4, m_szMediaKey4, QT_MAX_MEDIAKEY_LEN/4);
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

struct TEqpHduCfgInfo : public TEqpCfgInfo 
{
protected:
	
    THduChnlModePort atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	u8	m_byStartMode;//����ģʽ��(0: hdu_2 1:hdu_1 2:hdu_L )
public:
	TEqpHduCfgInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
		SetStartMode(STARTMODE_HDU_M);
	}

	void SetStartMode(u8 byStartMode){m_byStartMode = byStartMode; }
	u8   GetStartMode(){ return m_byStartMode; }

	void GetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			tHduChnModePort.SetOutModeType( atHduChnlModePort[byNum].GetOutModeType() );
			tHduChnModePort.SetOutPortType( atHduChnlModePort[byNum].GetOutPortType() );
		    tHduChnModePort.SetZoomRate( atHduChnlModePort[byNum].GetZoomRate() );
			tHduChnModePort.SetScalingMode( atHduChnlModePort[byNum].GetScalingMode() );
		}
		else
		{
			return;			
		}
		
		return;
	}
	
    void SetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			atHduChnlModePort[byNum].SetOutModeType( tHduChnModePort.GetOutModeType() );
			atHduChnlModePort[byNum].SetOutPortType( tHduChnModePort.GetOutPortType() );
            atHduChnlModePort[byNum].SetZoomRate( tHduChnModePort.GetZoomRate() );
			atHduChnlModePort[byNum].SetScalingMode(tHduChnModePort.GetScalingMode());
		}
		else
		{
			return;	
		}
		
		return;
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

#endif