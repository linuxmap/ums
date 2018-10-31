#ifndef TP_INFO_H
#define TP_INFO_H
#include "tpstruct.h"
#include "tpcfgdata.h"

#define TP_FILE_NAME_LEN 255	//文件名最大长度

//封装模板的相关信息，对原来零散的数据和接口进行管理
class CTemplateInfo
{
public:
	//单件
	static CTemplateInfo&	Instance();

private:
	CTemplateInfo();
public:
	~CTemplateInfo();

public:
	//初始化，读取配置文件
	BOOL32		Init();
	//导入模板
	BOOL32		UpLoadTempFromFile(s8* szFileName);
	//获取指定位置的模板
	BOOL32		GetConfTempInfo(TConfTemplateLocal &tTpConfTemplate, u16 wIndex);
	//设置模板
	BOOL32		SetConfTempInfo(TConfTemplateLocal& tTpConfTemplate, u16 wIndex);
	//删除指定索引位置的模板信息
	BOOL32		DelConfTempInfo(u16 wIndex);
	//获得所有的模板
	void		GetAllConfTemp(TConfTemplateLocal atConfTemplate[TP_CONFTEMPLATE_MAXNUM]);
	//获得配置信息
	void		GetControlData(TControlData& tControlData);
	//返回对应索引的位置是否有效
	BOOL32		IsValid(u16 wIndex);

	SEMHANDLE&	getSem() { return m_semConfLock; }	

private:
	//读取控制文件
	BOOL32		LoadControlFile();
	//读取模板文件
	BOOL32		LoadTpFile();
	//从指定的文件中读取模板
	BOOL32		LoadTemplate(FILE *pFile, TConfTemplateLocal& tConfTemp, s8* szSectionBuf);

private:
	//从文件中读取整数
	BOOL32 ReadIntegerValue(FILE* pFile, const s8 *const  pchSection, const s8 *const  pchKey, u32& dwVal);
	//从文件中读取字符串
	BOOL32 ReadStringValue(FILE* pFile, const s8 *const  pchSection, const s8 *const  pchKey, s8* pchBuf, u16 wLen);
	//读取模板的终端
	BOOL32 ReadEpList(FILE* pFile, const s8* const pchSection, TEpAddrList& tEpList);
	//读取轮询列表
	BOOL32 ReadTurnList(FILE* pFile, const s8* const pchSection, TConfTurnList& tTurnList);
	//读取会议讨论列表
	BOOL32 ReadAudMixList(FILE* pFile, const s8* const pchSection, TAuxMixList& tAudMixInfo);
	//读取主视频分辨率
	BOOL32 ReadMainVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat emRes[], u16 wMainResNum);
	//读取辅视频分辨率
	BOOL32 ReadMinorVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat emRes[], u16 wMinorResNum);
	//读取音频格式 by ywd
	BOOL32 ReadAudioRes(FILE* pFile,const s8* const pchSection,TUmsAudFormat emRes[],u16 wAudioResNum);
	//读取加密信息
	BOOL32 ReadEncryptInfo(FILE* pFile, const s8* const pchSection, TTPEncrypt& tEncryptInfo);
	//读取合成预案信息
	BOOL32 ReadVmpMemberCfg(FILE* pFile, const s8* const pchSection, TSaveVmpCfg& tVmpMemberCfg);
    //读取会场呼叫信息
	BOOL32 ReadEpCallProcotol(FILE* pFile, const s8* const pchSection, TTemplateConfEx& tTempex,TEpAddrList& tEpList);

private:
	s8					m_szControlFile[TP_FILE_NAME_LEN+1];	//控制配置文件名
	s8					m_szTpFileName[TP_FILE_NAME_LEN+1];		//模板文件名
	s8					m_szTpFolder[TP_FILE_NAME_LEN+1];
	TControlData		m_tControlData;							
	TConfTemplateLocal		m_atConfTemplate[TP_CONFTEMPLATE_MAXNUM];	//模板信息
	SEMHANDLE			m_semConfLock;	

private:
private:
	static s8 s_validTpNum[];
	static s8 s_validTpNumKey[];
	static s8 s_validSeq_[];

	static s8 s_tpMeetingName[];	//会议名称
	static s8 s_tpE164[];			//会议E164
	static s8 s_tpStartTime[];		//开始时间
	static s8 s_tpEpAddrNum[];		//呼叫数量
	static s8 s_tpEpAddrID_[];		//与会端点ID
	static s8 s_tpIsAliasIP[];		//是否是别名加IP呼叫
	static s8 s_tpEpAddrAlias_[];	//与会端点别名
	static s8 s_tpEpAddrAliasType_[];	//与会端点别名类型
	static s8 s_tpEpAddrE164_[];	//与会端点E164
	static s8 s_tpEpAddrE164Type_[];	//与会端点E164类型
	static s8 s_tpEpAddrCallType_[];    //与会端点呼叫类型
	static s8 s_tpEpAddrIP_[];	//与会端点E164
	static s8 s_tpEpAddrIPType_[];	//与会端点E164类型
 	static s8 s_tpAuxMixID_[];		//混音ID数组
	static s8 s_tpDiscussOn[];       //讨论开关
	static s8 s_tpDiscussVacOn[];   //讨论语音激励开关
	static s8 s_tpTurnInterval[];	//轮询间隔
	static s8 s_tpTurnOn[];         //轮询开关状态
	static s8 s_tpTurnNum[];		//参与轮询的数量
	static s8 s_tpTurnID_[];		//轮询列表ID数组

	static s8 s_tpMainVidNum[];     //主视频数量
	static s8 s_tpMinorVidNum[];    //辅视频数量
	static s8 s_tpMainVideoRes_[];  //主视频分辨率
	static s8 s_tpMinorVideoRes_[]; //辅视频分辨率
	static s8 s_tpMainVideoLvl_[];  //主视频分辨率水平
	static s8 s_tpMinorVideoLvl_[];  //辅视频分辨率水平
	static s8 s_tpMainVideoFrame_[];  //主视频帧率
	static s8 s_tpMinorVideoFrame_[]; //辅视频帧率
	static s8 s_tpAudioNum[];		//音频
	static s8 s_tpAudioFormat_[];  //音频
	static s8 s_tpAudioFreq_[];  //音频
	static s8 s_tpAudioReservel_[]; //音频
	static s8 s_tpHpConfBitRate[];
	static s8 s_tpConfDualBitRate[];
	static s8 s_tpEncryptKey[] ;//秘钥
    static s8 s_tpEncryptFreq[];
	static s8 s_tpEncryptType[];
	static s8 s_tpDefaultEncrypt[];
	static s8 s_tpConfUpBandWid[];
	static s8 s_tpConfDownBandWid[];
	static s8 s_tpVmpPlanStyle[];
	static s8 s_tpVmpPlanEpNum[];
	static s8 s_tpVmpPlanEpAlias_[];
	static s8 s_tpVmpPlanScrIndex_[];
	static s8 s_tpVmpPlanSpeakIndex[];
	static s8 s_tpVmpPlanDualIndex[];
	static s8 s_tpEpCallProtocol_[];
};

#endif