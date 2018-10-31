#ifndef _PB_INSTANCE_H_
#define _PB_INSTANCE_H_

#include <map>
#include "pbmsg.h"
#include "logclientapi.h"
#include "osp.h"

namespace pbmsg {

// OSP event
#define Ev_OSP_PBInst_Init					OSP_USEREVENT_BASE + 1
#define Ev_OSP_PBInst_Exit					OSP_USEREVENT_BASE + 2
#define Ev_OSP_PBInst_PBMsg					OSP_USEREVENT_BASE + 3

class CPBInstance;

// pb��Ϣ������
typedef BOOL32 (CPBInstance::*PFPBMsgFunc)(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode);
// CMessage������
typedef BOOL32 (CPBInstance::*PFMsgFunc)(CMessage* const pcMsg);

class PROTOBUFMSG_API CPBInstance : public log4cpclient::CLogBase , public CInstance
{

public:
	virtual ~CPBInstance(){
		m_bInit = FALSE;
	}

protected:
	CPBInstance(){
		m_bInit = FALSE;
	}

	// ��ʼ��
	virtual BOOL32	InstInit(u32 dwParam) = 0;
	virtual BOOL32	DaemonInstInit(u32 dwParam, CApp* pcApp) = 0;

	// �˳�
	virtual void	InstExit() = 0;
	virtual void	DaemonInstExit() = 0;

	// pb��Ϣ�������
	virtual BOOL32	PBMessageProc(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode) = 0;
	virtual BOOL32	DaemonPBMessageProc(CPBMsg* pcPBMsg, CApp* pcApp, u32 dwSrcId, u32 dwSrcNode) = 0;

	// CMessage��Ϣ�������
	virtual BOOL32	MessageProc(CMessage* const pcMsg) = 0;
	virtual BOOL32	DaemonMessageProc(CMessage* const pcMsg, CApp* pcApp) = 0;

	// ����ע��pb��Ϣ��ʵ�ֺ�����ӳ�䣬��Ҫ����Ϣ��ں�������HandlePBMsg
	BOOL32	RegPBMsgFunc(std::string strMsgName, PFPBMsgFunc pPBMsgFunc);
	BOOL32	UnRegPBMsgFunc(std::string strMsgName);
	BOOL32	IsPBMsgFuncReg(std::string strMsgName);
	void	ClearPBMsgFunc();
	BOOL32	HandlePBMsg(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode);

	// ����ע��CMessage��Ϣ��ʵ�ֺ�����ӳ�䣬��Ҫ����Ϣ��ں�������HandleMsg
	BOOL32	RegMsgFunc(u16 wEvent, PFMsgFunc pMsgFunc);
	BOOL32	UnRegMsgFunc(u16 wEvent);
	BOOL32	IsMsgFuncReg(u16 wEvent);
	void	ClearMsgFunc();
	BOOL32	HandleMsg(CMessage* const pcMsg);

private:
	// appʵ����Ϣ�������ڣ�ʹ���߼̳д�������������
	virtual void DaemonInstanceEntry( CMessage* const pMsg, CApp* pcApp);
	virtual void InstanceEntry( CMessage* const pMsg);

private:
	BOOL32									m_bInit;
	std::map<std::string, PFPBMsgFunc>		m_mapPBMsgFunc; //pb��Ϣ������map
	std::map<u16, PFMsgFunc>				m_mapMsgFunc; //CMessage��Ϣ������map
};

}// namespace pbmsg

#endif //_PB_INSTANCE_H_