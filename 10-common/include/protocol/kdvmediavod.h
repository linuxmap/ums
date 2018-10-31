/*****************************************************************************
ģ����      : kdvmediavod
�ļ���      : kdvmediavod.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : 
�汾        : V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2005/07/22  0.1         ���
2005/07/22  0.5         ����  
2005/11/22  1.0         ���      
******************************************************************************/

/*
�ӿ�˵����

  ʹ�ö��󣺱��ӿ�ͷ�ļ���ý��㲥�ͻ��˲ο���ʹ�ã�server�����Ҳ������ͷ�ļ�
  
	��Ϣ˵����
	1. ʹ��Osp��Ϣ���д��ݣ���Ϣ������������Ӧ�Ľṹ�����ļ��б�;
	2. ��Ϣ�ṹ������ȫ������������(BigEndian);
	3. ������Ϣ����SN����˿ͻ����޷�����������Ϣ��Ӧ����Ϣ����/Ӧ���״̬�ɿͻ��˱�֤;
	4. �����ļ��б���Ϣ�������ļ���ѹ���洢�ķ�ʽ����Ҫʹ��CVodFileList���д���
	
*/


#ifndef _KDVMEDIAVOD_H_
#define _KDVMEDIAVOD_H_

#include "kdvtype.h"
#include "kdvsys.h"
#include "osp.h"
#include "eventid.h"


#define MEDIAVOD_SERVER_ID          (u16)55
#define MEDIAVOD_SERVER_PRI         (u8)100

//------------------------ģ�麯�������Ĵ�����------------------------------------
#define  MEDIAVOD_NO_ERROR                  (u16)0//�ɹ�����ֵ  
#define  ERROR_MEDIAVOD_BASE                (u16)17000
#define  ERROR_MEDIAVOD_PARAM               (u16)(ERROR_MEDIAVOD_BASE+1)//�������� 
#define  ERROR_TOO_MANY_FILES               (u16)(ERROR_MEDIAVOD_BASE+2)//��������
#define  ERROR_TOO_LONG_FILENAME            (u16)(ERROR_MEDIAVOD_BASE+3)//��������
#define  ERROR_TOO_SHORT_BUF                (u16)(ERROR_MEDIAVOD_BASE+4)//��������
#define  ERROR_FILE_NAME                    (u16)(ERROR_MEDIAVOD_BASE+5)//��������
#define  ERROR_FILE_PATH                    (u16)(ERROR_MEDIAVOD_BASE+6)//��������
#define  ERROR_CREATE_PLAYER                (u16)(ERROR_MEDIAVOD_BASE+7)//��������
#define  ERROR_GET_FILEINFO                 (u16)(ERROR_MEDIAVOD_BASE+8)//
#define  ERROR_SET_LOCALPT                  (u16)(ERROR_MEDIAVOD_BASE+9)//
#define  ERROR_USERNOTEXIST                 (u16)(ERROR_MEDIAVOD_BASE+10)//
#define  ERROR_INVALIDPASSWD                (u16)(ERROR_MEDIAVOD_BASE+11)//


//------------------------��Ϣ��REJ��-------------------------------------------
#define  MEDIAVOD_REJ_NOREASON                (u8)0
//


#define  MEDIAVOD_REJ_FILE_NOT_FOUND          (u8)1
#define  MEDIAVOD_REJ_PLAY_NOTSTARTED         (u8)2
#define  MEDIAVOD_REJ_MAXUSER                 (u8)3  //�����û��Ѵﵽ�����������
#define  MEDIAVOD_REJ_USERNOTEXIST            (u8)4  //�û���������	
#define  MEDIAVOD_REJ_USERLOGINED             (u8)5  //���û��Ѿ���¼
#define  MEDIAVOD_REJ_INVALIDPASSWD           (u8)6  //�������
#define  MEDIAVOD_REJ_PARAM_NOTASF            (u8)7  // Client <-- Server ,�ļ���Ϊ�ջ���ASF�ļ�
#define  MEDIAVOD_REJ_PLAY_BUSY               (u8)9  // Client <-- Server ,���ڷ�����һ�ε���������

#define  MEDIAVOD_REJ_MSG_NOT_MATCH           (u8)10
#define  MEDIAVOD_REJ_FILE_LIST_FAIL          (u8)11
#define  MEDIAVOD_REJ_STATE_ERROR             (u8)12
#define  MEDIAVOD_REJ_OPERATE_FAIL            (u8)13

#define MEDIAVOD_MAX_CLIENT         32   // ��������ӵĿͻ�����
#define MEDIAVOD_MAX_USERNAME       32   // �û�������
#define MEDIAVOD_MAX_PASSWORD       32   // ���볤��
#define MEDIAVOD_MAX_PATHFILENAME   128  // ��·�����ļ�������
#define MEDIAVOD_MAX_DIRNAME        128  // ·��������
#define MEDIAVOD_MAX_FILENAME       50   // �ļ������� 
#define MEDIAVOD_MAX_FILENUM        400  // ͬһ�ļ���������ļ���

#define LANGUAGE_CHINESE	0
#define LANGUAGE_ENGLISH	1


//////////////////////////////// OSP��Ϣ��Χ /////////////////////////////
//////// KDVMEIDAVOD OSP��Ϣ��Χ: (MEDIAVOD_MESSAGE_START, MEDIAVOD_MESSAGE_END)////////

OSPEVENT( MEDIAVOD_MESSAGE_START, EV_VOD_BGN );

//ע��
OSPEVENT( MEDIAVOD_REG_REQ, MEDIAVOD_MESSAGE_START + 1 );// Client --> Server  [TVodReg]
OSPEVENT( MEDIAVOD_REG_ACK, MEDIAVOD_MESSAGE_START + 2 );// Client <-- Server  []  
OSPEVENT( MEDIAVOD_REG_REJ, MEDIAVOD_MESSAGE_START + 3 );// Client <-- Server  [u8]

//ע��
OSPEVENT( MEDIAVOD_UNREG_REQ, MEDIAVOD_MESSAGE_START + 4 );// Client --> Server  []
OSPEVENT( MEDIAVOD_UNREG_ACK, MEDIAVOD_MESSAGE_START + 5 );// Client <-- Server  []

//�ļ��б�����
OSPEVENT( MEDIAVOD_FILELIST_REQ, MEDIAVOD_MESSAGE_START + 6 );// Client --> Server [TVodListReq]  
OSPEVENT( MEDIAVOD_FILELIST_ACK, MEDIAVOD_MESSAGE_START + 7 );// Client <-- Server [�ַ�����ʹ��CVodFileList���д���]
OSPEVENT( MEDIAVOD_FILELIST_REJ, MEDIAVOD_MESSAGE_START + 8 );// Client <-- Server [u8] Dir err or no Files in this dir

//�ļ���Ϣ����
OSPEVENT( MEDIAVOD_FILEINFO_REQ, MEDIAVOD_MESSAGE_START + 9 );// Client --> Server  [TVodFileInfoReq]
OSPEVENT( MEDIAVOD_FILEINFO_ACK, MEDIAVOD_MESSAGE_START + 10 );// Client <-- Server  [TVodFileInfoAck]
OSPEVENT( MEDIAVOD_FILEINFO_REJ, MEDIAVOD_MESSAGE_START + 11 );// Client <-- Server  [u8]

//�ļ���������
OSPEVENT( MEDIAVOD_PLAY_REQ, MEDIAVOD_MESSAGE_START + 12 );// Client --> Server  [TVodPlayReq]
OSPEVENT( MEDIAVOD_PLAY_ACK, MEDIAVOD_MESSAGE_START + 13 );// Client <-- Server  []
OSPEVENT( MEDIAVOD_PLAY_REJ, MEDIAVOD_MESSAGE_START + 14 );// Client <-- Server  [u8]

//�ļ�����ֹͣ
OSPEVENT( MEDIAVOD_STOP_REQ, MEDIAVOD_MESSAGE_START + 15 );// Client --> Server  []
OSPEVENT( MEDIAVOD_STOP_ACK, MEDIAVOD_MESSAGE_START + 16 );// Client <-- Server  []
OSPEVENT( MEDIAVOD_STOP_REJ, MEDIAVOD_MESSAGE_START + 17 );// Client <-- Server  [u8]

//����״̬��ѯ
OSPEVENT( MEDIAVOD_STATE_REQ, MEDIAVOD_MESSAGE_START + 18 );// Client --> Server  []
OSPEVENT( MEDIAVOD_STATE_ACK, MEDIAVOD_MESSAGE_START + 19 );// Client --> Server  [TVodStateAck]

//������ת
OSPEVENT( MEDIAVOD_PLAYGOTO_REQ, MEDIAVOD_MESSAGE_START + 20 );// Client --> Server  [TVodPlayGotoReq]
OSPEVENT( MEDIAVOD_PLAYGOTO_ACK, MEDIAVOD_MESSAGE_START + 21 );// Client <-- Server  []
OSPEVENT( MEDIAVOD_PLAYGOTO_REJ, MEDIAVOD_MESSAGE_START + 22 );// Client <-- Server  [u8]

//������Ϣ����
OSPEVENT( MEDIAVOD_PLAYINFO_REQ, MEDIAVOD_MESSAGE_START + 23 );// Client --> Server  []
OSPEVENT( MEDIAVOD_PLAYINFO_ACK, MEDIAVOD_MESSAGE_START + 24 );// Client <-- Server  [TVodPlayInfoAck]
OSPEVENT( MEDIAVOD_PLAYINFO_REJ, MEDIAVOD_MESSAGE_START + 25 );// Client <-- Server  [u8]

//������Ϣ֪ͨ
OSPEVENT( MEDIAVOD_PLAYINFO_NTF, MEDIAVOD_MESSAGE_START + 26 );// Client <-- Server  [u8]

//������ͣ
OSPEVENT( MEDIAVOD_PLAYPAUSE_REQ, MEDIAVOD_MESSAGE_START + 27 );// Client --> Server  []
OSPEVENT( MEDIAVOD_PLAYPAUSE_ACK, MEDIAVOD_MESSAGE_START + 28 );// Client <-- Server  []
OSPEVENT( MEDIAVOD_PLAYPAUSE_REJ, MEDIAVOD_MESSAGE_START + 29 );// Client <-- Server  [u8]

//���Żָ�
OSPEVENT( MEDIAVOD_PLAYRESUME_REQ, MEDIAVOD_MESSAGE_START + 30 );// Client --> Server  []
OSPEVENT( MEDIAVOD_PLAYRESUME_ACK, MEDIAVOD_MESSAGE_START + 31 );// Client <-- Server  []
OSPEVENT( MEDIAVOD_PLAYRESUME_REJ, MEDIAVOD_MESSAGE_START + 32 );// Client <-- Server  [u8]

//����
OSPEVENT( MEDIAVOD_SERVERSTATE_REQ, MEDIAVOD_MESSAGE_START + 33 );


OSPEVENT( MEDIAVOD_MESSAGE_END, EV_VOD_END );


typedef struct tagVodReg
{
    s8  m_achUserName[MEDIAVOD_MAX_USERNAME];      //�û���
    s8  m_achPassword[MEDIAVOD_MAX_PASSWORD];      //�û�����
} TVodReg;



typedef struct tagVodFileInfoReq
{
    s8  m_achFileName[MEDIAVOD_MAX_PATHFILENAME];     //����·�����ļ���
} TVodFileInfoReq;


typedef struct tagVodFileInfoAck
{
private:
    u32 m_dwRecordTime;        //¼��ʱ�䣬��
    u32 m_dwDuration;          //������ʱ������
public:
    u8  m_byAudioType;          //��Ƶ�� 255��ʾû�и�·����
    u8  m_byVideo1Type;         //��Ƶ1��255��ʾû�и�·����
    u8  m_byVideo2Type;         //��Ƶ2��255��ʾû�и�·����
public:
    tagVodFileInfoAck()
    {
        m_dwRecordTime  = 0;        
        m_dwDuration    = 0;          
        m_byAudioType   = 0xff;         
        m_byVideo1Type  = 0xff;         
        m_byVideo2Type  = 0xff; 
    }
    
    ~tagVodFileInfoAck()
    {
    }
    
    void SetRecordTime(u32 dwRecordTime)
    {

        m_dwRecordTime  =  htonl(dwRecordTime);                             
    }
    
    void SetDuration(u32 dwDruation)
    {

        m_dwDuration  = htonl(dwDruation);                                    
         
    }
    
    u32 GetRecordTime()
    {
        return ntohl(m_dwRecordTime);
    }
    
    u32 GetDuration()
    {
        return ntohl(m_dwDuration);
    }    
    
} TVodFileInfoAck;


typedef struct tagVodStateAck
{
    u8  m_byState;              //�ýڵ�����״̬

} TVodState;


typedef struct tagVodPlayInfoAck
{
private:
    u32 m_dwDuration;          //������ʱ��������
    u32 m_dwPlayTime;          //�Ѳ���ʱ�䣬����
public:
    tagVodPlayInfoAck()
    {
        m_dwDuration = 0;
        m_dwPlayTime = 0;
        
    }

    ~tagVodPlayInfoAck()
    {
    }

    void SetDuration(u32 dwDuration)
    {
        m_dwDuration = htonl(dwDuration);
        
    }

    void SetPlayTime(u32 PlayTime)
    {
        m_dwPlayTime = htonl(PlayTime);        
    }
    
    u32 GetDuration()
    { 
        return ntohl(m_dwDuration); 
    }
    
    u32 GetPlayTime()
    {
        return ntohl(m_dwPlayTime);     
    }

} TVodPlayInfoAck, TVodPlayInfoNtf;


typedef struct tagVodPlayReq
{
public:
    s8  m_achFileName[MEDIAVOD_MAX_PATHFILENAME];    //����·�����ļ���
    u8  m_byStart;             //�Ƿ�������ʼ����
private:
    u16 m_wAudioPort;          //0��ʾ��ʹ��
    u16 m_wVideo1Port;         //0��ʾ��ʹ��
    u16 m_wVideo2Port;         //0��ʾ��ʹ��
    u32 m_dwIP;                //���ŵĵ�ַ
    
public:
    tagVodPlayReq()
    {
        m_byStart      = 0;
        m_wAudioPort   = 0;
        m_wVideo1Port  = 0;
        m_wVideo2Port  = 0;
        m_dwIP         = 0;
        memset(m_achFileName,0,sizeof(m_achFileName));
    }

    ~tagVodPlayReq()
    {
    }

    void SetAudioPort(u16 wAudioPort)
    {             
        m_wAudioPort = htons(wAudioPort);
    }

    void SetVideo1Port(u16 wVideo1Port)
    {

        m_wVideo1Port = htons(wVideo1Port);
 
    }

    void SetVideo2Port(u16 wVideo2Port)
    {
        m_wVideo2Port = htons(wVideo2Port);
    }

    void SetAddrIP(u32 dwIP)
    {
        m_dwIP = dwIP;
    }
    
    u16 GetAudioPort()
    {
        return ntohs(m_wAudioPort);
        
    }

    u16 GetVideo1Port()
    {
        return ntohs(m_wVideo1Port);
    }

    u16 GetVideo2Port()
    {
        return ntohs(m_wVideo2Port);
    }
    
    u32 GetAddrIP()
    {
        return m_dwIP;
    }

} TVodPlayReq;


typedef struct tagVodPlayGotoReq
{
private:
    u32 m_dwPlayTime;          //����ʱ��㣬��

public:
    tagVodPlayGotoReq()
    {
        m_dwPlayTime = 0;
    }

    ~tagVodPlayGotoReq()
    {
    }
    
    void SetPlayTime(u32 playtime)
    {
        m_dwPlayTime = htonl(playtime);
    }

    u32 GetPlayTime()
    {
        return ntohl(m_dwPlayTime);
    }

    
} TVodPlayGotoReq;



typedef struct tagVodListReq
{
    s8  m_achDirName[MEDIAVOD_MAX_DIRNAME];     //����·����Ŀ¼��
} TVodListReq;


typedef struct tagVodFileName
{
public:
    u8  m_byType;                 //0 Ŀ¼  1 �ļ� 
    u32 m_dwFileLen;              //�ļ�����
    s8  m_achFileName[MEDIAVOD_MAX_FILENAME];      //�ļ���
public:
    tagVodFileName()
    {
        m_byType      = 0;
        m_dwFileLen   = 0;
        memset(m_achFileName,0,sizeof(m_achFileName));
    }

    ~tagVodFileName()
    {
    }

    void SetFileLen(s32 FileLen)
    {
        m_dwFileLen = FileLen;
    }

    u32 GetFileLen()
    {
        return m_dwFileLen;
    }

} TVodFileName;

//�������ɣ��ͷ����ɣ��ļ��б��ַ���
typedef struct tagVodFileList
{
    u32 m_dwFileNum;
    TVodFileName m_tVodFileName[MEDIAVOD_MAX_FILENUM];

public:
    tagVodFileList()
	{
		m_dwFileNum = 0;
	};

    s32 GetFileCount()
    {
        return m_dwFileNum;
    }

    //����Ϣ�ַ����������ļ��б�
    u16 GetFileListFromString(u8* pBuf)
    {
        u32 i;
        if (NULL == pBuf)// || dwBufLen == 0)
        {
            return ERROR_MEDIAVOD_PARAM;
        }
        
        //file num
        memcpy(&m_dwFileNum, pBuf, sizeof(u32));
        m_dwFileNum = ntohl(m_dwFileNum);

        if (m_dwFileNum > MEDIAVOD_MAX_FILENUM)
        {
            return ERROR_TOO_MANY_FILES;
        }

        pBuf += sizeof(s32);

        for (i = 0; i < m_dwFileNum; i++)
        {
            s32 nNameLen;
            //type
            m_tVodFileName[i].m_byType = *(u8*)pBuf;
            pBuf += sizeof(u8);

            //file length
            memcpy(&m_tVodFileName[i].m_dwFileLen, pBuf, sizeof(u32));
            pBuf += sizeof(u32);
            m_tVodFileName[i].m_dwFileLen = ntohl(m_tVodFileName[i].m_dwFileLen);

            //file name
            nNameLen = strlen((s8*)pBuf);
            if (nNameLen >= MEDIAVOD_MAX_FILENAME)
            {
                return ERROR_TOO_LONG_FILENAME;
            }
            memcpy(m_tVodFileName[i].m_achFileName, pBuf, nNameLen);
            m_tVodFileName[i].m_achFileName[nNameLen] = '\0';
            pBuf += nNameLen + 1;
        }

        return MEDIAVOD_NO_ERROR;	
    }


    u16 SetFileListToString(u8* pUserBuf, u32* pdwBuffLen)
    {
        u8* pBuf;
        u8* pBufEnd;
        u32 i;
        
        if (NULL == pUserBuf || NULL == pdwBuffLen || *pdwBuffLen == 0)
        {
            return ERROR_MEDIAVOD_PARAM;
        }
        
        pBuf    = pUserBuf;
        pBufEnd = pUserBuf + (*pdwBuffLen) - MEDIAVOD_MAX_FILENAME;

        //file num
        u32 dwTmp = htonl(m_dwFileNum);
        memcpy(pBuf, &dwTmp, sizeof(u32));
        pBuf += sizeof(u32);

        for (i = 0; i < m_dwFileNum && pBuf < pBufEnd; i++)
        {
            s32 nNameLen;
            
            //type
            *(u8*)pBuf = m_tVodFileName[i].m_byType;
            pBuf += sizeof(u8);
            
            //file length
            dwTmp = htonl(m_tVodFileName[i].m_dwFileLen);
            memcpy(pBuf, &dwTmp, sizeof(u32));
            pBuf += sizeof(u32);
            
            //file name
            nNameLen = strlen(m_tVodFileName[i].m_achFileName);
            if (nNameLen >= MEDIAVOD_MAX_FILENAME)
            {
                return ERROR_TOO_LONG_FILENAME;
            }
            memcpy(pBuf, m_tVodFileName[i].m_achFileName, nNameLen);
            pBuf += nNameLen;
            *pBuf = '\0';
            pBuf++;
        }

        if (pBuf > pBufEnd)
        {
            return ERROR_TOO_LONG_FILENAME;
        }

        *pdwBuffLen = pBuf - pUserBuf;
		return MEDIAVOD_NO_ERROR;
    }

}TVodFileList;

s32	MoveToSectionStart( FILE *stream, const s8* lpszSectionName, BOOL32 bCreate );
s32	MoveToSectionEnd( FILE *stream, const s8* lpszSectionName, BOOL32 bCreate );
s32	DelSection( FILE *stream, const s8* lpszSectionName );
BOOL32 TrimCfgFile( const s8* lpszCfgFilePath );
u32 GetSectionKeyArray(FILE * stream, const s8* lpszSectionName, s8 **ppKeyArray, u32 dwMaxKeyNum, u32 &dwOffset );

#endif // _KDVMEDIAVOD_H_