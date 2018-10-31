#ifndef _PA_MACRO_H_

// #ifdef WIN32
// #define PACALLBACK CALLBACK
// #else
// #define PACALLBACK
// #endif
#define     PA_MAX_CONF_ID_LEN 			16        //����ID����                         
#define     PA_MAX_CONF_NAME_LEN		64	      //�������ֳ���                       
#define     PA_MAX_CONF_E164_LEN	 	16	      //������볤��                      
#define     PA_CONF_CAPACITY			192		  //����������      
#define     PA_MAXNUM_INVITEMT			64        //����������������
#define		PA_MAX_CONF_NUM				32		  //��������
#define     PA_MAXLEN_PASSWORD			32		  //������󳤶�

// ���ȶ���   
#define		PA_MAX_H323ALIAS_LEN        64        // �ն˱�����󳤶� 
#define     LEN_ENCKEY_MAX		        (u16)64	  //(1-65535) 

#define		PA_MAX_AUDIO_STREAM_COUNT    10       //��Ƶ���ͨ����
#define		PA_MAX_VIDEO_STREAM_COUNT    10       //��Ƶ���ͨ����
#define     MAX_INSTANCE_PROTOCAL        192      //���ʵ����
#define		INVALID_CALLID				 0        //��Ч��CallId
#define     PA_MAX_PROXYSERVER_NAME_LEN  255      //�������ǽ��������󳤶�
#define     PA_MAX_NAME_LEN              PA_MAX_H323ALIAS_LEN
#define     PA_MAX_PASSWORD_LEN          16       // ������󳤶�   
#define     PA_INVALIDE_AID				  -1
#define		PA_LEN_256				     (u16)256
#define     PA_REGGISTER_INSTANCE        1
#define     PA_DEFAULT_MAXSENDRECVBUFFERSIZE   20480        //Ĭ���׽��ַ��ͽ��ջ����С
#define     PA_REGNAME_SIZE				       64           //ע���������
#define     PA_REGNAME_SIZE_CNS				   2            //ע���������
#define     PA_INVALIDE_CHANNELID		       0
#define     PA_XMLBUFFER_LEN			       2048
#define     PA_MSGBUFFER_LEN				   65536
#define     PA_NODECHANGEINFO		           64
#define     PA_REFRESH_LIST_FIVE		       5
#define     PA_REFRESH_LIST_THREE	           3
#define		PA_MAX_CHAN_NUM				       16
#define     PA_MAX_EPID_LEN				       64
#define     PA_INVALID_VALUE                   0xffff
#define		PA_CONTACT_ADDR_SIZE               5

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef LOWORD16
#define LOWORD16(l)     ((u16)(l))
#endif

#ifndef HIWORD16
#define HIWORD16(l)     ((u16)(((u32)(l) >> 16) & 0xFFFF))
#endif

#ifndef MAKEDWORD
#define MAKEDWORD(l,h)  ((u32)(((u16)(l)) | ((u32)((u16)(h))) << 16))
#endif
#define PA_OK TRUE
#define PA_FAILED FALSE

#ifdef WIN32
#define PA_CALLBACK __cdecl
#else
#define PA_CALLBACK
#endif

#endif
