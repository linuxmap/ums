#include "handleconftemplateservice.h"
#include "umsobject.h"
#include "umsserver.h"
#include "handlecallservice.h"
#include "umsconfig.h"
#include "tpconfig.h"
#include "umsxmltype.h"
#include "umsapi.h"

#include "innereventumsserver.h"
#include "innereventumscall.h"
#include "innereventregsrv.h"
#include "innereventumsvmp.h"

// 外部消息
#include "eventoutumsconftemplate.h"
#include "eventoutumsbrdvmp.h"
#include "eventoutumscall.h"
#include "eventoutquantum.h"
#include "eventoutcfgex.h"

static s32 PreContractTimerCB(u32 dwTimerId, void* param)
{
    CUmsConfTemplateHandleService* pcRunTimerDB = (CUmsConfTemplateHandleService*)param;
    
    pcRunTimerDB->PrecontractOnTime(dwTimerId);
	return TP_RET_OK;
}



CUmsConfTemplateHandleService::CUmsConfTemplateHandleService(CTpObject* pcObjec)
:CTpHandler(pcObjec)
{
	Init();
}

CUmsConfTemplateHandleService::~CUmsConfTemplateHandleService()
{
	
}

void CUmsConfTemplateHandleService::Init()
{
	m_tHandleConfTemplate.Clear();
	m_bUpTemp = FALSE;

	TConfTemplateLocal tConfTemp;
	tConfTemp.m_wID = 0;
	m_tHandleConfTemplate.Add(tConfTemp,0);//添加ID为0的特殊模板
}


/*==============================================================================
函数名    :  Create
功能      :  初始化会议模板
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
BOOL32 CUmsConfTemplateHandleService::Create()
{
	LoadInfoFromTpCfg();
	return CTpHandler::Create();
}

void CUmsConfTemplateHandleService::LoadInfoFromTpCfg()
{
	//下标对应模版ID，因此需要遍历GET,0号下标对应预定模版不变
	TConfTemplateLocal tConfTemp;
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		if (umsGetConfTempInfo(tConfTemp, wIndex))
		{
			tConfTemp.m_wID = wIndex + 1;
			m_tHandleConfTemplate.Add(tConfTemp,wIndex+1);
		}
	}
}

BOOL32 CUmsConfTemplateHandleService::Handler( CTpMsg *const ptMsg )
{
	u16 wEvent = ptMsg->GetEvent();
	
	if (wEvent == evtp_QtQueryAlias_req)
	{
		EventQueryAlias(ptMsg->GetBody(), ptMsg->GetBodyLen());
		return TRUE;
	}

	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();
	void* pDataBuf = ptMsg->GetBody() + sizeof(TLogUser);
	u16 wSize = ptMsg->GetBodyLen() - sizeof(TLogUser);

	switch( wEvent ) 
	{
	case ev_SysCmsLoginInd:
		{
			EventLogin(pLogUser, pDataBuf, wSize);
		}
		break;

	case ev_UpdateConfTimer:
		{
			EventUpdateConfTimer();
		}
		break;

	case evtp_AddConfTemplate_req1:
		{
			TP_SAFE_CAST(m_tTempBuf.m_tTemplate, (u8*)pDataBuf);

			TTPConfTemplate tTemp;
			m_tTempBuf.GetValue(tTemp);

			EventAddConfReq(pLogUser, &tTemp, sizeof(TTPConfTemplate));
		}
		break;

	case evtp_DelConftemplate_Req:
		{
			EventDelConfReq(pLogUser, pDataBuf, wSize);
		}
		break;
	case ev_del_all_conftemp_req:
		{
			EventDelAllConfReq(pLogUser, pDataBuf, wSize);
		}
		break;
	case evtp_Updateconftemplate_Req1:
		{
			TP_SAFE_CAST(m_tTempBuf.m_tTemplate, (u8*)pDataBuf);
			
			TTPConfTemplate tTemp;
			m_tTempBuf.GetValue(tTemp);

			EventUpdateConfReq(pLogUser, &tTemp, sizeof(TTPConfTemplate));
		}
		break;

	case ev_uploadConftemp_req:
		{
			EventUpLoadConfTemp(pLogUser, pDataBuf, wSize);
		}
		break;

	case ev_uploadConftemp_rsq:
		{
			EventUpLoadConfTempRsq(pLogUser, pDataBuf, wSize);
		}
		break;

	case ev_downloadConftemp_req:
		{
			EventDownLoadConfTemp(pLogUser, pDataBuf, wSize);
		}
		break;

	case ev_downloadConftemp_rsq:
		{
			EventDownLoadConfTempRsq(pLogUser, pDataBuf, wSize);
		}
		break;
	case ev_save_vmpcfg_req:
		{
			EventSaveVmpPlan(pLogUser, pDataBuf, wSize);
		}
		break;
	case evtp_AddConfTemplateEx_req:
		{
			EventAddConfExReq(pLogUser, pDataBuf, wSize);
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

void CUmsConfTemplateHandleService::EventSaveVmpPlan(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	TSaveVmpPlanInfo tVmpPlanInfo;
	BOOL32 bRefresh = FALSE;

	TP_SAFE_CAST(tVmpPlanInfo, (u8*)pDataBuf);

	tpHint(Ums_Mdl_Service, ("[EventSaveVmpPlan] ConfID:%d, Style:%d, ConName:%s\n"),tVmpPlanInfo.m_wConfID,tVmpPlanInfo.m_tCfg.m_emStyle,tVmpPlanInfo.m_achConfname);

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		if (0 != strncmp(tVmpPlanInfo.m_achConfname,m_tHandleConfTemplate.m_atTPConfTemplate[wIndex].m_achConfName, TP_MAX_ALIAS_LEN + 1))
		{
			continue;
		}

		if (0 == wIndex) //临时模板不保存
		{
		 	bRefresh = FALSE;
			tpHint(Ums_Mdl_Service, ("[EventSaveVmpPlan] The Template is Temporary template\n"));
			break;
		}
		bRefresh = TRUE;
		m_tHandleConfTemplate.m_atTPConfTemplate[wIndex].m_tVmpCfg = tVmpPlanInfo.m_tCfg ;
		UpdateCfgData(wIndex);
		break;
    }
	if (!bRefresh)
	{
		tpHint(Ums_Mdl_Service, ("[EventSaveVmpPlan] The Template isnot Exist\n"));
	}

	//返回umscall
	CTpMsg cMsg;
	cMsg.SetEvent(ev_Save_VmpCfg_Ack);
	cMsg.SetBody(&tVmpPlanInfo.m_wCfgIndex, sizeof(u16));
	cMsg.CatBody(&bRefresh, sizeof(BOOL32));
	cMsg.Post(UMS_CALL_APP_INST(tVmpPlanInfo.m_wConfID), 0, UMS_SERVICE_APP_INST);	
}


void CUmsConfTemplateHandleService::EventQueryAlias(void* pDataBuf, u16 wDataSiz)
{
	TTPQTQueryData tQuerydata;
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, (u8*)pDataBuf);
	TP_SAFE_CAST(tQuerydata, (u8*)pDataBuf + sizeof(tHandle));
	
	EmQueryAliasRes emRes = emQueryFailed;
	
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsCallHandleService* pConfService = (CUmsCallHandleService*)pServer->GetService(CTpUmsServer::_CUmsCallHandleService);
	
	
	u8 abBuf[sizeof(TUmsHandle)+sizeof(TTPQTQueryData)+sizeof(EmQueryAliasRes)+sizeof(EmTPConfEncFrequency)] = {0};
	memcpy(abBuf, &tHandle, sizeof(tHandle));
	memcpy(abBuf+sizeof(TUmsHandle), &tQuerydata, sizeof(TTPQTQueryData));
	
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{			
		if (0 == strcmp(tQuerydata.m_szAlias, m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_achConfName)|| 
			0 == strcmp(tQuerydata.m_szAlias, m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_achConfE164))
		{
			if (m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_tEncrypt.IsQt())
			{
				EmTPConfEncFrequency emQtLev = m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_tEncrypt.GetQtLevl();
				memcpy(abBuf+sizeof(TUmsHandle)+sizeof(TTPQTQueryData)+sizeof(EmQueryAliasRes), 
					&emQtLev, sizeof(EmTPConfEncFrequency));
				
				//覆盖别名 底层库 统一用别名
				memcpy(tQuerydata.m_szAlias, m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_achConfName, sizeof(tQuerydata.m_szAlias));
				memcpy(abBuf+sizeof(TUmsHandle), &tQuerydata, sizeof(TTPQTQueryData));
				
				tHandle.handAppCall = pConfService->GetConf(&m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1]);
				memcpy(abBuf, &tHandle, sizeof(tHandle));
				
				emRes = emQuerySuccess;
			}
			break;
		}
	}
	memcpy(abBuf+sizeof(TUmsHandle)+sizeof(TTPQTQueryData), &emRes, sizeof(EmQueryAliasRes));
	
	tpHint(Ums_Mdl_Service, "EventQueryAlias Index:%d, Alias:%s, Ret:%d(0:success).\n", tQuerydata.m_wIndex, tQuerydata.m_szAlias, emRes);
	
	NotifyCall(evtp_QtQueryAlias_rsp, abBuf, sizeof(abBuf));
}



void CUmsConfTemplateHandleService::EventDownLoadConfTempRsq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSiz)
{
	tpHint(Ums_Mdl_Service,"[EventDownLoadConfTempRsq] Download template file end.\n");

	TpNotifyMsgToToolUserFromService(ev_downloadConftemp_rsq, pDataBuf, wDataSiz);
}

void CUmsConfTemplateHandleService::EventDownLoadConfTemp(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	umsDownLoadConTemp();
}

void CUmsConfTemplateHandleService::EventUpLoadConfTempRsq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	BOOL32 bRet = FALSE;
	TP_SAFE_CAST(bRet, (u8*)pDataBuf);

	if ( !bRet )
	{
		MdlError(Ums_Mdl_Service, ("EventUpLoadConfTempRsq return failed! Try! m_bUpTemp:%d\n", m_bUpTemp));
		m_bUpTemp = FALSE;
		TpNotifyMsgToToolUserFromService(ev_uploadConftemp_rsq, &bRet, sizeof(bRet));
		return ;
	}

	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	
	TConfTemplateLocal* atTmpConfTemplate = new TConfTemplateLocal[TP_CONFTEMPLATE_MAXNUM+1];
	
	memcpy(atTmpConfTemplate, m_tHandleConfTemplate.m_atTPConfTemplate, sizeof(m_tHandleConfTemplate.m_atTPConfTemplate));
	u16 wOldTempValidNum = m_tHandleConfTemplate.Size();
	Init();
	LoadInfoFromTpCfg();

	//导入成功后主动去全组注册，umsserver会先取消，再根据新模板重新注册
	MdlHint(Ums_Mdl_Service, ("EventUpLoadConfTempRsq all template reg.\n"));
	EmRegGroupNum emRegNum = em_AllGroup;
	pServer->NotifySelf(evtp_ums_reg_req, (u8*)&emRegNum, sizeof(EmRegGroupNum));

	//更新UMC界面
	TLogUser tUser;
	u8 abyBuf[sizeof(tagTTPConfTemplate) + sizeof(BOOL32)] = {0};

	u16 wNeedUpdateNum = 0;
	
	BOOL32 bRefresh = FALSE;
	BOOL32 abFlag[TP_CONFTEMPLATE_MAXNUM + 1] = {FALSE};
	u16 wIndex = 0;

	for (wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{//横向为导入后的模板信息，纵向为原模板信息
		if (TP_INVALID_INDEX == m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1].m_wID)
		{
			continue;
		}
		u16 wConfNameLen = strlen(m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1].m_achConfName);
		for (u16 wDndex = 0; wDndex < TP_CONFTEMPLATE_MAXNUM; wDndex++)
		{
			if (TP_INVALID_INDEX == atTmpConfTemplate[wDndex + 1].m_wID)
			{
				continue;
			}

			if (wConfNameLen > 0 && 
				(0 == strcmp(m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1].m_achConfName, atTmpConfTemplate[wDndex + 1].m_achConfName)))
			{//更新
				wNeedUpdateNum++;
				abFlag[wIndex + 1] = TRUE;
				break;
			}
		}
	}

	delete[] atTmpConfTemplate;
	atTmpConfTemplate = NULL;

	u16 wUpdateSucceedNum = wNeedUpdateNum;
	u16 wNeedAddNum = m_tHandleConfTemplate.Size() - wNeedUpdateNum;
	u16 wAddFailNum = 0;
	BOOL32 bUpdateRefresh = FALSE;
	TTPConfTemplateBuf tTemp;
	for (wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		//发ID有效的给界面,不包括0号
		if( TP_INVALID_INDEX == m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_wID )
		{
			continue;
		}
		
		tTemp.Clear();
		if (abFlag[wIndex + 1])
		{
			wNeedUpdateNum--;
			if (0 == wNeedUpdateNum)
			{
				bRefresh = TRUE;
			}

			tTemp.SetValue(m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1]);
			bRefresh = htonl(bRefresh);
//			TpNotifyMsgToUeFromService(evtp_Updateconftemplate_Notify, &tTemp.m_tTemplate1, sizeof(tTemp.m_tTemplate1), *ptLogUser);
			memcpy(abyBuf, &tTemp.m_tTemplate, sizeof(tTemp.m_tTemplate));
			memcpy(abyBuf + sizeof(tTemp.m_tTemplate), &bRefresh, sizeof(BOOL32));
			TpNotifyMsgToUeFromService(evtp_Updateconftemplate_Notify1, abyBuf, sizeof(abyBuf), *ptLogUser);
				
		}
		else
		{
			wNeedAddNum--;
			if (0 == wNeedAddNum)
			{
				bUpdateRefresh = TRUE;
			}

			if (TP_CONFTEMPLATE_MAXNUM <= wOldTempValidNum)
			{
				wAddFailNum++;
				continue;
			}
			wOldTempValidNum++;

			tTemp.SetValue(m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1]);
			bUpdateRefresh = htonl(bUpdateRefresh);
			memcpy(abyBuf, &tTemp.m_tTemplate, sizeof(tTemp.m_tTemplate));
			memcpy(abyBuf + sizeof(tTemp.m_tTemplate), &bUpdateRefresh, sizeof(BOOL32));
			TpNotifyMsgToUeFromService(evtp_AddConftemplate_Notify1, abyBuf, sizeof(abyBuf), *ptLogUser);
		}
	}
	
	u16 wAddNewNum = m_tHandleConfTemplate.Size() - wUpdateSucceedNum - wAddFailNum;
	
	TpNotifyMsgToToolUserFromService(ev_uploadConftemp_rsq, &bRet, sizeof(bRet));

	tpHint(Ums_Mdl_Service,"[EventUpLoadConfTempRsq] Upload template file end. m_bUpTemp:%d \n", m_bUpTemp);
	m_bUpTemp = FALSE;
}

void CUmsConfTemplateHandleService::EventUpLoadConfTemp(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	if (GETAPP(ptLogUser->m_dwUserInst) != AID_UMSTOOL2UMS_APP)
	{
		return ;
	}

	m_bUpTemp = TRUE;

	s8 szFileName[TP_UPLOAD_FILE_NAME_LENGTH + 1] = {0};
	memcpy(szFileName, pDataBuf, wDataSize);

	tpHint(Ums_Mdl_Service,"[EventUpLoadConfTemp] FileName:%s, m_bUpTemp:%d\n", szFileName, m_bUpTemp);

	umsUpLoadConfTempFile(szFileName);

// 导入前无需取消取消，导入成功后，再进行全组注册即可
// 	//导入前 取消注册
// 	MdlHint(Ums_Mdl_Service, ("EventUpLoadConfTemp unreg all template\n"));
// 	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
// 	TCnsRegInfo tReg;
// 	pServer->NotifySelf(evtp_ums_unreg_req, (u8*)&tReg, sizeof(tReg));	

	return;
}

void CUmsConfTemplateHandleService::EventLogin(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	BOOL32 bRefresh = FALSE;
	u8 abyBuf[sizeof(TTPConfTemplate) + sizeof(BOOL32)] = {0};

	TTPConfTemplateBuf tTmp;
	TTPConfTemplate tTmplate;
	TTemplateConfEx tTempex;
	u16 wSize = m_tHandleConfTemplate.Size();
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		//发ID有效的给界面,不包括0号
		if( TP_INVALID_INDEX == m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_wID)
		{
			continue;
		}
	
		wSize--;
		if (0 == wSize)
		{
			bRefresh = TRUE;
		}

		memcpy(&tTmplate, &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1], sizeof(TTPConfTemplate));

		tTmp.SetValue(tTmplate);
		bRefresh = htonl(bRefresh);
		memcpy(abyBuf, &tTmp.m_tTemplate, sizeof(tTmp.m_tTemplate));
		memcpy(abyBuf + sizeof(tTmp.m_tTemplate), &bRefresh, sizeof(BOOL32));
		TpNotifyMsgToUeFromService(evtp_AddConftemplate_Notify1, abyBuf, sizeof(abyBuf), *ptLogUser);

		if (TP_INVALID_INDEX != m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_tTempCfgEx.m_wTempID)
		{
			memcpy(&tTempex,&m_tHandleConfTemplate.m_atTPConfTemplate[wIndex +1].m_tTempCfgEx,sizeof(TTemplateConfEx));
		    TpNotifyMsgToUeFromService(evtp_AddConfTemplateEx_Notify, &tTempex, sizeof(TTemplateConfEx), *ptLogUser);
		}

	}
	return;
}

void CUmsConfTemplateHandleService::EventAddConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	TTPConfTemplate tConfTmp;
	TP_SAFE_CAST(tConfTmp, (u8*)pDataBuf);
	u16 wPosition = TP_INVALID_INDEX;
	if (0 == strcmp(tConfTmp.m_achConfName, tConfTmp.m_achConfE164))
	{
		tConfTmp.m_achConfName[0] = '\0';
	}

	TOprConfTmpResult tRet;
	tRet.m_emReason = TP_ConfTemplate_AddSuccess;

	TTPConfTemplate* ptConf = NULL;
	do 
	{
		if ( m_bUpTemp )
		{
			tRet.m_emReason = TP_ConfTemplate_TmpUpIng;
			break;
		}

		u16 wConfNameLen = strlen(tConfTmp.m_achConfName);
		u16 wE164Len = strlen(tConfTmp.m_achConfE164);
		if (wConfNameLen == 0 && wE164Len == 0)
		{
			tRet.m_emReason = TP_ConfTemplate_ParamInValid;
			break;
		}

		for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
		{			
			if ( wConfNameLen > 0 && 0 == strcmp(tConfTmp.m_achConfName, m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_achConfName)
				|| wE164Len > 0 && 0 == strcmp(tConfTmp.m_achConfE164, m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_achConfE164))
			{
				tRet.m_emReason = TP_ConfTemplate_E164Repeat;
				break;
			}
		}

		if (TP_ConfTemplate_AddSuccess != tRet.m_emReason)
		{
			break;
		}

		//查找位置并添加
		wPosition = m_tHandleConfTemplate.FindIdle();
		if (TP_INVALID_INDEX == wPosition)
		{
			tRet.m_emReason = TP_ConfTemplate_MaxNum;
			break;
		}
		//处理模板加密
		if (emTPEncryptTypeNone != tConfTmp.m_tEncrypt.m_emEncryptModel  &&
			!tConfTmp.m_tEncrypt.IsQt() &&
			TRUE == tConfTmp.m_bDefaultEncrypt)
		{
			static const s8 achkeysrc[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			srand(time(0));
			
			for (u16 wCount = 0; wCount < TP_ENCRYPT_KEY_LEN; wCount++)
			{
				tConfTmp.m_tEncrypt.m_achEncKey[wCount] = (s8)achkeysrc[rand()%strlen(achkeysrc)] ;			
			}
			tConfTmp.m_tEncrypt.m_achEncKey[TP_ENCRYPT_KEY_LEN] = '\0';
		}
		tConfTmp.m_tEncrypt.m_byKeyLen = strlen(tConfTmp.m_tEncrypt.m_achEncKey);

		tConfTmp.m_wID = wPosition;
		m_tHandleConfTemplate.Add(tConfTmp,wPosition);

		ptConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wPosition];

		tRet.m_emReason = TP_ConfTemplate_AddSuccess;
		tRet.m_wID = ptConf->m_wID;

		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();

//处理预约会议
		if (0 == ptConf->m_tStartTime)
		{
			break;
		}

		time_t CurTime;
		time(&CurTime);
		s32 interval = ptConf->m_tStartTime - CurTime;
		if (interval <= 10) 
		{
			break;
		}

		ptConf->m_dwTimeID = pServer->AddTimer(interval, (u32)PreContractTimerCB, this);
		
		tpHint(Ums_Mdl_Service,"[Add]m_dwTimeID = %d\n", ptConf->m_dwTimeID);
		if (0 == ptConf->m_dwTimeID)
		{
			MdlError(Ums_Mdl_Service, ("EventAddConfReq AddTimer Failed. confid:%d\n", tRet.m_wID));
			break;
		}

	} while (0);

	if (TP_ConfTemplate_AddSuccess == tRet.m_emReason)
	{

		UpdateCfgData(wPosition);
		SendNewReg(wPosition);

		TLogUser tUserTmp;
		TTPConfTemplateBuf tTmp;

		tTmp.SetValue(*ptConf);

		u8 abyBuf[sizeof(TTPConfTemplate) + sizeof(BOOL32)] = {0};
		memcpy(abyBuf, &tTmp.m_tTemplate, sizeof(TTPConfTemplate));
		BOOL32 bRefresh = TRUE;
		bRefresh = htonl(bRefresh);
		memcpy(abyBuf + sizeof(TTPConfTemplate), &bRefresh, sizeof(BOOL32));

		TpNotifyMsgToUeFromService(evtp_AddConftemplate_Notify1, abyBuf, sizeof(abyBuf), tUserTmp);
	}
	
	TpNotifyMsgToUeFromService(evpt_OperatorConfTemplate_Ret, &tRet, sizeof(tRet), *ptLogUser);

	return;
}


void CUmsConfTemplateHandleService::EventDelConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	u16 wConfID = *(u16*)pDataBuf;
	TConfTemplateLocal *pConfTemp;
	TOprConfTmpResult tRet;
	tRet.m_wID = wConfID;
	tRet.m_emReason = TP_ConfTemplate_DelSuccess;
	do 
	{
		if ( m_bUpTemp )
		{
			tRet.m_emReason = TP_ConfTemplate_TmpUpIng;
			break;
		}

		//临时会议不允许被删除
		if (0 == wConfID)
		{
			tRet.m_emReason = TP_ConfTemplate_UnFindConf;
			break;
		}

		//越界保护
		if (wConfID>TP_CONFTEMPLATE_MAXNUM)
		{
			tRet.m_emReason = TP_ConfTemplate_UnFindConf;
			break;
		}

		TConfTemplateLocal tTemplate;
		tTemplate.m_wID = wConfID;
		pConfTemp = m_tHandleConfTemplate.Del(tTemplate);

		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();		
		if ( 0 != pConfTemp->m_dwTimeID )
		{
			tpHint(Ums_Mdl_Service,"[Del]m_dwTimeID = %d\n",pConfTemp->m_dwTimeID);
			pServer->DelTimer(pConfTemp->m_dwTimeID);
		}
		pConfTemp->Clear();
			
	} while (0);

	if (TP_ConfTemplate_DelSuccess == tRet.m_emReason)
	{
		umsDelConfTempInfo(wConfID - 1);
		SendNewReg(wConfID);

		TLogUser tUserTmp;

		TDelRefreshConfTemplate tDelList;
		tDelList.m_wRefreshNum = 1;
		tDelList.m_awTmpList[0] = wConfID;
		TpNotifyMsgToUeFromService(evtp_Delconftemplate_Notify, &tDelList, sizeof(tDelList), tUserTmp);
	}
	MdlHint(Ums_Mdl_Service, ("evtp_Delconftemplate_Notify  . confid:%d\n", tRet.m_wID));
	TpNotifyMsgToUeFromService(evpt_OperatorConfTemplate_Ret, &tRet, sizeof(tRet), *ptLogUser);

	return;
}

namespace UmsTpmsg {
void tplocaltime(struct tm& t, const time_t& ti);
} //namespace UmsTpmsg

void CUmsConfTemplateHandleService::EventUpdateConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	//tmp为要更新的，SRC为以前那各位置的，DST为要比较的别的
	TTPConfTemplate* pConfTmp = (TTPConfTemplate*)pDataBuf;
	TOprConfTmpResult tRet;
	tRet.m_wID = pConfTmp->m_wID;
	BOOL bUpdate = FALSE;
	BOOL32 bSameName = TRUE;

	u16 wIndex = 0;
	MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Begin AudioFormatNum:%d,MainFormatNum:%d, MinorNum:%d.\n", pConfTmp->m_wAudFmtNum,pConfTmp->m_wMainNum, pConfTmp->m_wMinorNum));
	for (wIndex = 0; wIndex < pConfTmp->m_wAudFmtNum; ++wIndex)
	{
		MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Audio Index:%d, Format:%d, Freq:%d, Res:%d.\n", wIndex+1, pConfTmp->m_atAudFmt[wIndex].m_emFormat
			, pConfTmp->m_atAudFmt[wIndex].m_emSampleFreq, pConfTmp->m_atAudFmt[wIndex].m_byReserve1));
	}
	for (wIndex = 0; wIndex < pConfTmp->m_wMainNum; ++wIndex)
	{
		MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Main Index:%d, Quality:%d, Res:%d, Frame:%d.\n", wIndex+1, pConfTmp->m_atTpMainVideoRes[wIndex].m_emQualityLvl
								, pConfTmp->m_atTpMainVideoRes[wIndex].m_emRes, pConfTmp->m_atTpMainVideoRes[wIndex].m_wFrameRate));
	}
	for (wIndex = 0; wIndex < pConfTmp->m_wMinorNum; wIndex++)
	{
		MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Minor Index:%d, Quality:%d, Res:%d, Frame:%d.\n", wIndex+1, pConfTmp->m_atTpMinorVideoRes[wIndex].m_emQualityLvl
								, pConfTmp->m_atTpMinorVideoRes[wIndex].m_emRes, pConfTmp->m_atTpMinorVideoRes[wIndex].m_wFrameRate));
	}
	struct tm t;
	tplocaltime(t, pConfTmp->m_tStartTime);
	MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq ID:%d,Time:%4.4u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u\n"
		, pConfTmp->m_wID, t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec));
	
	TTPConfTemplate* ptSrcConf = NULL;	//yuan
	do 
	{
		if ( m_bUpTemp )
		{
			tRet.m_emReason = TP_ConfTemplate_TmpUpIng;
			break;
		}

		//越界保护
		if(pConfTmp->m_wID>TP_CONFTEMPLATE_MAXNUM)
		{
			tRet.m_emReason = TP_ConfTemplate_UnFindConf;
			break;
		}

		ptSrcConf = &m_tHandleConfTemplate.m_atTPConfTemplate[pConfTmp->m_wID];
		TTPConfTemplate* ptDstConf = NULL;

		//临时ID
		if (0 == ptSrcConf->m_wID)
		{
			memcpy(ptSrcConf,pConfTmp,sizeof(TTPConfTemplate));
			tRet.m_emReason = TP_ConfTemplate_UpdateSuccess;
			break;
		}

		u16 wConfNameLen = 0;
		u16 wConfE164Len = 0;

		BOOL bRepeat = FALSE;
		for (u16 wIndex = 1; wIndex<=TP_CONFTEMPLATE_MAXNUM; wIndex++ )
		{
			ptDstConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex];
			wConfNameLen = strlen(pConfTmp->m_achConfName);
			wConfE164Len = strlen(pConfTmp->m_achConfE164);
			
			if (ptSrcConf->m_wID == wIndex)
			{
				if (((0 != strcmp(pConfTmp->m_achConfName, ptDstConf->m_achConfName) && (wConfNameLen > 0)))
					|| ((0 != strcmp(pConfTmp->m_achConfE164, ptDstConf->m_achConfE164))))   //164号可为空
				{
					bSameName = FALSE;
				}
			}
			else
			{
				if (((0 == strcmp(pConfTmp->m_achConfName, ptDstConf->m_achConfName) && (wConfNameLen > 0)))
					|| ((0 == strcmp(pConfTmp->m_achConfE164, ptDstConf->m_achConfE164))&&(wConfE164Len > 0)))
				{
					tRet.m_emReason = TP_ConfTemplate_E164Repeat;
					bRepeat = TRUE;
					break;
				}
			}
		}		

		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
//处理预约会议
		if (pConfTmp->m_tStartTime != ptSrcConf->m_tStartTime)
		{
			if (ptSrcConf->m_dwTimeID != 0)
			{
				tpHint(Ums_Mdl_Service,"[update]m_dwTimeID = %d\n", ptSrcConf->m_dwTimeID);
				pServer->DelTimer(ptSrcConf->m_dwTimeID);
			}

			time_t CurTime;
			time(&CurTime);
			s32 interval = pConfTmp->m_tStartTime - CurTime;  ///时间修改
			if (interval > 10) 
			{
				pConfTmp->m_dwTimeID = pServer->AddTimer(interval, (u32)PreContractTimerCB, this);
				tpHint(Ums_Mdl_Service,"[updateafteradd]m_dwTimeID = %d\n", pConfTmp->m_dwTimeID);
				if (0 == pConfTmp->m_dwTimeID)
				{
					MdlError(Ums_Mdl_Service, ("EventUpdateConfReq AddTimer Failed. confid:%d\n", ptSrcConf->m_wID));
				}
			}			
		}
		else
		{//把老的timer保留
			pConfTmp->m_dwTimeID = ptSrcConf->m_dwTimeID;
		}

		if(bRepeat)
		{
			break;
		}
		else
		{
			//更新
			if (emTPEncryptTypeNone != pConfTmp->m_tEncrypt.m_emEncryptModel && 
				!pConfTmp->m_tEncrypt.IsQt() &&
				0 == strlen(pConfTmp->m_tEncrypt.m_achEncKey))
			{//加密处理
				static const s8 achkeysrc[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
				srand(time(0));
				
				for (u16 wCount = 0; wCount < TP_ENCRYPT_KEY_LEN; wCount++)
				{
					pConfTmp->m_tEncrypt.m_achEncKey[wCount] = (s8)achkeysrc[rand()%strlen(achkeysrc)] ;			
				}
				pConfTmp->m_tEncrypt.m_achEncKey[TP_ENCRYPT_KEY_LEN] = '\0';

			}
			pConfTmp->m_tEncrypt.m_byKeyLen = strlen(pConfTmp->m_tEncrypt.m_achEncKey);
			m_tHandleConfTemplate.Update(*pConfTmp);
			bUpdate = TRUE;
		}

		tRet.m_emReason = TP_ConfTemplate_UpdateSuccess;

	} while (0);
	
	if (bUpdate)
	{
		UpdateCfgData(pConfTmp->m_wID);
		if (!bSameName)
		{
			SendNewReg(pConfTmp->m_wID);
		}

		TTPConfTemplateBuf tTmp;
		tTmp.SetValue(*pConfTmp);

		TLogUser tUserTmp;

		u8 abyBuf[sizeof(TTPConfTemplate) + sizeof(BOOL32)] = {0};
		memcpy(abyBuf, &tTmp.m_tTemplate, sizeof(tTmp.m_tTemplate));
		BOOL32 bRefresh = TRUE;
		bRefresh = htonl(bRefresh);
		memcpy(abyBuf + sizeof(tTmp.m_tTemplate), &bRefresh, sizeof(BOOL32));

		TpNotifyMsgToUeFromService(evtp_Updateconftemplate_Notify1, abyBuf, sizeof(abyBuf), tUserTmp);
			
		MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq After AudioFormatNum:%d, MainFormatNum:%d, MinorNum:%d.\n",pConfTmp->m_wAudFmtNum, pConfTmp->m_wMainNum, pConfTmp->m_wMinorNum));
		for (wIndex = 0; wIndex < pConfTmp->m_wAudFmtNum; ++wIndex)
		{
			MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Audio Index:%d, AudFormat:%d, Freq:%d, Res:%d.\n", wIndex+1, pConfTmp->m_atAudFmt[wIndex].m_emFormat
				, pConfTmp->m_atAudFmt[wIndex].m_emSampleFreq, pConfTmp->m_atAudFmt[wIndex].m_byReserve1));
			
		}

		for (wIndex = 0; wIndex < pConfTmp->m_wMainNum; ++wIndex)
		{
			MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Main Index:%d, Quality:%d, Res:%d, Frame:%d.\n", wIndex+1, pConfTmp->m_atTpMainVideoRes[wIndex].m_emQualityLvl
					, pConfTmp->m_atTpMainVideoRes[wIndex].m_emRes, pConfTmp->m_atTpMainVideoRes[wIndex].m_wFrameRate));
						
		}
		for (wIndex = 0; wIndex < pConfTmp->m_wMinorNum; wIndex++)
		{
			MdlHint(Ums_Mdl_Service, ("EventUpdateConfReq Minor Index:%d, Quality:%d, Res:%d, Frame:%d.\n", wIndex+1, pConfTmp->m_atTpMinorVideoRes[wIndex].m_emQualityLvl,
				pConfTmp->m_atTpMinorVideoRes[wIndex].m_emRes, pConfTmp->m_atTpMinorVideoRes[wIndex].m_wFrameRate));
		}
	}

	TpNotifyMsgToUeFromService(evpt_OperatorConfTemplate_Ret, &tRet, sizeof(tRet), *ptLogUser);

	return;
}


void CUmsConfTemplateHandleService::EventUpdateConfTimer()
{
	TTPConfTemplate *pConfTmp = NULL;
	
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		pConfTmp = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex];
		
        if ( pConfTmp->m_tStartTime != 0 )
		{
			pServer->DelTimer(pConfTmp->m_dwTimeID);
			
			time_t CurTime;
			time(&CurTime);
			s32 interval = pConfTmp->m_tStartTime - CurTime; 
			if ( interval < 0)
			{
				pConfTmp->m_tStartTime = 0;
			}
			else if (interval > 10) 
			{
				pConfTmp->m_dwTimeID = pServer->AddTimer(interval, (u32)PreContractTimerCB, this);
			}
		}
	}
}


void CUmsConfTemplateHandleService::PrecontractOnTime(u32 dwTimerId)
{
	if (0 == dwTimerId)
	{
		return;
	}

	time_t CurTime;
	time(&CurTime);
	
	TConfTemplateLocal* ptConf = NULL;
	u16 wConfID = TP_INVALID_INDEX;

	for (u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{			
		if (dwTimerId == m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1].m_dwTimeID)
		{
			//ptConf = &Itor;
			ptConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1];
			break;
		}
	}

	TStartConfResult tStartRet;
	tStartRet.m_emReason = TP_StartConf_Success;

	do 
	{
		if(NULL == ptConf)
		{
			tStartRet.m_emReason = TP_StartConf_ConfTemplateUnExist;
			MdlError(Ums_Mdl_Service, ("PrecontractOnTime can not find conf. time:0x%x\n", dwTimerId));
			break;
		}

		tStartRet.m_wConfTemplateID = ptConf->m_wID;
		
		UpDateOnTimeConfOnStart(ptConf->m_wID);
		
		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
		CUmsCallHandleService* pCallService = (CUmsCallHandleService*)pServer->GetService(CTpUmsServer::_CUmsCallHandleService);

		
		wConfID = pCallService->GetConf((TTPConfTemplate*)ptConf);
		if (TP_VALID_HANDLE(wConfID))
		{
			tStartRet.m_emReason = TP_StartConf_ConfExist;
			break;
		}
		
		wConfID = pCallService->GetIdleConf((TTPConfTemplate*)ptConf);
		if (!TP_VALID_HANDLE(wConfID))
		{
			MdlError(Ums_Mdl_Service, ("PrecontractOnTime Ums Conf is FUll. confid:%d\n", wConfID));
			
			tStartRet.m_emReason = TP_StartConf_ConfFull;
			break;
		}

		TCallMgr* ptCallMgr = pCallService->GetCallMgr(wConfID);
		if (NULL == ptCallMgr)
		{
			MdlError(Ums_Mdl_Service, ("PrecontractOnTime Invalid call mgr. ConfID:%d.\n", wConfID));
		}
		else
		{
			ptCallMgr->m_bCallByTimer = TRUE;
		}
	
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsMakeConf);
		cMsg.SetBody(ptConf, sizeof(TConfTemplateLocal));
    	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID));

		pCallService->UpdateRunningConfCount();
	} while (0);

	MdlHint(Ums_Mdl_Service, ("EventStartConfReq ConfTempID:%d, ConfID:%d, ret:(%d->%s)\n"
		, ptConf ? ptConf->m_wID : TP_INVALID_INDEX, wConfID, TpEnumIdString(EmTpStartConfRet, tStartRet.m_emReason)));

    if( tStartRet.m_emReason != TP_StartConf_Success )
	{
	    TLogUser tUserTmp;                                                
	    TpNotifyMsgToUeFromService(evtp_StartConfTemplate_Ret, &tStartRet, sizeof(tStartRet), tUserTmp);
	}

    return;
}

TConfTemplateLocal* CUmsConfTemplateHandleService::GetConfTemplate(const TTpCallAddr&  tDstCallAddr)
{
	u16 wIndex = 0;
	TConfTemplateLocal *pConf = NULL;
	if ( 0 != strlen(tDstCallAddr.m_tAlias.m_abyAlias))
	{
		for(wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++)
		{
			pConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1];
			if(TP_INVALID_INDEX == pConf->m_wID)
			{
				continue;
			}
			if (0 == strcmp(tDstCallAddr.m_tAlias.m_abyAlias, pConf->m_achConfName) 
				|| 0 == strcmp(tDstCallAddr.m_tAlias.m_abyAlias, pConf->m_achConfE164))
			{
				return pConf;
			}
		}
	}
	else if (0 != strlen(tDstCallAddr.m_tE164.m_abyAlias))
	{
		for(wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++)
		{
			pConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1];
			if(TP_INVALID_INDEX == pConf->m_wID)
			{
				continue;
			}
			if (0 == strcmp(tDstCallAddr.m_tE164.m_abyAlias, pConf->m_achConfName) 
				|| 0 == strcmp(tDstCallAddr.m_tE164.m_abyAlias, pConf->m_achConfE164))
			{
				return pConf;
			}
		}
	}

	return NULL;
}

TConfTemplateLocal* CUmsConfTemplateHandleService::GetConfTemplate(const u16 wConfTemplateID)
{	//从界面过来的开启会议请求，根据ID召开，可以召开0号模板

	if(wConfTemplateID>TP_CONFTEMPLATE_MAXNUM)
	{
		return NULL;
	}
 	TConfTemplateLocal *pConf = NULL;
	pConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wConfTemplateID];

	if(TP_INVALID_INDEX == pConf->m_wID)
	{
	 	return NULL;
 	}

	return pConf;
}

u16 CUmsConfTemplateHandleService::GetConfTemplateAlias(TTPAlias atDstAlias[], u16 wMaxAlias)
{

	TTPConfTemplate *pConf = NULL;
	u16 wNum = 0;
	for(u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		pConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1];
		if(TP_INVALID_INDEX == pConf->m_wID)
		{
			continue;
		}
	
		if (strlen(pConf->m_achConfE164) > 0)
		{
			atDstAlias[wNum].SetAlias(tp_Alias_e164, 	pConf->m_achConfE164);
			wNum++;
			if (wNum >= wMaxAlias)
			{
				return wNum;
			}
		}
		
		if (strlen(	pConf->m_achConfName) > 0)
		{
			atDstAlias[wNum].SetAlias(tp_Alias_h323, pConf->m_achConfName);
			wNum++;
			if (wNum >= wMaxAlias)
			{
				return wNum;
			}
		}
	}	
	return wNum;
}


//--huzilong 增加组号，别名注册使用该接口
u16 CUmsConfTemplateHandleService::GetConfTemplateAlias(TTPAlias atDstAlias[], u16 wMaxAlias, EmRegGroupNum emRegGroupNum)
{
	TTPConfTemplate *pConf = NULL;
	u16 wNum = 0;
	u16 wGroupNum = 0;
	u16 wlow = 0;
	u16 whigh = 0;
	switch( emRegGroupNum )
	{
	case em_FirstGroup:
		{
			wGroupNum = 1;
		}
		break;
	case em_SecondGroup:
		{
			wGroupNum = 2;	
			
		}
		break;
	case em_ThirdGroup:
		{
			wGroupNum = 3;
		}
		break;
	case em_FourthGroup:
		{
			wGroupNum = 4;
		}
		break;


	default:
		{
			wGroupNum = 0;
		}
		break;
	}


	if(0 !=wGroupNum)
	{
		wlow = (wGroupNum-1)*TP_TEMPNUM_PERGROUP;
		whigh = wlow+TP_TEMPNUM_PERGROUP;
	}
	else
	{
		MdlError(Ums_Mdl_Service,("[GetConfTemplateAlias] Error emRegGroupNum = %d\n",emRegGroupNum));
		return 0;
	}

	for(u16 wIndex = wlow; wIndex < whigh; wIndex++)
	{
		pConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex+1];
		if(TP_INVALID_INDEX == pConf->m_wID)
		{
			continue;
		}
		
		if (strlen(pConf->m_achConfE164) > 0)
		{
			atDstAlias[wNum].SetAlias(tp_Alias_e164, 	pConf->m_achConfE164);
			wNum++;
			if (wNum >= wMaxAlias)
			{
				return wNum;
			}
		}
		
		if (strlen(	pConf->m_achConfName) > 0)
		{
			atDstAlias[wNum].SetAlias(tp_Alias_h323, pConf->m_achConfName);
			wNum++;
			if (wNum >= wMaxAlias)
			{
				return wNum;
			}
		}
	}	
	return wNum;
}


void CUmsConfTemplateHandleService::UpDateOnTimeConfOnStart(u16 wConfTemplateID)
{
	if(wConfTemplateID>TP_CONFTEMPLATE_MAXNUM)
	{
		MdlError(Ums_Mdl_Service,("[UpDateOnTimeConfOnStart] Error ID = %d\n",wConfTemplateID));
		return;
	}
	
	TTPConfTemplate* ptConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wConfTemplateID];
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	
	BOOL32 bUpdate = FALSE;
	if (ptConf->m_tStartTime != 0)
	{
		ptConf->m_tStartTime = 0;	
		
		bUpdate = TRUE;
	}

	if (ptConf->m_dwTimeID != 0)
	{
		pServer->DelTimer(ptConf->m_dwTimeID);
	}

	if (bUpdate)
	{
		//m_tStartTime改变后，必须要更新文件中去
		UpdateCfgData(wConfTemplateID);

		TLogUser tUserTmp;
		
		TTPConfTemplateBuf tTmp;
		tTmp.SetValue(*ptConf);

		u8 abyBuf[sizeof(tTmp.m_tTemplate) + sizeof(BOOL32)] = {0};
		memcpy(abyBuf, &tTmp.m_tTemplate, sizeof(tTmp.m_tTemplate));
		BOOL32 bRefresh = TRUE;
		bRefresh = htonl(bRefresh);
		memcpy(abyBuf + sizeof(tTmp.m_tTemplate), &bRefresh, sizeof(BOOL32));
		TpNotifyMsgToUeFromService(evtp_Updateconftemplate_Notify1, abyBuf, sizeof(abyBuf), tUserTmp);
	}
}

void CUmsConfTemplateHandleService::UpdateCfgData(u16 wPostion)
{
	//单独只更新一个
	umsSetConfTempInfo(m_tHandleConfTemplate.m_atTPConfTemplate[wPostion], wPostion-1);
}

void CUmsConfTemplateHandleService::SendNewReg(u16 wPostion)
{
	//注册
	EmRegGroupNum emRegGroupNum = em_AllGroup;
	do 
	{
		if( wPostion > 0 && wPostion <= TP_TEMPNUM_PERGROUP )
		{
			emRegGroupNum = em_FirstGroup;
			break;
		}
		if( wPostion > TP_TEMPNUM_PERGROUP && wPostion <= 2*TP_TEMPNUM_PERGROUP )
		{
			emRegGroupNum = em_SecondGroup;
			break;
		}
		if( wPostion > 2*TP_TEMPNUM_PERGROUP && wPostion <= 3*TP_TEMPNUM_PERGROUP )
		{
			emRegGroupNum = em_ThirdGroup;
			break;
		}
		if( wPostion > 3*TP_TEMPNUM_PERGROUP && wPostion <= 4*TP_TEMPNUM_PERGROUP )
		{
			emRegGroupNum = em_FourthGroup;
			break;
		}
		
		MdlError(Ums_Mdl_Service,("[UpdateCfgData] wPostion error %d\n", wPostion));
		return;

	} while (0);
	
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	pServer->NotifySelf(evtp_ums_update_reg, (u8 *)&emRegGroupNum, sizeof(emRegGroupNum));
}

void CUmsConfTemplateHandleService::EventDelAllConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	MdlHint(Ums_Mdl_Service, ("EventDelAllConfReq Begin\n"));
	
	TOprConfTmpResult tRet;
	tRet.m_emReason = TP_ConfTemplate_DelSuccess;

	do 
	{
		if ( m_bUpTemp )
		{
			tRet.m_emReason = TP_ConfTemplate_TmpUpIng;
			break;
		}
		
		TConfTemplateLocal* ptConfTemp = NULL;
		for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
		{
			if (TP_INVALID_INDEX == m_tHandleConfTemplate.m_atTPConfTemplate[wIndex + 1].m_wID)
			{
				continue;
			}
			TConfTemplateLocal tTemp;
			tTemp.m_wID = wIndex + 1;
			ptConfTemp = m_tHandleConfTemplate.Del(tTemp);
			
			CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
			if (0 != ptConfTemp->m_dwTimeID)
			{
				tpHint(Ums_Mdl_Service,"[Del]m_dwTimeID = %d\n",ptConfTemp->m_dwTimeID);
				pServer->DelTimer(ptConfTemp->m_dwTimeID);
			}

			ptConfTemp->Clear();

			umsDelConfTempInfo(wIndex);

		}
	} while (0);

	TLogUser tUserTmp;
	TpNotifyMsgToUeFromService(ev_del_all_conftemp_rsp, &tRet, sizeof(TOprConfTmpResult), tUserTmp);

	if (TP_ConfTemplate_DelSuccess == tRet.m_emReason)
	{//取消注册
		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
		TCnsRegInfo tReg;
		pServer->NotifySelf(evtp_ums_unreg_req, (u8*)&tReg, sizeof(tReg));	
	}
}

void CUmsConfTemplateHandleService::ShowConfTemp()
{
	tpHint(Ums_Mdl_Service," Show ConfTemp List:%d\n", m_tHandleConfTemplate.Size());

	u16 wNum = 1;
	TConfTemplateLocal* ptConf;
	for (u16 wIndex = 0; wIndex<=TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		ptConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wIndex];
		if( TP_INVALID_INDEX == ptConf->m_wID )
		{
			continue;
		}
		msgprintnotime("ID:%d, confName:%s, e164:%s, DefaultChair:%d, bPollOn:%d, bAudMixOn:%d, bVacOn:%d\n", ptConf->m_wID
					, ptConf->m_achConfName, ptConf->m_achConfE164, ptConf->m_wDefaultChairMan
					, ptConf->m_tTurnList.m_bPollOn, ptConf->m_atAuxMixList.m_bAudMixOn
					, ptConf->m_atAuxMixList.m_bVacOn);

		msgprintnotime("ConfUpBandWid:%d, ConfDownBandWid:%d\n", ptConf->m_wUpBandWid, ptConf->m_wDownBandWid);

		msgprintnotime("ConfEncryptType:%s, Len:%d, Key:%s,bDefaultEnc:%d\n",
			TpEnumString(EmTPEncryptType, ptConf->m_tEncrypt.m_emEncryptModel), 
			ptConf->m_tEncrypt.m_byKeyLen, ptConf->m_tEncrypt.m_achEncKey,ptConf->m_bDefaultEncrypt);

		msgprintnotime("AudioInfo:AudFmtNum:%d.\n", ptConf->m_wAudFmtNum);
		for (wNum = 0; wNum < ptConf->m_wAudFmtNum; wNum++)
		{
			msgprintnotime("   AudCap:%d, AudFmt:%s.\n", wNum, 
				UmsAudFormatPrint(ptConf->m_atAudFmt[wNum].m_emFormat));
		}

		msgprintnotime("VideoInfo:CapNum:%d, ConfBitRate:%d.\n", ptConf->m_wMainNum, ptConf->m_wConfBitRate);
		for (wNum = 0; wNum < ptConf->m_wMainNum; wNum++)
		{
			msgprintnotime("   VidCap %d, Profile:%s, Res:%s, FrameRate:%d.\n", wNum, UmsVidProfilePrint(ptConf->m_atTpMainVideoRes[wNum].m_emQualityLvl)
							, UmsVidResPrint(ptConf->m_atTpMainVideoRes[wNum].m_emRes), ptConf->m_atTpMainVideoRes[wNum].m_wFrameRate);
		}
		msgprintnotime("DualInfo:CapNum:%d, DualBitRate:%d.\n", ptConf->m_wMinorNum, ptConf->m_wHpDualBitRate);
		for (wNum = 0; wNum < ptConf->m_wMinorNum; wNum++)
		{
			msgprintnotime("   DualCap %d, Profile:%s, Res:%s, FrameRate:%d.\n", wNum, UmsVidProfilePrint(ptConf->m_atTpMinorVideoRes[wNum].m_emQualityLvl)
							,  UmsVidResPrint(ptConf->m_atTpMinorVideoRes[wNum].m_emRes), ptConf->m_atTpMinorVideoRes[wNum].m_wFrameRate);
		}
		msgprintnotime("ep list Num:%d\n", ptConf->m_atEpList.m_wNum);

		for (wNum = 0; wNum < ptConf->m_atEpList.m_wNum; ++wNum)
		{
			msgprintnotime("   Index:%d, 323name:%s, e164name:%s,ip:"TPIPFORMAT", epid:%d, bAliasIP:%d, CallType:%s,CallProtocol:%s\n", wNum+1
				, ptConf->m_atEpList.m_tCnsList[wNum].m_tEpAddr.m_tAlias.m_abyAlias
				, ptConf->m_atEpList.m_tCnsList[wNum].m_tEpAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptConf->m_atEpList.m_tCnsList[wNum].m_tEpAddr.m_dwIP)
				, ptConf->m_atEpList.m_tCnsList[wNum].m_wEpID, ptConf->m_atEpList.m_tCnsList[wNum].m_tEpAddr.m_bAliasIP,
				TpEnumString(EmTpAliasType, ptConf->m_atEpList.m_tCnsList[wNum].m_tEpAddr.m_byCallType),
				TpEnumString(EmTpConfProtocol, ptConf->m_tTempCfgEx.m_aemCallProtocol[wNum]));
		}

		msgprintnotime("Poll list Num:%d\n", ptConf->m_tTurnList.m_wNum);
		for (wNum = 0; wNum < ptConf->m_tTurnList.m_wNum; ++wNum)
		{
			msgprintnotime("   Index:%d, epid:%d\n", wNum+1, ptConf->m_tTurnList.m_awList[wNum]);
		}
		msgprintnotime("AudMix list:(");
		for (wNum = 0; wNum < ptConf->m_atAuxMixList.GetMixNum(); wNum++)
		{
			msgprintnotime(" %d,", ptConf->m_atAuxMixList.m_awList[wNum]);
		}
		msgprintnotime(" )\n");

		msgprintnotime("ConfVmpStyle:%s, ConfVmpEpNum:%d\n",TpEnumString(EmVMPStyle,ptConf->m_tVmpCfg.m_emStyle),ptConf->m_tVmpCfg.m_wEpNum);
		msgprintnotime("EpName list:(");
		for (wNum = 0; wNum < ptConf->m_tVmpCfg.m_wEpNum; ++wNum)
		{
			msgprintnotime(" %s, %d ",ptConf->m_tVmpCfg.m_atEpList[wNum].m_tEpAlias.m_abyAlias , ptConf->m_tVmpCfg.m_atEpList[wNum].m_wScrIndx);
		}
		msgprintnotime(" )\n\n");
	}
}


void CUmsConfTemplateHandleService :: EventAddConfExReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize)
{
	TTemplateConfEx tTemplateEx;
	TTemplateConfEx* ptTempEx = NULL;
	TTemplateConfEx tTempExRet;
	TP_SAFE_CAST(tTemplateEx, (u8*)pDataBuf);
	TConfTemplateLocal* ptConf = NULL;
	u16 wTempID = tTemplateEx.m_wTempID;
	u16 wIndex = 0;
	u16 wNum = 0;
	u16 wEpNum = 0;
	u16 wListNum= 0;
	EmAddTempConfExRes emRet = em_Addex_ok;
	do 
	{
		if (TP_INVALID_INDEX == wTempID)
		{
			emRet = em_TempID_error;
			MdlError(Ums_Mdl_Service, ("EventAddConfExReq Temp Index:%d.\n", tTemplateEx.m_wTempID));
			break;
		}

		ptConf = &m_tHandleConfTemplate.m_atTPConfTemplate[wTempID];
		//未找到相应模板
		if (TP_INVALID_INDEX == ptConf->m_wID)
		{
			emRet = em_TempID_error;
			MdlError(Ums_Mdl_Service, ("EventAddConfExReq connot find Temp Index:%d.\n", tTemplateEx.m_wTempID));
			break;
		}
	
		if (0 == tTemplateEx.m_wNum)
		{
			MdlError(Ums_Mdl_Service, ("EventAddConfExReq The callProtocol list num is 0.\n"));
			emRet = em_EplistNum_error;
			break;
		}
		 wListNum = ptConf->m_atEpList.m_wNum;
		if (tTemplateEx.m_wNum > wListNum)
		{
			MdlError(Ums_Mdl_Service, ("EventAddConfExReq The callProtocol list exceed num %d,listnum:%d.\n", tTemplateEx.m_wNum,wListNum));
			emRet = em_EplistNum_error;
			break;
		}
		for (wIndex = 0; wIndex < tTemplateEx.m_wNum; ++wIndex)
		{
			
			if(TP_INVALID_INDEX == tTemplateEx.m_awEpID[wIndex])
			{
				++wEpNum;
				tTempExRet.m_awEpID[wIndex] = tTemplateEx.m_awEpID[wIndex];
				MdlError(Ums_Mdl_Service, ("EventAddConfExReq The callProtocol EPID invalid index:%d .\n", wIndex ));
				continue;
			}
			//在模板中查找相应会场索引
			u16 wEpIndex = ptConf->m_atEpList.FindEpIndex(tTemplateEx.m_awEpID[wIndex]);
			if (TP_INVALID_INDEX == wEpIndex)
			{
				MdlError(Ums_Mdl_Service, ("EventEpCallProtocol cannot find EP index:%d EpID:%d.\n", wIndex,tTemplateEx.m_awEpID[wIndex]));
				tTempExRet.m_awEpID[wIndex] = tTemplateEx.m_awEpID[wIndex];
				++wEpNum;
				continue;
			}
			//没有指定协议
			if (tTemplateEx.m_aemCallProtocol[wIndex] != emTpSIP && tTemplateEx.m_aemCallProtocol[wIndex] != emTpH323)
			{					
				MdlError(Ums_Mdl_Service, ("EventEpCallProtocol the EP call protocol error EPID:%d call protocol:%s.\n", tTemplateEx.m_awEpID[wIndex], TpEnumString(EmTpConfProtocol,tTemplateEx.m_aemCallProtocol[wIndex])));
				tTempExRet.m_awEpID[wIndex] = tTemplateEx.m_awEpID[wIndex];
				tTempExRet.m_aemCallProtocol[wIndex] = tTemplateEx.m_aemCallProtocol[wIndex];
				++wNum;	
				continue;
			}
			ptTempEx = &ptConf->m_tTempCfgEx;
			if (wEpIndex == wIndex)
			{

				ptTempEx->m_awEpID[wIndex] = tTemplateEx.m_awEpID[wIndex];
				ptTempEx->m_aemCallProtocol[wIndex] = tTemplateEx.m_aemCallProtocol[wIndex];
			}
			//模板会场索引与传入索引不同 调整
			else
			{
				ptTempEx->m_awEpID[wEpIndex] = tTemplateEx.m_awEpID[wIndex];
				ptTempEx->m_aemCallProtocol[wEpIndex] = tTemplateEx.m_aemCallProtocol[wIndex];					
			}			
		
		}


	} while (0);
	if (wEpNum)
	{
		emRet = em_Eplist_error;
	}
	if (wNum)
	{
		emRet = em_CallProtocol_error;
	}

	if (em_Addex_ok != emRet)
	{
		tTempExRet.m_wTempID = wTempID;
		tTempExRet.m_wNum   = tTemplateEx.m_wNum;
		u8 abyBuf[sizeof(TTemplateConfEx) + sizeof(EmAddTempConfExRes)] = {0};
		memcpy(abyBuf, &tTempExRet, sizeof(TTemplateConfEx));
		memcpy(abyBuf + sizeof(TTemplateConfEx), &emRet, sizeof(EmAddTempConfExRes));
		TpNotifyMsgToUeFromService(evtp_AddConfTemplateEx_res , abyBuf, sizeof(abyBuf), *ptLogUser);

	} 
	else
	{

		ptTempEx->m_wTempID = wTempID;
		ptTempEx->m_wNum = wListNum ;
		for (wIndex = 0; wIndex < wListNum; ++wIndex)
		{
			if (TP_INVALID_INDEX == ptTempEx->m_awEpID[wIndex])
			{
				ptTempEx->m_awEpID[wIndex] = ptConf->m_atEpList.FindEpIndex(tTemplateEx.m_awEpID[wIndex]);
				continue;
			}
		}
		UpdateCfgData(wTempID);
		TpNotifyMsgToUeFromService(evtp_AddConfTemplateEx_Notify,ptTempEx, sizeof(TTemplateConfEx), *ptLogUser);
	}

}

