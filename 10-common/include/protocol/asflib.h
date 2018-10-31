/************************************************************
//  �� �� ����  asflib.h
//  ����ļ���  asflib.cpp
//	��    �ߣ�	�Ժ���
//	����ʱ�䣺	2005-08-29
//	�޸�ʱ�䣺	
************************************************************/

#ifndef __ASF_LIB__
#define __ASF_LIB__

#if __Win32__ || WIN32
#pragma pack(push, 1)				//	��һ���ֽڵĽṹ���룬��ֹ��ͬ�ı��������´���
#endif	//WIN32


/************************************************************
*************************************************************

//����ASF�ļ���д�ӿڵ����ݽṹ

*************************************************************
*************************************************************/
#include "kdvtype.h"
#include "osp.h"

#define OUT		// ��ʾ�����Ĳ������������
#define IN		// ��ʾ�����Ĳ������������

#define MAX_ASF_READER					400		//���ɲ���·��
#define MAX_ASF_PATH_LENTGTH			128		//asf�ļ�·����󳤶�,������,�ϲ㲻�ÿ���

#define COPY_DWORD(achByte, dwInt)          do{*(achByte) =   (u8)(((u32)dwInt)& 0xff) ; \
                                               *(achByte+1) = (u8)(((u32)dwInt >> 8)& 0xff) ; \
                                               *(achByte+2) = (u8)(((u32)dwInt >> 16)& 0xff); \
                                               *(achByte+3) = (u8)(((u32)dwInt >> 24)& 0xff); \
                                               } while(0);

#define COPY_WORD(achByte, wInt)             do{*(achByte) =   (u8)(((u16)wInt)& 0xff) ; \
                                                *(achByte+1) = (u8)(((u16)wInt >> 8)& 0xff); \
                                               } while(0);

typedef void* HTimer;

#ifndef PTR_CHECK_RET
#define PTR_CHECK_RET(p, r)  do{ if(!(p)) { OspPrintf(1, 0, "Point %s is null\n", #p); return (r); } }while(0)
#endif

#define CHECKSTREAMNUMBER(a)	(((a) >= 1 && (a) <= 127) ? TRUE : FALSE)

//��������Ӧ��ý������ʱ�õ��Ľṹ
typedef struct tagAudioTypeInfo 
{
	u8 byAudioMediaType;//��Ƶý������mp3,pcma,pcmu,g728,g729...
	u8 byAudioMode;//��Ƶģʽ
}TAudioTypeInfo
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

typedef union tagMediaDetailTypeIfo 
{
	u8 byVideoMediaType;//��Ƶý������h261,h263,h264,mp4...
	TAudioTypeInfo tAudioTypeInfo;
}UnionMediaDetailTypeInfo
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

//  �ļ�������ؽṹ 
typedef struct tagASFFileProperty{
	u64		qwTotalFileSize;				// �ļ���С
	u64		qwCreateDate;					// �ļ�����ʱ�䣬����FILETIME��ʽ
	u64		qwDataPacketsCount;				// ���������ݰ�����
	u64		qwPlayDuration;					// �ļ����ŵ���ʱ�䳤��(100nano-second)
	u64		qwSendDuration;					// �ļ����͵���ʱ�䳤��(100nano-second)
	u64		qwPreroll;					// �ļ���ʼ��ƫ��ʱ��
	BOOL32		bIsBroadCast;					// �ļ�/�ֳ����ı�ʶ
	u32		dwDataPacketSize;				// �������ݰ��Ĵ�С
	u32		dwMaximumBitrate;				// �������� bits per second for entire file.
	u16		wAudioStreamCount;				// ��Ƶ������Ŀ
	u16		wVideoStreamCount;				// ��Ƶ������Ŀ
} TASFFileProperty
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

//  �����������Խṹ 
typedef struct tagContentDescriptionProperty{
	u16		wTitleLength;					// ���ݱ��ⳤ��
	u16		wAuthorLength;					// �������߳���
	u16		wCopyrightLength;				// ���ݰ�Ȩ����
	u16		wDescriptionLength;				// ������������
	u16*	pwTitle;						// Unicode�ַ�����ʾ�����ݱ���
	u16*	pwAuthor;						// Unicode�ַ�����ʾ����������
	u16*	pwCopyright;					// Unicode�ַ�����ʾ�����ݰ�Ȩ
	u16*	pwDescription;					// Unicode�ַ�����ʾ������������Ϣ
} TContentDescriptionProperty
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

// ASF Audio Media Type
typedef struct tagAudioMediaInfo{
	u16		wCodecID_FormatTag;				// ��ƵCodec��ʶ
	u16		wNumberOfChannels;				// ��Ƶͨ����				
	u32		dwSamplesPerSecond;				// ������
	u32		dwAverageNumberOfBytesPerSecond;// ƽ������ Bytes / Second
	u16		wBlockAlignment;				// ������ֽ��� 
	u16		wBitsPerSample;					// ÿ�������ı�������Ϊ8����16
	u16		wCodecSpecificDataSize;			// ��ƵCodec��ʶ
	u8*		pbyCodecSpecificData;			// ��ƵCodec��ʶ
} TAudioMediaInfo
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;							// �൱�� WAVEFORMATEX �ṹ

// Spread Audio
typedef struct tagSpreadAudio{
	u8		bySpan;							// ��Ƶ���ݰ�����ſ��
	u16		wVirtualPacketLength;			// ��Ƶ���ݰ����غɳ���
	u16		wVirtualChunkLength;			// ��Ƶ���ݰ����غɳ���
	u16		wSilenceDataLength;				// �������ݳ���
	u8*		pbySilenceData;					// ��������
} TSpreadAudio
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

// ASF Video Media Type
typedef struct tagFormatDataStruct{
	u32		dwFormatDataSize;				// ��Ƶ�������ݴ�С
	s32		dwImageWidth;					// ��Ƶ������
	s32		dwImageHeight;					// ��Ƶ����߶�
	u16		wReserved;						// ��������
	u16		wBitsPerPixelCount;				// ÿ���صı�����
	u32		dwCompressionID;				// ��Ƶѹ��Codec��ʶ
	u32		dwImageSize;					// ����ߴ�
	s32		nHorizontalPixelsPerMeter;		// ˮƽ�ֱ���
	s32		nVerticalPixelsPerMeter;		// ��ֱ����ֱ���
	u32		dwColorsUsedCount;				// ��ɫ��
	u32		dwImportantColorsCount;			// 
	u8*		pbyCodecSpecificData;			// Codec ��չ��Ϣ
} TFormatData
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;								// �൱�� BITMAPINFOHEADER �ṹ

typedef struct tagVideoMediaInfo{
	u32		dwEncodedImageWidth;			// ��Ƶ������
	u32		dwEncodedImageHeight;			// ��Ƶ�����
	u16		wFormatDataSize;				// ��Ƶ�������ݴ�С
	TFormatData 	tFormatData;			
} TVideoMediaInfo
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

typedef struct tarOtherMediaInfo{
	u32		dwInfoLength;					// ����ý�����ݳ���
	u8		*pbyInfoData;					// ����ý������ָ��
} TOtherMediaInfo
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;


//  �����Խṹ 
typedef struct tagStreamProperty{
	u16		wStreamType;					// ������
	u8		byStreamNumber;					// �����
	u16		wErrorCorrectType;				// ������������	
	u32		dwErrorCorrectDataLength;		// ������������	
	u8		*pbyErrorCorrectData;			// ������������	
	BOOL32	bIsEncryptedContent;			// �Ƿ�����ݲ������ر���
	u32		dwAverageBitrate;				// ƽ��������  bits/s

	union{
		TAudioMediaInfo	 tAudioMediaInfo;   // ��Ƶ��������
		TVideoMediaInfo	 tVideoMediaInfo;	// ��Ƶ��������
		TOtherMediaInfo	 tOtherMediaInfo;	// ����ý����������
	};
} TStreamProperty
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;


// ���������������ṹ
struct TStreamListEntry {		
	TStreamProperty		tStreamProperty;	// �����������
	TStreamListEntry	*pNextStream;		// ��һ���������ָ��
	u8 					byStreamID;			// �������˳���
	u8					byAlignedField;		//�����ֽ�,������
	u16					wAlignedField;		//�����ֽ�,������

} 
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

//  �غ�����
typedef struct tagStreamDataPayload
{
	u8		byStreamNumber;					// �����			
	u32		dwMediaObjectNumber;			// ֡���
	BOOL32	bIsKeyFrame;					// �Ƿ�Ϊ�ؼ�֡
	u32		dwPresentationTime;				// ֡ʱ����Ϣ��ʱ�����
	u32		dwPayloadDataSize;				// ���ݳ���
	u8		*pbyPayloadData;				// ��Ч����
	
}TStreamDataPayload
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

//  ��־����
typedef struct tagMarkers{
	u64		qwOffset;						// ��־���ļ��е�λ��ƫ��
	u64		qwPresentationTime;				// ��־��ʾ��ʱ��
	u32		dwMarkerDescriptionLength;		// ��־����������
	u8		*pbyMarkerDescription;			// ��־��������Ϣ
} TMarkerStruct
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;


//  ����ű�����
typedef struct tagCommands{
	u32		dwPresentationTime;				// �ű�ִ�е�ʱ��
	u16		wCommandsTypeLength;			// �ű������ͳ���
	u16		*pwCommandsType;				// �ű�������
	u16		wCommandNameLength;				// �ű������Ƴ���
	u16		*pwCommandName;				// �ű�������
} TCommandStruct
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif
;

// ����֡���ݺ�Ļص�����
typedef void (* ASFFrameProcCallBack)(u32 dwUser, u32 dwStatus, u32 dwNextFrameTimeStamp, TStreamDataPayload *piFrameData);

//  ��������
enum {
		Audio_Media_Type				= 0,
		Video_Media_Type				= 1,
		Command_Media_Type				= 2,
		JFIF_Media_Type					= 3,
		Degradable_JPEG_Media_Type		= 4,
		File_Transfer_Media_Type		= 5,
		Binary_Media_Type				= 6,
		Unknown_Media_Type				= 7
};

typedef u16 ASF_MEDIA_TYPE;


//����ģʽ����������ţ�����
//05.7.12
enum {
    NORMAL_PLAY         = 0,
    FAST_PLAY           = 1,
    SLOW_PLAY           = 2
};

//���ű���
enum{
	NORMAL_SPEED		= 1,			//�����ٶ�
	TWICE_SPEED			= 2,			//������
	FOUR_TIMES_SPEED	= 4				//�ı���
};

//���򲥷�ʱ��״̬
enum{
		ASF_Read_Status_Wait			= 0,
		ASF_Read_Status_Playing			= 1,
		ASF_Read_Status_EOF				= 2,
		ASF_Read_Status_Closed			= 3,
		ASF_Read_Status_SINGLE_FRAME	= 4	//��֡����05.8.11
};
typedef u16	ASF_READ_STATUS;


//  ������������ 
enum {
		No_Error_Correction_Type 		= 0,
		Audio_Spread_Type 				= 1,
		Unknown_Error_Type 				= 2
};
typedef u16 ERROR_CORRECTION_TYPE;


//  �������صĴ�����
#ifndef __ASF_ERROR_CODE__
#define __ASF_ERROR_CODE__
enum
{
		ASF_Error_NoError				= 0,   // û�д�����ȷ����
		ASF_Error_FileNotFound			= 1,   // �ļ�û���ҵ�
		ASF_Error_InvalidASFFile		= 2,	// ��Ч��ASF�ļ�
		ASF_Error_ObjectNotFound 		= 3,	// ����û���ҵ�
		ASF_Error_BadIndex				= 4,	// ����Ķ�������
		ASF_Error_ValueNotFound			= 5,	// û���ҵ���Ӧ��ֵ
		ASF_Error_BadArgument			= 6,	// ����Ĳ���
		ASF_Error_ReadOnly				= 7,	// �ļ�ֻ������
		ASF_Error_NotEnoughSpace		= 8,	// �洢�ռ䲻�����
		ASF_Error_InternalError  		= 9,	// �޷������ڴ���ڲ�����
		ASF_Error_ReadFileError  		= 10,	// ���ļ��ڲ�����
		ASF_Error_WriteFileError  		= 11,	// д�ļ��ڲ�����
		ASF_Error_SeekFileError  		= 12,	// �����ļ�����
		ASF_Error_CreateFileError  		= 13,	// �����ļ�����
		ASF_Error_CreateThreadError		= 14,	// �����ļ�����
		ASF_Error_ObjectNULLError		= 15,	// ����ָ��Ϊ�յĴ���
		ASF_Error_TooMuchVideoStrream	= 16,	//
		ASF_Error_NotSupportedCodec		= 17,	//
		ASF_Error_FileEnd				= 18,	//
		ASF_Error_UnknownError			= 19,	// �޷�ȷ���Ĵ���		
		ASF_Error_WriteMemError			= 20	// [8/10/2011 liuxu] д�ڴ����
};
typedef u16 Error_Code;

static char * sASF_ErrorInfo[] = 
{
	/* 0  */ "No Error, return OK!" ,
	/* 1  */ "Open the file FAILED for ASF file does not exist or the file cannot be open with \"rb\" mode!" ,
	/* 2  */ "The opened file is invalid, it maybe not keep to ASF Specification, or occur some Error when parsing the file !"  ,
	/* 3  */ "Cannot find Object by the given index!"   ,
	/* 4  */ "It is a wrong index of Object!"  ,
	/* 5  */ "Cannot get value by the given index!" ,
	/* 6  */ "The input parameter is illegal,for example pointer is NULL or parameter is not in the range!"  ,
	/* 7  */ "The file is only for reading!" ,
	/* 8  */ "There is not enough space for write or new!" ,
	/* 9  */ "Failed in newing space for pointer!" ,
	/* 10 */ "Read file ERROR for the get bytes is not equal to the one that should get!"  ,
	/* 11 */ "Write file ERROR for the put bytes is not equal to the one that should put!"  ,
	/* 12 */ "Seek file ERROR !" ,
	/* 13 */ "Create file ERROR !" ,
	/* 14 */ "Create thread ERROR!" ,
	/* 15 */ "Input pointer is NULL!" ,
	/* 16 */ "there is too much stream or video stream!",
	/* 17 */ "not supported codec format id, cannot play the asf file!",
	/* 18 */ "to file end!",
	/* 19 */ "There is an unknown Error!" 	
};

#endif  // __ASF_ERROR_CODE__

// �ļ������ID�������õ�����Ϣ�Ͷ����ʶ
// ��ʶ����3λ�������
// 1 �� ��  ���ļ�ͷ��Ϣ��ص�ͷ������
// 2 �� ��  �����ݶ�����صĶ��� 
// 3 �� ��  ��������Ϣ��صĶ���
// 4 �� ��  �ۺ��ԵĶ���
// 9 �� ��  ��Ч�Ķ���
enum
{
		// ASF TOP-LEVEL HEADER OBJECT
		ASF_ObjectID_Header_Object                       = 100,
		ASF_ObjectID_File_Properties_Object              = 101,
		ASF_ObjectID_Stream_Properties_Object            = 102,
		ASF_ObjectID_Header_Extension_Object             = 103,
		ASF_ObjectID_Codec_List_Object                   = 104,
		ASF_ObjectID_Script_Command_Object               = 105,
		ASF_ObjectID_Marker_Object                       = 106,
		ASF_ObjectID_Bitrate_Mutual_Exclusion_Object     = 107,
		ASF_ObjectID_Error_Correction_Object             = 108,
		ASF_ObjectID_Content_Description_Object          = 109,
		ASF_ObjectID_Extended_Content_Description_Object = 110,
		ASF_ObjectID_Content_Branding_Object             = 111,
		ASF_ObjectID_Stream_Bitrate_Properties_Object    = 112,
		ASF_ObjectID_Content_Encryption_Object           = 113,
		ASF_ObjectID_Extended_Content_Encryption_Object  = 114,
		ASF_ObjectID_Alt_Extended_Content_Encryption_Object = 115,
		ASF_ObjectID_Digital_Signature_Object            = 116,
		ASF_ObjectID_Padding_Object                      = 117, 
		
		// ASF TOP-LEVEL DATA OBJECT
		ASF_ObjectID_Data_Object						= 200,
		ASF_ObjectID_Packet_Object						= 201,        
		ASF_ObjectID_DataErrorCorrection_Object			= 202,
		ASF_ObjectID_DataParseInfomation_Object			= 203,
		ASF_ObjectID_DataPadding_Object					= 204,
		ASF_ObjectID_DataPayload_Object					= 205,
		
		// ASF TOP-LEVEL INDEX OBJECTS       
		ASF_ObjectID_Simple_Index_Object                 = 300,
		ASF_ObjectID_Index_Object                        = 301,
		ASF_ObjectID_Media_Object_Index_Object           = 302,
		ASF_ObjectID_Timecode_Index_Object               = 303,
		
		// ASF ALL OBJECT		
		ASF_ObjectID_ALL_Object							 = 400,
		ASF_ObjectID_ALL_Header_Object					 = 401,
		ASF_ObjectID_ALL_Frame_Object					 = 402,

		// Present Nothing 
		ASF_ObjectID_Nothing_Object						 = 900
		
};
typedef u16 ASFObjectID;


class CKdvASFFile;
/*********************************************************
**********************************************************

����ASF�ļ���д�ӿ���

**********************************************************
**********************************************************/


class CKdvASFFileWriter
{
public:
	//
	// Constructors and destructor.
	CKdvASFFileWriter(void);
	~CKdvASFFileWriter(void);

	//  дASF�ļ��ĳ�ʼ������
	u16	Open(IN const char * pFileName);

	//  ����ASF�ļ���������Ϣ
	u16	SetASFFileProperty(IN TASFFileProperty * pFileProperty);
	
	//  ����ASF�ļ������ݰ�Ȩ��Ϣ
	u16	SetContentProperty(IN TContentDescriptionProperty * pContentDescriptionProperty);

	//�����Ƿ�������������
	u16  SetGenerateSimpleIndexObject(IN BOOL32 isGenarate = false);
		
	//  �����úõ�����ӵ��ļ�ͷ��
	u16  AddStream(IN TStreamProperty * pStreamProperty);

	//  ��ʼдASF�ļ������ݲ���
	u16  BeginWriting(void);

	//  ���ղ�ͬ�������д֡����
	u16  WriteSample(IN u8 byStreamNumber, IN u8 * pDataBuffer, IN u32 dwBufferSize,
					 IN BOOL32 bIsKeyFrame, IN u32 dwTimeStamp, IN u16 wDuration, OUT u32* pdwFileSize = NULL);
	
	//  ����д֡����
	u16  EndWriting(void);
	
	//  �ر��ļ����ͷ���Դ�ռ�
	u16  Close(void);


	//  �����Ƿ���Ҫ����Ļ���������Ϣ
	u16  SetDebugInfo(IN u16 wObjectID);
	//  ���ݺ����ķ���ֵ��ȡ��ϸ�Ĵ�����Ϣ
	char    *GetErrorInfo(IN u16 wErrorIndex);
	//  ר������ʾ���������ݡ���ÿ���ֽڵ�ֵ������ʮ�����Ƶ�������ʾ����
	void	ShowDataWithHex(IN u8 * pData, IN u32 dwDataLength);	
	
protected:

	CKdvASFFile			*m_pASFFile;				//  ASF�ļ��������ָ��
	
	u16					m_wObjectIDForDebug;		//	��ʾҪ���Ե�Ŀ�����ID
	
};



/********************************************************
*********************************************************

�ļ�����ASF�ļ��Ķ��ӿ���

*********************************************************
*********************************************************/


class CKdvASFFileReader
{
public:
	//
	// Constructors and destructor.
	CKdvASFFileReader(void);
	~CKdvASFFileReader(void);

	//  ��ASF�ļ��ĳ�ʼ������������ж��Ƿ�ΪASF�ļ�������ȡASF�ļ���ͷ��Ϣ
	u16	Open(IN const char * pFileName, IN ASFFrameProcCallBack inCallback = NULL , IN u32 dwContext = NULL);

	//  ���ô���֡���ݵĻص�����
	u16	SetCallback(IN u32 dwUser, IN ASFFrameProcCallBack inCallback);

	//  ��ȡASF�ļ�����ͷ����ĸ���
	u16	GetHeaderObjectTotal(OUT u32 * dwHeadObjectCount);
	
	//  ��ȡASF�ļ���������Ϣ
	u16	GetASFFileProPerty(OUT TASFFileProperty * pFileProperty);

	//05.7.26�õ���Ӧ�ֶεĳ���
	u16	GetContentDescriptionPropertyFieldLength(OUT u16 *poTitleLength,OUT u16 *poAuthorLength, OUT u16 *poCopyrightLength,OUT u16 *poDescriptionLength);
	
	//  ��ȡASF�ļ������ݰ�Ȩ��Ϣ,���������úó��ȣ�������ڴ�
	u16	GetContentDescriptionProperty(IN OUT TContentDescriptionProperty * pioContentDescriptionProperty);

	//  ��ȡASF�ļ��������ĸ���
	u16	GetStreamTotal(OUT u16 *wStreamCount);
	
	//�õ���Ӧ�ֶεĳ���
	u16 GetStreamPropertyRelativeFieldLenth(IN u8 byinStreamIndex, OUT u16 *poStreamType, OUT u32 *poErrorCorrectDataLength, OUT u16 *poAudVidOthCodecSpecificLength);

	//  ����������ȡASF�ļ���ÿ��������Ϣ,���������úó��ȣ�������ڴ�
	u16	GetStreamPropertyByIndex(IN u8 byStreamIndex,IN OUT TStreamProperty * pioStreamProperty);
	
	//  ��ȡASF�ļ��ľ�������
	u16	GetErrorCorrectionType(OUT u16 *pErrorType);
	//  ��ȡASF�ļ��ľ������ݳ���
	u16	GetErrorCorrectionDataLength(OUT u32 *pErrCorrDataLength);
	//  ��ȡASF�ļ��ľ�������
	u16	GetErrorCorrectionData(OUT u8 *pErrCorrData, IN u32 dwDataLength);	
	
	//  �����Ƿ񲥷���Ƶ��
	u16	SetPlayAudioStream(IN u8 byIndex, IN BOOL32 isPlayStream = TRUE);
//	u16	SetPlayAudioStream(IN BOOL32 isPlay = true );
	//  �����Ƿ񲥷���Ƶ����������������Ҫ����һ���������ô���ϵͳ�в���ǿ�Ʋ���һ������
	u16	SetPlayVideoStream(IN u8 byIndex, IN BOOL32 isPlayStream = TRUE);
//	u16	SetPlayVideoStream(IN BOOL32 isPlayFirstStream = true, IN BOOL32 isPlaySecondStream = true );//05.7.26

	//���ÿ�����źͱ���
    u16 SetPlayRate(IN u16 wPlayMode, IN u32 wPlayRate);

	//���ݱ������ID���ó���Ӧ��ý������
	u16	CodecFormatId2MediaType(IN u8 byiStreamType,IN u32 dwiCodecFormatID,OUT UnionMediaDetailTypeInfo& uoMediaDetailTypeInfo);

	//  �����������ʼʱ�䣬�첽��ȡASF�ļ���֡����
	//bIsAutoCallBack���Ƿ��Զ��ص����Զ��ص��͵�֡�ص����л�
	//�������Զ��ص����ǵ�֡�ص������������ûص�������������ô˺�����
	u16	Start(IN u32 dwStartTime = 0, BOOL32 bIsAutoCallBack = true);
	
	//��֡��ȡ������û����һ��
	u16	GetNextFrame( u32& dwStatus, TStreamDataPayload **ppoFrameData);

	//  ��ͣ�첽��ȡASF�ļ���֡����
	u16	Pause(void);
	//  ����ͣ��λ�������첽��ȡASF�ļ���֡����,���ɵ�֡�ص�ģʽ���ص��Զ��ص�ģʽ
	u16	Resume(void);
	//  ֹͣ�첽��ȡASF�ļ���֡����
	u16	Stop(void);
	//  �ر�ASF�ļ���ȡ�����ͷ���Դ
	u16	Close(void);	


	//  �����Ƿ���Ҫ����Ļ���������Ϣ
	u16		SetDebugInfo(IN u16 wObjectID);
	//  �������ASF�ļ������ݶ�����������Ϣ��Table Of Content��
	u16		DumpObjectTOC(void);
	//  ���ݺ����ķ���ֵ��ȡ��ϸ�Ĵ�����Ϣ
	char    *GetErrorInfo(IN u16 wErrorIndex);
	//  ר������ʾ���������ݡ���ÿ���ֽڵ�ֵ������ʮ�����Ƶ�������ʾ����
	void	ShowDataWithHex(IN u8 * pData, IN u32 dwDataLength);	
	
public:

private:
	CKdvASFFile*	m_pASFFile;				//  ASF�ļ��������ָ��

	u16				m_wObjectIDForDebug;		//	��ʾҪ���Ե�Ŀ�����ID
	
};


/***************************************************************
****************************************************************

ȫ�ֺ�������

****************************************************************
****************************************************************/

#ifndef API
#define API extern "C"
#endif


/*==============================================================
 AsfStartUp():	��ʱ���̴߳�������,��AsfCleanUp�����ԳƵ��ã��ڵ��ö��ӿ�֮ǰ����
				���ֻ�õ�д�ӿڣ��������������Բ����á��ڵ��ö��ӿ�֮ǰ��Ҫ����AsfStartUp(),
				����AsfStartUp����֮�����new���asfreader�����ʵ����	
				�������涨ʱ���Ĺ�ϵ,Ŀǰ��һ�������������֧��new 32��asfreader����,
				asfwriter�������ơ�	Delete���� asfreader֮�����AsfCleanUp()��
 ===============================================================*/
void AsfStartUp();

/*===============================================================
AsfCleanUp(): Asflib�Ķ�ʱ���߳��˳�����,��AsfStartUp�����ԳƵ���
================================================================*/
void AsfCleanUp();

/*================================================================
AsfWriteCleanUp:��ֻ�õ�asfwriter�������,���û�е���asfstartup��asfcleanup,
�����˳�ʱҪ������������ͷ��ڴ�,�������ڴ�й©.
���������asfstartup��asfcleanup,���õ����������
=================================================================*/
void AsfWriteCleanUp();

/*================================================================
 asflibversion(): asflib�汾��Ϣ
=================================================================*/
API void asflibversion();

/*================================================================
 asflibhelp(): asflib��������
=================================================================*/
API void asflibhelp();

/*================================================================
 asffileinfo()���ӿڴ򿪵��ļ������ź��ļ�����Ϣ
=================================================================*/
API void asffileinfo();

/*================================================================
 sfdebuginfo()��asflibʵʱ��Ϣ��ӡ
=================================================================*/
API void asfdebuginfo(s32 nIndex, s32 nLevel);

#if __Win32__ || WIN32
#pragma pack(pop)
#endif	//WIN32

#endif  //__ASF_LIB__
