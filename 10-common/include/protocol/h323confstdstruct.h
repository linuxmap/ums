#ifndef _H323CONFSTDSTRUCT_H
#define _H323CONFSTDSTRUCT_H

#include "kdv323common.h"


//������Ϣ
typedef struct tagConfInfo
{
	u8          m_abyConfId[LEN_GUID];
	TAliasAddr  m_tConfAlias;
	
	tagConfInfo()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
	}

	
	void Clear()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
		m_tConfAlias.Clear();
	}

	//���û���ID
	void SetConfId( u8 *pbyConfId, u32 dwLen );

	//��ȡ����ID
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	
	//����TAliasAddr
	void SetAliasAddr( TAliasAddr &tAliasAddr)
	{
		m_tConfAlias = tAliasAddr;
	}
	//��ȡTAliasAddr
	TAliasAddr& GetAliasAddr()
	{
		return m_tConfAlias;
	}
}TCONFINFO,*PTCONFINFO;

//�����б�
typedef struct tagConferences
{
	u8		   m_byNum;
	TCONFINFO  m_atConfInfo[MAX_CONF_NUM];
	
	tagConferences():m_byNum(0){}
	
	void Clear()
	{
		m_byNum = 0;
		memset( m_atConfInfo, 0, sizeof(m_atConfInfo) );
	}
	
	//���û�����Ŀ
	void SetConfNum( u8 num)
	{
		m_byNum = num;
	}
	//��ȡ������Ŀ
	u8 GetConfNum()
	{
		return m_byNum;
	}

	//���û�����Ϣ
	void SetConfInfo( TCONFINFO &tConfInfo, u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return ;		
		m_atConfInfo[byConfNo] = tConfInfo;
	}
	//��ȡ������Ϣ
	PTCONFINFO GetConfInfo( u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return  NULL;
		return &(m_atConfInfo[byConfNo]);
	}
}TCONFERENCES,*PTCONFERENCES;

//////////////////////////////  ��Ϣ�д��Ľṹ��  //////////////////////////


//ͨѶģʽ����
typedef struct tagCommunicationModeCommandInfo
{
	u8				m_bySessionID;
	u8				m_byAssociatedSessionID;
	TTERLABEL		m_tTerLabel;							//���Ϊ<255,255>��ʾ�����ն�
	u8				m_byDataType;							//type_audio/type_video/type_data
	u16				m_wPayloadType;							//ý��������
	TNETADDR		m_tRtp;									//rtp��ַ		
	TNETADDR		m_tRtcp;								//rtcp��ַ
	TTERLABEL		m_tDestination;							//Ŀ���ն�,<0,0>��ʾ��Ч
	u8				m_bySessionDescriptLen;
	s8				m_achSessionDescript[MAXSessionDescript+1];
					
	tagCommunicationModeCommandInfo()
	{
		Clear();
	}
	
	void Clear();

    //����SessionID
	void SetSessionID( u8 bySessionID)
	{
		m_bySessionID = bySessionID;
	}
    //�õ�SessionID
	u8 GetSessionID()
	{
		return m_bySessionID;
	}

    //����AssociatedSessionID
	void SetAssociatedSessionID( u8 byAssociatedSessionID )
	{
		m_byAssociatedSessionID = byAssociatedSessionID;
	}
    //�õ�AssociatedSessionID
	u8 GetAssociatedSessionID()
	{
		return m_byAssociatedSessionID;
	}

    //����TTERLABEL
	void SetTerLabel( TTERLABEL &tTerLabel)
	{
		m_tTerLabel = tTerLabel;
	}
    //�õ�TTERLABEL
	TTERLABEL& GetTerLabel()
	{
		return m_tTerLabel;
	}

    //������������
	void SetDataType( u8 byDataType)
	{
		m_byDataType = byDataType;
	}
    //�õ���������
	u8 GetDataType()
	{
		return m_byDataType;
	}

    //����ý������
	void SetPayloadType( u16 wPayloadType)
	{
		m_wPayloadType = wPayloadType;
	}
    //�õ�ý������
	u16 GetPayloadType()
	{
		return m_wPayloadType;
	}

    //����RTP��ַ
	void SetRTPAddr( TNETADDR &tRtp )
	{
		m_tRtp = tRtp;
	}
    //�õ�RTP��ַ
	TNETADDR& GetRTPAddr()
	{
		return m_tRtp;
	}

    //����RTCP��ַ
	void SetRTCPAddr( TNETADDR &tRtcp )
	{
		m_tRtcp = tRtcp;
	}
    //�õ�RTCP��ַ
	TNETADDR& GetRTCPAddr()
	{
		return m_tRtcp;
	}

    //����Ŀ�Ķ�TTERLABEL
	void SetDestTerLabel( TTERLABEL &tTerLabel)
	{
		m_tDestination = tTerLabel;
	}
    //�õ�Ŀ�Ķ�TTERLABEL
	TTERLABEL& GetDestTerLabel()
	{
		return m_tDestination;
	} 
	
    //����SessionDescript
	void SetSessionDescript( s8 *pSessionDescript, u8 byLen )
	{
		m_bySessionDescriptLen = Minimum( byLen, MAXSessionDescript );
		strncpy( m_achSessionDescript, pSessionDescript, m_bySessionDescriptLen );
		m_achSessionDescript[m_bySessionDescriptLen] = '\0';
	}
    //�õ�SessionDescript
	s8* GetSessionDescript()
	{
		return m_achSessionDescript;
	}
    //�õ�SessionDescript����
	u16 GetSessionDescriptLen()
	{
		return m_bySessionDescriptLen;
	}
}TCOMMODEINFO,*PTCOMMODEINFO;

typedef struct PROTO_API tagPassRsp
{
	TTERLABEL m_tTer;
	s32       m_nPassLen;
	u8        m_abyPassword[LEN_H243PWD+1]; 

	tagPassRsp()
	{
		Clear();
	}

	void Clear()
	{
		memset( &m_tTer, 0, sizeof(m_tTer) );
		m_nPassLen = 0;
		memset( m_abyPassword, 0, sizeof(m_abyPassword) );
	}

    void host2net(BOOL32 bhton);

	//����TTERLABEL
	void SetTerLabel( TTERLABEL &tTerLabel )
	{
		m_tTer = tTerLabel;
	}
	//��ȡTTERLABEL
	TTERLABEL& GetTerlabel()
	{
		return m_tTer;
	}
	
	//����Password
	void SetPassword( u8 *pPassword, u16 wLen );

	//��ȡPassword
	u16 GetPassword( u8 *pbyPassword, u16 &wLen );

}TPassRsp;

//�ն���Ϣ����
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;
	s8			m_achTerID[LEN_TERID + 1];

	tagTerminalInformation()
	{
		Clear();
	}

	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	//�����ն˱��
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo < 193 && byTerNo <193)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}
	//����ն˱��
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}
	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}
	//���Mcu��
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	//����ն˺�
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}

	//�����ն�����
	BOOL32 SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}
	//����ն�����
	s8* GetName()
	{
		return m_achTerID;
	}

	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
									  tTerInfo.m_tTerLabel.GetTerNo() );

		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}

	bool operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return false;
		}
		return true;
	}

	bool operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return true;
		}
		return false;
	}
}TTERINFO,*PTTERINFO;

//H239 Information
typedef struct PROTO_API tagH239Info
{
    emH239InfoType  m_emH239InfoType;
    TTERLABEL       m_tTerLabel;
    s32             m_nChannelId;
    
    /*��emH239FlowControlReleaseResponse
      ��emH239PresentationTokenResponse��ʹ��
      TRUE��ʾͬ�⣬FALSE��ʾ�ܾ�*/
    BOOL32            m_bIsResponseAck;   
    
    /*ͨ�����ʣ���λ��100bit/s����Χ��1��19200
      ��emH239FlowControlReleaseRequest
      ��emH239FlowControlReleaseResponse��Ϣ��ʹ��      
    */
    u32             m_dwBitRate;          
    
    /*
      MTȡ1��127֮������ֵ;
      MCU������Ϊ0�������о��庬��
    */
    u8              m_bySymmetryBreaking; 
    
    tagH239Info()
    {
        Clear();
    }

    void Clear();

    void host2net(BOOL32 bhton);

    BOOL32 SetH239InfoType(emH239InfoType nH239InfoType);
  
    emH239InfoType GetH239InfoType()
    {
        return m_emH239InfoType;
    }
    
    void SetTerLabel(TTERLABEL &tTerlabel)
    {
        m_tTerLabel = tTerlabel;
    }

    TTERLABEL &GetTerlabel()
    {
        return m_tTerLabel;
    }

    void SetSymmetryBreaking(u8 bySymmetryBreaking)
    {
        m_bySymmetryBreaking = bySymmetryBreaking;
    }
    u8 GetSymmetryBreaking()
    {
        return m_bySymmetryBreaking;
    }
    
    void SetResponseAck(BOOL32 bIsResponseAck)
    {
        m_bIsResponseAck = bIsResponseAck;
    }
    BOOL32 IsResponseAck()
    {
        return m_bIsResponseAck;
    }
    
    void SetChannelId(HCHAN hsChan)
    {
        m_nChannelId = cmGetLCNFromHchan(hsChan);
    }
    s32 GetChannelId()
    {
        return m_nChannelId;
    }
    void SetChannelId(s32 nChannelId)
    {
        m_nChannelId = nChannelId;
    }
    
}TH239INFO,*PTH239INFO;

///////////////////////////////// �����ṹ ////////////////////////////////
//userInput�ṹ���г�ͻ��ʹ����ҵ�Ķ��壨union��
typedef struct PROTO_API tagUserInputInfo 
{
    emUserInputIndication m_emUserInputType;
	union
	{
		struct 
		{
           s8  m_chSignalType;     //FROM ("0123456789#*ABCD!")
           s32 m_nDuration;        //��ʱֵ����λ��milliseconds
		}usersignal;
        s8 m_achAlphaNumeric[5];
	}arguments;

	s32 m_nNonStandardDataLen;
	u8* m_pbyNonStandardData; 

    tagUserInputInfo()
    {
		m_pbyNonStandardData = NULL;
		m_nNonStandardDataLen = 0;
		m_emUserInputType = emUserInputSignal;
        arguments.usersignal.m_chSignalType = '\0';
        arguments.usersignal.m_nDuration = 300;
		
    }

	//��ָ�븳ֵ�����ܱ��棬 С�ģ���������������
	BOOL32 SetNonStandData(u8 *pBuf, s32 nLen);

    //��ȡָ�룬���ܱ���С�ģ���������������
	BOOL32 GetNonStandData(u8 **ppBuf, s32 *pnLen);
			
    void SetSignalType(s8 signalType)
    {
        arguments.usersignal.m_chSignalType = signalType;
    }

    s8 GetSignalType()
    {
        return arguments.usersignal.m_chSignalType;
    }

    void SetDuration(s32 duration)
    {
        arguments.usersignal.m_nDuration = duration;
    }

    u16 GetDuration()
    {
        return arguments.usersignal.m_nDuration;
    }
	void SetAlpaNumericString( s8* string, u16 wLen );

	u16  GetAlpaNumericStringLen()
	{
		return strlen(arguments.m_achAlphaNumeric);
	}

	s8*  GetAlpaNumericString()
	{
		return arguments.m_achAlphaNumeric;
	}
}TUserInputInfo,*PTUserInputInfo;

typedef struct tagMultiplexCapability
{
	emH264NALMode m_emH264NALMode;

	tagMultiplexCapability()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emH264NALMode = emNALNode;
	}
	
	void SetH264NALMode( emH264NALMode emNALMode)
	{
		m_emH264NALMode = emNALMode;
	}
	emH264NALMode& GetH264NALMode()
	{
		return m_emH264NALMode;
	}

}TMultiplexCapability,*PTMultiplexCapability;
/////////////////////////////   ��Ϣ�д��Ľṹ�� //////////////////////////

//Facility����
typedef struct tagFacilityUUIE
{
	u8			  m_byReason;					//FacilityReason
	TAliasAddr	  m_tAlternativeAddrAlias;
	TCONFERENCES  m_tConferences;

	u8			  m_abyCallId[LEN_GUID]; 
	BOOL32        m_bExistCallId;
	
	//begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010

	TFacilityConfList_NSM  m_atConfList_NSM[MAX_CONF_NUM];

	//end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010

	tagFacilityUUIE()
	{
		Clear();
	}

	void Clear();

	//����TAliasAddr
	void SetAliasAddr( TAliasAddr &tAliasAddr )
	{
		m_tAlternativeAddrAlias = tAliasAddr;
	}
	//��ȡTAliasAddr
	TAliasAddr& GetAliasAddr()
	{
		return m_tAlternativeAddrAlias;
	}

	//����TCONFERENCES
	void SetConferences( TCONFERENCES &tConf )
	{
		m_tConferences = tConf;
	}
	//��ȡTCONFERENCES
	TCONFERENCES& GetConferences()
	{
		return m_tConferences;
	}

	//��ȡ����ID
	s32 GetCallId(u8* pbyCallId, s32 nLen);
	
	//���ú���ID
	void SetCallId(const u8* pbyCallId,u8 byLen);

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_atConfList_NSM[MAX_CONF_NUM-1].SetContinueFlag( bIsContinue );
    }
    BOOL32 IsContinue( void )
    {
        return m_atConfList_NSM[MAX_CONF_NUM-1].IsContinue();
    }

}TFACILITYINFO,*PTFACILITYINFO;


// typedef struct 
// {
// 	TFeccStruct m_tFeccStruct;
// 	TTERLABEL   m_tSrcTer;
// 	TTERLABEL   m_tDstTer;
// }TH245Fecc;

#endif //_H323CONFSTDSTRUCT_H
