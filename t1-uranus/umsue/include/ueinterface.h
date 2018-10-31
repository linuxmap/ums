#ifndef _h_ueinterface_h__
#define _h_ueinterface_h__

#include "umsobject.h"
#include "usermanage.h"
#include "umsinnerstruct.h"
#include "tpvector.h"
#include "umchandler.h"
#include "toolhandler.h"

class CUsrManage;
class CUmsUeInst :  public CUmsObject
{
public:
    CUmsUeInst();
	~CUmsUeInst();

public:
	u16				NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);
	u16				NotifyMsgToHdu(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);
	
protected:
	virtual BOOL	PreMessageProc ( CMessage *const ptMsg ); 
	virtual void	MessageProc( CTpMsg *const ptMsg);
	virtual BOOL32	ObjectInit(u32 wParam, u32 lParam);
	virtual void	ObjectExit();
	virtual void	InstanceDump(u32=0);
	
protected:
	//��ʾUMC�û���¼��Ϣ
	void			ShowLogin();
	//��ʾά�����ߵ�¼�û���Ϣ
	void			ShowToolLogin();

private:
	void			OnDisconnect(CMessage *const ptMsg);
	//�ַ�PreMessageProc��Ϣ
	void			DispatchPreMsg(CMessage* const pMsg);

private:
	static CUmcHandler*		m_pcUmcHandler;		//UMC�û�����ӿ�
	static CToolHandler*	m_pcToolHandler;	//ά�����ߴ���ӿ�

private:
	u32		m_dwUmcAppID;	//UMC��APPID
	u32		m_dwToolAppID;	//ά�����ߵ�APPID
	u32		m_dwListenNode;	//�����ڵ�
	u32		m_dwServiceInst;
};

typedef zTemplate<CUmsUeInst, 1> CUmsUeApp;


#endif // _h_ueinterface_h__
