/*****************************************************************************
ģ����      : �ն˿���̨
�ļ���      : MtcLibIntTest.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���ɲ��Խӿ�
����        : �ܹ㻯
�汾        : V3.0  Copyright(C) 1997-2004 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/02/01  3.0         �ܹ㻯      ����
2004/12/10  3.5         �����      �޸�Ϊ3.5��
2004/12/30  3.5         �����      ȥ�������ӿ�
******************************************************************************/
#pragma once
#include "MtcLib.h"

API u32 mtcinttestlibver();
API u32 mtcinttestlibhelp();

class CMtcLibIntTest
{
public:
	CMtcLibIntTest(void);
	virtual ~CMtcLibIntTest(void);

	virtual BOOL32 LinkInstance(u32 dwIP, u32 dwPort);
	virtual void DisLinkInstance(void);
	// �Ƿ��Ѻͱ�����ʵ����������
	virtual BOOL32 IsLinked(void);  

//////////////////////////////////////////////////////////////////////////
//CConnect
    //	��ѯ�տ��Ƿ��������ն�
	virtual BOOL32 IsMtcConnectedMt(void);
    //	��ѯ��ǰ�������ն�
	virtual BOOL32 GetConnectedMt(CMtcMt &mt);
    //	��ѯ��ǰ�û�
	virtual BOOL32 GetConnectedUser(CLoginRequest *pcLoginuser);
	  //�������ܣ��ն��Ƿ��ڿ���״̬
    virtual BOOL32 IsIdle();


//////////////////////////////////////////////////////////////////////////
//��ַ�����ɲ���

	//	�õ���ַ����Ŀ��
	virtual BOOL32 GetEntriesCount(u32 *pdwCount);
    //	�õ���ַ������
	virtual BOOL32 GetGroupCount(u32 *pdwCount);
    //	�õ���ַ����Ŀ��Ϣ
	virtual BOOL32 GetEntry(u32 dwIndex, CAddrEntry &entry);
    //	�õ�������Ŀ��Ϣ
	virtual BOOL32 GetFirstEntry(CAddrEntry &entry);
    //	�õ���һ����Ŀ��Ϣ
	virtual BOOL32 GetNextEntry(u32 u32Index, CAddrEntry &entry);
    //	�õ���ַ������Ϣ
	virtual BOOL32 GetGroup(u32 dwIndex, CAddrMultiSetEntry &mentry);
    //	�õ���������Ϣ
	virtual BOOL32 GetFirstGroup(CAddrMultiSetEntry &mentry);
    //	�õ���һ������Ϣ
	virtual BOOL32 GetNextGroup(u32 u32Index, CAddrMultiSetEntry &mentry);
	//��ѯһ��Ŀ�Ƿ����
	virtual BOOL32  IsEntryExist(CAddrEntry *pcEntry);
	//��ѯһ���Ƿ����
	virtual BOOL32 IsGroupExist(CAddrMultiSetEntry *pcAddrMentry);

//////////////////////////////////////////////////////////////////////////
// �û������ɲ���

	//����û�����
	virtual BOOL32 GetUserCounts(u32 *pdwCount);
	//��ѯһ�û��Ƿ����
	virtual BOOL32 IsUserExist(CUserFullInfo *pcUserInfo);

//////////////////////////////////////////////////////////////////////////
//������

    //	�õ�������Ϣ�б�
	virtual BOOL32 GetConfs(vector<TConfId>& vConf);
	//3.42	�õ���ǰ����
    virtual BOOL32 GetCurrentConf(TMtConfInfo *pConfInfo);
    //	��ѯ�Ƿ����ڵȴ����������Ӧ
	virtual BOOL32 IsWaitingCreateAck();
    //3.25	��ѯ�Ƿ����ڵȴ���������Ӧ
	virtual BOOL32 IsWaitingJoinAck();
    //3.26	��ѯ�Ƿ��ڻ�����
	virtual BOOL32 IsInMultConf();
    //3.27	��ѯ�Ƿ�������ѯ
	virtual BOOL32 IsPolling();
    //3.28	�õ�����ն���Ϣ�б�
	virtual BOOL32 GetMts(vector<CMtcMt>& vMts);    
    //3.29	�õ���ǰ������
	virtual BOOL32 GetSpeaker(CMtcMt *pcMtcMt);
    //3.30	�õ���ǰ��ϯ
	virtual BOOL32 GetChairman(CMtcMt *pcMtcMt);
    //3.31	�õ����������ն�
	virtual BOOL32 GetReqJoinMts(vector<CMtcMt>& vMts);
    //3.32	�õ����뷢�Ե��ն�
	virtual BOOL32 GetReqSpeakerMts(vector<CMtcMt>& vMts);
    //3.33	�õ�������ϯ���ն�
	virtual BOOL32 GetReqChairmanMts(vector<CMtcMt>& vMts);
	//�Ƿ�����
	virtual BOOL32 IsSpeaker();
	//�Ƿ���ϯ
	virtual BOOL32 IsChairman();
    //�Ƿ��ڲ廰
    virtual BOOL32 IsChime();
    //��ǰ��ƵԴ
    virtual BOOL32 GetCurVideoSource(CMtcMt *pMt);
    //�Ƿ�������
    virtual BOOL32 IsDiscuss();
    //�Ƿ�����������
    virtual BOOL32 IsVAC();
    //��ȡ��ǰ�Ļ��渴��״̬
    virtual BOOL32 GetVMPInfo(TMtVMPParam *ptVMPinfo);
    //�Ƿ��Ի�
    virtual BOOL32 IsSelpLoop();
    //��õ�ǰ�ն˿��յĸ���
    virtual BOOL32 GetNumOfSnapshot(u16 *pwNum);
	//3.44	�õ���ǰ����ѡ�����ն�
    virtual BOOL32 GetCurrentChoic(CMtcMt &Mt);
//////////////////////////////////////////////////////////////////////////
//��Ե����
	//3.21	��ѯ�Ƿ��ڵ�Ե������
	virtual BOOL32 IsInP2PConf();
    //3.22	��ѯ�Ƿ����ں���
	virtual BOOL32 IsCalling();
	//��ȡ��Ե�����еĺ�����
	virtual BOOL32 GetP2PCaller(CMtcMt *pMt);
//////////////////////////////////////////////////////////////////////////
//���
	//�Ƿ�˫��
	virtual BOOL32 IsDual();
	//��ȡ˫������
	virtual BOOL32 GetDualType(u8 *pchType);

//	virtual BOOL32 IsMonitorNear();
//    virtual BOOL32 IsMonitorFar();
	

	
//////////////////////////////////////////////////////////////////////////
//����
   //3.4	�õ���Ƶ����
//     virtual BOOL32 GetAudioSche(_TMATRIXINFO &ms);
    //3.5	�õ���Ƶ����
//     virtual BOOL32 GetVideoSche(_TMATRIXINFO &ms);
    //3.6	�õ���Ƶ����Դ
	virtual u32 GetAudioInputSrc();
    //3.7	�õ���Ƶ����Դ
	virtual u32 GetVideoInputSrc();
    //3.8	�Ƿ���
	virtual BOOL32 IsLocalSpeakerMute();
    //3.9	�Ƿ�����
	virtual BOOL32 IsLocalMicMute();
    //3.10	�õ��������
	virtual BOOL32 GetLocalSpeakerVolume(s32 *pnVolNum);
    //3.11	�õ���������
	virtual BOOL32 GetLocalMicVolume(s32 *pnVolNum);
    //3.12	�Ƿ�ң����ʹ��
	virtual BOOL32 IsEnableRemoteCtrl();
//////////////////////////////////////////////////////////////////////////
//�����ļ� 
//(�ٵ�������)  2:�Զ��л�Ϊ����ն�
//				3:��������
//				4:����˫��
//				5:�������
 
	//	�õ���ǰ����������
	virtual BOOL32 GetCfgLanguage(EmLanguage& emLanguage);
	//	��ȡH323��������Ϣ
	virtual BOOL32 GetCfgH323(PTH323Cfg pCfg);
    //	�õ���̫����������Ϣ
	virtual BOOL32 GetCfgEthnet(u8 byIndex, PTEthnetInfo pCfg);
	//	�õ���ǰ���û�������Ϣ
	virtual BOOL32 GetCfgUser(PTUserCfg pCfg);
	//	�õ���ǰ����Ƶ���ò���(����Ƶ�͸���Ƶ)
	virtual BOOL32 GetVideoParam(EmVideoType emType, PTVideoParam pCfg);
	//	�õ���ǰ��̨��������Ϣ
	virtual BOOL32 GetCfgOsd(PTOsdCfg pCfg);
	//	�õ���ǰ��E1������Ϣ
	virtual BOOL32 GetCfgE1(PTE1Config pCfg);
	//	�õ���ǰ�Ĵ���������Ϣ
	virtual BOOL32 GetCfgSerial(EmSerialType emType ,PTSerialCfg pCfg);
	//	�õ���ǰ��Qos������Ϣ
	virtual BOOL32 GetCfgQos(PTIPQoS pCfg);
	//	�õ���ǰ�ķ���ǽ������Ϣ
	virtual BOOL32 GetCfgFireWall(PTEmbedFwNatProxy pCfg);
	//	�õ�һ��·������
	virtual BOOL32 GetCfgRoute(u8 byIndex ,PTRouteCfg pCfg);
	//��ȡȫ����·��������Ϣ
	virtual BOOL32 GetAllRouteCfg(vector<TRouteCfg> &vctRouteCfg);
	//	�õ���ǰ��pppoe����
	virtual BOOL32 GetCfgPPPoE(PTPPPOECfg pCfg);
	//	�õ���ǰ��SNMP����
	virtual BOOL32 GetCfgSNMP(PTSNMPCfg pCfg);
	//	�õ���̬Napӳ�������
	virtual BOOL32 GetCfgNapMap(PTNATMapAddr pCfg);
	//	�õ������ش�������
	virtual BOOL32 GetCfgRetrans(TLostPackResend* pCfg);
	//	�Ƿ�AEC
	virtual	BOOL32 GetCfgAEC(BOOL32& bUsed);
	//	�Ƿ�AGC
	virtual BOOL32 GetCfgAGC(BOOL32& bUsed);
	//	�õ���ѡЭ�������
	virtual BOOL32 GetCfgAVPrior(PTAVPriorStrategy pCfg);
	//	�õ���������
	virtual BOOL32 GetCfgInVol(u8 &byVol);
	//	�õ��������
	virtual BOOL32 GetCfgOutVol(u8 &byVol);
	//	�õ�ͼ������
	virtual BOOL32 GetCfgImage(PTImageAdjustParam pCfg);
	//	�õ���Ƶ��ʽ������(����Ƶ�͸���Ƶ)
	virtual BOOL32 GetCfgVStandard(EmVideoType emType, EmVideoStandard &emStandard);
	//	�õ��������ʵ�����
	virtual BOOL32 GetCfgCallRate(u32 &dwCallRate);
	//	�õ�����ͷ������0....5
	virtual BOOL32 GetCfgCam(u8 byIndex, PTCameraCfg pCfg);
	//	�õ���ý�������
	virtual BOOL32 GetCfgStream(PTStreamMedia pCfg);
	 // ��ȡ��ǰ���ӽڵ��ʶ
	//2005 04 22 �ź���
	virtual u32 GetConnectedNodeID() const;
	virtual BOOL32 GetMtStatus(TTerStatus *pMtStatus);
protected:
    //����ͬ������
	BOOL32 SendEvent(u16 u16Event, const void *pBuf, u16 u16Size,
		void *pAckBuf, u16 u16AckSize, u16 &u16AckSizeRet);
private:
	// ��ǰ�������ӵĽڵ��ʶ
	u32 m_u32ConnectedNode;
	
};
