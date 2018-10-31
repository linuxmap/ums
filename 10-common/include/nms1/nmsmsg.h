/*=============================================================================
ģ   ��   ��: ���ܷ�����
��   ��   ��: nmsmsg.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: ��Ϣ��
��        ��: wjr
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2003/06/13  2.0     wjr         ����
2003/10/13  3.0     wjr         �޸�
2005/11/07  4.0     ���        ����淶��
=============================================================================*/

#ifndef __NMSMSG_H__20030613
#define __NMSMSG_H__20030613

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WINSOCK2API_
#pragma comment(lib, "ws2_32.lib")
#endif

static u32 g_dwSerialNo = 1;    // ��ˮ��

const s32 g_cnBufLen = 1024 * 2 + 16;
typedef struct tagTNmsMsgHead
{
    tagTNmsMsgHead()
    {
        ZeroMemory( this, sizeof (tagTNmsMsgHead) );
    }

    u32	m_dwSerialNo;	// ��ˮ��, ������
    u16	m_wEventID;		// �¼����, ������
    u16	m_wObjectType;	// ��������, ������
    u32	m_dwObjectID;	// ������, ������
    u32	m_dwTargetID;	// �������ṩ���û�-���ϵ����֪ͨ, ������
    u32	m_dwErrorCode;	// ������, ������
    u16	m_wTimeout;		// ��ʱʱ�䳤��--��λΪ��, ������
    u16	m_wMsgLength;	// ��Ϣ���ݳ���, ������
} TNmsMsgHead, *PTNmsMsgHead;

#define MSG_BODY_OFFSET     sizeof(TNmsMsgHead) // ��ϢͷΪ16���ӽ�

// ����ģ����Ϣ��
class CNmsMsg
{
protected:
    u8 m_byContent[g_cnBufLen];	// ��Ϣ��������1k��С

public:
    CNmsMsg(LPVOID pbyMsgBody = NULL, u16 wBodyLen = 0)
    {
        ::ZeroMemory( m_byContent, g_cnBufLen );
        PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
        if ( pbyMsgBody != NULL && wBodyLen != 0 )
        {
            ::CopyMemory( &m_byContent[MSG_BODY_OFFSET], pbyMsgBody, wBodyLen );
            m_ptMsgHead->m_wMsgLength = htons( wBodyLen );
        }
        m_ptMsgHead->m_dwSerialNo = htonl( g_dwSerialNo ++ );
        m_ptMsgHead->m_wTimeout = htons( 1 );
    }
    CNmsMsg& operator= (const CNmsMsg &cMsg)
    {
    	::CopyMemory( m_byContent, cMsg.m_byContent, g_cnBufLen );
    	return (*this);
    }

	~CNmsMsg() {}

public:

    /*=============================================================================
    �� �� ��:ClearMsgHead
    ��    ��:�����Ϣͷ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
    void ClearMsgHead(void)
    {
        ::ZeroMemory( m_byContent, MSG_BODY_OFFSET );
    }

    /*=============================================================================
    �� �� ��:ClearMsgBody
    ��    ��:�����Ϣ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
    void ClearMsgBody(void)
    {
        ::ZeroMemory( &m_byContent[MSG_BODY_OFFSET],
                      g_cnBufLen - MSG_BODY_OFFSET );
    }

    /*=============================================================================
    �� �� ��:ClearContent
    ��    ��:�����Ϣȫ������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
    void ClearContent(void)
    {
		::ZeroMemory( m_byContent, g_cnBufLen );
    }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡ��ˮ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��ˮ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
    u32 GetSerialNo(void) const
    {
        PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohl( m_ptMsgHead->m_dwSerialNo );
	}

    /*=============================================================================
    �� �� ��:SetSerialNo
    ��    ��:���õ�ǰ��Ϣ����ˮ��
    ��    ��:u32 dwSerialNo                 [in]    ��ǰ����ˮ��
    ע    ��:�÷���һ�㲻ʹ��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetSerialNo(u32 dwSerialNo)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead != NULL )
		{
			m_ptMsgHead->m_dwSerialNo = htonl( dwSerialNo );
		}
	}

    /*=============================================================================
    �� �� ��:SetSerialNo
    ��    ��:������Ϣ����ˮ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetSerialNo(void)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead != NULL )
		{
			m_ptMsgHead->m_dwSerialNo = htonl( g_dwSerialNo ++ );
		}
	}

    /*=============================================================================
    �� �� ��:GetObjectID
    ��    ��:��ȡ������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u32 GetObjectID(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohl( m_ptMsgHead->m_dwObjectID );
	}

    /*=============================================================================
    �� �� ��:GetObjectType
    ��    ��:��ȡ��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u16 GetObjectType(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohs( m_ptMsgHead->m_wObjectType );
	}

    /*=============================================================================
    �� �� ��:GetTargetID
    ��    ��:��ȡĿ�Ķ�����
    ��    ��:��
    ע    ��:�ú������������û����ϵ������¼���
             ����������û�����Ŀ�Ķ��������
             ����Ŀ�Ķ�������û�
    �� �� ֵ:������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u32 GetTargetID(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohl( m_ptMsgHead->m_dwTargetID );
	}

    /*=============================================================================
    �� �� ��:SetObject
    ��    ��:����Ŀ�Ķ���
    ��    ��:u32 dwObjectID                 [in]    ������Ϣ�Ķ�����
             u16 wObjectType                [in]    ������Ϣ�Ķ�������
             u32 dwTargetID                 [in]    ������Ϣ�Ķ�������Ķ�����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetObject(u32 dwObjectID, u16 wObjectType = 0, u32 dwTargetID = -1)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return;
		m_ptMsgHead->m_wObjectType = htons( wObjectType );
		m_ptMsgHead->m_dwObjectID = htonl( dwObjectID );
		m_ptMsgHead->m_dwTargetID = htonl( dwTargetID );
	}

    /*=============================================================================
    �� �� ��:SetErrorCode
    ��    ��:���ô�����
    ��    ��:u32 dwErrorCode                [in]    ������Ϣ�Ĵ�����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetErrorCode(u32 dwErrorCode)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return;
		m_ptMsgHead->m_dwErrorCode = htonl( dwErrorCode);
	}

    /*=============================================================================
    �� �� ��:GetErrorCode
    ��    ��:��ȡ������Ϣ�Ĵ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u32 GetErrorCode(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return (u32)~0;
		return ntohl( m_ptMsgHead->m_dwErrorCode );
	}

    /*=============================================================================
    �� �� ��:SetEventId
    ��    ��:�����¼����
    ��    ��:u16 wEventId                   [in]    ������Ϣ���¼�
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetEventId(u16 wEventId)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return;
		m_ptMsgHead->m_wEventID = htons( wEventId );
	}

    /*=============================================================================
    �� �� ��:GetEventId
    ��    ��:��ȡ�¼�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�¼���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u16 GetEventId(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohs( m_ptMsgHead->m_wEventID );
	}

    /*=============================================================================
    �� �� ��:SetMsgBody
    ��    ��:������Ϣ������
    ��    ��:LPVOID pbyMsgBody              [in]    ������Ϣ������
             u16 wBodyLen                   [in]    ������Ϣ�����ݳ���
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetMsgBody(LPVOID pbyMsgBody, u16 wBodyLen)
	{
		if ( pbyMsgBody != NULL && wBodyLen > 0 )
		{
			PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
			if ( m_ptMsgHead == NULL )
				return;
			::CopyMemory( &m_byContent[MSG_BODY_OFFSET], pbyMsgBody, wBodyLen );
			m_ptMsgHead->m_wMsgLength = htons( wBodyLen );
		}
	}

    /*=============================================================================
    �� �� ��:CatMsgBody
    ��    ��:�����Ϣ����
    ��    ��:LPVOID pbyMsgBody              [in]    ������Ϣ������
             u16 wBodyLen                   [in]    ������Ϣ�����ݳ���
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void CatMsgBody(LPVOID pbyMsgBody, u16 wBodyLen)
	{
		if ( pbyMsgBody != NULL && wBodyLen > 0) 
		{
			PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
			if ( m_ptMsgHead == NULL )
				return;
            s32 nOffset = MSG_BODY_OFFSET + ntohs( m_ptMsgHead->m_wMsgLength );
			::CopyMemory( m_byContent + nOffset, pbyMsgBody, wBodyLen );
			m_ptMsgHead->m_wMsgLength += htons( wBodyLen );
		}
	}

    /*=============================================================================
    �� �� ��:GetMsgBody
    ��    ��:��ȡ��Ϣ����
    ��    ��:LPVOID pbyMsgBody              [out]   ��ȡ�õ�����Ϣ����
             u16 wBodyLen                   [in]    ��Ϣ�ĳ���
             u16 wOffset                    [in]    ��Ϣ��ƫ��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u16 GetMsgBody(LPVOID pbyMsgBody, u16 wBodyLen, u16 wOffset = 0)
	{
		if ( pbyMsgBody == NULL )
		{
			return 0;
		}
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		u16 wLen = __min( wBodyLen, ntohs( m_ptMsgHead->m_wMsgLength ) );
		::CopyMemory( pbyMsgBody, m_byContent + MSG_BODY_OFFSET + wOffset, wLen );
		return wLen;
	}

    /*=============================================================================
    �� �� ��:GetMsgBody
    ��    ��:��ȡ��Ϣ����
    ��    ��:u16 wOffset                    [in]    ��Ϣ��ƫ��
    ע    ��:ֱ�ӷ�����Ϣ����ָ��
    �� �� ֵ:��Ϣ����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	LPVOID GetMsgBody(u16 wOffset = 0) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return NULL;
		if ( m_ptMsgHead->m_wMsgLength == 0 )
			return NULL;
		return (LPVOID)(m_byContent + MSG_BODY_OFFSET + wOffset);
	}

    /*=============================================================================
    �� �� ��:GetMsgBodyLen
    ��    ��:��ȡ��Ϣ��ĳ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��Ϣ��ĳ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u16 GetMsgBodyLen(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohs( m_ptMsgHead->m_wMsgLength );
	}

    /*=============================================================================
    �� �� ��:SetTimeout
    ��    ��:���ö�ʱʱ��
    ��    ��:u16 wTimeout                   [in]    ��ʱ��ʱ�䳤��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	void SetTimeout(u16 wTimeout)
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return;
		m_ptMsgHead->m_wTimeout = htons( wTimeout );
	}

    /*=============================================================================
    �� �� ��:GetTimeout
    ��    ��:��ȡ��ʱ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��ʱ����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2003/10/23  2.0     wjr     ����
    =============================================================================*/
	u16 GetTimeout(void) const
	{
		PTNmsMsgHead m_ptMsgHead = (PTNmsMsgHead)m_byContent;
		if ( m_ptMsgHead == NULL )
			return 0;
		return ntohs( m_ptMsgHead->m_wTimeout );
	}
};


#endif // __NMSMSG_H__20030613
