/*===========================================================================================
ģ������meetingtemplate
�ļ���   : tpdata.h                                                      
����ļ� :                                                                 
ʵ�ֹ��� : ����ģ��������弰Ĭ�ϳ�ʼ��
���ߣ�������
��Ȩ��
----------------------------------------------------------------------------------------------
�޸ļ�¼��
����            �汾            �޸���            �߶���         �޸ļ�¼
2011-7-25       v1.0            ������                           ����

==============================================================================================*/
#ifndef TPDATA_H
#define TPDATA_H


#ifdef   _VXWORKS_
	#include <inetlib.h>
	#include <semlib.h>
	#include <iolib.h>
	#include <dosfslib.h>
	#include <usrlib.h>
	#include "brddrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif


#include "tpstruct.h"
#include "tplog.h"


/*SECTIONֵ*/

//�м���ģ�����
const s8 validTpNum[] = "validTpNum";
const s8 validTpNumKey[] = "validTpNumKey";
const s8 validSeq_[] = "validSeq_";
const s8 template_[] = "template_";



//��������
const s8 tpMeetingName[] = "tpMeetingName";
//����E164
const s8 tpE164[] = "tpE164";
//��������
const s8 tpConfBitRate[] = "tpConfBitRate";

const s8 tpConfDualBitRate[] = "tpConfDualBitRate";

const s8 tpConfUpBandWid[] = "tpConfUpBandWid";

const s8 tpConfDownBandWid[] = "tpConfDownBandWid";


//��ʼʱ��
const s8 tpStartTime[] = "tpStartTime";

//����ģʽ
const s8 tpEncryptType[] = "tpEncryptType";
const s8 tpDefaultEncrypt[] = "tpDefaultEncrypt";
const s8 tpEncryptKey[] = "tpEncryptKey";
//����ϳ���Ϣ


//��������
const s8 tpEpAddrNum[] = "tpEpAddrNum";
//���˵�ID
const s8 tpEpAddrID_[] = "tpEpAddrID_";
//�Ƿ��Ǳ���+IP����
const s8 tpIsAliasIP_[] = "tpIsAliasIP_";
//���˵����
const s8 tpEpAddrAlias_[] = "tpEpAddrAlias_";
//���˵��������
const s8 tpEpAddrAliasType_[] = "tpEpAddrAliasType_";
//E164
const s8 tpEpAddrE164_[] = "tpEpAddrE164_";
//���˵�E164����
const s8 tpEpAddrE164Type_[] = "tpEpAddrE164Type_";
//���˵��������
const s8 toEpAddrCallType_[] = "tpEpAddrCallType_";
//IP
const s8 tpEpAddrIP_[] = "tpEpAddrIP_";
//���˵�IP����
const s8 tpEpAddrIPType_[] = "tpEpAddrIPType_";
//���ۻ᳡ID����
const s8 tpAudMixID_[] = "tpAudMixID_";
//���ۿ���
const s8 tpDiscussOn[] = "tpDiscussOn";
//����������������
const s8 tpDiscussVacOn[] = "tpDiscussVacOn";
//��ѯ���
const s8 tpTurnInterval[] = "tpTurnInterval";
//������ѯ������
const s8 tpTurnNum[] = "tpTurnNum";
//��ѯ�б�ID����
const s8 tpTurnID_[] = "tpTurnID_";
//��ѯ����
const s8 tpTurnOn[] = "tpTurnOn";
//��Ƶ����
const s8 tmAudioNum[] = "tpAudioNum";
//��Ƶ��ʽ
const s8 tpAudioFormat_[] = "tpAudioFormat_";
//��ƵƵ��
const s8 tpAudioFreq_[] = "tpAudioFreq_";
//����Ƶ��ʽ
const s8 tpAudioReservel_[] = "tpAudioReservel_";
//����Ƶ����
const s8 tpMainVidNum[] = "tpMainVidNum";
//����Ƶ����
const s8 tpMinorVidNum[] = "tpMinorVidNum";
//����Ƶ�ֱ���
const s8 tpVideoMainRes_[] = "tpMainVideoRes_";
//����Ƶ�ֱ���
const s8 tpVideoMinorRes_[] = "tpMinorVideoRes_";
//����Ƶ��ʽ���ʼ���
const s8 tpMainVideoLvl_[] = "tpMainVideoLvl_";
//����Ƶ��ʽ���ʼ���
const s8 tpMinorVideoLvl_[] = "tpMinorVideoLvl_";
//����Ƶ֡��
const s8 tpMainVideoFrame_[] = "tpMainVideoFrame_";
//����Ƶ֡��
const s8 tpMinorVideoFrame_[] = "tpMinorVideoFrame_";

//�ϳ�Ԥ������
const s8 tpVmpPlanStyle[] = "tpVmpPlanStyle";
//�ϳ�Ԥ��Ep����
const s8 tpVmpPlanEpNum[] = "tpVmpPlanEpNum";
//�����˸��棬˫������
const s8 tpVmpPlanSpeakIndex[] = "tpVmpPlanSpeakIndex";
const s8 tpVmpPlanDualIndex[] = "tpVmpPlanDualIndex";
//�ϳ�Ԥ��Ep�б�
const s8 tpVmpPlanEpAlias_[] = "tpVmpPlanEpAlias_";
const s8 tpVmpPlanScrIndex_[] =  "tpVmpPlanScrIndex_";
//�᳡��������
const s8 tpEpCallProtocol_[] =  "tpEpCallProtocol_";

//������������
typedef struct tagAllTpConfigData
{

	TConfTemplateLocal m_tTpConfTemplate;    //����ģ��

}TALLTpConfigData;


//������ģ�����ݺͶ�Ӧ���������Ľṹ��
typedef struct tagIndexALLTpConfigData
{
	TALLTpConfigData m_tALLTpConfigData;   //��������
	u16 m_wIndex;                         //����ֵ
}TIndexALLTpConfigData;


typedef struct tagTControlData
{
	u16 m_wValidNum;                           //��Чֵ
	BOOL m_abValidSeq[TP_CONFTEMPLATE_MAXNUM];  //�ļ���Ч���
}TControlData;


#endif
