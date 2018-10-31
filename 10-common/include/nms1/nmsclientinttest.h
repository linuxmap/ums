// NmsClientIntTest.h: interface for the CNmsClientIntTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NMSCLIENTINTTEST_H__9D5C14B4_DE71_40A2_9B82_0D6781FEC96C__INCLUDED_)
#define AFX_NMSCLIENTINTTEST_H__9D5C14B4_DE71_40A2_9B82_0D6781FEC96C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include <afxwin.h>
#include "NmcLibDef.h"
#include "nmsmacro.h"

typedef struct tagTConfQuery
{
	s8 m_szConfId[33];	// ����ID
}TConfQuery, *PTConfQuery; 

class CNmsClientIntTest  
{
public:
	CNmsClientIntTest();
	virtual ~CNmsClientIntTest();

	//////////////////////////////////////////////////////////////////////////
	// ���ù���
	//////////////////////////////////////////////////////////////////////////
	
    //�о����е��豸
    virtual u32 CmDeviceEnum(PTEquipProperty patDevices,	 // [in/out] �豸������
					  u32 &dwDeviceCount);	// [in/out] ����Ĵ�С
    //�о��豸���е��豸
    virtual u32 CmDeviceOfDirEnum(u32 dwDirID,
                      PTEquipProperty patDevices,	// [in/out] �豸������
					  u32 &dwDeviceCount);	// [in/out] ����Ĵ�С

    virtual u32 CmDirEnum(PTDirInfo patDirs, // [in/out] �豸�������
                u32 &dwDirCount);    // [in/out] ����Ĵ�С

    virtual u32 CmGetChildDirs(u32 dwDirID,
                    PTDirInfo patDir,     // [in/out] �豸�������
                    u32 &dwDirCount);   // [in/out] ����Ĵ�С

    //�õ��豸�ĵ�ǰ��߸澯����
    virtual u32 CmGetDeviceTopAlarmlevel(u32 dwDeviceID, u32 &dwLevel);
    //�õ���ǰ����澯
    virtual LPCTSTR CmGetDeviceAlarmDesc(u32 dwDeviceID); 
    
    //������Ϣ  [zhuyr][4/28/2005]
    virtual u32 CmGetConfoInfo(PTConfQuery pConfInfo,   // [in/out] ����ID������
                        u32 &dwConfoCount);     // [in/out] ����Ĵ�С
    virtual BOOL32 IsConfoInBase(TConfQuery& tConfID);    //�����Ƿ����
    virtual BOOL32 IsHasConf();                           //�Ƿ��л������

	//////////////////////////////////////////////////////////////////////////
	// ���Ϲ���

	// ��ѯ�豸�ĵ�ǰ�澯, IDΪ���ʾ��ȫ����
	virtual u32 FmCurrentAlarmQuery(u32 dwDeviceID,                         // [in] �豸����
							u32 &dwRecordCount);				// [out] ��¼����
	
	// ��ʷ�澯��ѯ
	virtual u32 FmHistoryAlarmQuery(THistoryAlarmCondition tCondition,	// [in] ��ѯ����
							  u32 &dwRecordCount);				// [out] ��¼����
	
	// ������־��ѯ
	virtual u32 SmOprLogQuery(	TOprLogCondition tCondition, // ��ѯ����
								u32 &dwRecordCount);		// ��¼����
    
    virtual BOOL32 IsLogExist(LPCTSTR lpszLogSerial); //�ַ������Ȳ��ܳ���32������ΪNULL
    /*=============================================================================
    �� �� ���� GetNextBatchRecord
    ��    �ܣ� ��ȡ��һ����¼, FmCurrentAlarmQuery��FmHistoryAlarmQuery�����
    ��    ���� u32 dwRemainCount:          [out]ʵ�ʷ��صļ�¼����
               PVOID pContent:    [out/buffer] ��¼�б��ڴ�
               u32 dwRecCount:             [in] ��¼�ڴ��п��Ա����������¼
    �� �� ֵ�� u32 :�ɹ���0��ʧ�ܣ������롣
    ˵��    ��PVOID���ͣ�PTAlarmContent��FmCurrentAlarmQuery��FmHistoryAlarmQuery����ã�
                         PTOprLogResult��QueryOprLog�����
    =============================================================================*/
    virtual u32 GetNextBatchRecord(u32& dwRemainCount, PTAlarmContent pContent, u32 dwRecCount);
    //�õ���־��¼
    virtual u32 GetNextBatchRecord(u32& dwRemainCount, PTOprLogResult pContent, u32 dwRecCount);
	
	// ��ѯ�豸�Ļ��ܹ�����Ϣ--��ܺ͵���
	virtual u32 FmMockMachineQuery(u32 dwDeviceID,  TMockMachineData& tMockData);	// [out] ��������
	// ���������ѯ������Ϣ
	virtual u32 FmMockBoardRefresh(u32 dwDeviceID, TBoard &tBoard);	// [out] ��������

    //////////////////////////////////////////////////////////////////////////
    // ��ȫ����

	// ö���û�
	virtual u32 SmUserEnum(PTNameStruct patUsers,		// [in/out/array] �û��б�
		u32 &dwBufCount);			// [in/out] �б���Ŀ
	
	// �û���Ϣ��ѯ
	virtual u32 SmUserQueryInfo(u32 dwUserID, PTUserBaseInfo ptUserBaseInof);
	

	// ��ѯ�û���Ȩ��
	virtual u32 SmUserPrivilege(	u32 dwUserID,	// [in] �û�ID
							u32 *pdwArrDevice,	// [in/out] �豸����
							u32 *pdwArrMask,	// [in/out] ��������
							u32 &dwCount);	// [in/out] �����С
	// ��ѯ���Ȩ��
//	virtual u32 SmGroupPrivilege(	u32 dwGroupID,	// [in] ��ID
//							u32 *pdwArrDevice,	// [in/out] �豸����
//							u32 *pdwArrMask,	// [in/out] ��������
//							u32 &dwCount);	// [in/out] �����С
	
	// ö��ϵͳ�е���
	virtual u32 SmGroupEnum(PTNameStruct patGroups,	// [in/out] �������
					  u32 &dwGroupCount);	// [in/out] ����Ĵ�С

	
	// ��ѯ����û���Ա
	virtual u32 SmGroupQueryUser(	u32 dwGroupID,	// [in] ��ı��
		PTNameStruct patUsers,	// [in/out] �û�������
		u32	&dwUserCount);	// [in/out] ����Ĵ�С
	
	// ��ѯ�û�ӵ�е���
	virtual u32 SmUserQueryGroup(	u32 dwUserID,	// [in] �û����
		PTNameStruct patGroups,	// [in/out] �������
		u32 &dwGroupCount);	// [in/out] ����Ĵ�С

    //#define TYPE_DEVICE       1
    //#define TYPE_Dir          2
    //#define TYPE_USER         3
    //#define TYPE_GROUP        4
	
    //���ӣ�������
    virtual BOOL32 LinkInstance(u32 dwIP, u16 dwPort = 2010);
    virtual void UnlinkInstance();

    //  [zhuyr][2/22/2005] �����ӿ�

         //�û��Ƿ����
	virtual BOOL32 IsUserExist(LPCSTR lpszUserName);

	//�û����Ƿ����

	virtual BOOL32 IsGroupExist(LPCSTR lpszGroupName);

	//�豸�Ƿ����

	virtual BOOL32 IsDeviceExist(LPCSTR lpszDeviceName);

	//��ѯĳ���иû�Ա�Ƿ����

	virtual BOOL32 IsUserInGroup(LPCSTR lpszGroupName, LPCSTR lpszUserName);

	//��ѯ�û��Ƿ�ӵ�и���

	virtual BOOL32 IsGroupInUser(LPCSTR lpszUserName, LPCSTR lpszGroupName);

	//��ѯ�豸���Ƿ����

	virtual BOOL32 IsDirExist(LPCSTR lpszDirName);

	//��ѯ�豸���и��豸�Ƿ����

	virtual BOOL32 IsDeviceInDir(LPCSTR lpszDirName , LPCSTR lpszDeviceName);

	//��ѯ�豸���и��豸���Ƿ����

	virtual BOOL32 IsDirInDir(LPCSTR lpszMainDir, LPCSTR lpszChildDir);

	//ͨ��������ȡid

	virtual BOOL32 GetIdByAlias(LPCSTR lpszAlias, s32 nIdType,u32 &dwID);

	//ͨ��id��ȡ����

	virtual BOOL32 GetAliasById(u32 dwID, s32 nIdType, s8* pszAlias);
    
    //�澯֪ʶ��  [zhuyr][5/17/2005]
    //�澯���Ƿ���֪ʶ����  [zhuyr][5/17/2005]
    virtual BOOL32  IsAlarmCodeExist(u32 dwAlarmCode); //1000~15000
    //��ѯĳ���澯���ԭ���б� nSize[in/out]
    virtual u32 GetAlarmKBCause(u32 dwAlarmCode, PTAlarmKBCause pCause, u32 &dwSize);
    //��ѯĳ���澯��Ľ�������б� nSize[in/out]
    virtual u32 GetAlarmKBSolution(u32 dwAlarmCode, PTAlarmKBCause pSolution, u32 &dwSize);

    //��ʷ�澯�Ƿ����  [zhuyr][5/17/2005]
    virtual BOOL32  IsHisAlarmExist(u32 dwSerialNo); 
protected:
	virtual u32 SendEvent(u16 u16Event, const void *pBuf, u16 u16Size,
		void *pAckBuf, u16 u16AckSize, u16 &u16AckSizeRet);

    virtual BOOL32 IsLinked();

    virtual u32 IsElementExist(LPCSTR lpszName, u32 byType);


    u32 m_dwConnectedNode;
    s8  m_szDesc[201];
};

#endif // !defined(AFX_NMSCLIENTINTTEST_H__9D5C14B4_DE71_40A2_9B82_0D6781FEC96C__INCLUDED_)
