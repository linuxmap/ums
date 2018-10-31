/*=======================================================================
模块名      :
文件名      : readlicense.h
相关文件    :
文件实现功能 : 读取license文件的内容
作者        : 邵云东
版本        : KCMV1.0  Copyright(C) 2003-2008 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2007/01/09  KCM1.0      邵云东      创建
=======================================================================*/

#include "readlicense.h"
#include "usbkeyconst.h"
#include "kdvsys.h"
#include "kdvencrypt.h"

#ifdef _USER_HKAPI
#include "hkapi.h"
#endif

#define MAX_KEY_VALUE_NUM						100							// 可读取的Key-Value对最大数

u16 g_wLastErrorCode = 0;													// 最后一次调用产生的错误码

TKeyValue g_tKeyValue[MAX_KEY_VALUE_NUM];
u16 g_wKeyValueNum = 0;

s8 g_achContentBuf[LEN_KEYFILE_CONT] = {0};
u16 g_wBufLen = 0;

s8 *strtokEx(s8 *pchBuf, const s8 *pchSeps)
{
	return strtok(pchBuf, pchSeps);
}

// 从子串中获取Key和Value
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
            strlen(KEY_VALUE_CONNECTOR) + 1 );	// Key与Value的分隔符

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


// 写文件到USB中
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
	dwRet = HK_ListReaders(NULL, &dwReaderNameLen, &dwReaderNum);			// 默认枚举第一个有效的USBKEY设备
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
	dwRet = HK_ConnectDev(&achDeviceName[dwDeviceSlot], &hCard);			// 连接设备
	if(0 != dwRet)
	{
		return ERR_LICENSE_NO_USB_KEY;
	}
#elif
    int nSlot = 0;
    dwRet = open_haikey( nSlot, &hCard );
#endif

	s8 achDevSerial[40] = {0};
	dwRet = HK_GetSerialNum(hCard, (u8*)achDevSerial);						// 比较Licnese文件与设备符合情况
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
	dwRet = HK_BeginTransaction(hCard);										// 开始独占设备
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
																			// 写文件
	dwRet = HK_WriteFile(hCard, 0x0000, (u8*)pchContent, wLen, &dwWriteDataLen);
	if (0 != dwRet)
	{
		FreeUSBKey( hCard );
		return ERR_LICENSE_WRITEKEY_FAILED;
	}

#ifdef WIN32
	HK_EndTransaction(hCard);												// 结束独占设备状态
	
	HK_DisconnectDev(hCard);												// 断开设备
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
	dwRet = HK_ListReaders(NULL, &dwReaderNameLen, &dwReaderNum);			// 默认枚举第一个有效的USBKEY设备
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
	dwRet = HK_ConnectDev(&achDeviceName[dwDeviceSlot], &hCard);			// 连接设备
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
	dwRet = HK_BeginTransaction(hCard);										// 开始独占设备
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

    // 读取文件
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
	HK_EndTransaction(hCard);												// 结束独占设备状态
	
	HK_DisconnectDev(hCard);												// 断开设备
#elif
    dwRet = close_haikey( hCard );
#endif

	hCard = NULL;

	return SUCCESS_LICENSE;
}

#endif

// 解密
void GenEncodeData(s8 *pOutBuf, u16 wInBufLen, s8 *pInBuf, BOOL32 bDirect)
{
    s8 achIV[MAX_IV_SIZE] = {0};
	
    s8 achKey[32] = {0};
    memset( achKey, 0, sizeof (achKey) );
	strncpy( achKey, KEDA_AES_KEY, strlen(KEDA_AES_KEY) );// 保持key为16的倍数
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
		wRet = ReadLicenseFileFromUSB(achContentBuf, wBufLen);				// 从USB设备读取文件
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
	GenEncodeData(achKeyValueContent, wKeyValueLen, achContentBuf, FALSE);	// 解密

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
	wRet = GetKeyValue(pchToken2, achKey, nKeyBuflen,						// 获取Key-Value对信息
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
		wRet = GetKeyValue(pchToken2, g_tKeyValue[i].achKey, nKeyLen,		// 获取Key-Value对信息
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
函 数 名: GenerateContentFromMemory
功    能: 从刷新后的内存里生成新的内容
参    数: s8 szEncryptedContent[LEN_KEYFILE_CONT]   [in]    新的加密数据
注    意: 相当于usbkey.dll里的WriteKey
返 回 值: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/12  1.0     王昊    创建
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

    //重新生成数据
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

    //恢复最后的几个数据
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
函 数 名：WriteLicenseFile
功    能：写License文件
参    数：BOOL32 bToUsb = FALSE             [in]    是否写入USB设备
返 回 值：u16 错误码
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2007/01/09	KCM1.0	邵云东	创建
2007/06/12  1.0     王昊    允许写入USB设备
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
        strcpy( szText, "操作成功" );
        break;
    case ERR_LICENSE_AUTH_FAILED:
        strcpy( szText, "授权码验证失败" );
        break;
    case ERR_LICENSE_FORMAT_FAILED:
        strcpy( szText, "信息格式错误" );
        break;
    case ERR_LICENSE_NO_VER_FAILED:
        strcpy( szText, "无版本信息" );
        break;
    case ERR_LICENSE_DEV_INFO_FAILED:
        strcpy( szText, "设备信息不全" );
        break;
    case ERR_LICENSE_ENCRYPT_FAILED:
        strcpy( szText, "加密失败" );
        break;
    case ERR_LICENSE_WRITEKEY_FAILED:
        strcpy( szText, "写License文件失败" );
        break;
    case ERR_LICENSE_SMALL_VALUE:
        strcpy( szText, "数值小于下限" );
        break;
    case ERR_LICENSE_BIG_VALUE:
        strcpy( szText, "数值大于上限" );
        break;
    case ERR_LICENSE_LONG_STRING:
        strcpy( szText, "字符串长度大于上限" );
        break;
    case ERR_LICENSE_NO_ITEM_ENUM:
        strcpy( szText, "没有此选项" );
        break;
    case ERR_LICENSE_OUT_DATE:
        strcpy( szText, "日期超出期限" );
        break;
    case ERR_LICENSE_NO_KEY:
        strcpy( szText, "不支持此KEY值" );
        break;
    case ERR_LICENSE_READ_CFG_FAIL:
        strcpy( szText, "读配置文件失败" );
        break;
    case ERR_LICENSE_INVALID_PARAM:
        strcpy( szText, "参数非法" );
        break;
    case ERR_LICENSE_NO_KEY_TYPE:
        strcpy( szText, "不支持此类型" );
        break;
    case ERR_LICENSE_NO_USB_KEY:
        strcpy( szText, "无USBKEY" );
        break;
    case ERR_LICENSE_USB_CONNECT_FAIL:
        strcpy( szText, "连接USB设备失败" );
        break;
    case ERR_LICENSE_USB_GET_FAIL:
        strcpy( szText, "独占USB设备失败" );
        break;
    case ERR_LICENSE_OPENFILE_FAILED:
        strcpy( szText, "打开文件错误" );
        break;
    case ERR_LICENSE_INVALID_USBKEY:
        strcpy( szText, "License文件与USB设备不符" );
        break;
    case ERR_LICENSE_USB_FORMAT_FAIL:
        strcpy( szText, "格式化USB设备失败" );
        break;
    case ERR_LICENSE_USB_VERY_PASSWORD:
        strcpy( szText, "校验USB设备口令失败" );
        break;
    case ERR_LICENSE_USB_CREATE_FILE_FAIL:
        strcpy( szText, "USB设备创建文件失败" );
        break;
    case ERR_LICENSE_USB_OPEN_FILE_FAIL:
        strcpy( szText, "USB设备打开文件失败" );
        break;
    case ERR_LICENSE_USB_DELETE_FILE_FAIL:
        strcpy( szText, "USB设备擦除文件失败" );
        break;
    case ERR_LICENSE_READKEY_FAILED:
        strcpy( szText, "读license文件失败" );
        break;
    case ERR_LICENSE_TOO_MANY_CHAR:
        strcpy( szText, "授权信息过长" );
        break;
    case ERR_LICENSE_UNKNOWN:
    default:
        strcpy( szText, "不明原因的错误" );
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
函 数 名: SetValue
功    能: 向内存设置数据
参    数: LPCSTR lpszKey                    [in]    段名
          LPCSTR lpszValue                  [in]    键值
注    意: 仅刷新读取出的数据内存
返 回 值: 错误码
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/12  1.0     王昊    创建
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




