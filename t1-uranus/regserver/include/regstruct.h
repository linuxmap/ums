#ifndef _h_regstruct_h__
#define _h_regstruct_h__
#include "umscommonstruct.h"

#define UMS_MAX_ALIAS_SIZE		64
#define CNS_MAX_ALIAS_SIZE		2

//B1 ע����Ϣ���
typedef struct tagTReqRegInfo
{
	EmGetRegInfoType	m_tRegType;			//��ѯ��Ϣ����
	u16					m_wPackSeq;			//����ţ���1��ʼ��0Ϊ��Чֵ
	u16					m_wTotalPackNum;	//������
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[UMS_MAX_ALIAS_SIZE];	//��ʱ��Ϊ���ֵΪ64������Ϊһ������
	EmTPEndpointType	m_emSelfType;				//ע�᷽ ��ϵͳ����(UMS��CNS) 
	
	tagTReqRegInfo()
	{
		memset( this, 0, sizeof(tagTReqRegInfo) );
	}
}TReqRegInfo, *PTReqRegInfo;


//B2 UMSע����Ϣ
typedef struct tagTUmsRegData
{
	u16					m_wAliasNum;	//��������
	TTPAlias			m_atAlias[UMS_MAX_ALIAS_SIZE];	//��������
	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//���е�ַ
	s8					m_aSelfVer[TP_MAX_VERSION_LEN +1];	//ע�᷽ �İ汾��
	s8					m_aCompileTm[TP_MAX_VERSION_LEN +1];	//ע�᷽�ı���ʱ��
	u32					m_dwCallType;	//��������TCP���л���UDP���У�ע������������������
	u32					m_dwExpires;	//��ʱʱ��
	u32_ip				m_dwSelfAddr;	//ע�᷽ �ĵ�ַ

	tagTUmsRegData()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegData));
	}
}TUmsRegData;

//B2 CNSע����Ϣ
typedef struct tagTCnsRegData
{
	u16					m_wAliasNum;	//��������
	TTPAlias			m_atAlias[CNS_MAX_ALIAS_SIZE];	//��������
	TTPTransAddr		m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//���е�ַ
	s8					m_aSelfVer[TP_MAX_VERSION_LEN +1];	//ע�᷽ �İ汾��
	s8					m_aCompileTm[TP_MAX_VERSION_LEN +1];	//ע�᷽�ı���ʱ��
	u32					m_dwCallType;	//��������TCP���л���UDP���У�ע������������������
	u32					m_dwExpires;	//��ʱʱ��
	u32_ip				m_dwSelfAddr;	//ע�᷽ �ĵ�ַ
	
	tagTCnsRegData()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegData));
	}
}TCnsRegData;

//B2 ע����Ϣ���
typedef struct tagTReqRegInfoEx
{
	EmGetRegInfoType	m_tRegType;			//��ѯ��Ϣ����
	EmTPEndpointType   	m_emSelfType;		//ע�᷽ ��ϵͳ����(UMS��CNS)
	u16					m_wPackSeq;			//����ţ���1��ʼ��0Ϊ��Чֵ
	u16					m_wTotalPackNum;	//������

	u16					m_wDataNum;			//�������			

	tagTReqRegInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTReqRegInfoEx));
	}
}TReqRegInfoEx;


#endif // _h_regstruct_h__
