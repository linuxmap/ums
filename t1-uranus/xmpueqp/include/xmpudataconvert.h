#ifndef _ums_data_convert_h_
#define _ums_data_convert_h_

#include "tpcommonstruct.h"
#include "mediastruct.h"

void ConvertVidForamtFromUmsToXmpu(const TUmsVidFormat tForamt, MediaAPI::TMediaVidStreamCap& tStreamCap);
 u8 ConvertVmpStyleFromUmsToXmpu(const  EMVmpStyle emStyle );
 u8 ConvertMpu2StyleFromUmsToXmpu(const EmUmsVmpStyle emStyle);
 u8 ConvertEncKeyModeFromUmsToXmpu(const EmTPEncryptType emType);







#endif // _ums_data_convert_h_