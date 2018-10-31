#include "convert.h"


void ConvertViewTypeToPB(const EmViewType tReq, pbmsg::EmViewType& tPbReq)
{
	switch(tReq)
	{
	case emViewType_Invalid:
		tPbReq = pbmsg::emViewType_Invalid;
		break;
	case emViewType_Ep:
		tPbReq = pbmsg::emViewType_Ep;
		break;
	case emViewType_Vmp:
		tPbReq = pbmsg::emViewType_Vmp;
		break;
	default:
		tPbReq = pbmsg::emViewType_Invalid;
		break;
	}
	return;
}

void ConvertViewReqToPB(const TViewReq tReq, pbmsg::TViewReq& tPbReq)
{
	tPbReq.set_wconfid(tReq.m_wConfId);
	tPbReq.set_wsrcepid(tReq.m_wSrcEpId);
	tPbReq.set_wsrcscreenindex(tReq.m_wSrcScreenIndex);
	tPbReq.set_wdstepid(tReq.m_wDstEpId);
	tPbReq.set_wdstscreenindex(tReq.m_wDstScreenIndex);
	pbmsg::EmViewType emPBViewType;
	ConvertViewTypeToPB(tReq.m_emViewType, emPBViewType);
	tPbReq.set_emviewtype(emPBViewType);
	return;
}

void ConvertViewTypeFromPB(const pbmsg::EmViewType tPbReq, EmViewType& tReq)
{
	switch(tPbReq)
	{
	case pbmsg::emViewType_Invalid:
		tReq = emViewType_Invalid;
		break;
	case pbmsg::emViewType_Ep:
		tReq = emViewType_Ep;
		break;
	case pbmsg::emViewType_Vmp:
		tReq = emViewType_Vmp;
		break;
	default:
		tReq = emViewType_Invalid;
		break;
	}
	return;
}

void ConvertViewReqFromPB(const pbmsg::TViewReq tPbReq, TViewReq& tReq)
{
	tReq.m_wConfId = tPbReq.wconfid();
	tReq.m_wSrcEpId = tPbReq.wsrcepid();
	tReq.m_wSrcScreenIndex = tPbReq.wsrcscreenindex();
	tReq.m_wDstEpId = tPbReq.wdstepid();
	tReq.m_wDstScreenIndex = tPbReq.wdstscreenindex();
	ConvertViewTypeFromPB(tPbReq.emviewtype(), tReq.m_emViewType);
	return;
}
