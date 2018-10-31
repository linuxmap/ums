#ifndef _h_regstruct_h__
#define _h_regstruct_h__
#include "umscommonstruct.h"

#define UMS_MAX_ALIAS_SIZE		64
#define CNS_MAX_ALIAS_SIZE		2

//B1 注册信息结果
typedef struct tagTReqRegInfo
{
	EmGetRegInfoType	m_tRegType;			//查询信息类型
	u16					m_wPackSeq;			//包序号，从1开始，0为无效值
	u16					m_wTotalPackNum;	//包总数
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[UMS_MAX_ALIAS_SIZE];	//暂时定为最大值为64个名称为一波返回
	EmTPEndpointType	m_emSelfType;				//注册方 的系统类型(UMS和CNS) 
	
	tagTReqRegInfo()
	{
		memset( this, 0, sizeof(tagTReqRegInfo) );
	}
}TReqRegInfo, *PTReqRegInfo;


//B2 UMS注册信息
typedef struct tagTUmsRegData
{
	u16					m_wAliasNum;	//别名个数
	TTPAlias			m_atAlias[UMS_MAX_ALIAS_SIZE];	//别名数组
	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//呼叫地址
	s8					m_aSelfVer[TP_MAX_VERSION_LEN +1];	//注册方 的版本号
	s8					m_aCompileTm[TP_MAX_VERSION_LEN +1];	//注册方的编译时间
	u32					m_dwCallType;	//呼叫类型TCP呼叫还是UDP呼叫，注册服务器不处理此属性
	u32					m_dwExpires;	//超时时间
	u32_ip				m_dwSelfAddr;	//注册方 的地址

	tagTUmsRegData()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegData));
	}
}TUmsRegData;

//B2 CNS注册信息
typedef struct tagTCnsRegData
{
	u16					m_wAliasNum;	//别名个数
	TTPAlias			m_atAlias[CNS_MAX_ALIAS_SIZE];	//别名数组
	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//呼叫地址
	s8					m_aSelfVer[TP_MAX_VERSION_LEN +1];	//注册方 的版本号
	s8					m_aCompileTm[TP_MAX_VERSION_LEN +1];	//注册方的编译时间
	u32					m_dwCallType;	//呼叫类型TCP呼叫还是UDP呼叫，注册服务器不处理此属性
	u32					m_dwExpires;	//超时时间
	u32_ip				m_dwSelfAddr;	//注册方 的地址
	
	tagTCnsRegData()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegData));
	}
}TCnsRegData;

//B2 注册信息结果
typedef struct tagTReqRegInfoEx
{
	EmGetRegInfoType	m_tRegType;			//查询信息类型
	EmTPEndpointType   	m_emSelfType;		//注册方 的系统类型(UMS和CNS)
	u16					m_wPackSeq;			//包序号，从1开始，0为无效值
	u16					m_wTotalPackNum;	//包总数

	u16					m_wDataNum;			//结果个数			

	tagTReqRegInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTReqRegInfoEx));
	}
}TReqRegInfoEx;


#endif // _h_regstruct_h__
