#ifndef _data_conf_handler_h_
#define _data_conf_handler_h_

#include "tphandle.h"
#include "tptype.h"
#include "callnodemgr.h"

//////////////////////////////////////////////////////////////////////////
//���	�װ�������

enum EmDataConfStatus
{
	em_data_conf_idle,		//���ݻ��鴦�ڿ���״̬
	em_data_conf_working,	//���ݻ��鴦�ڿ���״̬
};

class CDataConfHandler : public CTpHandler
{
public:
	//�滻ΪCUmsConfInst
	CDataConfHandler(CTpObject* pcObject);
	~CDataConfHandler();

public:
	void				Dump(){}
	
public:
	virtual BOOL32		Handler(CTpMsg *const ptMsg);
	
public:
	//�����Ƿ����
	BOOL32				ConfIdle() const;
	//�����Ƿ���
	BOOL32				ConfWorking() const;
	//����״̬
	EmDataConfStatus	ConfStatus() const;
	//���ݻ��������IP
	u32					ServerIP() const;
	//��������
	void				HungupConf();

	void				OnChanConnect(TCallNode* ptNode);
private:
	void	EventJoinDataConf(CTpMsg* const ptMsg);
	void	EventJoinDataConfInd(CTpMsg* const ptMsg);
	void	EventHungUpDataConf(CTpMsg* const ptMsg);
	
private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }

private:
	EmDataConfStatus	m_emStatus;		//���ݻ���״̬
	u32					m_dwServerIP;	//���ݻ��������IP
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