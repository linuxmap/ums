#ifndef _h_cnsinnerstruct_h__
#define _h_cnsinnerstruct_h__

#include "tpsys.h"
#include "tpstruct.h"
#include "md5.h"
#include "usermanage.h"


const int CN_MAX_FULLFILENAME_LEN = 128; // �����ļ�����󳤶�
const int CN_MAX_USER_NAME_LENGTH = 32; // �û�������
const int CN_MAX_PASSWORD_LENGTH  = 32; // ���볤��


//Added by meifang
//��ǰ�᳡״̬
typedef struct tagTTPCurCnsConfStatus
{		
	EmCALLSTATE	emCallState; //�᳡����״̬  
	BOOL        m_bJoinConf;//�Ƿ�λ�
	tm			m_tConfTime; 
	EmCnState   emCnsState; //�᳡����״̬
	s8			achConfName[TP_MAX_ALIAS_LEN+1];	//�����������
public:
	tagTTPCurCnsConfStatus()
	{ 
		memset( this, 0, sizeof(struct tagTTPCurCnsConfStatus) );
	}
	u32 CalcElapseTime( const tm& tLaterTime )
	{
		u64 llOldTime = UnifyTimeBySec( m_tConfTime );
		u64 llLaterTime = UnifyTimeBySec( tLaterTime );
		u32 dwElapseTime = (u32)( llLaterTime - llOldTime );
		return dwElapseTime;
	}
	u64 UnifyTimeBySec( const tm& tTime )
	{
		int nPYRunYears = ( ( tTime.tm_year%4 ) ? ( tTime.tm_year/4 +1 ) : ( tTime.tm_year/4 ) );
		int nDays = tTime.tm_year*365 + nPYRunYears + tTime.tm_yday;
		u64 llHours = nDays*24 + tTime.tm_hour;
		u64 llMinutes = llHours*60 + tTime.tm_min;
		u64 llSeconds = llMinutes*60 + tTime.tm_sec;
		return llSeconds;
	}
}TTPCurCnsConfStatus;

//�᳡ע��״̬
typedef struct tagTTPCnsRegStatus
{
	BOOL    bIsSIPRegister;
	u32_ip  dwSIPIp;
	BOOL    bIsGKRegister;
	u32_ip  dwGkIp;

	public:
		tagTTPCnsRegStatus(){ memset( this, 0, sizeof(struct tagTTPCnsRegStatus) ); }
}TTPCnsRegStatus;

//TPad��¼��Ϣ
typedef struct tagTTPTPadLoginRequest
{
	CLoginRequest     cLoginRequest;
	s8                achTPadVersion[MAX_DEVICEVER_LEN];

	public:
		tagTTPTPadLoginRequest(){ memset( this, 0, sizeof(struct tagTTPTPadLoginRequest) ); }
}TTPTPadLoginRequest;

//�û���Ϣ
typedef struct tagTTPUserInfo
{
	CUserFullInfo     cUserFullInfo;
	s8                achTPadVersion[MAX_DEVICEVER_LEN];

	public:
		tagTTPUserInfo(){ memset( this, 0, sizeof(struct tagTTPUserInfo) ); }
}TTPUserInfo;

//End to add


#endif // _h_tpinnerstruct_h__
