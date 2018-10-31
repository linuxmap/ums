#include "vmpstyleinfo.h"
#include "kdvmulpic_hd.h"
#include "umsobject.h"

extern BOOL32 g_bLogon;
extern BOOL32 g_bVmpStyleUp;

//////////////////////////////////////////////////////////////////////////
//vmpstyle
CVmpStyle::CVmpStyle()
{
	Clear();
}

CVmpStyle::CVmpStyle(EmUmsVmpStyle emStyle)
{
	Set(emStyle);
}

void CVmpStyle::Set(EmUmsVmpStyle emStyle)
{
	m_emStyle = emStyle;
	
	if (g_bVmpStyleUp)
	{
		switch (emStyle)
		{
		case em_ums_vmp_one:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_ONE;
				m_nChanNum = 1;
			}
			
			break;
		case em_ums_vmp_two_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_TWO_S;
				m_nChanNum = 2;
			}
			break;
			
		case em_ums_vmp_three_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_THREE_S;
				m_nChanNum = 3;
			}
			break;
			
		case em_ums_vmp_four_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_FOUR_S;
				m_nChanNum = 4;
			}
			break;
			
		case em_ums_vmp_five_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_FIVE_S;
				m_nChanNum = 5;
			}
			break;
			
		case em_ums_vmp_six_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SIX_S;
				m_nChanNum = 6;
			}
			break;
			
		case em_ums_vmp_seven_pic_380:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SEVEN_S;
				m_nChanNum = 7;
			}
			break;
			
		case em_ums_vmp_seven_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SEVEN_BIG_S;
				m_nChanNum = 7;
			}
			break;
			
		case em_ums_vmp_eight_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_EIGHT_S;
				m_nChanNum = 8;
			}
			break;
			
		case em_ums_vmp_nine_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_NINE_S;
				m_nChanNum = 9;
			}
			break;
			
		case em_ums_vmp_ten_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_TEN_S;
				m_nChanNum = 10;
			}
			break;
			
		default:
			{
				MdlError(Ums_Mdl_Mpu2TP, ("CVmpStyle::Set Invalid type. Type:%d.\n", emStyle));
				m_nHardStyle = MULPIC_TYPE_ERROR;
				m_nChanNum = 0;
			}
		}
	}
	else
	{
		switch (emStyle)
		{
		case em_ums_vmp_one:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_ONE;
				m_nChanNum = 1;
			}
			
			break;
		case em_ums_vmp_two_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_TWO;
				m_nChanNum = 2;
			}
			break;
			
		case em_ums_vmp_three_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_THREE;
				m_nChanNum = 3;
			}
			break;
			
		case em_ums_vmp_four_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_FOUR;
				m_nChanNum = 4;
			}
			break;
			
		case em_ums_vmp_five_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_FIVE;
				m_nChanNum = 5;
			}
			break;
			
		case em_ums_vmp_six_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SIX;
				m_nChanNum = 6;
			}
			break;
			
		case em_ums_vmp_seven_pic_380:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SEVEN;
				m_nChanNum = 7;
			}
			break;
			
		case em_ums_vmp_seven_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_SEVEN_BIG;
				m_nChanNum = 7;
			}
			break;
			
		case em_ums_vmp_eight_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_EIGHT;
				m_nChanNum = 8;
			}
			break;
			
		case em_ums_vmp_nine_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_NINE;
				m_nChanNum = 9;
			}
			break;
			
		case em_ums_vmp_ten_pic:
			{
				m_nHardStyle = MULPIC_TYPE_SIMPLE_TEN;
				m_nChanNum = 10;
			}
			break;
			
		default:
			{
				MdlError(Ums_Mdl_Mpu2TP, ("CVmpStyle::Set Invalid type. Type:%d.\n", emStyle));
				m_nHardStyle = MULPIC_TYPE_ERROR;
				m_nChanNum = 0;
			}
		}
	}
}

void CVmpStyle::Clear()
{
	m_emStyle = em_ums_vmp_invalid;
	m_nHardStyle = MULPIC_TYPE_ERROR;
	m_nChanNum = 0;
}
