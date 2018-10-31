#include "xmpudataconvert.h"
#include "umsapi.h"
#include "mediaclientapi.h"
#include "umsconfigex.h"

void ConvertVidForamtFromUmsToXmpu( const TUmsVidFormat tForamt, MediaAPI::TMediaVidStreamCap& tStreamCap )
{
	u16 wVidW = 0;
	u16 wVidH = 0;
	tStreamCap.SetVidType(CTpTypeAdpt::GetVidPayloadValue(tForamt.m_emFormat));
	tStreamCap.SetFrameRate((u8)tForamt.m_wFrameRate);
	tStreamCap.SetBitRate(tForamt.m_wBitrate);
	if ( tForamt.m_emQualityLvl == emTPH264HP )
	{
		tStreamCap.SetProfileType(1);
	}
	else if( tForamt.m_emQualityLvl == emTPH264BP )
	{
		tStreamCap.SetProfileType(0);
	}
	CTpTypeAdpt::GetWHByVidResolution(tForamt.m_emRes, wVidW, wVidH);
	tStreamCap.SetHeight(wVidH);
	tStreamCap.SetWidth(wVidW);
	tStreamCap.SetRealPayload(MEDIA_TYPE_H264);
	tStreamCap.SetActivPayload(MEDIA_TYPE_H264);

	MdlHint(Ums_Mdl_Xmpu, ("  ConvertVidForamtFromUmsToXmpu VidType:%d, FrameRate:%d, BitRate:%d, Protype:%d, Width:%d, Heigh:%d \n", 
		tStreamCap.GetVidType(), tStreamCap.GetFrameRate(), tStreamCap.GetBitRate(), tStreamCap.GetProfileType(), 
		tStreamCap.GetWidth(), tStreamCap.GetHeight()));
}

u8 ConvertVmpStyleFromUmsToXmpu( const  EMVmpStyle emStyle)
{
	u8 byStyle = 0;
	switch(emStyle)
	{
	case tp_VmpStyle_DYNAMIC:
		byStyle = MEDIAVMP_STYLE_DYNAMIC;
		break;
	case tp_VmpStyle_ONE:
		byStyle = MEDIAVMP_STYLE_ONE;
		break;
	case tp_VmpStyle_VTWO:
		byStyle = MEDIAVMP_STYLE_VTWO;
		break;
	case tp_VmpStyle_HTWO:
		byStyle = MEDIAVMP_STYLE_HTWO;
		break;
	case tp_VmpStyle_THREE:
	case tp_VmpStyle_leftBig:
	case tp_VmpStyle_MidBig:
	case tp_VmpStyle_RightBig:
		byStyle = MEDIAVMP_STYLE_THREE_1UP2BOTTOM;
		break;
	case tp_VmpStyle_FOUR:
	case tp_VmpStyle_SPECFOUR:
	case tp_VmpStyle_FOUR_3BOTTOMMIDDLE:
		byStyle = MEDIAVMP_STYLE_FOUR;
		break;
	case tp_VmpStyle_SIX:
	case tp_VmpStyle_SIX_L2UP_S4DOWN:
	case tp_VmpStyle_SIX_DIVIDE:
		byStyle = MEDIAVMP_STYLE_SIX;
		break;
	case tp_VmpStyle_EIGHT:
		byStyle = MEDIAVMP_STYLE_EIGHT;
		break;
	case tp_VmpStyle_NINE:
		byStyle = MEDIAVMP_STYLE_NINE;
		break;
	case tp_VmpStyle_TEN:
	case tp_VmpStyle_TEN_H:
	case tp_VmpStyle_TEN_M:
		byStyle = MEDIAVMP_STYLE_TEN;
		break;
	case tp_VmpStyle_THIRTEEN:
	case tp_VmpStyle_THIRTEEN_M:
		byStyle = MEDIAVMP_STYLE_THIRTEEN;
		break;
	case tp_VmpStyle_SIXTEEN:
		byStyle = MEDIAVMP_STYLE_SIXTEEN;
		break;
	case tp_VmpStyle_SEVEN:
		byStyle = MEDIAVMP_STYLE_SEVEN;
		break;
	case tp_VmpStyle_TWENTY:
		byStyle = MEDIAVMP_STYLE_TWENTY;
		break;
	case tp_VmpStyle_FOURTEEN:
		byStyle = MEDIAVMP_STYLE_FOURTEEN;
		break;
	case tp_VmpStyle_FIFTEEN:
		byStyle = MEDIAVMP_STYLE_FIFTEEN;
		break;
	case tp_VmpStyle_3VERTICAL:
		byStyle = MEDIAVMP_STYLE_THREE;
		break;
	case tp_VmpStyle_TWENTYFIVE:
		byStyle = MEDIAVMP_STYLE_TWENTYFIVE;
		break;
	default:
		byStyle = MEDIAVMP_STYLE_DYNAMIC;
		break;
	}
	return byStyle;
}

u8 ConvertMpu2StyleFromUmsToXmpu( const EmUmsVmpStyle emStyle )
{
	u8 byStyle = 0;
	if (CUmsConfigEx::GetInstance()->GetVmptpStyleUp())
	{
		switch(emStyle)
		{
		case em_ums_vmp_invalid:
			byStyle = MEDIAVMP_STYLE_DYNAMIC;
			break;
		case em_ums_vmp_one:
			byStyle = MEDIAVMP_STYLE_SIMPLE_ONE;
			break;
		case em_ums_vmp_two_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_TWO_UP;
			break;
		case em_ums_vmp_three_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_THREE_UP;
			break;
		case em_ums_vmp_four_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_FOUR_UP;
			break;
		case em_ums_vmp_five_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_FIVE_UP;
			break;
		case em_ums_vmp_six_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SIX_UP;
			break;
		case em_ums_vmp_seven_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SEVEN_UP;
			break;
		case em_ums_vmp_seven_pic_380:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SEVEN_BIG_UP;
			break;
		case em_ums_vmp_eight_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_EIGHT_UP;
			break;
		case em_ums_vmp_nine_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_NINE_UP;
			break;
		case em_ums_vmp_ten_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_TEN_UP;
			break;
		default:
			byStyle = MEDIAVMP_STYLE_DYNAMIC;
			break;
		}
	}
	else
	{
		switch(emStyle)
		{
		case em_ums_vmp_invalid:
			byStyle = MEDIAVMP_STYLE_DYNAMIC;
			break;
		case em_ums_vmp_one:
			byStyle = MEDIAVMP_STYLE_SIMPLE_ONE;
			break;
		case em_ums_vmp_two_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_TWO;
			break;
		case em_ums_vmp_three_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_THREE;
			break;
		case em_ums_vmp_four_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_FOUR;
			break;
		case em_ums_vmp_five_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_FIVE;
			break;
		case em_ums_vmp_six_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SIX;
			break;
		case em_ums_vmp_seven_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SEVEN;
			break;
		case em_ums_vmp_seven_pic_380:
			byStyle = MEDIAVMP_STYLE_SIMPLE_SEVEN_BIG;
			break;
		case em_ums_vmp_eight_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_EIGHT;
			break;
		case em_ums_vmp_nine_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_NINE;
			break;
		case em_ums_vmp_ten_pic:
			byStyle = MEDIAVMP_STYLE_SIMPLE_TEN;
			break;
		default:
			byStyle = MEDIAVMP_STYLE_DYNAMIC;
			break;
		}
	}
	

	return byStyle;
}

u8 ConvertEncKeyModeFromUmsToXmpu( const EmTPEncryptType emType )
{
	if (emType == emTPEncryptTypeAES)
	{
		return ENCRYPT_AES;
	}
	else if (emType == emTPEncryptTypeDES)
	{
		return ENCRYPT_DEC;
	}
	else
	{
		return ENCRYPT_NONE;
	}
}
