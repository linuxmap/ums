#ifndef _h_umsueinit_h__
#define _h_umsueinit_h__

#define TP_MAX_USR_FILE_PATH_LEN	128			//UMSUE中存储用户信息的文件路径的长度

//UeCfg : 
typedef struct tagTUmsUeCfg
{
	u32 m_dwServiceInst;			//业务的APPID + INSTID
	u32 m_dwUeInst;					//界面的APPID + INSTID
	u16 m_wListenPort;				//业务侦听端口
	s8  m_acUsrInfoFilePath[TP_MAX_USR_FILE_PATH_LEN];
	u32	m_dwToolInst;				//维护工具的APPID + INSTID
	tagTUmsUeCfg()
	{
		memset( this, 0, sizeof(tagTUmsUeCfg));
	}
}TUmsUeCfg;


void InitUeLib(TUmsUeCfg& tCfg);
#endif // _h_umsueinit_h__
