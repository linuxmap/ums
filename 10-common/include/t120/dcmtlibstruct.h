/*****************************************************************************
ģ����      : DcMtLib
�ļ���      : dcmtlibstruct.h
����ļ�    : dcmtlibstruct.cpp
�ļ�ʵ�ֹ���: dcmtlib�ṹ����
����		: chenhongbin
�汾        : V1.0
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾     �޸���             �޸�����
2005/05/24  1.0      chenhongbin         ����
******************************************************************************/
#ifndef _DCMTLIBSTRUCT_H
#define _DCMTLIBSTRUCT_H

#include"kdvtype.h"
#include "ptlib.h"

#ifdef _WIN32
#pragma pack( push )
#pragma pack( 1 )
#endif

typedef u32 NodeID; //�ڵ�ID
typedef s32 ChannelId;
typedef s32 StaticChannelId;
typedef s32 DynamicChannelId;

//#define ENABLE_DCMTLIB_LOG
/*====================================================================
// ��ӡ��־ �궨��
=====================================================================*/
#ifdef ENABLE_DCMTLIB_LOG
    #define DCMTLIB_LOG(format, para1, para2, para3)\
        { \
            CHAR anBuf[1024]; \
	        sprintf(anBuf, ".\\T120_LOG\\%ld_%ld.log", GetCurrentProcessId(), GetCurrentThreadId()); \
            HANDLE handleFile = CreateFile(anBuf, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); \
            if (handleFile != NULL) \
            { \
                SetFilePointer(handleFile, NULL, NULL, FILE_END); \
                DWORD dwRcv; \
                SYSTEMTIME tSystime; \
                GetLocalTime(&tSystime); \
                CHAR anFormat[256]; \
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] DCMTLIB: %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat, para1, para2, para3); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }

    #define DCMTLIB_LOG_DEFAULT(format)\
        { \
            CHAR anBuf[1024]; \
	        sprintf(anBuf, ".\\T120_LOG\\%ld_%ld.log", GetCurrentProcessId(), GetCurrentThreadId()); \
            HANDLE handleFile = CreateFile(anBuf, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); \
            if (handleFile != NULL) \
            { \
                SetFilePointer(handleFile, NULL, NULL, FILE_END); \
                DWORD dwRcv; \
                SYSTEMTIME tSystime; \
                GetLocalTime(&tSystime); \
                CHAR anFormat[256]; \
                sprintf(anFormat, "[%2.2d:%2.2d:%2.2d:%3.3d] DCMTLIB: %s\r\n", tSystime.wHour, tSystime.wMinute, tSystime.wSecond, tSystime.wMilliseconds, format); \
                sprintf(anBuf, anFormat); \
                WriteFile(handleFile, anBuf, strlen(anBuf), &dwRcv, NULL); \
                CloseHandle(handleFile); \
            } \
        }
#else
    #define DCMTLIB_LOG(format, para1, para2, para3)
    #define DCMTLIB_LOG_DEFAULT(format)
#endif

//����Զ�̿��ƻظ�
enum ERcConfirmType
{
    e_ConfirmSuccuss,          // 0 ��ʾ��ȷ�ϡ����Զ����տ�������
    e_ConfirmUnexpected,       // 1 δʹ��
    e_ConfirmAlwaysRefused,    // 2 ��ʾ�����ڲ����ܿ�������
    e_ConfirmRefused,          // 3 ��ʾ���ܾ���
    e_ConfirmForbidden         // 4 ��ʾ Disable RC
};

//�ն˲��ܷ����Ӧ��
typedef enum
{
    e_AppShareDisable = 0x0a,        //���ܷ�����
    e_AppWhiteboardDisable = 0x28,   //���ܷ���װ�
    e_AppFileTransDisable = 0x49,    //���ܷ����ļ�����
    e_AppChatDisable = 0x18,         //���ܷ�������
    e_AppAllAllowed = 0x08,          //�ܷ�������Ӧ��
    e_AppAllDisable = 0x7b,          //���ܷ�������Ӧ��
}EAppDisable;

//������Ӧ���
typedef enum 
{
	e_CrSuccess,
	e_CrUserRejected,
	e_CrResourcesNotAvaiable,
	e_CrRejectedForSymmetryBreaking,
	e_CrLockedConferenceNotSupported,
	e_CrInvalidConference,
	e_CrInvalidPassword,
	e_CrInvalidConvenerPassword,
	e_CrChallengeResponseRequired,
	e_CrInvalidChallengeResponse
} EConferenceResponseResult;

//�ڵ�����
typedef enum 
{
	e_NtTerminal		= 0,
	e_NtMultipointTerminal	= 1,
	e_NtMCU			= 2
} ENodeType;

//�߳��û�ԭ��
typedef enum 
{
	e_UserInitiated,
	e_HigherNodeDisconnected,
	e_NodeEjected
} EEjectUserReason;

//�߳��û����
typedef enum 
{
	e_EuSuccess,
	e_EuInvalidRequester,
	e_EuInvalidNode
} EEjectUserResult;

//���Ľڵ�λ��
typedef enum
{
	e_CNPSelf,
	e_CNPLocal,
	e_CNPRemote
} EConfNodePos;

//�������ԭ��
typedef enum 
{
	e_CtUserInitiated,
	e_CtTimedConference
} EConferenceTerminateReason;

//�ڵ���Ϣ�ṹ
struct TNodeInfo
{
    PString m_strNodeIp;        //�ڵ�Ip
    PString m_strNodeAlias;     //�ڵ����
    PString m_strNodeEmail;     //�ڵ�E-mail
    PString m_strNodeLocation;  //�ڵ�λ��
    PString m_strNodePhone;     //�ڵ�绰
    u16     m_wNodePort;        //�ڵ�Ķ˿�
};

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 23 ������Ҫ�ڽ��ն˱��������г�
#define WINDOW_FLAG_TAGGABLE    0x00800000L
// 7 �����Ƿ���С��
#define WINDOW_FLAG_MINIMIZED   0x00000080L
// 5 �����Ƿ���Ӧ�õĴ���
#define WINDOW_FLAG_HOSTED      0x00000020L
// 3 �����Ƿ��ڸǹ���Ӧ�õı��طǹ���Ӧ�ô���
#define WINDOW_FLAG_LOCAL       0x00000008L

/*====================================================================
�ṹ �� TAppShareWindow
���� �� Ӧ�ù����ڽṹ
====================================================================*/
struct TAppShareWindow
{
    //����ID
    s32     m_nWindowID;
    //�������ڽ���ID
    s32     m_nWindowExtra;
    //������ID
    s32     m_nWindowOwner;
    //������Ļ����
    u16    m_wLeft;
    //������Ļ����
    u16    m_wTop; 
    //������Ļ����
    u16    m_wRight; 
    //������Ļ����
    u16    m_wBottom; 
    //���ڱ��ⳤ��
    u16    m_wWindowTitleLength;
    //���ڱ���
    char    m_chWindowTitle[50]; 
private:
    //���ڱ�־
    s32     m_nWindowFlags;

public:
    TAppShareWindow()
    {
        m_nWindowID = 0;
        m_nWindowExtra = 0;
        m_nWindowOwner = 0;
        m_nWindowFlags = 0;
        m_wLeft = 0;
        m_wTop = 0;
        m_wRight = 0;
        m_wBottom = 0;
        m_wWindowTitleLength = 0;
        memset( m_chWindowTitle , 0 , sizeof(m_chWindowTitle) );
    };

    void SetWindowTitle(const char* szWindowTitle,u16 wTitleLen)
    {
        if(wTitleLen > sizeof(m_chWindowTitle))
        {
            strncpy(m_chWindowTitle,szWindowTitle,sizeof(m_chWindowTitle));

            if(m_chWindowTitle[48] > 0x8F)
            {
                m_chWindowTitle[48] = '\0';
                m_wWindowTitleLength = 48;
            }
            else
            {
                m_chWindowTitle[49] = '\0';
                m_wWindowTitleLength = 49;
            }
        }
        else
        {
            strncpy(m_chWindowTitle,szWindowTitle,wTitleLen);
            m_wWindowTitleLength = wTitleLen;
        }
    }
    TAppShareWindow( const TAppShareWindow& window )
    {
        m_nWindowID = window.m_nWindowID;
        m_nWindowExtra = window.m_nWindowExtra;
        m_nWindowOwner = window.m_nWindowOwner;
        m_nWindowFlags = window.m_nWindowFlags;
        m_wLeft = window.m_wLeft;
        m_wTop = window.m_wTop;
        m_wRight = window.m_wRight;
        m_wBottom = window.m_wBottom;
        m_wWindowTitleLength = window.m_wWindowTitleLength;
        memcpy( m_chWindowTitle , window.m_chWindowTitle , sizeof(m_chWindowTitle) );
    };
    TAppShareWindow& operator= ( const TAppShareWindow& window )
    {
        if( &window != this )
        {
            m_nWindowID = window.m_nWindowID;
            m_nWindowExtra = window.m_nWindowExtra;
            m_nWindowOwner = window.m_nWindowOwner;
            m_nWindowFlags = window.m_nWindowFlags;
            m_wLeft = window.m_wLeft;
            m_wTop = window.m_wTop;
            m_wRight = window.m_wRight;
            m_wBottom = window.m_wBottom;
            m_wWindowTitleLength = window.m_wWindowTitleLength;
            memcpy( m_chWindowTitle , window.m_chWindowTitle , sizeof(m_chWindowTitle) );
        }
        return *this;
    };

    bool operator==(const TAppShareWindow& window) const
    {
        if( m_nWindowID   != window.m_nWindowID)
//        || m_nWindowExtra != window.m_nWindowExtra
//        || m_nWindowOwner != window.m_nWindowOwner
//        || m_nWindowFlags != window.m_nWindowFlags
//        || m_wLeft        != window.m_wLeft
//        || m_wTop         != window.m_wTop
//        || m_wRight       != window.m_wRight
//        || m_wBottom      != window.m_wBottom
//        || m_wWindowTitleLength != window.m_wWindowTitleLength)
        {
            return false;
        }

        return true;
    };

    //���ò�ѯ�����Ƿ���Ҫ�г�
    void SetWindowTaggable( )
    {
        m_nWindowFlags |= WINDOW_FLAG_TAGGABLE;
    };
    void ResetWindowTaggable( )
    {
        m_nWindowFlags &= ~WINDOW_FLAG_TAGGABLE;
    };
    bool IsWindowTaggable( )
    {
        return ( ( m_nWindowFlags & WINDOW_FLAG_TAGGABLE ) != 0 ? true : false );
    };

    //���ò�ѯ�����Ƿ���С��
    void SetWindowMinimized( )
    {
        m_nWindowFlags |= WINDOW_FLAG_MINIMIZED;
    };
    void ResetWindowMinimized( )
    {
        m_nWindowFlags &= ~WINDOW_FLAG_MINIMIZED;
    };
    bool IsWindowMinimized( )
    {
        return ( ( m_nWindowFlags & WINDOW_FLAG_MINIMIZED ) != 0 ? true : false );
    };

    //���ò�ѯ�����Ƿ�����
    void SetWindowHosted( )
    {
        m_nWindowFlags |= WINDOW_FLAG_HOSTED;
    };
    void ResetWindowHosted( )
    {
        m_nWindowFlags &= ~WINDOW_FLAG_HOSTED;
    };
    bool IsWindowHosted( )
    {
        return ( ( m_nWindowFlags & WINDOW_FLAG_HOSTED ) != 0 ? true : false );
    };

    //���ò�ѯ�����Ƿ񱾵طǹ�����
    void SetWindowLocal( )
    {
        m_nWindowFlags |= WINDOW_FLAG_LOCAL;
    };
    void ResetWindowLocal( )
    {
        m_nWindowFlags &= ~WINDOW_FLAG_LOCAL;
    };
    bool IsWindowLocal( )
    {
        return ( ( m_nWindowFlags & WINDOW_FLAG_LOCAL ) != 0 ? true : false );
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TAppShareColorPointer
���� �� �����ϵͳ���ṹ
====================================================================*/
struct TAppShareColorPointer
{
    //��ϵͳ��껺������
    u16 m_wCacheIndex; 
    //��ϵͳ��������ȵ�����
    u16 m_wHotSpotX; 
    //��ϵͳ��������ȵ�����
    u16 m_wHotSpotY; 
    //��ϵͳ���������
    u16 m_wWidth; 
    //��ϵͳ�������߶�
    u16 m_wHeight; 
    u16 m_wAndMaskLength;
    u16 m_wXorMaskLength;
    u8* m_pbyMask;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TStillImageColorRGB
���� �� ���Ӱװ���ɫ
====================================================================*/
struct TStillImageColorRGB
{
    u8 m_byRed;
    u8 m_byGreen;
    u8 m_byBlue;

    TStillImageColorRGB()
    {
        m_byRed = 0;
        m_byGreen = 0;
        m_byBlue = 255;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TStillImagePoint
���� �� ���Ӱװ�ָʾ��
====================================================================*/
struct TStillImagePoint
{
    s32 m_nPointX;
    s32 m_nPointY;

    TStillImagePoint()
    {
        m_nPointX = 0;
        m_nPointY = 0;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TStillImageBitmap
���� �� ���Ӱװ�ָͼƬ
====================================================================*/
struct TStillImageBitmap
{
    //BMP���(RegisterAllocateHandle����)
    s32     m_nBitmapHandle;
    //��������(RegisterAllocateHandle����)
    s32     m_nWorkspaceHandle;
    //ƽ��ID(ֵΪ1)
    u8    m_byPlaneID;

    //��ͼ״̬(�Ƿ�ѡ��)
    enum ViewState
    {
        e_unselected,
        e_selected,
        e_hidden
    };
    ViewState m_enumViewState;

    //��ָ��ƽ���Z�����λ��
    enum ZOrder
    {
        e_front,
        e_back
    };
    ZOrder m_enumZOrder;

    //BMP���Ͻ������
    TStillImagePoint  m_tAnchorPoint;

    //BMP���
    s32     m_nBitmapWidth;
    //BMP�߶�
    s32     m_nBitmapHeight;
    
    //�Ƿ��к���BMP����
    bool    m_bMoreToFollow;

    //BMP���ݼ�����
    s32     m_nBitmapDataLength;
    u8*   m_pbyBitmapData;

    TStillImageBitmap()
    {
        m_enumViewState = e_selected;
        m_enumZOrder = e_front;
        m_pbyBitmapData = NULL;
        m_nBitmapDataLength = 0;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TStillImageDrawing
���� �� ���Ӱװ�ָ��ͼ����
====================================================================*/
struct TStillImageDrawing
{
    //ͼ�ξ��(RegisterAllocateHandle����)
    s32     m_nDrawingHandle;
    //��������(RegisterAllocateHandle����)
    s32     m_nWorkspaceHandle;
    //ƽ��ID(ֵΪ1)
    u8    m_byPlaneID;
    
    //ͼ����״
    enum DrawingType
    {
        e_point,        // ��
        e_openPolyLine, // ��������
        e_closedPolyLine, //�������
        e_rectangle,    //����
        e_ellipse       //��Բ
    };
    DrawingType    m_enumDrawingType;

    //Pen��ɫ
    TStillImageColorRGB m_tPenColor;
    //�Ƿ���Ҫ�������ɫ
    bool    m_bFilled;
    //�����ɫ
    TStillImageColorRGB m_tFillColor;
    //Pen���(3--16)
    u8    m_byPenThickness;

    //Pen�ʼ���״
    enum PenNib
    {
        e_circular,
        e_square
    };
    PenNib  m_enumPenNib;

    //����״
    enum LineStyle
    {
        e_solid,
        e_dashed,
        e_dotted,
        e_dash_dot,
        e_dash_dot_dot,
        e_two_tone
    };
    LineStyle   m_enumLineStyle;

    //�Ƿ������ʾ
    bool    m_bHighlight;

    //��ͼ״̬(�Ƿ�ѡ��)
    enum ViewState
    {
        e_unselected,
        e_selected,
        e_hidden
    };
    ViewState   m_enumViewState;

    //��ָ��ƽ���Z�����λ��
    enum ZOrder
    {
        e_front,
        e_back
    };
    ZOrder  m_enumZOrder;

    //ͼ�ε�һ���������
    TStillImagePoint  m_tAnchorPoint;

    //ͼ�ε㼯��������
    s32 m_nDrawingPointsNum;
    TStillImagePoint* m_ptDrawingPoints;

    TStillImageDrawing()
    {
        m_enumDrawingType = e_openPolyLine;
        m_byPenThickness = 3;
        m_enumPenNib = e_circular;
        m_enumLineStyle = e_solid;
        m_bHighlight = false;
        m_enumViewState = e_selected;
        m_enumZOrder = e_front;
        m_bFilled = false;
		m_nDrawingPointsNum = 0;
		m_ptDrawingPoints = NULL;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#define SI_LF_FACESIZE 32

/*====================================================================
�ṹ �� TStillImageLogfont
���� �� ���Ӱװ�����,��Ӧ��Windows����ṹLOGFONT
====================================================================*/
struct TStillImageLogfont
{
    long m_lfHeight; 
    long m_lfWidth; 
    long m_lfEscapement; 
    long m_lfOrientation; 
    long m_lfWeight; 
    u8 m_lfItalic; 
    u8 m_lfUnderline; 
    u8 m_lfStrikeOut; 
    u8 m_lfCharSet; 
    u8 m_lfOutPrecision; 
    u8 m_lfClipPrecision; 
    u8 m_lfQuality; 
    u8 m_lfPitchAndFamily; 
    char m_lfFaceName[SI_LF_FACESIZE];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*====================================================================
�ṹ �� TStillImageText
���� �� ���Ӱװ��ı�
====================================================================*/
struct TStillImageText
{
    //���־��(RegisterAllocateHandle����)
    s32     m_nTextHandle;
    //��������
    s32     m_nWorkspaceHandle;
    //ƽ��ID(ֵΪ1)
    u8    m_byPlaneID;

    //������ɫ
    TStillImageColorRGB m_tTextColor;
    //���ֺ�ɫ
    TStillImageColorRGB m_tTextBackColor;

    //��ͼ״̬(�Ƿ�ѡ��)
    enum ViewState
    {
        e_unselected,
        e_selected,
        e_hidden
    };
    ViewState   m_enumViewState;

    //��ָ��ƽ���Z�����λ��
    enum ZOrder
    {
        e_front,
        e_back
    };
    ZOrder  m_enumZOrder;

    //�������Ͻ������
    TStillImagePoint m_tAnchorPoint;

    //��������
    TStillImageLogfont m_tLogFont;

    //�������ݼ�����
    s32 m_nTextDataLength;
    u8* m_pbyTextData;

    TStillImageText()
    {
        m_nTextHandle = 0;
        m_nWorkspaceHandle = 0;
        m_byPlaneID = 1;
        m_tTextColor.m_byRed = 0;
        m_tTextColor.m_byGreen = 0;
        m_tTextColor.m_byBlue = 0;
        m_tTextBackColor.m_byRed = 0xff;
        m_tTextBackColor.m_byGreen = 0xff;
        m_tTextBackColor.m_byBlue = 0xff;
        m_enumViewState = e_selected;
        m_enumZOrder = e_front;
        m_pbyTextData = NULL;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*====================================================================
�ṹ �� TStillImagePlaneParameter
���� �� ���Ӱװ�ƽ̨�ṹ
====================================================================*/
struct TStillImagePlaneParameter
{
    //ƽ��ID(ֵΪ0,1,2)
    u8    m_byPlaneID;
    //�Ƿ�ɱ༭
    bool    m_bEditable;
    //�Ƿ�֧��ע��
    bool    m_bAnnotation;
    //�Ƿ�֧��ͼ��
    bool    m_bImage;
    //�Ƿ����Ʊ���
    bool    m_bProtected;

    TStillImagePlaneParameter()
    {
        m_byPlaneID = 1;
        m_bEditable = true;
        m_bAnnotation = true;
        m_bImage = true;
        m_bProtected = false;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*====================================================================
�ṹ �� TStillImageViewParameter
���� �� ���Ӱװ���ͼ�ṹ
====================================================================*/
struct TStillImageViewParameter
{
    //��ͼ���(RegisterAllocateHandle����)
    s32     m_nViewHandle;

    //��ͼ״̬(�Ƿ񽹵���ͼ)
    enum ViewState
    {
        e_hidden,
        e_background,
        e_foreground,
        e_focus
    };
    ViewState   m_enumViewState;

    //��ͼ�Ƿ�����(false��ʾ������)
    bool    m_bUpdatesEnabled;

    TStillImageViewParameter()
    {
        m_nViewHandle = 0;
        m_enumViewState = e_foreground;
        m_bUpdatesEnabled = true;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*====================================================================
�ṹ �� TStillImageWorkspace
���� �� ���Ӱװ幤�����ṹ
====================================================================*/
struct TStillImageWorkspace
{
    //��������(RegisterAllocateHandle����)
    s32     m_nWorkspaceHandle;

    u16     m_wAppRosterInstance;

    //�������Ƿ�ͬ��
    bool    m_bSynchronized;

    //�������Ƿ���ռ����¼�
    bool    m_bAcceptKeyboardEvents;

    //�������Ƿ��������¼�
    bool    m_bAcceptPointingDeviceEvents;

    //��������
    s32     m_nWorkspaceWidth;
    //������߶�
    s32     m_nWorkspaceHeight;

    //ƽ�����
    TStillImagePlaneParameter   m_atPlaneParameters[3];

    //��ͼ����(HandleΪ0��ʾ��������ͼ)
    TStillImageViewParameter    m_tViewParameter;

    TStillImageWorkspace()
    {
        m_nWorkspaceHandle = 0;
        m_wAppRosterInstance = 0;
        m_bSynchronized = true;
        m_bAcceptKeyboardEvents = false;
        m_bAcceptPointingDeviceEvents = false;
        m_nWorkspaceWidth = 0;
        m_nWorkspaceHeight = 0;
    };
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif
