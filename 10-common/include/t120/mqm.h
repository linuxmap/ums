/******************************************************************************
ģ����      ��Mqm
�ļ���      ��Mqm.h
����ļ�    ��Mqm.cpp
�ļ�ʵ�ֹ��ܣ�ʵ��MQM
����        ����ɸ��
�汾        ��4.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �߶���      �޸�����
23/05/05    0.1         ��ɸ��      ��ɸ��      ����
******************************************************************************/
#ifndef _MQM_H_
#define _MQM_H_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <queue>
#include <map>
#include <list>
#include <kdvtype.h>
#include <ptlib.h>

/*====================================================================
// ��ӡ��־ �궨��
=====================================================================*/
#ifdef ENABLE_MQM_LOG
    static PMutex G_MQM_LOG;
    #define MQM_LOG(format, para1, para2, para3) \
        { \
            PWaitAndSignal lock(G_MQM_LOG); \
            printf(format, para1, para2, para3); \
            printf("\n"); \
        }
/*
    #define MQM_LOG(format, para1, para2, para3) \
        { \
            CHAR anBuf[1024]; \
	        sprintf(anBuf, ".\\T120_LOG\\%ld_%ld.log", GetCurrentProcessId(), GetCurrentThreadId()); \
            HANDLE handleFile = CreateFile(anBuf, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); \
            if (handleFile != NULL) \
            { \
                SetFilePointer(handleFile, NULL, NULL, FILE_END); \
                DWORD dwRcv; \
                SYSTEMTIME tSystime; \
                GetLocalTime(&tSystime); \
                CHAR anFormat[256]; \
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] MQM    : %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat, para1, para2, para3); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }
*/
#else
    #define MQM_LOG(format, para1, para2, para3)
#endif


#ifndef NEW_WITH_CHECK
    #ifdef ENABLE_NEW_CHECK
        static PMutex G_NEW_CHECK_LOG;
        #define CHECK_NEW(pNewPoint) \
            if (pNewPoint == NULL) \
            { \
                PWaitAndSignal lock(G_NEW_CHECK_LOG); \
                printf("**** ���ش���:�����ڴ�ʧ��**** \n"); \
            }
        #define CHECK_DELETE(pDeletePoint) \
            if (pDeletePoint == NULL) \
            { \
                PWaitAndSignal lock(G_NEW_CHECK_LOG); \
                printf("**** ���ش���:ɾ���ڴ�ʧ��**** \n"); \
            }
    #else
        #define CHECK_NEW(pNewPoint)
        #define CHECK_DELETE(pDeletePoint)
    #endif

    #define NEW_WITH_CHECK(pcNewPoint, NewTypeAndParas) \
        pcNewPoint = new NewTypeAndParas; \
        CHECK_NEW(pcNewPoint);
    #define DECLEAR_AND_NEW(CType, pcNewPoint, NewTypeAndParas) \
        CType* pcNewPoint = new NewTypeAndParas; \
        CHECK_NEW(pcNewPoint);
    #define DELETE_WITH_CHECK(pcDeletePoint) \
        CHECK_DELETE(pcDeletePoint); \
        delete pcDeletePoint;
    #define DELETE_ARRAY_WITH_CHECK(paDeleteArray) \
        CHECK_DELETE(paDeleteArray); \
        delete[] paDeleteArray;
#endif



    
/*====================================================================
// �궨��
=====================================================================*/
#define MAX_QUEUE_SIZE	0xffffff // ������󳤶ȶ���
#define INVALID_QUEUEID	0		 //��Ч����ID

class CMsg;
class CQueue;
class CMqmThread;
class CMqmSyncReceiver;

/*====================================================================
// ���ͱ�������
=====================================================================*/
typedef u32 QueueID; //���б��
typedef u32 MsgID; //��Ϣ���

typedef std::map<QueueID,CQueue*> TQueueMap;
typedef std::pair<QueueID,CQueue*> TQueuePair;
typedef std::map<MsgID, CMsg*> TMsgMap;
typedef std::pair<MsgID,CMsg*> TMsgPair;

typedef struct tagMessageContext
{
    tagMessageContext();
    tagMessageContext(QueueID nQueueID, u8 nContextType=0, void* pcContextRes=NULL);

    // ���ڲ���
    bool operator == (const tagMessageContext tRightValue);
    // �����ڲ���
    bool operator != (const tagMessageContext tRightValue);

    QueueID m_nQueueID; // ��Ϣ�ķ��Ͷ���
    u8 m_nContextType; // ��Ϣ�Ļ������ͣ����������ͻ��߽��������ͣ�
    void* m_pcContextRes; // ��Ϣ�ķ����߻��߽�����
}TMessageContext;


/*====================================================================
���� �� CMsg
���� �� �����е�ÿ�����ݶ��壬ʵ�ʵ���Ϣ����Ӵ�������
====================================================================*/
class CMsg
{
private:
    // �����ڲ����к�
    MsgID GenerateMsgId();

public:
	// ����
    CMsg(u8 nCatalog, u8 nType);
	// ����
    virtual ~CMsg(){};
    // ���ɻظ���Ϣ
    void BuildAck(const CMsg* const pcMsg);
    // ����ת����Ϣ
    void BuildPass();
    // �õ�MsgID
    MsgID GetMsgID();
    u8 m_nMsgCatalog; // ��Ϣ���(��)
    u8 m_nMsgType; // ��Ϣ���(С)
    TMessageContext m_tMsgFromContext;    //��Ϣ�ķ�����
    TMessageContext m_tMsgToContext;  //��Ϣ�Ľ�����
    
private:    
    MsgID m_nID; // ��Ϣ���(Ψһ��MQM�ڲ�ʹ��)

private:
};

/*====================================================================
���� �� CQueue
���� �� һ������
====================================================================*/
class CQueue
{
public:
	//���������
	CQueue(u32 uMaxVal);
	~CQueue();

    QueueID GetQueueID();
	bool InsetrtMsg(CMsg* cMsg);
	CMsg* GetMsg();
    // ���ж���
    typedef std::queue<CMsg*> TMsgQueue;
    TMsgQueue m_queMsg;

    PSemaphore m_semQueueSize; // Ŀǰ�����е���Ϣ��Ŀ
    PMutex m_mutexData; // ���л�������֤�����л������
    CMqmSyncReceiver* m_pcSyncReceiver; // �ö��е�ͬ����Ϣ������

private:
	QueueID m_nID; // ���б��(Ψһ��MQM�ڲ�ʹ��)
};

/*====================================================================
���� �� CMqm
���� �� ʵ��MQM�Ĺ���
====================================================================*/
class CMqm
{
public:
	CMqm();//���캯��
	~CMqm();//��������
    
	QueueID CreateQueue(u32 uMaxVal); // ��������
    bool SendMsg(const CMsg& cSendMsg, CMsg& cRecvMsg); // ������Ϣ
    bool SendMsg(CMsg& cSendMsg); // ������Ϣ�����ͺͽ�������ͬ�Ļ�������
    bool PostMsg(CMsg* cPostMsg); // ������Ϣ

//private:
    // ���ж��ж��壺<��Ϣ����ָ��>
    TQueueMap m_mapQueue;
	
    // ������Ϣ�ڴ棺<��Ϣ��,��Ϣ��ָ��>
    TMsgMap m_mapMsg;

	PMutex m_mutexMapQueue; //m_mapMsg��ͬ����
	PMutex m_mutexMapMsg; //m_mapQueue��ͬ����
};

// ��Ϣ���(��)����
typedef enum
{
    e_General,
    e_Tc,
    e_Mcs,
    e_Gcc,
    e_Ape,
    e_Adapter
} enumMsgCatalog;

// ͨ����Ϣ����(С)����
typedef enum
{
    e_Terminate,
    e_DebugPrint
} enumGeneralMsgType;


/*====================================================================
���� �� CGeneralTerminatePrimitive
���� �� �����߳���������
====================================================================*/
class CGeneralTerminatePrimitive : public CMsg
{
public:
    CGeneralTerminatePrimitive():CMsg(e_General, e_Terminate)
    {
    }
};



/*====================================================================
���� �� CGeneralDebugPrintPrimitive
���� �� ��ӡ������Ϣ
====================================================================*/
class CGeneralDebugPrintPrimitive : public CMsg
{
public:
    CGeneralDebugPrintPrimitive():CMsg(e_General, e_DebugPrint)
    {
    }
};

#endif //_MQM_H_
