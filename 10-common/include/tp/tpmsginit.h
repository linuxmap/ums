#ifndef _h_tpmsginit_h__
#define _h_tpmsginit_h__


//event初始化函数， CMS通用
namespace UmsTpmsg{

void InitTpEvent();


//UMS专属初始化函数
void InitUmsEvent();

} //namespace UmsTpmsg

//CNS专属初始化函数

void InitCnsEvent();

#endif // _h_tpmsginit_h__
