#ifndef _LOCAL_XML_TYPE_H_
#define _LOCAL_XML_TYPE_H_

#include "tpcommonxmltype.h"

const char XmlLocalTypeVersion[] = "2015-3-10 19:34:43";

//Local Data struct type begin
enum EmXDataLocalType
{
	emx_EmTpMcuSelView = _placeholder_emxEnumTptypeEnd, //Localö���������ݿ�ʼ,����Tpö�ٽ���
	emx_EmTpColor,
	emx_EmTpSize,
	emx_EmTpLogoStyle,
	emx_EmTpStyle,
	emx_emTpTransparency,
	emx_EmTVModle,
	emx_EmPanCamBright,
	emx_TTPMCUSelViewReq = _placeholder_emxTpStructTypeend, //Local���ݽṹ�������ݿ�ʼ,����Tp�ṹ�����
	emx_TTPShowLogo,
	emx_TTPLogoInfo,
	emx_TTPShowBanner,
	emx_TTPBannerInfo,
	emx_TTPVideoSourceName,
	emx_TTPVideoInfoTool,
	emx_TCentreTVCfg,
	emx_TCentreCurInfo,
	emx_TPanCamName,
	emx_TPanCamGroupName,
	emx_TPanCamInfo,
	emx_TTPVAdapterInfo,
_placeholder_emxDataTypeEnd = emxDataTypeEnd, //���Ͷ������
};
//Local Data struct type end

namespace UmsTpmsg {
#define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)
#define TpEnumString(type, index) GetTpEnumString(emx_##type, index)

s8* GetTpEnumString(u16 wType, u16 wIndex);
TXDATAINFO** CombineEnumDateInfo(void);
TXDATAINFO** CombineStructDateInfo(void);
void CombineEnumXDescripTbl(void);

} //namespace UmsTpmsg

#endif //_LOCAL_XML_TYPE_H_
