#ifndef UMC_HANDLER_H
#define UMC_HANDLER_H
#include "tphandle.h"
#include "usermanage.h"
#include "umsinnerstruct.h"
#include "tpvector.h"

class CUmcHandler : public CTpHandler
{
public:
	CUmcHandler(CTpObject* pcObject, u32 dwUmcAppID);
	virtual ~CUmcHandler();
	
public:
	virtual BOOL32 Handler(CTpMsg* const ptMsg);

public:
	//����ǰ�õ���Ϣ
	BOOL32			PreHandler(CMessage* const ptMsg);
	//��ʾ��¼�û�����Ϣ
	void			ShowLogin();

private:
	//�û���¼����
	void			EventUserLogin(CMessage* const ptMsg);
	//����û�
	void			EventAddUserReq(CMessage* const ptMsg);
	//ɾ���û�
	void			EventDelUser(CMessage* const ptMsg);
	//�޸��û�����
	void			EventChangePwdReq(CMessage* const ptMsg);
	//��������
	void			EventDisconnect(CMessage* const ptMsg);

private:
	//��ӡ�¼�����Ϣ����Ҫ������ʹ��
	void			PrintEventInfo(CTpMsg* const ptMsg);
	//��ӡ�ӽ���������Ϣ
	void			PrintEventInfoFromUI(CTpMsg* const ptMsg);
private:
	CUsrManage			m_cUserMG;		//�û�����
	CTpVector<TLogUser> m_tLogUser;		//�Ѿ���¼���û�
	u32					m_dwUmcAppID;	//UMCAPPID
};	

#endif