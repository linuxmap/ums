#ifndef _h_handlelicense_h__
#define _h_handlelicense_h__

#include "tphandle.h"
#include "tpstruct.h"

#define LICENSE_MSG_LEN 128
typedef struct tagTLicenseInfo
{
	s8 abyLicenseVer[LICENSE_MSG_LEN];
	s8 abyLicenseType[LICENSE_MSG_LEN];
	u8 abyDeviceMac[6];		//ums������ַ
	u16	wAccessNum;			//�����������
	TTPTime tTime;			//��ȨʧЧʱ��

	s8 abyProjectName[LICENSE_MSG_LEN];
	s8 abyUserType[LICENSE_MSG_LEN];
	s8 abyContractCode[LICENSE_MSG_LEN];
	s8 abyCustomerName[LICENSE_MSG_LEN];
	s8 abySeller[LICENSE_MSG_LEN];
	s8 abyDescription[LICENSE_MSG_LEN];

	tagTLicenseInfo()
	{
		memset(this, 0, sizeof(tagTLicenseInfo));
		strncpy(abyLicenseVer, "V1.1.2", LICENSE_MSG_LEN-1);
		strncpy(abyLicenseType, "KDVUMS", LICENSE_MSG_LEN-1);

		wAccessNum = 192;	//��ppc_82xx��ppc_85xx��Ĭ�϶���192;�����ppc_82xx��ppc_85xx�������Ȩ�ļ�
	}

}TLicenseInfo;
class CUmsLicenseService : public CTpHandler
{
public:
	CUmsLicenseService(CTpObject* pcObjec);
	~CUmsLicenseService();
	
public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	virtual BOOL32 Create();

	void	ShowLicense();
	void	ReadLicense();
	u16		GetAccessNum()	{ return m_tInfo.wAccessNum;}
	TTPTime	GetLicenseTime() { return m_tInfo.tTime; }
	BOOL32	ProccessLicenseOutputReq(s8* szPathName, u16 wPathLen);
	void	LicenseTimeCheck(TTPTime tLicense);
private:
	TLicenseInfo m_tInfo;
	BOOL32		 m_bIsMaster;
	BOOL32		 m_bTimeIsValid;
};





#endif // _h_handlelicense_h__
