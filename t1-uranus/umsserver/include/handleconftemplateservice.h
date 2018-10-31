#ifndef _h_handleconftemplateservice_h__
#define _h_handleconftemplateservice_h__
#include "tpstruct.h"
#include "tphandle.h"
#include "umsinnerstruct.h"
#include "tpvector.h"
 
//使用静态数组，方便模版文件操作---huzilong
typedef struct tagTHandleConfTemplate
{
	TConfTemplateLocal m_atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM+1];
	
	tagTHandleConfTemplate()
	{
		Clear();
	}

	void Clear()
	{
		memset(m_atTPConfTemplate,0,sizeof(m_atTPConfTemplate));
		
		for(u16 wIndex = 0; wIndex<=TP_CONFTEMPLATE_MAXNUM; wIndex++)
		{
			m_atTPConfTemplate[wIndex].m_wID = TP_INVALID_INDEX;
			m_atTPConfTemplate[wIndex].Clear();
		}
	}

	BOOL IsFull()
	{
		BOOL bFull = TRUE;
		for( u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++ )
		{
			if( TP_INVALID_INDEX == m_atTPConfTemplate[wIndex+1].m_wID )
			{
				bFull = FALSE;
				return bFull;
			}
		}	
		return bFull;
	}

	BOOL Add(TConfTemplateLocal& tConftemp, u16 wNum)
	{
		if(TP_INVALID_INDEX != m_atTPConfTemplate[wNum].m_wID)
		{
			return FALSE;
		}
		else
		{
			m_atTPConfTemplate[wNum] = tConftemp;
		//	memcpy(&m_atTPConfTemplate[wNum],&tConftemp,sizeof(TTPConfTemplate));
			return TRUE;
		}
	}

	BOOL Add(TTPConfTemplate& tConftemp, u16 wNum)
	{
		if (TP_INVALID_INDEX != m_atTPConfTemplate[wNum].m_wID)
		{
			return FALSE;
		}
		else
		{
			m_atTPConfTemplate[wNum] = tConftemp;
			return TRUE;
		}
	}

	TConfTemplateLocal * Del(TConfTemplateLocal& tConftemp)
	{
		u16 wID = tConftemp.m_wID;
		m_atTPConfTemplate[wID].m_wID = TP_INVALID_INDEX;
		memset(m_atTPConfTemplate[wID].m_achConfName,0,TP_MAX_ALIAS_LEN+1);
		memset(m_atTPConfTemplate[wID].m_achConfE164,0,TP_MAX_ALIAS_LEN+1);
		return &m_atTPConfTemplate[wID];
	}

	void Update(TConfTemplateLocal& tConftemp)
	{
		u16 wIndex = tConftemp.m_wID;
		m_atTPConfTemplate[wIndex] = tConftemp;
		//memcpy(&m_atTPConfTemplate[wIndex],&tConftemp,sizeof(tConftemp));
	}

	void Update(TTPConfTemplate& tConfTemp)
	{
		u16 wIndex = tConfTemp.m_wID;
		m_atTPConfTemplate[wIndex] = tConfTemp;
	}


	u16 FindIdle()
	{
		for( u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++ )
		{
			if( TP_INVALID_INDEX == m_atTPConfTemplate[wIndex+1].m_wID )
			{
				return (wIndex+1);
			}
		}		
		return TP_INVALID_INDEX;

	}

	u16 Size()
	{
		u16 size = 0;
		for( u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; wIndex++ )
		{
			if( TP_INVALID_INDEX != m_atTPConfTemplate[wIndex+1].m_wID )
			{
				++size;
			}
		}

		return size;
	}


}THandleConfTemplate;


class CUmsConfTemplateHandleService : public CTpHandler
{
public:
	CUmsConfTemplateHandleService(CTpObject* pcObjec);
	~CUmsConfTemplateHandleService();
	
public:
	virtual BOOL32		Handler( CTpMsg *const ptMsg );
	virtual BOOL32		Create();

public:
	void				ShowConfTemp();
	void				PrecontractOnTime(u32 dwTimerId);
	TConfTemplateLocal*	GetConfTemplate(const TTpCallAddr&  tDstAlias);
	TConfTemplateLocal*	GetConfTemplate(const u16 wConfTemplateID);
	u16					GetConfTemplateAlias(TTPAlias atDstAlias[], u16 wMaxAlias);
	u16					GetConfTemplateAlias(TTPAlias atDstAlias[], u16 wMaxAlias, EmRegGroupNum emRegGroupNum);
	void				UpDateOnTimeConfOnStart(u16 wConfTemplateID);

	TTemplateConfEx*	GetConfTemplateCall(const u16 wConfTemplateID);
protected:
	void	EventLogin(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	void	EventAddConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	void	EventDelConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	void	EventDelAllConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	void	EventUpdateConfReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);

	void	EventUpdateConfTimer();

	//导入模板文件
	void	EventUpLoadConfTemp(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	//导入模板文件结果
	void	EventUpLoadConfTempRsq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	//导出模板文件请求
	void	EventDownLoadConfTemp(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSize);
	//导出文件应答
	void	EventDownLoadConfTempRsq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSiz);
	//保存合成预案
	void    EventSaveVmpPlan(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSiz);
	//模板扩展信息
	void    EventAddConfExReq(TLogUser* ptLogUser, void* pDataBuf, u16 wDataSiz);

    void	EventQueryAlias(void* pDataBuf, u16 wDataSiz);
private:
	void	UpdateCfgData( u16 wPostion );
	void	SendNewReg(u16 wPostion);
	//初始化
	void	Init();
	//从配置文件读取信息
	void	LoadInfoFromTpCfg();
	
protected:
	TTPConfTemplateBuf	  m_tTempBuf;
	THandleConfTemplate   m_tHandleConfTemplate;	//索引为0的模板为临时模板，永远存在，且不保存
	BOOL32				  m_bUpTemp;//正常导入模板 标识
};



#endif // _h_handleconftemplateservice_h__
