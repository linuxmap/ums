#ifndef _h_umsconfigex_h__
#define _h_umsconfigex_h__

#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"
#include "umsinnertype.h"


enum EmUmsRunType
{
	Ums_Run_On_Win32 = 0,
	Ums_Run_On_Mpc2 = 1,
	Ums_Run_On_Cri2 = 2,
	Ums_Run_On_Linux = 3,

	Ums_Run_On_Unkonw = 100,
};
 
class CUmsConfigEx
{
private:
	//���鿪ʼʱ�� ÿ��������ն���㲥Դ�Ĺؼ�֡����������¼���
	u32 m_dwBeginFastUpdateInterval;
	//���鿪ʼʱ�� �趨��ʱ��������Ч���������,�������������־Ͳ����ؼ�֡������㲥Դ
	u32 m_dwBeginFastUpdateNeglectNum;
	
	//ÿ��������ն���㲥Դ�Ĺؼ�֡����������¼���
	u32 m_dwFastUpdateInterval ;
	//�趨��ʱ��������Ч���������,�������������־Ͳ����ؼ�֡������㲥Դ
	u32	m_dwFastUpdateNeglectNum;	

	u16 m_dwRsFirstTime;
	u16 m_dwRsSecondTime;
	u16 m_dwRsThirdTime;
	u16 m_dwRsRejectTime;
	u16 m_wIpCallLvl;
	u16 m_wE164CallLvl;
	u16 m_wAliasCallLvl;

	s32 m_nMixProtectedTime;		//���������ı���ʱ��
	BOOL32 m_bIsPrintToCom;         //�Ƿ������ӡ������

	BOOL32 m_bVmpUsed;
	
	u16 m_wTvWallLastPic;          // ����ǽ�����ʾ����

	BOOL32 m_bVirPoll;             // �Ƿ��ʼ��������ѯ���

	BOOL32 m_bEnc3060Bas;             //���� ��25/50ǿ�Ƴ�30/60
	BOOL32 m_bEnc3060Vmp;             //�ϳ� ��25/50ǿ�Ƴ�30/60

	u32 m_dwDelayTime;

	u32 m_dwmpu2tpNetBandMul;      //Mpu2tp  NetBand �Ŵ���

	BOOL32 m_bVmptpStyleUp;          //�໭��ϳ�ͼ���Ƿ������Ļ�·�
	EmUmsRunType m_emUmsRunType;

	BOOL32 m_bCasecadeMcu;			// �Ƿ���mcu

	u16	m_wApu2MixNumOne;
	u16	m_wApu2MixNumTwo;
	u16	m_wApu2MixNumThree;
	u16	m_wApu2MixNumFour;

	BOOL32 m_bdualmix;          //�Ƿ���˫��ǿ�ƻ���

	BOOL32 m_bXmpu5Used;  //�Ƿ�����Xmpu5�໭��ϳ�

private:
	static CUmsConfigEx *m_pcInstance;
	BOOL32 m_bIsInited;
protected:
	CUmsConfigEx()
	{
		m_bIsInited = FALSE;

		m_dwBeginFastUpdateInterval = 5;
		m_dwBeginFastUpdateNeglectNum = 1;	

		m_dwFastUpdateInterval = 2;
		m_dwFastUpdateNeglectNum = 1;	
		
		m_dwRsFirstTime = 0;
		m_dwRsSecondTime = 0;
		m_dwRsThirdTime = 0;
		m_dwRsRejectTime = 0;

		m_nMixProtectedTime = 4;

		m_bIsPrintToCom = FALSE;

		m_bVmpUsed = TRUE;

		m_wTvWallLastPic = TWLP_SHOW_DEFPIC_MODE;

		m_bVirPoll = FALSE;

		m_bEnc3060Bas = FALSE;
		m_bEnc3060Vmp = FALSE;

		m_dwDelayTime = 1500;

		m_dwmpu2tpNetBandMul = 20;
		m_bVmptpStyleUp = FALSE;

		m_emUmsRunType = Ums_Run_On_Unkonw;

		m_bCasecadeMcu = FALSE;

		m_wApu2MixNumOne = 34;
		m_wApu2MixNumTwo = 10;
		m_wApu2MixNumThree = 10;
		m_wApu2MixNumFour = 10;

		m_bdualmix = FALSE;
		m_bXmpu5Used = TRUE;
		
	}
	CUmsConfigEx(CUmsConfigEx&){}
protected:
	BOOL32 SaveToFile(){return TRUE;}
	
public:
	BOOL32 ReadFromFile();
	u32  GetFastUpdateInterval()	{ return m_dwFastUpdateInterval; }
	u32  GetFastUpdateNeglectNum()	{ return m_dwFastUpdateNeglectNum; }
	
	u32  GetBeginFastUpdateInterval()	{ return m_dwBeginFastUpdateInterval; }
	u32  GetBeginFastUpdateNeglectNum()	{ return m_dwBeginFastUpdateNeglectNum; }


	u16  GetRsFirstTime()	{ return m_dwRsFirstTime; }
	u16  GetRsSecondTime()	{ return m_dwRsSecondTime; }
	u16  GetRsThirdTime()	{ return m_dwRsThirdTime; }
	u16  GetRsRejectTime()	{ return m_dwRsRejectTime; }
	u16  GetIpCallLvl()     { return m_wIpCallLvl; }
	u16  GetE164CallLvl()   { return m_wE164CallLvl; }
	u16  GetAliasCallLvl()  { return m_wAliasCallLvl; }

	BOOL32 GetVmpUsed() { return m_bVmpUsed; }
	void SetVmpUsed(BOOL32 bUsed) { m_bVmpUsed = bUsed; }

	u16 GetTvWallLastPic() { return m_wTvWallLastPic; }
	void SetTvWallLastPic(u16 wLastPic) 
	{
		if (TWLP_SHOW_BLACK_MODE != wLastPic && TWLP_SHOW_DEFPIC_MODE != wLastPic 
			&& TWLP_SHOW_LASTFRAME_MODE != wLastPic && TWLP_SHOW_USERDEFPIC_MODE != wLastPic) 
			m_wTvWallLastPic = TWLP_SHOW_DEFPIC_MODE; 
		else
			m_wTvWallLastPic = wLastPic;
	}

	BOOL32	GetVirPoll() { return m_bVirPoll; }
	void SetVirPoll(BOOL32 bVirPoll) { m_bVirPoll = bVirPoll; } 

	BOOL32	GetEnc3060Bas() { return m_bEnc3060Bas; }
	void SetEnc3060Bas(BOOL32 b3060) { m_bEnc3060Bas = b3060; } 

	BOOL32	GetEnc3060Vmp() { return m_bEnc3060Vmp; }
	void SetEnc3060Vmp(BOOL32 b3060) { m_bEnc3060Vmp = b3060; } 

	u32	GetDelayTime() { return m_dwDelayTime; }

	u16	GetMixNum(u16 wIndex) 
	{
		if (0 == wIndex)
		{
			return m_wApu2MixNumOne;
		}
		else if (1 == wIndex)
		{
			return m_wApu2MixNumTwo;
		}
		else if (2 == wIndex)
		{
			return m_wApu2MixNumThree;
		}
		else if (3 == wIndex)
		{
			return m_wApu2MixNumFour;
		}
		return 0;
	}

    u32 GetMpu2tpNetBandMul() {	return m_dwmpu2tpNetBandMul;}
	BOOL32 GetVmptpStyleUp() {return m_bVmptpStyleUp;}
	void SetVmptpStyleUp(BOOL32 bUpStyle) { m_bVmptpStyleUp = bUpStyle; }

	EmUmsRunType  GetUmsRunType()	{ return m_emUmsRunType; }
	void  SetUmsRunType(EmUmsRunType type)	{ m_emUmsRunType = type; }

	BOOL32  IsCasecadeMcuOn()	{ return m_bCasecadeMcu; }
	void  SetCasecadeMcuOn(BOOL32 bOn)	{ m_bCasecadeMcu = bOn; }

	s32		GetMixProtectedTime() const{ return m_nMixProtectedTime; }
	void	SetMixProtectedTime(s32 nTime){ m_nMixProtectedTime = nTime; }

	BOOL32 GetPrintState() { return m_bIsPrintToCom; }
	void SetPrintState(BOOL32 bIsPrint) { m_bIsPrintToCom = bIsPrint; }


	BOOL32 IsDualMixOn() {return m_bdualmix;}

	BOOL32 GetXmpu5Used() { return m_bXmpu5Used; }
	void SetXmpu5Used(BOOL32 bUsed) { m_bXmpu5Used = bUsed; }

public:
	virtual ~CUmsConfigEx()
	{
		if ( m_pcInstance != NULL )
		{
			delete m_pcInstance;
			m_pcInstance = NULL;
		}
	}
public:
	static CUmsConfigEx* GetInstance();
	//��ʾ����˽����Ϣ
    void ShowAll(void);
};

#endif //_h_umsconfigex_h__






















