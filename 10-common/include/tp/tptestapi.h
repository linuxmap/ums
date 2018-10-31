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

#else  // ����ƽ̨�ģ������Ǿ�̬����

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

	// ��ʼ���ӿڣ�ϵͳ����ʱ���ã�name������Ҫtest��server�����д����ȷ�ᵼ���޷��ɹ���¼
	TPTEST_API BOOL32	TpTestClientInit(s8* szName);

	// ��¼�ӿڣ���Ҫ����em_CBType_Login_OK��em_CBType_Login_Fail�����ص�
	// �յ�em_CBType_Login_Fail�ص���ζ�ŵ�¼ʧ�ܻ��¼�ɹ���������˽ӿڷ��ص�hHandle��ʧЧ
	TPTEST_API BOOL32	TpTestClientLogin(OUT TPTESTHANDLE& hHandle, IN u32 dwIp, IN TPTestCBDefine fCB, IN USERHANDLE hUserHandle = NULL);

	// �˳��ӿڣ��޺����ص���hHandle��ʧЧ
	TPTEST_API BOOL32	TpTestClientLoginOut(IN TPTESTHANDLE hHandle);

	// ����comdata����Ҫ��¼�ɹ��ٵ���
	// ��Ҫ����em_CBType_TestComData_Ok��em_CBType_TestComData_Fail�����ص�
	TPTEST_API BOOL32	TpTestClientComDataReq(IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen);

	// ����iodata����Ҫ��¼�ɹ��ٵ���
	// ��Ҫ����em_CBType_TestIOData_Ok��em_CBType_TestIOData_Fail�����ص�
	TPTEST_API BOOL32	TpTestClientIODataReq(IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen);

}


#endif//_TP_TEST_API_H_