/*****************************************************************************
   ģ����      : MCU-DCS���ڷ�ʽ���ɣ�ͨ������
   �ļ���      : mcudcspdu.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: 
   ����        : ����
   �汾        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2005/12/02  0.1         ����        ����
   2006/06/14  0.2         �޽���      ���ʵ��
******************************************************************************/
#ifndef _MCU_DCS_PDU_H_
#define _MCU_DCS_PDU_H_


#define IN
#define OUT
#define IN_OUT
#define CONDITION_RETURN(func) if ( !func ) return FALSE;

#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
    #ifndef PACKED
        #define PACKED
    #endif
#else
    #ifndef PACKED
        #define PACKED __attribute__ ( (packed) ) 
    #endif
#endif


/*====================================================================
-- Part 1 : ���ļ�˵����ʹ�÷���ʾ��
====================================================================*/
// ���ļ��Ľṹ��
//    �ӿڲ��֣�
//                ��������ӿ�  CKdvMcuDcsNetData
//                �������ݽӿ�  CKdvMcuDcsItem
//                PDU�ӿ�       CMcuDcsPDU
//    ʵ�ֲ��֣�
//                �������ʵ��  CNetDataCoder
//                ��������ʵ��  
//                PDUʵ��
//
// ʹ��ʾ��
//
// CDcsMcuMtMtOfflineNotifyPdu cExamplePdu;     // Э��PDU
// CNetDataCoder cCoder;                        // �������
// u8 achNetData[100];                          // ��������
//
// ����ʵ��
// cCoder.SetNetDataBuffer(achNetData, 100);
// cExamplePdu.PduEncode(cCoder);
// ���������ݴ����achNetData��
// 
// ����ʵ��
// cCoder.SetNetDataBuffer(achNetData, 100);
// cExamplePdu.PduDecode(cCoder);
// ���������ݴ����cExamplePdu��

/*====================================================================
-- Part 2 : ����ӿڶ���
====================================================================*/

/*====================================================================
���� �� CKdvMcuDcsNetData
���� �� �������������������뷽��
====================================================================*/
class CKdvMcuDcsNetData
{
protected:
    u32 m_dwBufferLength;
    u8* m_pBufferPointer;
    u32 m_dwCurrentPos;
public:
    // ���캯��
    CKdvMcuDcsNetData() : m_dwBufferLength(0), m_pBufferPointer(NULL), m_dwCurrentPos(0)
    {
    }
    u32 GetCurrentLength()
    {
        return m_dwCurrentPos;
    }
    // �����������ݻ�������(�����/����ǰ)�����ݴ�������
    virtual void SetNetDataBuffer(IN u8* pBufferPointer, IN u32 dwBufferLength)
    {
        m_pBufferPointer = pBufferPointer;
        m_dwBufferLength = dwBufferLength;
        m_dwCurrentPos = 0;
    }
    // ����ָ�����ȵ����ݣ������б����
    BOOL32 SkipData(IN u16 nCount)
    {
        if (m_dwCurrentPos + nCount <= m_dwBufferLength)
        {
            m_dwCurrentPos += nCount;
            return TRUE;
        }
        return FALSE;
    }
    // U8���ͱ���
    virtual BOOL32 U8Encode(IN u8 nCount, IN const u8* pStartAt) = 0;
    // S8���ͱ���
    virtual BOOL32 S8Encode(IN u8 nCount, IN const s8* pStartAt) = 0;
    // U16���ͱ���
    virtual BOOL32 U16Encode(IN u8 nCount, IN const u16* pStartAt) = 0;
    // S16���ͱ���
    virtual BOOL32 S16Encode(IN u8 nCount, IN const s16* pStartAt) = 0;
    // U32���ͱ���
    virtual BOOL32 U32Encode(IN u8 nCount, IN const u32* pStartAt) = 0;
    // S32���ͱ���
    virtual BOOL32 S32Encode(IN u8 nCount, IN const s32* pStartAt) = 0;
    // U8���ͽ���
    virtual BOOL32 U8Decode(IN u8 nCount, OUT u8* pStartAt) = 0;
    // S8���ͽ���
    virtual BOOL32 S8Decode(IN u8 nCount, OUT s8* pStartAt) = 0;
    // U16���ͽ���
    virtual BOOL32 U16Decode(IN u8 nCount, OUT u16* pStartAt) = 0;
    // S16���ͽ���
    virtual BOOL32 S16Decode(IN u8 nCount, OUT s16* pStartAt) = 0;
    // U32���ͽ���
    virtual BOOL32 U32Decode(IN u8 nCount, OUT u32* pStartAt) = 0;
    // S32���ͽ���
    virtual BOOL32 S32Decode(IN u8 nCount, OUT s32* pStartAt) = 0;
}PACKED;


/*====================================================================
���� �� CKdvMcuDcsItem
���� �� Э��Ļ������ݣ��ɶ��������
====================================================================*/
class CKdvMcuDcsItem
{
public:
    // �����������Ͷ���
    enum EItemType
    {
        ErrorInfor      = 0,
        DcsInfor        = 1,
        ConfBasicInfor  = 2,
        ConfShortInfor  = 3,
        MtShortInfor    = 4,
        McuMsstateInfor = 5
    };
    // �������ݱ���
    BOOL32 ItemEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(ItemEncodeHead(cNetData));
        CONDITION_RETURN(ItemDataEncode(cNetData));
        return TRUE;
    }
    // �������ݽ���
    BOOL32 ItemDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(ItemDecodeHead(cNetData));
        CONDITION_RETURN(ItemDataDecode(cNetData));
        return TRUE;
    }
protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData&) const = 0;
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData&) = 0;
    // �õ�������������
    virtual EItemType GetItemType() const = 0;
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const = 0;
private:
    BOOL32 ItemEncodeHead(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        u8 byItemType = GetItemType();
        CONDITION_RETURN(cNetData.U8Encode(1, &byItemType));
        u16 wItemLengh = GetItemLength();
        CONDITION_RETURN(cNetData.U16Encode(1, &wItemLengh));
        return TRUE;
    }
    BOOL32 ItemDecodeHead(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        u8 byItemType;
        u16 wItemLengh;
        CONDITION_RETURN(cNetData.U8Decode(1, &byItemType));
        CONDITION_RETURN(cNetData.U16Decode(1, &wItemLengh));
        // �������ָ����Ҫ��Item��������Item
        if ( byItemType != (u8)GetItemType() )
        {
            cNetData.SkipData(wItemLengh);
            return FALSE;
        }
        return TRUE;
    }
}PACKED;


/*====================================================================
���� �� CMcuDcsPDU
���� �� PDU���ɶ��������
====================================================================*/
class CMcuDcsPDU
{
public:
    // ��ͷ����
    u8 m_nHeadLength;
    // �汾��
    u8 m_byVersion;
    // �����������к�
    u8 m_bySeq;
    // ����ID
    u16 m_wConfId;
    // �ն�ID
    u16 m_wMtId;
    // ���캯��
    CMcuDcsPDU() : m_nHeadLength(7), m_byVersion(1), m_bySeq(0), m_wConfId(0), m_wMtId(0)
    {
    }
    // ���������ݵõ���PDU
    virtual BOOL32 PduDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(PduDecodeHead(cNetData));
        CONDITION_RETURN(PduDataDecode(cNetData));
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(PduEncodeHead(cNetData));
        CONDITION_RETURN(PduDataEncode(cNetData));
        return TRUE;
    }
protected:
    // PDU�������ݱ���
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    };
    // PDU�������ݽ���
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    };
private:
    // PDU��ͷ����
    BOOL32 PduEncodeHead(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(cNetData.U8Encode(1, &m_nHeadLength));
        CONDITION_RETURN(cNetData.U8Encode(1, &m_byVersion));
        CONDITION_RETURN(cNetData.U8Encode(1, &m_bySeq));
        CONDITION_RETURN(cNetData.U16Encode(1, &m_wConfId));
        CONDITION_RETURN(cNetData.U16Encode(1, &m_wMtId));
        return TRUE;
    }
    // PDU��ͷ����
    BOOL32 PduDecodeHead(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(cNetData.U8Decode(1, &m_nHeadLength));
        if (m_nHeadLength < 7)
        {
            return FALSE;
        }
        CONDITION_RETURN(cNetData.U8Decode(1, &m_byVersion));
        CONDITION_RETURN(cNetData.U8Decode(1, &m_bySeq));
        CONDITION_RETURN(cNetData.U16Decode(1, &m_wConfId));
        CONDITION_RETURN(cNetData.U16Decode(1, &m_wMtId));
        if (m_nHeadLength > 7)
        {
            cNetData.SkipData(m_nHeadLength-7);
        }
        return TRUE;
    }
}PACKED;


/*====================================================================
-- Part 3 : �������ʵ��
====================================================================*/


/*====================================================================
���� �� CNetDataCoder
���� �� �򵥱������ʵ��
====================================================================*/
class CNetDataCoder : public CKdvMcuDcsNetData
{
public:
    // U8���ͱ���
    virtual BOOL32 U8Encode(IN u8 nCount, IN const u8* pStartAt)
    {
        if ( m_dwCurrentPos + nCount <= m_dwBufferLength )
        {
            memcpy(m_pBufferPointer+m_dwCurrentPos, pStartAt, nCount);
            m_dwCurrentPos += nCount;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    };
    // S8���ͱ���
    virtual BOOL32 S8Encode(IN u8 nCount, IN const s8* pStartAt)
    {
        return U8Encode(nCount, (const u8*)pStartAt);
    };
    // U16���ͱ���
    virtual BOOL32 U16Encode(IN u8 nCount, IN const u16* pStartAt)
    {
        if (m_dwCurrentPos+2*nCount <= m_dwBufferLength)
        {
            u16* pCurrentU16Pointer = (u16*)(m_pBufferPointer+m_dwCurrentPos);
            m_dwCurrentPos += 2*nCount;
            for (s32 nPos=0; nPos<nCount; nPos++)
            {
                *pCurrentU16Pointer = htons(*(pStartAt+nPos));
                pCurrentU16Pointer++;
            }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    };
    // S16���ͱ���
    virtual BOOL32 S16Encode(IN u8 nCount, IN const s16* pStartAt)
    {
        return U16Encode(nCount, (const u16*)pStartAt);
    };
    // U32���ͱ���
    virtual BOOL32 U32Encode(IN u8 nCount, IN const u32* pStartAt)
    {
        if (m_dwCurrentPos+4*nCount <= m_dwBufferLength)
        {
            u32* pCurrentU32Pointer = (u32*)(m_pBufferPointer+m_dwCurrentPos);
            m_dwCurrentPos += 4*nCount;
            for (s32 nPos=0; nPos<nCount; nPos++)
            {
                *pCurrentU32Pointer = htonl(*(pStartAt+nPos));
                pCurrentU32Pointer++;
            }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    // S32���ͱ���
    virtual BOOL32 S32Encode(IN u8 nCount, IN const s32* pStartAt)
    {
        return U32Encode(nCount, (const u32*)pStartAt);
    }

    // U8���ͽ���
    virtual BOOL32 U8Decode(IN u8 nCount, OUT u8* pStartAt)
    {
        if ( m_dwCurrentPos + nCount <= m_dwBufferLength )
        {
            memcpy(pStartAt, m_pBufferPointer+m_dwCurrentPos, nCount);
            m_dwCurrentPos += nCount;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    // S8���ͽ���
    virtual BOOL32 S8Decode(IN u8 nCount, OUT s8* pStartAt)
    {
        return U8Decode(nCount, (u8*)pStartAt);
    }
    // U16���ͽ���
    virtual BOOL32 U16Decode(IN u8 nCount, OUT u16* pStartAt)
    {
        if (m_dwCurrentPos+2*nCount <= m_dwBufferLength)
        {
            u16* pCurrentU16Pointer = (u16*)(m_pBufferPointer+m_dwCurrentPos);
            m_dwCurrentPos += 2*nCount;
            for (s32 nPos=0; nPos<nCount; nPos++)
            {
                *(pStartAt+nPos) = ntohs(*pCurrentU16Pointer);
                pCurrentU16Pointer++;
            }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    // S16���ͽ���
    virtual BOOL32 S16Decode(IN u8 nCount, OUT s16* pStartAt)
    {
        return U16Decode(nCount, (u16*)pStartAt);
    }
    // U32���ͽ���
    virtual BOOL32 U32Decode(IN u8 nCount, OUT u32* pStartAt)
    {
        if (m_dwCurrentPos+4*nCount <= m_dwBufferLength)
        {
            u32* pCurrentU32Pointer = (u32*)(m_pBufferPointer+m_dwCurrentPos);
            m_dwCurrentPos += 4*nCount;
            for (s32 nPos=0; nPos<nCount; nPos++)
            {
                *(pStartAt+nPos) = ntohl(*pCurrentU32Pointer);
                pCurrentU32Pointer++;
            }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    // S32���ͽ���
    virtual BOOL32 S32Decode(IN u8 nCount, OUT s32* pStartAt)
    {
        return U32Decode(nCount, (u32*)pStartAt);
    }
}PACKED;

/*====================================================================
-- Part 4 : ��������ʵ��
====================================================================*/

/*====================================================================
���� �� CErrorInfor
���� �� �������ݣ�������Ϣ
====================================================================*/
class CErrorInfor : public CKdvMcuDcsItem
{
public:
    // �������Ͷ���
    enum EErrorType
    {
        e_Succuss               = 0,    // �ɹ�
        e_UnSpecified           = 1,    // δ����
		e_UnConfig				= 2,	// ��DCSû������
        e_NoSuchConf            = 3,    // �޴˻���
        e_ConfAlreadyExist      = 4,    // �����Ѵ���
        e_NoSuchMt              = 5,    // �޴��ն�
        e_MtAlreadyExist        = 6,    // �ն��Ѵ���
        e_NotOnline             = 7,    // �ն�û������
        e_AlreadyOnline         = 8,    // �ն�������
        e_PermissionDeny        = 9,    // �޴�Ȩ��
        e_NotReady              = 10,    // δ׼����
        e_PassWordError         = 11,   // ���벻��ȷ
        e_ConfFull              = 12,   // ��������
        e_MtFull                = 13,   // �ն�����
		e_DcsFull				= 14,	// ע���DCS����
		e_NotDaemon				= 15,	// ע����Ϣû�з���DAEMON��
        e_NotDoubleMcu          = 16    // û�д���MCU 
    };
    // ��������
    EErrorType m_emErrorType;
protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        u8 byErrorType = (u8)m_emErrorType;
        CONDITION_RETURN(cNetData.U8Encode(1, &byErrorType));
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        u8 byErrorType;
        CONDITION_RETURN(cNetData.U8Decode(1, &byErrorType));
        m_emErrorType = (EErrorType)byErrorType;
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return ErrorInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        return (sizeof(u8));
    }
}PACKED;


/*====================================================================
���� �� CDcsInfor
���� �� �������ݣ�DCS��Ϣ
====================================================================*/
class CDcsInfor : public CKdvMcuDcsItem
{
private:
    // ��ѡ����������ĳһλΪ1����ʾ�ÿ�ѡ����ڣ�0��ʾ������
        // ��һλ ---- ��������
        // �ڶ�λ ---- ����ն���
		// ����λ ---- ���ֱ���¼��ն���
        // ����λ ---- ��߼�����
        // ����λ ---- Ԥ���˿���ʼ�˿ںͷ�Χ
        // ����Ϊ ---- DCS ID��MCU�ڲ�ʹ�ã�
    u8 m_byOptionField;

public:
    // DCS IP��ַ
    u32 m_dwDcsIp;
    // DCS�˿�
    u16 m_wDcsPort;
    // ����������Ĭ��32
    u8 m_byMaxConfCount;
    // ����������ն�����Ĭ��64
    u8 m_byMaxMtCount;
    // ���ֱ���¼��ն�����Ĭ��32
    u8 m_byMaxDirectMtCount;
    // ��߼�������Ĭ��16
    u8 m_byMaxHeight;
    // Ԥ���˿ڷ�Χ��ʼ�˿ڣ�Ĭ��9000
    u16 m_wReservedPortStart;
    // Ԥ���˿ڷ�Χ��С��Ĭ��100
    u16 m_wReservedPortRang;
	// DCS ID (MCU�ڲ�ʹ��)
	u8  m_byDcsId;
    CDcsInfor() : m_byOptionField(0), m_byMaxConfCount(32), m_byMaxMtCount(64),
        m_byMaxHeight(16), m_wReservedPortStart(9000), m_wReservedPortRang(100), m_byDcsId(0)
    {
    }
public:
    enum EOption
    {
        e_MaxConfCount   = 0x80>>0, // ��������
        e_MaxMtCount     = 0x80>>1, // ����������ն���
        e_MaxDirectCount = 0x80>>2, // ���ֱ���¼��ն���
        e_Height         = 0x80>>3, // ��߼�����
        e_ReservedPort   = 0x80>>4, // Ԥ���˿���Ϣ
		e_DcsId			 = 0x80>>5	// DCS ID��
    };
    // �����ѡ��
    void IncludeOption(IN EOption emOption)
    {
        m_byOptionField |= emOption;
    }
    // �ж��Ƿ��п�ѡ��
    BOOL32 HasOption(IN EOption emOption) const
    {
        return ( (m_byOptionField & emOption) != 0 );
    }

protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(cNetData.U32Encode(1, &m_dwDcsIp));
        CONDITION_RETURN(cNetData.U16Encode(1, &m_wDcsPort));
        CONDITION_RETURN(cNetData.U8Encode(1, &m_byOptionField));
        if ( HasOption(e_MaxConfCount) )
        {
            CONDITION_RETURN(cNetData.U8Encode(1, &m_byMaxConfCount));
        }
        if ( HasOption(e_MaxMtCount) )
        {
            CONDITION_RETURN(cNetData.U8Encode(1, &m_byMaxMtCount));
        }
        if ( HasOption(e_MaxDirectCount) )
        {
            CONDITION_RETURN(cNetData.U8Encode(1, &m_byMaxDirectMtCount));
        }
        if ( HasOption(e_Height) )
        {
            CONDITION_RETURN(cNetData.U8Encode(1, &m_byMaxHeight));
        }
        if ( HasOption(e_ReservedPort) )
        {
            CONDITION_RETURN(cNetData.U16Encode(1, &m_wReservedPortStart));
            CONDITION_RETURN(cNetData.U16Encode(1, &m_wReservedPortRang));
        }
		if ( HasOption(e_DcsId) )
        {
            CONDITION_RETURN(cNetData.U8Encode(1, &m_byDcsId));
        }
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(cNetData.U32Decode(1, &m_dwDcsIp));
        CONDITION_RETURN(cNetData.U16Decode(1, &m_wDcsPort));
        CONDITION_RETURN(cNetData.U8Decode(1, &m_byOptionField));
        if ( HasOption(e_MaxConfCount) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &m_byMaxConfCount));
        }
        if ( HasOption(e_MaxMtCount) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &m_byMaxMtCount));
        }
        if ( HasOption(e_MaxDirectCount) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &m_byMaxDirectMtCount));
        }
        if ( HasOption(e_Height) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &m_byMaxHeight));
        }
        if ( HasOption(e_ReservedPort) )
        {
            CONDITION_RETURN(cNetData.U16Decode(1, &m_wReservedPortStart));
            CONDITION_RETURN(cNetData.U16Decode(1, &m_wReservedPortRang));
        }
		if ( HasOption(e_DcsId) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &m_byDcsId));
        }
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return DcsInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        u16 wLength = sizeof(u32) + sizeof(u16) + sizeof(u8);
        if ( HasOption(e_MaxConfCount) )
        {
            wLength += sizeof(u8);
        }
        if ( HasOption(e_MaxMtCount) )
        {
            wLength += sizeof(u8);
        }
        if ( HasOption(e_MaxDirectCount) )
        {
            wLength += sizeof(u8);
        }
        if ( HasOption(e_Height) )
        {
            wLength += sizeof(u8);
        }
        if ( HasOption(e_ReservedPort) )
        {
            wLength += 2*sizeof(u16);
        }
		if ( HasOption(e_DcsId) )
        {
            wLength += sizeof(u8);
        }

        return wLength;
    }
}PACKED;


/*====================================================================
���� �� CConfBasicInfor
���� �� �������ݣ����������Ϣ
====================================================================*/
class CConfBasicInfor : public CKdvMcuDcsItem
{
public:
    // ��������
    s8 m_achConfName[64];
    // �Ƿ��������
    BOOL32 m_bHasPassword;
    // ��������
    s8 m_achConfPassword[64];
    // ���캯��
    CConfBasicInfor() : m_bHasPassword(FALSE)
    {
        memset(m_achConfName, 0, sizeof(m_achConfName));
        memset(m_achConfPassword, 0, sizeof(m_achConfPassword));
    }
protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(cNetData.S8Encode(64, m_achConfName));
        u8 byHasPassword = (u8)m_bHasPassword;
        CONDITION_RETURN(cNetData.U8Encode(1, &byHasPassword));
        if (m_bHasPassword)
        {
            CONDITION_RETURN(cNetData.S8Encode(64, m_achConfPassword));
        }
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(cNetData.S8Decode(64, m_achConfName));
        u8 byHasPassword;
        CONDITION_RETURN(cNetData.U8Decode(1, &byHasPassword));
        m_bHasPassword = (byHasPassword!=0);
		if (m_bHasPassword)
		{
			CONDITION_RETURN(cNetData.S8Decode(64, m_achConfPassword));
		}
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return ConfBasicInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        u16 wItemLength = sizeof(m_achConfName) + sizeof(u8);
        if (m_bHasPassword)
        {
            wItemLength += sizeof(m_achConfPassword);
        }
        return wItemLength;
    }
}PACKED;


/*====================================================================
���� �� CConfShortInfor
���� �� �������ݣ��������Ϣ
====================================================================*/
class CConfShortInfor : public CKdvMcuDcsItem
{
private:
    // ��ѡ����������ĳһλΪ1����ʾ�ÿ�ѡ����ڣ�0��ʾ������
        // ��һλ ---- ����λKB
        // �ڶ�λ ---- �Ƿ�����ն���������
    u8 m_byOptionField;

public:
    enum EOption
    {
        e_BandWidth   = 0x80>>0, // ����
        e_SupportJoin = 0x80>>1  // �Ƿ�����ն���������
    };

 	// ����λKB
    u32 m_dwBandWidth;
    // �Ƿ�����ն���������
    BOOL32 m_bSupportJoinedMt;

public:
    // ���캯��
    CConfShortInfor() :
        m_byOptionField(0), m_dwBandWidth(64), m_bSupportJoinedMt(FALSE)
    {
    }
    // �����ѡ��
    void IncludeOption(IN EOption emOption)
    {
        m_byOptionField |= emOption;
    }
    // �ж��Ƿ��п�ѡ��
    BOOL32 HasOption(IN EOption emOption) const
    {
        return ( (m_byOptionField&emOption) != 0 );
    }

protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        u8 byTempBool;
        CONDITION_RETURN(cNetData.U8Encode(1, &m_byOptionField));
        if ( HasOption(e_BandWidth) )
        {
            CONDITION_RETURN(cNetData.U32Encode(1, &m_dwBandWidth));
        }
        if ( HasOption(e_SupportJoin) )
        {
            byTempBool = (u8)m_bSupportJoinedMt;
            CONDITION_RETURN(cNetData.U8Encode(1, &byTempBool));
        }
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        u8 byTempBool;
        CONDITION_RETURN(cNetData.U8Decode(1, &m_byOptionField));
        if ( HasOption(e_BandWidth) )
        {
            CONDITION_RETURN(cNetData.U32Decode(1, &m_dwBandWidth));
        }
        if ( HasOption(e_SupportJoin) )
        {
            CONDITION_RETURN(cNetData.U8Decode(1, &byTempBool));
            m_bSupportJoinedMt = (byTempBool!=0);
        }
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return ConfShortInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        u16 wItemLength = sizeof(m_byOptionField);
        if ( HasOption(e_BandWidth) )
        {
            wItemLength += sizeof(m_dwBandWidth);
        }
        if ( HasOption(e_SupportJoin) )
        {
            wItemLength += sizeof(u8);
        }
        return wItemLength;
    }
}PACKED;


/*====================================================================
���� �� CMtShortInfor
���� �� �������ݣ��ն˼���Ϣ
====================================================================*/
class CMtShortInfor : public CKdvMcuDcsItem
{
public:
    enum EPositionType
    {
        // �¼��ڵ㣺�ȴ����ն���������
        e_Below_Joined,
        // �¼��ڵ㣺����������ն�
        e_Below_Invite,
        // �ϼ��ڵ㣺����������ն���ָ���Ļ���
        e_Above_Join,
        // �ϼ��ڵ㣺�����ն��������
        e_Above_Invited
    };
    // �ն��ڻ����е�λ������
    EPositionType m_emPositionType;
private:
    // ��ѡ����������ĳһλΪ1����ʾ�ÿ�ѡ����ڣ�0��ʾ������
        // ��һλ ---- �����ַ
        // �ڶ�λ ---- �ȴ����볬ʱ
        // ����λ ---- �ն��豸����
    u8 m_byOptionField;
public:
    // �ն�IP��ַ��e_Above_Join��Ч,��Ϊ�ϼ��ڵ��ַ����e_Below_Joined��Ч,��Ϊ��������У�顿
    u32 m_dwMtIp;
    // �ն˶˿ڡ�e_Above_Join��Ч,��Ϊ�ϼ��ڵ��ַ��
    u16 m_wMtPort;
    // �ȴ�ʱ�䣬��λ�롾e_WaitForJoin��Ч��
    u16 m_wTimeOut;

    enum EDeviceType
    {
        // T120Э���е�MCU
        e_Mcu,
        // T120Э���е�MT
        e_Mt,
        // T120Э���е�Terminal��δʹ�ã�
        e_Terminal
    };
    // �ն˵��豸����
    EDeviceType m_emDeviceType;

    CMtShortInfor() :
        m_emPositionType(e_Below_Joined), m_byOptionField(0),
        m_dwMtIp(0), m_wMtPort(0), m_wTimeOut(0), m_emDeviceType(e_Mt)
    {
    }
public:
    enum EOption
    {
        e_NodeAddress     = 0x80>>0, // �����ַ
        e_WaitJoinTimeout = 0x80>>1, // �ȴ����볬ʱ
        e_DeviceType      = 0x80>>2  // �ն��豸����
    };
    // �����ѡ��
    void IncludeOption(IN EOption emOption)
    {
        m_byOptionField |= emOption;
    }
    // �ж��Ƿ��п�ѡ��
    BOOL32 HasOption(IN EOption emOption) const
    {
        return ( (m_byOptionField&emOption) != 0 );
    }

protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        u8 byPositionType = (u8)m_emPositionType;
        CONDITION_RETURN(cNetData.U8Encode(1, &byPositionType));
        CONDITION_RETURN(cNetData.U8Encode(1, &m_byOptionField));

        if ( HasOption(e_NodeAddress) )
        {
            CONDITION_RETURN(cNetData.U32Encode(1, &m_dwMtIp));
            CONDITION_RETURN(cNetData.U16Encode(1, &m_wMtPort));
        }
        if ( HasOption(e_WaitJoinTimeout) )
        {
            CONDITION_RETURN(cNetData.U16Encode(1, &m_wTimeOut));
        }
        if ( HasOption(e_DeviceType) )
        {
            u8 byDeviceType = (u8)m_emDeviceType;
            CONDITION_RETURN(cNetData.U8Encode(1, &byDeviceType));
        }
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        u8 byPositionType;
        CONDITION_RETURN(cNetData.U8Decode(1, &byPositionType));
        m_emPositionType = (EPositionType)byPositionType;
        CONDITION_RETURN(cNetData.U8Decode(1, &m_byOptionField));

        if ( HasOption(e_NodeAddress) )
        {
            CONDITION_RETURN(cNetData.U32Decode(1, &m_dwMtIp));
            CONDITION_RETURN(cNetData.U16Decode(1, &m_wMtPort));
        }
        if ( HasOption(e_WaitJoinTimeout) )
        {
            CONDITION_RETURN(cNetData.U16Decode(1, &m_wTimeOut));
        }
        if ( HasOption(e_DeviceType) )
        {
            u8 byDeviceType;
            CONDITION_RETURN(cNetData.U8Decode(1, &byDeviceType));
            m_emDeviceType = (EDeviceType)byDeviceType;
        }
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return MtShortInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        u16 wItemLength = sizeof(u8) + sizeof(m_byOptionField);
        if ( HasOption(e_NodeAddress) )
        {
            wItemLength += sizeof(m_dwMtIp) + sizeof(m_wMtPort);
        }
        if ( HasOption(e_WaitJoinTimeout) )
        {
            wItemLength += sizeof(m_wTimeOut);
        }
        if ( HasOption(e_DeviceType) )
        {
            wItemLength += sizeof(u8);
        }
        return wItemLength;
    }
}PACKED;

/*====================================================================
���� �� CMcuMsstateInfor
���� �� �������ݣ�����MCU����ת��״̬��Ϣ
====================================================================*/
class CMcuMsstateInfor : public CKdvMcuDcsItem
{
public:
    BOOL32 m_bMcuMsstateInfo;

protected:
    // �����������ݱ���
    virtual BOOL32 ItemDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        u8 byMcuMsstateInfo = (u8)m_bMcuMsstateInfo;
        CONDITION_RETURN(cNetData.U8Encode(1, &byMcuMsstateInfo));
        return TRUE;
    }
    // �����������ݽ���
    virtual BOOL32 ItemDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        u8 byMcuMsstateinfo;
        CONDITION_RETURN(cNetData.U8Decode(1, &byMcuMsstateinfo));
        m_bMcuMsstateInfo = (byMcuMsstateinfo !=0 );
        return TRUE;
    }
    // �õ�������������
    virtual EItemType GetItemType() const
    {
        return McuMsstateInfor;
    }
    // �õ��������ݵ����ݵĳ���
    virtual u16 GetItemLength() const
    {
        return (sizeof(u8));
    }

}PACKED;


/*====================================================================
-- Part 5 : PDUʵ��
====================================================================*/

/*====================================================================
���� �� CDcsMcuRegReqPdu
���� �� DCS_MCU_REG_REQ����
====================================================================*/
class CDcsMcuRegReqPdu : public CMcuDcsPDU
{
public:
    // DCS��Ϣ
    CDcsInfor m_cDcsInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cDcsInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cDcsInfor.ItemEncode(cNetData);
    }
}PACKED;

/*====================================================================
���� �� CMcuDcsRegAckPdu
���� �� MCU_DCS_REG_ACK����
====================================================================*/
class CMcuDcsRegAckPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;


/*====================================================================
���� �� CMcuDcsRegNackPdu
���� �� MCU_DCS_REG_NACK����
====================================================================*/
class CMcuDcsRegNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;


/*====================================================================
���� �� CMcuDcsCreateConfReqPdu
���� �� MCU_DCS_CREATECONF_REQ����
====================================================================*/
class CMcuDcsCreateConfReqPdu : public CMcuDcsPDU
{
public:
    // ���������Ϣ
    CConfBasicInfor m_cConfBasicInfor;
    // �������Ϣ
    CConfShortInfor m_cConfShortInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(m_cConfBasicInfor.ItemDecode(cNetData));
        CONDITION_RETURN(m_cConfShortInfor.ItemDecode(cNetData));
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(m_cConfBasicInfor.ItemEncode(cNetData));
        CONDITION_RETURN(m_cConfShortInfor.ItemEncode(cNetData));
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuCreateConfAckPdu
���� �� DCS_MCU_CREATECONF_ACK����
====================================================================*/
class CDcsMcuCreateConfAckPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuCreateConfNackPdu
���� �� DCS_MCU_CREATECONF_NACK����
====================================================================*/
class CDcsMcuCreateConfNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;


/*====================================================================
���� �� CDcsMcuCreateConfNotifyPdu
���� �� DCS_MCU_CREATECONF_NOTIFY����
====================================================================*/
class CDcsMcuCreateConfNotifyPdu : public CMcuDcsPDU
{
public:
    // ���������Ϣ
    CConfBasicInfor m_cConfBasicInfor;
    // �������Ϣ
    CConfShortInfor m_cConfShortInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(m_cConfBasicInfor.ItemDecode(cNetData));
        CONDITION_RETURN(m_cConfShortInfor.ItemDecode(cNetData));
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(m_cConfBasicInfor.ItemEncode(cNetData));
        CONDITION_RETURN(m_cConfShortInfor.ItemEncode(cNetData));
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CMcuDcsReleaseConfReqPdu
���� �� MCU_DCS_RELEASECONF_REQ����
====================================================================*/
class CMcuDcsReleaseConfReqPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuReleaseConfAckPdu
���� �� DCS_MCU_RELEASECONF_ACK����
====================================================================*/
class CDcsMcuReleaseConfAckPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuReleaseConfNackPdu
���� �� DCS_MCU_RELEASECONF_NACK����
====================================================================*/
class CDcsMcuReleaseConfNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;


/*====================================================================
���� �� CDcsMcuReleaseConfNotifyPdu
���� �� DCS_MCU_RELEASECONF_NOTIFY����
====================================================================*/
class CDcsMcuReleaseConfNotifyPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CMcuDcsAddMtReqPdu
���� �� MCU_DCS_ADDMT_REQ����
====================================================================*/
class CMcuDcsAddMtReqPdu : public CMcuDcsPDU
{
public:
    // �ն˼���Ϣ
    CMtShortInfor m_cMtShortInfor;
    // �������Ϣ�����ն�����Ϊe_Above_Joinʱ��Ч��
    CConfBasicInfor m_cConfBasicInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(m_cMtShortInfor.ItemDecode(cNetData));
        if (m_cMtShortInfor.m_emPositionType == CMtShortInfor::e_Above_Join)
        {
            CONDITION_RETURN(m_cConfBasicInfor.ItemDecode(cNetData));
        }
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(m_cMtShortInfor.ItemEncode(cNetData));
        if (m_cMtShortInfor.m_emPositionType == CMtShortInfor::e_Above_Join)
        {
            CONDITION_RETURN(m_cConfBasicInfor.ItemEncode(cNetData));
        }
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuAddMtAckPdu
���� �� DCS_MCU_ADDMT_ACK����
====================================================================*/
class CDcsMcuAddMtAckPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuAddMtNackPdu
���� �� DCS_MCU_ADDMT_NACK����
====================================================================*/
class CDcsMcuAddMtNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;



/*====================================================================
���� �� CMcuDcsDelMtReqPdu
���� �� MCU_DCS_DELMT_REQ����
====================================================================*/
class CMcuDcsDelMtReqPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuDelMtAckPdu
���� �� DCS_MCU_DELMT_ACK����
====================================================================*/
class CDcsMcuDelMtAckPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;

/*====================================================================
���� �� CDcsMcuDelMtNackPdu
���� �� DCS_MCU_DELMT_NACK����
====================================================================*/
class CDcsMcuDelMtNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;


/*====================================================================
���� �� CDcsMcuMtMtOnlineNotifyPdu
���� �� DCS_MCU_MT_ONLINE_NOTIFY����
====================================================================*/
class CDcsMcuMtMtOnlineNotifyPdu : public CMcuDcsPDU
{
public:
    // �ն˼���Ϣ
    CMtShortInfor m_cMtShortInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        CONDITION_RETURN(m_cMtShortInfor.ItemDecode(cNetData));
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        CONDITION_RETURN(m_cMtShortInfor.ItemEncode(cNetData));
        return TRUE;
    }
}PACKED;


/*====================================================================
���� �� CDcsMcuMtMtOfflineNotifyPdu
���� �� DCS_MCU_MT_OFFLINE_NOTIFY����
====================================================================*/
class CDcsMcuMtMtOfflineNotifyPdu : public CMcuDcsPDU
{
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return TRUE;
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return TRUE;
    }
}PACKED;


/*====================================================================
���� �� CDcsMcuGetmsstatusReqPdu
���� �� DCS_MCU_GETMSSTATUS_REQ����
====================================================================*/
class CDcsMcuGetmsstatusReqPdu : public CMcuDcsPDU
{
public:
    // DCS��Ϣ
    CDcsInfor m_cDcsInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cDcsInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cDcsInfor.ItemEncode(cNetData);
    }
}PACKED;


/*====================================================================
���� �� CMcuDcsGetmsstatusAckPdu
���� �� MCU_DCS_GETMSSTATUS_ACK����
====================================================================*/
class CMcuDcsGetmsstatusAckPdu : public CMcuDcsPDU
{
public:
    //����MCU����ת��״̬��Ϣ
    CMcuMsstateInfor m_cMcuMsstate;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cMcuMsstate.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cMcuMsstate.ItemEncode(cNetData);
    }
}PACKED;

/*====================================================================
���� �� CMcuDcsGetmsstatusNackPdu
���� �� MCU_DCS_GETMSSTATUS_NACK����
====================================================================*/
class CMcuDcsGetmsstatusNackPdu : public CMcuDcsPDU
{
public:
    // ������Ϣ
    CErrorInfor m_cErrorInfor;
protected:
    // ���������ݵõ���PDU
    virtual BOOL32 PduDataDecode(IN_OUT CKdvMcuDcsNetData& cNetData)
    {
        return m_cErrorInfor.ItemDecode(cNetData);
    }
    // �ѱ�PDU����Ϊ��������
    virtual BOOL32 PduDataEncode(IN_OUT CKdvMcuDcsNetData& cNetData) const
    {
        return m_cErrorInfor.ItemEncode(cNetData);
    }
}PACKED;


#ifdef WIN32
    #pragma pack( pop )
#endif

#endif  // _MCU_DCS_PDU_H_
