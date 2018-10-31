#include "pbmsg.h"
#include "pbmessage.pb.h"

namespace pbmsg{

google::protobuf::Message* CreateMessage(const std::string &strFullName)
{
	google::protobuf::Message *pcMessage = NULL;
	const google::protobuf::Descriptor *pcMsgDescriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(strFullName);
	if (pcMsgDescriptor != NULL)
	{
		const google::protobuf::Message * const pcMsgPrototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(pcMsgDescriptor);
		if (pcMsgPrototype != NULL)
		{
			pcMessage = pcMsgPrototype->New();
		}
	}
	return pcMessage;
}	

CPBMsg::CPBMsg()
{
	m_strMsgName.clear();
	m_dwSequenceId = 0;
	m_vctBodys.clear();
}

CPBMsg::~CPBMsg()
{
	Clear();
}

void CPBMsg::Clear()
{
	m_strMsgName.clear();
	m_dwSequenceId = 0;
	for (u32 i = 0; i < m_vctBodys.size(); i++)
	{
		if (m_vctBodys[i].bDelete && m_vctBodys[i].pcBody != NULL)
		{
			SAFE_DELETE(m_vctBodys[i].pcBody);
		}		
	}
	m_vctBodys.clear();
}

void CPBMsg::AddMsgBody( google::protobuf::Message *pcMsgBody )
{
	TBodyItem tBodyItem;
	tBodyItem.bDelete = FALSE;
	tBodyItem.pcBody  = pcMsgBody;
	m_vctBodys.push_back(tBodyItem);
}

google::protobuf::Message* CPBMsg::GetMsgBody( u32 dwIndex /*= 0*/ )
{
	if (dwIndex < m_vctBodys.size())
	{
		return m_vctBodys[dwIndex].pcBody;
	}
	else
	{
		return NULL;
	}
}

u16 CPBMsg::GetMsgBodySize()
{
	return (u16)m_vctBodys.size();
}

BOOL32 CPBMsg::Encode( u8* pbyBuf, u16 &wBufLen )
{
	pbmsg::TPBMessage tMsg;
	tMsg.mutable_header()->set_msg_name(m_strMsgName);
	tMsg.mutable_header()->set_seq_id(m_dwSequenceId);

	pbmsg::TMsgBody *ptBody = NULL;
	for (u32 i = 0; i < m_vctBodys.size(); i++)
	{
		ptBody = tMsg.mutable_body()->Add();
		ptBody->set_name(m_vctBodys[i].pcBody->GetTypeName());
		m_vctBodys[i].pcBody->SerializeToString(ptBody->mutable_content());
	}

	if (tMsg.ByteSize() > wBufLen)
	{
		return FALSE;
	}

	tMsg.SerializeToArray(pbyBuf, wBufLen);
	wBufLen = tMsg.ByteSize();

	return TRUE;
}


BOOL32 CPBMsg::Decode(const u8* pbyBuf, u16 wBufLen )
{
	Clear();

	if (NULL == pbyBuf || 0 == wBufLen)
	{
		return FALSE;
	}

	pbmsg::TPBMessage tMsg;
	tMsg.ParseFromArray(pbyBuf, wBufLen);	

	m_strMsgName = tMsg.mutable_header()->msg_name();
	m_dwSequenceId = tMsg.mutable_header()->seq_id();

	TBodyItem tBodyItem;
	google::protobuf::Message *pcMsgBody = NULL;
	for (s32 i = 0; i < tMsg.body().size(); i++)
	{
		pcMsgBody = CreateMessage(tMsg.body(i).name());

		if (NULL == pcMsgBody)
		{
			return FALSE;
		}

		pcMsgBody->ParseFromString(tMsg.body(i).content());
		tBodyItem.bDelete = TRUE;
		tBodyItem.pcBody  = pcMsgBody;
		m_vctBodys.push_back(tBodyItem);
	}

	return TRUE;
}

}
