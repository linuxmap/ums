#ifndef BFCPMODULE_H
#define BFCPMODULE_H

#include "bfcpdata.h"
//#include "sipcapset.h"

#ifdef WIN32
#define BFCPCALLBACK __cdecl
#else
#define BFCPCALLBACK
#endif

class CBfcpBinary;

typedef void (BFCPCALLBACK* CBOpenDualChannel)( void *ptSipCap, BOOL bFlag );

typedef void (BFCPCALLBACK* CBCloseDualChannel)( void *ptSipCap );

typedef BOOL (BFCPCALLBACK* CBDualCapsetChanged)( void *ptSipCap );

typedef struct tagBfcpCBFunction
{
	CBOpenDualChannel      m_cbOpenDualChannel;
	CBCloseDualChannel     m_cbCloseDualChannel;
	CBDualCapsetChanged    m_cbDualCapsetChanged;
	
	void Clear()
	{
		m_cbOpenDualChannel = NULL;
		m_cbCloseDualChannel = NULL;
		m_cbCloseDualChannel = NULL;
	}

	tagBfcpCBFunction()
	{
		Clear();
	}
}TBfcpCBFunction;

class CBfcpModule
{
public:
	CBfcpModule( void *pcCapset, TBfcpCBFunction *ptBfcpCB, u16 wFloorId, u32 dwConferenceId, u16 wUserId, TRequestAddress& tRequestAddress );
	~CBfcpModule();

	//�ͻ��ˣ�����floor����Hello��FloorRequest��FloorRelease��
	BOOL SendFloorRequireMessage( EmBfcpPrimitive emPrimitive );
	//�������ˣ�����floor״̬��FloorStatus����bFlagΪTRUE����floorΪGranted״̬������floorΪReleased״̬
	BOOL SendFloorStatusMessage( BOOL bFlag = TRUE );
	//�������ˣ�����FloorRequestStatusӦ��bFlagΪTRUE����floorΪGranted״̬������floorΪDenied״̬
	BOOL SendFloorRequestStatusMessage( BOOL bFlag = TRUE );
	//�������ˣ����BFCP��Ϣ
	s32 HandleBfcpMessage( SOCKHANDLE tSocket );
	//��BFCP��Ϣ�Ļ�Ӧ
	BOOL BfcpResponse( CBfcpPacketData *pcPacketData );
	//����BFCP��ز���
	void UpdateBfcpModuleInfo( u16 wFloorId, u32 dwConferenceId, u16 wUserId );
	
private:
	BOOL SendBfcpFloorRequest( TFloorRequestInfo& tFloorRequestInfo );
	BOOL SendBfcpFloorRelease();
	BOOL SendBfcpFloorRequestQuery();
	BOOL SendBfcpFloorRequestStatus( TBfcpCommonHeader& tHeader, TGroupedAttribute& tFloorRequestInfo );
	BOOL SendBfcpUserQuery();
	BOOL SendBfcpUserStatus();
	BOOL SendBfcpFloorQuery();
	BOOL SendBfcpFloorStatus( TGroupedAttribute& tFloorRequestInfo );
	BOOL SendBfcpChairAction();
	BOOL SendBfcpChairActionAck();
	BOOL SendBfcpHello();
	BOOL SendBfcpHelloAck();
	BOOL SendBfcpError( u16 wTransactionId, EmBfcpErrorCode emErrorCode, s8 *pchErrorInfo, EmBfcpPrimitive emPrimitive = emBfcpPrimitiveBegin );
	u16 GetIdleIndex( s8 *pchIdName );
	void ConstructFloorRequestInfo( EmBfcpPrimitive emPrimitive, TGroupedAttribute& tFloorRequestInfo, BOOL bFlag = TRUE );

	u16 m_wFloorId;
	u32 m_dwConferenceId;
	u16 m_wTransactionId;
	u16 m_wUserId;
	u16 m_wFloorRequestId;
	u16 m_wOngoingFloorRequestNum;
	BOOL m_bIsParticipant;
	TBfcpId m_atTransactionId[MAX_TRANSACTION_ID];
	TBfcpId m_atFloorRequestId[MAX_FLOOR_REQUEST_ID];
	EmBfcpRequestStatus m_emRequestStatus;

	void *m_pcCapset;
	TBfcpCBFunction m_tBfcpCbFun;
	CBfcpBinary *m_pcBfcpBinary;
};

void CheckBfcpMessageServer( CBfcpModule *pcModuleServer );

// Log Debug Interface
API void bfcphelp();
API void bfcplogon( s32 nLevel );
API void bfcplogoff();
API void bfcpversion();
API void RegBfcpFunLinux();
void BfcpLog( const s8 *pFormat, va_list vaList );
void BfcpPrintf( const s8 *pFormat, ... );

#endif
