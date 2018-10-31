#ifndef __mcu_inst_def_h_
#define __mcu_inst_def_h_

#include "tpmsg.h"

enum EmServiceInstanceState
{
	STATE_WAITREG,      // �ȴ�ע��
	STATE_INIT,			// ��ʼ��
	STATE_NORMAL,		// ����
};

//������Ϣ��eqp
void SendMsgToEqp( u16 wEvent, u8 * const pbyMsg, u16 wLen, u16 wInsID, u32 dwNode );
void SendMsgToEqpSsn(u32 dwDstIID, u16 wEvent, u8 * const pbyMsg, u16 wLen);
void SendMsgToServer(u16 wEvent, u8* pbyMsg = NULL, u16 wLen = 0);
void SendMsgToCall(u16 wEvent, u8* pbyMsg = NULL, u16 wLen = 0);

#endif