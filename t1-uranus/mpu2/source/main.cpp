#include "umsboardinst.h"
#include "tplog.h"
#include "tpmsginit.h"
#include "eventoutmpu2tp.h"
#include "umsvmpinst.h"
#include "umsconfig.h"

//Protocol_file

#include "qtinterface.h"
#include "qtstruct.h"


#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
#include "nipwrapper.h"
#include "umsapi.h"
#include "codecwrapperdef_hd.h"
#endif

#ifdef WIN32
#define emUmsVmpExeFileName "umsvmp"
#define emUmsVmpKdvLogCfg "umsvmplog.ini"
#define emUmsVmpCfg "umsvmpcfg.ini"
#else

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_LINUX12_)
#define emUmsVmpExeFileName "/usr/bin/mpu2"
#define emUmsVmpExceptionFileName "/usr/conf/umsvmpexception.txt"
#define emUmsVmpKdvLogCfg "/usr/conf/umsvmplog.ini"
#define emUmsVmpCfg "/usr/conf/umsvmpcfg.ini"

#else
#define emUmsVmpExeFileName "/tp/umsvmp"
#define emUmsVmpExceptionFileName "/tp/umsvmpexception.txt"
#define emUmsVmpKdvLogCfg "/tp/umsvmplog.ini"
#define emUmsVmpCfg "/tp/umsvmpcfg.ini"
#endif

#endif

#ifdef _LINUX_

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
#define emVmpStyleCfg "/usr/conf/vmpstylecfg.ini"
#else
#define emVmpStyleCfg "/tp/vmpstylecfg.ini"
#endif

#else

#define emVmpStyleCfg "vmpstylecfg.ini"

#endif

BOOL32 g_bVmpStyleUp = FALSE;
u32    g_dwBWScale = 75;
extern u32 g_dwMpu2tpNetBandMul;


API void init(u16 wDstChan, char* szRcvIP, u16 wPort)
{
	TVmpRegAck tAck;
	TVmpTimeSpan tSpan;

	tAck.m_dwRcvIP = inet_addr(szRcvIP);
	tAck.m_wRcvPort = wPort;

	tSpan.m_wFirstTimeSpan = 100;
	tSpan.m_wSecondTimeSpan = 200;
	tSpan.m_wThirdTimeSpan = 400;
	tSpan.m_wRejectTimeSpan = 800;

	s8 szBuf[sizeof(TVmpRegAck)+sizeof(TVmpTimeSpan)] = {0};
	memcpy(szBuf, &tAck, sizeof(tAck));
	memcpy(szBuf+sizeof(tAck), &tSpan, sizeof(tSpan));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_regist_ack);
	cMsg.SetBody(szBuf, sizeof(szBuf));
	cMsg.Post(MAKEIID(AID_MPU2TP_APP, wDstChan));
}

API void startvmp(u16 wDstChan, u16 wStyle)
{
	TVmpStartParam tInfo;
	tInfo.m_tStyleInfo.m_emVmpStyle = (EmUmsVmpStyle)wStyle;
	tInfo.m_tStyleInfo.m_emShowMode = ums_vmp_black_mode;
	tInfo.m_tStyleInfo.m_byMemberNum = (u8)wStyle;

	BOOL32 bMerg3 = false;
	if ( wStyle > 3 )
	{
		bMerg3 = TRUE;
	}
	
	BOOL32 bMerg6 = false;
	if ( wStyle > 6 )
	{
		bMerg6 = TRUE;
	}
	for ( u16 wIndex = 0; wIndex < wStyle; wIndex ++ )
	{
		tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_dwHandle = wIndex+1;
		tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = false;
		
		if ( bMerg3 && wIndex < 3 )
		{
			tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = TRUE;
		}
		
		if ( bMerg6 && wIndex < 6 )
		{
			tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = TRUE;
		}
	}

	tInfo.m_tEncParam.m_byEncType = MEDIA_TYPE_H264;
	tInfo.m_tEncParam.m_byFrameRate = 30;
	tInfo.m_tEncParam.m_byProfileType = 1;
	tInfo.m_tEncParam.m_wBitRate = 2048;
	tInfo.m_tEncParam.m_wVideoHeight = 1080;
	tInfo.m_tEncParam.m_wVideoWidth = 1920;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_start_req);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(MAKEIID(AID_MPU2TP_APP, wDstChan));
	
}

API void changevmp(u16 wDstChan, u16 wStyle)
{
	TVmpMdyInfo tInfo;
	tInfo.m_wServiceID = wDstChan;

	tInfo.m_tStyleInfo.m_emVmpStyle = (EmUmsVmpStyle)wStyle;
	tInfo.m_tStyleInfo.m_emShowMode = ums_vmp_black_mode;
	tInfo.m_tStyleInfo.m_byMemberNum = (u8)wStyle;

	BOOL32 bMerg3 = false;
	if ( wStyle > 3 )
	{
		bMerg3 = TRUE;
	}

	BOOL32 bMerg6 = false;
	if ( wStyle > 6 )
	{
		bMerg6 = TRUE;
	}
	for ( u16 wIndex = 0; wIndex < wStyle; wIndex ++ )
	{
		tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_dwHandle = wIndex+1;
		tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = false;

		if ( bMerg3 && wIndex < 3 )
		{
			tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = TRUE;
		}

		if ( bMerg6 && wIndex < 6 )
		{
			tInfo.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged = TRUE;
		}
	}
	
	tInfo.m_tEncParam.m_byEncType = MEDIA_TYPE_H264;
	tInfo.m_tEncParam.m_byFrameRate = 30;
	tInfo.m_tEncParam.m_byProfileType = 1;
	tInfo.m_tEncParam.m_wBitRate = 2048;
	tInfo.m_tEncParam.m_wVideoHeight = 1080;
	tInfo.m_tEncParam.m_wVideoWidth = 1920;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_mdy_param);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(MAKEIID(AID_MPU2TP_APP, wDstChan));
	

}

API void testframe(u16 wChanID)
{
	OspInstDump(AID_MPU2TP_APP, wChanID, em_ask_frame);
}

API void showvmp(u16 wChanID)
{
	OspInstDump(AID_MPU2TP_APP, wChanID, em_show_info);
}

BOOL32 g_bLogon = FALSE;
API void logon()
{
	g_bLogon = TRUE;
}
API void logoff()
{
	g_bLogon = FALSE;
}

API void showenc(u16 wVmpID)
{
	OspInstDump(AID_MPU2TP_APP, wVmpID, em_show_enc);
}

#define VER_mpu2tp_ver  UMS_VerID
API void ver()
{
	msgprint("mpu2tp ver: %s  compile time: %s, %s\n", VER_mpu2tp_ver, __DATE__,  __TIME__);
}

API void shownetbandmul(void)
{
	msgprint("mpu2tp net band mul : %d ", g_dwMpu2tpNetBandMul);
}


API void setnetbandmul(u32 dwmul)
{
	if (dwmul)
	{
        g_dwMpu2tpNetBandMul = dwmul;
	}
}
s8* GetVmpStyleFile()
{
	return emVmpStyleCfg;
	//	return NULL;
}
void ReadBWScaleInfo()
{
	msgprint("[ReadBWScaleInfo] Begin Read.\n");

	const s8* pszCfgFile = GetVmpStyleFile();
	if (NULL == pszCfgFile)
	{
		msgprint("read failure\n");
		return ;
	}

	FILE* pfFile = fopen(pszCfgFile,"rb"); //文件不存在，创建
	if (NULL == pfFile)
	{
		msgprint("open brdcfg file %s failure. \n", pszCfgFile);
		return ;
	}

	// file vaild
	fseek(pfFile,0L,SEEK_END);
	u32  dwLen = ftell(pfFile);
	if (dwLen <= 0)
	{
		return  ;
	}

	if ( NULL != pfFile )
	{
		fclose(pfFile);
		pfFile = NULL;
	}
	int wValue = 0;
	BOOL32 bRet;
	bRet = GetRegKeyInt(GetVmpStyleFile(), "LocalInfo", "BWScale", 75, &wValue);
	if (bRet)
	{
		g_dwBWScale = wValue;
	}
	
	msgprint("bwscale: %d \n", g_dwBWScale);
	

}
API void readbw()
{
	ReadBWScaleInfo();	
}

API void help()
{
	OspPrintf(TRUE, FALSE, "logon/logoff()                               ---打开/关闭打印\n");
	OspPrintf(TRUE, FALSE, "semlogoff()                                  ---关闭是否阻塞的打印\n");
	OspPrintf(TRUE, FALSE, "semlogon()                                   ---放开是否阻塞的打印\n");
	OspPrintf(TRUE, FALSE, "showsem()                                    ---打印是否阻塞\n");
	OspPrintf(TRUE, FALSE, "ver()                                        ---版本信息和编译时间\n");
	OspPrintf(TRUE, FALSE, "init(u16 wDstChan, char* szRcvIP, u16 wPort) ---模拟初始化一个合成器\n");
	OspPrintf(TRUE, FALSE, "startvmp(u16 wDstChan, u16 wStyle)           ---开启合成\n");
	OspPrintf(TRUE, FALSE, "testframe(u16 wChanID)                       ---测试关键帧请求消息\n");
	OspPrintf(TRUE, FALSE, "showvmp(u16 wChanID)                         ---打印合成器相关信息\n");
	OspPrintf(TRUE, FALSE, "addvmpchan(u16 wDstChan, u16 wChanIndex)     ---添加一个合成成员\n");
	OspPrintf(TRUE, FALSE, "delvmpchan(u16 wDstChan, u16 wChanIndex)     ---删除一个合成成员\n");
	OspPrintf(TRUE, FALSE, "stopvmp(u16 wDstChan)                        ---停止合成\n");
	OspPrintf(TRUE, FALSE, "changevmp(u16 wDstChan, u16 wStyle)          ---调整合成\n");
	OspPrintf(TRUE, FALSE, "showenc(u16 wVmpID)                          ---打印是否编码\n");
	OspPrintf(TRUE, FALSE, "shownetbandmul(void))                        ---查询mpu2tp net band 扩大倍数(15:代表1.5倍；20:代表2.0 倍)\n");
	OspPrintf(TRUE, FALSE, "setnetbandmul(u32 dwmul)                     ---设置mpu2tp net band 扩大倍数(15:代表1.5倍；20:代表2.0 倍)\n");
}

API void addvmpchan(u16 wDstChan, u16 wChanIndex)
{
	TVmpChanInfo tInfo;
	tInfo.m_wChanIndex = wChanIndex;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_addchan_req);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(MAKEIID(AID_MPU2TP_APP, wDstChan));

}

API void delvmpchan(u16 wDstChan, u16 wChanIndex)
{
	TVmpChanInfo tInfo;
	tInfo.m_wChanIndex = wChanIndex;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_delchan_req);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(MAKEIID(AID_MPU2TP_APP, wDstChan));
	
}

API void stopvmp(u16 wDstChan)
{
	OspPost(MAKEIID(AID_MPU2TP_APP, wDstChan), ev_mpu2tp_stop_req, NULL, 0);
}

API void loglog()
{
	SetLogFlush();
}


#include <stdio.h>
namespace UmsTpmsg {
extern void regist_tpmsg_commond();
}
API void RegAllXmlCommand();
void ReadVmpStyleInfo();
int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV vmp SYSTEM                   *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");

#ifdef _LINUX_ //异常捕获
	regist_exception(emUmsVmpExeFileName, emUmsVmpExceptionFileName);
#endif

	if(!OspInit(TRUE, TELNET_UMSVMP_PORT))
	{
		printf("Osp Init failed! \n");
	}

#if defined(_LINUX12_)
	TpMakeDir("/usr/conf/");
	BrdInit();
	BrdDelUser (UMS_UserName,UMS_UserName, USER_TYPE_FTP);
	BrdAddUser(UMS_UserName_New,UMS_PassWord_New,USER_TYPE_FTP);
	BrdDelUser(UMS_UserName,UMS_UserName, USER_TYPE_TELNET_SUPER);
	BrdAddUser(UMS_UserName_New, UMS_PassWord_New, USER_TYPE_TELNET_SUPER);
	BrdWebsEnable(BRD_WEBS_DISABLE); // 设置nip的web服务失效
#endif

#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("init", (void*)init, "init(u16 wDstChan)");
	OspRegCommand("startvmp", (void*)startvmp, "startvmp(u16 wDstChan)");
	OspRegCommand("addvmpchan", (void*)addvmpchan, "addvmpchan(u16 wDstChan, u16 wChanIndex)");
	OspRegCommand("delvmpchan", (void*)delvmpchan, "delvmpchan(u16 wDstChan, u16 wChanIndex)");
	OspRegCommand("stopvmp", (void*)stopvmp, "stopvmp(u16 wDstChan)");
	OspRegCommand("testframe", (void*)testframe, "testframe(u16 wDstChan)");
	OspRegCommand("showvmp", (void*)showvmp, "showvmp(u16 wDstChan)");
	OspRegCommand("changevmp", (void*)changevmp, "changevmp(u16 wDstChan)");
	OspRegCommand("showenc", (void*)showenc, "showenc(u16 wVmpID)");
	OspRegCommand("loglog", (void*)loglog, "loglog");
    OspRegCommand("shownetbandmul", (void*)shownetbandmul, "shownetbandmul()");
	OspRegCommand("setnetbandmul", (void*)setnetbandmul, "setnetbandmul(u32 dwmul)");
	OspRegCommand("readbw", (void*)readbw, "readbw()");
#endif

	InitUmsEvent();

	RegAllXmlCommand();
	regist_tpmsg_commond();
	regist_tp_commond();

	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
	OspSetPrompt("UmsVmp");

	initKdvLog( emUmsVmpKdvLogCfg, FALSE );

#ifdef _DEBUG
	tploglow(0);
#else
	tplogoff();
#endif
	
	OspDelay(100);
	msgprint("\t**********************************************\n");
	msgprint("\t*                                            *\n");
	msgprint("\t*          KDV mpu2-tp Starting ...          *\n");
	msgprint("\t*                                            *\n");
	msgprint("\t**********************************************\n");

    //Protocol_file

	TQtInitParam tParam;
	QtLibInit(tParam);


	EMBrdType emBrdType = em_mpu2_tp_brd;
	StartCallBack pCall = (StartCallBack)InitUmsVmp;
	StartBoardServer(emBrdType, pCall);
	ReadVmpStyleInfo();
	ReadBWScaleInfo();
 	while(true)
 	{
 		OspDelay(100);
 	}
	
	//Protocol_file
	QtLibQuit();

	StopApp();

	return 0;
}



void WriteDefautVmpStyleInfoToFile()
{
	SetRegKeyString(GetVmpStyleFile(), "LocalInfo", "VmpStyle", "0");
}


void ReadVmpStyleInfo()
{
	msgprint("[ReadVmpStyleInfo] Begin Read.\n");
	
	const s8* pszCfgFile = GetVmpStyleFile();
	if (NULL == pszCfgFile)
	{
		msgprint("read failure\n");
		return ;
	}

	FILE* pfFile = fopen(pszCfgFile,"rb"); //文件不存在，创建
	if (NULL == pfFile)
	{
		msgprint("open brdcfg file %s failure. \n", pszCfgFile);
		return ;
	}
	
	// file vaild
	fseek(pfFile,0L,SEEK_END);
	u32  dwLen = ftell(pfFile);
	if (dwLen <= 0)
	{
		return ;
	}
	
	if ( NULL != pfFile )
	{
		fclose(pfFile);
		pfFile = NULL;
	}
	
	BOOL32 bRet;
	int wValue = 0;
	bRet = GetRegKeyInt(GetVmpStyleFile(), "LocalInfo", "VmpStyle", 0, &wValue);
	if (!bRet)
	{
		msgprint("read vmp style failure.\n");
		g_bVmpStyleUp = FALSE;
	}
	else
	{
		if (wValue)
		{
			g_bVmpStyleUp = TRUE;
		}
		else
		{
			g_bVmpStyleUp = FALSE;
		}
		
		msgprint("read vmp style g_bVmpStyleUp:%d.\n", g_bVmpStyleUp);
	}
}