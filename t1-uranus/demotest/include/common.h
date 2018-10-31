#ifndef _COMMON_H_
#define _COMMON_H_

#include "osp.h"
#include "kdvtype.h"

#define SERVER_INST_NUM			1
#define SERVER_APP_ID			100
#define SERVER_APP_NAME			"Server"
#define SERVER_APP_PRI			80
#define SERVER_APP_QUEUESIZE	1024
#define SERVER_APP_STACKSIZE	200 << 10

#define CLIENT_INST_NUM			1
#define CLIENT_APP_ID			200
#define CLIENT_APP_NAME			"Client"
#define CLIENT_APP_PRI			80
#define CLIENT_APP_QUEUESIZE	1024
#define CLIENT_APP_STACKSIZE	200 << 10


#define Opr_Ok					u32(0)

enum Ev_Event_Define
{
	Ev_View_Req = 2000,
	Ev_View_ReqRsp,
};

enum EmViewType
{
	emViewType_Invalid = 0,
	emViewType_Ep = 1,
	emViewType_Vmp = 2,
};

typedef struct tagTViewReq
{
	u16			m_wConfId;
	u16			m_wSrcEpId;
	u16			m_wSrcScreenIndex;
	u16			m_wDstEpId;
	u16			m_wDstScreenIndex;
	EmViewType	m_emViewType;

	tagTViewReq()
	{
		memset(this, 0, sizeof(tagTViewReq));
	}

}TViewReq;

#endif //_COMMON_H_