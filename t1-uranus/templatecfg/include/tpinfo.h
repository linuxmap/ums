#ifndef TP_INFO_H
#define TP_INFO_H
#include "tpstruct.h"
#include "tpcfgdata.h"

#define TP_FILE_NAME_LEN 255	//�ļ�����󳤶�

//��װģ��������Ϣ����ԭ����ɢ�����ݺͽӿڽ��й���
class CTemplateInfo
{
public:
	//����
	static CTemplateInfo&	Instance();

private:
	CTemplateInfo();
public:
	~CTemplateInfo();

public:
	//��ʼ������ȡ�����ļ�
	BOOL32		Init();
	//����ģ��
	BOOL32		UpLoadTempFromFile(s8* szFileName);
	//��ȡָ��λ�õ�ģ��
	BOOL32		GetConfTempInfo(TConfTemplateLocal &tTpConfTemplate, u16 wIndex);
	//����ģ��
	BOOL32		SetConfTempInfo(TConfTemplateLocal& tTpConfTemplate, u16 wIndex);
	//ɾ��ָ������λ�õ�ģ����Ϣ
	BOOL32		DelConfTempInfo(u16 wIndex);
	//������е�ģ��
	void		GetAllConfTemp(TConfTemplateLocal atConfTemplate[TP_CONFTEMPLATE_MAXNUM]);
	//���������Ϣ
	void		GetControlData(TControlData& tControlData);
	//���ض�Ӧ������λ���Ƿ���Ч
	BOOL32		IsValid(u16 wIndex);

	SEMHANDLE&	getSem() { return m_semConfLock; }	

private:
	//��ȡ�����ļ�
	BOOL32		LoadControlFile();
	//��ȡģ���ļ�
	BOOL32		LoadTpFile();
	//��ָ�����ļ��ж�ȡģ��
	BOOL32		LoadTemplate(FILE *pFile, TConfTemplateLocal& tConfTemp, s8* szSectionBuf);

private:
	//���ļ��ж�ȡ����
	BOOL32 ReadIntegerValue(FILE* pFile, const s8 *const  pchSection, const s8 *const  pchKey, u32& dwVal);
	//���ļ��ж�ȡ�ַ���
	BOOL32 ReadStringValue(FILE* pFile, const s8 *const  pchSection, const s8 *const  pchKey, s8* pchBuf, u16 wLen);
	//��ȡģ����ն�
	BOOL32 ReadEpList(FILE* pFile, const s8* const pchSection, TEpAddrList& tEpList);
	//��ȡ��ѯ�б�
	BOOL32 ReadTurnList(FILE* pFile, const s8* const pchSection, TConfTurnList& tTurnList);
	//��ȡ���������б�
	BOOL32 ReadAudMixList(FILE* pFile, const s8* const pchSection, TAuxMixList& tAudMixInfo);
	//��ȡ����Ƶ�ֱ���
	BOOL32 ReadMainVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat emRes[], u16 wMainResNum);
	//��ȡ����Ƶ�ֱ���
	BOOL32 ReadMinorVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat emRes[], u16 wMinorResNum);
	//��ȡ��Ƶ��ʽ by ywd
	BOOL32 ReadAudioRes(FILE* pFile,const s8* const pchSection,TUmsAudFormat emRes[],u16 wAudioResNum);
	//��ȡ������Ϣ
	BOOL32 ReadEncryptInfo(FILE* pFile, const s8* const pchSection, TTPEncrypt& tEncryptInfo);
	//��ȡ�ϳ�Ԥ����Ϣ
	BOOL32 ReadVmpMemberCfg(FILE* pFile, const s8* const pchSection, TSaveVmpCfg& tVmpMemberCfg);
    //��ȡ�᳡������Ϣ
	BOOL32 ReadEpCallProcotol(FILE* pFile, const s8* const pchSection, TTemplateConfEx& tTempex,TEpAddrList& tEpList);

private:
	s8					m_szControlFile[TP_FILE_NAME_LEN+1];	//���������ļ���
	s8					m_szTpFileName[TP_FILE_NAME_LEN+1];		//ģ���ļ���
	s8					m_szTpFolder[TP_FILE_NAME_LEN+1];
	TControlData		m_tControlData;							
	TConfTemplateLocal		m_atConfTemplate[TP_CONFTEMPLATE_MAXNUM];	//ģ����Ϣ
	SEMHANDLE			m_semConfLock;	

private:
private:
	static s8 s_validTpNum[];
	static s8 s_validTpNumKey[];
	static s8 s_validSeq_[];

	static s8 s_tpMeetingName[];	//��������
	static s8 s_tpE164[];			//����E164
	static s8 s_tpStartTime[];		//��ʼʱ��
	static s8 s_tpEpAddrNum[];		//��������
	static s8 s_tpEpAddrID_[];		//���˵�ID
	static s8 s_tpIsAliasIP[];		//�Ƿ��Ǳ�����IP����
	static s8 s_tpEpAddrAlias_[];	//���˵����
	static s8 s_tpEpAddrAliasType_[];	//���˵��������
	static s8 s_tpEpAddrE164_[];	//���˵�E164
	static s8 s_tpEpAddrE164Type_[];	//���˵�E164����
	static s8 s_tpEpAddrCallType_[];    //���˵��������
	static s8 s_tpEpAddrIP_[];	//���˵�E164
	static s8 s_tpEpAddrIPType_[];	//���˵�E164����
 	static s8 s_tpAuxMixID_[];		//����ID����
	static s8 s_tpDiscussOn[];       //���ۿ���
	static s8 s_tpDiscussVacOn[];   //����������������
	static s8 s_tpTurnInterval[];	//��ѯ���
	static s8 s_tpTurnOn[];         //��ѯ����״̬
	static s8 s_tpTurnNum[];		//������ѯ������
	static s8 s_tpTurnID_[];		//��ѯ�б�ID����

	static s8 s_tpMainVidNum[];     //����Ƶ����
	static s8 s_tpMinorVidNum[];    //����Ƶ����
	static s8 s_tpMainVideoRes_[];  //����Ƶ�ֱ���
	static s8 s_tpMinorVideoRes_[]; //����Ƶ�ֱ���
	static s8 s_tpMainVideoLvl_[];  //����Ƶ�ֱ���ˮƽ
	static s8 s_tpMinorVideoLvl_[];  //����Ƶ�ֱ���ˮƽ
	static s8 s_tpMainVideoFrame_[];  //����Ƶ֡��
	static s8 s_tpMinorVideoFrame_[]; //����Ƶ֡��
	static s8 s_tpAudioNum[];		//��Ƶ
	static s8 s_tpAudioFormat_[];  //��Ƶ
	static s8 s_tpAudioFreq_[];  //��Ƶ
	static s8 s_tpAudioReservel_[]; //��Ƶ
	static s8 s_tpHpConfBitRate[];
	static s8 s_tpConfDualBitRate[];
	static s8 s_tpEncryptKey[] ;//��Կ
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