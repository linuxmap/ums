#ifndef _h_msgtype_h__
#define _h_msgtype_h__
#include "kdvtype.h"
#include "xmlengine.h"



namespace UmsTpmsg{

enum EmxSysDataType
{
	emxAtomTypeBegin =0,//ԭ����������
		emx_s32,
		emx_BOOL32,
		emx_BOOL,
		emx_u8,
		emx_s8,
		emx_u16,
		emx_u32,
		emx_u32_ip,
		emx_u8_blob,
		emx_time_t,
		emx_string,
	emxEnumTypeBegin = 20,//ö����������

	emxStructTypeBegin = 400, //���ݽṹ��������(mtstruct.h ҵ���ṹ����ͷ�ļ��Ľ������)

	emxDataTypeEnd = 1000 //���Ͷ������
};

struct TXEVENTINFO
{
	u16   eventid;				//Event idֵ
	char* name;					//Event description
	TXDATANODE* tDataNode;		//����Ӧ�ṹ����

	TXEVENTINFO()
	{
		eventid = 0;
		name = 0;
		tDataNode = 0;
	}
};


//MsgInfo : ��Ϣ��Ϣ
typedef struct tagTTpMsgInfo
{
	u32 m_dwOutMinEventValue;
	u32 m_dwOutMaxEventValue;

	u32 m_dwInnerMinEventValue;
	u32 m_dwInnerMaxEventValue;

	TXDATAINFO** m_ptMsgEnumDataInfo;
	TXDATAINFO** m_ptMsgStructDataInfo;

	tagTTpMsgInfo()
	{
		m_dwOutMinEventValue = 0;
		m_dwOutMaxEventValue = 0;
		m_dwInnerMinEventValue = 0;
		m_dwInnerMaxEventValue = 0;
		m_ptMsgEnumDataInfo = NULL;
		m_ptMsgStructDataInfo = NULL;
	}	
}TTpMsgInfo;


BOOL32 InitEventMgr(TTpMsgInfo& tInfo);
void ExitEventMgr();


} //namespace UmsTpmsg

using namespace UmsTpmsg; 

#endif // _h_msgtype_h__
