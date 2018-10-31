#ifndef QT_STRUCT_H_
#define QT_STRUCT_H_
#include "kdvtype.h"
#include <string.h>


#define QT_MT_LISTEN_PORT	6001	//�����ն˼����˿�
const u8 Auth[] = "KDVCOM";

// ��Կ����
#define QT_KEY_LEN_16 16
//��ȡ��Կ�����ĳ���
#define QT_KEY_MAX_LEN	1024
//������Կ
#define QT_MAX_MEDIA_KEY	1024

// ��֤��Ϣ����
#define KDV_AUTH_INFO_LEN 32
//��������
#define QT_ALIAS_MAX_LEN	64

//����ID���� Э����
#define QT_UNIQUE_ID_MAX_LEN	64

#define QTIN
#define QTOUT

typedef u32 QTCALLHANDLE;		//ConfId+EpId
typedef u32 QTBFCPHANDLE;		//ConfId+EpId
typedef u64 QTKEYHANDLE;		//ReqKeyFlag+SectionIndex
typedef u32	QTMediaKeyHandle;

// qt�����õ���APPID
#define APPID_QTLIB_BEGIN   60000
#define APPID_QTLIB_SEVER   APPID_QTLIB_BEGIN+1
#define APPID_QTLIB_CLIENT  APPID_QTLIB_SEVER+1

//����ԭ��
enum EmQtRetReason
{
	EmQtRetReason_Idle = 0,
	EmQtRetReason_Success,
		
	//����ԭ��
	EmQtRetReason_Local,
		
	//������δ����
	EmQtRetReason_DisConnect,
	EmQtRetReason_ShakeFail,
		
	//����ʧ��
	EmQtRetReason_ReqFail,
		
	//��ȡʧ��
	EmQtRetReason_GetFail,
		
	//�Զ���Ƶ�ն� ʧ��
	EmQtRetReason_PeerUnreach,//���ɴ�
	EmQtRetReason_PeerGetFail,//��ȡʧ��
		
	//���ʧ��
	EmQtRetReason_ClearFail,
	EmQtRetReason_TimeOut,

	//��Կ��ƥ��
	EmQtRetReason_NotMatch,

	//InitMediaKeyʧ�ܺ� ��Ҫ�ҶϺ���
	EmQtRetReason_MediaKeyFail,
	//ƽ̨���Ѵ���������Կ
	EmQtRetReason_PlatMediaKeyExist,
};

enum EmQtMTState
{
	EmQTState_Idle = 0,
	EmQTState_Shaked,
	EmQTState_Disconnect, 
};

//�������� 
enum EmQtAliasType
{
	EmQtAliasType_Alias,
	EmQtAliasType_E164,
	EmQtAliasType_H323ID,
	EmQtAliasType_Email,
	EmQtAliasType_EpID,
	EmQtAliasType_GKID,
	EmQtAliasType_PartyNumber,
	EmQtAliasType_Others,
};

enum EmQtKeyFrequency
{
	EmQtFrequencyEverySeconds,	//ÿ��һ��
	EmQtFrequencyEveryMinutes,	//ÿ����һ��
	EmQtFrequencyEveryConf,		//ÿ������һ����Կ
};

//�ص�qt��״̬
typedef void (* QtCBQtMTState)( EmQtMTState emQtMtState, void* wParam);

//�ص�������Կ���ϲ�
typedef void(*QtCBMediaKey)(u32 dwConfID, QTMediaKeyHandle hMediaHandle, s8 szAlias[QT_ALIAS_MAX_LEN+1], u8 acMediaKey[QT_MAX_MEDIA_KEY+1], u32 dwKeyLen, EmQtKeyFrequency emKeyFrequency, u32 wQtFlag, u16 wConverIndex);
typedef void(*QtCBMediaKeyDstMT)(u32 dwConfID, s8 szAlias[QT_ALIAS_MAX_LEN+1]);
//�ص�callhandle
typedef void(*QtCBCallHandle)(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType,  QTCALLHANDLE hCallHandle, u8 szCallID[QT_UNIQUE_ID_MAX_LEN+1], BOOL32 bDel);
//�ص�mediahanle
typedef void(*QtCBMediaHandle)(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType, QTMediaKeyHandle hMediaHandle);

typedef void(*QtQueryAlias)(u16 wIndex, s8 szAlias[QT_ALIAS_MAX_LEN]);

//���ܻ����лص�ʧ��ԭ����ϲ�ҵ��
typedef void (*QtCBQtRetReason)(EmQtRetReason emQtRetReason, void* wParam);

//������Կȡ��ʧ��ʱ�ص�
typedef void(*QtCBMediaKeyFail)(u32 dwPeerMtIp, s8 szLocalAlias[QT_ALIAS_MAX_LEN+1], s8 szPeerAlias[QT_ALIAS_MAX_LEN+1]);

//�ص�bfcphandle
typedef void(*QtCBBfcpHandle)(u32 dwPeerMtIp, QTBFCPHANDLE hBfcpHandle, s8 szBfcpID[QT_UNIQUE_ID_MAX_LEN+1]);

enum EmQtProtocol
{
	EmQtProtocol_H323,
	EmQtProtocol_SIP,
	EmQtProtocol_End,
};

typedef struct tagTQTQueryInfo
{
	u16		m_wIndex;
	s8		m_szAlias[QT_ALIAS_MAX_LEN+1];
	tagTQTQueryInfo()
	{
		memset(this, 0, sizeof(tagTQTQueryInfo));
	}
}TQTQueryInfo;

typedef struct tagTQtInitParam
{
	u32								m_dwQtListenIp;								//���������ն˵�ip
	u32								m_dwQtMtId;									//���������ն˵�id  ���磺340100001
	u16								m_wQtListenPort;							//�����ն˵ļ����˿�  �̶���6001
	s8								m_acAuth[KDV_AUTH_INFO_LEN+1];				//��֤��Ϣ  �̶���KDVCOM
	 
	QtCBQtMTState					m_pfCBState;								//�ص�qtmt��״̬(����)���ϲ�������Կ
	QtCBMediaKey					m_pfCBMediaKey;								//�ص�����Կ�����ɵ�������Կ
	QtCBCallHandle					m_pfCBCallHandle;							//���ж˻ص�callhandle
	QtCBMediaHandle					m_pfCBMediaHandle;							//���ж˻ص�mediahandle
	QtQueryAlias					m_pcCBQueryAlias;							//ƽ̨�����ӿ�ʹ�ã�������ѯ���б����ļ��ܵȼ�
	QtCBQtRetReason					m_pfCBRetReason;							//���ܻ����з���QT��Կ��ش���ԭ��

	BOOL32							m_bEncryption;								//�Ƿ������ܣ��ն�ʹ��
	EmQtKeyFrequency				m_emKeyFrequency;							//���ܵȼ����ն�ʹ��
	BOOL32							m_bPlatform;								//ʹ�øÿ��ҵ�����ͣ�TRUE Ϊƽ̨��FALSE Ϊ�ն�
	EmQtProtocol					m_emProtocol;
	BOOL32							m_bG400;									//ʹ�øÿ��ҵ�����ͣ�TRUEΪG400�� FALSEΪ����
	
	QtCBBfcpHandle					m_pfCbBfcpHandle;							//bfcp�ı��˻ص�bfcphandle

	tagTQtInitParam()
	{
		memset(this, 0, sizeof(tagTQtInitParam));
		m_wQtListenPort = QT_MT_LISTEN_PORT;
		memcpy(m_acAuth, Auth, strlen((s8*)Auth));
		m_bEncryption = FALSE;
		m_emProtocol = EmQtProtocol_SIP;
	}
	
}TQtInitParam;

typedef struct tagTQtCallParam
{
	EmQtKeyFrequency				m_emKeyFrequency;							//���˼��ܵȼ�
	u32								m_dwConfID;									//����ID�������ص�������Կ
	u32								m_dwPeerQtId;								//�Զ������ն�ID
	u32								m_dwPeerMtIp;								//�Զ���Ƶ�ն�IP
	EmQtAliasType					m_emAliasType;								//�Զ˱�������, G400 ʹ��
	s8								m_szLocalAlias[QT_ALIAS_MAX_LEN + 1];		//���˱�����QTLIB G400���ֱ���ipcʹ��
	s8								m_szPeerAlias[QT_ALIAS_MAX_LEN + 1];		//�Զ˱���
	BOOL32							m_bCallEncryption;							//�����Ƿ����,Э��ʹ��	
	u8								m_achUniqueId[QT_UNIQUE_ID_MAX_LEN + 1];
	tagTQtCallParam()
	{
		memset(this, 0, sizeof(tagTQtCallParam));
		m_emKeyFrequency = EmQtFrequencyEveryConf;
		m_bCallEncryption = FALSE;
	}

}TQtCallParam;


#endif
