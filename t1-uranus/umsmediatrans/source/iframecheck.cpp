#include "tpsys.h"
#include "dataswitch.h"
#include "iframecheck.h"
#include "mpdata.h"
#include "umsobject.h"
#include "innereventumsmediatrans.h"
#include "umsxmltype.h"

static BOOL32		g_bShowRcvFlag = FALSE;
static BOOL32		g_bShowSndFlag = FALSE;
static BOOL32		g_bShowSendFiltle = FALSE;
static BOOL32		g_bShowSendInfo = FALSE;

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

API void showrcvpack(BOOL32 bShow)
{
	g_bShowRcvFlag = bShow;

	msgprint("g_bShowRcvFlag = :%d\n", g_bShowRcvFlag);
}


API void showsndpack(BOOL32 bShow)
{
	g_bShowSndFlag = bShow;
	
	msgprint("g_bShowSndFlag = :%d\n", g_bShowSndFlag);
}


API void showsndinfo(BOOL32 bShow)
{
	g_bShowSendInfo = bShow;
	msgprint("g_bShowSendInfo = :%d\n", g_bShowSendInfo);
}
API void showsenddst(BOOL32 bShow)
{
	g_bShowSendFiltle = bShow;
}


#define MAXnum_ref_frames_in_pic_order_cnt_cycle  255
#define MAXIMUMVALUEOFcpb_cnt                     32
#define MAXnum_slice_groups_minus1                8
#define MPEG4_FRAMEMODE_POS                       2

#define RTP_FIXEDHEADER_SIZE            (s32)12

//�ؼ�֡��ȡ ϵ�к궨��
#define     EX_HEADER_SIZE              4
#define     MIN_PACK_EX_LEN             4

typedef enum 
{
    P_SLICE = 0,
    B_SLICE,
    I_SLICE,
    SP_SLICE,
    SI_SLICE
} stdh264SliceType;


// RTP ���ṹ����
typedef struct
{
    u8	 m_byMark;			//�Ƿ�֡�߽�1��ʾ���һ��
    u8   m_byExtence;		//�Ƿ�����չ��Ϣ
    u8   m_byPadNum;		//���ܵ�padding����
    u8   m_byPayload;		//�غ�
    u32  m_dwSSRC;			//ͬ��Դ
    u16  m_wSequence;		//���к�
    u32  m_dwTimeStamp;		//ʱ���
    u8  *m_pExData;         //��չ����
    s32  m_nExSize;			//��չ��С��sizeof(u32)�ı�����
    u8  *m_pRealData;		//ý������ 
    s32  m_nRealSize;		//���ݴ�С 
    s32  m_nPreBufSize;		//m_pRealDataǰԤ����Ŀռ�;
}TRtpPack;

//H261ͷ�ṹ��Ϊ�˱�����⣬�ֶ����ͱ�׼һ��
typedef struct
{
    s32 sBit;
    s32 eBit;
    s32 i;
    s32 v;
    s32 gobN;
    s32 mbaP;
    s32 quant;
    s32 hMvd;
    s32 vMvd;
}TH261Header;

//H264ͷ�ṹ
typedef struct
{
    u16		 m_wWidth;			// ����֡�Ŀ��
    u16		 m_wHeight;			// ����֡�ĸ߶�
    BOOL32	 m_bIsKeyFrame;		// ����֡�Ƿ�Ϊ�ؼ�֡�� 1���ǹؼ�֡  0�����ǹؼ�֡
    u32		 m_dwSPSId;			// SPS��ID
    BOOL32	 m_bIsValidSPS;		// H264��SPS�Ƿ���Ч
    BOOL32	 m_bIsValidPPS;		// H264��PPS�Ƿ���Ч
} TKdvH264Header;

//h264 ������Ϣ����
typedef struct
{
    u8 *pu8Start;
    u8 *pu8P;
    u8 *pu8End;
    s32 s32Left;        // i_count number of available bits 
    
} TBitStream; 

typedef struct tagSeqParameterSetRBSP
{
    BOOL32   bIsValid;												// indicates the parameter set is valid
    
    u32	profile_idc;										        // u(8)
    //#ifdef G50_SPS
    BOOL32		constrained_set0_flag;								// u(1)
    BOOL32		constrained_set1_flag;								// u(1)
    BOOL32		constrained_set2_flag;								// u(1)
    //#endif
    //uint_8  reserved_zero_5bits; /*equal to 0*/					// u(5)
    u32			level_idc;											// u(8)
    //#ifndef G50_SPS
    //	BOOL32		more_than_one_slice_group_allowed_flag;			// u(1)
    //	BOOL32		arbitrary_slice_order_allowed_flag;				// u(1)
    //	BOOL32		redundant_slices_allowed_flag;					// u(1)
    //#endif
    u32			seq_parameter_set_id;								// ue(v)
    u32			log2_max_frame_num_minus4;							// ue(v)
    u32			pic_order_cnt_type;									// ue(v)
    // if( pic_order_cnt_type == 0 ) 
    u32			log2_max_pic_order_cnt_lsb_minus4;					// ue(v)
    // else if( pic_order_cnt_type == 1 )
    BOOL32		delta_pic_order_always_zero_flag;					// u(1)
    s32			offset_for_non_ref_pic;								// se(v)
    s32			offset_for_top_to_bottom_field;						// se(v)
    u32			num_ref_frames_in_pic_order_cnt_cycle;				// ue(v)
    // for( i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++ )
    s32			offset_for_ref_frame[MAXnum_ref_frames_in_pic_order_cnt_cycle];   // se(v)
    u32			num_ref_frames;										// ue(v)
    BOOL32		gaps_in_frame_num_value_allowed_flag;				// u(1)
    u32			pic_width_in_mbs_minus1;							// ue(v)
    u32			pic_height_in_map_units_minus1;						// ue(v)
    BOOL32		frame_mbs_only_flag;								// u(1)
    // if( !frame_mbs_only_flag ) 
    BOOL32		mb_adaptive_frame_field_flag;						// u(1)
    BOOL32		direct_8x8_inference_flag;							// u(1)
    //#ifdef G50_SPS
    BOOL32		frame_cropping_flag;								// u(1)
    u32			frame_cropping_rect_left_offset;					// ue(v)
    u32			frame_cropping_rect_right_offset;					// ue(v)
    u32			frame_cropping_rect_top_offset;						// ue(v)
    u32			frame_cropping_rect_bottom_offset;					// ue(v)
    //#endif
    BOOL32		vui_parameters_present_flag;						// u(1)
    //not of syntax
    s32			MaxFrameNum;
} TSeqParameterSetRBSP;


typedef struct  tagPicParameterSetRBSP
{
    BOOL32		bIsValid;											// indicates the parameter set is valid
    u32			pic_parameter_set_id;                               // ue(v)
    u32			seq_parameter_set_id;                               // ue(v)
    BOOL32		entropy_coding_mode_flag;                           // u(1)
    // if( pic_order_cnt_type < 2 )  in the sequence parameter set
    BOOL32      pic_order_present_flag;                             // u(1)
    u32			num_slice_groups_minus1;                            // ue(v)
    u32			slice_group_map_type;								// ue(v)
    // if( slice_group_map_type = = 0 )
    u32			run_length_minus1[MAXnum_slice_groups_minus1];  	// ue(v)
    // else if( slice_group_map_type = = 2 )
    u32			top_left[MAXnum_slice_groups_minus1];				// ue(v)
    u32			bottom_right[MAXnum_slice_groups_minus1];			// ue(v)
    // else if( slice_group_map_type = = 3 || 4 || 5
    BOOL32		slice_group_change_direction_flag;				    // u(1)
    u32			slice_group_change_rate_minus1;					    // ue(v)
    // else if( slice_group_map_type = = 6 )
    u32			num_slice_group_map_units_minus1;					// ue(v)
    u32			*slice_group_id;									// complete MBAmap u(v)
    u32			num_ref_idx_l0_active_minus1;                       // ue(v)
    u32			num_ref_idx_l1_active_minus1;                       // ue(v)
    BOOL32		weighted_pred_flag;                                 // u(1)
    BOOL32		weighted_bipred_idc;                                // u(2)
    s32			pic_init_qp_minus26;                                // se(v)
    s32			pic_init_qs_minus26;                                // se(v)
    s32			chroma_qp_index_offset;                             // se(v)
    BOOL32		deblocking_filter_control_present_flag;             // u(1)
    BOOL32		constrained_intra_pred_flag;                        // u(1)
    BOOL32		redundant_pic_cnt_present_flag;                     // u(1)
    BOOL32		vui_pic_parameters_flag;                            // u(1)
    //#ifndef G50_SPS
    //	BOOL32   frame_cropping_flag;                               // u(1)
    //    u32  frame_cropping_rect_left_offset;					    // ue(v)
    //    u32  frame_cropping_rect_right_offset;					// ue(v)
    //    u32  frame_cropping_rect_top_offset;					    // ue(v)
    //    u32  frame_cropping_rect_bottom_offset;				    // ue(v)
    //#endif
} TPicParameterSetRBSP;

typedef struct
{
    u16		first_mb_in_slice;						//ue(v)  slice�е�һ��MB�ĵ�ַ
    u16		slice_type;								//ue(v)  slice�ı�������
    u16		pic_parameters_set_id;	
} Tstdh264Dec_SliceHeaderData;

class CMpBitStreamFilter
{
public:
    // �ؼ�֡���
    static BOOL32 IsKeyFrame( u8 byPayLoad, u8 *pBuf, s32 nSize );
	
private:    
    // Toolkits and utilities    
    // u32������������ת��
    static void ConvertN2H(u8 *pBuf, s32 nStartIndex, s32 nSize);
    
    // u32��ȡָ��bits range
    static u32  GetBitField(u32 dwValue, s32 nStartBit, s32 nBits);
	
    static BOOL32 IsH261KeyFrame( u8 *pBuf, s32 nSize );
    static BOOL32 IsH263KeyFrame( u8 *pBuf, s32 nSize );
    static BOOL32 IsH264KeyFrame( u8 *pBuf, s32 nSize );
    static BOOL32 IsMpeg4KeyFrame( const TRtpPack *ptRtpPack );   // MPEG4 & H262
    
private:
    static void stdh264_bs_init( TBitStream *s, void *p_data, s32 i_data );
    static s32 stdh264_bs_pos( TBitStream *s );
    static s32 stdh264_bs_eof( TBitStream *s );
    static u32 stdh264_bs_read( TBitStream *s, s32 i_count );
    static u32 stdh264_bs_read1( TBitStream *s );
    static u32 stdh264_bs_show( TBitStream *s, s32 i_count );
    static void stdh264_bs_skip( TBitStream *s, s32 i_count );
    static s32 stdh264_bs_read_ue( TBitStream *s );
    static s32 stdh264_bs_read_se( TBitStream *s );
    static s32 stdh264_bs_read_te( TBitStream *s, s32 x );
	
    static s32 stdh264_FirstPartOfSliceHeader(TBitStream *s, Tstdh264Dec_SliceHeaderData *dec_slice_header);
	
    static BOOL32 DecodeH264SPS( TBitStream *s, TSeqParameterSetRBSP *sps, 
		TKdvH264Header *pStdH264Header );
    
    static BOOL32 DecodeH264PPS( TBitStream *s, TPicParameterSetRBSP *pps, 
		TKdvH264Header *pStdH264Header );
};





void CMpBitStreamFilter::ConvertN2H(u8 *pBuf, s32 nStartIndex, s32 nSize)
{
    for(s32 i=nStartIndex; i<(nStartIndex+nSize); i++) 
    {
        ((u32 *)pBuf)[i] = ntohl(((u32 *)pBuf)[i]);
    }
    return;
}


u32 CMpBitStreamFilter::GetBitField(u32 dwValue, s32 nStartBit, s32 nBits)
{
    s32  nMask = (1 << nBits) - 1;
    
    return (dwValue >> nStartBit) & nMask; 
}

BOOL32 CMpBitStreamFilter::IsKeyFrame( u8 byPayLoad, u8 *pBuf, s32 nSize  )
{
    if (NULL == pBuf || nSize < RTP_FIXEDHEADER_SIZE )
    {
       msgprintnotime("IsKeyFrame data NULL or Size <12------------------------------------------!\n" );
		return FALSE;
    }        
    
    u8 abyTmpBuf[RTP_FIXEDHEADER_SIZE*3] = {0};
    memcpy(abyTmpBuf, pBuf, min(nSize, RTP_FIXEDHEADER_SIZE*3) );
    
    u32* header =(u32*)abyTmpBuf;
    
    TRtpPack tRtpPack;
    memset(&tRtpPack, 0, sizeof(tRtpPack));
    
    //RTP fixed Header Convert
    ConvertN2H(abyTmpBuf, 0, 3);

    //tRtpPack.m_dwTimeStamp = header[1];
    //tRtpPack.m_wSequence   = (u16)GetBitField(header[0], 0, 16);
    //tRtpPack.m_dwSSRC      = header[2];
    //tRtpPack.m_byMark      = (u8)GetBitField(header[0], 23, 1);
    //tRtpPack.m_byPayload   = (u8)GetBitField(header[0], 16, 7);
    tRtpPack.m_byExtence     = (u8)GetBitField(header[0], 28, 1);
    
    //CSRC
    ConvertN2H(abyTmpBuf, 3, GetBitField(header[0], 24, 4));
    s32 nOffSet          = RTP_FIXEDHEADER_SIZE + GetBitField(header[0], 24, 4)*sizeof(u32);    
    tRtpPack.m_nRealSize = nSize - nOffSet;
    tRtpPack.m_pRealData = abyTmpBuf + nOffSet; 

    //��չͷ �� ������ Fixed Header����, Ŀǰ���ڴ����Զ����mp4��mp3��
    if (tRtpPack.m_byExtence)/*Extension Bit Set*/
    {
        if(tRtpPack.m_nRealSize < EX_HEADER_SIZE+MIN_PACK_EX_LEN) 
        {
           msgprintnotime("IsKeyFrame pack data  Size <8------------------------------------------!\n" );
			return -1;
        }
        s32 xStart = nOffSet/s32(sizeof(u32));
        ConvertN2H(abyTmpBuf, xStart, 1);
        tRtpPack.m_nExSize    = (u16)GetBitField(header[xStart], 0, 16);
        tRtpPack.m_pExData    = abyTmpBuf + (xStart+1) * sizeof(u32);
        tRtpPack.m_nRealSize -= ((tRtpPack.m_nExSize + 1)*sizeof(u32));
        tRtpPack.m_pRealData += ((tRtpPack.m_nExSize + 1)*sizeof(u32));
    }

    //Padding Bit Set
    if (GetBitField(header[0], 29, 1))
    {
        // ��㴦��
        // ע����ڼ���������padding���ȵ��ռ� - ���һ���ֽ�
        tRtpPack.m_byPadNum  = 1;
    }

    BOOL32 bIFrame = FALSE;

    switch( byPayLoad ) 
    {            
    case MEDIA_TYPE_H263PLUS:
        // 263+��Ƶ��֧�ּ�⣬ֱ��pass
        bIFrame = TRUE;
        break;
    case MEDIA_TYPE_H261:
        bIFrame = IsH261KeyFrame( tRtpPack.m_pRealData, tRtpPack.m_nRealSize );
        break;
    case MEDIA_TYPE_H263:
        bIFrame = IsH263KeyFrame( pBuf, nSize );
        break;
    case MEDIA_TYPE_H264:
        bIFrame = IsH264KeyFrame( pBuf, nSize );
        break;
    case MEDIA_TYPE_H262:
    case MEDIA_TYPE_MP4:
        bIFrame = IsMpeg4KeyFrame( &tRtpPack );
        break;    
        // ��Ƶ�����
    case MEDIA_TYPE_MP3:
    case MEDIA_TYPE_PCMA:
    case MEDIA_TYPE_PCMU:
    case MEDIA_TYPE_G721:
    case MEDIA_TYPE_G722:
    case MEDIA_TYPE_G7231:
    case MEDIA_TYPE_G728:
    case MEDIA_TYPE_G729:
    case MEDIA_TYPE_G7221C:
	case MEDIA_TYPE_G719:
        bIFrame = FALSE;
        break;
    default:
        bIFrame = TRUE;
        break;
    }
    return bIFrame;
}

BOOL32 CMpBitStreamFilter::IsH261KeyFrame(u8 *pBuf, s32 nSize)
{
    TH261Header tH261Header;
    memset(&tH261Header, 0, sizeof(tH261Header));
    
    u32 dwH261Header = *((u32 *)(pBuf));
    
    //get h261 header
    dwH261Header  = ntohl(dwH261Header);
    //tH261Header.vMvd  = GetBitField(dwH261Header, 0, 5);	
    //tH261Header.hMvd  = GetBitField(dwH261Header, 5, 5);	
    //tH261Header.quant = GetBitField(dwH261Header, 10, 5);	
    //tH261Header.mbaP  = GetBitField(dwH261Header, 15, 5);	
    //tH261Header.gobN  = GetBitField(dwH261Header, 20, 4);	
    //tH261Header.v     = GetBitField(dwH261Header, 24, 1);	
    tH261Header.i	    = GetBitField(dwH261Header, 25, 1);	
    //tH261Header.eBit  = GetBitField(dwH261Header, 26, 3);	
    //tH261Header.sBit  = GetBitField(dwH261Header, 29, 3);
    
    return tH261Header.i;
}

BOOL32 CMpBitStreamFilter::IsH263KeyFrame(u8 *pBuf, s32 nSize)
{
    if (NULL == pBuf || nSize < RTP_FIXEDHEADER_SIZE + 8)
    {
        return -1;
    }        
    
    //����H263ͷƫ��
    s32 nOffSet = RTP_FIXEDHEADER_SIZE;
    
    //����׼������RTPͷ����12�ֽڵ����
    u8 byCC;
    //CSRC��Ŀ
    byCC = *(pBuf);
    byCC &= 0x0f;
    nOffSet += byCC * sizeof(u32);
    
    if (nSize < nOffSet + 4)
    {
        return -1;
    }
    
    //�Ƿ�����չ
    u8 byExtend;
    byExtend = *(pBuf);
    byExtend &= 0x10;
    if (byExtend)
    {
        u16 wExtLen;
        wExtLen = *(pBuf+nOffSet + 2);
        wExtLen += (wExtLen << 8) + *(pBuf+ nOffSet + 3);
        nOffSet += wExtLen * sizeof(u32);
    }
    
    if (nSize < nOffSet + 4)
    {
        return -1;
    }
    
    BOOL32 bKeyFrame = FALSE;
    //��ģʽ
    u8 byMode;
    byMode = *(pBuf+nOffSet);
    byMode &= 0xc0;
    if ((byMode & 0x80) == 0) // A mode
    {
        u8 byInterFrame;
        byInterFrame = *(pBuf+nOffSet + 1);
        byInterFrame &= 0x10;
        if (!byInterFrame)
        {
            bKeyFrame = TRUE;
        }
    }
    else if ((byMode & 0x80) && ((byMode & 0x40) == 0))
    {
        if (nSize < nOffSet + 8)
        {
            return -1;
        }
        
        u8 byInterFrame;
        byInterFrame = *(pBuf+nOffSet + 4);
        byInterFrame &= 0x80;
        if (!byInterFrame)
        {
            bKeyFrame = TRUE;
        }
    }
    
    if (bKeyFrame)
    {
        return 1;
    }
    
    return 0;
}

BOOL32 CMpBitStreamFilter::IsH264KeyFrame(u8 *pBuf, s32 nSize)
{
    u8* pRtpPackBuf = pBuf + RTP_FIXEDHEADER_SIZE;
    s32 nRtpPackBufSize = nSize - RTP_FIXEDHEADER_SIZE;

    TKdvH264Header tH264Header;
    memset(&tH264Header, 0, sizeof(TKdvH264Header));
    
    if (nRtpPackBufSize <= 1 )
    {
        return FALSE;
    }
    
    BOOL32 bRet = TRUE;
    // the format of the NAL unit type octet is reprinted below:
    //  +---------------+
    //	|0|1|2|3|4|5|6|7|
    //	+-+-+-+-+-+-+-+-+
    //	|F|NRI|  Type   |
    //	+---------------+
    u8  byNaluTypeOctet = (u8) (*pRtpPackBuf);
    
    u32 dwNaluType = byNaluTypeOctet & 0x1F;  // ȡ�õ�5λ
    TBitStream tBitStream;
    memset(&tBitStream, 0, sizeof(tBitStream));

    // TBitStream�ṹ��RTP���ĵ�14�ֽڿ�ʼ��ǰ12�ֽ�ΪRTPͷ����13�ֽ�ΪNalu���ͣ�
    stdh264_bs_init(&tBitStream, (pRtpPackBuf+1), (nRtpPackBufSize-1));
    TSeqParameterSetRBSP tSPS;
    TPicParameterSetRBSP tPPS;
    Tstdh264Dec_SliceHeaderData tSlice_header;
    memset(&tSPS, 0, sizeof(tSPS));
    memset(&tPPS, 0, sizeof(tPPS));
    memset(&tSlice_header, 0, sizeof(tSlice_header));
    
    switch(dwNaluType) 
    {
//     case 1:
//     case 5:  // NALU_TYPE_IDR
//     case 28: // FU_A �а����Լ��֧��
//         stdh264_FirstPartOfSliceHeader(&tBitStream, &tSlice_header);
//         if(u16(I_SLICE) == tSlice_header.slice_type)
//         {
//             MdlHint(Ums_Mdl_Media, ("[IsH264KeyFrame]Keyframe:I_SLICE\n"));
//             tH264Header.m_bIsKeyFrame = TRUE;
//         }
//         break;
    case 7:  // NALU_TYPE_SPS
        bRet = DecodeH264SPS(&tBitStream, &tSPS, &tH264Header);
        if ( bRet )
        {
//            MdlHint(Ums_Mdl_Media, ("[IsH264KeyFrame]NALU_TYPE_SPS\n"));
			msgprint("[IsH264KeyFrame]NALU_TYPE_SPS\n");
            tH264Header.m_bIsKeyFrame = TRUE;
        }
        break;
//     case 8:  // NALU_TYPE_PPS
//         bRet = DecodeH264PPS(&tBitStream, &tPPS, &tH264Header);
//         if ( bRet )
//         {
//             MdlHint(Ums_Mdl_Media, ("[IsH264KeyFrame]NALU_TYPE_PPS\n"));
// 
//             tH264Header.m_bIsKeyFrame = TRUE;
//         }
//         break;
    default:
        break;
    }
    
    return tH264Header.m_bIsKeyFrame;
}

BOOL32 CMpBitStreamFilter::IsMpeg4KeyFrame(const TRtpPack *ptRtpPack )
{        
    if ( ptRtpPack->m_nExSize != 0)
    {
        u8* pbyHeader = ptRtpPack->m_pExData;
        return ( 1 == pbyHeader[MPEG4_FRAMEMODE_POS] );
    }

    return FALSE;
}


void CMpBitStreamFilter::stdh264_bs_init( TBitStream *s, void *p_data, s32 i_data )
{
    s->pu8Start = (u8*) p_data;
    s->pu8P     = (u8*) p_data;
    s->pu8End   = (u8*) s->pu8P + i_data;
    s->s32Left  = 8;
}

s32 CMpBitStreamFilter::stdh264_bs_pos( TBitStream *s )
{
    return( 8 * ( s->pu8P - s->pu8Start ) + 8 - s->s32Left );
}

s32 CMpBitStreamFilter::stdh264_bs_eof( TBitStream *s )
{
    return( s->pu8P >= s->pu8End ? 1: 0 );
}

u32 CMpBitStreamFilter::stdh264_bs_read( TBitStream *s, s32 i_count )
{
	static u32 dwstdh264MaskArr[33] = 
	{ 
		0x00,
        0x01,      0x03,      0x07,      0x0f,
        0x1f,      0x3f,      0x7f,      0xff,
        0x1ff,     0x3ff,     0x7ff,     0xfff,
        0x1fff,    0x3fff,    0x7fff,    0xffff,
        0x1ffff,   0x3ffff,   0x7ffff,   0xfffff,
        0x1fffff,  0x3fffff,  0x7fffff,  0xffffff,
        0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff,
        0x1fffffff,0x3fffffff,0x7fffffff,0xffffffff };
		
    s32 i_shr;
    u32 i_result = 0;

    while( i_count > 0 )
    {
        if( s->pu8P >= s->pu8End )
        {
            break;
        }

        if( ( i_shr = s->s32Left - i_count ) >= 0 )
        {
            /* more in the buffer than requested */
            i_result |= ( *s->pu8P >> i_shr )&dwstdh264MaskArr[i_count];
            s->s32Left -= i_count;
            if( s->s32Left == 0 )
            {
                s->pu8P++;
                s->s32Left = 8;
            }
            return( i_result );
        }
        else
        {
            /* less in the buffer than requested */
			//i_result |= ((*s->pu8P & dwstdh264MaskArr[s->s32Left]) << -i_shr);
           i_result |= ((*s->pu8P & dwstdh264MaskArr[s->s32Left]) << abs(i_shr));
           i_count  -= s->s32Left;
           s->pu8P++;
           s->s32Left = 8;
        }
    }

    return( i_result );
}

u32 CMpBitStreamFilter::stdh264_bs_read1( TBitStream *s )
{

    if( s->pu8P < s->pu8End )
    {
        u32 i_result;

        s->s32Left--;
        i_result = ( *s->pu8P >> s->s32Left )&0x01;
        if( s->s32Left == 0 )
        {
            s->pu8P++;
            s->s32Left = 8;
        }
        return i_result;
    }

    return 0;
}

u32 CMpBitStreamFilter::stdh264_bs_show( TBitStream *s, s32 i_count )
{
    if( s->pu8P < s->pu8End && i_count > 0 )
    {
        u32 i_cache = ((s->pu8P[0] << 24)+(s->pu8P[1] << 16)+(s->pu8P[2] << 8)+s->pu8P[3]) << (8-s->s32Left);
        return( i_cache >> ( 32 - i_count) );
    }
    return 0;
}


void CMpBitStreamFilter::stdh264_bs_skip( TBitStream *s, s32 i_count )
{
    s->s32Left -= i_count;

    while( s->s32Left <= 0 )
    {
        s->pu8P++;
        s->s32Left += 8;
    }
}

s32 CMpBitStreamFilter::stdh264_bs_read_ue( TBitStream *s )
{
    s32 i = 0;
    
    while( stdh264_bs_read1( s ) == 0 && s->pu8P < s->pu8End && i < 32 )
    {
        i++;
    }
    return( ( 1 << i) - 1 + stdh264_bs_read( s, i ) );
}

s32 CMpBitStreamFilter::stdh264_bs_read_se( TBitStream *s )
{
    s32 val = stdh264_bs_read_ue( s );
    
    return val&0x01 ? (val+1)/2 : -(val/2);
}

s32 CMpBitStreamFilter::stdh264_bs_read_te( TBitStream *s, s32 x )
{
    if( x == 1 )
    {
        return 1 - stdh264_bs_read1( s );
    }
    else if( x > 1 )
    {
        return stdh264_bs_read_ue( s );
    }
    return 0;
}

s32 CMpBitStreamFilter::stdh264_FirstPartOfSliceHeader(TBitStream *s, Tstdh264Dec_SliceHeaderData *dec_slice_header)
{
    s32 tmp;
    dec_slice_header->first_mb_in_slice = stdh264_bs_read_ue( s );
    tmp = stdh264_bs_read_ue( s );
    if (tmp>4) 
    {
        tmp -=5;
    }
    dec_slice_header->slice_type = (u16) tmp;
    
    return 0;
}


BOOL32 CMpBitStreamFilter::DecodeH264SPS( TBitStream *s, TSeqParameterSetRBSP *sps, 
                                          TKdvH264Header *pStdH264Header )
{
    u32 i;
    
    sps->profile_idc               = stdh264_bs_read( s, 8 );
    
    sps->constrained_set0_flag     = stdh264_bs_read( s, 1 );
    sps->constrained_set1_flag     = stdh264_bs_read( s, 1 );
    sps->constrained_set2_flag     = stdh264_bs_read( s, 1 );
    stdh264_bs_skip( s, 5 );        //reserved_zero
    
    sps->level_idc                 = stdh264_bs_read( s, 8 );
    
    sps->seq_parameter_set_id      = stdh264_bs_read_ue( s );
    sps->log2_max_frame_num_minus4 = stdh264_bs_read_ue( s );
    sps->pic_order_cnt_type        = stdh264_bs_read_ue( s );
    
    if (sps->pic_order_cnt_type == 0)
    {
        sps->log2_max_pic_order_cnt_lsb_minus4 = stdh264_bs_read_ue( s );
    }
    else if (sps->pic_order_cnt_type == 1)
    {
        sps->delta_pic_order_always_zero_flag      = stdh264_bs_read( s, 1 );
        sps->offset_for_non_ref_pic                = stdh264_bs_read_se( s );
        sps->offset_for_top_to_bottom_field        = stdh264_bs_read_se( s );
        sps->num_ref_frames_in_pic_order_cnt_cycle = stdh264_bs_read_ue( s );
        if (sps->num_ref_frames_in_pic_order_cnt_cycle > MAXnum_ref_frames_in_pic_order_cnt_cycle)
        {
            return FALSE;
        }
        for(i=0; i<sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
        {
            sps->offset_for_ref_frame[i]           = stdh264_bs_read_se( s );
        }
    }
    
    sps->num_ref_frames                        = stdh264_bs_read_ue( s );
    sps->gaps_in_frame_num_value_allowed_flag  = stdh264_bs_read( s, 1 );
    sps->pic_width_in_mbs_minus1               = stdh264_bs_read_ue( s );  //  Width
    sps->pic_height_in_map_units_minus1        = stdh264_bs_read_ue( s );  //  Height
    sps->frame_mbs_only_flag                   = stdh264_bs_read( s, 1 );
    if (!sps->frame_mbs_only_flag)
    {
        sps->mb_adaptive_frame_field_flag      = stdh264_bs_read( s, 1 );
    }
    sps->direct_8x8_inference_flag             = stdh264_bs_read( s, 1 );
    sps->frame_cropping_flag                   = stdh264_bs_read( s, 1 );
    
    if (sps->frame_cropping_flag)
    {
        sps->frame_cropping_rect_left_offset   = stdh264_bs_read_ue( s );
        sps->frame_cropping_rect_right_offset  = stdh264_bs_read_ue( s );
        sps->frame_cropping_rect_top_offset    = stdh264_bs_read_ue( s );
        sps->frame_cropping_rect_bottom_offset = stdh264_bs_read_ue( s );
    }
    
    sps->vui_parameters_present_flag           = stdh264_bs_read( s, 1 );
    if (sps->vui_parameters_present_flag)
    {
        //OspPintf( 1, 0, "VUI sequence parameters present but not supported, ignored, proceeding to next NALU\n");
    }
    
    sps->bIsValid = TRUE;
    
    pStdH264Header->m_bIsValidSPS = TRUE;
    pStdH264Header->m_dwSPSId     = sps->seq_parameter_set_id;
    pStdH264Header->m_wWidth      = (u16)(sps->pic_width_in_mbs_minus1 + 1) * 16;
    pStdH264Header->m_wHeight     = (u16)(sps->pic_height_in_map_units_minus1 + 1) * 16;
    
    return TRUE;
}

BOOL32 CMpBitStreamFilter::DecodeH264PPS( TBitStream *s, TPicParameterSetRBSP *pps, 
							              TKdvH264Header *pStdH264Header )
{
	u32 i;
	s32 NumberBitsPerSliceGroupId;
	
	pps->pic_parameter_set_id     = stdh264_bs_read_ue( s );
	pps->seq_parameter_set_id     = stdh264_bs_read_ue( s );
	pps->entropy_coding_mode_flag = stdh264_bs_read( s, 1 );
	pps->pic_order_present_flag   = stdh264_bs_read( s, 1 );
	pps->num_slice_groups_minus1  = stdh264_bs_read_ue( s );
	
	// FMO stuff begins here
    //hual modi 2005-06-24
    if (pps->num_slice_groups_minus1 > MAXnum_slice_groups_minus1)
    {
        return FALSE;
    }

    if (pps->num_slice_groups_minus1 > 0)
	{
		pps->slice_group_map_type = stdh264_bs_read_ue( s );

		switch( pps->slice_group_map_type )
		{
			case 0:
			{
				for (i=0; i<=pps->num_slice_groups_minus1; i++)
				{
					pps->run_length_minus1[i] = stdh264_bs_read_ue( s );
				}
				break;
			}
			case 2:
			{
				for (i=0; i<pps->num_slice_groups_minus1; i++)
				{
					//! JVT-F078: avoid reference of SPS by using ue(v) instead of u(v)
					pps->top_left [i]                  = stdh264_bs_read_ue( s );
					pps->bottom_right [i]              = stdh264_bs_read_ue( s );
				}
				break;
			}
			case 3:
			case 4:
			case 5:
			{
				pps->slice_group_change_direction_flag = stdh264_bs_read( s, 1 );
				pps->slice_group_change_rate_minus1    = stdh264_bs_read_ue( s );
				break;
			}
			case 6:
			{
				if (pps->num_slice_groups_minus1+1 >4)
				{
					NumberBitsPerSliceGroupId = 3;
				}
				else if (pps->num_slice_groups_minus1+1 > 2)
				{
					NumberBitsPerSliceGroupId = 2;
				}
				else
				{
					NumberBitsPerSliceGroupId = 1;
				}
				
				//! JVT-F078, exlicitly signal number of MBs in the map
				pps->num_slice_group_map_units_minus1      = stdh264_bs_read_ue( s );
                
                //hual add 2005-06-24
                if (NULL == pps->slice_group_id)
                {
                    break;
                }

				for (i=0; i<=pps->num_slice_group_map_units_minus1; i++)
				{
					pps->slice_group_id[i] = stdh264_bs_read(s,NumberBitsPerSliceGroupId );//maywrong
				}
				break;
			}
			default:
				break;
		}
	}
	
	// End of FMO stuff
	
	pps->num_ref_idx_l0_active_minus1           = stdh264_bs_read_ue( s );
	pps->num_ref_idx_l1_active_minus1           = stdh264_bs_read_ue( s );
	pps->weighted_pred_flag                     = stdh264_bs_read( s, 1 );
	pps->weighted_bipred_idc                    = stdh264_bs_read( s, 2 );
	pps->pic_init_qp_minus26                    = stdh264_bs_read_se( s );
	pps->pic_init_qs_minus26                    = stdh264_bs_read_se( s );
	pps->chroma_qp_index_offset                 = stdh264_bs_read_se( s );
	pps->deblocking_filter_control_present_flag = stdh264_bs_read( s, 1 );
	pps->constrained_intra_pred_flag            = stdh264_bs_read( s, 1 );
	pps->redundant_pic_cnt_present_flag         = stdh264_bs_read( s, 1 );
	
	pps->bIsValid = TRUE;
	pStdH264Header->m_bIsValidPPS = TRUE;

	return TRUE;
}

u32 RcvFilterCallBackFun(u32 dwRecvIP, u16 wRecvPort, u32 dwSrcIP, u16 wSrcPort, u8* pData, u32 uLen)
{
#define CHECK_OK 0
#define CHECK_ERROR 1

	//������ת��
	u16 wRecvPortLocal  = ntohs(wRecvPort);
	u16 wSrcPortLocal  = ntohs(wSrcPort);

    if (uLen <= 12)    // С�ڵ���rtpͷ(12Byte)��Ϊת�����԰�
    {
        MdlLowHint(enLogLowest, ("ERROR, [RcvFilterCallBackFun] Pack for port.%d is ignored due to UdpLen.%d\n", wRecvPortLocal, uLen));
        return CHECK_ERROR;
    }
	

    u8 byPayloadType  = ntohs(*(u16 *)pData) & 0x007F;
    u16 wNewSeqNum     = ntohs(*(u16 *)(pData + 2));
    u32 dwNewTimeStamp = ntohl(*(u32 *)(pData + 4));
    u32 dwNewSSRC      = ntohl(*(u32 *)(pData + 8));
	
	if (g_bShowRcvFlag)
	{
		msgprint("[RcvFilter]port:%d, Payload.%d SeqNum.%d, TS.%d��SSRC.%d !\n"
			, wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
	}
    
	TCheckIFrame* ptFrame = CMpData::m_tRcvCheck.FindByPort(wRecvPortLocal);
	if (NULL == ptFrame || ptFrame->m_tUnit.GetHead() == NULL)
	{
		msgprintnotime("Frame is NULL-------------------------------------------!\n" );
		return CHECK_OK;
	}
	
	CUnitListPtr Itor = ptFrame->m_tUnit.GetHead();

	if (TP_IFrameCheck_Poll == Itor->m_tData.m_emType)
	{//�������˿�ת��Ŀ�꣬�¶˿��������ؼ�֡���϶˿ڱ����ȴ�
	 //�¶˿ڵ�m_dwValue2�洢�϶˿�
		if (Itor->m_tData.m_tTwoRcv.m_wNewPort == wRecvPortLocal)	
		{
			if (!Itor->m_tData.m_tTwoRcv.m_bTrans)
			{
				if (CMpBitStreamFilter::IsKeyFrame( byPayloadType, pData, uLen ))
				{
					msgprint("[RcvFilter port]IsKey. port:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
						, wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
					
					ENTER_UPDATESEM;
				
					Itor->m_tData.m_tTwoRcv.m_bTrans = TRUE;	//��⵽�ؼ�֡
					
					TCheckIFrame* ptOldIFrame = CMpData::m_tRcvCheck.FindByPort(Itor->m_tData.m_tTwoRcv.m_wOldPort);
					if (NULL != ptOldIFrame && ptOldIFrame->m_tUnit.GetHead() > 0)
					{
						ptOldIFrame->m_tUnit.GetHead()->m_tData.m_tTwoRcv.m_bTrans = FALSE;	
					}
					
					EXIT_UPDATESEM;
					
					CTpMsg tMsg;
					tMsg.SetEvent(ev_IframeRcvCheck_Res);
					tMsg.SetBody(&wRecvPortLocal, sizeof(wRecvPortLocal));
					tMsg.Post(UMS_MEDIATRANS_APP_INST);
				}
				
				if (Itor->m_tData.m_tTwoRcv.m_bTrans)
				{
					return CHECK_OK;
				}
			}
			else
			{
				return CHECK_OK;
			}			
		}
		else
		{//�϶˿ڣ������ȴ�
			if (Itor->m_tData.m_tTwoRcv.m_bTrans)
			{
				return CHECK_OK;
			}
			return CHECK_ERROR;
		}
	}
	else
	{//����Դ���

		if (Itor->m_tData.m_tBySrc.m_dwOldIP == dwSrcIP && Itor->m_tData.m_tBySrc.m_wOldPort == wSrcPortLocal && !Itor->m_tData.m_tBySrc.m_bUsedNew)
		{
			return CHECK_OK;
		}
		
		if (Itor->m_tData.m_tBySrc.m_dwNewIP == dwSrcIP && Itor->m_tData.m_tBySrc.m_wNewPort == wSrcPortLocal)
		{
			if (Itor->m_tData.m_tBySrc.m_bUsedNew)
			{
				return CHECK_OK;
			}

			if (CMpBitStreamFilter::IsKeyFrame( byPayloadType, pData, uLen ))
			{
				msgprint("[RcvFilter Src]IsKey. port:%d, Payload.%d, SeqNum.%d, TS.0x%x��SSRC.0x%x !\n"
					, wRecvPort, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
				
				ENTER_UPDATESEM;
				Itor->m_tData.m_tBySrc.m_bUsedNew = TRUE;
				EXIT_UPDATESEM;
				
				CTpMsg tMsg;
				tMsg.SetEvent(ev_IframeRcvCheck_Res);
				tMsg.SetBody(&wRecvPortLocal, sizeof(wRecvPortLocal));
				tMsg.Post(UMS_MEDIATRANS_APP_INST);
				
				return CHECK_OK;
			}
			if (g_bShowRcvFlag)
			{
				msgprint("[RcvFilter Src]key is not ok, new is unuseful. port:%d, Payload.%d, SeqNum.%d, TS.0x%x��SSRC.0x%x !\n"
					, wRecvPort, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
			}
			
			return CHECK_ERROR;
		}
		if (g_bShowRcvFlag)
		{
			msgprint("[RcvFilter Src]key is ok, old is unuseful. port:%d, Payload.%d, SeqNum.%d, TS.0x%x��SSRC.0x%x !\n"
				, wRecvPort, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
		}
	}
	return CHECK_ERROR;
}

CUnitListPtr FindByDstPort(TCheckIFrame* ptSndIFrame, u16 wPort)
{
	for (CUnitListPtr Itor = ptSndIFrame->m_tUnit.GetHead(); Itor != NULL; Itor = Itor->m_ptNext)
	{
		if ( Itor->m_tData.m_tSndDis.m_wDstPort == wPort )
		{
			return Itor;
		}
	}
	return NULL;
}


void SndFilterCallBackFun(u32 dwRecvIP, u16 wRecvPort, u32 dwSrcIP,  u16 wSrcPort,
						  TNetSndMember *ptSends,            // ת��Ŀ���б�
						  u16* pwSendNum,                    // ת��Ŀ����� 
						  u8* pUdpData, u32* pdwUdpLen)
{
	u32 dwUdpLen = *pdwUdpLen;
	//������ת��
	u16 wRecvPortLocal  = ntohs(wRecvPort);
	u16 wSrcPortLocal  = ntohs(wSrcPort);

	if (dwUdpLen <= 12)    // С�ڵ���rtpͷ(12Byte)��Ϊת�����԰�
    {
		*pwSendNum = 0;
        MdlLowHint(enLogLowest, ("ERROR, [SndFilterCallBackFun] Pack for port.%d is ignored due to UdpLen.%d\n", wRecvPortLocal, dwUdpLen));
        return;
    }
	u16 wPreSendNum = *pwSendNum;
	
    u8 byPayloadType  = ntohs(*(u16 *)pUdpData) & 0x007F;
    u16 wNewSeqNum     = ntohs(*(u16 *)(pUdpData + 2));
    u32 dwNewTimeStamp = ntohl(*(u32 *)(pUdpData + 4));
    u32 dwNewSSRC      = ntohl(*(u32 *)(pUdpData + 8));
	
	if (g_bShowSndFlag)
	{
		msgprintnotime("[SndFilter]port:%d, Payload.%d SeqNum.%d, TS.%d��SSRC.%d !\n"
			, wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
	}
    
	TCheckIFrame* ptSndIFrame = CMpData::m_tSndCheck.FindByPort(wRecvPortLocal);
	if (NULL == ptSndIFrame || ptSndIFrame->m_tUnit.GetHead() == NULL )
	{
		return;
	}
	
	u16 wDelNum = 0;
	u16 bDstPort = 0;
	do 
	{
		for (CUnitListPtr Itor = ptSndIFrame->m_tUnit.GetHead(); Itor != NULL; Itor = Itor->m_ptNext)
		{
			//m_bIFrameCheck ΪFALSE�򲻷���  ΪTRUE����
			if (TP_IFrameCheck_Dis == Itor->m_tData.m_emType )
			{//B4����ƽ��
				if (g_bShowSendInfo)
				{
					msgprint("[SndFilter] TP_IFrameCheck_Dis . Type:%d->%s, RcvPort:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
						,TpEnumIdString(EmTpIFrameCheckType, Itor->m_tData.m_emType) , wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
				}

				if ( Itor->m_tData.m_tSndDis.m_bCheck )
				{//������  �������ؼ�֡.

					if ( !ptSndIFrame->m_bCheck )
					{//���һ��
						continue;
					}
					
					if ( Itor->m_tData.m_bIFrameCheck )
					{//����
						continue;
					}
					
					if (CMpBitStreamFilter::IsKeyFrame( byPayloadType, pUdpData, dwUdpLen ))
					{//Ϊ�ؼ�֡ �򽫶�Ӧ���ϵķ��ͼ��Ķ�ӦĿ�Ķ˿� ����Ϊ������
						TCheckIFrame* ptOldIFrame = CMpData::m_tSndCheck.FindByPort(Itor->m_tData.m_tSndDis.m_wOldPort);
						if (NULL == ptOldIFrame || ptOldIFrame->m_tUnit.GetHead() == NULL )
						{
							msgprint("[SndFilter] TP_IFrameCheck_Dis Old Invalid! RcvPort:%d, OldRcvPort:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
								, wRecvPortLocal, Itor->m_tData.m_tSndDis.m_wOldPort, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
							continue;
						}
						CUnitListPtr ItorOld = FindByDstPort(ptOldIFrame, Itor->m_tData.m_tSndDis.m_wDstPort);

						//�µ��йؼ�֡ ���µ��Ժ󶼷��� 
						//�ϵ��Ժ󶼲�����
						ENTER_UPDATESEM;
						ItorOld->m_tData.m_bIFrameCheck = FALSE;
						Itor->m_tData.m_bIFrameCheck = TRUE;
						ptSndIFrame->m_bCheck = FALSE;
						EXIT_UPDATESEM;

						//����
						bDstPort = Itor->m_tData.m_tSndDis.m_wDstPort;

						msgprint("[SndFilter] TP_IFrameCheck_Dis Iframe Check. RcvPort:%d, OldRcvPort:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
							, wRecvPortLocal, Itor->m_tData.m_tSndDis.m_wOldPort, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );

						continue;
					}
					else
					{
						//������
					}
				}
				else
				{//�����ȴ� ��Ϊ�ϵ�
					if ( Itor->m_tData.m_bIFrameCheck )
					{//����
						continue;
					}
					else
					{
						//������
					}
				}

				u16 wSendNum = *pwSendNum;
				for(u16 wSendIndex = 0; wSendIndex < wSendNum; wSendIndex++)
				{
					if (ptSends[wSendIndex].dwIP != Itor->m_tData.m_tSndDis.m_dwDstIp
						|| ptSends[wSendIndex].wPort != Itor->m_tData.m_tSndDis.m_wDstPort)
					{
						continue;
					}
					
					//m_dwDstIp:m_wDstPort �ӷ����б���ɾ��
					
					//�������һ���������һ����ֵ����ǰĿ��
					if (wSendIndex != wSendNum - 1)
					{
						ptSends[wSendIndex] = ptSends[wSendNum - 1];
					}
					
					wSendNum--;
					
					break;//��⵽Ŀ�꣬��ֱ���˳�ѭ��
				}
				
				*pwSendNum = wSendNum;
			}
			else
			{
				if (!Itor->m_tData.m_bIFrameCheck)
				{
					if (g_bShowSendInfo)
					{
						msgprint("[SndFilter]UnNeed Check. Type:%d->%s, RcvPort:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
							,TpEnumIdString(EmTpIFrameCheckType, Itor->m_tData.m_emType) , wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
					}
					continue;
				}

				//���ⷢ���˼��˿�   m_bIFrameCheck �˴����ж� wRecvPortLocal
				TCheckIFrame* ptRcvIFrame = CMpData::m_tRcvCheck.FindByPort(Itor->m_tData.m_tSndBySrc.m_wRcvPort);
				if (NULL == ptRcvIFrame || ptRcvIFrame->m_tUnit.GetHead() == NULL /*|| !ptRcvIFrame->m_tUnit.GetHead()->m_tData.m_bIFrameCheck*/)
				{
					if (g_bShowSendInfo)
					{
						msgprint("[SndFilter]Dst UnCheck. Port:%d, Payload.%d, SeqNum.%d, ptRcvIFrame:%d, TS.%d, SSRC.%d !\n"
							, wRecvPortLocal, byPayloadType, wNewSeqNum, ptRcvIFrame, dwNewTimeStamp, dwNewSSRC );
					}
					
					ENTER_UPDATESEM;
					Itor->m_tData.m_bIFrameCheck = FALSE;
					EXIT_UPDATESEM;
					
					wDelNum++;
					continue;
				}
				
				CUnitListPtr ItorRcv = ptRcvIFrame->m_tUnit.GetHead();
				
				if (Itor->m_tData.m_tSndBySrc.m_dwCheckIp == ItorRcv->m_tData.m_tBySrc.m_dwNewIP
					&& Itor->m_tData.m_tSndBySrc.m_wCheckPort == ItorRcv->m_tData.m_tBySrc.m_wNewPort && ItorRcv->m_tData.m_tBySrc.m_bUsedNew)
				{
					if (g_bShowSendInfo)
					{
						msgprint("[SndFilter]Iframe Check. port:%d, Payload.%d, SeqNum.%d, TS.%d��SSRC.%d !\n"
							, wRecvPortLocal, byPayloadType, wNewSeqNum, dwNewTimeStamp, dwNewSSRC );
					}
					
					ENTER_UPDATESEM;
					Itor->m_tData.m_bIFrameCheck = FALSE;
					EXIT_UPDATESEM;
					
					wDelNum++;
					continue;
				}

				u16 wSendNum = *pwSendNum;
				for(u16 wSendIndex = 0; wSendIndex < wSendNum; wSendIndex++)
				{
					if (ptSends[wSendIndex].dwIP != Itor->m_tData.m_tSndBySrc.m_dwDstIp
						|| ptSends[wSendIndex].wPort != Itor->m_tData.m_tSndBySrc.m_wDstPort)
					{
						continue;
					}
					
					//m_dwDstIp:m_wDstPort �ӷ����б���ɾ��
					
					//�������һ���������һ����ֵ����ǰĿ��
					if (wSendIndex != wSendNum - 1)
					{
						ptSends[wSendIndex] = ptSends[wSendNum - 1];
					}
					
					wSendNum--;
					
					break;//��⵽Ŀ�꣬��ֱ���˳�ѭ��
				}
				
				*pwSendNum = wSendNum;
			}	

		}//for

	} while (0);


	if (g_bShowSendFiltle)
	{
		u16 wSendNum = *pwSendNum;
		OspPrintf(TRUE, FALSE, "[SndFilter]RcvPort:%d, SN:%d, PreNum:%d, dstNum:%d, ", wRecvPortLocal, wNewSeqNum, wPreSendNum, wSendNum);
		
		
		for(u16 wSendIndex = 0; wSendIndex < wSendNum; wSendIndex++)
		{
			OspPrintf(TRUE, FALSE, "%d:("ADDRPORT_FORMAT")", wSendIndex+1, ADDRPORT(ptSends[wSendIndex].dwIP, ptSends[wSendIndex].wPort));
		}
		OspPrintf(TRUE, FALSE, "\n");
	}

	if (wDelNum > 0)
	{
		CTpMsg tMsg;
		tMsg.SetEvent(ev_IframeSndCheck_Res);
		tMsg.SetBody(&wRecvPortLocal, sizeof(wRecvPortLocal));
		tMsg.Post(UMS_MEDIATRANS_APP_INST);
	}

	if ( bDstPort > 0 )
	{
		CTpMsg tMsg;
		tMsg.SetEvent(ev_IframeSndDisCheck_Res);
		tMsg.SetBody(&wRecvPortLocal, sizeof(wRecvPortLocal));
		tMsg.CatBody(&bDstPort, sizeof(bDstPort));
		tMsg.Post(UMS_MEDIATRANS_APP_INST);
	}
}

