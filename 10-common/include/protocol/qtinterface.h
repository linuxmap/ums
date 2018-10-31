#ifndef _QT_INTERFACE_IMPL_H_
#define _QT_INTERFACE_IMPL_H_

#include "qtstruct.h"

//��ʼ��QTLIB ��,HDU APU2 ��ʼ������ʹ��Ĭ��ֵ
BOOL32	QtLibInit(QTIN const TQtInitParam& tQtParam);
//����QTLIB��
void	QtLibQuit();


//���ü�����Ϣ 
//bEncryption	�򿪻��߹رռ��ܹ���
//emKeyFre		���ܵȼ�
void	QtSetEncryptionInfo(BOOL32 bEncryption, EmQtKeyFrequency emKeyFre, EmQtProtocol emProtocol);

//�����Ƿ�USB���� 
void	QtSetUsbEncrpty(BOOL32 bEncryptUsb, QTOUT u8 acKey[QT_KEY_LEN_16+1]);

//��ʼ��һ�κ���
EmQtRetReason	QtInitCall(QTIN const TQtCallParam& tCallParam, EmQtProtocol QTIN emQtProtocol, QTOUT QTCALLHANDLE& hCallHandle);
//����һ�κ���ʹ�õ���Դ
void			QtExitCall(QTIN QTCALLHANDLE hCallHandle);

u32 QtGetLocalQtID();

//��ȡ������Կ
EmQtRetReason QtGetKeyForMsgEnc(QTIN QTCALLHANDLE hCallHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]);
BOOL32 QtGetKeyForMsgDec(QTIN QTCALLHANDLE hCallHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);

//��ȡ������Կ
BOOL32 QtInitMediaKey(QTIN const TQtCallParam& tCallParam, EmQtProtocol QTIN emQtProtocol, QTOUT QTMediaKeyHandle& hMediaHandle);
BOOL32 QtGetKeyForMediaEnc(QTIN QTMediaKeyHandle hMediaHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]); 
BOOL32 QtGetKeyForMediaDec(QTIN QTMediaKeyHandle hMediaHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);
void   QtExitMediaKey(QTIN QTMediaKeyHandle hMediaHandle);

//BFCP 
//Ŀǰ�汾��֧��bfcp�����ں��У���˸ýӿڱ�������QtInitCall�ӿ�֮�����
EmQtRetReason QtInitBfcp(QTIN const TQtCallParam& tCallParam, QTOUT QTBFCPHANDLE& hBfcpHandle);
void QtExitBfcp(QTIN QTBFCPHANDLE hBfcpHandle);
EmQtRetReason QtGetKeyForBfcpEnc(QTIN QTBFCPHANDLE hBfcpHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]);
BOOL32 QtGetKeyForBfcpDec(QTIN QTBFCPHANDLE hBfcpHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);


//����������Կ�����յ�ƽ̨���͵�������Կ��Ϣ����øýӿ�
BOOL32 QtSetMediaKey(QTIN QTMediaKeyHandle& hMediaHandle, QTIN u8 acKey[QT_MAX_MEDIA_KEY+1], QTIN u32 dwKeyLen, QTIN EmQtKeyFrequency emQtKeyFrequency, QTIN u32 wQtFlag = 0,QTIN u16 wConverIndex = -1);

//���Խӿ�
void SetTest();

//UMSƽ̨ҵ��ʹ��
void QtSetConfID(QTIN s8* byAlias, QTIN u16 wConfID);
void QtSetConfInfo(QTIN u16 wConfID, BOOL32 bDownConf, BOOL32 bReset );
void QtQueryConfEncryptionResult(u16 wConfID, void* ptInfo, BOOL32 bRes, EmQtKeyFrequency emKeyFre);
void SetMediaKeyFailCB(QTIN QtCBMediaKeyFail cpFun);

#endif

