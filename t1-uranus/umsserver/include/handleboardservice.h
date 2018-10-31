#ifndef HANDLE_BOARD_SERVICE_H
#define HANDLE_BOARD_SERVICE_H

#include "tphandle.h"
#include "umsinnerstruct.h"

#define UPDATE_SUCCESS			0			//升级成功
#define UPDATE_APP_ERROR		1			//app 升级错误
#define UPDATE_0S_ERROR			2			//OS 升级错误
#define UPDATE_BOOT_ERROR		3			//Boot 升级错误
#define UPDATE_SET_FLAG_ERROR	4			//Set Flag 升级错误
#define UPDATE_ERROR			-1			//升级失败

typedef struct tagTTPBrdRegRes
{
	u8       m_byBrdLayer; //层号
	u8       m_byBrdSlot;  //槽号
	BOOL32   m_bReg;       //板子是否注册
	BOOL32   m_bModeReg;   //业务是否注册
	
	tagTTPBrdRegRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byBrdLayer = (u8)TP_INVALID_INDEX;
		m_byBrdSlot = (u8)TP_INVALID_INDEX;
		m_bReg = FALSE;
		m_bModeReg = FALSE;
	}
	
}TTPBrdRegRes;

typedef struct tagTHandleBoard
{
	TTPBrdInfo        m_atBrdCfg[TP_BOARD_MAX_NUM];
	TBrdVersion		  m_tBrdVer[TP_BOARD_MAX_NUM]; //版本
    TTelnetFtpStatus  m_tBrdTelFtpStat[TP_BOARD_MAX_NUM];//telnet和ftp开关状态
	BOOL32			  m_abEqp[EQP_ID_TOTAL_END - EQP_ID_HDU_END];
	tagTHandleBoard()
	{
		BrdVerInit();
		Clear();
		for (u16 wIndex = 0; wIndex < EQP_ID_TOTAL_END - EQP_ID_HDU_END; wIndex++)
		{
			m_abEqp[wIndex] = FALSE;
		}
	}

	void Clear()
	{
		memset(m_atBrdCfg, 0, sizeof(m_atBrdCfg));
		for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; ++wIndex)
		{
			m_atBrdCfg[wIndex].m_tBrdCfg.m_byBrdID = (u8)TP_INVALID_INDEX;
			m_tBrdTelFtpStat[wIndex].Clear();
		}
	}
	void BrdVerInit()
	{
		for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
		{
			m_tBrdVer[wIndex].Clear();
		}
	}
	EMBrdType GetBrdType(u16 wIndex)
	{
		return m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
	}

	u16	GetEqpID(u16 wIndex, u16 wMdlIndex)
	{
		return m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId;
	}

	void SetBrdRegInfo(TBrdStateInfo& tBrdState, u16 wIndex)
	{
		m_atBrdCfg[wIndex].m_bReg = tBrdState.m_bReg;
		memcpy(m_atBrdCfg[wIndex].m_abEqpReg, tBrdState.m_abEqpReg, sizeof(m_atBrdCfg[wIndex].m_abEqpReg));
	}

	BOOL32 IsBrdReg(u16 wIndex)
	{
		return m_atBrdCfg[wIndex].m_bReg;
	}


	void SetBrdUsedInfo(BOOL32& bUsed, u16 wIndex)
	{
		m_atBrdCfg[wIndex].m_bBrdUsed = bUsed;
	}
	//根据层号槽位号计算出单板信息存储在数组中的索引
	u16 FindBrdIndex(u8 byBrdLayer, u8 byBrdSlot)
	{
		//单板的层号槽位号从0开始
		u16 wIndex = TP_INVALID_INDEX;
		wIndex = byBrdLayer * TP_BOARD_MAX_SLOT + byBrdSlot;
		return wIndex;
	}

	//单板操作
	BOOL32 AddBoard(TTPBrdCfg tBrdCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdCfg, &tBrdCfg,sizeof(TTPBrdCfg));
		return TRUE;
	}

	//删除单板
	TTPBrdCfg* DelBoard(u16 wIndex)
	{
		m_atBrdCfg[wIndex].m_tBrdCfg.m_byBrdID = (u8)TP_INVALID_INDEX;
// 		m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = (u8)TP_INVALID_INDEX;
// 		m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = (u8)TP_INVALID_INDEX;
		m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = 0;
		m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
		for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_BRD_MAXNUM_EQP; wMdlIndex++)
		{
			if ( 0 != m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId )
			{
				u16 wNum = m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId - EQP_ID_VMP_BEG;
				m_abEqp[wNum] = FALSE;
			}
			m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_emEqpType = em_unknow_mdl;
			memset(m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_szEqpAlias, 0, sizeof(TP_MAX_ALIAS_LEN));
			m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId = 0;
		}
		//板卡删除，清除ftp和telnet状态
		m_tBrdTelFtpStat[wIndex].Clear();
		return (&m_atBrdCfg[wIndex].m_tBrdCfg);
	}

	//修改单板
	void ModifyBoard(TTPBrdCfg tBrdCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdCfg, &tBrdCfg, sizeof(TTPBrdCfg));
	}
	//单板模式操作
	u16 AddBrdMode(TTPMdlCfg tBrdModeCfg, u16 wIndex)
	{
		for (u16 wModeIndex = 0; wModeIndex < TP_UMS_BRD_MAXNUM_EQP; wModeIndex++)
		{
			if (em_unknow_mdl == m_atBrdCfg[wIndex].m_tBrdMode[wModeIndex].m_emEqpType)
			{
				memcpy(&m_atBrdCfg[wIndex].m_tBrdMode[wModeIndex], &tBrdModeCfg, sizeof(TTPMdlCfg));
				return wModeIndex;
			}
		}
		return TP_UMS_BRD_MAXNUM_EQP;
	}
	void AddBrdMode(TTPMdlCfg* ptMdlCfg, u16 wIndex)
	{
		if (NULL != ptMdlCfg)
		{
			memcpy(m_atBrdCfg[wIndex].m_tBrdMode, ptMdlCfg, sizeof(TTPMdlCfg) * TP_UMS_BRD_MAXNUM_EQP);
		}
	}
	//删除单板模式，此接口针对删除某个
	void DelBrdMode(u16 wIndex, u16 wMdlIndex)
	{
		m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_emEqpType = em_unknow_mdl;
		memset(m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_szEqpAlias, 0, sizeof(m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_szEqpAlias));
		m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId = 0;
	}
	//此接口针对删除所有外设
	void DelBrdMode(u16 wIndex)
	{
		for (u8 byIndex = 0; byIndex < TP_UMS_BRD_MAXNUM_EQP; byIndex++)
		{
			m_atBrdCfg[wIndex].m_tBrdMode[byIndex].Clear();
		}
		if (em_eapu_brd == GetBrdType(wIndex))
		{
			m_atBrdCfg[wIndex].m_tBrdMode[0].m_byAudmixNum = TP_APU2_MAX_CHAN_NUM;
		}
	}
	//修改单板模式
	void ModifyBrdMode(TTPMdlCfg* ptMdlCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdMode, ptMdlCfg, sizeof(TTPMdlCfg) * TP_UMS_BRD_MAXNUM_EQP);
	}
	
	//单板类型与外设类型匹配
	BOOL32 BrdTypeCheck(EMBrdType emBrdType, TTPMdlCfg atMdlCfg[], u16 wEqpNum, EMEqpType& emErrorType)
	{
		for ( u16 wIndex = 0; wIndex < wEqpNum; wIndex ++ )
		{
			switch (emBrdType)
			{
			case em_unknow_brd:
				//外设类型未知
				if ( atMdlCfg[wIndex].m_emEqpType != em_unknow_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_eapu_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_audmix_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_mpc_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_mpc_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_mpu2ecard_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_bas_mdl && atMdlCfg[wIndex].m_emEqpType != em_vmp_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_hdu2_brd:
			case em_hdu2_qt_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_hdu_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_is22_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_dataswitch_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_cri2_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_dataswitch_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_mpu2_tp_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_vmp_tp_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_apu2_tp_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_audbas_mdl && atMdlCfg[wIndex].m_emEqpType != em_audmix_mdl )
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			case em_mpu2basic_brd:
				if ( atMdlCfg[wIndex].m_emEqpType != em_bas_mdl && atMdlCfg[wIndex].m_emEqpType != em_vmp_mdl)
				{
					emErrorType = atMdlCfg[wIndex].m_emEqpType;
					return FALSE;
				}
				break;
			default:
				break;
			}
		}

		return TRUE;
	}
	//检查该单板是否配置模式,配置返回TRUE
	BOOL32 CheckBrdIsCfgMdl(u16 wBrdIndex)
	{
		for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_BRD_MAXNUM_EQP; wMdlIndex++)
		{
			if (em_unknow_mdl == m_atBrdCfg[wBrdIndex].m_tBrdMode[wMdlIndex].m_emEqpType)
			{
				continue;
			}
			return TRUE;
		}
		return FALSE;
	}

	//为模式产生eqpid
	u16 MakeMdlEqpId(const EMEqpType& emMdlType )
	{
		u16 wLowIndex, wHighIndex;
		switch(emMdlType)
		{
		case em_vmp_mdl:
			{
				wLowIndex = EQP_ID_VMP_BEG;
				wHighIndex = EQP_ID_BAS_BEG;
			}
			break;
		case em_bas_mdl:
			{
				wLowIndex = EQP_ID_BAS_BEG;
				wHighIndex = EQP_ID_AUD_MIX_BEG;
			}
			
			break;
		case em_audmix_mdl:
			{
				wLowIndex = EQP_ID_AUD_MIX_BEG;
				wHighIndex = EQP_ID_AUD_BAS_BEG;
			}
			break;
		case em_audbas_mdl:
			{
				wLowIndex = EQP_ID_AUD_BAS_BEG;
				wHighIndex = EQP_ID_TOTAL_END;
			}
			break;
		default:
			{
				wLowIndex = EQP_ID_TOTAL_END;
				wHighIndex = EQP_ID_TOTAL_END;
			}
			break;
		}

		for (wLowIndex; wLowIndex < wHighIndex; wLowIndex++)
		{
			if (!m_abEqp[wLowIndex - EQP_ID_VMP_BEG])
			{
				m_abEqp[wLowIndex - EQP_ID_VMP_BEG] = TRUE;
				return wLowIndex;
			}
		}
		return 0;
	}
}THandelBoard;

//处理从维护工具过来的单板信息
class CUmsBoardHandleService:public CTpHandler
{
public:
	CUmsBoardHandleService(CTpObject* pcObject);
	~CUmsBoardHandleService();

public:
	virtual BOOL32 Handler(CTpMsg *const ptMsg);
	virtual BOOL32 Create();
public:
	void ShowBoard();
protected:
	/*处理维护工具用户登录消息*/
	void EventLogin(u8* pDataBuf, u16 wDataSize);
	/*处理添加单板消息*/
	void EventAddBoard(u8* pDataBuf, u16 wDataSize);
	/*处理删除单板消息*/
	void EventDelBoard(u8* pDataBuf, u16 wDataSize);
	/*处理修改单板消息*/
	void EventModifyBoard(u8* pDataBuf, u16 wDataSize);

	/*处理删除单板模式消息*/
	void EventDelBoardMode(u8* pDataBuf, u16 wDataSize);
	/*处理修改单板模式消息*/
	void EventModifyBoardMode(u8* pDataBuf, u16 wDataSize);

	//重启单板
	void EventBrdReoot(u8* pDataBuf, u16 wDataSize);
	//升级单板
	void EventBrdUpGrade(u8* pDataBuf, u16 wDataSize);
	void EventBrdUpdateAck(u8* pDataBuf, u16 wDataSize);
	void EventUpdateTaskReturn(u8* pDataBuf, u16 wDataSize);
	void EventBoardVerAck(u8* pDataBuf, u16 wDataSize);
	//外设占用情况
	void EventAudiomixUsed(u8* pDataBuf, u16 wDataSize);
	void EventVmpUsed(u8* pDataBuf, u16 wDataSize);
	void EventBasUsed(u8* pDataBuf, u16 wDataSize);

	void EventXmpuResUsed(u8* pDataBuf, u16 wDataSize);
    //Telnet和ftp开关
	void EventSwitchTelnetFtp(u8* pDataBuf, u16 wDataSize);

	// 统一
	void EventEqpUsedReq(u8* pDataBuf, u16 wDataSize);
protected:
	//处理eqp过来单板状态消息
	void EventBrdRegResult(u8* pDataBuf, u16 wDataSize);
	void EventBrdModeRegResult(u8* pDataBuf, u16 wDataSize);
	void EventBrdDisc(u8* pDataBuf, u16 wDataSize);
	void EventBrdUsed(u8* pDataBuf, u16 wDataSize);
	//开关telnet Ftp结果
	void EventBrdSwitchTelFtpRes(u8* pDataBuf, u16 wDataSize); 

private:
	/*从umscfg.ini文件中读取单板信息*/
	void ReadBrdInfoFromUmsCfg();
	/*更新配置文件信息*/
	void UpdateBrdCfgInfo(u16 wBrdIndex);

private:
	void	NotifyBrdInfoToTool(TBrdStateInfo& tBrd, u16 wIndex);//通知单板信息给维护工具界面
	void	UpdateBrdInfoToEqp(BOOL32 bUsed, u16 wBrdIndex);    //更新相应单板信息到eqp
	void	CountUiBrdLocation(u16 wIndex, TTPBrdInfo& tUiInfo);//根据数组索引，计算界面层号 槽号
	u8		CountBrdSavedSlot(u8 bySlot, EMBrdType emType);		//计算板子存储的槽位号

	u8      CountUiSlotbySaveSlot(u8 bySlot, EMBrdType emType); // 上述的一个逆运算

	void    TelnetFtpStatNty(u16 wBrdIndex,EmBoardSwitchType emBrdSwitchType);

private:
	void	ReadMpcInfo();						 //Creat时，读取IS2.2信息
	BOOL32	UpdateMpcBrd(TTPBrdUpGrade tBrd);

public:
	void    SwitchMpcTelnetFtp(EmBoardSwitchType emBrdSwitchType, BOOL32 bBrdSwitch);  //主控板开关Telnet Ftp

    
private:
	EmTpBoardRet	SingleBrdMdlHandler(EMBrdType emType, u16 wBrdIndex);//单模式板子处理
	BOOL32			IsBrdSingleMdl(EMBrdType emType);
	BOOL32			NeedStateNty(u16 wBrdIndex, BOOL32 abState[]);
	BOOL32			IsModifiedSame(TTPMdlCfg tSrc[], TTPMdlCfg tDst[]);
private:
	BOOL32	m_bIsUpdate;   //升级标识
	BOOL32  m_bSshSwitch;  //ssh开关状态
protected:
	THandelBoard	m_tHandleBoard;  //操作单板
	u16				m_wMpcBrdIndex;
};

class CUmsMainBoardUpdateTask
{
public:
	CUmsMainBoardUpdateTask();
	~CUmsMainBoardUpdateTask();
public:
	BOOL32	BrdFileIsUngz(s8 * const sFileName);				//主控板子升级文件是否为压缩包
	BOOL32	UpdateMpc2BoardLinuxSys(s8 * const szFileName);		//.gz包升级
	BOOL32	UpdateMpc2BoardLinuxSys_Ungz(s8 * const szFileName);	//.bin包升级
	BOOL32	Mpc2SysUpGrade(s8* pszFileName);					//主控板卡升级
	BOOL32	RemoveFile(const s8* pszFileName);				//删除文件
public:
	s8*		GetUpdateName() { return m_achFileName; }
	void	SetUpdateName(s8* pszName);
	void	Clear() { memset(m_achFileName, 0, sizeof(m_achFileName)); }
private:
	s8	m_achFileName[TP_UPGRADE_FILENAME_LENGTH];
};
#endif