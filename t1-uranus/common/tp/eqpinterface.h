#ifndef _h_eqpinterface_h__
#define _h_eqpinterface_h__
#include "tpsys.h"
#include "umsinnerstruct.h"
#include "umsobject.h"


#ifndef localmin
#define localmin(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef localmax
#define localmax(a,b) ((a)>(b)?(a):(b))
#endif

void InitEqpLib();

//基类
typedef struct tagTEqpParam
{
	EMEqpType		m_emEqpType;
	u32				m_dwCapCount;
	TEqpRes*		m_ptEqpRes;
	
	tagTEqpParam()
	{
		m_emEqpType = em_unknow_mdl;
		m_dwCapCount = 0;
		m_ptEqpRes = NULL;
	}
}TEqpParam;

//接入
typedef struct tagTAdaptEqpParam : public TEqpParam
{
	tagTAdaptEqpParam()
	{	
		m_emEqpType = em_adapter_mdl;
		m_dwCapCount = 1;
	}
}TAdaptEqpParam;

//Mix
typedef struct tagTMixEqpRes : public TEqpRes
{
	u8	m_byEqpID;//外设ID
	u16	m_wEqpRtcpStartPort;
	u16	m_wEqpStartPort;
	u16 m_wUmsStartPort;

	u16	m_wChanNum;

	tagTMixEqpRes()
	{
		Clear();
	}
	void Clear()
	{
		m_wEqpRtcpStartPort = 0;
		m_wEqpStartPort = 0;
		m_wUmsStartPort = 0;
		m_byEqpID = 0;

		m_wChanNum = 0;

		TEqpRes::Clear();
	}
}TMixEqpRes;

typedef struct tagTMixerParam : public TEqpParam
{
	u16	m_wConfID;

	u16 m_wChanLimit;  // 申请混音器所需通道限制
	u16  m_wReqNum;
	u32  m_dwNode; 

	tagTMixerParam()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wChanLimit = 0;

		m_wReqNum = 0;
		m_dwNode = 0;
	}

	void Init( TEqpRes* ptEqpRes, u16 wConfID, u16 wChanLimit = 0, u16 wReqNum = 0, u32 dwNode = 0)
	{
		m_wConfID = wConfID;

		m_emEqpType = em_audmix_mdl;
		m_ptEqpRes = ptEqpRes;

		m_wChanLimit = wChanLimit;
		m_wReqNum = wReqNum;
		m_dwNode = dwNode;
	}
}TMixerParam;

//转发
typedef struct tagTMediaParam : public TEqpParam
{	
	enum EmMediaAssignType
	{
		emAssignConf,
		emAssignNode,
	};
	
	EmMediaAssignType m_emAssignType;
	TEqpRes			  m_atEqp[UMS_CONF_MAX_DS_NUM];
	u32				  m_dwNodeIp;			//会场ip 多转发 双网段场景下 带ip申请转发板
	tagTMediaParam()
	{
		m_emEqpType = em_dataswitch_mdl;
		m_dwCapCount = 1;
		
		m_emAssignType = emAssignConf;
		m_dwNodeIp = 0;
	}
}TMediaParam;


//nb
typedef struct tagTNbParam : public TEqpParam
{	
	tagTNbParam()
	{
		m_emEqpType = em_netbuf_mdl;
		m_dwCapCount = 1;
	}
}TNbParam;

typedef struct tagTMpcParam : public TEqpParam
{	
	tagTMpcParam()
	{
		m_emEqpType = em_mpc_mdl;
		m_dwCapCount = 1;
	}
}TMpcParam;

//Vmp
typedef struct tagTVmpEqpRes : public TEqpRes
{
	u8	m_byEqpID;//外设ID
	u16	m_wUmsStartPort;
	u16	m_wEqpStartPort;
	EMEqpModleType m_emMdlType;
	tagTVmpEqpRes()
	{
		Clear();
	}
	void Clear()
	{
		m_wUmsStartPort = 0;
		m_wEqpStartPort = 0;
		m_byEqpID = 0;
		m_emMdlType = em_unknow_eqp_mdl;
		TEqpRes::Clear();
	}
}TVmpEqpRes;

typedef struct tagTVmpParam : public TEqpParam
{
	u16				m_wConfID;
	EMVmpStyle		m_emVmpStyle;
	u8				m_byVMPMemberNum;	  //当前合成成员数目
	TTPVMPMember	m_atVMPMember[TP_MAX_STREAMNUM]; //画面合成成员
	u8				m_byOutMemBerNum;
	TUmsVidFormat	m_atVMPOutMember[TP_VMP_MAX_OUT_CHN_NUM];
	tagTVmpParam()
	{
		m_emVmpStyle = tp_VmpStyle_MidBig;
		m_wConfID = TP_INVALID_INDEX;
		m_emEqpType = em_vmp_mdl;
		m_dwCapCount = 1;
		m_byVMPMemberNum = TP_MAX_STREAMNUM;
		m_byOutMemBerNum = TP_VMP_MAX_OUT_CHN_NUM;
		
		memset(m_atVMPMember, 0, sizeof(m_atVMPMember));
		memset(m_atVMPOutMember, 0, sizeof(m_atVMPOutMember));
	}

	void SetParam( u16 wConfID, u8 byOutNum, TUmsVidFormat atOutMember[], TEqpRes* ptEqpRes )
	{
		m_wConfID = wConfID;
//		m_byVMPMemberNum = min(byInNum, TP_MAX_STREAMNUM);
		m_byOutMemBerNum = localmin(byOutNum, TP_VMP_MAX_OUT_CHN_NUM);;

// 		memcpy(&m_atVMPMember[0], &atVmpMemeber[0], 
// 						min(byInNum,m_byVMPMemberNum)*sizeof(TTPVMPMember));
		memcpy(&m_atVMPOutMember[0], &atOutMember[0], 
						localmin(byOutNum,m_byOutMemBerNum)*sizeof(TUmsVidFormat));

		m_ptEqpRes = ptEqpRes;
	}

}TVmpParam;


//Bas
typedef struct tagTBasChnInfo
{
	u8	m_byEqpID;//外设ID
	u16	m_wChnIndx;//通道在数组中的索引
	u16	m_wUmsStartPort;
	u16	m_wEqpStartPort;
	u32 m_dwMediaNode;
	u32 m_dwMediaIP;
	
	tagTBasChnInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wUmsStartPort = 0;
		m_wEqpStartPort = 0;
		m_byEqpID = 0;
		m_wChnIndx = 0;
		m_dwMediaNode = INVALID_NODE;
		m_dwMediaIP = 0;
	}
	void SetMediaInfo( TBasMediaInfo& tMediaInfo )
	{
		m_dwMediaNode = tMediaInfo.m_dwNewDsNode;
		m_dwMediaIP = tMediaInfo.m_dwNewDsIP;
	}
}TBasChnInfo;

typedef struct tagTBasEqpRes : public TEqpRes
{
	TBasChnInfo m_tBasChnInfo;
	tagTBasEqpRes()
	{
		Clear();
	}
	void Clear()
	{
		m_tBasChnInfo.Clear();
		TEqpRes::Clear();
	}
}TBasEqpRes;

typedef struct tagTBasParam : public TEqpParam
{
	enum EmAssignType
	{
		em_AssignType_Brd,//广播  3000能力
		em_AssignType_Sel,//选看等 1500能力
	};
	u16				m_wConfID;
	EmAssignType	m_emAssignType;
	u8				m_byOutMemBerNum;
	tagTBasParam()
	{
		m_emAssignType = em_AssignType_Brd;
		m_emEqpType = em_bas_mdl;
		m_dwCapCount = 1;
		m_byOutMemBerNum = TP_CONF_MAX_MAIN_VIDEO_RES_NUM;
	}
	
	void SetParam( u16 wConfID, EmAssignType emAssignType, u8 byOutNum, TEqpRes* ptEqpRes )
	{
		m_wConfID = wConfID;
		m_emAssignType = emAssignType;
		m_emEqpType = em_bas_mdl;
		m_ptEqpRes = ptEqpRes;
		m_byOutMemBerNum = byOutNum;
	}
}TBasParam;

typedef struct tagTAudBasParam : public TEqpParam
{
	u16	m_wConfID;

	u16  m_wReqNum;
	u32   m_dwNode; 

	tagTAudBasParam()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wReqNum = 0;
		m_dwNode = 0;
	}
	
	void SetParam( u16 wConfID, TEqpRes* ptEqpRes , u16 wReqNum = 0, u32 dwNode = 0)
	{
		m_wConfID = wConfID;
		m_emEqpType = em_audbas_mdl;
		m_ptEqpRes = ptEqpRes;
		m_wReqNum = wReqNum;
		m_dwNode = dwNode;
	}
}TAudBasParam;

BOOL32 AssignEqpEx( TEqpParam* ptEqpParam);	
BOOL32 AssignEqpByNodeEx(TEqpParam* ptEqpParam);
BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);	

BOOL32 GetAllEqpRes( TEqpRes* pcEqpRes, u16 wEqpNum, EMEqpType emEqpType );

#endif // _h_eqpinterface_h__
