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

//cndevice模块枚举类型 --add by zhangapei
//显示器型号：Sharp 70LCD-LX640A、sharp 70LX550A，默认sharp 70LX550A
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

