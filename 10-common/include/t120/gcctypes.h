#ifndef _GCC_TYPES_H
#define _GCC_TYPES_H

//#include "../../common/PlatformSystem.h"

#include <ptlib.h>
#include <ptclib/asner.h>
#include "mcstypes.h"
#include <list>

#define MAX_HANDLE_COUNT    0xefffffff

namespace Gcc 
{
/*!
* Container for a Numeric and a Text String (Text String is optional).
* Might work as a selector as well depending on the context. When used
* as a selector only one of the numeric or text string is used, which is
* decided by the hasTextField flag.
	*/
	class NumericTextString
	{
	public:
		NumericTextString()	: m_hasTextField(false)
		{}
		NumericTextString(const PString &numeric) : m_numeric(numeric), m_hasTextField(false)
		{}
		NumericTextString(const PString &numeric, const PString &text) : m_numeric(numeric), m_text(text), m_hasTextField(true)
		{}
		
		bool operator ==(const NumericTextString &second) const
		{
			if (m_numeric == second.m_numeric) 
			{
				if (m_hasTextField && second.m_hasTextField)
					return (m_text == second.m_text) ? true : false;
				return true;
			}
			return false;
		}
		
		bool HasTextField() const 
		{
			return m_hasTextField; 
		}

		void SetHasTextField(bool b) 
		{ 
			m_hasTextField = b; 
		}
		
		PString &Numeric() 
		{ 
			return m_numeric; 
		}

		const PString &Numeric() const 
		{ 
			return m_numeric; 
		}

		PString &Text() 
		{ 
			return m_text; 
		}

		const PString &Text() const 
		{
			return m_text; 
		}
		
	private:
		PString m_numeric;
		PString m_text;
		bool m_hasTextField;
	};
	
	typedef enum 
	{
		NtTerminal		= 0,
		NtMultipointTerminal	= 1,
		NtMCU			= 2
	} NodeType;
	
	typedef enum 
	{
		CmConventionalOnly	= 0,
		CmCountedOnly		= 1,
		CmAnonymousOnly		= 2,
		CmConventionalControl	= 3,
		CmUnrestrictedMode	= 4,
		CmNonStandardMode	= 5
	} ConferenceMode;
	
	typedef enum 
	{
		TmAutomatic		= 0,
		TmManual		= 1
	} TerminationMethod;
	
	typedef enum
	{
		CpTerminate,
		CpEjectUser,
		CpAdd,
		CpLockUnlock,
		CpTransfer
	} ConductorPrivileges;

    /*====================================================================
    ���� �� ConferenceDescriptor
    ���� �� ���������ӣ������˻���ĸ�����Ϥ
    ====================================================================*/
    class ConferenceDescriptor
	{
	public:
		ConferenceDescriptor();
		ConferenceDescriptor(const ConferenceDescriptor& confDesc);
		~ConferenceDescriptor();
		ConferenceDescriptor& operator = (const ConferenceDescriptor& cConfDesc);

        // �õ�����ID
        u32 GetConfId()
        {
            return m_name.Numeric().AsInteger();
        }
        // �õ��ڵ��ڻ����е�����
        PString &NodeName()
        {
            return m_strNodeName;
        }
        // �õ���������
		NumericTextString &Name() 
		{
			return m_name; 
		}
        // �õ���������
		const NumericTextString &Name() const 
		{
			return m_name; 
		}
		
		bool IsLocked() const 
		{
			return m_locked;
		}

		void SetLocked(bool b)
		{ 
			m_locked = b;
		}

		bool IsListed() const 
		{
			return m_listed;
		}

		void SetListed(bool b) 
		{
			m_listed = b;
		}

		bool IsConductible() const 
		{ 
			return m_conductible; 
		}

		void SetConductible(bool b) 
		{ 
			m_conductible = b;
		}

        const PString& GetConductorAddr() const
        {
            return m_strConductorAddr;
        }

        void SetConductorAddr(const PString& strAddr)
        {
            m_strConductorAddr = strAddr;
        }
		bool IsPasswordInTheClearRequired() const 
		{ 
			return m_passwordInTheClearRequired;
		}

		void SetPasswordInTheClearRequired(bool b) 
		{ 
			m_passwordInTheClearRequired = b;
		}

		TerminationMethod GetTerminationMethod() const 
		{ 
			return m_terminationMethod; 
		}

		void SetTerminationMethod(TerminationMethod t) 
		{ 
			m_terminationMethod = t; 
		}

		
		const PString &GetNameModifier() const;
		void SetNameModifier(const PString &);
		const PString &GetDescription() const;
		void SetDescription(const PString &);
		
		bool IsDefaultConference() const;
		void SetDefaultConference(bool);
		ConferenceMode GetConferenceMode() const;
		void SetConferenceMode(ConferenceMode);
		
		bool HasNameModifier() const;
		bool HasDescription() const;
		bool HasDefaultFlag() const;
		bool HasConferenceMode() const;

		typedef std::list<ConductorPrivileges> ConductorPrivilegesList;
		
		ConductorPrivilegesList& GetConductorPrivileges() 
		{
			return m_conductorPrivileges;
		}

		ConductorPrivilegesList& GetConductedPrivileges() 
		{
			return m_conductedPrivileges;
		}

		ConductorPrivilegesList& GetNonConductedPrivileges() 
		{
			return m_nonConductedPrivileges;
		}

		void SetBandWidth(unsigned int nBandWidth)
		{
			m_nBandWidth = nBandWidth;
		}

		unsigned int GetBandWidth() const
		{
			return m_nBandWidth;
		}

		void SetMyAppMask(BYTE byAppMask)
		{
			m_byMyApeMask = byAppMask;
		}

		BYTE GetMyAppMask() const
		{
			return m_byMyApeMask;
		}

		void SetNormalApeMask(BYTE byApeMask)
		{
			m_byNormalApeMask = byApeMask;
		}

		BYTE GetNormalApeMask() const
		{
			return m_byNormalApeMask;
		}

		void SetConductorApeMask(BYTE byApeMask)
		{
			m_byConductorApeMask = byApeMask;
		}

		BYTE GetConductorApeMask() const
		{
			return m_byConductorApeMask;
		}

        const void* GetUserData() const
		{
			return m_pUserData;
		}

		void SetUserData(void* pUserData)
		{
			m_pUserData = pUserData;
		}

		ConductorPrivilegesList m_conductorPrivileges;
		ConductorPrivilegesList m_conductedPrivileges;
		ConductorPrivilegesList m_nonConductedPrivileges;
	private:
        // �ڵ��ڻ����е�����
        PString m_strNodeName;
        // ��������
		NumericTextString m_name;
        // �����������η�
        PString m_nameModifier;
        // ��������
		PString m_description;
        // �����Ƿ�����
		bool m_locked;
        // �����Ƿ��г��ڡ������ѯ���Ľ����
		bool m_listed;
        // �����Ƿ���ϯģʽ
		bool m_conductible;
        // ������ϯ��IP��ַ�Ͷ˿�
        PString m_strConductorAddr;
        // �Ƿ���Ҫ����
		bool m_passwordInTheClearRequired;	
        // δʹ��
		bool m_defaultConferenceFlag;
        // ����ģʽ
		ConferenceMode m_conferenceMode;
        // �������ģʽ
		TerminationMethod m_terminationMethod;
        // ��ѡ
		unsigned int m_optional;
        // ����
		unsigned int m_nBandWidth;
        // ���ڵ��ڸû����е�APE����
		BYTE m_byMyApeMask;
        // �û����еķ���ϯ�ڵ�APE����
		BYTE m_byNormalApeMask;
        // �û����е���ϯ�ڵ�APE����
		BYTE m_byConductorApeMask;
        // �û�����
		void* m_pUserData;
	};
	
	typedef enum 
	{
		CrSuccess,
		CrUserRejected,
		CrResourcesNotAvaiable,
		CrRejectedForSymmetryBreaking,
		CrLockedConferenceNotSupported,
		CrInvalidConference,
		CrInvalidPassword,
		CrInvalidConvenerPassword,
		CrChallengeResponseRequired,
		CrInvalidChallengeResponse
	} ConferenceResponseResult;
	
	typedef enum 
	{
		CtRnUserInitiated,
		CtRnTimedConference
	} ConferenceTerminateReason;
	
	typedef enum 
	{
		NcConventional,
		NcCounted,
		NcAnonymous,
		NcNonStandard
	} NodeCategory;
	
	typedef enum 
	{
		EpGrant,
		EpRevoke
	} EnrollPermission;
	
	typedef enum 
	{
		EurUserInitiated,
		EurHigherNodeDisconnected,
		EurNodeEjected
	} EjectUserReason;
	
	typedef enum 
	{
		EurtSuccess,
		EurtInvalidRequester,
		EurtInvalidNode
	} EjectUserResult;
	
	typedef enum
	{
		AcrtSuccess,
		AcrtInvalidConference,
		AcrtNotConductor,
		AcrtRejected
	} AssignConductorResult;

	typedef enum
	{
		RcrtSuccess,
		RcrtNotConductor,
		RcrtNotOwnConductor,
		RcrtRejected
	} ReleaseConductorResult;

	typedef enum
	{
		PcrtSuccess,
		PcrtInvalidConference,
		PcrtNotConductor
	} PleaseConductorResult;

	typedef enum
	{ 
		GcrtSuccess,
		GcrtInvalidConference,
		GcrtNotConductor,
		GcrtRejected
	} GiveConductorResult;

	//���Ľڵ�λ��
	typedef enum
	{
		CNPSelf,        // ���ڵ�
		CNPLocal,       // �������ڵĽڵ� 
		CNPRemote,      // �Ǳ������Ľڵ� 
        CNPDirectLow,   // ֱ���¼��ڵ�
        CNPDirectAbove  // ֱ���ϼ��ڵ�
	} ConfNodePos;

    class Key : public PString 
    {
    public:
        enum Type 
        {
            Standard,
            H221NonStandard
        };
        
        Key() : m_type(Standard) {}
        Key(Type type, const PString &key = PString::Empty()) : PString(key), m_type(type)
        {}
        Key( const Key& key )
        {
            m_type = key.m_type;          
            *((PString *)this) = key;
        }
        
        PASN_ObjectId AsObjectId() const 
        { 
            return PASN_ObjectId(*this);
        }
        
        Key &operator=(const Key &);
        
        Type GetType() const 
        { 
            return m_type;
        }
        
        void SetType(Type type) 
        { 
            m_type = type; 
        }
    private:
        Type m_type;
    };
	
	typedef enum
	{
		CtStatic,
		CtDynamicMulticast,
		CtDynamicPrivate,
		CtDynamicUserId
	} ChannelType;
	
    class CapabilityId
    {
    public:
        enum Type 
        {
            Standard,
            NonStandard
        };
        
        CapabilityId() : m_type(Standard), m_standard(0)
        {}
        
        CapabilityId( int value ) : m_type(Standard), m_standard(value)
        {}
        
        CapabilityId( const Key& key ) : m_type(NonStandard), m_standard(0), m_key(key)
        {}
        
        CapabilityId( const CapabilityId& capid )
        {
            m_type = capid.m_type;
            m_standard = capid.m_standard;
            m_key = capid.m_key;
        }
        
        operator int &()
        { 
            return m_standard;
        }
        
        operator const int &() const 
        {
            return m_standard;
        }
        
        operator Key &() 
        {
            return m_key;
        }
        
        operator const Key &() const 
        {
            return m_key; 
        }
        
        CapabilityId &operator=(const CapabilityId &);
        
        Type GetType() const 
        { 
            return m_type; 
        }
        
        void SetType(Type type)
        { 
            m_type = type; 
        }
    private:
        Type m_type;
        int m_standard;
        Key m_key;
    };
    
    class CapabilityClass
    {
    public:
        enum Type
        {
            Logical,
            UnsignedMin,
            UnsignedMax
        };
        
        CapabilityClass( Type type , int value ) : m_type(type), m_value(value)
        {}
        
        CapabilityClass( const CapabilityClass& capclass )
        {
            m_type = capclass.m_type;
            m_value = capclass.m_value;
        }
        
        operator int &()
        { 
            return m_value;
        }
        
        operator const int &() const 
        { 
            return m_value; 
        }
        
        Type GetType() const 
        {
            return m_type; 
        }
        
    private:
        Type m_type;
        int m_value;
    };


    // APE��������
    typedef struct ApplicationCapability
    {
        ApplicationCapability(CapabilityId capid , Gcc::CapabilityClass::Type classtype , int classvalue , int numofEntities )
            : m_capabilityId(capid), 
            m_capabilityClass( classtype, classvalue) , 
            m_numberOfEntities(numofEntities)
        {
        }
        ApplicationCapability( int idvalue , Gcc::CapabilityClass::Type classtype , int classvalue , int numofEntities )
            : m_capabilityId(idvalue), 
            m_capabilityClass( classtype, classvalue) , 
            m_numberOfEntities(numofEntities)
        {
        }
        ApplicationCapability( const Gcc::Key &key , Gcc::CapabilityClass::Type classtype , int classvalue , int numofEntities )
            : m_capabilityId(key) , 
            m_capabilityClass( classtype, classvalue) , 
            m_numberOfEntities(numofEntities)
        {
        }
        ApplicationCapability( const ApplicationCapability& apeCap )
            : m_capabilityId( apeCap.m_capabilityId ) , 
            m_capabilityClass( apeCap.m_capabilityClass ) , 
            m_numberOfEntities(apeCap.m_numberOfEntities )
        {
        }
	    CapabilityId m_capabilityId;
	    CapabilityClass m_capabilityClass;
	    u32 m_numberOfEntities;
    } TApplicationCapability;
    // ��������Ϣ
    typedef std::list<TApplicationCapability> TApeCapabilitiesList;



	class SessionKey
	{
	public:
		SessionKey() {}
		SessionKey(const Key &key, TChannelId session = 0) : m_protocolKey(key), m_session(session)
		{}
		SessionKey(const SessionKey &key) : m_protocolKey(key.m_protocolKey), m_session(key.m_session)
		{}
		
		const Key &ProtocolKey() const 
		{
			return m_protocolKey; 
		}

		Key &ProtocolKey()
		{ 
			return m_protocolKey; 
		}
		
		const TChannelId &SessionId() const 
		{ 
			return m_session; 
		}

		TChannelId &SessionId()
		{
			return m_session; 
		}
		
	private:
		Key m_protocolKey;
		TChannelId m_session;
	};
    

	class ApplicationRecord
	{
	public:
		ApplicationRecord(bool = false, bool = false);
		ApplicationRecord(const ApplicationRecord &);
		
		bool HasStartupChannel() const;
		void SetHasStartupChannel(bool);
		bool HasApplicationUserId() const;
		void SetHasApplicationUserId(bool);
		bool HasNonCollapsingCapabilities() const;
		void SetHasNonCollapsingCapabilities(bool);
		
		typedef struct NonCollapsingCapability 
		{
			CapabilityId m_id;
			PBYTEArray m_applicationData;
		} NonCollapsingCapability;
		
		typedef std::list<NonCollapsingCapability> NonCollapsingCapabilities;
		
		bool IsActive() const
		{ 
			return m_active;
		}

		void SetActive(bool b)
		{
			m_active = b; 
		}

		bool IsConductingCapable() const 
		{ 
			return m_conductingCapable;
		}

		void SetConductingCapable(bool b) 
		{ 
			m_conductingCapable = b; 
		}

		ChannelType GetStartupChannel() const 
		{ 
			return m_startupChannel;
		}

		void SetStartupChannel(ChannelType t) 
		{ 
			SetHasStartupChannel(true); m_startupChannel = t; 
		}

		TUserId GetApplicationUserId() const 
		{
			return m_applicationUserId;
		}

		void SetApplicationUserId(TUserId u) 
		{ 
			SetHasApplicationUserId(true); m_applicationUserId = u; 
		}
				
		NonCollapsingCapabilities &GetNonCollapsingCapabilities() 
		{ 
			return m_nonCollapsingCapabilities; 
		}

		const NonCollapsingCapabilities &GetNonCollapsingCapabilities() const 
		{
			return m_nonCollapsingCapabilities;
		}
		
	private:
		unsigned int m_options;
		
		bool m_active;
		bool m_conductingCapable;
		ChannelType m_startupChannel;
		TUserId m_applicationUserId;
		NonCollapsingCapabilities m_nonCollapsingCapabilities;
	};
	
	class UserData 
	{
	public:
		UserData() {}
		UserData(const Key &key, const PBYTEArray &value) : m_key(key), m_value(value)
		{}
	private:
		Key m_key;
		PBYTEArray m_value;
	};	

	typedef enum
	{
        AmAppShareDisable = 0x0a,       // 0000 1010
		AmAppChatDisable = 0x28,        // 0010 1000
		AmAppWhiteboardDisable = 0x49,  // 0100 1001
		AmAppFileTransDisable = 0x18,   // 0001 1000
		AmAppAllAllowed = 0x08,         // 0000 1000
		AmAppAllDisable = 0x7b	        // 0111 1011
	} AppMask;

#define NIM_IP		"T\0C\0P\0:\0"
#define NIM_VER		"V\0E\0R\0:\0"
#define NIM_EMAIL	"E\0M\0A\0I\0L\0:\0"
#define NIM_LOC		"L\0O\0C\0A\0T\0I\0O\0N\0:\0"
#define NIM_PHONE	"P\0H\0O\0N\0E\0N\0U\0M\0:\0"

	typedef enum
	{
		NimIP = 1,
		NimVer = 2,
		NimEmail = 4,
		NimLoc = 8,
		NimPhone = 16
	} NodeInfoMask;

}

#endif

