#ifndef _h_regoprdb_h__
#define _h_regoprdb_h__

#include "tpobject.h"
#include "regserver.h"
#include "tpmemmanager.h"
#include "tptrie.h"
#include "regstruct.h"

#define MAX_SEND_REGINFO_NUM_ONE_TIME 		(u32)40	//每次发送的注册信息的条数

typedef struct tagTRegData
{
	u32				m_dwTryTimes;
	u32				m_dwTimerID;
	u32				m_dwExpires;	//超时时间
	s32				m_nCSqence;		//序列号 //m_tRegistrar m_dwExpires m_aCallId m_nCSqence 需要业务层保存，以便查询
	u32				m_dwCallType;				
	u32_ip			m_dwSelfAddr;	//注册方 的地址

	s8				m_aSelfVer[TP_MAX_VERSION_LEN + 1];				//注册方 的版本号
	s8				m_aCompileTm[TP_MAX_VERSION_LEN + 1];			//注册方 的编译时间
	s8				m_aCallId[TP_MAX_NUM_CALLID];					//呼叫ID

	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//呼叫地址
	CMemPool<TTPAlias>	m_alias;									//别名节点
	EmTPEndpointType	m_emSelfType;								//注册方 的系统类型(UMS和CNS)

	u32					m_dwSelfQtID;								//注册方 的本地量子终端的ID

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

//别名ID
typedef struct tagAliasID
{
	u32		m_dwParentID;	//上级节点存储的ID
	u32		m_dwAliasID;	//别名节点的存储ID
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
	//消息处理函数
	virtual void	MessageProc(CTpMsg *const ptMsg);

protected:
	//初始化
	virtual BOOL32	ObjectInit(u32 wParam, u32 lParam);
	//清理
	virtual void	ObjectExit(void);
	virtual void	InstanceDump(u32=0);

protected:
	//注册
	BOOL32			ProcessRegEvent(CTpMsg *const ptMsg);
	//解除注册
	BOOL32			ProcessUnRegEvent(CTpMsg *const ptMsg);
	//查询
	BOOL32			ProcessARQEvent(CTpMsg *const ptMsg);
	//注册信息查询
	BOOL32			ProcessRegInfoEvent(CTpMsg* const ptMsg);
	
protected:
	void			ShowAllReg();
	void			ShowTimer();
	void			ShowNode();
	void			ShowRegMem();
	void			GetRegInfo();
	void			AddRegInfo();

private:
	//添加注册信息
	EmTpCnsRegUms	AddReg(TCnsRegInfo* ptRegInfo);
	//删除注册信息
	EmTpCnsRegUms	DelReg(TCnsRegInfo* ptRegInfo);
	//查找是否存在相同别名
	BOOL32			IsRepeat(TCnsRegInfo* ptRegInfo);
	//添加别名
	BOOL32			AddAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID);
	//更新别名信息
	BOOL32			UpdateAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID);
	//查找出了本身以外是否还存在相同的别名
	BOOL32			IsRepeatExceptSelfNode(TCnsRegInfo* ptRegInfo, u32 dwID);
	//获得定时器对应的ID
	u32				GetTimerObj(u32 dwTimer);
	//删除注册的别名
	void			DelAlias(u32 dwID);
	//发送消息给升级工具
	void			SendRegInfoToUpgradTool( CTpMsg *const ptMsg );
	//
	void			ReqRegInfoFromOldVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType);
	//
	BOOL32			ReqRegInfoFromNewVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType, s8* pCallID);

private:
	//获取包总数 B1
	u16				GetPackNums(const EmGetRegInfoType& emType) const;
	//B2
	u16				GetPackNumsEx(const EmGetRegInfoType& emType) const;
	//查找是否已存在同样的注册，如果存在删除
	void			DelExistReg(TCnsRegInfo* ptRegInfo);

private:
	CTpTimerMgr*		m_pcTimerMgr;	//定时
	CMemPool<TRegData>	m_regDataMem;	//内存池
	CTrie<u32>			m_regTre;		//注册树
	CTrie<TAliasID>		m_aliasTre;		//别名树 
	u16					m_wCnsNums;	//CNS别名总数
	u16					m_wUmsNums;	//UMS别名总数

	u16					m_wUmsNodeNums;	//ums注册数量
	u16					m_wCnsNodeNums;	//cns注册数量
};


typedef zTemplate<CTpRegOprdb, 1> CTpRegOprdbApp;

#endif // _h_regoprdb_h__

