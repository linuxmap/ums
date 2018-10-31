#ifndef _ums_vmp_h_
#define _ums_vmp_h_
#include "kdvmulpic_hd.h"
#include "vmpstyleinfo.h"
#include "vmprcvchan.h"
#include "vmpsndchan.h"
#include "tpsys.h"

class CVmpRcvChan;
//
class CUmsVmp
{
public:
	CUmsVmp();
	~CUmsVmp();

public:
	BOOL32		Init(u32 dwRcvIP, u16 wRcvPort, u16 wLocalRcvPort, u16 wLocalSndPort, const TVmpTimeSpan& tSpan);
	EmVmpRes	Start(const TVmpStartParam& tInfo);
	void		Stop();
	EmVmpRes	ChangeStyleParam(const TVmpStyleInfo& tInfo);
	EmVmpRes	SetEncParam(const TVmpEncParam& tParam);
	TVideoEncParam* GetEncParam() { return &m_tEncParam; }

	void		UpdateRmtPort(u32 dwRcvIP, u16 wRcvPort);

	BOOL32		CheckFrame(u16 wMemberIndx);
	BOOL32		SetFast();

	BOOL32		UpdateSidelineColor(BOOL32 bDefault = TRUE);
	void		SetSideLineFlag(u8 acSide[], u8 byNum) { memcpy(m_abyFlag, acSide, sizeof(m_abyFlag)); }

//Protocol_file

	void		SetMediaKey(TTPQTMediaKeyInfo& tSndQ);
	void		SetQtHandle(u16 wHandle) { m_wQtHandle = wHandle; }
	u16			GetQtHandle() { return m_wQtHandle; }


	void		Show();
private:
	void		Clear();
	BOOL32		SetIdleChanShow(EmVmpShowMode emShowMode);
	EmVmpRes	StartMerge();
	
	void		SetEncrypt(const TTPEncrypt& tEncrypt);

private:
	static void RecvFrame(PFRAMEHDR pFrmHdr, u32 dwContext);
	static void VmpCallBack(PTFrameHeader pFrameInfo, void* pContext);

private:
	friend class CVmpRcvChan;

private:
//下面这些参数 每次合成停止都会清空
	CVmpRcvChan		m_acMediaRcv[UMS_VMP_MAX_RCV];   //10 路接收
	BOOL32			m_abAddChanFlag[UMS_VMP_MAX_RCV];
	CVmpSndChan		m_cSndChan;
	CVmpStyle		m_cStyle;
	TVmpStartParam	m_tParam;
	TVideoEncParam	m_tEncParam;
//////////////////////////////////////////////////////////////////////////
//下面这些参数 注册成功才更新
	CHardMulPic		m_cHardMulPic;
	BOOL32			m_bAlreadyCreated;
	u32				m_dwRcvIP;
	u16				m_wRcvPort;
	u16				m_wLocalRcvPort;
	u16				m_wLocalSndPort;
	TVmpTimeSpan	m_tSpan;

//Protocol_file
    u16				m_wQtHandle;

	u8				m_abyFlag[UMS_VMP_MAX_RCV];
public:
	u16				m_wVmpID;
	BOOL32			m_bShowEnc;
};

#endif
