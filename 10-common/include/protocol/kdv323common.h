#ifndef _H323COMMON_H
#define _H323COMMON_H

#include "kdvcommon.h"

#define INVALID_NODEID      RV_PVT_INVALID_NODEID
#define TYPE_NONE           0         //��ʾΪδ�����ַ
#define TYPE_IPV4           1         //��ʾ֧��IPv4��ַ
#define TYPE_IPV6           2         //��ʾ֧��IPv6��ַ

///////////////////////////////// ���ȶ��� ///////////////////////////////
#define LEN_H245_CONFID		(u16)32					//H245����ID 
#define LEN_CONFNAME		(u16)256				//h323-id
#define LEN_NETADDR			sizeof(TNETADDR)		//��·��ַ����
//#define LEN_MTNUM_PERCONF	(u16)193				//ÿ�������е���������
#define LEN_OID				(u16)16					//OID����
#define LEN_CALLADDR		sizeof(TAliasAddr)		//���е�ַ����
#define LEN_CHANPARAM		sizeof(TCHANPARAM)		//�ŵ���������
#define LEN_TERINFO			sizeof(TTERINFO)		//�ն���Ϣ����
#define LEN_CAP				sizeof(TKdv323CapSet)	//������������
#define LEN_H243PWD			(u16)32                 //���볤��
#define LEN_DISPLAY_MAX		(u16)82                 //��ʾ��Ϣ����󳤶�
#define LEN_DISPLAY_MIN		(u16)2                  //��ʾ��Ϣ����С����

#define LEN_USERINFO_MAX    (u8)131					//UserInfor����󳤶�
#define LEN_USERINFO_MIN	(u16)2                  //UserInfor����С����
#define TLCALLPORT			(u16)1760				//���ж˿�
#define CALLPORT			(u16)1720				//���ж˿�
#define RASPORT				(u16)1719				//RAS�˿� 
#define MAXALIASNUM			(u16)128				//��������
#define MAXSessionDescript	(u8)128                 //֧�ֵ����SessionDescript
#define MAX_LEN_CONFNAME    (u16)64					//����������󳤶�
#define PRODUCTSTRING_LESS_SIZE        (u16)32      //��Ʒ��Ϣ�ĳ���,���ڻ�ȡ�Է��Ĳ�Ʒ��Ϣ
#define VERSIONSTRING_LESS_SIZE        (u16)32      //�汾��Ϣ�ĳ���,���ڻ�ȡ�Է��İ汾��Ϣ
#define LEN_NONSTANDARD_MAX (u16)2048               //setup��Ϣ�зǱ����ݵ���󳤶�
#define MAX_CALL_NUM        (u16)1024
#define MIN_CALL_NUM        (u16)10
#define MAX_CHANNEL_NUM     (u16)20
#define MIN_CHANNEL_NUM     (u16)12
#define RequestMsg_BGN		(u16)101
#define RequestMsg_END		(u16)300
#define ResponseMsg_BGN		(u16)301
#define ResponseMsg_END		(u16)500
#define CommandMsg_BGN		(u16)501
#define CommandMsg_END		(u16)700
#define IndicationMsg_BGN	(u16)701
#define IndicationMsg_END	(u16)900
#define LEN_256				(u16)256
#define LEN_128				(u16)128
#define REG_NAME_LEN		(u16)64
#define REG_PWD_LEN			(u16)64
#define VALID_LEN_ALIAS      (u16)16   //��Ч��������  
#define RAS_RESPONSE_TIMEOUT (u32)20  

#define FLAG_H460FEATURESIGNALL			18			//460.18
#define FLAG_H460MEDIAFWSIGNALL			19			//460.19     

#define FLAG_H460SUPPORTMULTIPLEXDMEDIA	1			//֧�ֶ˿ڸ���
#define FLAG_H460MEDIATRAVESALSERVER	2			//����Ϊ460������

//�Ǳ���Ϣ����Ŷ���
enum
{	
	KDVP_NSM_SUCCESS		 						= 0,  
	KDVP_NSM_SER_DB_ERR  						    = 1,
	KDVP_NSM_TIMEOUT_ERR 						    = 2,		//ƽ̨�ڲ���ʱ
	KDVP_NSM_NOTE164_ERR 							= 3,				 
	KDVP_NSM_DATA_ERR 								= 4,        
	KDVP_NSM_MCU_NOIDLEVPU							= 5,        //û���㹻�����Ŀ���ý�崦����
	KDVP_NSM_MCU_MINIMEDIACONFMTNUM					= 6,        //����С��ý���������ն�����, 
	KDVP_NSM_MCU_MAXCONFNUM							= 7,        //�Ѵ���������
	KDVP_NSM_MCU_ENCRYPEERR							= 8,        //��������ģʽ����
	KDVP_NSM_MCU_CONFNOTEXIST						= 9,        //���鲻����
	KDVP_NSM_MCU_MAXMTNUM							= 10,       //�ﵽ���λ���Ա��
	KDVP_NSM_GK_MPCD_DISCONNECTED				    = 11,       //MPCD��GK����          nu����
	KDVP_NSM_MCU_CONFRESUMING						= 12,       //MCU�����ָ���
	KDVP_NSM_MCU_PASSERR							= 13,       //�����������
	KDVP_NSM_MCU_NSATPMS							= 14,       //������Ȩ��
	KDVP_NSM_MCU_NSATDADDR							= 15,       //û���鲥��ַ
	KDVP_NSM_MCU_CONFE164REPEAT					    = 16,       //����E164���ظ�
	KDVP_NSM_MCU_UNDEFINED							= 17,       
	KDVP_NSM_MCU_PEER_NODISTURB 			        = 18,       //��������žܾ�
};

/////////////////////////
#ifndef H323CASCADE_H_

#define CASCADE_USERNAME_MAXLEN     (s32)32
#define CASCADE_USERPASS_MAXLEN     (s32)32 

typedef struct tagRequest
{
    s32  m_nReqID;//��ˮ��/ϵ�к�
	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];//�ʺ�
	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];//����
	//�����ʺź�����
	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
	{
		strncpy(m_aszUserName, aszUserName, sizeof(m_aszUserName) - 1);
		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
		strncpy(m_aszUserPass, aszUserPass, sizeof(m_aszUserPass) - 1);
		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
	}

	tagRequest()
	{
		memset(this, 0, sizeof(*this));
	};
}TReq;


//������л��鼶����ע��ע������
typedef struct tagRegUnReg: public TReq     //��Զ�mcuע��ע����������Ϣ
{
    BOOL32 m_bReg;               //true:ע��;false ע��
}TRegUnRegReq;

#endif
/////////////////////////

#define		MAXLEN_E164                     16			//���E164���볤��
#define		MAX_STACK_BUFFER_SIZE           (u32)5120	//Э��ջ������ͻ���




#define KDV_NSM_MAX_LEN        (s32)(1024*10)  
//��������
enum AliasType
{
	type_aliastype,
	type_e164 = 0x1,
	type_h323ID,
	type_email,
	type_epID,
	type_GKID,
	type_partyNumber,
	type_others
};

// IP��ַ����
enum TransportAddrType 
{
	addr_uca,		//unicast
	addr_mca,		//multicast
	addr_err = 0xff
};

//����ִ�н��
enum ActResult 
{
    act_err = -1,
	act_ok
};


//������ַ
#pragma pack(4)		//[20141022]����������-���˽ṹ�������ֽ����ڴ����
typedef struct PROTO_API tagALIASADDR
{
	AliasType  m_emType;
	s8		   m_achAlias[LEN_ALIAS+2];			//h323-Id ��������λΪ��
	
	tagALIASADDR()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emType = type_aliastype;
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}
	
	//���ñ���
	BOOL32 SetAliasAddr( AliasType aliasType, const char* pAlias )
	{
		if ( aliasType <= type_aliastype || aliasType >= type_others ||
			pAlias == NULL ) 
			return FALSE;
		
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		
		m_emType = aliasType;
		
		s32 nLen = Minimum( (s32)strlen(pAlias), (s32)LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		
		return TRUE;
	}	
	//���type
	AliasType GetAliasType()
	{
		return m_emType;
	}
	
	void SetAliasType(AliasType emType)
	{
		m_emType = emType;
	}
	//��ñ���
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TALIASADDR,*PTALIASADDR;
#pragma pack()


//transport��ַ
#pragma pack(4)		//[20141022]����������-���˽ṹ�������ֽ����ڴ����
typedef struct PROTO_API tagTransportAddress
{
    //add by yj for ipv6
	u8          m_byIPType;                                 //֧�ֵ� IP��ַ����
	u8          m_dwIP_ipv6[IPV6_NAME_LEN];			        //Э��ջ����IP(ipv6)����������;
    //end
	u32 m_dwIP;
	u16 m_wPort;
	u8	m_byType;
	
	tagTransportAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		m_dwIP	 = 0;
		m_wPort  = 0;
		m_byType = addr_uca;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
		memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
        //end
	}
	
    void host2net(BOOL32 bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }
	
	//����transport��ַ
	void SetNetAddress(u32 dwIPAddr, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		m_dwIP   = dwIPAddr;
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV4;
	}
	//add by yj for ipv6
	//����ip��ַ����
	void SetIPAddr_Type(u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetIPAddr_Type( )
	{
		return	m_byIPType;
	}
	void SetNetAddress_Ipv6(u8* dwIPAddr_ipv6, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		memcpy(m_dwIP_ipv6, dwIPAddr_ipv6, sizeof(m_dwIP_ipv6));
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV6;
		
	}
	
	u8 *GetIPAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
	
	//��ȡIP��ַ
	u32 GetIPAddr()
	{
		return m_dwIP;
	}
	//��ȡ�˿�
	u16 GetIPPort()
	{
		return m_wPort;
	}
	//��ȡ����
	u8 GetNetAddrType()
	{
		return m_byType;
	}

	void SetIPAddr(u32 dwIP)
    {
        m_dwIP = dwIP;
		m_byIPType = TYPE_IPV4;
    }

	void SetIPPort(u16 wPort)
	{
		m_wPort = wPort;
	}

}TNETADDR,*PTNETADDR;
#pragma pack()

//����ʱ�ı�����ַ
typedef struct PROTO_API tagAliasAddr
{
	CallAddrType    m_emType;		//��������
	TNETADDR		m_tNetAddr;		//IP����ʱʹ��		
	TALIASADDR		m_tAlias;		//��������ʹ��

	tagAliasAddr()
	{
		m_emType = emcat_err;
	}

	void Clear()
	{
		m_emType = emcat_err;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}

	//����ΪIP��ַ����
	void SetIPCallAddr( TNETADDR *pTNetAddr )
	{
		if ( pTNetAddr != NULL )
		{
			m_emType = emcat_ip;
			memcpy( &m_tNetAddr, pTNetAddr, sizeof(m_tNetAddr) );
		}		
	}

	//add by yj for ipv6
	//��ȡip��ַ����
	u8 GetIPAddr_Type( )
	{
		if (m_emType == emcat_ip) 
		{
		return	m_tNetAddr.GetIPAddr_Type();
		}
		return TYPE_NONE;
	}
	//��ȡ���е�IP(ipv6)��ַ
	u8* GetIPAddr_Ipv6()
	{
		if (m_emType == emcat_ip) 
		{
			if (m_tNetAddr.m_byIPType == TYPE_IPV6)
			{
				return m_tNetAddr.GetIPAddr_Ipv6();
			}
		}
		return 0;
	}
//	s16 GetIPAddr_Ipv6_ScopeId()
//	{
//		if (m_emType == emcat_ip) 
//		{
//			if (m_tNetAddr.m_byIPType == TYPE_IPV6)
//			{
//				return m_tNetAddr.GetIPAddr_Ipv6_ScopeId();
//			}
//		}
//		return -1;
//	}

	//end

	//��ȡ���е�IP��ַ
	u32 GetIPAddr()
	{
		if (m_emType == emcat_ip) 
		{
			//add by yj
			if (m_tNetAddr.m_byIPType == TYPE_IPV4)
			{
				return m_tNetAddr.GetIPAddr();
			}
		    //end
		}
		return 0;
	}

	//��ȡ���еĶ˿�
	u16 GetIPPort()
	{
		if (m_emType == emcat_ip) 
		{
			return m_tNetAddr.GetIPPort();
		}
		return 0;
	}
	//����Ϊ������ַ����
	void SetIPCallAddr( TALIASADDR *pAliasAddr )
	{
		if ( pAliasAddr != NULL )
		{
			m_emType = emcat_alias;
			memcpy( &m_tAlias, pAliasAddr, sizeof(m_tAlias) );
		}		
	}
	//��ȡ��������
	AliasType GetAliasType()
	{
		if (m_emType == emcat_alias)
		{
			return m_tAlias.GetAliasType();
		}
		return type_aliastype;
	}
	//��ȡ����
	s8* GetAliasName()
	{
		if (m_emType == emcat_alias)
		{
			return m_tAlias.GetAliasName();
		}
		return NULL;
	}
	//��ȡ��������
	CallAddrType GetCallAddrType()
	{
		return m_emType;
	}
}TAliasAddr,*PTAliasAddr;

//begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010
typedef struct tagFacilityConfList_NSM
{
protected:
	u8   m_abyConfId[LEN_GUID+1];	//����ID
	u16  m_wListIdx;				// ��TCONFERENCES�ṹ�еĴ��λ��������������

	//�����Ǳ�����
	s8	 m_sConfE164[LEN_ALIAS+1];	// ����E164����
	u8	 m_byMtNum;					// ����ն���
	u16  m_wRemainTime;				// ����ʣ��ʱ��, ��λ�Ƿ���
	u32  m_dwReserved1;
	u32  m_dwIsContinue;

	BOOL32         m_bConfListNonStandard;// whether contains non-standard information or not when facilityreason is conferenceListChoice

	////////
public:
	tagFacilityConfList_NSM()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(m_abyConfId,0,sizeof(m_abyConfId));
		SetListIdx(0);
		SetConfE164( NULL, 0 );
		SetMtNum( 0 );
		SetRemainTime( 0 );
		SetConfListNonStandard( FALSE );
	}
	//���û���ID
	void SetConfId( u8 *pbyConfId, u32 dwLen )
	{
		if ( pbyConfId == NULL )
			return;
		
		u32 realLen = Minimum(dwLen, (u32)LEN_GUID);
		memcpy( m_abyConfId, pbyConfId, realLen );
		m_abyConfId[realLen] = '\0';
	}
	//��ȡ����ID
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	//���ô��λ������
	void SetListIdx( u16 wListIdx )
	{
		m_wListIdx = htons(wListIdx);
	}
	//��ȡ���λ������
	u16 GetListIdx()
	{
		return ntohs(m_wListIdx);
	}
	// ���û���E164����
	void SetConfE164( s8 * psConfE164, u8 byLen )
	{
		memset( m_sConfE164, 0, sizeof(m_sConfE164) );
		if ( NULL == psConfE164 || 0 == byLen )
		{
			return;
		}
		u8 byRealLen = Minimum( byLen, (u8)LEN_ALIAS );
		memcpy( m_sConfE164, psConfE164, byRealLen );
		return;
	}
	// ��ȡ����E164����
	s8 * GetConfE164( void )
	{
		return m_sConfE164;
	}
	// ��������ն���
	void SetMtNum( u8 byMtNum )
	{
		m_byMtNum = byMtNum;
	}
	// ��ȡ����ն���
	u8   GetMtNum( void )
	{
		return m_byMtNum;
	}
	// ���û���ʣ��ʱ��
	void SetRemainTime( u16 wRemainTime )
	{
		m_wRemainTime = htons(wRemainTime);
	}
	// ��ȡ����ʣ��ʱ��
	u16  GetRemainTime( void )
	{
		return ntohs(m_wRemainTime);
	}
	BOOL32 IsIdleConf(void)
	{
		return ( GetMtNum() == 0 ) ? TRUE : FALSE;
	}

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_dwIsContinue = bIsContinue ? htonl(1) : htonl(0);
    }
    BOOL32 IsContinue( void )
    {
        return ( ntohl(m_dwIsContinue) == 1 ) ? TRUE : FALSE;
    }
	void SetConfListNonStandard( BOOL32 bConfListNonStandard )
	{
		m_bConfListNonStandard = htonl(bConfListNonStandard);
	}
	BOOL32 IsConfListNonStandard()
	{
		return ntohl(m_bConfListNonStandard);
	}
	void SetReserved1( u32 dwReserved )
	{
		m_dwReserved1 = htonl( dwReserved );
	}
	u32 GetReserved1( void )
	{
		return ntohl( m_dwReserved1 );
	} 
}
TFacilityConfList_NSM,*PTFaclilityConfList_NSM;
//end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010





#ifdef WIN32
#pragma pack(1)
#define PACKED 
#endif // WIN32


// �ն˵�ַ��Ϣ

// ��ַ����
#define		ADDR_TYPE_IP		1
#define		ADDR_TYPE_ALIAS		2
// // 
// ��������
#define		ALIAS_H323ID		1
#define		ALIAS_E164			2
#define		ALIAS_EMAIL			3

typedef struct tagTerAddr
{
public :
	u8 GetAddrType( void ) { return byAddrType; }
	void SetAddrType( u8 byType ) { byAddrType = byType; }
	
	void SetIpAddr( u32 ip, u16 port )
	{
		dwIp = ip;
		wPort = htons( port );
	}
	u32 GetIpAddr( void ) { return dwIp; }
	u16 GetIpPort( void ) { return ntohs( wPort ); }

	//add by yj for ipv6
	void SetIpAddr_Ipv6( u8* ipv6, u16 port, s16 scopeID)
	{
		memcpy(dwIp_ipv6, ipv6, sizeof(dwIp_ipv6));
		wPort = htons( port );
        swScopeId = scopeID;
	}
	u8* GetIpAddr_Ipv6( void ) { return dwIp_ipv6; }
	s16 GetScopeId( void ) { return swScopeId; }
	//end

	u8 GetAliasType( void ) { return byAliasType; }
	s8* GetAliasName( void ) { return achAlias; }
	BOOL32 SetAlias( u8 byType, const s8* pchName, u8 byNameLen ) 
	{ 
		if ( pchName == NULL || byNameLen == 0 )
			return FALSE;
		
		byAliasType = byType; 
		memset( achAlias, 0, sizeof( achAlias ) );
		u8 byLen = Minimum( byNameLen, (u8)VALID_LEN_ALIAS );
		memcpy( achAlias, pchName, byLen );
		achAlias[byLen] = '\0';
		return TRUE;
	}
	
	tagTerAddr() 
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
	void Reset( void )
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
private :
	u8	byAddrType;		// ��ַ����
	u32 dwIp;			// IP(������)
	u16	wPort;			// �˿ں�
	u8	byAliasType;	// ��������
	s8 achAlias[ VALID_LEN_ALIAS + 1 ];

	//add by yj for ipv6
    u8	byAddrIpType;		// IP��ַ����
    u8 dwIp_ipv6[IPV6_NAME_LEN];			// IPv6��ַ(��������)
	s16 swScopeId;
	//end
}





#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
__attribute__ ((packed)) 
#endif
TTERADDRESS,*PTTERADDRESS;

#ifdef WIN32
#pragma pack()
#endif

#endif
