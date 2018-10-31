/*=======================================================================
ģ����      :
�ļ���      : readlicense.h
����ļ�    :
�ļ�ʵ�ֹ��� : ��ȡlicense�ļ�������
����        : ���ƶ�
�汾        : KCMV1.0  Copyright(C) 2003-2008 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/01/09  KCM1.0      ���ƶ�      ����
=======================================================================*/

#include "readlicense.h"
#include "usbkeyconst.h"
#include "kdvsys.h"
#include "kdvencrypt.h"

#ifdef _USER_HKAPI
#include "hkapi.h"
#endif

#define MAX_KEY_VALUE_NUM						100							// �ɶ�ȡ��Key-Value�������

u16 g_wLastErrorCode = 0;													// ���һ�ε��ò����Ĵ�����

TKeyValue g_tKeyValue[MAX_KEY_VALUE_NUM];
u16 g_wKeyValueNum = 0;

s8 g_achContentBuf[LEN_KEYFILE_CONT] = {0};
u16 g_wBufLen = 0;

s8 *strtokEx(s8 *pchBuf, const s8 *pchSeps)
{
	return strtok(pchBuf, pchSeps);
}

// ���Ӵ��л�ȡKey��Value
u16 GetKeyValue(s8 *pchBuf, s8 *pchKey, s32 &nKeyLen, s8 *pchValue, s32 &nValueLen)
{
	if(NULL == pchBuf || NULL == pchKey || NULL == pchValue) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	u16 wBufLen = strlen(pchBuf);
	if(wBufLen < 3) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	s8 *pchPos = pchBuf;
	s8 *pchToken = NULL;
	s8 achSep[5] = {0};
	memcpy( achSep, (s8*)KEY_VALUE_CONNECTOR,
            strlen(KEY_VALUE_CONNECTOR) + 1 );	// Key��Value�ķָ���

	pchToken = strtok(pchPos, achSep);
	if(NULL == pchToken) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}

	u16 wLenKey = strlen(pchToken);
	if(nKeyLen < wLenKey) 
	{
		return ERR_LICENSE_LONG_STRING;
	}
	memcpy(pchKey, pchToken, wLenKey);
	pchKey[wLenKey] = '\0';

	if(wBufLen - wLenKey - 1 < 1) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}

	pchPos += wLenKey + 1;
	u16 wLenValue = strlen(pchPos);
	if(nValueLen < wLenValue) 
	{
		return ERR_LICENSE_LONG_STRING;
	}
	memcpy(pchValue, pchPos, wLenValue);
	pchValue[wLenValue] = '\0';

	return SUCCESS_LICENSE;
}

#ifdef _USER_HKAPI

void FreeUSBKey(HKHANDLE hDevice )
{
#ifdef WIN32
	if (NULL != hDevice)
	{
		HK_EndTransaction(hDevice);
	}
	if (NULL != hDevice)
	{
		HK_DisconnectDev(hDevice);
	}
#elif
    if ( hDevice != NULL )
    {
        close_haikey( hDevice );
    }
#endif

	return;
}


// д�ļ���USB��
u16 WriteLicenseFileToUSB(s8 *pchContent, u16 wLen)
{
	s8 achLicenseKey[40] = {0};
	s32 nLicenseKey = 40;
	u16 wCheck = GetValue((s8*)KEY_LICENSE_KEY, achLicenseKey, nLicenseKey);
	if(SUCCESS_LICENSE != wCheck) 
	{
		return ERR_LICENSE_INVALID_USBKEY;
	}
	HKHANDLE hCard = NULL;
	u32 dwWriteDataLen = MAXLEN_USBKEY_NAME;
	u32 dwRet = 0;
	u32 dwIndex = 0;
	u32 dwDeviceSlot = 0;
	u32 dwDeviceState = 0;
	u32 dwReaderNameLen = 0;
	u32 dwReaderNum     = 0;
	s8  achDeviceName[MAXLEN_USBKEY_NAME];

	memset(achDeviceName, 0x00, sizeof(achDeviceName));
#ifdef WIN32
	dwRet = HK_ListReaders(NULL, &dwReaderNameLen, &dwReaderNum);			// Ĭ��ö�ٵ�һ����Ч��USBKEY�豸
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	if(0 == dwReaderNum || dwReaderNameLen > MAXLEN_USBKEY_NAME)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	dwRet = HK_ListReaders(achDeviceName, &dwReaderNameLen, &dwReaderNum);
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	while(0x00 != achDeviceName[dwIndex])
	{
		dwRet = HK_GetDevState(&achDeviceName[dwIndex], &dwDeviceState);
		if (0 != dwRet)
		{
			return ERR_LICENSE_NO_USB_KEY;
		}
		if (HGS_STATE_PRESENT == dwDeviceState)
		{
			dwDeviceSlot = dwIndex;
			break;
		}
		dwIndex = dwIndex + strlen(&achDeviceName[dwIndex]) + 1;
	}
	if(0x00 == achDeviceName[dwDeviceSlot])
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	dwRet = HK_ConnectDev(&achDeviceName[dwDeviceSlot], &hCard);			// �����豸
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
#elif
    int nSlot = 0;
    dwRet = open_haikey( nSlot, &hCard );
#endif

	s8 achDevSerial[40] = {0};
	dwRet = HK_GetSerialNum(hCard, (u8*)achDevSerial);						// �Ƚ�Licnese�ļ����豸�������
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_GET_FAIL;
	}
	if(strcmp(achDevSerial, achLicenseKey) != 0)
	{
//		return ERR_LICENSE_INVALID_USBKEY;
	}

#ifdef WIN32
	dwRet = HK_BeginTransaction(hCard);										// ��ʼ��ռ�豸
	if (0 != dwRet)
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_GET_FAIL;
	}
#endif

	dwRet = HK_Erase(hCard, "1111");
	if(0 != dwRet) 
	{
		dwRet = HK_Format(hCard, "test", "1111", "1111", HK_ANYONE_ACCESS, HK_ANYONE_ACCESS);
		if(0 != dwRet) 
		{
			FreeUSBKey( hCard );
			return ERR_LICENSE_USB_DELETE_FILE_FAIL;
		}
		dwRet = HK_Erase(hCard, "1111");
		if(0 != dwRet) 
		{
			FreeUSBKey( hCard );
			return ERR_LICENSE_USB_DELETE_FILE_FAIL;
		}
	}
	
	dwRet = HK_Format(hCard, "test", "1111", "1111", HK_ANYONE_ACCESS, HK_ANYONE_ACCESS);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_FORMAT_FAIL;
	}

	dwRet = HK_VerifyOfficerPIN(hCard, "1111");
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_VERY_PASSWORD;
	}
	
	dwRet = HK_BacktoMDir(hCard);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_VERY_PASSWORD;
	}

	HK_FILEINFO tFileInfo;
	tFileInfo.ulID = 0xEF01;
	tFileInfo.ucFileType = HK_FILETYPE_BINARY;
	tFileInfo.ucReadAccess = HK_SUPER_PIN_ACCESS;
	tFileInfo.ucWriteAccess = HK_SUPER_PIN_ACCESS;
	tFileInfo.ulFileSize = wLen;
	dwRet = HK_CreateFile(hCard, &tFileInfo);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_CREATE_FILE_FAIL;
	}
	
	dwRet = HK_OpenFile(hCard, 0xEF01);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_OPEN_FILE_FAIL;
	}
																			// д�ļ�
	dwRet = HK_WriteFile(hCard, 0x0000, (u8*)pchContent, wLen, &dwWriteDataLen);
	if (0 != dwRet)
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_WRITEKEY_FAILED;
	}

#ifdef WIN32
	HK_EndTransaction(hCard);												// ������ռ�豸״̬
	
	HK_DisconnectDev(hCard);												// �Ͽ��豸
#elif
    dwRet = close_haikey( hCard );
#endif

	hCard = NULL;
	
	return SUCCESS_LICENSE;
}

u16 ReadLicenseFileFromUSB(s8 *pchContent, u16 &wLen)
{
	HKHANDLE hCard = NULL;
	u32 dwWriteDataLen = MAXLEN_USBKEY_NAME;
	u32 dwRet = 0;
	u32 dwIndex = 0;
	u32 dwDeviceSlot = 0;
	u32 dwDeviceState = 0;
	u32 dwReaderNameLen = 0;
	u32 dwReaderNum     = 0;
	s8  achDeviceName[MAXLEN_USBKEY_NAME] = {0};

	memset(achDeviceName, 0x00, sizeof(achDeviceName));
#ifdef WIN32
	dwRet = HK_ListReaders(NULL, &dwReaderNameLen, &dwReaderNum);			// Ĭ��ö�ٵ�һ����Ч��USBKEY�豸
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	if(0 == dwReaderNum || dwReaderNameLen > MAXLEN_USBKEY_NAME)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	dwRet = HK_ListReaders(achDeviceName, &dwReaderNameLen, &dwReaderNum);
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	while(0x00 != achDeviceName[dwIndex])
	{
		dwRet = HK_GetDevState(&achDeviceName[dwIndex], &dwDeviceState);
		if (0 != dwRet)
		{
			return ERR_LICENSE_NO_USB_KEY;
		}
		if (HGS_STATE_PRESENT == dwDeviceState)
		{
			dwDeviceSlot = dwIndex;
			break;
		}
		dwIndex = dwIndex + strlen(&achDeviceName[dwIndex]) + 1;
	}
	if(0x00 == achDeviceName[dwDeviceSlot])
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
	dwRet = HK_ConnectDev(&achDeviceName[dwDeviceSlot], &hCard);			// �����豸
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
#elif
    int nSlot = 0;
    dwRet = open_haikey( nSlot, &hCard );
    if ( dwRet != 0 )
    {
        return ERR_LICENSE_NO_USB_KEY;
    }
#endif

	dwRet = HK_VerifyOfficerPIN(hCard, "1111");
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_VERY_PASSWORD;
	}

	dwRet = HK_BacktoMDir(hCard);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_VERY_PASSWORD;
	}

#ifdef WIN32
	dwRet = HK_BeginTransaction(hCard);										// ��ʼ��ռ�豸
	if (0 != dwRet)
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_GET_FAIL;
	}
#endif

	dwRet = HK_OpenFile(hCard, 0xEF01);
	if(0 != dwRet) 
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_USB_OPEN_FILE_FAIL;
	}

    // ��ȡ�ļ�
	if(wLen < MAXLEN_USBKEY_NAME) 
	{
		return ERR_LICENSE_READKEY_FAILED;
	}
	s8 achbb[MAXLEN_USBKEY_NAME + 1] = {0};
	u32 dwbbLen = MAXLEN_USBKEY_NAME;
	dwRet = HK_ReadFile(hCard, 0x0000, (u8*)achbb, dwbbLen, &dwWriteDataLen);
	if (0 != dwRet)
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_READKEY_FAILED;
	}

	memcpy(pchContent, achbb, dwWriteDataLen);
	wLen = (u16)dwWriteDataLen;

#ifdef WIN32
	HK_EndTransaction(hCard);												// ������ռ�豸״̬
	
	HK_DisconnectDev(hCard);												// �Ͽ��豸
#elif
    dwRet = close_haikey( hCard );
#endif

	hCard = NULL;

	return SUCCESS_LICENSE;
}

#endif

// ����
void GenEncodeData(s8 *pOutBuf, u16 wInBufLen, s8 *pInBuf, BOOL32 bDirect)
{
    s8 achIV[MAX_IV_SIZE] = {0};
	
    s8 achKey[32] = {0};
    memset( achKey, 0, sizeof (achKey) );
	strncpy( achKey, KEDA_AES_KEY, strlen(KEDA_AES_KEY) );// ����keyΪ16�ı���
    u16 wKeyLen = strlen(achKey);

    s32 nRet = -1;
	if( bDirect ) // eccrypt 
	{
		nRet = KdvAES( achKey, wKeyLen, MODE_CBC, DIR_ENCRYPT, achIV,
			(u8*)pInBuf, wInBufLen, (u8*)pOutBuf );
	}
	else  // decrypt
	{
		nRet = KdvAES( achKey, wKeyLen, MODE_CBC, DIR_DECRYPT, achIV,
			(u8*)pInBuf, wInBufLen, (u8*)pOutBuf );
	}

	return;
}

u16 ReadLicenseFile(s8 *pchPath)
{
	if(NULL == pchPath) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	u16 wRet = SUCCESS_LICENSE;
	s8 achContentBuf[512] = {0};
	u16 wBufLen = 512;

	s8 achKeyValueContent[512] = {0};
	u16 wBufKeyValueLen = 512;

#ifdef _USER_HKAPI
	if(strcmp(pchPath, USB_PATH) == 0) 
	{
		wRet = ReadLicenseFileFromUSB(achContentBuf, wBufLen);				// ��USB�豸��ȡ�ļ�
		if(SUCCESS_LICENSE != wRet) 
		{
			return wRet;
		}
	}
	else
	{
#endif
		FILE *pHandler = fopen( (LPCSTR)pchPath, "rb" );
		if(NULL == pHandler) 
		{
			return ERR_LICENSE_OPENFILE_FAILED;
		}
		fread(achContentBuf, sizeof(achContentBuf), 1, pHandler);
		fclose(pHandler);
#ifdef _USER_HKAPI
	}
#endif
	u16 wTotalLen = strlen(achContentBuf);

	u16 wKeyValueLen = sizeof(achContentBuf);
	GenEncodeData(achKeyValueContent, wKeyValueLen, achContentBuf, FALSE);	// ����

	s32 i = 0;
	s32 nCharPos = 0;
	s8 *pchToken2 = "NULL";
	s8 *pBuf = achKeyValueContent;
	s8 achKey[1024] = {0};
	s8 achValue[1024] = {0};
	s32 nKeyBuflen = 1024;
	s32 nValueBuflen = 1024;
	u16 wInfoLen = 0;

	nCharPos = strcspn(pBuf, "&");
	pchToken2 = strtok(pBuf, "&");
	if(NULL == pchToken2) 
	{
		return ERR_LICENSE_FORMAT_FAILED;
	}
	wRet = GetKeyValue(pchToken2, achKey, nKeyBuflen,						// ��ȡKey-Value����Ϣ
						achValue, nValueBuflen);
	if(SUCCESS_LICENSE != wRet) 
	{
		return wRet;
	}
	if(strcmp(achKey, ENCRPT_LENGTH) == 0) 
	{
		wInfoLen = atoi(achValue);
	}
	else
	{
		return ERR_LICENSE_FORMAT_FAILED;
	}
	pBuf += nCharPos + 1;
	s8 achInfoBuf[1024] = {0};
	memcpy(achInfoBuf, pBuf, wInfoLen);
    achInfoBuf[wInfoLen] = '\0';
	pBuf = achInfoBuf;
	nCharPos = strcspn(pBuf, "&");
	pchToken2 = strtok(pBuf, "&");
	while(NULL != pchToken2)
	{
		if(i >= MAX_KEY_VALUE_NUM) 
		{
			return ERR_LICENSE_FORMAT_FAILED;
		}
		s32 nKeyLen = sizeof(g_tKeyValue[i].achKey);
		s32 nValueLen = sizeof(g_tKeyValue[i].achValue);
		wRet = GetKeyValue(pchToken2, g_tKeyValue[i].achKey, nKeyLen,		// ��ȡKey-Value����Ϣ
			g_tKeyValue[i].achValue, nValueLen);
		if(SUCCESS_LICENSE != wRet) 
		{
			return wRet;
		}
		i++;
		pBuf += nCharPos + 1;
		nCharPos = strcspn(pBuf, "&");
		pchToken2 = strtok(pBuf, "&");
	}
	g_wKeyValueNum = static_cast<u16>(i);

//    printf( "g_wKeyValueNum = %d, wBufLen = %d\n", g_wKeyValueNum, wBufLen );
//    u16 w = 0;
//    for ( ; w < g_wKeyValueNum; w ++ )
//    {
//        printf( "%s = %s\n", g_tKeyValue[w].achKey, g_tKeyValue[w].achValue );
//    }

	memcpy(g_achContentBuf, achContentBuf, wBufLen);
    if ( wBufLen < LEN_KEYFILE_CONT )
    {
        g_achContentBuf[wBufLen] = '\0';
	    g_wBufLen = wBufLen;
    }
    else
    {
        g_achContentBuf[LEN_KEYFILE_CONT - 1] = '\0';
        g_wBufLen = LEN_KEYFILE_CONT - 1;
    }

	return SUCCESS_LICENSE;
}

/*=============================================================================
�� �� ��: GenerateContentFromMemory
��    ��: ��ˢ�º���ڴ��������µ�����
��    ��: s8 szEncryptedContent[LEN_KEYFILE_CONT]   [in]    �µļ�������
ע    ��: �൱��usbkey.dll���WriteKey
�� �� ֵ: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2007/06/12  1.0     ���    ����
=============================================================================*/
u16 GenerateContentFromMemory(s8 szEncryptedContent[LEN_KEYFILE_CONT])
{
#define CHECK_LEN(nNewPartLen)                              \
    if ( ( nOffset + nNewPartLen ) >= LEN_KEYFILE_CONT )    \
    {                                                       \
        return ERR_LICENSE_TOO_MANY_CHAR;                   \
    }

    if ( g_wKeyValueNum == 0 )
    {
        return ERR_LICENSE_DEV_INFO_FAILED;
    }

    s8 szContent[LEN_KEYFILE_CONT] = {0};
    s32 nOffset = 0;
    s32 nTempLen = 0;

    s8 szKeyname[32] = {0};
    s8 szKey[1024] = {0};
    s32 nKeyLen = 1024;

    strcpy( szKeyname, KEY_LICENSE_KEY );
    GetValue( szKeyname, szKey, nKeyLen );

    //������������
    u16 wIndex = 0;
    for ( wIndex = 0; wIndex < g_wKeyValueNum; wIndex ++ )
    {
        if (    strcmp( g_tKeyValue[wIndex].achKey, ENCRPT_LENGTH ) == 0
             || strcmp( g_tKeyValue[wIndex].achKey, KEY_LICENSE_KEY ) == 0  )
        {
            continue;
        }

        nTempLen = strlen( g_tKeyValue[wIndex].achKey );
        CHECK_LEN(nTempLen);
        memcpy( szContent + nOffset, g_tKeyValue[wIndex].achKey, nTempLen );
        nOffset += nTempLen;
        CHECK_LEN(sizeof (u8));
        szContent[nOffset] = '=';
        nOffset += sizeof (s8);
        nTempLen = strlen( g_tKeyValue[wIndex].achValue );
        CHECK_LEN(nTempLen);
        memcpy( szContent + nOffset, g_tKeyValue[wIndex].achValue, nTempLen );
        nOffset += nTempLen;
        CHECK_LEN(sizeof (u8));
        szContent[nOffset] = '&';
        nOffset += sizeof (s8);
    }

    //�ָ����ļ�������
//    nTempLen = strlen( KEY_VALUE_SEPARETE );
//    CHECK_LEN(nTempLen);
//    strcpy( szContent + nOffset, KEY_VALUE_SEPARETE );
//    nOffset += nTempLen;
    nTempLen = strlen( KEY_LICENSE_KEY );
    CHECK_LEN(nTempLen);
    strcpy( szContent + nOffset, KEY_LICENSE_KEY );
    nOffset += nTempLen;
    nTempLen = strlen( KEY_VALUE_CONNECTOR );
    CHECK_LEN(nTempLen);
    strcpy( szContent + nOffset, KEY_VALUE_CONNECTOR );
    nOffset += nTempLen;
    nTempLen = strlen( szKey );
    CHECK_LEN(nTempLen);
    strcpy( szContent + nOffset, szKey );
    nOffset += nTempLen;

    while ( ( nOffset % 16 ) != 0 )
    {
        nTempLen = strlen( KEY_VALUE_SEPARETE );
        CHECK_LEN(nTempLen);
        strcpy( szContent + nOffset, KEY_VALUE_SEPARETE );
        nOffset += nTempLen;
    }

    s8 szPrefix[64] = {0};
    sprintf( szPrefix, "%s=%d&", ENCRPT_LENGTH, nOffset );

    nTempLen = strlen( szPrefix );
    CHECK_LEN(nTempLen);
    memmove( szContent + nTempLen, szContent, nOffset );
    memcpy( szContent, szPrefix, nTempLen );

    nOffset += nTempLen;

    GenEncodeData( szEncryptedContent, sizeof (szContent), szContent, TRUE );

    return SUCCESS_LICENSE;
}

/*========================================================================
�� �� ����WriteLicenseFile
��    �ܣ�дLicense�ļ�
��    ����BOOL32 bToUsb = FALSE             [in]    �Ƿ�д��USB�豸
�� �� ֵ��u16 ������
--------------------------------------------------------------------------
�޸ļ�¼��
��		��	�汾	�޸���	�޸�����
2007/01/09	KCM1.0	���ƶ�	����
2007/06/12  1.0     ���    ����д��USB�豸
========================================================================*/
KDC_CALL u16 WriteLicenseFile(BOOL32 bToUsb /* = FALSE */)
{
	if(g_wBufLen <= 0) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	
	u16 wRet = SUCCESS_LICENSE;
	s8 achLicneseFilePath[1024] = {0};
	s32 nLicneseFilePathLen = 1024;
	wRet = GetValue((s8*)KEY_LICENSE_FILE_PATH, achLicneseFilePath, nLicneseFilePathLen);

	s8 *pchPath = achLicneseFilePath;
	if(SUCCESS_LICENSE != wRet) 
	{
		return wRet;
	}

#ifdef _USER_HKAPI
    if ( bToUsb || strcmp( achLicneseFilePath, USB_PATH ) == 0 )
    {
        SetValue( KEY_LICENSE_FILE_PATH, USB_PATH );
        s8 szContent[LEN_KEYFILE_CONT] = {0};

        wRet = GenerateContentFromMemory( szContent );
        if ( SUCCESS_LICENSE != wRet )
        {
            return wRet;
        }

        u16 wLen = sizeof ( szContent );
        wRet = WriteLicenseFileToUSB( szContent, wLen );
		if ( SUCCESS_LICENSE != wRet ) 
		{
			return wRet;
		}
    }
    else
    {
        s8 szContent[LEN_KEYFILE_CONT] = {0};
        FILE *pHandler = fopen( (LPCSTR)pchPath, "wb" );

        GenerateContentFromMemory( szContent );
	    if(NULL == pHandler) 
	    {
		    return ERR_LICENSE_OPENFILE_FAILED;
	    }
	    fwrite( szContent, sizeof (szContent), 1, pHandler );
	    fclose( pHandler );
    }

#else
    s8 szContent[LEN_KEYFILE_CONT] = {0};
    FILE *pHandler = fopen( (LPCSTR)pchPath, "wb" );

    GenerateContentFromMemory( szContent );
	if(NULL == pHandler) 
	{
		return ERR_LICENSE_OPENFILE_FAILED;
	}
	fwrite( szContent, sizeof (szContent), 1, pHandler );
	fclose( pHandler );
#endif

	return SUCCESS_LICENSE;
}

u16 EnumKeyList(TKeyValue *pchKeyValueList, s32 &nListLen)
{
//    printf( "g_wKeyValueNum = %d\n", g_wKeyValueNum );
//    u16 w = 0;
//    for ( ; w < g_wKeyValueNum; w ++ )
//    {
//        printf( "%s = %s\n", g_tKeyValue[w].achKey, g_tKeyValue[w].achValue );
//    }

	if(NULL == pchKeyValueList || nListLen < g_wKeyValueNum) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	nListLen = static_cast<s32>(g_wKeyValueNum);
	for(u16 i = 0; i < g_wKeyValueNum; i++)
	{
		memcpy(&pchKeyValueList[i], &g_tKeyValue[i], sizeof(TKeyValue));
	}
	return SUCCESS_LICENSE;
}

u16 GetValue(s8 *pchKey, s8 *pchValue, s32 &nValueLen)
{
	if(NULL == pchKey || NULL == pchValue) 
	{
		return ERR_LICENSE_INVALID_PARAM;
	}
	for(u16 i = 0; i < g_wKeyValueNum; i++)
	{
		if(strcmp(pchKey, g_tKeyValue[i].achKey) == 0)
		{
			s32 nBufLen = strlen(g_tKeyValue[i].achValue);
			if(nValueLen < nBufLen)
			{
				return ERR_LICENSE_INVALID_PARAM;
			}
			nValueLen = nBufLen;
			memcpy(pchValue, g_tKeyValue[i].achValue, nValueLen);
            pchValue[nValueLen] = '\0';

			return SUCCESS_LICENSE;
		}
	}

	return ERR_LICENSE_NO_KEY;
}

BOOL32 GetErrorCodeDescription(u16 wErrorCode, s8 *pchDescription, s32 &nLen, s8 *pchIniFilePath)
{
    s8 szText[1024] = {0};

    switch ( wErrorCode )
    {
    case SUCCESS_LICENSE:
        strcpy( szText, "�����ɹ�" );
        break;
    case ERR_LICENSE_AUTH_FAILED:
        strcpy( szText, "��Ȩ����֤ʧ��" );
        break;
    case ERR_LICENSE_FORMAT_FAILED:
        strcpy( szText, "��Ϣ��ʽ����" );
        break;
    case ERR_LICENSE_NO_VER_FAILED:
        strcpy( szText, "�ް汾��Ϣ" );
        break;
    case ERR_LICENSE_DEV_INFO_FAILED:
        strcpy( szText, "�豸��Ϣ��ȫ" );
        break;
    case ERR_LICENSE_ENCRYPT_FAILED:
        strcpy( szText, "����ʧ��" );
        break;
    case ERR_LICENSE_WRITEKEY_FAILED:
        strcpy( szText, "дLicense�ļ�ʧ��" );
        break;
    case ERR_LICENSE_SMALL_VALUE:
        strcpy( szText, "��ֵС������" );
        break;
    case ERR_LICENSE_BIG_VALUE:
        strcpy( szText, "��ֵ��������" );
        break;
    case ERR_LICENSE_LONG_STRING:
        strcpy( szText, "�ַ������ȴ�������" );
        break;
    case ERR_LICENSE_NO_ITEM_ENUM:
        strcpy( szText, "û�д�ѡ��" );
        break;
    case ERR_LICENSE_OUT_DATE:
        strcpy( szText, "���ڳ�������" );
        break;
    case ERR_LICENSE_NO_KEY:
        strcpy( szText, "��֧�ִ�KEYֵ" );
        break;
    case ERR_LICENSE_READ_CFG_FAIL:
        strcpy( szText, "�������ļ�ʧ��" );
        break;
    case ERR_LICENSE_INVALID_PARAM:
        strcpy( szText, "�����Ƿ�" );
        break;
    case ERR_LICENSE_NO_KEY_TYPE:
        strcpy( szText, "��֧�ִ�����" );
        break;
    case ERR_LICENSE_NO_USB_KEY:
        strcpy( szText, "��USBKEY" );
        break;
    case ERR_LICENSE_USB_CONNECT_FAIL:
        strcpy( szText, "����USB�豸ʧ��" );
        break;
    case ERR_LICENSE_USB_GET_FAIL:
        strcpy( szText, "��ռUSB�豸ʧ��" );
        break;
    case ERR_LICENSE_OPENFILE_FAILED:
        strcpy( szText, "���ļ�����" );
        break;
    case ERR_LICENSE_INVALID_USBKEY:
        strcpy( szText, "License�ļ���USB�豸����" );
        break;
    case ERR_LICENSE_USB_FORMAT_FAIL:
        strcpy( szText, "��ʽ��USB�豸ʧ��" );
        break;
    case ERR_LICENSE_USB_VERY_PASSWORD:
        strcpy( szText, "У��USB�豸����ʧ��" );
        break;
    case ERR_LICENSE_USB_CREATE_FILE_FAIL:
        strcpy( szText, "USB�豸�����ļ�ʧ��" );
        break;
    case ERR_LICENSE_USB_OPEN_FILE_FAIL:
        strcpy( szText, "USB�豸���ļ�ʧ��" );
        break;
    case ERR_LICENSE_USB_DELETE_FILE_FAIL:
        strcpy( szText, "USB�豸�����ļ�ʧ��" );
        break;
    case ERR_LICENSE_READKEY_FAILED:
        strcpy( szText, "��license�ļ�ʧ��" );
        break;
    case ERR_LICENSE_TOO_MANY_CHAR:
        strcpy( szText, "��Ȩ��Ϣ����" );
        break;
    case ERR_LICENSE_UNKNOWN:
    default:
        strcpy( szText, "����ԭ��Ĵ���" );
        break;
    }

    s32 nRealLen = strlen( szText );
    if ( nRealLen > nLen || pchDescription == NULL )
    {
        return FALSE;
    }

    strcpy( pchDescription, szText );

    return TRUE;

//	if(NULL == pchDescription || nLen < 1) 
//	{
//		return FALSE;
//	}
//	if(NULL == pchIniFilePath) 
//	{
//		return FALSE;
//	}
//	s8 achDescription[1024] = {0};
//	u32 dwLenBuf = 1024;
//	s8 achKeyName[10] = {0};
//	BOOL32 bRet = FALSE;
//
//	sprintf(achKeyName, "%d", wErrorCode);
//
//	bRet = GetRegKeyString(pchIniFilePath, ERROR_SEGMENT, 
//		achKeyName, "", achDescription, dwLenBuf);
//	if(!bRet) 
//	{
//		return FALSE;
//	}
//	
//	s32 nLenBuf = strlen(achDescription);
//	if(nLenBuf >= nLen) 
//	{
//		return FALSE;
//	}
//	
//	memcpy(pchDescription, achDescription, nLenBuf);
//	pchDescription[nLenBuf] = '\0';
//	nLen = nLenBuf;
//	
//	return TRUE;
}

u16 GetKeyValueNum()
{
	return g_wKeyValueNum;
}
/*

TKeyValue * EnumKeyList(s32 &nListLen)
{
	nListLen = g_wKeyValueNum;
	return g_tKeyValue;
}
*/

/*=============================================================================
�� �� ��: SetValue
��    ��: ���ڴ���������
��    ��: LPCSTR lpszKey                    [in]    ����
          LPCSTR lpszValue                  [in]    ��ֵ
ע    ��: ��ˢ�¶�ȡ���������ڴ�
�� �� ֵ: ������
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2007/06/12  1.0     ���    ����
=============================================================================*/
u16 SetValue(LPCSTR lpszKey, LPCSTR lpszValue)
{
    if ( lpszKey == NULL || lpszValue == NULL )
    {
        return ERR_LICENSE_INVALID_PARAM;
    }

    u16 wIndex = 0;
    for ( ; wIndex < g_wKeyValueNum; wIndex ++ )
    {
        if ( strcmp( g_tKeyValue[wIndex].achKey, lpszKey ) == 0 )
        {
            memset( g_tKeyValue[wIndex].achValue, 0,
                    sizeof (g_tKeyValue[wIndex].achValue) );
            strncpy( g_tKeyValue[wIndex].achValue, lpszValue,
                     sizeof (g_tKeyValue[wIndex].achValue) - 1 );
            return SUCCESS_LICENSE;
        }
    }

    if ( g_wKeyValueNum == MAX_KEY_VALUE_NUM )
    {
        return ERR_LICENSE_FORMAT_FAILED;
    }
    g_wKeyValueNum ++;
    memset( &g_tKeyValue[wIndex], 0, sizeof (g_tKeyValue[wIndex]) );
    strncpy( g_tKeyValue[wIndex].achKey, lpszKey,
             sizeof (g_tKeyValue[wIndex].achKey) - 1 );
    strncpy( g_tKeyValue[wIndex].achValue, lpszValue,
             sizeof (g_tKeyValue[wIndex].achValue) - 1 );

    return SUCCESS_LICENSE;
}




