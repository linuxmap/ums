#ifndef _TPADDRMGR_H
#define _TPADDRMGR_H


#include "tpstruct.h"
#include "kdvtype.h"
#include "tptype.h"
#include "tplog.h"
#include <list>
#include <vector>

using namespace UmsTpmsg;

class CSipRegInfo
{
public:
	CSipRegInfo();
	
	virtual ~CSipRegInfo()
	{
		
	}
	void Clear();
	
	void RemoveAll( EmGetRegInfoType emType );
	void AddSipRegInfo( const TTPSipRegInfo &tSipRegInfo );
	void RemoveAllBak( EmGetRegInfoType emType );
	void AddSipRegInfoBak( const TTPSipRegInfo &tSipRegInfo );
	void Replace( EmGetRegInfoType emType );
	u16 GetPackTotalNum( EmGetRegInfoType emType );
	u16 GetPackTotalNumBak( EmGetRegInfoType emType );
	BOOL GetPack( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize );
	BOOL GetPackBak( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize );
	void OutputAll();
	
protected:
	
private:
	std::list<TTPSipRegInfo> m_tSipRegInfoList;     //�����
	
	std::list<TTPSipRegInfo> m_tSipRegInfoList_Bak;     //���汸�ݰ�
};


//ȫ�ֵ�����,����ȫ�ֵ�ַ��
class CTPAddrMgr
{
public:
	enum EmTPAddrMgrStatus
	{
		em_Idle,        
		em_Updating_CNS, //������
		em_Updating_UMS,
		em_Updating_ALL,
		em_EnableNty    //������ɣ�֪ͨ
		
	};
	static CTPAddrMgr *GetInstance()
	{
		static CTPAddrMgr s_cInstance;
		return &s_cInstance;
	}

	virtual ~CTPAddrMgr()
	{

	}
	

	void AddOneUserNty( const TTPAddrNtyUser &tTPAddNtyUser );             //����Ҫ֪ͨ���û�
	u16  GetUserNtyNum( );                                                 //��������û�����
	BOOL GetUserNty( TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize );         //��������û�
	void AddOnePack( const TTPSipRegPackInfo &tPackInfo,
					 const TTPSipRegInfo &tSipRegInfo,
					 const EmGetRegInfoType &emType );                      //�����,ÿ�μ�����ɺ���ҪCHECK״̬����ΪNTY�����֪ͨ����
	
	void ClearUserNty()														//���û��б�
	{
		m_tNtyUserList.clear();
	}

	EmTPAddrMgrStatus GetStatus()										   //�Ƿ��������ȫ����Ϣ
	{
		return m_emStatus;
	}

	void SetStatus( EmTPAddrMgrStatus emStatus )
	{
		m_emStatus = emStatus;
	}

	u16 GetPackTotalNum( EmGetRegInfoType emType )
	{
		return m_cSipRegInfo.GetPackTotalNum( emType );
	}

	BOOL GetPack( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize )
	{
		return m_cSipRegInfo.GetPack( emType, ptSipRegInfo, wSize );
	}
	void OutPutAll()
	{
		msgprint("EmStatus->%d\n",m_emStatus);
		m_cSipRegInfo.OutputAll();
	}

	BOOL IsEnableUpdateAndSetStatus( EmGetRegInfoType emType );

	BOOL IsEnableNtyAndSetStatus()
	{
		if( em_EnableNty == m_emStatus )
		{
			SetStatus( em_Idle );
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

protected:
	CTPAddrMgr()
	{
		Clear();
	}
	void Clear()
	{
		m_cSipRegInfo.Clear();
		m_tNtyUserList.clear();
		m_emStatus = em_Idle;
	}
	void StatusStrategy( EmGetRegInfoType emType );
private:
	CSipRegInfo m_cSipRegInfo;
	std::list<TTPAddrNtyUser> m_tNtyUserList;
	EmTPAddrMgrStatus m_emStatus;                        

};


//B2�汾��ȫ�ֵ�ַ������UMS ʹ��
class CTPAddrMgrEx
{
public:
	CTPAddrMgrEx();
	~CTPAddrMgrEx();

public:
	static CTPAddrMgrEx& Instance();

public:
	//���UMS ��Ϣ
	void		AddPack(const TRegPackInfoEx& tPackInfo, const TUmsRegPackEx& tRegInfo);
	//���CNS ��Ϣ
	void		AddPack(const TRegPackInfoEx& tPackInfo, const TCnsRegPackEx& tRegInfo);
	//���MT  ��Ϣ
	void		AddPack(const TTPMtRegInfo& tMtInfo);
	//���MCU ��Ϣ
	void		AddPack(const TTPMcuRegInfo& tMcuInfo);
	//����û�
	void		AddUser(const TTPAddrNtyUser& tUser);
	void        AddUserForCns(const TTPAddrNtyUser& tUser);
	//ɾ���û�
	void		DelUser(const TTPAddrNtyUser& tUser);

public:
	//��ȡCNS ���ݰ�����
	u16			GetCnsPackNum() const;
	//��ȡCNS ע����Ϣ
	u16			GetCnsRegPack(TCnsRegPackEx* ptCnsInfo, u16 wSize);
	//��ȡUMS ���ݰ�����
	u16			GetUmsPackNum() const;
	//��ȡUMS ע����Ϣ
	u16			GetUmsRegPack(TUmsRegPackEx* ptUmsInfo, u16 wSize);
	//��ȡMT ���ݰ�����
	u16			GetMtPackNum() const;
	//��ȡMT ע����Ϣ
	u16			GetMtRegPack(TTPMtRegInfo* ptMtInfo, u16 wSize);
	//��ȡMCU ���ݰ�����
	u16			GetMcuPackNum() const;
	//��ȡMCU ע����Ϣ
	u16			GetMcuRegPack(TTPMcuRegInfo* ptMcuInfo, u16 wSize);

public:
	//�û�����
	u16			GetUserNums() const;
	//��ȡ�û�
	u16			GetUserNty(TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize);
	//�����û���Ϣ
	void		ClearUser();

public:
	//SIP �������
	BOOL32		IsSipEnd() const;
	//GK  �������
	BOOL32		IsGkEnd() const;
	//����SIP ��Ϣ
	void		ClearSipInfo();
	//����GK ��Ϣ
	void		ClearGkInfo();

	//Add by tanxiaodong 213-08-07.
	//����SIP�е�CNS��Ϣ
	void       ClearCnsInfo();

	//����SIP�е�UMS��Ϣ
	void       ClearUmsInfo();
	//End to add.
	void       ClearGkInfoForCns();

private:
	BOOL32		m_bSipEnd;	//SIP �����Ƿ������
	BOOL32		m_bGkEnd;	//GK  �����Ƿ������

	u16			m_wUseCount;	//�û���Ϣʹ�ô��� ���Ϊ2�Σ��������ֵ��ȷ���Ƿ�Ҫ����ǰ���û���Ϣ

	std::vector<TUmsRegPackEx>	m_umsInfo;	//umsע����Ϣ
	std::vector<TCnsRegPackEx>	m_cnsInfo;	//cnsע����Ϣ
	std::vector<TTPMtRegInfo>	m_mtInfo;	//mt ע����Ϣ
	std::vector<TTPMcuRegInfo>	m_mcuInfo;	//mcuע����Ϣ

	std::vector<TTPAddrNtyUser>	m_userList;	//������û��б�
};



#endif