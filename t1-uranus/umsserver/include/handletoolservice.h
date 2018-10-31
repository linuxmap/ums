#ifndef HANDLE_TOOL_SERVICE_H
#define HANDLE_TOOL_SERVICE_H
#include "tphandle.h"
#include "umsinnerstruct.h"

//����ά�����������Ϣ�Ļ�ȡ
class CUmsToolHandleService : public CTpHandler
{
public:
	CUmsToolHandleService(CTpObject* pcObjec);
	~CUmsToolHandleService();

public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	
public:
	//�������ڿ����������ά������
	void	UpdateConfCount();

private:
	//�����û���¼��Ϣ
	void	EventLogin();
	//��ȡϵͳ��Ϣ����CPU ���ڴ�
	void	EventSysInfo();
	//��ȡ���ڿ���Ļ�������
	void	EventConfCount();
	//����UMS
	void	EventRebootUms();
	//��ѯ��Ȩʹ������
	void	EventAuthCount();
	void	EventAuthCountNty(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void 	EventLicenseOutputReq();

	//����ǽʹ�����
	void	EventHduCount();

private:
};

#endif