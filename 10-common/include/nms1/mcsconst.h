/*=============================================================================
ģ   ��   ��: �������̨ҵ���ܿ�
��   ��   ��: mcsconst.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: mcslib�г�������
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/04/26  4.0     ���        ����
=============================================================================*/

#ifndef _MCSCONST_20050426_H_
#define _MCSCONST_20050426_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "errorid.h"
#include "eventid.h"

#define AUTO_INC_VERSION		"4,4,3,358"

//  ¼���ļ�
#define MAX_FILE_NUM                    (s32)1000      //֧������ļ���

#define MCSLIB_OK                       (u16)0//���óɹ�
#define MCSLIB_BASE_ERROR               (u16)ERR_MC_BGN//�������׼ֵ
#define MCSLIB_ERROR_OSP_ALREADY_INIT   (u16)(ERR_MC_BGN + 1)//Osp �Ѿ���ʼ��
#define MCSLIB_ERROR_OSP_INIT           (u16)(ERR_MC_BGN + 2)//osp ��ʼ��ʧ��
#define MCSLIB_ERROR_OSP_NO_INIT        (u16)(ERR_MC_BGN + 3)//osp û�г�ʼ��
#define MCSLIB_ERROR_CREATE_APP		    (u16)(ERR_MC_BGN + 4)//����Ӧ��ʧ��  
#define MCSLIB_NO_MEMORY                (u16)(ERR_MC_BGN + 5)//�����ڴ����
#define MCSLIB_INVALID_WINDOW           (u16)(ERR_MC_BGN + 6)//��Ч�Ĵ��ھ��
#define MCSLIB_NOT_IN_IDLE_STATE        (u16)(ERR_MC_BGN + 7)//����Ѿ�������MCU
#define MCSLIB_NOT_REGISTER_WINDOW      (u16)(ERR_MC_BGN + 8)//���û��ע�ᴰ��
#define MCSLIB_MUST_WAIT                (u16)(ERR_MC_BGN + 9)//������ڴ���ǰһ����
#define MCSLIB_INVALID_PARAM            (u16)(ERR_MC_BGN + 10)//��Ч�Ĳ���
#define MCSLIB_FAIL_CONNECT_MCU         (u16)(ERR_MC_BGN + 11)//����MCUʧ��
#define MCSLIB_FAIL_POSTMSG_TO_MCU      (u16)(ERR_MC_BGN + 12)//��MCU������Ϣʧ��
#define MCSLIB_FAIL_ALREADY_CREATE      (u16)(ERR_MC_BGN + 13)//�����Ѿ�����
#define MCSLIB_FAIL_REG_SESSION		    (u16)(ERR_MC_BGN + 14)//ע��MCU����ʧ��
#define MCSLIB_FAIL_UNREG_SESSION       (u16)(ERR_MC_BGN + 15)//ע��MCU����ʧ��
#define MCSLIB_NOT_IN_NORMAL_STATE      (u16)(ERR_MC_BGN + 16)//��ػ�û������MCU
#define MCSLIB_MAXNUM_MCU               (u16)(ERR_MC_BGN + 17)//�����������ĿMCU

//  Mt������, ����MCU
#define MT_TYPE_LOCALMCU    (u8)90

//  �����Ŵ���
#define INDEX_ERR           -1

//MCU�ȴ��ظ�(��Ϊ��λ)
#define DELAY_TIME_DEFAULT      (u16)6

//  ���鼶������
typedef enum enumCascadeType
{
    emSingleConf        = 0,    //  �Ǽ�������
    emTwoLayerMMcuConf  = 1,    //  ��������, ����MCU���ϼ�
    emTwoLayerSMcuConf  = 2,    //  ��������, ����MCU���¼�
    emThreeLayerConf    = 3     //  ������������
} EMCascadeType;

//  ����MCU�������ݳ�ʼ��
typedef enum enumConfInitValue
{
    emLockInfo          = 0,        //  ����MCU������Ϣ
    emAllMtStatus       = 1,        //  �����ն�״̬, ����������MCU
    emAllMtAlias        = 2,        //  �����ն˱���, ����������MCU
    emAllMcuMediaSrc    = 3,        //  �����¼�MCUý��Դ
    emAllSMcuLockStatus = 4,        //  �����¼�MCU����״̬
    emAllSMcuMixParam   = 5,        //  �����¼�MCU��������
    emAllInfo           = 6         //  ������Ϣ
} EMConfInitValue;

//  ��������
typedef enum enumLangID
{
//    emChineseSimplified     = 0,        //  ��������
//    emChineseTraditional    = 1,        //  ��������
    emEnglish               = 0,        //  Ӣ��
    emChinese               = 1,        //  ����
    emOther                 = 3         //  ����(Ĭ��Ӣ��)
} EMLangID;

//  ʵ����
#define INSID_MCSLIB            (u16)1      //  mcslib��ʼʵ����
#define INSID_MCSLIB_TESTER     (u16)1      //  mcslib��Ԫ����testerʵ����
#define INSID_MCSLIB_MCU        (u16)1      //  mcslib��Ԫ����ģ��MCUʵ����
#define INSID_ADDRBOOK          (u16)1      //  ��ַ��
#define INSID_UM                (u16)1      //  �û�����

//  mcslib ״̬
#define MCSLIB_STATE_IDLE       (u16)100
#define MCSLIB_STATE_NORMAL     (u16)101

//  MCS�ȴ�MCU�ظ�ʱ�䣬OSP��ʱ(����Ϊ��λ)
#define DEFAULT_TIMEOUT         (u32)6000
//  MCU�ȴ��ظ�(��Ϊ��λ)
#define DELAY_TIME_DEFAULT      (u16)6
//  ���ӱ���MCU��ʱʱ��(1��)
#define CONNECT_BAKMCU_TIMEOUT  (s32)1000
//  ��ѯMCU��CPUʹ���ʳ�ʱʱ��(60��)
#define MCU_REFRESHMCU_TIMEOUT  (u32)60 * 1000

//  �����ϲ�����buffer��С, 32K
#define BUF_SIZE_TO_UI          (s32)(32 * 1024)

//  �������̨����MCU�����
#define MAXNUM_MCS_MCU          (s32)16

//  ��ѯ��ʼ�˿�
#define QUERY_PORT              (u16)6682

//  mcu������󳤶�
#define MAXLEN_MCU_NAME         (s32)64

//  �ն��б��������
#define MTTABLE_STEP            (s32)32

//  ��Ϣջ��󳤶�
#define QUEUE_SIZE              (u16)2000

// ÿ��sessionռ�Ķ˿���
#define MCS_SESSION_PORT_NUM    ((u16)(PORTSPAN*11))     
// ��ʼ�����˿�
#define MCS_MONITOR_BASE_PORT   (u16)7200   
// ���������˿�
#define MCS_MONITOR_END_PORT    ((u16)(MCS_MONITOR_BASE_PORT + (MAXNUM_MCS_MCU - 1)* MCS_SESSION_PORT_NUM ))

//  ���󷽰�������
#define MAXNUM_MATRIXSCHE       (s32)8

//  һ�鵥�������е��������ģ����
#define MAXNUM_BRDEQP           (s32)4

// H264 ר�÷ֱ���,�ڽ�����ʾ��
#define VIDEO_FORMAT_NULL                           255
// H264����MCU�滻�ķֱ���
#define VIDEO_FORMAT_H264REPL                       VIDEO_FORMAT_CIF

//¼���ļ�����󳤶�(����·���Լ�'\0')
#define MAXLEN_REC_FILE_NAME                        255

//�ն˱�����󳤶�
#define MCS_MAXLEN_ALIAS                                16

//���ɲ���
#define INTTEST_MAXNUM_ADDRENTRY    (u32)100    //ÿ�η��͵�ַ����Ŀ�����
#define INTTEST_MAXNUM_ADDRGROUP    (u32)40     //ÿ�η��͵�ַ�������������
#define INTTEST_MAXNUM_MT           (u32)60     //ÿ�η����ն�������
#define INTTEST_MAXNUM_PERI         (u32)30     //ÿ�η�������������
#define INTTEST_MAXNUM_BRD          (u32)14     //ÿ�η��͵�������������

#define FIRSTTIMESPAN               (u16)40      //��һ���ش�����
#define SECONDTIMESPAN              (u16)120     //�ڶ����ش�����
#define THIRDTIMESPAN               (u16)240     //�������ش�����
#define REJECTTIMESPAN              (u16)480     //���ڶ�����ʱ����

typedef enum enumTimerWaitState
{
    //  ��ʼ
    emTimerWaitNormal = 0,              //��0��ʼ��������
    //  ����MCU
    emTimerWaitConnectMcu,              //����MCU
    emTimerWaitSyncTime,                //ʱ��ͬ��
    emTimerWaitGetMcuStatus,            //��ȡMCU״̬
    emTimerWaitGetMcuEqpCfg,            //��ȡMCU��������
    emTimerWaitGetMcuBrdCfg,            //��ȡMCU��������
    emTimerWaitGetMcuGeneralCfg,        //��ȡMCU��������
    emTimerWaitAddrReg,                 //ע���ַ��
    emTimerWaitAddrGetEntryNum,         //��ȡ��ַ����Ŀ����
    emTimerWaitAddrGetEntry,            //��ȡ��ַ����Ŀ
    emTimerWaitAddrGetGroupNum,         //��ȡ��ַ������������
    emTimerWaitAddrGetGroup,            //��ȡ��ַ��������
	// lrf [6/22/2006]
	emTimerWaitGetUserGroupList,		//��ȡ�û����б�
    emTimerWaitGetUserList,             //��ȡ�û��б�
	emTimerWaitListAllConf,             //��ȡ���л����б�
    emTimerWaitGetPeriEqpStatus,        //��ȡ����״̬
	emTimerWaitGetDcsStatus,			//��ȡDCS״̬
    emTimerWaitGetLockInfo,             //��ȡ����������Ϣ
    emTimerWaitGetAllMtStatus,          //��ȡ�����ն�״̬
    emTimerWaitGetAllMtAlias,           //��ȡ�����ն˱���
    emTimerWaitGetAllMcuMediaSrc,       //��ȡ����MCUý��Դ
    emTimerWaitGetAllSMcuLockStatus,    //��ȡ�����¼�MCU�������
    emTimerWaitGetAllSMcuMixParam,      //��ȡ�����¼�MCU��������
    emTimerWaitGetVmpStyle,             //��ȡ����ϳɷ���
    //  MCU����
    emTimerWaitGetMcuMsStatus,          //��ȡMUC������״̬
    emTimerWaitGetMcuCpuStatus,         //��ȡMCU��CPUʹ����
    emTimerWaitModifyMcuEqpCfg,         //�޸�MCU��������
    emTimerWaitModifyMcuBrdCfg,         //�޸�MCU��������
    emTimerWaitChangeHDUSchemeInfo,     //xts20090120 �޸ĵ���ǽԤ������
    emTimerWaitModifyMcuGeneralCfg,     //�޸�MCU��������
    emTimerWaitGetMcuTime,              //��ȡMCUϵͳʱ��
    emTimerWaitModifyMcuTime,           //�޸�MCUϵͳʱ��
    emTimerWaitRebootBrd,               //���𵥰�
    //  �������
    emTimerWaitCreateConf,              //��������
    emTimerWaitCreateConfByTemplate,    //����ģ�崴������
    emTimerWaitReleaseConf,             //��������
    emTimerWaitChangeConfLockMode,      //�޸Ļ�������ģʽ
    emTimerWaitChangeConfPwd,           //�޸Ļ�������
    emTimerWaitSaveConf,                //�������
    emTimerWaitModifyConf,              //�޸Ļ���
    emTimerWaitDelayConf,               //������ʱ
    //  �������
    emTimerWaitSpecChairman,            //ָ����ϯ
    emTimerWaitCancelChairman,          //ȡ����ϯ
    emTimerWaitSpecSpeaker,             //ָ��������
    emTimerWaitCancelSpeaker,           //ȡ��������
    emTimerWaitAddMt,                   //����ն�
    emTimerWaitDelMt,                   //ɾ���ն�
    emTimerWaitStartMonitor,            //��ʼ���
    emTimerWaitStopMonitor,             //ֹͣ���
    //  �������
    emTimerWaitGetPollParam,            //��ȡ������ѯ����
    emTimerWaitSpecPollPos,                 //ָ����ǰ��ѯ���ն�
    emTimerWaitGetTwPollParam,          //��ȡ����ǽ��ѯ����
    emTimerWaitChangeVacHoldTime,       //�޸���������ʱ��
    //  �ն˲���
    emTimerWaitCallMt,                  //�����ն�
    emTimerWaitSetMtCallMode,           //�����ն˺��з�ʽ
    emTimerWaitDropMt,                  //�Ҷ��ն�
    emTimerWaitStartSee,                //�ն�ѡ��
    emTimerWaitStopSee,                 //ֹͣѡ��
    emTimerWaitStartVmpSee,             //vmpѡ��
    emTimerWaitStopVmpSee,              //ֹͣvmpѡ��
    emTimerWaitGetMtAlias,              //��ȡ�ն˱���
    emTimerWaitGetMtBitrate,            //��ȡ�ն�����
    emTimerWaitAudMute,                 //��������
    emTimerWaitGetMatrix,               //��ȡ�ն˾���
    emTimerWaitGetMatrixScheme,         //��ȡ���󷽰�
    emTimerWaitGetMatrixExPort,         //��ȡ���þ������Ӷ˿�
    emTimerWaitLockSMcu,                //�����¼�MCU
    emTimerWaitGetMtVersion,            //��ȡ�ն˰汾��Ϣ
    //  ¼��
    emTimerWaitStartRec,                //��ʼ¼��
    emTimerWaitPauseRec,                //��ͣ¼��
    emTimerWaitResumeRec,               //�ָ�¼��
    emTimerWaitStopRec,                 //ֹͣ¼��
    emTimerWaitStartPlay,               //��ʼ����
    emTimerWaitPausePlay,               //��ͣ����
    emTimerWaitResumePlay,              //�ָ�����
    emTimerWaitStopPlay,                //ֹͣ����
    emTimerWaitSeekPlay,                //������ȵ���
//    emTimerWaitGetAllRecFile,           //��ȡ¼���ļ�
    emTimerWaitDeleteRecFile,           //ɾ��¼���ļ�
    emTimerWaitChangeRecFileName,       //�޸�¼���ļ���
    emTimerWaitPublishRecFile,          //����¼���ļ�
    emTimerWaitCancelPub,               //ȡ��¼���ļ�����
    emTimerWaitModifyRecFile,           //�޸�¼���ļ���
    //  ����
    emTimerWaitStartMix,                //��ʼ����
    emTimerWaitStopMix,                 //ֹͣ����
    emTimerWaitStartVac,                //��ʼ��������
    emTimerWaitStopVac,                 //ֹͣ��������
    emTimerWaitMixDelay,                //������ʱ
    //  ����ϳ�
    emTimerWaitStartVmp,                //��ʼ����ϳ�
    emTimerWaitStopVmp,                 //ֹͣ����ϳ�
    emTimerWaitChangeVmpParam,          //�޸Ļ���ϳɲ���
    emTimerWaitStartVmpBrdst,           //��ʼ����ϳɹ㲥
    emTimerWaitStopVmpBrdst,            //ֹͣ����ϳɹ㲥
    //  ����ǽ
    emTimerWaitStartTW,                 //��ʼ����ǽ
    emTimerWaitStopTW,                  //ֹͣ����ǽ
    //  �໭�����ǽ
    emTimerWaitStartMultiTW,            //��ʼ�໭�����ǽ
    emTimerWaitChangeMultiTWParam,      //�޸Ķ໭�����ǽ����
    emTimerWaitStopMultiTW,             //ֹͣ�໭�����ǽ
    //  �û�
    emTimerWaitAddUser,                 //����û�
    emTimerWaitDelUser,                 //ɾ���û�
    emTimerWaitModifyUser,              //�޸��û�
    //  ��ַ��
    emTimerWaitAddrUnreg,               //ע����ַ��
    emTimerWaitAddrAddEntry,            //��ӵ�ַ����Ŀ
    emTimerWaitAddrDelEntry,            //ɾ����ַ����Ŀ
    emTimerWaitAddrModifyEntry,         //�޸ĵ�ַ����Ŀ
    emTimerWaitAddrAddGroup,            //���ӵ�ַ��������
    emTimerWaitAddrDelGroup,            //ɾ����ַ��������
    emTimerWaitAddrModifyGroup,         //�޸ĵ�ַ��������
    emTimerWaitAddrGroupAddEntry,       //���ַ�������������Ŀ
    emTimerWaitAddrGroupDelEntry,       //�ӵ�ַ��������ɾ����Ŀ
	//ext
	emTimerWaitDownLoadCfg,				//���������ļ�
    emTimerWaitUpLoadCfg,				//�ϴ������ļ�
	emTimerUpgradeComplete,				// ftp�ϴ����
	//�û������
	emTimerWaitAddUserGroup,			//�����û���
	emTimerWaitDelUserGroup,			//ɾ���û���
	emTimerWaitModifyUserGroup,			//�޸��û���
    //ָ�����᳡���ϼ��ش����ն�
    emTimerWaitSpecOutView,
    // ��OSP��ʽ�ϴ��ļ�
    emTimerWaitUploadFileReq,           // �ϴ��ļ�����
    emTimerWaitUploadFilePackageReq,    // �ϴ�������
    emTimerWaitUpdateTelnetLoginInfoReq,// ����Telnet����
    emTimerWaitStartRollCallReq,        // ��ʼ����
    emTimerWaitStopRollCallReq,         // ��������
    emTimerWaitChangeRollCallReq,       // �޸ĵ�����Ա
    //�������ǽ
    emTimerWaitGetGetHduSchemeInfo,     //��ȡ�������ǽ����
    emTimerWaitSetChannelVolumeInfo,    //�������ǽͨ����������
    emTimerWaitStartHduBatchPollReq,    //��ʼ�������ǽͨ��������ѯ
    emTimerWaitStopHduBatchPollReq,     //ֹͣ�������ǽͨ��������ѯ
    emTimerWaitPauseHduBatchPollReq,    //��ͣ�������ǽͨ��������ѯ
    emTimerWaitResumeHduBatchPollReq,   //�ָ��������ǽͨ��������ѯ
    //�������
    emTimerWaitVcsChangeModeReq,        // �޸ĵ���ģʽ
    emTimerWaitVcsSchedulingMtReq,      // �����ն�
    emTimerWaitVcsEnterConfReq,         // ������Ȼ���
    emTimerWaitVcsQuitConfReq,          // �뿪���Ȼ���
    emTimerWaitVcsSoundControlReq,      // ��������
    emTimerWaitVcsGetVCSNameReq,        // ��ȡVCS����
    emTimerWaitVcsChangeVCSNameReq,     // �޸�VCS����
    emTimerWaitVcsCallGroupReq,         // �������ģʽ
    emTimerWaitVcsDropCallGroupMtReq,   // �Ҷ����ģʽ
    emTimerWaitVcsStartChairPollReq,    // ����������ѯ
    emTimerWaitVcsStopChairPollReq,     // ֹͣ������ѯ
    emTimerWaitVcsAddMtReq,             // �����ʱ�ն�
    emTimerWaitVcsDeleteMtReq,          // ɾ���ն�
    emTimerWaitVcsUserSettingReq,       //�û�����
    //  ����
    emTimerWaitEnd
} EMTimerWaitState;

#endif  //  _MCSCONST_20050426_H_
