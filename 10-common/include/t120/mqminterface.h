/******************************************************************************
ģ����      ��MqmInterface
�ļ���      ��MqmInterface.h
����ļ�    ��MqmInterface.cpp, Mqm.h
�ļ�ʵ�ֹ��ܣ�ʵ��MQM
����        ����ɸ��
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
28/05/05    0.1         ��ɸ��      ��ɸ��      ����
******************************************************************************/
#ifndef _MQMINTERFACE_H_
#define _MQMINTERFACE_H_

#include "mqm.h"
//#include "stdafx.h"

class CMqmInterface
{
public:
    // ���������
    CMqmInterface();
    ~CMqmInterface();

    //�ӿ�
    bool InitInstance(); //��ʼ��
    void ExitInstance(); //�˳�
    QueueID CreateQueue(u32 uMaxVal = MAX_QUEUE_SIZE); // ��������
    bool SetSyncReceiver(CMqmSyncReceiver* pcMqmSyncReceiver, QueueID nQueueID);
    bool SendMsg(const CMsg& cSendMsg, CMsg& cRecvMsg); // ������Ϣ
    bool SendMsg(CMsg& cSendMsg); // ������Ϣ�����ͺͽ�������ͬ�Ļ�������
    bool PostMsg(CMsg* pcPostMsg); // ������Ϣ
    bool RecvMsg(CMqmThread* pcMqmThread); // ������Ϣ

private:
    CMqm* m_pcMqm;  //��Ϣ���й�����MQM��ָ��
};

/*====================================================================
���� �� CMqmThread
���� �� MQM���е�ѭ����ȡ��
====================================================================*/
class CMqmThread : public PThread
{
    PCLASSINFO(CMqmThread, PThread);
public:
    CMqmThread();

    bool BindQueue(CMqmInterface* pcMqmInterface, QueueID tQueueID); // ���̰߳󶨵�����
    bool SendMsg(CMsg& cSendMsg, CMsg& cRecvMsg); // ������Ϣ
    bool SendMsg(CMsg& cSendMsg); // ������Ϣ�����ͺͽ�������ͬ�Ļ�������
    bool PostMsg(CMsg* cPostMsg);// ������Ϣ
	QueueID GetQueueID();
    void ExitThread();
    // ���麯������Ϣ����
    virtual void OnRecvMsg(CMsg& cPostMsg) = 0;

private:
    void Main();    //�߳�������

private:
    CMqmInterface* m_pcMqmInterface;    //Mqm�ӿ�ʵ��
    QueueID m_nQueueID; //�󶨵Ķ���ID
    bool m_bExit;
	
};

/*====================================================================
���� �� CMqmSyncReceiver
���� �� �����е�ͬ����Ϣ������
====================================================================*/
class CMqmSyncReceiver
{
public:
    CMqmSyncReceiver(); //���캯��
    bool BindQueueSync(CMqmInterface* pcMqmInterface, QueueID nQueueID); // �󶨶���
    virtual bool OnRecvSyncMsg(const CMsg& cSendMsg, CMsg& cRecvMsg) = 0; // ͬ����Ϣ������
};

#endif //_MQMINTERFACE_H_
