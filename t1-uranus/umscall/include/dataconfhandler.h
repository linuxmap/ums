#ifndef _data_conf_handler_h_
#define _data_conf_handler_h_

#include "tphandle.h"
#include "tptype.h"
#include "callnodemgr.h"

//////////////////////////////////////////////////////////////////////////
//许成	白板会议管理

enum EmDataConfStatus
{
	em_data_conf_idle,		//数据会议处于空闲状态
	em_data_conf_working,	//数据会议处于开会状态
};

class CDataConfHandler : public CTpHandler
{
public:
	//替换为CUmsConfInst
	CDataConfHandler(CTpObject* pcObject);
	~CDataConfHandler();

public:
	void				Dump(){}
	
public:
	virtual BOOL32		Handler(CTpMsg *const ptMsg);
	
public:
	//会议是否空闲
	BOOL32				ConfIdle() const;
	//会议是否开启
	BOOL32				ConfWorking() const;
	//会议状态
	EmDataConfStatus	ConfStatus() const;
	//数据会议服务器IP
	u32					ServerIP() const;
	//结束会议
	void				HungupConf();

	void				OnChanConnect(TCallNode* ptNode);
private:
	void	EventJoinDataConf(CTpMsg* const ptMsg);
	void	EventJoinDataConfInd(CTpMsg* const ptMsg);
	void	EventHungUpDataConf(CTpMsg* const ptMsg);
	
private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }

private:
	EmDataConfStatus	m_emStatus;		//数据会议状态
	u32					m_dwServerIP;	//数据会议服务器IP
};

inline BOOL32 CDataConfHandler::ConfIdle() const
{
	return em_data_conf_idle == m_emStatus;
}

inline BOOL32 CDataConfHandler::ConfWorking() const
{
	return em_data_conf_working == m_emStatus;
}

inline EmDataConfStatus CDataConfHandler::ConfStatus() const
{
	return m_emStatus;
}

inline u32 CDataConfHandler::ServerIP() const
{
	return m_dwServerIP;
}

inline void CDataConfHandler::HungupConf()
{
	m_emStatus = em_data_conf_idle;
	m_dwServerIP = 0;
}	

#endif