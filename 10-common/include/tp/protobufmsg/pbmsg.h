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
		BOOL32 bDelete; ///<CPBMsg内部使用，用于决定是否在CPBMsg对象销毁时delete tBody
		google::protobuf::Message* pcBody;  ///<消息体
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

	google::protobuf::Message* GetMsgBody(u32 dwIndex = 0); // 索引从0开始

	u16  GetMsgBodySize();

	// 编码
	// pbyBuf编码后数据拷贝至此，需要使用者分配空间
	// wBufLen传入为使用者分配pbyBuf的大小，编码成功后，wBufLen作为编码后数据实际大小传出
	// 如果使用者分配的空间太小，不足以容纳编码后数据，则函数返回失败
	BOOL32 Encode(u8* pbyBuf, u16 &wBufLen);

	// 解码
	// pbyBuf待解码的buf
	// wBufLen待解码的buf大小
	BOOL32 Decode(const u8* pbyBuf, u16 wBufLen);

protected:
	std::string              m_strMsgName;      ///<消息Name， 唯一标示
	u32                      m_dwSequenceId;    ///<消息序列号

	std::vector<TBodyItem>   m_vctBodys;        ///<消息体
};

}// namespace pbmsg

#endif //_PB_MSG_H_