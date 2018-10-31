#ifndef _h_tptime_h__
#define _h_tptime_h__


#include "osp.h"
#include "kdvtype.h"

typedef s32 (*KdvTimerHandler)(u32 dwTimerId, void* param);


typedef enum
{
    TIME_FREE  = 0,
	TIME_ALLOC,
	TIME_RUNNING,
} TimerState;


typedef struct tagTpTimer
{
    void*           m_pParam;					//�ص������Ĳ���
    u32             m_dwInterval;               //��ʱ���ļ��������
	KdvTimerHandler m_pCallBack;				//�ص�����
    u32             m_dwAbsTime;                //��ʱ���ľ��Դ���ʱ��
    TimerState      m_eState;
	
    struct tagTpTimer* m_ptNext;				//�û������ָ��
	
	//05.9.5
	tagTpTimer()
	{
		clear();
	};
	~tagTpTimer()
	{
		clear();
	}
	void clear()
	{
		m_pCallBack = NULL;
		m_pParam = NULL;
		m_ptNext = NULL;
		m_eState = TIME_FREE;
		m_dwInterval = 0;
		m_dwAbsTime = 0;
	}
} TTpTimer;


class CTpTimerMgr
{
public:
    CTpTimerMgr();
    ~CTpTimerMgr();
    
public:
    BOOL32  Create(s32 nTotalNum);    
    s32  Close();    
	
    TTpTimer* AddTimer(u32 dwInterval, KdvTimerHandler pCallBack, void* context);
	
    BOOL32 DeleteTimer(TTpTimer* ptTimer);
	
    BOOL32 UpdateTimer(TTpTimer* ptTimer);
	
    s32 Check();	
	
    s32 GetStatis(u32* pdwNowTime, s32* pnTotal, s32* pnUsed);
	
    BOOL32 DeleteAllTimer();
	//private:
public:
    TTpTimer* m_ptUsedList; //ʹ���б�
    
    TTpTimer* m_ptFreeListFirst;    //����ͷ�б�
	
    TTpTimer* m_ptFreeListLast;    //����βָ��
	
	
    TTpTimer* m_patTimer;  //���ٵĶ�ʱ������
    
    u32 m_dwNowTime;        //��ǰʱ��
	s32 m_nTimerCount;      //��ʱ���ܸ���
    s32 m_nUsedCount;
	
private:
    BOOL32 DeleteFirst();
    TTpTimer* NewTimer();
    BOOL32 AddTimer(TTpTimer* ptTimer);
	
	
};


#endif // _h_tptime_h__
