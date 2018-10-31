#ifndef _TP_TEST_COMMON_H_
#define _TP_TEST_COMMON_H_

#define TEST_MODE_SERVER_APP_ID		400
#define TEST_MODE_CLIENT_APP_ID		401
#define TEST_LISTEN_PORT			31000

#define TEST_MODE_CLIEN_NAME_LEN	64

#define TEST_MODE_BUF_LEN_32		32
#define TEST_MODE_BUF_LEN_64		64
#define TEST_MODE_BUF_LEN_128		128

#define TEST_MODE_BUF_LEN_1024		1024
#define TEST_MODE_BUF_LEN_2048		2048


//reason from client
#define	BUF_ERROR_CLIENT_BUSY			"client is busy"
#define	BUF_ERROR_SERVER_UNREACHABLE	"server is unreachable"
#define	BUF_ERROR_SERVER_DISCONNECT		"server is disconnect"

//reason from server
#define	BUF_ERROR_CLIENT_FULL			"client is full"
#define	BUF_ERROR_CLIENT_UNKOWN			"client is unkown"
#define	BUF_ERROR_CLIENT_NOTLOGIN		"client is not login"
#define	BUF_ERROR_CLIENT_COMDATA		"comdata is error"
#define	BUF_ERROR_CLIENT_IODATA			"iodata is error"


#ifndef localmin
#define localmin(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef localmax
#define localmax(a,b) ((a)>(b)?(a):(b))
#endif

//以点分整数形式打印ip地址
#if !defined  u32IpForMat     
#define  u32IpForMat		"%u.%u.%u.%u"
#endif//u32IpForMat

#if !defined u32ToIp
#define u32ToIp(ip) ((u8 *)&(ip))[0], \
	((u8 *)&(ip))[1], \
	((u8 *)&(ip))[2], \
	((u8 *)&(ip))[3]
#endif//u32ToIp

//event定义
enum EmTestEvent
{
	em_event_Begin = 1000,
	em_event_Login_Req,			//client name用于验证
	em_event_Login_Req_OK,		//null
	em_event_Login_Req_Fail,	//s8[64] fail buf

	em_event_Login_Quit,

	em_event_test_SendComData_Req,
	em_event_test_SendComData_Req_OK,//null
	em_event_test_SendComData_Req_Fail,////s8[64] fail buf

	em_event_test_SendIOData_Req,
	em_event_test_SendIOData_Req_OK,//null
	em_event_test_SendIOData_Req_Fail,////s8[64] fail buf
};

#endif //_TP_TEST_COMMON_H_