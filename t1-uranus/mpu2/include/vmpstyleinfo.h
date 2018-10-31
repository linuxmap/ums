#ifndef _ums_vmp_style_info_h_
#define _ums_vmp_style_info_h_
#include "tpsys.h"
#include "tptype.h"

//合成风格
class CVmpStyle
{
public:
	CVmpStyle();
	explicit CVmpStyle(EmUmsVmpStyle emStyle);
	
public:
	void	Set(EmUmsVmpStyle emStyle);
	void	Clear();
	
public:
	s32		GetHardStyle() const { return m_nHardStyle; }
	s32		GetChanNum() const { return m_nChanNum; }
	
private:
	EmUmsVmpStyle	m_emStyle;
	s32				m_nChanNum;
	s32				m_nHardStyle;
};

#endif

