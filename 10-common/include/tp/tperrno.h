#ifndef _h_tperrno_h__
#define _h_tperrno_h__

#define TP_UMS_ChairIsUMS		10000				//��ϯ��UMS
#define TP_UMS_ChairIsMT		10001				//��ϯ��MT
#define TP_UMS_ChairIsMCU		10002				//��ϯ��MCU
#define TP_UMS_SuperDropped		10003				//�ϼ�����
#define TP_UMS_ChairIsFailed    10009               //��ϯδ���� 

#define TP_UMS_AdapterQuit		10004				//��������
#define TP_UMS_AllEpHungUp		10005				//���л᳡�Ҷ�
#define TP_UMS_BasDisConnect	10006				//��������
#define TP_UMS_BasStartFail		10007				//���俪��ʧ��
#define TP_UMS_MediaTransQuit	10008				//ת�������


#define TP_UMS_ChairIsB3CNS		10010				//��ϯ���ϰ汾CNS
#define TP_UMS_SpeakerVmpError	10011				//����ʱVMP���� , �ݽ�ʱVMP ����

#define TP_UMS_QuitAudMix       15000				//�������������رգ���Դ����

//TvWall  to umc
#define Tp_UMS_TvWall_MTVmpFail 10050               // ��Դ���㣬�������ǽͨ��ʧ��
#define TP_UMS_TvWall_InvalidMT 10051               // ��Ч�նˣ��������ǽͨ��ʧ��
#define TP_UMS_TvWall_BandError 10052               // �����㣬�������ǽͨ��ʧ��
#define TP_UMS_TvWall_VmpError  10053               // �ϳ������ߣ��������ǽͨ��ʧ��
#define TP_UMS_TvWall_VmpCapFail 10054              //Ϊ������ʱ���ն˲����ֱ��ʽ���ͨ�����������������������ʾ��Ϣ�����ϳ��������㡱
#define TP_UMS_TvWall_AssignVmpFail 10055           // ��ӻ���ϳ����������ǽ�໭��ͨ��, ��ʾ"���󲥷ŵ���ǽʧ�ܣ����Ͳ�ƥ��"
#define TP_UMS_TvWall_VmpStop   10056               // �ϳ�ֹͣ���������ǽͨ��ʧ��


//#define TP_UMS_Discard_Start    10100				
#define TP_UMS_Discard_AddEp    10101				//������ͳһ��������ʱ���᳡xx��������ʧ�� 
#define TP_UMS_Discard_EpOnLine	10102				//�������᳡xx����ʱ����������ʧ�ܣ�  
                                                    //ע������������Ϣm_dwReserve1��᳡ID��m_dwReserve2��ö��ֵEmDiscussOprRes����ԭ��

#define TP_Discuss_StopByUms_NoVaildEp   10103   // ����������Ч��Ա�����۽���
#define TP_Discuss_StopByUms_MixError    10104   // ��������ߣ����۽���
#define TP_Discuss_StopByUms_BasError    10105   // �������ߣ����۽���
#define TP_Discuss_StopByUms_VmpError  10106   // �ϳɰ���ߣ����۽���
#define TP_Discuss_AssignVmpFail              10107   //��������ʧ��,���ۺϳ���Դ����
#define TP_Discuss_AssignMixFail                10108   //��������ʧ��,���ۻ�����Դ����
#define TP_Discuss_AssignVBasFail             10109  //��������ʧ��,����������Դ����
#define TP_Discuss_OtherFail                       10110   //��������ʧ�ܣ�����ԭ��

// 
#define TP_UMS_VMP_Audience_ChanNoVid    10150      //�ϳ���vip���㣬��û��С�����Ͳ�֧�ֽ��ֱ��ʣ���ͨ�᳡xx����ϳ���xx��ͼ�� ע��m_dwReserve1Ϊ�᳡ID��m_dwReserve2Ϊ�ϳ���ID          
#define TP_UMS_VMP_Speaker_ChanNoVid     10151      //�ϳ���vip���㣬���Ի᳡xx����ϳ���xx��ͼ�� ע��m_dwReserve1Ϊ�᳡ID��m_dwReserve2Ϊ�ϳ���ID          
#define TP_UMS_VMP_Dual_ChanNoVid        10152      //�ϳ���vip���㣬�᳡xx��˫������ϳ���xx��ͼ�� ע��m_dwReserve1Ϊ�᳡ID��m_dwReserve2Ϊ�ϳ���ID          
#define TP_UMS_VMP_GetVidFail            10153      //��������ʧ�ܣ��᳡xx����ϳ�����ͼ�� ע��m_dwReserve1Ϊ�᳡ID��m_dwReserve2Ϊ�ϳ���ID

#define TP_UMS_Poll_BasDisCnnt  10200               //������ߣ���ѯֹͣ
#define TP_UMS_Poll_VmpDisCnnt  10201               //�ϳɵ��ߣ���ѯֹͣ
#define TP_UMS_Poll_EpNextBas	10202               //��ѯ�����᳡xx��������Դ����   ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_Poll_EpNextBW	10203               //��ѯ�����᳡xx��������Դ����   ע��m_dwReserve1 Ϊ�᳡ID

#define TP_UMS_View_BasDisCnnt  10250               //CNC�����䲻�㣬ѡ��ֹͣ  UMC�����䲻�㣬�᳡XXѡ��ֹͣ  ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_View_VmpDisCnnt  10251               //CNC���ϳɵ��ߣ�ѡ��ֹͣ  UMC���ϳɵ��ߣ��᳡XXѡ��ֹͣ  ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_View_BWFull      10252               //CNC�������㣬ѡ��ֹͣ  UMC�������㣬�᳡XXѡ��ֹͣ  ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_View_NoVid       10253               //CNC������ƵԴ��ѡ��ֹͣ  UMC������ƵԴ���᳡XXѡ��ֹͣ  ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_View_NoVmp       10254               //CNC���޷��տ��ϳ�ͼ�񣺻���ϳ���Դ����  UMC���᳡XX�޷��տ��ϳ�ͼ�񣺻���ϳ���Դ����  ע��m_dwReserve1 Ϊ�᳡ID
#define TP_UMS_View_VmpStop     10255               //CNC���ϳ���ֹ��ѡ��ֹͣ  UMC���ϳ���ֹ���᳡XXѡ��ֹͣ  ע��m_dwReserve1 Ϊ�᳡ID

#define TP_UMS_Dual_BasDisCnnt  10300               //������ߣ�˫��ֹͣ
#define TP_UMS_Dual_MixDisCnnt  10301               //���������ߣ�˫��ֹͣ
#define TP_UMS_Dual_BasFull     10302               //����˫��ʧ�ܣ�������Դ����



#define TP_ROLLCALLER_OFFLINE              10350              //�����ߵ��ߣ���������
#define Tp_ROLLCALL_MIX_ERROR              10351              //��������������
#define Tp_ROLLCALL_CREATE_CHAN_FAIL       10352              //�ϵ�������PUT��Ƶ����
#define Tp_ROLLCALL_ALLTARGET_OFFLINE      10353              //���еı������߶�����
#define Tp_ROLLCALL_START_NO_TARGET        10354              //��������û��ѡ�񱻵�����



#define TP_CONFAUDMIX_MIX_ERROR        10370              //�������������������
#define TP_CONFAUDMIX_STOP_NO_EP       10371              //������������еĻ᳡���ߣ����ƻ���ģʽ��
#define TP_CONFAUDMIX_MIXCHAN_FULL     10372              //�������������ͨ����
#define TP_CONFAUDMIX_DELETE_SPEAKER   10373              //�������������ʱɾ��������

#define TP_UMS_FECC_NO_323MT			10380				// �᳡Զң  ��323�ն�
#define TP_UMS_FECC_CHANNEL_NOT_OPEN	10381               // �᳡Զң  Զңͨ��δ��


#define TP_UMS_QT_MediaKeyFail        10500               //���������ܳ�Э��ʧ��
#define TP_UMS_InitMeetingFail				10501                //��ʼ������ʧ��
#define TP_UMS_AssignVmpFail            10502                //���뻭��ϳ���Դʧ��


#endif // _h_tperrno_h__
