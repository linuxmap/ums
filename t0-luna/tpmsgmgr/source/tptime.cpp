#include "tptime.h"
#include "tpsys.h"
#include "tplog.h"

//单线程timer，由外部调用check进行时间更新，每次1s，内部进行时间计数作为运行时间

/*
    每次check到一个定时器到期后，从运行队列中摘除，然后由应用决定是否重新加入定时器队列。
*/

CTpTimerMgr::CTpTimerMgr()
{
    m_ptUsedList        = NULL;
    m_ptFreeListFirst   = NULL; 
    m_ptFreeListLast    = NULL;
    m_patTimer          = NULL;
	m_nTimerCount       = 0;
    m_dwNowTime         = 0;
    m_nUsedCount        = 0;
}


CTpTimerMgr::~CTpTimerMgr()
{
    Close();
}


BOOL32 CTpTimerMgr::Create(s32 nTotalNum)
{
    Close();
  
	m_nTimerCount = nTotalNum;
    if (nTotalNum <= 0 )
    {
        return FALSE;
    }
    m_patTimer = (TTpTimer*)malloc(sizeof(TTpTimer) * nTotalNum);
    if (NULL == m_patTimer)
    {
        return FALSE;
    }

    //建立空链表
    m_ptFreeListFirst = m_patTimer;
    m_ptFreeListLast  = m_patTimer;

    s32 i;
    for(i = 1; i < nTotalNum; i++)
    {
        m_ptFreeListLast->m_ptNext = m_patTimer + i;
        m_ptFreeListLast = m_ptFreeListLast->m_ptNext;
    }

    m_ptFreeListLast->m_ptNext = NULL;

    return TRUE;
}


s32 CTpTimerMgr::Close()
{
    if (NULL != m_patTimer)
    {
        free(m_patTimer);
        m_patTimer = NULL;
    }
    m_ptFreeListFirst = NULL;
    m_ptFreeListLast  = NULL;
    m_ptUsedList      = NULL;
    m_dwNowTime       = 0;
    
    return 0;
}


TTpTimer* CTpTimerMgr::NewTimer()
{
    if (NULL == m_ptFreeListFirst)
    {
        return NULL;
    }

    TTpTimer* ptTimer;
    ptTimer = m_ptFreeListFirst;
    m_ptFreeListFirst = m_ptFreeListFirst->m_ptNext;

    if (NULL == m_ptFreeListFirst) 
    {
        m_ptFreeListLast = NULL;
    }
    
    ptTimer->m_dwAbsTime = 0;
    ptTimer->m_pCallBack = NULL;
    ptTimer->m_pParam = NULL;
    ptTimer->m_dwInterval = 0;
    ptTimer->m_eState = TIME_ALLOC;
    ptTimer->m_ptNext = NULL;

    return ptTimer;
}

TTpTimer* CTpTimerMgr::AddTimer(u32 dwInterval, KdvTimerHandler pCallBack, void* context)
{
    if (NULL == pCallBack )
    {
        msgprint("AddTimer failed.\n");
        return NULL;
    }

	if (m_nUsedCount > m_nTimerCount )
	{
		msgprint("[asftimer]exist timer[%d] > the max count[%d]\n", m_nUsedCount, m_nTimerCount);
		return NULL;
	}
	
    TTpTimer* ptNewTimer;
    ptNewTimer = NewTimer();
    if (NULL == ptNewTimer)
    {
        OspPrintf(1, 0, "New Timer Failed.\n");

        return NULL;
    }

    ptNewTimer->m_dwInterval = dwInterval;
    ptNewTimer->m_pCallBack = pCallBack;
    ptNewTimer->m_pParam = context;

    AddTimer(ptNewTimer);

    m_nUsedCount++;

    return ptNewTimer;
}

//更新定时器（可以是空闲的，也可以是正在运行的），重新加入运行队列
BOOL32 CTpTimerMgr::UpdateTimer(TTpTimer* ptTimer)
{
    if (NULL == ptTimer)
    {
        return FALSE;
    }
    
    if (TIME_RUNNING == ptTimer->m_eState)
    {
        //从使用队列中删除
        TTpTimer* ptPre;
        TTpTimer* ptLoop;
        ptPre = NULL;
        ptLoop = m_ptUsedList;
        while (NULL != ptLoop)
        {
            if (ptLoop == ptTimer)
            {
                break;
            }
            ptPre = ptLoop;
            ptLoop = ptLoop->m_ptNext;
        }
        if (NULL == ptPre)
        {
            if (NULL != ptLoop)
            {
                m_ptUsedList = ptLoop->m_ptNext;
            }
        }
        else if (NULL != ptLoop)
        {
            ptPre->m_ptNext = ptLoop->m_ptNext;
        }
        
        if (NULL == ptLoop)
        {
            msgprint("UpdateTimer Failed\n");
            return FALSE;
        }
        ptTimer->m_eState = TIME_ALLOC;
    }


    //重新加入队列
    s32 nRet;
    nRet = AddTimer(ptTimer);

    return TRUE;
}

BOOL32 CTpTimerMgr::DeleteTimer(TTpTimer* ptTimer)
{
    if (NULL == ptTimer)
    {
        return FALSE;
    }

    if (TIME_RUNNING == ptTimer->m_eState)
    {
        //从使用队列中删除
        TTpTimer* ptPre;
        TTpTimer* ptLoop;
        ptPre = NULL;
        ptLoop = m_ptUsedList;
        while (NULL != ptLoop)
        {
            if (ptLoop == ptTimer)
            {
                break;
            }
            ptPre = ptLoop;
            ptLoop = ptLoop->m_ptNext;
        }
        if (NULL == ptPre)
        {
            if (NULL != ptLoop)
            {
                m_ptUsedList = ptLoop->m_ptNext;
            }
        }
        else if (NULL != ptLoop)
        {
            ptPre->m_ptNext = ptLoop->m_ptNext;
        }
        
        if (NULL == ptLoop)
        {
            msgprint("DeleteTimer Timer:0x%x Failed. not found\n", ptTimer);
            return FALSE;
        }
        
        ptTimer->m_ptNext = NULL;
        ptTimer->m_eState = TIME_ALLOC;
    }

    if (TIME_ALLOC != ptTimer->m_eState)
    {
        msgprint("Timer:0x%x already deleted.", ptTimer);
        return FALSE;
    }

    //加入空闲队列
    if (NULL != m_ptFreeListLast)
    {
        m_ptFreeListLast->m_ptNext = ptTimer;
    }
    m_ptFreeListLast = ptTimer;
    
    if (NULL == m_ptFreeListFirst)
    {
        m_ptFreeListFirst = ptTimer;
    }

    ptTimer->m_eState = TIME_FREE;
    
    m_nUsedCount--;
	if( m_nUsedCount < 0 )
	{
		
        msgprint("UsedCount < 0 \n");
        m_nUsedCount = 0;
	}
    
    return TRUE;
}

s32 CTpTimerMgr::Check()
{
    u32 dwNextTime;

    m_dwNowTime++;

    if (NULL == m_ptUsedList)
    {
        return 0;
    }

    TTpTimer* ptTimer;
    ptTimer = m_ptUsedList;
    dwNextTime = ptTimer->m_dwAbsTime;
    while(m_dwNowTime >= dwNextTime)
    {
        DeleteFirst();
        
        if (ptTimer->m_pCallBack != NULL)
        {
            ptTimer->m_pCallBack((u32)ptTimer, ptTimer->m_pParam);
        }

        // get next timer
        ptTimer = m_ptUsedList;
        if (NULL == ptTimer)
        {
            break;
        }

        dwNextTime = ptTimer->m_dwAbsTime;
    }

    return 0;
}


s32 CTpTimerMgr::DeleteFirst()
{
    TTpTimer* ptTimer;
    ptTimer = m_ptUsedList;

    if (NULL == m_ptUsedList)
    {
        return TP_RET_ERROR;
    }
	
    //从使用队列中移除
    m_ptUsedList = m_ptUsedList->m_ptNext;

    ptTimer->m_ptNext = NULL;
    ptTimer->m_eState = TIME_ALLOC;

    return 0;
}

BOOL32 CTpTimerMgr::AddTimer(TTpTimer* ptTimer)
{
    //插入队列
    TTpTimer* ptPre;
    TTpTimer* ptLoop;
    ptLoop = m_ptUsedList;
    ptPre = NULL;

    if (TIME_FREE == ptTimer->m_eState)
    {
        msgprint("Timer is Deleted.\n");
        return FALSE;
    }

    if (TIME_RUNNING == ptTimer->m_eState)
    {
        msgprint("Timer is In Used.\n");
        return FALSE;
    }

    ptTimer->m_dwAbsTime = m_dwNowTime + ptTimer->m_dwInterval;

    while (NULL != ptLoop)
    {
        if (ptLoop->m_dwAbsTime > ptTimer->m_dwAbsTime)
        {
            break;
        }
        ptPre = ptLoop;
        ptLoop = ptLoop->m_ptNext;
    }

    if (NULL == ptPre)  //插入链首
    {
        m_ptUsedList = ptTimer;
        ptTimer->m_ptNext = ptLoop;
    }
    else //其他
    {
        ptPre->m_ptNext = ptTimer;
        ptTimer->m_ptNext = ptLoop;
    }

    ptTimer->m_eState = TIME_RUNNING;

    return TRUE;
}

s32 CTpTimerMgr::GetStatis(u32* pdwNowTime, s32* pnTotal, s32* pnUsed)
{
    if (NULL != pdwNowTime) *pdwNowTime = m_dwNowTime;
    if (NULL != pnTotal)    *pnTotal = m_nTimerCount;
    if (NULL != pnUsed)     *pnUsed  = m_nUsedCount;
    return 0;
}

BOOL32 CTpTimerMgr::DeleteAllTimer()
{

	TTpTimer* ptTimer = m_ptUsedList;
	TTpTimer* ptTimerBak = NULL;
	u16 wCount = 0;
	while(NULL != m_ptUsedList)
	{
		ptTimerBak = m_ptUsedList->m_ptNext;
		DeleteTimer(ptTimer);
		ptTimer->clear();
		ptTimer = ptTimerBak;
		wCount ++ ;
		msgprint("Timer is delete %d.\n",wCount);
	}
	msgprint("the totle time is %d,used time is %d \n", m_nTimerCount,m_nUsedCount);
return TRUE;
}