#ifndef _TP_TEST_API_H_
#define _TP_TEST_API_H_

#include "kdvtype.h"

// add for win32 dll
#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPTESTDLL)

#ifdef _TPTESTAPI_EXPORTS
#define TPTEST_API extern "C"  __declspec(dllexport)
#else
#define TPTEST_API extern "C"  __declspec(dllimport)
#endif

#else  // 其他平台的，或者是静态链接

#define TPTEST_API extern "C"

#endif
// end for win32 dll

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#ifndef NULL
#define NULL	0
#endif

#define USERHANDLE						void* 
#define TPTESTHANDLE_MAX_NUM			5
#define TPTESTHANDLE					u16
#define INVAILD_TPTESTHANDLE			0
#define IS_VAILD_TPTESTHANDLE(handle)	((handle > 0) && (handle <= TPTESTHANDLE_MAX_NUM))

enum EmTpTestCBType
{
	em_CBType_Login_OK = 100, //null
	em_CBType_Login_Fail, //s8[64] fail buf

	em_CBType_TestComData_Ok = 200,//null
	em_CBType_TestComData_Fail, //s8[64] fail buf

	em_CBType_TestIOData_Ok = 300,//null
	em_CBType_TestIOData_Fail, //s8[64] fail buf

};

typedef BOOL32 (* TPTestCBDefine)(
	TPTESTHANDLE hTpHandle,
	USERHANDLE hUserHandle,
	EmTpTestCBType	emCBType,
	s8 *pszBuf, 
	u32 nSize);

namespace tptest{

	// 初始化接口，系统启用时调用，name根据需要test的server来填，填写不正确会导致无法成功登录
	TPTEST_API BOOL32	TpTestClientInit(s8* szName);

	// 登录接口，需要处理em_CBType_Login_OK和em_CBType_Login_Fail两个回调
	// 收到em_CBType_Login_Fail回调意味着登录失败或登录成功后断链，此接口返回的hHandle将失效
	TPTEST_API BOOL32	TpTestClientLogin(OUT TPTESTHANDLE& hHandle, IN u32 dwIp, IN TPTestCBDefine fCB, IN USERHANDLE hUserHandle = NULL);

	// 退出接口，无后续回调，hHandle将失效
	TPTEST_API BOOL32	TpTestClientLoginOut(IN TPTESTHANDLE hHandle);

	// 测试comdata，需要登录成功再调用
	// 需要处理em_CBType_TestComData_Ok和em_CBType_TestComData_Fail两个回调
	TPTEST_API BOOL32	TpTestClientComDataReq(IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen);

	// 测试iodata，需要登录成功再调用
	// 需要处理em_CBType_TestIOData_Ok和em_CBType_TestIOData_Fail两个回调
	TPTEST_API BOOL32	TpTestClientIODataReq(IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen);

}


#endif//_TP_TEST_API_H_