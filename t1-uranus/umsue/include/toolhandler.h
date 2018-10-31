#ifndef TOOL_HANDLER_H
#define TOOL_HANDLER_H
#include "tphandle.h"
#include "umsinnerstruct.h"

//ά�������û���Ϣ����
class CToolHandler : public CTpHandler
{
public:
	CToolHandler(CTpObject* pcObject, u32 dwToolAppID);
	virtual ~CToolHandler();

public:
	virtual BOOL32 Handler(CTpMsg* const ptMsg);

public:
	//����ǰ�õ���Ϣ
	BOOL32			PreHandler(CMessage* const ptMsg);
	//��ʾ��¼�û�����Ϣ
	void			ShowLogin();

private:
	//�û���¼
	void			EventUserLogin(CMessage* const ptMsg);
	//��������
	void			EventDisconnect(CMessage* const ptMsg);

private:
	//��ӡ�¼�����Ϣ����Ҫ������ʹ��
	void			PrintEventInfo(CTpMsg* const ptMsg);
	//��ӡ�ӽ���������Ϣ
	void			PrintEventInfoFromUI(CTpMsg* const PtMsg);

private:
	TLogUser		m_tCurLogUser;	//��ǰ��¼�û�
	u32				m_dwToolAppID;	//ά������APPID

	BOOL32          m_bLockflag;     //����
	u32             m_dwLockReason;   //�������ɣ�UE ֻ���治����         
};

#endif