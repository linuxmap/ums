#ifndef _SIPCONFNONSTDSTRUCT_H
#define _SIPCONFNONSTDSTRUCT_H

#include "kdvsipcommon.h"
#include "sipcallstdstruct.h"
#include "sipconfnonstdmsg.h"

#define SIP_REG_NONSTANDARD "KDRegNSM"


typedef struct tagSipFlowCtrl
{
	s32   m_nChannelId;
	u16   m_wBitRate;
	tagSipFlowCtrl()
	{
		m_nChannelId = -1;
		m_wBitRate = 0;
	}
}TSipFlowCtrl,*PTSipFlowCtrl;

#endif //_SIPCONFNONSTDSTRUCT_H
