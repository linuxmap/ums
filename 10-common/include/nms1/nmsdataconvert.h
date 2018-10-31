#if !defined (__NMS_DATA_CONVERT_H__)
#define __NMS_DATA_CONVERT_H__


/*=============================================================================
�� �� ��:NmsHex2Asc
��    ��:��һ��16���Ƶ�����0~9,a~f��ת��Ϊ�ַ�, ��0x0->'0',...,0x0f->'f'
��    ��:u8 byHex                           [in]    ��ת����BIN
         u8 *pbyAsc                         [out]   ���
ע    ��:��
�� �� ֵ:�Ƿ�ɹ�
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����淶��
=============================================================================*/
inline BOOL32 NmsHex2Asc(u8 byHex, u8 *pbyAsc)
{
    if ( pbyAsc == NULL || byHex < 0 || byHex > 0x0f )
    {
        return FALSE;
    }

    if ( byHex < 10 )
    {
        *pbyAsc = byHex + '0';
    }
    else
    {
        *pbyAsc = byHex - 10 + 'A';
    }

    return TRUE;
}

/*=============================================================================
�� �� ��:NmsAsc2Hex
��    ��:�������ַ�תΪһ��16���Ƶ�ֵ, ��1~fѹ����һ���ֽڣ���7f->0x7f
��    ��:const u8 *pbyAsc                   [in]    ��ת����ASC
         u8 *pbyHex                         [out]   ���
ע    ��:��
�� �� ֵ:�Ƿ�ɹ�, ���ת��ʧ�ܣ�����FALSE, ������ַ�����0~9,a~f֮�䣬����FLASE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����淶��
=============================================================================*/
inline BOOL32 NmsAsc2Hex(const u8 *pbyAsc, u8 *pbyHex)
{
    if ( pbyHex == NULL || pbyAsc == NULL )
    {
        return FALSE;
    }

    u8 byLow    = 0;
    u8 byHigh   = 0;

    if ( pbyAsc[0] >= '0' && pbyAsc[0] <= '9' )
    {
        byLow = pbyAsc[0] - '0';
    }
    else if ( pbyAsc[0] >= 'a' && pbyAsc[0] <= 'f' )
    {
        byLow = pbyAsc[0] - 'a' + 10;
    }
    else if ( pbyAsc[0] >= 'A' && pbyAsc[0] <= 'F' )
    {
        byLow = pbyAsc[0] - 'A' + 10;
    }
    else
    {
        return FALSE;
    }

    if ( pbyAsc[1] >= '0' && pbyAsc[1] <= '9' )
    {
        byHigh = pbyAsc[1] - '0';
    }
    else if ( pbyAsc[1] >= 'a' && pbyAsc[1] <= 'f' )
    {
        byHigh = pbyAsc[1] - 'a' + 10;
    }
    else if ( pbyAsc[1] >= 'A' && pbyAsc[1] <= 'F' )
    {
        byHigh = pbyAsc[1] - 'A' + 10;
    }
    else
    {
        return FALSE;
    }

    *pbyHex = (byLow << 4 | byHigh );

    return TRUE;
}

/*=============================================================================
�� �� ��:NmsDataHex2Asc
��    ��:��һ��16���Ƶ��ڴ�ֵת��Ϊ�ַ���, ��0x72a9->"72a9"
��    ��:const u8 *pbyHex                   [in]    ��ת����HEX��
         s32 nHexlen                        [in]    ��ת����HEX�볤��
         u8 *pbyAsc                         [out]   ת����Ľ��
ע    ��:������ԭ��������������һ���ֽ�תΪ2���ֽ�
�� �� ֵ:�Ƿ�ɹ�, ���ת��ʧ�ܣ�����FALSE, ������ַ�����0~9,a~f֮�䣬����FLASE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����淶��
=============================================================================*/
inline BOOL32 NmsDataHex2Asc(const u8 *pbyHex, s32 nHexlen, u8 *pbyAsc)
{
    u8 byLow    = 0;
    u8 byHigh   = 0;

    for ( s32 nIndex = 0; nIndex < nHexlen; nIndex ++ )
    {
        byLow = (pbyHex[nIndex] & 0xf0) >> 4;
        byHigh = (pbyHex[nIndex] & 0x0f);

        if ( ! NmsHex2Asc( byLow, &pbyAsc[2 * nIndex] ) )
        {
            return FALSE;
        }
        if ( ! NmsHex2Asc( byHigh, &pbyAsc[2 * nIndex + 1] ) )
        {
            return FALSE;
        }
    }

    return TRUE;
}


/*=============================================================================
�� �� ��:NmsDataAsc2Hex
��    ��:��һ���ַ�����16������ʽתΪ�ڴ棬���"98df13"->0x98df13
��    ��:const u8 *pbyAsc                   [in]    ��ת����ASC��
         u8 *pbyHex                         [out]   �����ת����Ľ��
         s32 nHexLen                        [in]    ��ת����ASC�볤��
ע    ��:������ԭ����һ�룬�ַ����ĳ��ȱ�����2�ı���
�� �� ֵ:�Ƿ�ɹ�, ����ַ������в���'0'~'9'��'a'~'f','A'~'F'֮��ģ��򷵻�FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����淶��
=============================================================================*/
inline BOOL32 NmsDataAsc2Hex(const u8 *pbyAsc, u8 *pbyHex, s32 nHexLen)
{
    if ( nHexLen % 2 != 0 )     //  ������ż�����ַ�
    {
        return FALSE;
    }

    for ( s32 nIndex = 0; nIndex < nHexLen / 2; nIndex ++ )
    {
        if ( ! NmsAsc2Hex( pbyAsc + 2 * nIndex, pbyHex + nIndex ) )
        {
            return FALSE;
        }
    }

    return TRUE;
}

#endif // __NMS_DATA_CONVERT_H__
