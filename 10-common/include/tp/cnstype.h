#ifndef _h_cnstype_h__
#define _h_cnstype_h__
#include "osp.h"

enum EmTpMcuSelView
{
	emTpMcuSelView_Idle,
		emTpMcuSelView_Req,
		emTpMcuSelView_Success
};

enum EmTpColor
{
	emRed,
	emBlue,
	emYellow,
	emBlack,
	emGreen
};

enum EmTpSize
{
	emBig,
	emMid,
	emlittle
};

enum EmTpLogoStyle
{
	emLeftUp,
	emLeftDown,
	emMidUp,
	emMidDown,
	emRightUp,
	emRightDown
};

enum EmTpStyle
{
	emStyleOne,
	emStyleTwo,
	emStyleThree
};

enum emTpTransparency
{
	emTransparent,
	emTranslucent,
	Opaque
};

//cndeviceģ��ö������ --add by zhangapei
//��ʾ���ͺţ�Sharp 70LCD-LX640A��sharp 70LX550A��Ĭ��sharp 70LX550A
enum EmTVModle
{
	emSharp70LCD_LX640A,
	emSharp70LX550A,
};

enum EmPanCamBright
{
	emBrightUp = 0x02,
	emBrightDown,
};
//add end

#endif // _h_cnstype_h__

