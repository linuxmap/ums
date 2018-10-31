/**                                                                            
*** Copyright (c) 2002-2003 Keda Communication Co.LTD.
���ע��
**/     

#ifndef _CCI_H___
#define _CCI_H___



#ifdef __cplusplus
extern "C" {
#endif
/*
*	Defines macro for CCI Function return.
*/
//#include "algorithmtype.h"
	
#define	CCI_OPEN_FAIL 			-1		//CCI��ʧ��
#define CCI_OPEN_SUCCESS		 0		// CCI�򿪳ɹ�

#define	CCI_CLOSE_SUCCESS	   	 0		//CCI�رճɹ�
#define	CCI_CLOSE_FAIL			-1		//CCI�ر�ʧ��

#define CCI_SND_LEN_ERR 		12		//���ͳ��ȴ�
#define	CCI_BUF_DAMAGE			11		//CCI���л��屻�ƻ�
#define	CCI_SND_FAIL			10		//CCI����ʧ��
#define	CCI_SEND_SUCCESS		9		// CCI���ͳɹ�
#define CCI_HOST_UNOPEN			8		//HOST��û�д�
#define	CCI_QUE_OVERFLOW 		7		//��������



#define CCI_REV_LEN_ERR 		6		//���ճ��ȴ���
#define CCI_USERBUF_NOT_ENOUGH	5		//buf���Ȳ���
#define CCI_PARAM_ERR			4		//��������
#define	CCI_REV_WRONG_TYPE		3		//�յ���������
#define	CCI_REV_SUCCESS			2		//������ȷ
#define CCI_REV_NO_MSG 			1		//û����Ϣ

//
//msg type define
//
#define USER_MSG_TYPE			0		//�û��������Ϣ
#define	CYCLE_TEST_TYPE			1		//�Ի�������Ϣ
#define	MAP_CYCLE_TEST			2		//MAP�Ի�������Ϣ
#define	HOST_PRINT_TYPE			3		//HOST��ӡ��Ϣ
#define MAP_SEND_TYPE			4		//MAP������Ϣ
#define	MAP_PRINT_TYPE			5		//MAP��ӡ��Ϣ
#define LIGHT_MAP				6		//�����Ϣ


//#define MAX_DN_QUEUENUM		200			//������ж�������

/* 
* Defines API function for CCI-MAP
*/
SCODE CciMsgOpen(l32 *piQueNum);

SCODE CciMsgClose();

SCODE CciMsgSnd(void* pvMsg, l32 iMsgLen);

SCODE CciSndData(void* pvMsg,l32 iMsgLen,l32 iMsgType);

SCODE CciMsgRev(void* pvMsgStoreBuf,l32 iMsgBufLen,l32 *piMsgLen,l32 iQueNo);

void MsgsInQue(l32 iQueNo, l32 *piMsgsInQue);

u32 HeartBeatAdd();

void CciPrintf(const char *fmt,... );

void CciGetMaxMsgLen(l32 iQueueNo,l32 *piMaxMsgLen);

SCODE CciConcateSndData(void* pvFirstMsg,l32 iFirstMsgLen, void* pvSecondMsg, l32 iSecondMsgLen, l32 iMsgType);

void  CciWriteErrNo(l32 nErrIdx, l32  nErrNo); // nErrIdx��0��15

void  ErrNoWriteEnable(BOOL bEnable);	//�����Ƿ�׼��cci��¼������, ��������ã�׼��д

SCODE CciWriteDownQue(l32 iQueNo, void *pbyFirstMsg, l32 iFirstMsgLen, void *pbySecondMsg, l32 iSecondMsgLen);	//ģ������д���ж���

#ifdef __cplusplus
}
#endif
#endif /* _CCI_H___ */
