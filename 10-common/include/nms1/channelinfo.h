/*=============================================================================
ģ   ��   ��: StreamPlayer��ý�岥����
��   ��   ��: ChannelInfo.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: ΪMCU��MT����ý�幦���ṩý������д���ļ�����
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/04/19  4.0     ���        ��������
=============================================================================*/

#ifndef  __CHANNELINFO_H
#define	 __CHANNELINFO_H

#include <time.h>
#include <stdio.h>
#include "osp.h"


#define MAX_H235KEY_LEN         (s32)255    //  ����Ƶ������Կ��󳤶�
#define MAX_CHANNELNAME_LEN     (s32)255    //  Ƶ������󳤶�
#define MAX_CHANNELPWD_LEN      (s32)32     //  Ƶ��������󳤶�


//  ����/���ܽṹ
typedef struct tagChannelEncryptKey
{
    enum EmEncryptMode      //  ����ģʽ
    {
        emEncryptNone   = (u8)0,    //  ������
        emEncryptDES    = (u8)1,    //  DES����
        emEncryptAES    = (u8)2     //  AES����
    };

    u8  m_byMode;                   // ����ģʽ(emEncryptNone/emEncryptDES/emEncryptAES)
    u8  m_byKeyLen;                 // ��Կ����(���ֽ�Ϊ��λ)
    u8  m_abyKey[MAX_H235KEY_LEN];  // ��Կ����

    /*=============================================================================
    �� �� ��:tagChannelEncryptKey
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    tagChannelEncryptKey()
    { memset( this, 0, sizeof (tagChannelEncryptKey) ); }

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        switch ( m_byMode ) //  ����ģʽ
        {
        case emEncryptNone:
            ::OspPrintf( TRUE, FALSE, "EncryptMode = None, " );
            break;
        case emEncryptDES:
            ::OspPrintf( TRUE, FALSE, "EncryptMode = DES, " );
            break;
        case emEncryptAES:
            ::OspPrintf( TRUE, FALSE, "EncryptMode = AES, " );
            break;
        default:
            ::OspPrintf( TRUE, FALSE, "EncryptMode = unknown(%d), ", m_byMode );
            break;
        }

        ::OspPrintf( TRUE, FALSE, "KeyLen = %d\nKey: ", m_byKeyLen );//��Կ����
        for ( s32 nIndex = 0; nIndex < m_byKeyLen; nIndex ++ )      //��Կ����
        {
            ::OspPrintf( TRUE, FALSE, "%.2x ", m_abyKey[nIndex] );
        }
        ::OspPrintf( TRUE, FALSE, "\n" );
    }

} TChannelEncryptKey;


//AAC LC����
#define CHANNEL_AAC_SAMPLE_FRQ_8                (u8)1
#define CHANNEL_AAC_SAMPLE_FRQ_11               (u8)2
#define CHANNEL_AAC_SAMPLE_FRQ_12               (u8)3
#define CHANNEL_AAC_SAMPLE_FRQ_16               (u8)4
#define CHANNEL_AAC_SAMPLE_FRQ_22               (u8)5
#define CHANNEL_AAC_SAMPLE_FRQ_24               (u8)6
#define CHANNEL_AAC_SAMPLE_FRQ_32               (u8)7
#define CHANNEL_AAC_SAMPLE_FRQ_44               (u8)8
#define CHANNEL_AAC_SAMPLE_FRQ_48               (u8)9
#define CHANNEL_AAC_SAMPLE_FRQ_64               (u8)10
#define CHANNEL_AAC_SAMPLE_FRQ_88               (u8)11
#define CHANNEL_AAC_SAMPLE_FRQ_96               (u8)12

#define CHANNEL_AAC_CHNL_TYPE_CUST              (u8)11
#define CHANNEL_AAC_CHNL_TYPE_SINGLE            (u8)1
#define CHANNEL_AAC_CHNL_TYPE_DOUBLE            (u8)2
#define CHANNEL_AAC_CHNL_TYPE_3                 (u8)3
#define CHANNEL_AAC_CHNL_TYPE_4                 (u8)4
#define CHANNEL_AAC_CHNL_TYPE_5                 (u8)5
#define CHANNEL_AAC_CHNL_TYPE_5P1               (u8)51
#define CHANNEL_AAC_CHNL_TYPE_7P1               (u8)71

//  ����/������Ϣ
typedef struct tagChannelEncrypt
{
    u8                  m_byRealAudioPT;    // ��Ƶ��ʵ�غ�ֵ
    u8                  m_byRealVideoPT;    // ��Ƶ��ʵ�غ�ֵ
    u8                  m_byAudioEncType;   // ��Ƶ��̬�غ�ֵ(�����ʽ)
    u8                  m_byVideoEncType;   // ��Ƶ��̬�غ�ֵ(�����ʽ)
    TChannelEncryptKey  m_tEncryptKey[2];   // ��Կ [0]Ϊ��Ƶ, [1]Ϊ��Ƶ
    u8                  m_byAACSamplePerSecond; // AAC������
    u8                  m_byAACChannels;        // AACͨ����

    /*=============================================================================
    �� �� ��:tagChannelEncrypt
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    tagChannelEncrypt()
    { memset( this, 0, sizeof (tagChannelEncrypt) ); }

    /*=============================================================================
    �� �� ��:GetPT
    ��    ��:��ȡ�����غ�
    ��    ��:��
    ע    ��:���ĸ�u8�غ�ƴ�ӳ�һ��u32�غ�
    �� �� ֵ:ƴ���ֶ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    �޸�
    =============================================================================*/
    u32 GetPT(void) const
    {
        u32 dwPt = ( (u32)m_byRealAudioPT << 24 | (u32)m_byRealVideoPT << 16
                        | (u32)m_byAudioEncType << 8 | (u32)m_byVideoEncType );
        return dwPt;
    }

    /*=============================================================================
    �� �� ��:GetKey
    ��    ��:��ȡ��Կ
    ��    ��:s8* pchBuf                 [out]   ��Կ����
             u8 byChannel               [in]    ��Կ���� 0: ��Ƶ; 1: ��Ƶ
    ע    ��:���ļ�д��Ͷ�ȡʹ��
    �� �� ֵ:��Կ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    �޸�
    =============================================================================*/
    s8* GetKey(s8* pchBuf, u8 byChannel) const
    {
        if ( byChannel > 1 || pchBuf == NULL )    //  ��������
        {
            ::OspPrintf( TRUE, FALSE,
                         "[TChannelEncrypt::GetKey] invalid param.\n" );
            return NULL;
        }

        try
        {
            const TChannelEncryptKey *ptKey = &m_tEncryptKey[byChannel];
            u32 dwKey = 0;
            for ( s32 nIndex = 0; nIndex < ptKey->m_byKeyLen; nIndex += 4 )
            {
                u16 wLow = ((u16)ptKey->m_abyKey[nIndex + 3])
                                | ((u16)ptKey->m_abyKey[nIndex + 2] << 8 );
                u16 wHigh = ((u16)ptKey->m_abyKey[nIndex + 1])
                                | ((u16)ptKey->m_abyKey[nIndex] << 8 );
                dwKey = ((u32)wLow) | ((u32)wHigh << 16 );
                sprintf( pchBuf + nIndex * 2, "%.8x", dwKey );
            }

            return pchBuf;
        }
        catch ( ... )
        {
            ::OspPrintf( TRUE, FALSE,
                         "[TChannelEncrypt::GetKey] not enough memory.\n" );
            return NULL;
        }
    }

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "Video:\nActivePT = %d, RealPT = %d\n",
                     m_byVideoEncType, m_byRealVideoPT );
        m_tEncryptKey[0].Print();
        ::OspPrintf( TRUE, FALSE, "Audio:\nActivePT = %d, RealPT = %d\n",
                     m_byAudioEncType, m_byRealAudioPT );
        m_tEncryptKey[1].Print();
        // AAC����
        ::OspPrintf( TRUE, FALSE, "Audio AAC:\nSamplePerSecond = %d, AACChannels = %d\n",
                     m_byAACSamplePerSecond, m_byAACChannels );
    }

} TChannelEncrypt;

//  ��ý��Ƶ����Ϣ
typedef struct tagStreamChannel
{
    s8              m_aszChannelName[MAX_CHANNELNAME_LEN + 1];  //Ƶ������
    s8              m_aszPassWord[MAX_CHANNELPWD_LEN + 1];      //����
    u32             m_dwStreamNum;  //ֻ�鲥����Ƶʱ, Ϊ1; ͬʱ�鲥˫��Ϊ2
    u32             m_dwIp;         //�鲥IP(������)
    u16             m_wPort[2];     //�˿���Ϣ(������), [0]Ϊ����Ƶ, [1]Ϊ˫��
    TChannelEncrypt m_tEncrypt[2];  //[0]Ϊ����Ƶ, [1]Ϊ˫��

    /*=============================================================================
    �� �� ��:tagStreamChannel
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    tagStreamChannel()
    { memset( this, 0, sizeof (tagStreamChannel) ); }

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/18  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE,
                     "ChannelName = %s, Pwd = %s, IP = %d, StreamNum = %d\n",
                     m_aszChannelName, m_aszPassWord, m_dwIp, m_dwStreamNum );
        ::OspPrintf( TRUE, FALSE, "Main: port = %d\n", m_wPort[0] );
        m_tEncrypt[0].Print();
        ::OspPrintf( TRUE, FALSE, "Dual: port = %d\n", m_wPort[1] );
        m_tEncrypt[1].Print();
    }

} TStreamChannel;

/*=============================================================================
�� �� ��:WriteChannel
��    ��:����ҳ�ļ�д��Ƶ����Ϣ
��    ��:TStreamChannel *ptChannel      [in]    ͨ��ָ��
         s32 nChannelNum                [in]    ͨ����
         FILE *pf                       [in]    ��ҳ�ļ�(�Ѵ�, ��ָ����һ��д��λ��)
ע    ��:WriteHtmlר�ú���
�� �� ֵ:�ɹ�: TRUE; ʧ��: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/04/18  4.0     ���    �޸�
=============================================================================*/
inline BOOL32 WriteChannel(TStreamChannel *ptChannel, s32 nChannelNum, FILE *pf)
{
    s8      aszContent[1024]    = {0};  //  �ļ�����
    s32     nLen                = 0;    //  д�볤��

    try
    {
        if ( pf == NULL )   //  �ļ��������ȷ
        {
            ::OspPrintf( TRUE, FALSE, "[WriteChannel] invalid file.\n" );
            return FALSE;
        }

        if ( nChannelNum == 0 || ptChannel == NULL )    //  ����Ҫд��Ƶ��
        {
            return TRUE;
        }

        for ( s32 nIndex = 0; nIndex < nChannelNum; nIndex ++ )
        {
            memset( aszContent, 0, sizeof (aszContent) );
            s8 aszHref[1024] = {0};
            s8 *pszBuf = NULL;
            TStreamChannel *ptCurChannel = &ptChannel[nIndex];  //��ǰ����ͨ��

            nLen = sprintf( aszHref, "num=%u&",
                            ptChannel[nIndex].m_dwStreamNum );
            if ( nLen == -1 )
            {
                return FALSE;
            }

            pszBuf = aszHref + nLen;
            nLen = sprintf( pszBuf, "ip=%u&pass=%s",
                            ptChannel[nIndex].m_dwIp,
                            ptChannel[nIndex].m_aszPassWord );
            if ( nLen == -1 )
            {
                return FALSE;
            }

            s8 achKeyBuf[MAX_H235KEY_LEN] = {0};
            s8 achKeyBuf2[MAX_H235KEY_LEN] = {0};
            TChannelEncrypt *ptEncrypt = NULL;

            for ( u32 dwNum = 0; dwNum < ptChannel[nIndex].m_dwStreamNum;
                  dwNum ++ )
            {
                ptEncrypt = &ptCurChannel->m_tEncrypt[dwNum];
                memset( achKeyBuf, 0, sizeof (achKeyBuf) );
                memset( achKeyBuf2, 0, sizeof (achKeyBuf2) );
                pszBuf = pszBuf + nLen;
                nLen = sprintf( pszBuf,
"&port=%u&apt=%u&aacfreq=%u&aacchn=%u&vkeylen=%u&vkeymode=%u&vkey=%s&akeylen=%u&akeymode=%u&akey=%s",
                                ptCurChannel->m_wPort[dwNum],
                                ptEncrypt->GetPT(),
                                ptEncrypt->m_byAACSamplePerSecond,
                                ptEncrypt->m_byAACChannels,
                                ptEncrypt->m_tEncryptKey[0].m_byKeyLen,
                                ptEncrypt->m_tEncryptKey[0].m_byMode,
                                ptEncrypt->GetKey( achKeyBuf, 0 ),
                                ptEncrypt->m_tEncryptKey[1].m_byKeyLen,
                                ptEncrypt->m_tEncryptKey[1].m_byMode,
                                ptEncrypt->GetKey( achKeyBuf2, 1 ) );

                if ( nLen == -1 )
                {
                    return FALSE;
                }
            }

            s32 nSize = strlen( aszHref );
            //���׼���
            for ( s32 nPos = 0; nPos < nSize; nPos ++ )
            {
                //���˲��ܼ��ܵķ���
                switch ( aszHref[nPos] )
                {
                case '=':
                case '&':
                case '<':
                case '>':
                    break;
                default:
                    aszHref[nPos] = aszHref[nPos] + 1;
                    break;
                }
            }

            nLen = sprintf( aszContent,
                    "<p><a href='player.htm?%s' target='target'>%s</a></p>\n",
                            aszHref, ptCurChannel->m_aszChannelName );
            if ( nLen == -1 )
            {
                return FALSE;
            }
            fwrite( aszContent, sizeof (s8), nLen, pf );
        }

        return TRUE;
    }
    catch ( ... )
    {
        ::OspPrintf( TRUE, FALSE, "[WriteChannel] unknown error.\n" );
        return FALSE;
    }
}

/*=============================================================================
�� �� ��:WriteHtml
��    ��:д��ҳ�ļ�
��    ��:s8 *pszFileName                [in]    ��ҳ�ļ���
         TStreamChannel *ptChannel      [in]    ͨ��ָ��
         s32 nChannelNum                [in]    ͨ����
ע    ��:��
�� �� ֵ:�ɹ�: TRUE; ʧ��: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/04/18  4.0     ���    �޸�
=============================================================================*/
inline BOOL32 WriteHtml(s8 *pszFileName, TStreamChannel *ptChannel, s32 nChannelNum)
{
    FILE    *pf                 = NULL; //  �ļ�ָ��
    s8      aszContent[1024]    = {0};  //  �ļ�����
    time_t  tTime               = 0;    //  ��ǰʱ��
    s32     nLen                = 0;    //  д�볤��
    BOOL32  bRet                = FALSE;//  ���ز���

    try
    {
        pf = fopen( pszFileName, "w" );
        if ( pf == NULL )       //  �ļ���ʧ��
        {
            return bRet;
        }

        //д����
        nLen = sprintf( aszContent, "%s%d%s%s%s%s%s",
                        "<html>\n<head>\n<title>��ý�����Ƶ��ˢ����",
                        time( &tTime ), "</title>\n",
        "<meta HTTP-EQUIV=Content-Type CONTENT=text/html; charset=gb2312>\n",
        "<meta NAME=Description CONTENT=2004���ڿƴ����������𿪷�>\n\n",
                        "</head>\n<body bgcolor=#243D53>\n\n",
                        "<span id=linker1  type=hidden>\n" );
        if ( nLen == -1 )
        {
            fclose( pf );
            return bRet;
        }
        fwrite( aszContent, sizeof (s8), nLen, pf );

        bRet = WriteChannel( ptChannel, nChannelNum, pf );
        if ( ! bRet )
        {
            fclose( pf );
            return FALSE;
        }

        //д��ҳ���ʽ��Ϣ2
        memset( aszContent, 0, sizeof (aszContent) );
        nLen = sprintf( aszContent, "%s", "</span>\n</body>\n</html>\r\n" );
        if ( nLen == -1 )
        {
            fclose( pf );
            return FALSE;
        }
        fwrite( aszContent, sizeof (s8), nLen, pf );
        fflush( pf );
        fclose( pf );

        return TRUE;
    }
    catch ( ... )
    {
        ::OspPrintf( TRUE, FALSE, "[WriteHtml] unknown error.\n" );
        return FALSE;
    }
}

#endif  //  __CHANNELINFO_H
