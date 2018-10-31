#ifndef _EQPMGR_H_
#define _EQPMGR_H_

#include "umsobject.h"
#include "umseqp.h"
#include "mcudef.h"

typedef struct tagTBrdEntry
{
	BOOL32		m_bUsed;					// 是否配置
             
	//配置文件读取
	TTPBrdCfg	m_tBrdCfg;					//板子配置
	
	u8			m_byEqpNum;					// 运行的外设个数运行的外设个数
    TTPEqpCfg	m_atEqpCfg[TP_UMS_BRD_MAXNUM_EQP];// 运行在该单板上的外设配置
	BOOL32		m_abEqpReg[TP_UMS_BRD_MAXNUM_EQP];

	// 以下为板子上来更新
	BOOL32		m_bBrdState;				// 是否在线
	BOOL32		m_bBrdDel;					//板子是否被删除
	BOOL32		m_bMdlDel;					//模式是否删除
	u32			m_dwBrdNode;				//板子连接上来的OspNode 可作为板子的唯一标识
	u32			m_dwBrdIns;                 //板子的Inst号
    EMOsType	m_emOSType;                 // 单板的OS类型
	//暂定为板子上来更新
	u8			m_byPortChoice;				// 网口选择
    u8			m_byCastChoice;				// 组播选择
	tagTBrdEntry()
	{
		memset(this, 0, sizeof(tagTBrdEntry));
		m_bUsed = FALSE;
	}

	void BrdDisConnect()
	{
		m_bBrdState = FALSE;
		m_bBrdDel = FALSE;
		m_bMdlDel = FALSE;
		m_dwBrdNode = INVALID_NODE;
		m_dwBrdIns = INVALID_INS;
		m_emOSType = em_unknow_OsType;
		m_byPortChoice = 0;
		m_byCastChoice = 0;
		memset(m_abEqpReg, 0, sizeof(m_abEqpReg));
	}
	void BrdClear()
	{
		m_bUsed = FALSE;
		m_tBrdCfg.Clear();
		for (u16 wIndex = 0;wIndex < TP_UMS_BRD_MAXNUM_EQP; wIndex++)
		{
			m_atEqpCfg[wIndex].Clear();
			m_abEqpReg[wIndex] = FALSE;
		}
		m_byEqpNum = 0;
	}
	void BrdMdlDel(u16 wMdlIndex)
	{
		m_atEqpCfg[wMdlIndex].m_emEqpType = em_unknow_mdl;
		m_atEqpCfg[wMdlIndex].m_emEqpMdlType = em_unknow_eqp_mdl;
		memset(&m_atEqpCfg[wMdlIndex].m_szEqpAlias, 0, sizeof(m_atEqpCfg[wMdlIndex].m_szEqpAlias));	
		m_atEqpCfg[wMdlIndex].m_byEqpID = 0;
		m_abEqpReg[wMdlIndex] = FALSE;
		m_atEqpCfg[wMdlIndex].m_byAudmixNum = 0;
	}
	//根据service获取到的配置设置对应位置单板配置
	void SetBrdCfg(const TTPBrdCfg& tBrdCfg) 
	{
		memcpy(&m_tBrdCfg, &tBrdCfg, sizeof(TTPBrdCfg));
	}
	void SetMdlCfg(u16 wMdlIndex, const TTPMdlCfg& tMdlCfg)
	{
		m_atEqpCfg[wMdlIndex].m_emEqpType = tMdlCfg.m_emEqpType;
		m_atEqpCfg[wMdlIndex].m_emEqpMdlType = tMdlCfg.m_emEqpMdlType;

		memcpy(&m_atEqpCfg[wMdlIndex].m_szEqpAlias, tMdlCfg.m_szEqpAlias, sizeof(m_atEqpCfg[wMdlIndex].m_szEqpAlias));
		m_atEqpCfg[wMdlIndex].m_byEqpID = (u8)tMdlCfg.m_wEqpId;
		m_atEqpCfg[wMdlIndex].m_byAudmixNum = tMdlCfg.m_byAudmixNum;
	}
}TBrdEntry;

class CEqpMgr
{
public:
	CEqpMgr();
	~CEqpMgr();
public:
	virtual void Handle(CTpMsg *const ptMsg);
public:
	void Init(CUmsEqpInst* pEqpInst);//开机从配置文件读取配置

	TBrdEntry* GetBrdCfg( const TTPBrdPos& tBrdPos );//根据Node取得板子配置信息
	TBrdEntry* GetBrdCfg(const u8 byLayer, const u8 bySlot, const EMBrdType emType);
	TBrdEntry* GetBrdCfg(u32 dwBrdIP);
	TTPEqpCfg* GetEqpCfgByEqpID(u8 byEqpID);

	BOOL32     CheckBrdInfo( TTPBrdRegInfo *const ptBrdInfo, u32 dwNode, u32 dwIns );
	EMEqpType  BrdDisConnect(u32 dwBrdNode);
	void       UpdateBrdUsedState(TTPBrdUsedInfo& tUsed);  //更新单板使用状态
	void	   UpdateEqpRegState(u32 dwNode, u8 byEqpId, BOOL32 bReg); //更新外设注册状态
	void	   UpdateSysTimeToAllBrd();

	void	   RebootBrd(u32 dwBrdIP);
	
	u16        GetBrdIndex(u8 byBrdLayer, u8 byBrdSlot); //获得单板在数组中对应索引
	u16		   GetBrdIndex(u32 dwNode);					 //根据node号获得板子索引
	u16        GetEqpIndex(u16 wBrdIndex, u8 byEqpId);	 //根据eqpid找到对应外设
	void       ShowBrdInfo();

	u32        GetBrdInst(u16 wBrdIndex);  // 返回m_atBrdEntry[wBrdIndex]的单板Inst号 add by gaoyong

private:
	void       EventBrdCfgInfo(CTpMsg* const ptMsg);    //单板配置信息
	void       EventDelHandle(CTpMsg* const ptMsg);     //单板删除处理
	void       EventModifyHandle(CTpMsg* const ptMsg); //单板修改处理
	void	   EventMdlDelHandle(CTpMsg* const ptMsg); //模式删除
	void	   EventMdlModifyHandle(CTpMsg* const ptMsg);//模式修改
	void	   EventReboot(CTpMsg* const ptMsg);      //单板重启
	void	   EventUpGrade(CTpMsg* const ptMsg);     //单板升级
	void	   EventHardVerAck(CTpMsg* const ptMsg);  //单板版本号响应
	void	   EventUpdateAck(CTpMsg* const ptMsg);   //单板升级响应
	void	   EventEqpUsedReq(CTpMsg* const ptMsg);	  //混音 画面合成 适配占用情况

    void       EventSwitchTelnetFtp(CTpMsg* const ptMsg); //Telnet Ftp开关
	void       EventSwitchTelFtpAck(CTpMsg* const ptMsg);

private:
	void       NotifyBrdInfoToService(u16 wEvent, u8* pbyMsg = NULL, u16 wLen = 0);//通知单板信息到service
	void	   SendMsgToBrd(u32 dwSrcIID, u32 dwNode, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0);
private:
	u16			FindBrdArrayIndex(TTPBrdPos tPos);	//根据注册带来的信息找出所存数组中的索引
protected:
	CUmsEqpInst*	m_pcEqpInst;
	TBrdEntry		m_atBrdEntry[TP_BOARD_MAX_NUM];//保存板子的配置和状态

};

#endif