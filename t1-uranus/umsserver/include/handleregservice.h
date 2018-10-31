#ifndef _h_handleregservice_h__
#define _h_handleregservice_h__
#include "tpstruct.h"
#include "tpsys.h"
#include "tphandle.h"
#include "umsinnertype.h"
#include "umsconfig.h"
#include "umsinnerstruct.h"


class CUmsRegHandleService : public CTpHandler
{
public:
	CUmsRegHandleService(CTpObject* pcObjec);
	~CUmsRegHandleService();
	
public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	virtual BOOL32 Create();

public:
	void ShowRegState();
	
protected:
	void EventLogin(void* pDataBuf, u16 wDataSize);
	void EventLogout(u8* pDataBuf, u16 wDataSize);
	void EventSetRegCfg(u8* pDataBuf, u16 wDataSize);
	void EventSetGkRegCfg(u8* pDataBuf, u16 wDataSize);
	void EventRegReq(u8* pDataBuf, u16 wDataSize);
	
	void EventRegRet(u8* pData, u16 wDataSize);
	void EventUnRegRet(u8* pData, u16 wDataSize);
	void EventReqRegInfo(CTpMsg *const ptMsg);
	void EventReqRegInfoRet(CTpMsg* const ptMsg);
	void EventUmsRegInfoRet(CTpMsg* const ptMsg);
	void EventCnsRegInfoRet(CTpMsg* const ptMsg);
	void EventMtRegInfoRet(CTpMsg* const ptMsg);
	void EventMcuRegInfoRet(CTpMsg* const ptMsg);
	void EventUpdateReg(const EmRegGroupNum& emGroupNum,BOOL32 bUpdateQtID = FALSE);
	void EventAdapterRegOut(u8* pData, u16 wDataSize);
protected:
	void Register( EmRegGroupNum emRegGroupNum, EmRegType emRegType);
	void UnRegister(EmRegType emRegType, EmRegGroupNum emGroupNum = em_AllGroup, BOOL32 bForce = FALSE);

private:
	//����B2��ȫ�ֵ�ַ�����û�
	void PostRegInfoToUserEx();
	//����ָ�����͵�ע����Ϣ��ָ�����û�
	void PostRegInfoToUser(TLogUser& tUser, const EmGetRegInfoType& tType);
	//֪ͨά������UMS��SIP��GK��ע����Ϣ
	void NotifyRegInfoToTpTool();

public:
	//���SIP��ע����
	void ClearRegRet(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums = em_AllGroup);
	//��ĳ�����ݰ���״̬�л�Ϊ����ע��״̬
	void SetGroupReging(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums = em_AllGroup);
	//��Ӧ��ע�������Ƿ�ɹ�ע��һ��
	BOOL32 IsRegOneGroup(const EmRegType& emRegType) const;
	//����Ӧע�����͵�ÿ����ע��״̬����һ��Ϊ�ɹ���������ע���򷵻�TRUE
	BOOL32 IsReg(const EmRegType& emRegType);

public:
	void  UpdateReg(const EmRegGroupNum emGroupNum);
    void  UpdateQtId(const u32 dwQtid);
public:

	//ע�����Լ�ʧ��ԭ��
	typedef struct tagRegRet
	{
		EmUmsRegState	m_emRegState;	//ע��״̬
		EmTpCnsRegUms	m_emReason;		//ע��ʧ�ܵ�ԭ��

		tagRegRet()
		{
			Clear();
		}

		void Clear()
		{
			m_emRegState = em_un_reg;
			m_emReason   = tp_CnsRegRet_Unknow;
		}
	}TRegRet;

protected:
	u16					m_wTempGroupNum;//ע������ʵ�ʸ���
	TTPSipRegistrarCfg  m_tSipRegCfg;	//Ŀǰֻ�õ�CFG�е���Ϣ�������������ȣ������������ⷢ
	TTPGKCfg			m_tGKRegCfg;	//GKע����Ϣ
	BOOL32				m_bReqRegInfo;	//�Ƿ��ѯ��ע����Ϣ

	TRegRet				m_atRegRet[TP_TEMPGROUP_MAXNUM][em_reg_type_end];	//ÿ����ע����
};

#endif // _h_handleregservice_h__
