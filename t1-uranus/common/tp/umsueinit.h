#ifndef _h_umsueinit_h__
#define _h_umsueinit_h__

#define TP_MAX_USR_FILE_PATH_LEN	128			//UMSUE�д洢�û���Ϣ���ļ�·���ĳ���

//UeCfg : 
typedef struct tagTUmsUeCfg
{
	u32 m_dwServiceInst;			//ҵ���APPID + INSTID
	u32 m_dwUeInst;					//�����APPID + INSTID
	u16 m_wListenPort;				//ҵ�������˿�
	s8  m_acUsrInfoFilePath[TP_MAX_USR_FILE_PATH_LEN];
	u32	m_dwToolInst;				//ά�����ߵ�APPID + INSTID
	tagTUmsUeCfg()
	{
		memset( this, 0, sizeof(tagTUmsUeCfg));
	}
}TUmsUeCfg;


void InitUeLib(TUmsUeCfg& tCfg);
#endif // _h_umsueinit_h__
