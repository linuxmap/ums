#ifndef HANDLE_BOARD_SERVICE_H
#define HANDLE_BOARD_SERVICE_H

#include "tphandle.h"
#include "umsinnerstruct.h"

#define UPDATE_SUCCESS			0			//�����ɹ�
#define UPDATE_APP_ERROR		1			//app ��������
#define UPDATE_0S_ERROR			2			//OS ��������
#define UPDATE_BOOT_ERROR		3			//Boot ��������
#define UPDATE_SET_FLAG_ERROR	4			//Set Flag ��������
#define UPDATE_ERROR			-1			//����ʧ��

typedef struct tagTTPBrdRegRes
{
	u8       m_byBrdLayer; //���
	u8       m_byBrdSlot;  //�ۺ�
	BOOL32   m_bReg;       //�����Ƿ�ע��
	BOOL32   m_bModeReg;   //ҵ���Ƿ�ע��
	
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
	TBrdVersion		  m_tBrdVer[TP_BOARD_MAX_NUM]; //�汾
    TTelnetFtpStatus  m_tBrdTelFtpStat[TP_BOARD_MAX_NUM];//telnet��ftp����״̬
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
	//���ݲ�Ų�λ�ż����������Ϣ�洢�������е�����
	u16 FindBrdIndex(u8 byBrdLayer, u8 byBrdSlot)
	{
		//����Ĳ�Ų�λ�Ŵ�0��ʼ
		u16 wIndex = TP_INVALID_INDEX;
		wIndex = byBrdLayer * TP_BOARD_MAX_SLOT + byBrdSlot;
		return wIndex;
	}

	//�������
	BOOL32 AddBoard(TTPBrdCfg tBrdCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdCfg, &tBrdCfg,sizeof(TTPBrdCfg));
		return TRUE;
	}

	//ɾ������
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
		//�忨ɾ�������ftp��telnet״̬
		m_tBrdTelFtpStat[wIndex].Clear();
		return (&m_atBrdCfg[wIndex].m_tBrdCfg);
	}

	//�޸ĵ���
	void ModifyBoard(TTPBrdCfg tBrdCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdCfg, &tBrdCfg, sizeof(TTPBrdCfg));
	}
	//����ģʽ����
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
	//ɾ������ģʽ���˽ӿ����ɾ��ĳ��
	void DelBrdMode(u16 wIndex, u16 wMdlIndex)
	{
		m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_emEqpType = em_unknow_mdl;
		memset(m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_szEqpAlias, 0, sizeof(m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_szEqpAlias));
		m_atBrdCfg[wIndex].m_tBrdMode[wMdlIndex].m_wEqpId = 0;
	}
	//�˽ӿ����ɾ����������
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
	//�޸ĵ���ģʽ
	void ModifyBrdMode(TTPMdlCfg* ptMdlCfg, u16 wIndex)
	{
		memcpy(&m_atBrdCfg[wIndex].m_tBrdMode, ptMdlCfg, sizeof(TTPMdlCfg) * TP_UMS_BRD_MAXNUM_EQP);
	}
	
	//������������������ƥ��
	BOOL32 BrdTypeCheck(EMBrdType emBrdType, TTPMdlCfg atMdlCfg[], u16 wEqpNum, EMEqpType& emErrorType)
	{
		for ( u16 wIndex = 0; wIndex < wEqpNum; wIndex ++ )
		{
			switch (emBrdType)
			{
			case em_unknow_brd:
				//��������δ֪
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
	//���õ����Ƿ�����ģʽ,���÷���TRUE
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

	//Ϊģʽ����eqpid
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

//�����ά�����߹����ĵ�����Ϣ
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
	/*����ά�������û���¼��Ϣ*/
	void EventLogin(u8* pDataBuf, u16 wDataSize);
	/*������ӵ�����Ϣ*/
	void EventAddBoard(u8* pDataBuf, u16 wDataSize);
	/*����ɾ��������Ϣ*/
	void EventDelBoard(u8* pDataBuf, u16 wDataSize);
	/*�����޸ĵ�����Ϣ*/
	void EventModifyBoard(u8* pDataBuf, u16 wDataSize);

	/*����ɾ������ģʽ��Ϣ*/
	void EventDelBoardMode(u8* pDataBuf, u16 wDataSize);
	/*�����޸ĵ���ģʽ��Ϣ*/
	void EventModifyBoardMode(u8* pDataBuf, u16 wDataSize);

	//��������
	void EventBrdReoot(u8* pDataBuf, u16 wDataSize);
	//��������
	void EventBrdUpGrade(u8* pDataBuf, u16 wDataSize);
	void EventBrdUpdateAck(u8* pDataBuf, u16 wDataSize);
	void EventUpdateTaskReturn(u8* pDataBuf, u16 wDataSize);
	void EventBoardVerAck(u8* pDataBuf, u16 wDataSize);
	//����ռ�����
	void EventAudiomixUsed(u8* pDataBuf, u16 wDataSize);
	void EventVmpUsed(u8* pDataBuf, u16 wDataSize);
	void EventBasUsed(u8* pDataBuf, u16 wDataSize);

	void EventXmpuResUsed(u8* pDataBuf, u16 wDataSize);
    //Telnet��ftp����
	void EventSwitchTelnetFtp(u8* pDataBuf, u16 wDataSize);

	// ͳһ
	void EventEqpUsedReq(u8* pDataBuf, u16 wDataSize);
protected:
	//����eqp��������״̬��Ϣ
	void EventBrdRegResult(u8* pDataBuf, u16 wDataSize);
	void EventBrdModeRegResult(u8* pDataBuf, u16 wDataSize);
	void EventBrdDisc(u8* pDataBuf, u16 wDataSize);
	void EventBrdUsed(u8* pDataBuf, u16 wDataSize);
	//����telnet Ftp���
	void EventBrdSwitchTelFtpRes(u8* pDataBuf, u16 wDataSize); 

private:
	/*��umscfg.ini�ļ��ж�ȡ������Ϣ*/
	void ReadBrdInfoFromUmsCfg();
	/*���������ļ���Ϣ*/
	void UpdateBrdCfgInfo(u16 wBrdIndex);

private:
	void	NotifyBrdInfoToTool(TBrdStateInfo& tBrd, u16 wIndex);//֪ͨ������Ϣ��ά�����߽���
	void	UpdateBrdInfoToEqp(BOOL32 bUsed, u16 wBrdIndex);    //������Ӧ������Ϣ��eqp
	void	CountUiBrdLocation(u16 wIndex, TTPBrdInfo& tUiInfo);//����������������������� �ۺ�
	u8		CountBrdSavedSlot(u8 bySlot, EMBrdType emType);		//������Ӵ洢�Ĳ�λ��

	u8      CountUiSlotbySaveSlot(u8 bySlot, EMBrdType emType); // ������һ��������

	void    TelnetFtpStatNty(u16 wBrdIndex,EmBoardSwitchType emBrdSwitchType);

private:
	void	ReadMpcInfo();						 //Creatʱ����ȡIS2.2��Ϣ
	BOOL32	UpdateMpcBrd(TTPBrdUpGrade tBrd);

public:
	void    SwitchMpcTelnetFtp(EmBoardSwitchType emBrdSwitchType, BOOL32 bBrdSwitch);  //���ذ忪��Telnet Ftp

    
private:
	EmTpBoardRet	SingleBrdMdlHandler(EMBrdType emType, u16 wBrdIndex);//��ģʽ���Ӵ���
	BOOL32			IsBrdSingleMdl(EMBrdType emType);
	BOOL32			NeedStateNty(u16 wBrdIndex, BOOL32 abState[]);
	BOOL32			IsModifiedSame(TTPMdlCfg tSrc[], TTPMdlCfg tDst[]);
private:
	BOOL32	m_bIsUpdate;   //������ʶ
	BOOL32  m_bSshSwitch;  //ssh����״̬
protected:
	THandelBoard	m_tHandleBoard;  //��������
	u16				m_wMpcBrdIndex;
};

class CUmsMainBoardUpdateTask
{
public:
	CUmsMainBoardUpdateTask();
	~CUmsMainBoardUpdateTask();
public:
	BOOL32	BrdFileIsUngz(s8 * const sFileName);				//���ذ��������ļ��Ƿ�Ϊѹ����
	BOOL32	UpdateMpc2BoardLinuxSys(s8 * const szFileName);		//.gz������
	BOOL32	UpdateMpc2BoardLinuxSys_Ungz(s8 * const szFileName);	//.bin������
	BOOL32	Mpc2SysUpGrade(s8* pszFileName);					//���ذ忨����
	BOOL32	RemoveFile(const s8* pszFileName);				//ɾ���ļ�
public:
	s8*		GetUpdateName() { return m_achFileName; }
	void	SetUpdateName(s8* pszName);
	void	Clear() { memset(m_achFileName, 0, sizeof(m_achFileName)); }
private:
	s8	m_achFileName[TP_UPGRADE_FILENAME_LENGTH];
};
#endif