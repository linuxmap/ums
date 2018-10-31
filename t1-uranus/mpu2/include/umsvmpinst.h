#ifndef _ums_vmp_inst_h_
#define _ums_vmp_inst_h_
#include "osp.h"
#include "umsvmp.h"
#include "tpsys.h"
#include "tpmsg.h"

using namespace UmsTpmsg;

enum EmTest
{
	em_init_channel,
	em_ask_frame,
	em_show_info,
	em_show_enc,
};


enum EmVmpStatus
{
	em_vmp_invalid,
	em_vmp_idle,
	em_vmp_working,
};

class CUmsVmpInst : public CInstance
{
public:
	CUmsVmpInst();
	~CUmsVmpInst();

public:
	virtual void InstanceEntry(CMessage *const pcMsg);
	virtual void InstanceDump(u32 dwParam);

private:
	void	EventInit(CMessage *const pcMsg);
	void	EventRegTimer(CTpMsg& cMsg);
	void	EventCheckFrameTimer(CMessage *const pcMsg);
	void	EventFrameReq(CTpMsg& cMsg);
	void	EventRegAck(CTpMsg& cMsg);
	void	EventRegNack(CTpMsg& cMsg);
	void	EventDisconnect(CMessage *const pcMsg);

	void	EventStartReq(CTpMsg& cMsg);
	void	EventMdyParam(CTpMsg& cMsg);
	void	EventStopReq(CTpMsg& cMsg);
	void	EventUpdateSpeakerFlag(CTpMsg& cMsg);

//Protocol_file

    void	EventSetMediaKey(CTpMsg& cMsg);


	void	Show();
public:
	void	TestInitChannel();
	void	TestAskFrame();

private:
	void	Register();
	void	Clear();

public:
	void	PostMsg(u32 dwDestIID, u16 wEvent, void* pBuf, u16 wLength);

private:
	BOOL32	m_bRegState;	//注册状态

private:
	CUmsVmp	m_cUmsVmp;
	u32		m_dwLastTime;
};

class CVmpData
{
public:
	CVmpData();
	~CVmpData();

public:
	void	Clear();
	void	Init() { m_bInit = TRUE; }
	BOOL32	IsInit() const { return m_bInit; }

public:
	void	SetNode(u32 dwNode) { m_dwNode = dwNode; }
	u32		ConnectNode() const { return m_dwNode; }

private:
	u32		m_dwNode;		//连接节点
	BOOL32	m_bInit;		//是否初始化
};


typedef zTemplate<CUmsVmpInst, UMS_VMP_MAX_CHANNEL, CVmpData>	CUmsVmpApp;

//回调接口
void InitUmsVmp(u32 dwNode);
void StopApp();

#endif
