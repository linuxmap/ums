#ifndef _KDVADS_H_
#define _KDVADS_H_

/*
    ADS (Abstract Data Service) �������ݷ���
    �ṩ���ݽṹ���������
*/

#include "Kdvtype.h"
#include "osp.h"

#ifndef STK_API
#define STK_API         OSP_API
#endif


#ifndef KDVERROR
#define KDVERROR        -1
#endif

#ifndef MEMALLOC
#define MEMALLOC(nSize) malloc(nSize)
#define MEMFREE(p)      free(p)
#endif

#define ADS_LOG         1
#define ADSDEBUG

//�����С
#define ALIGNSIZE       sizeof(void*)

#define ALIGN(n)        (((n)+ALIGNSIZE-1)/ALIGNSIZE * ALIGNSIZE)


typedef enum
{
    LOGINFO     =   (u32)0, 
    LOGDEBUG    =   (u32)1,
    LOGWARN     =   (u32)2,
    LOGERROR    =   (u32)3,
    LOGEXCEPT   =   (u32)4,   
    LOGALLWAYS  =   (u32)5,
    LAST_LEVEL
} ELogLevel;


void LogPrintf(s32 eModule, ELogLevel eLevel, const s8* pszformat, ...);


/*-----------------------------   CAdsArray    ----------------------------------
    CAdsArray���������ʵ�ֶԾ�̬����Ĺ���Ϊ�û��ṩ�̶���С�ṹ����������ͷţ�
����ȡ����̬�ڴ���䡣�ڴ˻����ϣ����Խ�һ��ʵ����������POOL�����ȶ����Խ�һ����
ǿ�����ݿ�Ĺ���
    CAdsArray��Ҫ�ṩ���ӡ�ɾ������ȡ�Ȳ�����
---------------------------------------------------------------------------------*/

//����ڵ��û����ݵ�Ԫ
typedef void* PArrayElement;

/*
    Ԫ�رȽϺ���ԭ��
    ���ƥ�䣬�򷵻�TRUE, ���򷵻�FALSE
    �ú��������ڶ����С�
*/
typedef BOOL32 (*IsElemMatchingT)(void* pElement, void *pParam);

/*
    Ԫ�ش�����ԭ��
    �ú�����ѭ�������У�ÿ�ε��ý���������pParam�óɷ���ֵ����������һ�ε���
    �ú��������ڶ����С�
*/
typedef void* (*ProcessElemT)(void* pElement, void *pParam);


/*ͳ����Ϣ�ṹ*/
typedef struct tagAdsStats
{
    u32      m_dwCur;           //��ǰʹ������
    u32      m_dwMaxUsage;      //����ʹ������
    u32      m_dwMax;           //�������
} TAdsStats;


class STK_API CAdsArray
{
public:
    CAdsArray();
    virtual ~CAdsArray();

    /*====================================================================
    ������      ��Create(s32 nElemSize, s32 nMaxElemNum, const s8* pchName)
    ����		�������������������Array�ڴ棬��������Ӧ�Ĳ���
    �������˵����nElemSize     Ԫ�ش�С
                  nMaxElemNum   ���Ԫ������
                  logMgr        ��־���
                  pchName       Array����
    ����ֵ˵��  ��ʧ�ܣ�FALSE
                  �ɹ���TRUE
    ====================================================================*/    
    BOOL32 Create(s32 nElemSize, s32 nMaxElemNum, const s8* pchName=NULL);

    //�ͷ�ռ�õĿռ�
    void Close();

    //�ж϶����Ƿ���Ч
    BOOL32 IsValid(); 
    
    //����һ���µĵ�Ԫ�����ص�Ԫ��ָ�롣�����ڲ�����Ԫ��Id�ĳ��ϣ�
    PArrayElement Add();

    /*====================================================================
    ������      ��Add(PArrayElement pElem)
    ����		����pElemԪ�ؼ�������
    �������˵����pElem---ָ���û�Ԫ�ص�ָ�룬Ԫ�ش�С�̶�
    ����ֵ˵��  ��ʧ�ܣ�����-1
                  �ɹ��������������е�λ��
    ====================================================================*/
    s32 Add(PArrayElement pElem);

    /*====================================================================
    ������      ��AddExt(PArrayElement* ppOutElem)
    ����		��ȡ��һ���յ�Elem������ppOutElemָ�������
    �������˵����ppOutElem---���ڱ��淵�ص�ָ��
    ����ֵ˵��  ��ʧ�ܣ�����-1;
                  �ɹ��������������е�λ�ã�
    ====================================================================*/
    s32 AddExt(PArrayElement* ppOutElem);
    
    /*====================================================================
    ������      ��GetByPtr(void *pPtr)
    ����		��ͨ��Ԫ��ָ��õ���Ԫ�ص�λ��
    �������˵����pPtr---ָ��Array��Ԫ��ָ��
    ����ֵ˵��  ��ʧ�ܣ�����-1
                  �ɹ��������������е�λ��
    ====================================================================*/
    s32 GetByPtr(PArrayElement pPtr);

    /*====================================================================
    ������      ��GetNext(s32 nCur)
    ����		�����ص�ǰλ��nCur����һ����Ч��Ԫ��λ��
    �������˵����nCur---��ǰ����ʼλ��
    ����ֵ˵��  ��ʧ�ܣ�����-1
                  �ɹ��������������е�λ��
    ====================================================================*/
    s32 GetNext(s32 nCur);
    
    //�������
    void Clear();

    //ɾ��ָ����Ԫ��
    BOOL32 Delete(PArrayElement pArrayElement);

    /*====================================================================
    ������      ��Delete(s32 nLocation)
    ����		��ɾ��ָ��Ԫ��
    �������˵����nLocation---ɾ����Ԫ��λ�ú�
    ����ֵ˵��  ��ʧ�ܣ�FALSE
                  �ɹ���TRUE
    ====================================================================*/
    BOOL32 Delete(s32 nLocation);

    /*====================================================================
    ������      ��Find(void* pParam)
    ����		�������ڲ��ȽϺ�����Ѱ������ĵ�һ��Ԫ��
    �������˵����pParam---�ȽϺ����Ĳ��������бȽϵĹؼ�ֵ
    ����ֵ˵��  ��ʧ�ܣ�-1
                  �ɹ����ҵ��ĵ�Ԫ��λ�ú�
    ====================================================================*/
    s32 Find(void* pParam);

    /*====================================================================
    ������      ��GetElem(s32 nLocation)
    ����		��ȡ��ָ��λ���ϵ�Ԫ��
    �������˵����nLocation----��Ԫ��λ�ú�
    ����ֵ˵��  ��ʧ�ܣ�NULL
                  �ɹ�����Ԫ��ָ��
    ====================================================================*/
    PArrayElement GetElem(s32 nLocation);
    
    //ȡ��Array��ͳ����Ϣ�����󷵻�FALSE
    BOOL32 GetStatistics(TAdsStats* pStats);
    BOOL32 GetStatistics(s32* pnTotalNum, s32* pnMaxUsage, s32* pnCurNum);

    //ȡ�õ�һ���ڵ��λ�ã����󷵻�KDVERROR
    s32 GetFirstLocation();

    //���õ�һ���ڵ��λ�ã����󷵻�KDVERROR
    s32 SetFirstLocation(s32 nLlocation);

    //ȡ�����һ���ڵ��λ�ã����󷵻�KDVERROR
    s32 GetLastLocation();

    //�������һ���ڵ��λ�ã����󷵻�KDVERROR
    s32 SetLastLocation(s32 nLlocation);

    //ȡ�õ�ǰԪ�ص����������󷵻�KDVERROR
    s32 GetCurNum();

    //ȡ�õ�ǰ�յ�Ԫ�����������󷵻�KDVERROR
    s32 GetFreeNum();

    //ȡ��Array��������������󷵻�KDVERROR
    s32 GetMaxNum();

    //�ж�ָ��λ���ϵ�Ԫ���Ƿ�Ϊ��, Ϊ�շ���TRUE
    BOOL32 IsElemVacant(s32 nLocation);

    //ȡ��Array�����֣����󷵻�NULL
    const s8* GetName();

    //ȡ�÷�ֵʹ�����������󷵻�KDVERROR
    s32 GetMaxUsage();

    //ȡ��Ԫ�صĴ�С�����󷵻�KDVERROR
    s32 GetElemSize();

    //ȡ��Array�ıȽϺ���
    IsElemMatchingT GetCompareFunc();

    //���õ�Ԫ����ص�����
    void SetCompareFunc(IsElemMatchingT Func);
    
    //�õ���Ԫ����ص�����
    ProcessElemT GetProcElemFunc();

    //���ô�ӡ����
    void SetProcElemFunc(ProcessElemT Func);

    //�����е�Ԫ����Ĭ�ϵ�Ԫ���������д���
    //pParam�ǵ�Ԫ�������Ĳ�����ÿ�ε��õ�Ԫ��������pParam��Ϊ����ֵ
    void DoAll(void *pParam);

private:
    //ȡ�÷����ڴ������
    s32 GetAllocationSize(s32 nElemSize, s32 m_nMaxNumOfElements);

    //����ָ����Ԫ������
    void SetElem(s32 nLocation, PArrayElement pSrc);
    
private:
    //ȡ��λͼ��ʼλ��
    #define BITMAP(pHeader)      ((u8 *)(pHeader) + sizeof(TArrayHeader))
    
    //λͼ��С
    #define BITMAPSIZE(n)   (((n)+7)/8 + (ALIGNSIZE - (((n)+7)/8)%ALIGNSIZE)%ALIGNSIZE)


    //�õ�ָ��λ�õ�����
    #define ELEMDATA(nLoc) \
                    (m_ptHeader->m_pchArrayLocation + (nLoc) * m_ptHeader->m_dwElemSize)

   
private:
    struct tagArrayHeader* m_ptHeader;

};







/*-----------------------------   CAdsList      ----------------------------------
    CAdsList�����������CAdsArray�Ļ����Ͻ�һ�������˽ṹ���ǰ�����ӹ�ϵ���ṩ��
һ����Ӧ���������������
---------------------------------------------------------------------------------*/
//����ڵ��û����ݵ�Ԫ
typedef void* PListElement;

class STK_API CAdsList : private CAdsArray
{

public:
    CAdsList(){};
    virtual ~CAdsList();

    /**************************������ɾ��***********************************/
    //����ռ䣬��������ʼ��List����
    BOOL32  Create(s32 nElemSize, s32 nMaxElemNum, const char* pchName=NULL);
    //����List�����ͷſռ�
    void    Close();


    /**************************�ڵ������***********************************/
    //�õ������ͷ
    s32 Head() { return CAdsArray::GetFirstLocation(); }

    //�õ������β
    s32 Tail() { return CAdsArray::GetLastLocation(); }

    //�õ��������һ���ڵ�
    s32 Next(s32 nLocation);

    //�õ������ǰһ���ڵ�
    s32 Prev(s32 nLocation);

    //�õ�����ָ���ڵ��Ԫ��
    PListElement GetElem(s32 nLocation);

    //ͨ��Ԫ��ָ��õ�����ڵ�
    s32 GetByPtr(PListElement pListElement);

    //��ע��ıȽϺ����������в���ƥ��Ľڵ�
    s32 Find(s32 nLocation, void *pParam);

    //�õ�Ԫ�ش�С
    s32 GetElemSize()
    {
        return CAdsArray::GetElemSize() - sizeof(s32) - sizeof(s32);
    };


    
    /**************************�����ɾ��***********************************/
    //��Ԫ�ؼ���������ָ��λ��֮��
    s32     Add(s32 nLocation, PListElement elem); /* after location */
    //ɾ��ָ���Ľڵ㡣
    BOOL32  Delete(s32 nLocation);
    //ɾ�����нڵ�
    BOOL32  DeleteAll();
    //����ڵ㣬���³�ʼ������
    void    Clear();

    //�ӵ�β��    
    s32 AddTail(PListElement pElem)
    {
        return Add(Tail(), pElem);
    };

    //�ӵ�ͷ��
    s32 AddHead(PListElement pElem)
    {
        return Add(KDVERROR, pElem);
    };

    //ɾ��ͷ�ڵ�
    BOOL32 DeleteHead()
    {
        return Delete(Head());
    };

    //ɾ��β�ڵ�
    BOOL32 DeleteTail()
    {
        return Delete(Tail());
    };

    /**************************����*************************************/

    //���ζ������е�Ԫ������Ԫ����
    //pParam�ǵ�Ԫ����ص������Ĳ���������ÿ�ε��ú��óɻص������ķ���ֵ
    void DoAll(void *pParam);
    

    /*************************����̳й����Ĳ���˽�к���****************************/

    //ȡ�õ�ǰԪ�ص�����
    s32 GetCurNum() { return CAdsArray::GetCurNum(); }

    //ȡ���������
    s32 GetMaxNum() { return CAdsArray::GetMaxNum(); }

    //ȡ�ñȽϺ���
    IsElemMatchingT GetCompareFunc() { return CAdsArray::GetCompareFunc(); }

    //���ñȽϺ���
    void SetCompareFunc(IsElemMatchingT pFunc) { CAdsArray::SetCompareFunc(pFunc); }

    //�ж�ָ��λ���ϵĽڵ��Ƿ�Ϊ��
    s32 IsElemVacant(s32 nLocation) { return CAdsArray::IsElemVacant(nLocation); }

    //ȡ������Ԫ��ʹ������
    s32 GetMaxUsage() { return CAdsArray::GetMaxUsage(); };

    //ȡ��ͳ����Ϣ
    s32 GetStatistics(TAdsStats* pStats) { return CAdsArray::GetStatistics(pStats); }

    BOOL32 GetStatistics(s32* pnTotalNum, s32* pnMaxUsage, s32* pnCurNum)
    {
        return CAdsArray::GetStatistics(pnTotalNum, pnMaxUsage, pnCurNum);
    };

    //�õ���ӡ����
    ProcessElemT GetProcElemFunc() { return CAdsArray::GetProcElemFunc(); }
    
    //���ô�ӡ����
    void SetProcElemFunc(ProcessElemT func){ CAdsArray::SetProcElemFunc(func); }


private:
    //��Ԫ�ؼ�������,�����������ϵ�޸�
	s32 AddNode(PListElement pElem);
};





/*-----------------------------   CAdsTree      ----------------------------------
    CAdsTree����������CAdsArray�Ļ��������������Ĺ���Ͳ�����
    Tree���ݵ���֯��ʽ��
        A��Tree�ڵ��childָ��ָ���һ��child�ڵ�(��Ϊhead)��
        B��һ���ڵ������child�ڵ�ͨ��brotherָ�빹�ɵ�������;
        C���յ�ָ�붼Ϊ-1��
    
      ����������
                         (��)          A
                                    /  |  \
                                   B   C   D
                                 /  \  | 
                                E    F G
        
          Preorder������ ���������ٸ��ڵ㡣˳��Ϊ��EFBGCDA
          Postorder�������ȸ��ڵ㣬��������˳��Ϊ��ABEFCGD
          ʵ����Ĭ�ϵı�������Next����Postorder˳��          
          
            ע�⣺����������Ƕ�����������û�����ҵĸ��
---------------------------------------------------------------------------------*/
//���ڵ��û���Ԫ
typedef void* PTreeElement;


class CAdsTree;

/*
    ���ڵ㴦����ԭ��
    ��ѭ�������У�ÿ�ε��ý���������pParam�óɷ���ֵ����������һ�ε���
    �ú��������ڶ����С�
*/
typedef void* (*TreeProcElemFuncT)(CAdsTree* pcTree, s32 nNodeId, void *pParam);

/*
    ������������ڵ㴦����ԭ��
    ��ѭ�������У�ÿ�ε��ý���������pParam�óɷ���ֵ����������һ�ε���
    �ú��������ڶ����С�
*/
typedef void* (*TreeProcElemFuncLayerT)(CAdsTree* pcTree, s32 nNodeId, s32 nLayer, void *pParam);

/*
    �ж��������ڵ��Ƿ�ƥ��ĺ���ԭ��
    ���ƥ�䣬�򷵻�TRUE, ���򷵻�FALSE
*/
typedef BOOL32 (*TreeIsTwoMatchingT)(PTreeElement pElem1, PTreeElement pElem2, void *pParam);



class STK_API CAdsTree : private CAdsArray
{
 
public:
    CAdsTree(){};
    virtual ~CAdsTree();

    //��������ʼ��Tree����
    BOOL32 Create(s32 nElemSize, s32 nMaxElemNum, const char* pchName);
    //���ٷ���ĵ�Ԫ
    void Close();


    /*********************  �������ʲ�������   **************************/

    //�õ����ݵ�Ԫָ�룬ʧ�ܷ���NULL
    PTreeElement GetElem(s32 nLoc);

    //�õ����ڵ㣬ʧ�ܷ���KDVERROR
    s32 GetRoot(s32 nodeId);

    //�õ���N���ӽڵ㣬ʧ�ܷ���KDVERROR
    s32 GetByIndex(s32 nParent, s32 nIndex);

    //�õ����ڵ㣬ʧ�ܷ���KDVERROR
    s32 Parent(s32 nNode);

    //�õ���һ���ֵܽڵ㣬ʧ�ܷ���KDVERROR
    s32 Brother(s32 nNode);

    //�õ���һ���ӽڵ㣬ʧ�ܷ���KDVERROR
    s32 Head(s32 nParent);

    //�õ����һ���ӽڵ㣬ʧ�ܷ���KDVERROR
    s32 Tail(s32 nParent);

    //�õ��ӽڵ����ţ�ʧ�ܷ���KDVERROR
    s32 Index(s32 nParent, s32 nChild);

    //�õ��ӽڵ����Ŀ��ʧ�ܷ���KDVERROR
    s32 NumChilds(s32 nParent);

    //�õ���һ���ڵ�(Postorder˳��)��ʧ�ܷ���KDVERROR
    s32 Next(s32 nRoot, s32 nLocation);

    //�õ������Ľڵ�����ʧ�ܷ���KDVERROR
    s32 TreeSize(s32 nRootId);

        
    /************************    ���    ********************************/

    //����һ���µĸ��ڵ㣬�����µĸ��ڵ�ţ�ʧ�ܷ���KDVERROR
    s32 AddRoot(PTreeElement pElem);

    //�����һ���ӽڵ㣬�����¼���ڵ�Ľڵ�ţ�ʧ�ܷ���KDVERROR
    s32 AddHead(s32 nParent, PTreeElement pElem);

    //�������һ���ӽڵ㣬�����¼���ڵ�Ľڵ�ţ�ʧ�ܷ���KDVERROR
    s32 AddTail(s32 nParent, PTreeElement pElem);

    //�����ֵܽڵ㣬�����¼���ڵ�Ľڵ�ţ�ʧ�ܷ���KDVERROR
    s32 AddBrother(s32 nBrother, PTreeElement pElem);

    /*====================================================================
    ������      ��AddTree(s32 nDestParentId, CAdsTree* pcSrcTree, s32 nSrcRootId,
                          TreeProcElemFuncT pAddFunc, void* pParam)
    ����		����Դ����pcSrcTre��ָ����nSrcRootIdȫ�����Ƶ�����nDestParentId�ڵ��£�
                  ��ΪnDestParentId�ڵ�����һ��child��
                  ���ƹ�����ÿ�μ����½ڵ㶼���ûص�����pAddFunc��
    �������˵����nDestParentId Ŀ��parent�ڵ�
                  pcSrcTree     ָ��Դ�������ָ��
                  nSrcRootId    Դ�����ĸ��ڵ�
                  pAddFunc      �ص�����
                  pParam        �ص���������
    ����ֵ˵��  ���ɹ����������ĸ��ڵ�
                  ʧ�ܣ�KDVERROR
    ====================================================================*/
    s32 Add(s32 nDestParentId, CAdsTree* pcSrcTree, s32 nSrcRootId, TreeProcElemFuncT pAddFunc, void* pParam)
    {
        return AddTree(nDestParentId, pcSrcTree, nSrcRootId, pAddFunc, pParam, TRUE);
    };

    /*====================================================================
    ������      ��AddChilds(s32 nDestParentId, CAdsTree* pcSrcH, s32 nSrcRootId,
                            TreeProcElemFuncT pAddFunc, void* pParam)
    ����		����Դ����pcSrcTre��ָ���ڵ�nSrcRootId�µ�ȫ���������Ƶ�����nDestParentId
                  �£����ƹ�����ÿ�μ����½ڵ㶼���ûص�����pAddFunc��
    �������˵����nDestParentId Ŀ��parent�ڵ�
                  pcScRH        ָ��Դ�������ָ��
                  nSrcRootId    Դ�����ĸ��ڵ�
                  pAddFunc      �ص�����
                  pParam        �ص���������
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 AddChilds(s32 nDestParentId, CAdsTree* pcSrcH, s32 nSrcRootId,
                     TreeProcElemFuncT pAddFunc, void* pParam);


    /************************    �ƶ�   ********************************/

    /*====================================================================
    ������      ��Set(s32 nDestParentId, CAdsTree* pcSrcH, s32 nSrcRootId, TreeProcElemFuncT pAddFunc,
                      TreeProcElemFuncT fDleteFunc, void* pParam)
    ����		����Դ����pcSrcTree��ָ����nSrcRootIdȫ�����Ʋ����nDestParentId����
                  ���ƺ�nDestParentId������nSrcRootId������ͬ����nDestParentId�ڵ��
                  brother��parent��ϵ���䡣ԭ��nDestParentId�ڵ��µĽڵ�ȫ��ɾ����
    �������˵����nDestParentId Ŀ��parent�ڵ�
                  pcScRH        ָ��Դ�������ָ��
                  nSrcRootId    Դ�����ĸ��ڵ�
                  pAddFunc      �ڵ�����ʱ�Ļص�����
                  pDleteFunc    �ڵ�ɾ��ʱ�Ļص�����
                  pParam        �ص���������
    ����ֵ˵�� �� �ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 Set(s32 nDestParentId, CAdsTree* pcSrcH, s32 nSrcRootId, TreeProcElemFuncT pAddFunc,
               TreeProcElemFuncT pDleteFunc, void* pParam);

    /*====================================================================
    ������      ��Move(s32 nDestNodeId, s32 nSrcRootId, BOOL32 bKeepSrcRoot, 
                       TreeProcElemFuncT pDleteFunc, void* pParam)
    ����		����ָ���ڵ�nSrcRootId������ȫ���ƶ�������nDestParentId�¡�
                  ԭnDestParentId�µĽڵ�ȫ��ɾ���������а�����ϵ�����������ƶ���
    �������˵����nDestParentId Ŀ��parent�ڵ�
                  nSrcRootId    Դ�����ĸ��ڵ�
                  bKeepSrcRoot  �Ƿ���nSrcRootId�ڵ㣨��ָ���ڵ㣩
                  pDleteFunc       �ڵ�ɾ��ʱ�Ļص�����
                  pParam        �ص���������
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 Move(s32 nDestNodeId, s32 nSrcRootId, BOOL32 bKeepSrcRoot, 
                TreeProcElemFuncT pDleteFunc, void* pParam);

    /*====================================================================
    ������      ��AdoptChild(s32 nAdoptedChildId, s32 nNewParentId, s32 nNewBrotherId)
    ����		���ѽڵ��ƶ����µ�λ�á�
    �㷨ʵ��	��
    ����ȫ�ֱ�������
    �������˵����nAdoptedChildId   �ƶ��Ľڵ�
                  nNewParentId  ��λ�õ�parent
                  nNewBrotherId ��λ�õ�brother
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 AdoptChild(s32 nAdoptedChildId, s32 nNewParentId, s32 nNewBrotherId);


    /************************    ɾ��   ********************************/

    //ɾ���������ɹ�����TRUE��ʧ�ܷ���FALSE
    BOOL32 Delete(s32 nRootId, TreeProcElemFuncT pDleteFunc, void *pParam);

    //ɾ�����ڵ��µ�ȫ���������ɹ�����TRUE��ʧ�ܷ���FALSE
    BOOL32 DeleteChilds(s32 nRootId, TreeProcElemFuncT pDleteFunc, void *pParam);


    /************************    ��ѯ   ********************************/

    //�����ӽڵ㣬�ɹ�����TRUE��ʧ�ܷ���FALSE
    s32 GetChild(s32 nParent, void *pParam, s32 nIndex);

    /*====================================================================
    ������      ��Find(s32 nRootId, void *pParam, s32 nIndex)
    ����		��������nRootId�в��ҵ�nIndex��ƥ��Ľڵ㡣
                  ����˳�����Postorder��
                  ����ע��ıȽϺ������бȽϣ��ޱȽϺ����������ֱ�ӱȽϵ�һ��ֵ��
    �������˵����nSubTreeRoot  ���ڵ�
                  pParam        �ȽϺ����Ĳ���
                  nIndex        ���
    ����ֵ˵��  ���ɹ����ҵ��Ľڵ��
                  ʧ�ܣ�KDVERROR
    ====================================================================*/
    s32 Find(s32 nRootId, void *pParam, s32 nIndex);

    /*====================================================================
    ������      ��CompareTrees(s32 nDestRootId, CAdsTree* pcSrcH, s32 nSrcRootId,
                               RTECompareTwo pCompareTwoFunc, void *pParam)
    ����		���Ƚ����������Ľڵ��ֵ������������next�����������ޱȽϺ�����ʱ��
                  ���õ�Ԫ���ݱȽϡ�
                  ע������˵������������״��ͬ��
    �������˵����nDestRootId        Ŀ��parent�ڵ�
                  pcSrcH             Դ������
                  nSrcRootId         Դ�����ĸ��ڵ�
                  pCompareTwoFunc    �Ƚϻص�����
                  pParam             �ص���������
    ����ֵ˵��  ����ͬ��TRUE
                  ��ͬ��FALSE
    ====================================================================*/
    BOOL32 CompareTrees(s32 nDestRootId, CAdsTree* pcSrcH, s32 nSrcRootId,
                        TreeIsTwoMatchingT pCompareTwoFunc, void *pParam);

    //�����и��ڵ�ִ��ָ������
    void DoAllRoot(TreeProcElemFuncT pOperationFunc, void* pParam);

    /*====================================================================
    ������      ��ProcElemsInDepth(s32 nParent, s32 nMaxLevel, void *pParam);
    ����		������ָ������ڵ����е�Ԫ������˳��Preorder��
    �������˵����nParent         �����ĸ�
                  nMaxLevel       ���Ĵ�ӡ������������ʾ������
                  pParam          �ص���������
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 ProcElemsInDepth(s32 nParent, s32 nMaxLevel, void *pParam);
    
    //�õ���һ�����ĸ���ʧ�ܷ���KDVERROR
    s32 Root(); 
    
    //Preorder˳���µ���һ���ڵ㣬������ʧ�ܷ���KDVERROR
    s32 NextPreorder(s32 nRoot, s32 nLocation);
    
    //�õ����������ߵĽڵ㣬ʧ�ܷ���KDVERROR�� �ú����ɵõ�preorder��������ʼ�ڵ�
    s32 LeftMostChild(s32 nParent);


    /*************************����̳й����Ĳ���˽�к���****************************/

    //���
    void Clear() { CAdsArray::Clear(); }

    //ȡ��Array�ıȽϺ���
    IsElemMatchingT GetCompareFunc() { return CAdsArray::GetCompareFunc(); }

    //���ñȽϺ���
    void SetCompareFunc(IsElemMatchingT pFunc) { CAdsArray::SetCompareFunc(pFunc); }

    //�õ���Ԫ������
    TreeProcElemFuncLayerT GetProcElemFunc()
    { 
        return (TreeProcElemFuncLayerT)CAdsArray::GetProcElemFunc();
    }

    //���õ�Ԫ������
    void SetProcElemFunc(TreeProcElemFuncLayerT pFunc)
    { 
        CAdsArray::SetProcElemFunc((ProcessElemT)pFunc);
    }

    //�õ���ǰʹ�õĽڵ���
    s32 GetCurNum() { return CAdsArray::GetCurNum(); }

    //�õ��������
    s32 GetMaxNum() { return CAdsArray::GetMaxNum(); }

    //ȡ�õ�ǰ�յ�Ԫ������
    s32 GetFreeNum() { return CAdsArray::GetFreeNum(); }

    //�õ����ʹ����
    s32 GetMaxUsage() { return CAdsArray::GetMaxUsage(); }

    //�ж�ָ��λ���ϵĽڵ��Ƿ�Ϊ��
    s32 IsElemVacant(s32 nLocation) { return CAdsArray::IsElemVacant(nLocation); }

    //ȡ��ͳ����Ϣ
    s32 GetStatistics(TAdsStats* pStats) { return CAdsArray::GetStatistics(pStats); }

    BOOL32 GetStatistics(s32* pnTotalNum, s32* pnMaxUsage, s32* pnCurNum)
    {
        return CAdsArray::GetStatistics(pnTotalNum, pnMaxUsage, pnCurNum);
    };


private:
    //����ڵ�
    s32 AddNode(PTreeElement pElem, s32 nParent, s32 nBrother);
    
    //ɾ���ڵ�
    BOOL32 DeleteNode(s32 nLocation, TreeProcElemFuncT pDleteFunc, void *pParam);

    //����Ϊ�ӽڵ�
    s32 SetChild(s32 nParent, s32 nChild);

    //����Ϊ�ֵܽڵ�
    s32 SetBrother(s32 nLocation, s32 nBrother);

    //��Tree�����е���������
    s32 AddTree(s32 nDestParentId, CAdsTree* pcSrcTree, s32 nSrcRootId,
                TreeProcElemFuncT fadd, void* pParam, BOOL32 bCheck);

    //Postorder˳���µ���һ���ڵ�
    s32 NextPostorder(s32 nRoot, s32 nLocation);

    /* �Ƶ��������� */
    BOOL32 Move2Other(s32 nDestNodeId, s32 nSrcRootId, BOOL32 bKeepSrcRoot,
                      TreeProcElemFuncT pDleteFunc, void *pParam);

    //����ǰ��Ԫ�����ݹ鴦����һ�㵥Ԫ������˳��Postorder
    BOOL32 RecureProcElem(s32 nParent, s32 nMaxLevel, void *pParam, 
                          TreeProcElemFuncLayerT pFunc,  u32 dwLayer);

};	








/*-----------------------------   CAdsPool      ----------------------------------
	CAdsPool������������CAdsArray�Ļ����Ͻ�һ�������˿�ķ���͹���ʹ�ø��ʺ�
�����޽ṹ���ڴ���������ȡ����̬�ڴ������ͷš�
---------------------------------------------------------------------------------*/
class CAdsPool:private CAdsArray
{
public:
    //���캯��
    CAdsPool(){};
    //��������
    virtual ~CAdsPool();

    /*====================================================================
    ������      ��Create(s32 nElemSize, s32 nMaxNumOfBlocks, const s8*  pszName)
    ����		�������������������Pool�ڴ棬����Pool�ڵ�Ľṹ��ȷ������
                  ��Ԫ�Ĵ�С
    �������˵����nElemSize         Ԫ�ش�С
                  nMaxNumOfBlocks   ���Ԫ������
                  pszName           Pool����
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 Create(s32 nElemSize, s32 nMaxNumOfBlocks, const s8* pszName);
    
    //���ٷ�����ڴ浥Ԫ
    void Close();
    
    //���Pool�е���������
    void Clear() { CAdsArray::Clear(); }


    /*====================================================================
    ������      ��Alloc(s32 nSize)
    ����		����Pool�з���ռ䣬���ѷ���Ŀռ�����
    �������˵����nSize         ��Ҫ����Ĵ�С
    ����ֵ˵��  ������Ŀ�������ʼ���
                  ʧ�ܣ�KDVERROR
    ====================================================================*/
    s32 Alloc(s32 nSize);
    
    /*====================================================================
    ������      ��AllocCopyExternal(const void* pSrc, s32 nSize)
    ����		����Pool�з���ռ䣬�����ⲿ����Դ���
    �������˵����pSrc          �ⲿ����ָ�룬���ΪNULL���������
                  nSize         �������ݵ�����
    ����ֵ˵��  ���ɹ�������Ŀ�������ʼ���
                  ʧ�ܣ�KDVERROR
    ====================================================================*/
    s32 AllocCopyExternal(const void* pSrc, s32 nSize);

    /*====================================================================
    ������      ��AllocCopyInternal(CAdsPool* pcSrcPool, const void* pSrc, s32 nSize)
    ����		����Pool�з���ռ䣬����ָ����Pool�еĵ�Ԫ��䡣
                  �������鿽����nSize���Դ���Դ������������0��
    �������˵����pcSrcPool     ԴPool����
                  pSrc          Դ���ݵ�Ԫָ��
                  nSize         ���ݵĴ�С
    ����ֵ˵��  ���ɹ�������ռ��ָ��
                  ʧ�ܣ�NULL
    ====================================================================*/
    s32 AllocCopyInternal(CAdsPool* pcSrcPool, s32 nSrc, s32 nSize);

    //���ݿ�ߴ�仯��nLoc��ʼλ�úţ�nSize�µĴ�С��������ʼλ�ú�
    s32 Realloc(s32 nLoc, s32 nSize);

    //�ͷſ�����nLoc��ʼλ�úţ��ɹ�����TRUE��ʧ�ܷ���FALSE
    BOOL32 Delete(s32 nLoc);


    /*====================================================================
    ������      ��CopyFromExternal(s32 nLoc, const void* pSrc, s32 nShift, s32 nSize)
    ����		�����ⲿ����Դ�������ݵ�ָ��λ��
    �������˵����nLoc          ��һ���λ��
                  pSrc          �ⲿ���ݵ�Ԫָ��
                  nShift        �����ڵ���ʼƫ���ֽ���
                  nSize         Ҫ�������ݵĴ�С
    ����ֵ˵��  ��ʵ�ʸ��Ƶ������ֽ���
    ====================================================================*/
    s32 CopyFromExternal(s32 nLoc, const void* pSrc, s32 nShift, s32 nSize);

    /*====================================================================
    ������      ��CopyToExternal(s32 nLoc, void* pDest, s32 nShift, s32 nSize)
    ����		����ָ��λ�ø������ݵ��ⲿ����Դ
    �������˵����nLoc          ��һ���λ��
                  pDest         �ⲿ���ݵ�Ԫָ��
                  nShift        �����ڵ���ʼƫ���ֽ���
                  nSize         Ҫ�������ݵĴ�С
    ����ֵ˵��  ��ʵ�ʸ��Ƶ������ֽ���
    ====================================================================*/
    s32 CopyToExternal(s32 nLoc, void* pDest, s32 nShift, s32 nSize);

    /*====================================================================
    ������      ��CopyInternal(s32 nDestLoc, s32 nSrcLoc, s32 nSize)
    ����		���ڲ�������֮����и���
                  ˵����ʵ�ʸ������ݵĴ�С�ǰ������ġ�
                  Ҫ��nSize�ǰ������ġ�
    �������˵����nDestLoc      Ŀ��������ʼ���
                  nSrcLoc       Դ������ʼ���
                  nSize         �������ݵĴ�С
    ����ֵ˵��  ��ʵ�ʸ��Ƶ������ֽ���
    ====================================================================*/
    s32 CopyInternal(s32 nDestLoc, s32 nSrcLoc, s32 nSize);

    //��ָ�������ݸ��Ƶ���һ��Pool�����ָ������
    BOOL32 CopyPoolToPool(CAdsPool* pcPoolDest, s32 nSrcLoc, s32 nDestLoc, s32 nSize);

    //�ѿ�����һ�����ó�ָ��ֵ��nSize�������
    BOOL32 Set(s32 nLoc, s8 chValue, s32 nSize);
    
    //���ⲿ����Դ���бȽ�
    s32 CompareExternal(s32 nLoc, void* pSrc, s32 nSize);

    //�ڲ����������бȽ�
    s32 CompareInternal(s32 nLocA, s32 nLocB, s32 nSize);

    //�õ�ͳ����Ϣ
    BOOL32 Statistics(s32* pPoolSize, s32* pAvailableSpace, s32* pAllocatedSpace);
    
    BOOL32 GetStatistics(s32* pnTotalNum, s32* pnMaxUsage, s32* pnCurNum)
    {
        return CAdsArray::GetStatistics(pnTotalNum, pnMaxUsage, pnCurNum);
    };

    //�õ�ָ���Ŀ��������ݴ�С
    s32 ChunkSize(s32 nLoc);

    //���ⲿPool�����е����ݿ���бȽ�
    s32 ComparePoolToPool(CAdsPool* pcPoolDest, s32 nSrcLoc, s32 nDestLoc, s32 nSize);

    /*====================================================================
    ������      ��GetPtr(s32 nLoc, s32 nOffset, void **ppPointer, s32 nTotalLength)
    ����		���õ�ʵ�����ݵ�ָ��
    �������˵����nLoc          ����ʼλ��
                  nOffset       ƫ����
                  ppPointer     ���ص�����ָ���ָ��
                  nTotalLength  �������ݵĳ���
    ����ֵ˵��  ������㿪ʼ����������ĳ���
    ====================================================================*/
    s32 GetPtr(s32 nLoc, s32 nOffset, void **ppPointer, s32 nTotalLength);
    
private:
    BOOL32 INVALID_LOCATION(s32 nLoc);
    struct tagPoolElem* GetNode(s32 nLoc);
};


/*-----------------------------   CAdsHash      ----------------------------------
    CAdsHash����ϣ�������CAdsArray�Ļ����Ͻ�һ�������˹�ϣ��Ĺ����Լӿ�������
������ʽ������Hash����ֵ�ĺ��������û��ṩ��
---------------------------------------------------------------------------------*/

/*����Hash Key�ĺ���*/
typedef u32 (*PHashFuncT)(void *pKey, s32 nKeySize, s32 nHashSize);

/*Ԫ�صıȽϺ������Ƚϼ�ֵ�Ƿ����*/
typedef BOOL32 (*PHashCompareFuncT)(void *pKey1, void* pKey2, u32 dwKeySize);

class CAdsHash;
//���嵥Ԫ����ص�����ԭ��
typedef void* (*HashProcElemT)(CAdsHash* pcHash, void* pElem, void* pParam);


class STK_API CAdsHash : private CAdsArray
{
public:
    CAdsHash();
	~CAdsHash();

    //������������������ڴ棬��ɳ�ʼ��
    BOOL32 Create(s32 nNumOfKeys, s32 nNumOfElems, 
                  PHashFuncT pHashFunc, PHashCompareFuncT pCompareFunc,
                  s32 nKeySize, s32 nElemSize, const s8* pszName=NULL);

    //���ٷ�����ڴ�
    void Close();

    //�ѵ�Ԫ���ӵ�Hash����
    void* Add(void*  pKey, void*  pUserElem, BOOL32 bSearchBeforeInsert=FALSE);

    //���ҵ�һ��ƥ��Ľڵ�
    void* Find(void* pKey);

    //������һ��ƥ��Ľڵ�
    void* FindNext(void* pKey, void* pNode);

    //�ɽڵ�λ�õõ�����Ԫ�ص�ָ��
    void* GetElement(void* pNode);

    //����ָ���ڵ�ĵ�Ԫ����
    BOOL32 SetElement(void* pNode, void* pUserElem);

    //�õ�ָ���ڵ�Ĺؼ�ֵ��ָ��
    void* GetKey(void* pNode);

    //ɾ��ָ���Ľڵ�
    BOOL32 Delete(void* pNode);
    
    //�����е�Ԫ����Ĭ�ϵ�Ԫ���������д���pParam�ڵ�����ѭ����ֵ
    BOOL32 DoAll(void* pParam);


    //�õ���ӡ����
    HashProcElemT GetProcElemFunc() 
    { 
        return (HashProcElemT)(CAdsArray::GetProcElemFunc());
    }

    //���ô�ӡ����
    void SetProcElemFunc(HashProcElemT pFunc)
    { 
        CAdsArray::SetProcElemFunc((ProcessElemT)pFunc);
    }

    //Ĭ�ϵıȽϺ���
    static BOOL32 DefaultCompare(void *pKey1, void* pKey2, u32 dwKeySize);

    //Ĭ�ϵ�Hash Key����
    static u32 HashStr(void* pParam, s32 nParamSize, s32 nHashSize);

    /*************************����̳й����Ĳ���˽�к���****************************/
    
    //ȡ�õ�ǰԪ�ص�����
    s32 GetCurNum() { return CAdsArray::GetCurNum(); }
    //ȡ���������
    s32 GetMaxNum() { return CAdsArray::GetMaxNum(); }
    //ȡ��Array�ıȽϺ���
    IsElemMatchingT GetCompareFunc() { return CAdsArray::GetCompareFunc(); }
    //���ñȽϺ���
    void SetCompareFunc(IsElemMatchingT pFunc) { CAdsArray::SetCompareFunc(pFunc); }
    //�ж�ָ��λ���ϵĽڵ��Ƿ�Ϊ��
    s32 IsElemVacant(s32 nLocation) { return CAdsArray::IsElemVacant(nLocation); }
    //ȡ������Ԫ��ʹ������
    s32 GetMaxUsage() { return CAdsArray::GetMaxUsage(); }
    //ȡ��ͳ����Ϣ
    s32 GetStatistics(TAdsStats* pStats) { return CAdsArray::GetStatistics(pStats); }

private:
    struct tagHashHeader* m_ptHashHeader;
    
};








/*-----------------------------   CAdsHeap      ----------------------------------
    CAdsHeap���Ѷ���ʵ���˲��ֶ������ܣ���������ȫ����������ʽ˳���ȡ�ڵ㣬��
Ҫ������ʵ����СԪ�صĻ�ȡ�����ڵ��Ƕ��е���СԪ�ء�
    CAdsHeapʵ�����Ѿ�Ĭ���˶��ϵĽڵ㱣�����32λ�з��������ȽϺ������û��ṩ����
����KDVERROR(-1)��
---------------------------------------------------------------------------------*/

typedef s32 (*PCmpareFunc)(s32 nNodeDataA, s32 nNodeDataB, void* pParam);
typedef s32 (*PUpdateFunc)(s32 *pnNodeData, void *pParam);


class STK_API CAdsHeap
{
public:
    CAdsHeap();
    virtual ~CAdsHeap();

    //������������������ڴ棬���Heap����ĳ�ʼ��
    BOOL32 Create(s32 nHeapCapacity, PCmpareFunc pCompareFunc,
                  PUpdateFunc pUpdateFunc, void *pParam);

	//���������������ָ���ڴ�������Heap���󣬲���ɳ�ʼ��
    BOOL32 CreateFrom(s32 nHeapCapacity, s8 *pchBuff, s32 nBuffSize,
                      PCmpareFunc pCompareFunc, PUpdateFunc pUpdateFunc, void *pParam);
	//����Heap
    void Close();
    //�õ�Heap�Ĵ�С
	s32 GetCurNum();
	//�ѽڵ����Heap
	s32 Insert(s32 nNodeData);
	//����Heap���ڵ㣬��ɾ�����ڵ�
	s32 ExtractTop();
	//�õ������ڵ�
	s32 GetTop();
	//ɾ���ڵ�
	s32 DeleteNode(s32 *pnNodeData);
	//���½ڵ�
	BOOL32 UpdateNode(s32 *pnNodeData);
	//���¶Ѷ�
	BOOL32 UpdateTop();

    s32 Point2Pos(s32* pnNodeData);

    s32* Pos2Point(s32 nLoc);

protected:
private:
    //�ӽ��nLoc��ʼ��������heap�������Ϊ��Сֵ
	void Heapify(u32 nLoc);

    //�ѵ�nSrc��ֵ�ƶ���nDest�����������nSrc��ֵ
	void Move(u32 dwDest, u32 dwSrc);

    //�����ڵ�A��B�����ڵ�
	void Swap(u32 dwNodeA, u32 dwNodeB);

    //�ѵ�dwLoc��ֵ��ΪppNodeָ���ֵ�����ص�update����
	void Set(s32 nNodeData, u32 dwLoc);

    //����λ�úŵõ��õ��ָ�루ppNode��
    s32 NODEDATA(s32 nLoc);


private:
    struct tagHeapHeader* m_ptHeader;

};




/*-----------------------------   CAdsBitBuff    ----------------------------------
    CAdsBitBuffʵ��λ����Ĺ���ֻ�ܴ�β�����в���
---------------------------------------------------------------------------------*/

class STK_API CAdsBitBuff
{
public:
    CAdsBitBuff();

    virtual ~CAdsBitBuff();


    /*====================================================================
    ������      ��Create(s32 nBitBytes)
    ����		��������������������ڴ棬��������Ӧ��ʼ��
    �������˵����nBitBytes     Bitbuf������ֽ���
    ����ֵ˵��  ��ʧ�ܣ�FALSE
                  �ɹ���TRUE
    ====================================================================*/
    BOOL32 Create(s32 nBitBytes);

    /*====================================================================
    ������      ��CreateFrom(s32 nBitBytes, s8 *pchBuf, s32 nBufSize)
    ����		�����ⲿ�����Ϲ���Bitbuf����
    �������˵����nBitBytes     Bitbuf������ֽ���
                  pchBuf        �ⲿ����
                  nBufSize      �ⲿ����Ĵ�С
    ����ֵ˵��  ��ʧ�ܣ�FALSE
                  �ɹ���TRUE
    ====================================================================*/
    BOOL32 CreateFrom(s32 nBitBytes, u8 *pchBuf, s32 nBufSize);

    //�ر�λ�����ͷ��Ѿ�������ڴ�
    void Close();


    /*====================================================================
    ������      ��SetOctets(s32 nBitBytes, s32 nBitsInUse, u8 *pchBuf)
    ����		�����ⲿ���е�λ���壨����ͷ�ṹ���������󣬽��й���
    �������˵����nBitBytes     Bitbuf������ֽ���
                  nBitsInUse    �Ѿ�ʹ�õ�bit����
                  pchBuf        λ������ʼ��ַ
    ����ֵ˵��  ��ʧ�ܣ�FALSE
                  �ɹ���TRUE
    ====================================================================*/
    s32 SetOctets(s32 nBitBytes, s32 nBitsInUse, u8 *pchBuf);

    //�ѻ������
    void Clear();

    //ȡ��λ������׵�ַ
    u8* GetBitBuff();

    //λ�����Ƿ��Ƕ����
    BOOL32 IsAligned();
    
    /*====================================================================
    ������      ��AlignBits(s32 nLength)
    ����		���ֽڶ��볤��nLengthʱҪ�����λ��
    �������˵����nLength   λ����
    ����ֵ˵��  ������Ҫ�����λ��
    ====================================================================*/
    s32 AlignBits(s32 nLocation);

    /*====================================================================
    ������      ��SetAligned()
    ����		����λ������Ϊ�����
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 SetAligned();

    /*====================================================================
    ������      ��SetUnaligned()
    ����		����λ������Ϊ�Ƕ����
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 SetUnaligned();

    /*====================================================================
    ������      ��FreeBits()
    ����		���õ�δʹ�õ�λ��
    ����ȫ�ֱ�������
    �������˵������
    ����ֵ˵��  ������δʹ�õ�λ�������󷵻�KDVERROR
    ====================================================================*/
    s32 FreeBits();

    /*====================================================================
    ������      ��FreeBytes()
    ����		���õ�δʹ�õ��ֽ���
    ����ֵ˵��  ������δʹ�õ��ֽ��������󷵻�KDVERROR
    ====================================================================*/
    s32 FreeBytes();
    
    /*====================================================================
    ������      ��BitsInUse()
    ����		���õ���ʹ�õ�λ��
    ����ֵ˵��  ��������ʹ�õ�λ�������󷵻�KDVERROR
    ====================================================================*/
    s32 BitsInUse();

    /*====================================================================
    ������      ��BytesInUse()
    ����		���õ���ʹ�õ��ֽ���
    ����ֵ˵��  ��������ʹ�õ��ֽ��������󷵻�KDVERROR
    ====================================================================*/
    s32 BytesInUse();

    /*====================================================================
    ������      ��AddTail(u8 *pchSrc, s32 nSrcFrom, s32 nSrcBitsNum, BOOL32 bIsAligned) 
    ����		�����ⲿ����Դ����ָ��������λ�ӵ���������β��
    �������˵����pchSrc             �ⲿ����Դ�׵�ַ
                  nSrcFrom           �ⲿ����λ��ƫ����
                  nSrcBitsNum        Ҫ���Ƶ�λ��
                  bIsAligned         �Ƿ�Ҫ����
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32 AddTail(u8 *pchSrc, s32 nSrcFrom, s32 nSrcBitsNum, BOOL32 bIsAligned);

    /*====================================================================
    ������      ��Move(s32 nSrcOffset, s32 nBitsNum, s32 nDestOffset)
    ����		����ָ�����ȵ�����λ��һ��λ�ø��Ƶ���һ��λ�ã�����ԭ��������
    �������˵����nSrcOffset        Դ���ݵ�ƫ��λ��
                  nBitsNum          �ƶ���bit��
                  nDestOffset       Ŀ�����ݵ�ƫ��λ��
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 Move(s32 nSrcOffset, s32 nBitsNum, s32 nDestOffset);

    /*====================================================================
    ������      ��Set(s32 nFromOffset, s32 nBitsNum, u8 *pchSrc)
    ����		�����ⲿ����Դ���Ʋ����ǵ�ָ��λ��
    ����ȫ�ֱ�������
    �������˵����nFromOffset       �����������ƫ��λ��
                  nBitsNum          ���ǵ�bit��
                  pchSrc             �ⲿ���ݵ���ʼ��ַ
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 Set(s32 nFromOffset, s32 nBitsNum, u8 *pchSrc);
    
    /*====================================================================
    ������      ��DelTail(u32 nBitsNum) 
    ����		����β��ɾ��ָ����λ��
    �������˵����nBitsNum          ɾ����bit��
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 DelTail(s32 nBitsNum);

    /*====================================================================
    ������      ��DelHead(s32 nBitsNum) 
    ����		����ͷ��ɾ��ָ����λ��
    �������˵����dwBitsNum          ɾ����bit��
    ����ֵ˵��  ��TRUE:  �ɹ�
                  FALSE: ʧ��
    ====================================================================*/
    BOOL32 DelHead(s32 nBitsNum);
    
    BOOL32 IsOverflow();

    s32 Display();

    static s32 GetAllocationSize(s32 nTotalBytes)
    {
        return sizeof(TBitBufHeader) + nTotalBytes;
    };

private:
    typedef struct tagBitBufHeader{
        BOOL32 m_bIsAllocated;     //�Ƿ�������ڴ�
        s32    m_nBytesNum;        //BitBuff���ֽ���
        s32    m_nBitsInUse;       //��ʹ�õ�bit��
        BOOL32 m_bIsAligned;       //�Ƿ����ֽڶ����
        u8*    m_pchBits;          //BitBuff����ʼ��ַ
        BOOL32 m_bIsOverflow;      //�Ƿ����
    } TBitBufHeader, *PTBitBufHeader;

private:

    BOOL32 IsValid(){ return ((m_ptHeader == NULL) ? FALSE : TRUE); }
    


private:
    PTBitBufHeader m_ptHeader;
};






/*-----------------------------   CAdsETimer    ----------------------------------
    CAdsETimer��ʵ�ֶ�ʱ���Ĺ����ⲿ�����Եص���check()�����ʹ���ʱ���ĵ��ڡ�
����Ķ�ʱ������ѭ����ʱ�������ں��Զ����ݼ��ʱ���ٴμ��붨ʱ�����С���Ҫ�ֹ�����
delete��������ɾ����
---------------------------------------------------------------------------------*/
typedef void (*ETimerHandlerT)(void *param);


class STK_API CAdsETimer
{
public:
    CAdsETimer();
    ~CAdsETimer();

    /*====================================================================
    ������      ��Create(s32 nTimerNum)
    ����		��������ʱ����
    �������˵����nTimerNum     ��ʱ��������
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/    
    BOOL32  Create(s32 nTimerNum);

    /*====================================================================
    ������      ��Close()
    ����		�����ٶ�ʱ����
    ====================================================================*/
    void    Close();

    /*====================================================================
    ������      ��Add(ETimerHandler pCallback, void *pParam, u32 dwTimeOut)
    ����		������һ����ʱ��
    �������˵����pCallback     ��ʱ�����ڵĻص�����
                  pParam        �ص������Ĳ���
                  dwTimeOut     ��ʱ���ĵ���ʱ��
    ����ֵ˵��  ����ʱ����λ�ú�
                  ʧ�ܣ�KDVERROR
    ====================================================================*/    
    s32     Add(ETimerHandlerT pCallback, void *pParam, u32 dwTimeOut);

    /*====================================================================
    ������      ��Delete(s32 nLoc)
    ����		��ɾ��һ����ʱ��
    �������˵����nLoc          ��ʱ����λ�ú�
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32  Delete(s32 nLoc);

    /*====================================================================
    ������      ��DeleteByValue(ETimerHandler pCallback, void* pParam)
    ����		��ͨ����ʱ���Ĳ���ɾ����ʱ��
    �������˵����pCallback    ��ʱ�����ڵĻص�����
                  pParam       �ص������Ĳ���
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/    
    s32     DeleteByValue(ETimerHandlerT pCallback, void* pParam);

    /*====================================================================
    ������      ��Find(ETimerHandler pCallback, void *pParam)
    ����		������һ����ʱ��
    �������˵����pCallback          ��ʱ�����ڵĻص�����
                  pParam             �ص������Ĳ��� 
    ����ֵ˵��  ���ҵ������ض�ʱ����λ�ú�
                  û�ҵ�������KDVERROR
    ====================================================================*/
    s32     Find(ETimerHandlerT pCallback, void *pParam);

    /*====================================================================
    ������      ��Check()
    ����		����鶨ʱ�������Ե��ڵĶ�ʱ�����д���
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/    
    BOOL32  Check(); 

    /*====================================================================
    ������      ��GetNextExpiration()
    ����		��ȡ����һ�����ڵĶ�ʱ���ľ��Ե���ʱ��
    ����ֵ˵��  ���ɹ�����һ�����ڶ�ʱ���ĵ���ʱ��
                  ʧ�ܣ�KDVERROR
    ====================================================================*/
    u32     GetNextExpiration();

    /*====================================================================
    ������      ��GetCount()
    ����		��ȡ����ʹ�ö�ʱ��������
    ����ֵ˵��  ����ʹ�ö�ʱ��������
    ====================================================================*/
    s32     GetCount();

    /*====================================================================
    ������      ��GetParams(s32 nLoc, ETimerHandler* ppCallback, void** ppParam)
    ����		��ȡ�ö�ʱ���Ĳ���
    �������˵����nLoc          ��ʱ����λ�ú�
                  ppCallback    ��ʱ�����ڵĻص�������ָ�루���ڷ��أ�
                  ppParam       �ص������Ĳ�����ָ�루���ڷ��أ� 
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32  GetParams(s32 nLoc, ETimerHandlerT* ppCallback, void** ppParam);
    
    //�õ�App���
    void* GetTimerApp(){ return m_pTimerApp;}
    
    //����App���
    void  SetTimerApp(void* pTimerApp){ m_pTimerApp = pTimerApp;}
    
private:
    /*====================================================================
    ������      ��GetMinElement()
    ����		��ȡ�����Ҫ���ڵĶ�ʱ��
    ����ֵ˵��  ���ɹ������ض�ʱ���ĵ�ַ
                  ʧ�ܣ�NULL
    ====================================================================*/
    struct tagETimerNode* GetMinElement();

    /*====================================================================
    ������      ��UpdateMinElem()
    ����		�����¶�ʱ�����У���������
    �㷨ʵ��	��
    ����ȫ�ֱ�������
    �������˵����
    ����ֵ˵��  ���ɹ���TRUE
                  ʧ�ܣ�FALSE
    ====================================================================*/
    BOOL32      UpdateMinElem();

private:
    CAdsList    m_tList;
    CAdsHeap    m_tHeap;
    void*       m_pTimerApp;
};





/*-----------------------------   CAdsId     ------------------------------------
    CAdsIdʵ�ֶ�һ����������Ĺ����ṩ���䡢�ͷŲ�����
    ��Ҫ���ڷ���˿ں������������
---------------------------------------------------------------------------------*/
class CAdsId
{
public:
    CAdsId();
    ~CAdsId();
    
    //����
    BOOL32 Create(s32 nFrom, s32 nTo);
    
    //�ر�
    void Close();
    
    //����һ������
    s32 New();

    //�ͷ�һ������
    BOOL32 Delete(s32 nId);

    //�ͷ����еĺ���
    BOOL32 DeleteAll();

    //�ж��Ƿ��ǿ��е�
    BOOL32 IsFree(s32 nId);
    
    //�õ���ʼֵ
    s32 GetFrom();
    
    //�õ���ֵֹ
    s32 GetTo();

private:
    struct tagIdHeader* m_pcIdHeader;

    void SetId(s32 nId);
    void ClearId(s32 nId);
    s32  GetId(s32 nId);
        

};


#endif  // _KDVADS_H_
