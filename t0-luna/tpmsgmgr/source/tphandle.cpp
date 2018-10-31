#include "tphandle.h"

namespace UmsTpmsg {


void CTpHandler::Error(s8* szFormat, ... )
{
	if( !m_pcInstance )
		return;

    va_list pvList;
    va_start(pvList, szFormat);	

	char msg[MAX_MSG_LEN_TMP];
	if ( vsnprintf( msg, sizeof(msg), szFormat, pvList) > 0 ) 
		m_pcInstance->Error( "%s",msg );
	
    va_end(pvList);
	
}

void CTpHandler::LowHint(s8* szFormat, ... )
{
	if( !m_pcInstance )
		return;

    va_list pvList;
    va_start(pvList, szFormat);	

	char msg[MAX_MSG_LEN_TMP];
	if ( vsnprintf( msg, sizeof(msg), szFormat, pvList) > 0 ) 
		m_pcInstance->LowHint( "%s",msg );

    va_end(pvList);
	
}

void CTpHandler::Hint(s8* szFormat, ... )
{
	if( !m_pcInstance )
		return;

    va_list pvList;
    va_start(pvList, szFormat);	

	char msg[MAX_MSG_LEN_TMP];
	if ( vsnprintf( msg, sizeof(msg), szFormat, pvList) > 0 ) 
		m_pcInstance->Hint( "%s",msg );
	
    va_end(pvList);
	
}

} //namespace UmsTpmsg