#ifndef _h_regoprdb_h__
#define _h_regoprdb_h__

#include "tpobject.h"
#include "regserver.h"
#include "tpmemmanager.h"
#include "tptrie.h"
#include "regstruct.h"

#define MAX_SEND_REGINFO_NUM_ONE_TIME 		(u32)40	//ÿ�η��͵�ע����Ϣ������

typedef struct tagTRegData
{
	u32				m_dwTryTimes;
	u32				m_dwTimerID;
	u32				m_dwExpires;	//��ʱʱ��
	s32				m_nCSqence;		//���к� //m_tRegistrar m_dwExpires m_aCallId m_nCSqence ��Ҫҵ��㱣�棬�Ա��ѯ
	u32				m_dwCallType;				
	u32_ip			m_dwSelfAddr;	//ע�᷽ �ĵ�ַ

	s8				m_aSelfVer[TP_MAX_VERSION_LEN + 1];				//ע�᷽ �İ汾��
	s8				m_aCompileTm[TP_MAX_VERSION_LEN + 1];			//ע�᷽ �ı���ʱ��
	s8				m_aCallId[TP_MAX_NUM_CALLID];					//����ID

	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//���е�ַ
	CMemPool<TTPAlias>	m_alias;									//�����ڵ�
	EmTPEndpointType	m_emSelfType;								//ע�᷽ ��ϵͳ����(UMS��CNS)

	u32					m_dwSelfQtID;								//ע�᷽ �ı��������ն˵�ID

	tagTRegData()
	{
		Clear();
	}
	void Clear()
	{
		m_dwTryTimes	= 0;
		m_dwTimerID		= 0;
		m_dwExpires		= 0;
		m_nCSqence		= 0;
		m_dwCallType	= 0;				
		m_dwSelfAddr	= 0;
		m_emSelfType	= emTPEndpointTypeUnknown;

		m_dwSelfQtID	= 0;


		memset(m_aSelfVer, 0, sizeof(m_aSelfVer));
		memset(m_aCompileTm, 0, sizeof(m_aCompileTm));
		memset(m_aCallId, 0, sizeof(m_aCallId));
		memset(m_atCalledAddr, 0, sizeof(m_atCalledAddr));
	}
	
	tagTRegData& operator = (const tagTRegData& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}

	BOOL32 operator == (const tagTRegData& tRhs)
	{
		return 0 == strcmp(m_aCallId, tRhs.m_aCallId);
	}

	void SetValue(TCnsRegInfo& tRegInfo)
	{
		m_dwCallType	= tRegInfo.m_dwCallType;
		m_dwExpires		= tRegInfo.m_tCsnNodeInfo.m_dwExpires;
		m_nCSqence		= tRegInfo.m_tCsnNodeInfo.m_nCSqence;
		m_dwSelfAddr	= tRegInfo.m_tCsnNodeInfo.m_atCalledAddr[0].m_dwIP;
		m_emSelfType	= tRegInfo.m_tCsnNodeInfo.m_emSelfType;

		m_dwSelfQtID	= tRegInfo.m_tCsnNodeInfo.m_dwSelfQtID;


		memcpy(m_aCallId, tRegInfo.m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
		memcpy(m_atCalledAddr, tRegInfo.m_tCsnNodeInfo.m_atCalledAddr, sizeof(m_atCalledAddr));
		memcpy(m_aSelfVer, tRegInfo.m_tCsnNodeInfo.m_aSelfVer, sizeof(m_aSelfVer));
		memcpy(m_aCompileTm, tRegInfo.m_tCsnNodeInfo.m_aCompileTm, sizeof(m_aCompileTm));
	}

	void GetValue(TCnsRegInfo& tRegInfo)
	{
		tRegInfo.m_dwCallType				 = m_dwCallType;
		tRegInfo.m_tCsnNodeInfo.m_dwExpires  = m_dwExpires;
		tRegInfo.m_tCsnNodeInfo.m_nCSqence	 = m_nCSqence;
		tRegInfo.m_tCsnNodeInfo.m_dwSelfAddr = m_dwSelfAddr;
		tRegInfo.m_tCsnNodeInfo.m_emSelfType = m_emSelfType;

        tRegInfo.m_tCsnNodeInfo.m_dwSelfQtID = m_dwSelfQtID;


		memcpy(tRegInfo.m_tCsnNodeInfo.m_aCallId, m_aCallId, TP_MAX_NUM_CALLID);
		memcpy(tRegInfo.m_tCsnNodeInfo.m_atCalledAddr, m_atCalledAddr, sizeof(m_atCalledAddr));
		memcpy(tRegInfo.m_tCsnNodeInfo.m_aSelfVer, m_aSelfVer, sizeof(m_aSelfVer));
		memcpy(tRegInfo.m_tCsnNodeInfo.m_aCompileTm, m_aCompileTm, sizeof(tRegInfo.m_tCsnNodeInfo.m_aCompileTm));
	}

	void Update( TCnsRegNode& tCnsReg )
	{
		memset( m_aSelfVer, 0, sizeof(m_aSelfVer) );
		memcpy( m_aSelfVer, tCnsReg.m_aSelfVer, sizeof(m_aSelfVer) );
		m_aSelfVer[TP_MAX_VERSION_LEN] = '\0';

		memset( m_aCompileTm, 0, sizeof(m_aCompileTm));
		memcpy( m_aCompileTm, tCnsReg.m_aCompileTm, sizeof(m_aCompileTm) );
		m_aCompileTm[TP_MAX_VERSION_LEN] = '\0';

        m_dwSelfQtID = tCnsReg.m_dwSelfQtID;


		return ;
	}
}TRegData;

//����ID
typedef struct tagAliasID
{
	u32		m_dwParentID;	//�ϼ��ڵ�洢��ID
	u32		m_dwAliasID;	//�����ڵ�Ĵ洢ID
}TAliasID, *PTAliasID;


class CTpTimerMgr;
class CTpRegOprdb :  public CTpObject
{
public:
    CTpRegOprdb();
	~CTpRegOprdb();

public:
	void			RegTimeOut(u32 dwTime);

protected:
	//��Ϣ������
	virtual void	MessageProc(CTpMsg *const ptMsg);

protected:
	//��ʼ��
	virtual BOOL32	ObjectInit(u32 wParam, u32 lParam);
	//����
	virtual void	ObjectExit(void);
	virtual void	InstanceDump(u32=0);

protected:
	//ע��
	BOOL32			ProcessRegEvent(CTpMsg *const ptMsg);
	//���ע��
	BOOL32			ProcessUnRegEvent(CTpMsg *const ptMsg);
	//��ѯ
	BOOL32			ProcessARQEvent(CTpMsg *const ptMsg);
	//ע����Ϣ��ѯ
	BOOL32			ProcessRegInfoEvent(CTpMsg* const ptMsg);
	
protected:
	void			ShowAllReg();
	void			ShowTimer();
	void			ShowNode();
	void			ShowRegMem();
	void			GetRegInfo();
	void			AddRegInfo();

private:
	//���ע����Ϣ
	EmTpCnsRegUms	AddReg(TCnsRegInfo* ptRegInfo);
	//ɾ��ע����Ϣ
	EmTpCnsRegUms	DelReg(TCnsRegInfo* ptRegInfo);
	//�����Ƿ������ͬ����
	BOOL32			IsRepeat(TCnsRegInfo* ptRegInfo);
	//��ӱ���
	BOOL32			AddAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID);
	//���±�����Ϣ
	BOOL32			UpdateAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID);
	//���ҳ��˱��������Ƿ񻹴�����ͬ�ı���
	BOOL32			IsRepeatExceptSelfNode(TCnsRegInfo* ptRegInfo, u32 dwID);
	//��ö�ʱ����Ӧ��ID
	u32				GetTimerObj(u32 dwTimer);
	//ɾ��ע��ı���
	void			DelAlias(u32 dwID);
	//������Ϣ����������
	void			SendRegInfoToUpgradTool( CTpMsg *const ptMsg );
	//
	void			ReqRegInfoFromOldVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType);
	//
	BOOL32			ReqRegInfoFromNewVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType, s8* pCallID);

private:
	//��ȡ������ B1
	u16				GetPackNums(const EmGetRegInfoType& emType) const;
	//B2
	u16				GetPackNumsEx(const EmGetRegInfoType& emType) const;
	//�����Ƿ��Ѵ���ͬ����ע�ᣬ�������ɾ��
	void			DelExistReg(TCnsRegInfo* ptRegInfo);

private:
	CTpTimerMgr*		m_pcTimerMgr;	//��ʱ
	CMemPool<TRegData>	m_regDataMem;	//�ڴ��
	CTrie<u32>			m_regTre;		//ע����
	CTrie<TAliasID>		m_aliasTre;		//������ 
	u16					m_wCnsNums;	//CNS��������
	u16					m_wUmsNums;	//UMS��������

	u16					m_wUmsNodeNums;	//umsע������
	u16					m_wCnsNodeNums;	//cnsע������
};


typedef zTemplate<CTpRegOprdb, 1> CTpRegOprdbApp;

#endif // _h_regoprdb_h__

