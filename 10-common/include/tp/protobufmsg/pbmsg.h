#ifndef _PB_MSG_H_
#define _PB_MSG_H_

#include <vector>
#include <string>
#include <google/protobuf/message.h>
#include <google/protobuf/generated_enum_reflection.h>
#include "kdvtype.h"

namespace pbmsg {

#define SAFE_DELETE(p) \
	do \
	{ \
	if ((p) != NULL) \
	{ \
	delete (p); \
	(p) = NULL; \
} \
} while (0)

class PROTOBUFMSG_API CPBMsg
{	
	struct TBodyItem
	{
		BOOL32 bDelete; ///<CPBMsg�ڲ�ʹ�ã����ھ����Ƿ���CPBMsg��������ʱdelete tBody
		google::protobuf::Message* pcBody;  ///<��Ϣ��
	};

public:
	CPBMsg();
	virtual ~CPBMsg();

	void Clear();

	void SetMsgName(const std::string strMsgName){m_strMsgName = strMsgName;}

	const std::string& GetMsgName(){return m_strMsgName;}

	void SetSequenceID(u32 dwSequenceId){m_dwSequenceId = dwSequenceId;}

	const u32 GetSequenceID(){return m_dwSequenceId;}

	void AddMsgBody(google::protobuf::Message *pcMsgBody);

	google::protobuf::Message* GetMsgBody(u32 dwIndex = 0); // ������0��ʼ

	u16  GetMsgBodySize();

	// ����
	// pbyBuf��������ݿ������ˣ���Ҫʹ���߷���ռ�
	// wBufLen����Ϊʹ���߷���pbyBuf�Ĵ�С������ɹ���wBufLen��Ϊ���������ʵ�ʴ�С����
	// ���ʹ���߷���Ŀռ�̫С�����������ɱ�������ݣ���������ʧ��
	BOOL32 Encode(u8* pbyBuf, u16 &wBufLen);

	// ����
	// pbyBuf�������buf
	// wBufLen�������buf��С
	BOOL32 Decode(const u8* pbyBuf, u16 wBufLen);

protected:
	std::string              m_strMsgName;      ///<��ϢName�� Ψһ��ʾ
	u32                      m_dwSequenceId;    ///<��Ϣ���к�

	std::vector<TBodyItem>   m_vctBodys;        ///<��Ϣ��
};

}// namespace pbmsg

#endif //_PB_MSG_H_