/*=============================================================================
模   块   名: 无
文   件   名: printctrl.h
相 关  文 件: printctrl.cpp
文件实现功能: 打印控制
作        者: 俞锦锦
版        本: V1.0  Copyright(C) 2011-2012 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2011/04/23  1.0     俞锦锦        创建
=============================================================================*/

#if !defined(AFX_PRINTCTRL_H__9355B609_A421_4E87_8928_6D78ADA82BDA__INCLUDED_)
#define AFX_PRINTCTRL_H__9355B609_A421_4E87_8928_6D78ADA82BDA__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvtype.h"
#include <map> 
using namespace std;



enum EmEventType
{
	emEventTypeUms,     //cms 与 ums 交互的消息
	emEventTypeCns,     //cms 与 cns 交互的消息
    emEventTypeUmsSend, //cms 发送给ums的消息
	emEventTypeUmsRecv, //cms 接收到的ums的消息
	emEventTypeCnsSend, //cms 发送给cns的消息
	emEventTypeCnsRecv, //cms 接收到cns的消息
    emEventTypeCmsWindow,   //cms 界面上的打印
	emEventTypeUmstoolSend,   //umstool 发送到ums的消息
    emEventTypeUmstoolRecv,   //umstool 接收到ums的消息
	emEventTypecnstoolSend,   //cnstool 发送到cns的消息
    emEventTypecnstoolRecv,   //cnstool 接收到cns的消息
    emEventTypeTPadSend, //发送给tpad的消息
    emEventTypeTPadRecv, //接收到tpad的消息
};

class CPrintCtrl  
{  

public: 

   /*=============================================================================
    函 数 名:GetPrintCtrl
    功    能:单例，获取打印类指针
    参    数:dwMsgID ：要打印的消息号，format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static const CPrintCtrl*GetPrintCtrl(); 

#ifndef _UNICODE
	static const CString GetTime();
#else
	static  const char* GetTime();
#endif
	
 
   /*=============================================================================
    函 数 名:ForcePrtMsg
    功    能:强制打印某消息，该消息是不是已经设置要打印的 
    参    数:dwMsgID ：要打印的消息号，emEventType:要打印的消息类型：usm还是cns， format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void ForcePrtMsg( u16 dwMsgID, EmEventType emEventType ,char * format,...  );
  

	/*=============================================================================
    函 数 名:PrtMsgBdy
    功    能:是否打印消息体
    参    数:bPrintMsgBdy：TRUE为打印，否则不打印
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
    static void PrtMsgBdy( BOOL32 bPrintMsgBdy );


	/*=============================================================================
    函 数 名:PrtMsg
    功    能:打印某消息，如果该消息不在已设置的打印范围，则不会打印出来
    参    数:dwMsgID ：要打印的消息号，emEventType:要打印的消息类型：usm还是cns，format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintMsg( u16 dwMsgID, EmEventType emEventType, char * format,... );



	/*=============================================================================
    函 数 名:PrtMsg
    功    能:打印某消息 
    参    数:format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintMsg( char * format,... );
	
	/*=============================================================================
    函 数 名:PrtMsg
    功    能:打印telnet消息 
    参    数:format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     杨奇峰  创建
    =============================================================================*/
	static void PrintMsg( EmEventType emEventType, char * format,...);

    /*=============================================================================
    函 数 名:SetPrintMsgType
    功    能:设置要/不 打印的消息类型
    参    数:dwPrintMsgType ：要打印的消息类型，bPrint：是否要打印
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void SetPrintMsgType( const u32 dwPrintMsgType, const BOOL bPrint ); 


 
	/*=============================================================================
    函 数 名:StopPrint
    功    能:不打印任何消息
    参    数: 
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void StopPrint();


	/*=============================================================================
    函 数 名:SetPrintAllMsg
    功    能: 打印全部消息
    参    数:  
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintAllMsg();

   /*=============================================================================
    函 数 名:SetPrintMsgLevel
    功    能: 打印全部消息
    参    数:  
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintMsgLevel( u8 abyLevel );


	/*=============================================================================
    函 数 名:PrintEnterMsg
    功    能: 在接收消息处打印所有的消息
    参    数:  
    注    意:在消息入口处，打印所有消息
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintEnterMsg( BOOL bPrint );

	/*=============================================================================
    函 数 名:IsPrintEnterMsg
    功    能: 是否打印入口处的消息
    参    数:  
    注    意: 主要用于内部打印时判断
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
    static BOOL IsPrintEnterMsg();

	/*=============================================================================
    函 数 名:PrintOutMsg
    功    能: 打印所有发出去的消息
    参    数:  
    注    意:在消息出口处打印所有的消息
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void PrintOutMsg(  BOOL bPrint  );

	/*=============================================================================
    函 数 名:IsPrintOutMsg
    功    能: 是否打印出口处的消息
    参    数:  
    注    意: 主要用于内部打印时判断
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static BOOL IsPrintOutMsg();


   
	/*=============================================================================
    函 数 名:SetPritnMsgID
    功    能:打印消息号为dwPrintEventId的消息
    参    数: 
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void SetPrintMsgID( const u32 dwPrintEventId );  
    
	/*=============================================================================
    函 数 名:SetPringMsgRange
    功    能:设置要打印的消息号的范围
    参    数: dwMaxMsgID：要打印的消息号的最大值，dwMinMsgID：要打印的消息号的最小值
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static void SetPrintMsgRange( const u32 dwMaxMsgID, const u32 dwMinMsgID );


	
    /*=============================================================================
	函 数 名： MappingHelper
	功    能： 映射事件名称，同时注册到事件类别数组里面
	算法实现： 
	全局变量： 
	参    数： u16 wEvent                 事件ID
			 const CString& strName     事件名称 
                u8 abyLevel              级别（ 1级为最高级，2级为中级，大于2的均划为最低级 ）
	返 回 值： void 
	-----------------------------------------------------------------------------
	修改记录：
	日  期		版本		修改人		走读人    修改内容
	2004/10/13     3.5		王慧琛                  规范化
	=============================================================================*/
	static void  MappingHelper(u16 wEvent, const CString& strName, u8 abyLevel = 2 );


	/*=============================================================================
	函 数 名： GetEventDescribe
	功    能：获取某消息的描述
	算法实现： 
	全局变量： 
	参    数： u16 wEvent                 事件ID
			 const CString& strName     事件名称 
         
	返 回 值： void 
	-----------------------------------------------------------------------------
	修改记录：
	日  期		版本		修改人		走读人    修改内容
	2004/10/13     3.5		王慧琛                  规范化
	=============================================================================*/
	static CString  GetEventDescribe( u16 wEvent );

	/*=============================================================================
    函 数 名:GetPrintLevel
    功    能:得到当前的打印级别
    参    数: 
    注    意: 
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/09/03  1.0     徐华秀  创建
    =============================================================================*/
	 static u8  GetPrintLevel();

  
    ~CPrintCtrl();

protected:

    CPrintCtrl();

	/*=============================================================================
    函 数 名:IsPrintMsg
    功    能:判断dwMsgID是否要打印
    参    数:dwMsgID ：要打印的消息号
    注    意:如果要使用打印某一类型的消息功能，该函数一定要重写，否则，有可能打印不出来
    返 回 值:成功TRUE，失败FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static  BOOL32 IsPrintMsg( const u16 wMsgID );

 


	/*=============================================================================
    函 数 名:IsPrintMsgBdy
    功    能:是否要打印消息体
    参    数: 
    注    意: 
    返 回 值:成功TRUE，失败FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	static  BOOL32 IsPrintMsgBdy() ;


	/*=============================================================================
    函 数 名:emType
    功    能:获取消息类型的描述
    参    数: 
    注    意: 
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
    static CString GetEventTypeDescribe(EmEventType emType );
	


	/*=============================================================================
    函 数 名:ResumeMem
    功    能:重置成员为初始状态
    参    数: 
    注    意: 
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
	 static void  ResumeMem();
   
protected:
	static u32  m_dwPrintMsgType;   //要打印的消息类型
	static u32  m_dwPrintMsgID;     //要打印的消息号
	static u32  m_dwPrintRangeMax;  //要打印的消息范围 中的最大值
	static u32  m_dwPrintRangeMin;  //要打印的消息范围 中的最小值
	static BOOL32 m_bPrintMsgBdy;    //是否要打印消息体
	static BOOL32 m_bPrintAllMsg;    //是否要打印全部消息
	static BOOL32 m_bPrintEnterMsg;  //是否要打印入口处消息
	static BOOL32 m_bPrintOutMsg;     //是否要打印出口处消息
	static BOOL32 m_bPrintTelnetMsg;  //是否要打印telnet消息
    static u8     m_bayPrintLevel;    //当前的打印级别.   0 不打印 
	static map<u16, u8>       m_mapEventLevel;         // 消息级别
    static map<u16, CString>   m_mapEventsName;        // 消息名称映射表
	
	static CPrintCtrl* m_pPrtCtrl;

	
	 
};




#endif // !defined(AFX_PRINTCTRL_H__9355B609_A421_4E87_8928_6D78ADA82BDA__INCLUDED_)
