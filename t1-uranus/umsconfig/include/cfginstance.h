 /*****************************************************************************
   模块名      : KDVMT MtAgent
   文件名      : CCfgDataManager.h
   相关文件    : CCfgDataManager.cpp
   文件实现功能: KDVMT 代理基类头文件
   作者        : 
   版本        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2005/03/24  1.0         耿昌明       创建
   2005/07/21  4.0         张  飞       修改：为CCfgDataManager添加获取文件名称函数
                                        修改： CIMtCfg消息内容，修改InstanceEntry实现方式
   
******************************************************************************/

#ifndef _CFGDATAMAN_HEADER_
#define _CFGDATAMAN_HEADER_

#include "osp.h"
#include "kdvsys.h"
#include "cfgdata.h"
class CPersistCfg : public CInstance
{
public:
	CPersistCfg();
	virtual ~CPersistCfg();
	
	virtual void InstanceEntry( CMessage* const pcMsg );
	void InstanceDump( u32 param ){};
	void InstanceExit(){};
protected:
	void OnInitPersist(u8* buf,u16 wLen);
	void OnUpdateData(u8* buf ,u16 wLen);
	void OnSaveFileData(u8* buf,u16 wLen);
	void OnSaveFileImmediately(u8* buf,u16 wLen);
    void OnSaveMtbFileData(u8* buf, u16 wlen); // add by wangliang for batchcfg 2007/01/09
protected:
	BOOL PersistFileData();
	BOOL WriteFileToRawDisk();
private:
	u8*  m_pbySaveData;
    u32  m_dwDataSize;
	BOOL m_bNeedSaveCfgData;
	s8   m_achFileName[256];
	TALLConfigData m_tALLConfigDataBak;
};

typedef zTemplate<CPersistCfg> CCfgDataApp;

#endif


