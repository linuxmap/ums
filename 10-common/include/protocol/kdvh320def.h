/*****************************************************************************
ģ����      : Kdv H320
�ļ���      : KdvH32Def.h
����ļ�    : 
�ļ�ʵ�ֹ���: H.320Э��ջ�궨��
����        : ���ؾ�
�汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/04/06  1.0         ���ؾ�      ����
2004/11/08  1.0         ����      ����ع��������Ż�����
******************************************************************************/

#ifndef _KDVH320DEF_H
#define _KDVH320DEF_H


//////////////////////////////////////////////////////////////////////////////

//��������ֵ����

#define KDVH320_OK                      (u16)0      //�����ɹ�

#define KDVH320_INVALIDMASK             (u16)1      //��Чʱ϶����
#define KDVH320_MCCFAIL                 (u16)2      //����mcc����e1����ʧ��
#define KDVH320_SEMFAIL                 (u16)3      //������Ҫ���ź���ʧ��
#define KDVH320_TASKFAIL                (u16)4      //������Ҫ�̻߳�����ʧ��
#define KDVH320_HASSTARTUP              (u16)5      //Э��ջ�Ѿ��������ˣ����ܷ�������
#define KDVH320_NEW_MEMORY	            (u16)6      //ģ���ڴ�����������

#define KDVH320_NOTSTARTUP              (u16)100    //Э��ջ��δ�������͵����˹��ܽӿ�

#define KDVH320_COLLIDE                 (u16)110    //���ڴ����ͻ���ø���ģʽʧ��

#define KDVH320_SNDBASFAIL              (u16)120    //����bas��ʧ��
#define KDVH320_NOTINCONF               (u16)121    //���ڻ����в��÷���ָ��
#define KDVH320_INCONF                  (u16)122    //���ڻ�����
#define KDVH320_NOTSUPPORTEDCMD         (u16)123    //��ͼ���ͶԶ˲�֧�ֵ�ָ��
#define KDVH320_BCMODE                  (u16)124    //�㲥ģʽ�²��ܽ��������ķ��Ͳ���
#define KDVH320_INVALIDFECCMODE         (u16)125    //��ͼ������Ч��fecc����
#define KDVH320_FECCNOTSUPPORT          (u16)126    //��֧��fecc����
#define KDVH320_FECCNOTSTARTED          (u16)127    //Ӧ��������fecc���ܽ���fecc����
#define KDVH320_FECCHASSTARTED          (u16)128    //fecc������������������

#define KDVH320_NOTSUPPORTEDTYPE		(u16)130    //��ͼ���Ͳ�֧�ֵ����͵�����
#define KDVH320_BUFFFULL				(u16)131    //�����ݴ滺�����������޷�����ָ������
#define KDVH320_NULLBUFF				(u16)132    //���뻺����Ϊ��
#define KDVH320_INVALIDPARAM            (u16)133    //�������Ϸ�

#define KDVH320_INVALID_CHANID			(u16)134	//����ͨ��id���Ϸ�

#define KDVH320_VIDEOLOOPBACK           (u16)135    //������Ƶ���أ����ܷ�����Ƶ����

#define KDVH320_SHORTTHANTWOFRAM        (u16)200    //ʣ�����ݳ��Ȳ�������������H.221֡��
#define KDVH320_NOTFOUND                (u16)201    //�˴ν��յ������в����ܺ���h.221֡

//////////////////////////////////////////////////////////////////////////////

#define MAXLEN_EPALIAS					(u16)32	    //������󳤶�(��Ч����31byte��Э���й涨)
#define MAXNUM_MT                       (u16)191    //����ն˸���

//////////////////////////////////////////////////////////////////////////////

//���й���ģʽ
typedef enum
{
	callmode_unicast            = 0x01, //����ģʽ
	callmode_broadcast          = 0x02,	//�㲥ģʽ
	callmode_rcvonly            = 0x03,	//ֻ����
	callmode_sndonly            = 0x04,	//ֻ����
	callmode_rcvandsnd          = 0x05,	//�����ҷ���
		
} emCallWorkMode;

//////////////////////////////////////////////////////////////////////////////

//��������
typedef enum
{
	dtype_none  = 0, //NULL
	dtype_audio,     //Audio
	dtype_video,     //Video
	dtype_lsd,       //LSD
	dtype_hsd,       //HSD
	dtype_mlp,       //MLP
	dtype_hmlp,      //H-MLP
	dtype_state,     //State Info
	dtype_bas,       //Bas Code
	dtype_cmd,       //C&I
	dtype_fecc       //FECC

} emDataType;

//////////////////////////////////////////////////////////////////////////////

//�ϱ���״̬������
typedef enum
{
	state_remotecapset  = 1, // �Զ�������������ΪTKdvH320CapSet
	state_localmuxmode,      // ����ѡ���ķ��͸���ģʽ������ΪTKDVH320MuxMode
	state_remotemuxmode,     // �Ѽ����ĶԶ˸���ģʽ������ΪTKDVH320MuxMode
	state_framealign,        // ֡��λ��������
	state_framelost,         // ֡ʧ��������Ϊ��ʾ����������������ʧ��������һ��˫��
	state_abitset,           // �Զ���Ϊ���˷��͵�֡δ����
	state_abitclear,         // �Զ���Ϊ���˷��͵�֡����
	state_vidratechange,     // �����ܹ�֧�ֵ������Ƶ�������ʣ�
	                         // ����Ϊ��ʾÿ������ܷ��͵��ֽ�����һ��˫��
		
} emStateType;

//////////////////////////////////////////////////////////////////////////////

//fecc���

/*   
*   h.281 encoded in host bit order:
*   +-------+---------+--------+---------+--------+---------+--------+---------+
*   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
*   +-------+---------+--------+---------+--------+---------+--------+---------+
*/

//fecc����
typedef enum
{
	feccact_Invalid             = 0,  
	feccact_Start               = 0x01,  //��ʼ
	feccact_Continue            = 0x02,  //����
	feccact_Stop                = 0x03,  //ֹͣ
	feccact_SelectVideoSource   = 0x04,  //ѡ����ƵԴ
	feccact_VideoSourceSwitched = 0x05,  //�л���ƵԴ
	feccact_StoreAsPreset       = 0x06,  //�洢Ԥ��λ
	feccact_ActivatePreset      = 0x07,  //�ָ���Ԥ��λ
	feccact_AutoFocus           = 0x11   //�Զ�����

} emFeccAction;

//����ͷ���ƶ���
//PTFZ codes, parameters for action Start, continue and stop.
typedef enum
{
	feccreq_Invalid             = 0,
	feccreq_PanLeft             = 0x80,	//�����ƶ�
	feccreq_PanRight            = 0xc0,	//�����ƶ�
	feccreq_TiltUp              = 0x30,	//�����ƶ�
	feccreq_TiltDown            = 0x20,	//�����ƶ�
	feccreq_FocusIn             = 0x03,	//����
	feccreq_FocusOut            = 0x02,	//Զ��		
	feccreq_ZoomIn              = 0x0c,	//��Ұ��С
	feccreq_ZoomOut             = 0x08,	//��Ұ���
		
	feccreq_BrightnessUp        = 0x01,	//���ȼ�(nonstandard)
	feccreq_BrightnessDown      = 0x04  //���ȼ�(nonstandard)

} emFeccPTFZRequest;

//��ƵԴ����ģʽ
typedef enum
{
	vidmode_motion		= 0,    //Motion video
	vidmode_normal_res  = 0x02,	//Normal resolution image
	vidmode_double_res  = 0x03 	//Double resolution image
	
} emVidWorkMode;


//һЩ����ģʽ��Ӧ��ʱ϶����
typedef enum
{
	tsmode_none         = 0x00000000,
	tsmode_64K          = 0x00000002,
	tsmode_128K         = 0x00000006,
	tsmode_192K         = 0x0000000e,
	tsmode_256K         = 0x0000001e,
	tsmode_320K         = 0x0000003e,
	tsmode_384K         = 0x0000007e,
	tsmode_512K         = 0x000001fe,
	tsmode_768K         = 0x00001ffe,
	tsmode_1152K        = 0x000efffe,
	tsmode_1472K        = 0x01fefffe,
	tsmode_1536K        = 0x03fefffe,
	tsmode_1920K        = 0xfffefffe 
		
} emTSMaskMode;

//////////////////////////////////////////////////////////////////////////////

//��������/////////////////

//��������������� (����������� ��u32���д洢���������������Ϊ32λ)
typedef enum
{
	simplecap_max_num   = 32,             // �����������Ϊ 32 λ
	transcap_max_num    = 24,             // �����������������Ϊ 24 λ
	audcap_max_num      = 9,              // �����Ƶ��������Ϊ 9 λ
	vidcap_max_num      = 16,             // �����Ƶ��������Ϊ 16 λ
	lsdcap_max_num      = 16,             // ���LSD ��������Ϊ 16 λ
	hsdcap_max_num      = 11,             // ���HSD ��������Ϊ 11 λ
	mlpcap_max_num      = 17,             // ���mlp ��������Ϊ 17 λ
	hmlpcap_max_num     = 9               // ���hmlp��������Ϊ 9 λ

} emMaxCapNum;

//������������
typedef enum
{
	transcap_none       = 0x00000000,	  // no this capability

	transcap_smcomp     = 0x00000001,	  // transrate sm-comp

	transcap_128K       = 0x00000002,	  // transrate 128K
	transcap_192K       = 0x00000004,	  // transrate 192K
	transcap_256K       = 0x00000008,	  // transrate 256K
	transcap_320K       = 0x00000010,	  // transrate 320K
	transcap_512K       = 0x00000020,	  // transrate 512K
	transcap_768K       = 0x00000040,	  // transrate 768k
	transcap_1152K      = 0x00000080,	  // transrate 1152K

	transcap_1b         = 0x00000100,	  // transrate 1B
	transcap_2b         = 0x00000200,	  // transrate 2B
	transcap_3b         = 0x00000400,	  // transrate 3B
	transcap_4b         = 0x00000800,	  // transrate 4B
	transcap_5b         = 0x00001000,	  // transrate 5B
	transcap_6b         = 0x00002000,	  // transrate 6B

	transcap_restrict   = 0x00004000,	  // transrate restrict
	transcap_6bh0comp   = 0x00008000,	  // transrate 6B-H0-Comp

	transcap_h0         = 0x00010000,	  // transrate 1 H0
	transcap_2h0        = 0x00020000,	  // transrate 2 H0
	transcap_3h0        = 0x00040000,	  // transrate 3 H0
	transcap_4h0        = 0x00080000,	  // transrate 4 H0
	transcap_5h0        = 0x00100000,	  // transrate 5 H0
	
	transcap_1472K      = 0x00200000,	  // transrate 1472K

	transcap_h11        = 0x00400000,	  // transrate H11
	transcap_h12        = 0x00800000 	  // transrate H12
		
} emTransCapType;

//��Ƶ��������
typedef enum
{
	audcap_none         = 0x00000000,	  // no this capability
	
	audcap_neutral      = 0x00000001,	  // no change to current terminal capabilities
	
	audcap_g711a        = 0x00000002,	  // G.711 a-law
	audcap_g711u        = 0x00000004,	  // G.711 u-law
	audcap_g722_64      = 0x00000008,	  // G.711 and G.722 m1 (real 56kbps)
	audcap_g722_48      = 0x00000010,	  // G.711 and G.722 m1/m2/m3 (real 56kbps) ��������8800mcu�������
	audcap_g728         = 0x00000020,	  // G.711 and G.728
	audcap_g7231        = 0x00000040,	  // G.711 and G.7231
	audcap_g729         = 0x00000080,	  // G.711 and G.729

	audcap_null         = 0x00000100,     // just a filler
	audcap_iso1b        = 0x00000200,	  // Aud-ISO-1B
	audcap_iso2b        = 0x00000400,	  // Aud-ISO-2B
	audcap_iso3b        = 0x00000800,	  // Aud-ISO-3B
	audcap_iso4b        = 0x00001000,	  // Aud-ISO-4B
	audcap_iso5b        = 0x00002000,	  // Aud-ISO-5B
	audcap_iso6b        = 0x00004000,	  // Aud-ISO-6B

	audcap_sample16k    = 0x00008000,	  // Aud-Sample 16k
	audcap_sample22_05k = 0x00010000,     // Aud-Sample 22.05k
	audcap_sample24k    = 0x00020000,	  // Aud-Sample 24k
	audcap_sample32k    = 0x00040000,	  // Aud-Sample 32k
	audcap_sample44_1k  = 0x00080000,     // Aud-Sample 44.1k
	audcap_sample48k    = 0x00100000,	  // Aud-Sample 48k

	audcap_coremode1    = 0x00200000,	  // Aud-CorrMode-1
	audcap_coremode2    = 0x00400000,	  // Aud-CorrMode-2
	audcap_coremode3    = 0x00800000,	  // Aud-CorrMode-3
	
	audcap_asyncmode    = 0x01000000,	  // Aud-AsyncMode
	
	audcap_layer1       = 0x02000000,	  // Aud-LayerI
	audcap_layer2       = 0x04000000,	  // Aud-LayerII
	audcap_layer3       = 0x08000000 	  // Aud-LayerIII
		
} emAudCapType;

//��Ƶ��������
typedef enum
{
	vidcap_none         = 0x00000000,	  // no this capability
	vidcap_h261qcif     = 0x00000001,	  // H.261 QCIF
	vidcap_h261cif      = 0x00000002,	  // H.261 CIF and QCIF
	vidcap_mpeg1        = 0x00000004,     // MPEG1
    vidcap_h263qcif     = 0x00000008,     // h.263 QCIF and SQCIF
    vidcap_h263cif      = 0x00000010,     // h.263 CIF
    vidcap_h263_4cif    = 0x00000020,     // h.263 4CIF
    vidcap_h263_16cif   = 0x00000040      // h.263 16CIF
		
} emVidCapType;

//��Ƶ����֡����������
typedef enum
{
	vidcap_mpi_12997    = 0x00000100,	  // mpi=1/29.97
	vidcap_mpi_22997    = 0x00000200,	  // mpi=2/29.97
	vidcap_mpi_32997    = 0x00000400,	  // mpi=3/29.97
	vidcap_mpi_42997    = 0x00000800, 	  // mpi=4/29.97
    vidcap_mpi_52997    = 0x00001000,     // mpi=5/29.97
    vidcap_mpi_62997    = 0x00002000,     // mpi=6/29.97
    vidcap_mpi_102997   = 0x00004000,     // mpi=10/29.97
    vidcap_mpi_152997   = 0x00008000,     // mpi=15/29.97
    vidcap_mpi_302997   = 0x00010000      // mpi=30/29.97
		
} emVidCapMPIType;

//LSD��������
typedef enum
{
	lsdcap_none         = 0x00000000,	  // no this capability
	lsdcap_var          = 0x00000001,	  // LSD var  rate
	lsdcap_300          = 0x00000002,	  // LSD 300  rate
	lsdcap_1200         = 0x00000004,	  // LSD 1200 rate
	lsdcap_4800         = 0x00000008,	  // LSD 4800 rate
	lsdcap_6400         = 0x00000010,	  // LSD 6400 rate
	lsdcap_8000         = 0x00000020,	  // LSD 8000 rate
	lsdcap_9600         = 0x00000040,	  // LSD 9600 rate
	lsdcap_14_4K        = 0x00000080,	  // LSD 14.4K rate
	lsdcap_16K          = 0x00000100,	  // LSD 16K  rate
	lsdcap_24K          = 0x00000200,	  // LSD 24K  rate
	lsdcap_32K          = 0x00000400,	  // LSD 32K  rate
	lsdcap_40K          = 0x00000800,	  // LSD 40K  rate
	lsdcap_48K          = 0x00001000,	  // LSD 48K  rate
	lsdcap_56K          = 0x00002000,	  // LSD 56K  rate
	lsdcap_62_4K        = 0x00004000,	  // LSD 62.4K  rate
	lsdcap_64K          = 0x00008000 	  // LSD 64K  rate
	
} emLSDCapType;

//HSD��������
typedef enum
{
	hsdcap_none         = 0x00000000,	  // no this capability
	hsdcap_var          = 0x00000001,	  // HSD var  rate
	hsdcap_64K          = 0x00000002,	  // HSD 64K  rate
	hsdcap_128K         = 0x00000004,	  // HSD 128K rate
	hsdcap_192K         = 0x00000008,	  // HSD 192K rate
	hsdcap_256K         = 0x00000010,	  // HSD 256K rate
	hsdcap_320K         = 0x00000020,	  // HSD 320K rate
	hsdcap_384K         = 0x00000040,	  // HSD 384K rate
	hsdcap_512K         = 0x00000080,	  // HSD 512K rate
	hsdcap_768K         = 0x00000100,	  // HSD 768K rate
	hsdcap_1152K        = 0x00000200,	  // HSD 1152K rate
	hsdcap_1536K        = 0x00000400 	  // HSD 1536K rate
		
} emHSDCapType;

//MLP��������
typedef enum
{
	mlpcap_none         = 0x00000000,	  // no this capability
	mlpcap_var          = 0x00000001,	  // MLP var  rate
	mlpcap_4K           = 0x00000002,	  // MLP 4K   rate
	mlpcap_6_4K         = 0x00000004,	  // MLP 6.4k rate

	mlpcap_set1         = 0x00000008,	  // MLP set1: 6.4k 14.4k 32k 40k
	mlpcap_set2         = 0x00000010,	  // set2: 4k 6.4k 8k 14.4k 16k 22.4k 24k 30.4k 32k 38.4k 40k 46.4k 62.4k

	mlpcap_14_4K        = 0x00000020,	  // MLP 14.4K rate
	mlpcap_22_4K        = 0x00000040,	  // MLP 22.4K rate
	mlpcap_30_4K        = 0x00000080,	  // MLP 30.4K rate
	mlpcap_38_4K        = 0x00000100,	  // MLP 38.4K rate
	mlpcap_46_4K        = 0x00000200,	  // MLP 46.4K rate
	mlpcap_62_4K        = 0x00000400,	  // MLP 62.4K rate

	mlpcap_8K           = 0x00000800,	  // MLP 8K   rate
	mlpcap_16K          = 0x00001000,	  // MLP 16K  rate
	mlpcap_24K          = 0x00002000,	  // MLP 24K  rate
	mlpcap_32K          = 0x00004000,	  // MLP 32K  rate
	mlpcap_40K          = 0x00008000,	  // MLP 40K  rate
	mlpcap_64K          = 0x00010000 	  // MLP 64K  rate
		
} emMLPCapType;

//H-MLP��������
typedef enum
{
	hmlpcap_none        = 0x00000000,	  // no this capability
	hmlpcap_var         = 0x00000001,	  // H-MLP var  rate

	hmlpcap_14_4K       = 0x00000002,	  // H-MLP 14.4K rate
	hmlpcap_62_4K       = 0x00000004,	  // H-MLP 62.4K rate
	
	hmlpcap_64K         = 0x00000008,	  // H-MLP 64K  rate
	hmlpcap_128K        = 0x00000010,	  // H-MLP 128K rate
	hmlpcap_192K        = 0x00000020,	  // H-MLP 192K rate
	hmlpcap_256K        = 0x00000040,	  // H-MLP 256K rate
	hmlpcap_320K        = 0x00000080,	  // H-MLP 320K rate
	hmlpcap_384K        = 0x00000100 	  // H-MLP 384K rate
	
} emHMLPCapType;

//others��������
typedef enum
{
	othercap_none       = 0x00000000,	  // no this capability

	othercap_encrypt    = 0x00000001,	  // Encrypt   Cap
	othercap_mbe        = 0x00000002,	  // MBE       Cap
	othercap_esccf      = 0x00000004,	  // ESCCF     Cap
	othercap_v120lsd    = 0x00000008,	  // V.120-LSD Cap
	othercap_v120hsd    = 0x00000010,	  // V.120-HSD Cap
	othercap_v14lsd     = 0x00000020,	  // V.14-LSD  Cap
	othercap_v14hsd     = 0x00000040,	  // V.14-HSD  Cap
	othercap_h224mlp    = 0x00000080,	  // H.224-MLP Cap
	othercap_h224lsd    = 0x00000100,	  // H.224-HSD Cap
	othercap_h224hsd    = 0x00000200,	  // H.224-HSD Cap
	othercap_h224sim    = 0x00000400,	  // H.224-SIM Cap
	othercap_t120       = 0x00000800,	  // T.120-CAP Cap

	othercap_nildata    = 0x00001000,	  // Nil-Data  Cap
	othercap_h224token  = 0x00002000,	  // H.224-token Cap
	othercap_h221ta6    = 0x00004000 	  // H.221 Table A.6 Cap
		
} emOtherCapType;

//////////////////////////////////////////////////////////////////////////////

//���ӹ���ʱ���غ����Ͷ���/////////////////

//���ӹ���ģʽ***********************
//�����������221֡�����fas��bas�ֽ� ֻ����Э��ջ��ʼ��ʱ��������;�����޸�

typedef enum
{
	transtype_close = 0,	  // closed	

	transtype_64K,            // transrate 1 B
	transtype_2_64K,          // transrate 2 B
	transtype_3_64K,          // transrate 3 B
	transtype_4_64K,          // transrate 4 B
	transtype_5_64K,          // transrate 5 B
	transtype_6_64K,          // transrate 6 B
	
	transtype_384K,           // transrate 1 H0
	transtype_2_384K,         // transrate 2 H0
	transtype_3_384K,         // transrate 3 H0
	transtype_4_384K,         // transrate 4 H0
	transtype_5_384K,         // transrate 5 H0

	transtype_1536K,          // transrate H11
	transtype_1920K,          // transrate H12

	transtype_128K,           // transrate 128kbps
	transtype_192K,           // transrate 192kbps
	transtype_256K,           // transrate 256kbps
	transtype_320K,           // transrate 320kbps
	transtype_lossic,         // transrate loss i.c.
	transtype_512K,           // transrate 512kbps
	transtype_768K,           // transrate 768kbps
	transtype_1152K,          // transrate 1152kbps
	transtype_1472K           // transrate 1472kbps
		
} emTransWorkType;	

//ý������***********************

typedef enum
{
	payloadtype_none = 0,

	//��Ƶͨ����ʽ
	audtype_Begin,
	audtype_g711a_56K,        // G.711 A-law 56kbps
	audtype_g711u_56K,        // G.711 U-law 56kbps
	audtype_g711a_48K,        // G.711 A-law 48kbps
	audtype_g711u_48K,        // G.711 U-law 48kbps
	audtype_g722_56K,         // G.722 56kbps 
	audtype_g722_48K,         // G.722 48kbps   
	audtype_g728,  	          // G.728
	audtype_g729,  	          // G.729
	audtype_g7231, 	          // G.7231	
	audtype_End,
		
	//��Ƶͨ����ʽ
	vidtype_Begin,	
	vidtype_h261,
	vidtype_h263,
	vidtype_End,

	//lsdͨ����ʽ
	lsdtype_Begin,
	lsdtype_300,  	          // LSD 300  rate
	lsdtype_1200,  	          // LSD 1200 rate
	lsdtype_4800,  	          // LSD 4800 rate
	lsdtype_6400,  	          // LSD 6400 rate
	lsdtype_8000,  	          // LSD 8000 rate
	lsdtype_9600,  	          // LSD 9600 rate
	lsdtype_14_4K,  	      // LSD 14.4K rate
	lsdtype_16K,  	          // LSD 16K  rate
	lsdtype_24K,  	          // LSD 24K  rate
	lsdtype_32K,  	          // LSD 32K  rate
	lsdtype_40K,  	          // LSD 40K  rate
	lsdtype_48K,  	          // LSD 48K  rate
	lsdtype_56K,  	          // LSD 56K  rate
	lsdtype_62_4K,  	      // LSD 62.4K  rate
	lsdtype_64K,  	          // LSD 64K  rate
	lsdtype_var,  	          // LSD var  rate
	lsdtype_End,
		
	//hsdͨ����ʽ
	hsdtype_Begin,
	hsdtype_64K,  	          // HSD 64K  rate
	hsdtype_128K,  	          // HSD 128K rate
	hsdtype_192K,  	          // HSD 192K rate
	hsdtype_256K,  	          // HSD 256K rate
	hsdtype_320K,  	          // HSD 320K rate
	hsdtype_384K,  	          // HSD 384K rate
	hsdtype_512K,  	          // HSD 512K rate
	hsdtype_768K,  	          // HSD 768K rate
	hsdtype_1152K,  	      // HSD 1152K rate
	hsdtype_1536K,  	      // HSD 1536K rate
	hsdtype_var,  	          // HSD var  rate
	hsdtype_End,

	//mlpͨ����ʽ
	mlptype_Begin,
	mlptype_4K,  	          // MLP 4K   rate
	mlptype_6_4K,  	          // MLP 6.4k rate	
	mlptype_8K,  	          // MLP 8K   rate
	mlptype_14_4K,  	      // MLP 14.4Krate
	mlptype_16K,  	          // MLP 16K  rate
	mlptype_22_4K,  	      // MLP 22.4Krate
	mlptype_24K,  	          // MLP 24K  rate
	mlptype_30_4K,  	      // MLP 30.4K rate
	mlptype_32K,  	          // MLP 32K  rate
	mlptype_38_4K,  	      // MLP 38.4K rate
	mlptype_40K,  	          // MLP 40K  rate
	mlptype_46_4K,  	      // MLP 46.4K rate
	mlptype_62_4K,  	      // MLP 62.4K rate	
	mlptype_64K,  	          // MLP 64K  rate
	mlptype_var,  	          // MLP var  rate
	mlptype_End,

	//hmlpͨ����ʽ
	hmlptype_Begin,
	hmlptype_14_4K,  	      // H-MLP 14.4K rate
	hmlptype_62_4K,  	      // H-MLP 62.4K rate	
	hmlptype_64K,  	          // H-MLP 64K  rate
	hmlptype_128K,  	      // H-MLP 128K rate
	hmlptype_192K,  	      // H-MLP 192K rate
	hmlptype_256K,  	      // H-MLP 256K rate
	hmlptype_320K,  	      // H-MLP 320K rate
	hmlptype_384K,  	      // H-MLP 384K rate
	hmlptype_var,  	          // H-MLP var  rate
	hmlptype_End,

	payloadtype_end

} emPayloadType;

//////////////////////////////////////////////////////////////////////////////

//ָ���***********************

// h.230 defined c&i
typedef enum
{
	h_ci_invalid = 0,           // invalid c&i

	//video
	h_ci_VidIndicateSuppressed, //[incoming]&[outgoing]: [NULL]&[NULL] ͼ����ʾֹͣ����
	h_ci_VidIndicateActive,     //[incoming]&[outgoing]: [NULL]&[NULL] ͼ����ʾ��������
	h_ci_VidIndicateActive2,    //[incoming]&[outgoing]: [NULL]&[NULL] ͼ����ʾ��������(vid no.2)
	h_ci_VidIndicateActive3,    //[incoming]&[outgoing]: [NULL]&[NULL] ͼ����ʾ��������(vid no.3)
	h_ci_VidIndicateReady,      //[incoming]&[outgoing]: [NULL]&[NULL] ͼ����ʾԤ����������
	h_ci_VidCommandFreeze,      //[incoming]&[outgoing]: [NULL]&[NULL] ͼ�񶳽�����
	h_ci_VidCommandUpdate,      //[incoming]&[outgoing]: [NULL]&[NULL] ͼ��ǿ�Ƹ�������
    h_ci_VidH262H263,           //h263 cap
	h_ci_VidIndicate_VSTRD,     //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "video spatial temporal tradeoff preference"
	h_ci_VidIndicate_VSTRDENCLVL,//[incoming]&[outgoing]: [NULL]&[NULL] video indicate "video spatial temporal tradeoff encoder level"
	h_ci_VidIndicate_CPCF,      //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "custom picture clock frequency"
	h_ci_VidIndicate_GHOP,      //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "H.263 GOB header on preference"
	h_ci_VidIndicate_CancelGHOP,//[incoming]&[outgoing]: [NULL]&[NULL] video indicate "Cancel-H.263 GOB header on preference"
	h_ci_VidIndicate_CSFMT,     //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "H.263 Custom Source Formate Preference"
	h_ci_VidIndicate_CPAR,      //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "H.263 Custom Pixel Aspect Ratio Preference"
	h_ci_VidIndicate_SCLPREF,   //[incoming]&[outgoing]: [NULL]&[NULL] video indicate "H.263 Scalablity Preference"		
	h_ci_VidNotDecodeMBs,       //[incoming]&[outgoing]: [NULL]&[NULL]       ������MB��������
	h_ci_VidFastUpdateGOB,      //[incoming]&[outgoing]: [TVFUGOB]&[TVFUGOB] GOB��������
	h_ci_VidFastUpdateMB,       //[incoming]&[outgoing]: [TVFUMB]&[TVFUMB]   MB��������

	//audio
	h_ci_AudIndicateMuted,      //[incoming]&[outgoing]: [NULL]&[NULL]  ��Ƶ�طž���
	h_ci_AudIndicateActive,     //[incoming]&[outgoing]: [NULL]&[NULL]  ��Ƶ�طż���
	h_ci_AudCommandEqualize,    //[incoming]&[outgoing]: [NULL]&[NULL]  ��Ƶ����
	h_ci_AudCommandZeroDelay    //[incoming]&[outgoing]: [NULL]&[NULL]  ��Ƶ0�ӳ�

} emH230CIType;

//self defined c&i

#define KDVH320_CI_TRANSRATE        (u16)1000	//�Զ˴�������ģʽָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_AUDIO            (u16)1001	//�Զ˴�������Ƶ����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_VIDEO            (u16)1002	//�Զ˴�������Ƶ����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_LSD              (u16)1003	//�Զ˴�����LSD����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_HSD              (u16)1004	//�Զ˴�����HSD����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_MLP              (u16)1005	//�Զ˴�����MLP����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_HMLP             (u16)1006	//�Զ˴�����H-MLP����ָ�����Ϊ��ʾ�����һ����
#define KDVH320_CI_ENCRYPT          (u16)1007	//�Զ˴�����Encrypt����ָ�0���������㣺��
#define KDVH320_CI_V120LSD          (u16)1008	//V.120-LSD
#define KDVH320_CI_V120HSD          (u16)1009	//V.120-HSD
#define KDVH320_CI_V14LSD           (u16)1010	//V.14-LSD
#define KDVH320_CI_V14HSD           (u16)1011	//V.14-HSD
#define KDVH320_CI_H224MLP_ON       (u16)1012	//H.224-MLP-ON
#define KDVH320_CI_H224MLP_OFF      (u16)1013	//H.224-MLP-OFF
#define KDVH320_CI_H224LSD_ON       (u16)1014	//H.224-LSD-ON
#define KDVH320_CI_H224LSD_OFF      (u16)1015	//H.224-LSD-OFF
#define KDVH320_CI_H224HSD_ON       (u16)1016	//H.224-HSD-ON
#define KDVH320_CI_H224HSD_OFF      (u16)1017	//H.224-HSD-OFF
#define KDVH320_CI_T120_ON          (u16)1018	//T.120-ON
#define KDVH320_CI_T120_OFF         (u16)1019	//T.120-OFF
#define KDVH320_CI_H224TOKEN_ON     (u16)1020	//H.224-TOKEN-ON
#define KDVH320_CI_H224TOKEN_OFF    (u16)1021	//H.224-TOKEN-OFF
#define KDVH320_CI_H221TA6CMD       (u16)1022	//Commands from H.221 Table A.6

#define KDVH320_CI_NUMBER           (u16)2000	//Number
#define KDVH320_CI_CHARACTER        (u16)2001	//Character
#define KDVH320_CI_CAPMARK          (u16)2002	//��������ʼ�����
#define KDVH320_CI_TRCAP            (u16)2003	//��������
#define KDVH320_CI_AUCAP            (u16)2004	//��Ƶ����
#define KDVH320_CI_VIDCAP           (u16)2005	//��Ƶ����
#define KDVH320_CI_LSDCAP           (u16)2006	//lsd����
#define KDVH320_CI_HSDCAP           (u16)2007	//HSD����
#define KDVH320_CI_MLPCAP           (u16)2008	//MLP����
#define KDVH320_CI_HMLPCAP          (u16)2009	//HMLP����
#define KDVH320_CI_OTHERCAP         (u16)2010	//��������

#define KDVH320_CI_CANCELMCC        (u16)2050	//Cancel MCC
#define KDVH320_CI_CANCELMIZ        (u16)2051	//Cancel MIZ
#define KDVH320_CI_CANCELMIS        (u16)2052	//Cancel MIS
#define KDVH320_CI_CANCELMCV        (u16)2053	//Cancel MCV
#define KDVH320_CI_CANCELMIV        (u16)2054	//Cancel MIV
#define KDVH320_CI_CANCELMMS        (u16)2055	//Cancel MMS
#define KDVH320_CI_CANCELMIM        (u16)2056	//Cancel MIM

//h.230 defined c&i

//video

//audio

//for maintenance purpose
#define KDVH320_CI_LCV              (u16)2122	//loopback command "video loop request"
#define KDVH320_CI_LCD              (u16)2123	//loopback command "digital loop request"
#define KDVH320_CI_LCA              (u16)2124	//loopback command "audio loop request"
#define KDVH320_CI_LCO              (u16)2125	//loopback command off

//multipoint working
#define KDVH320_CI_MCV              (u16)2126	//Multipoint Command Visualization-forcing
#define KDVH320_CI_MIV              (u16)2127	//Multipoint Indication Visualization-forcing
#define KDVH320_CI_MVC              (u16)2128	//Multipoint Visualization Capability
#define KDVH320_CI_MVA              (u16)2129	//Multipoint Visualization Achieved
#define KDVH320_CI_MVR              (u16)2130	//Multipoint Visualization Refused/Revoked
#define KDVH320_CI_MCC              (u16)2131	//Multipoint Command Conference
#define KDVH320_CI_MCS              (u16)2132	//Multipoint Command Symmetrical data-transmission
#define KDVH320_CI_MCN              (u16)2133	//Multipoint Command Negating MCS
#define KDVH320_CI_MMS              (u16)2134	//Multipoint Command Mode-Symmetrize
#define KDVH320_CI_MIZ              (u16)2135	//Multipoint Indication Zero-communication
#define KDVH320_CI_MIS              (u16)2136	//Multipoint Secondary-status
#define KDVH320_CI_MIM              (u16)2137	//Multipoint Indicate Master-MCU
#define KDVH320_CI_MIL              (u16)2138	//Multipoint Indicate Loop
#define KDVH320_CI_MIH              (u16)2139	//Multipoint Indicate Hierarchy
#define KDVH320_CI_MIJ              (u16)2140	//Multipoint Indicate Joined_Real_Conference
#define KDVH320_CI_RAN              (u16)2141	//Random Number
#define KDVH320_CI_TIA              (u16)2142	//Terminal Indicate Assignment
#define KDVH320_CI_TIN              (u16)2143	//Terminal Indicate Number
#define KDVH320_CI_TIL              (u16)2144	//Terminal Indicate List ((msg body: TH320TIL))
#define KDVH320_CI_TID              (u16)2145	//Terminal Indicate Dropped
#define KDVH320_CI_TCU              (u16)2146	//Terminal Command Update
#define KDVH320_CI_TIF              (u16)2147	//Terminal Indicate Floor-request
#define KDVH320_CI_TIC              (u16)2148	//Terminal Indicate Capability
#define KDVH320_CI_TIX              (u16)2149	//Terminal Indicate additional-channel-X
#define KDVH320_CI_TCI              (u16)2150	//Terminal Command Identify
#define KDVH320_CI_TCS_0            (u16)2151	//Reserved
#define KDVH320_CI_TCS_1            (u16)2152	//Terminal Command String: password
#define KDVH320_CI_TCS_2            (u16)2153	//Terminal Command String: identiy(person or terminal)
#define KDVH320_CI_TCS_3            (u16)2154	//Terminal Command String: conference identity
#define KDVH320_CI_TCS_4            (u16)2155	//Externsion address
#define KDVH320_CI_TII              (u16)2156	//Terminal Indicate Identity
#define KDVH320_CI_IIS              (u16)2157	//Information Indicate Sting (msg body: TH320IIS)
#define KDVH320_CI_TIS              (u16)2158	//Terminal Indicate identity-stop
#define KDVH320_CI_TIE              (u16)2159	//Terminal Indicate End_of_Listing
#define KDVH320_CI_TCP              (u16)2160	//Terminal Command Personal-identifer
#define KDVH320_CI_TIP              (u16)2161	//Terminal Indicate Personal-identifer (msg body: TH320MtExt)
#define KDVH320_CI_TCA              (u16)2162	//Token Command Association
#define KDVH320_CI_TIR              (u16)2163	//Token Indicate Response (msg body: TKdvH320TIR)
#define KDVH320_CI_VIN              (u16)2164	//Video Indicate Number
#define KDVH320_CI_VIN2             (u16)2165	//Video Indicate Number(2)
#define KDVH320_CI_VIC              (u16)2166	//Video Indicate Compose
#define KDVH320_CI_VIM              (u16)2167	//Video Indicate Mixing
#define KDVH320_CI_VCB              (u16)2168	//Video Command Broadcasting
#define KDVH320_CI_CancelVCB        (u16)2169	//Cancel Video Command Broadcasting
#define KDVH320_CI_VCS              (u16)2170	//Video Command Select
#define KDVH320_CI_CancelVCS        (u16)2171	//Cancel Video Command Select
#define KDVH320_CI_VCR              (u16)2172	//
#define KDVH320_CI_CIC              (u16)2173	//Chair-control Indicate Capability
#define KDVH320_CI_CCD              (u16)2174	//Chair Command Disconnect
#define KDVH320_CI_CIR              (u16)2175	//Chair Indicate Release/refuse
#define KDVH320_CI_CCK              (u16)2176	//Chair Command Kill
#define KDVH320_CI_CCA              (u16)2177	//Chair Command Acquire
#define KDVH320_CI_DCA_L            (u16)2178	//LSD/HSD Command Acquire-token
#define KDVH320_CI_DCA_H            (u16)2179	//LSD/HSD
#define KDVH320_CI_CIT              (u16)2180	//Chair Indicate Token
#define KDVH320_CI_DIT_L            (u16)2181	//LSD Indicate Token
#define KDVH320_CI_DIT_H            (u16)2182	//HSD Indicate Token
#define KDVH320_CI_CCR              (u16)2183	//Chair Command Release/refuse
#define KDVH320_CI_DCR_L            (u16)2184	//LSD/HSD Command Release/refuse
#define KDVH320_CI_DCR_H            (u16)2185	//
#define KDVH320_CI_CIS              (u16)2186	//Chair Indicate Stopped-using-token
#define KDVH320_CI_DIS_L            (u16)2187	//LSD Indicate Stopped-using-token
#define KDVH320_CI_DIS_H            (u16)2188	//HSD Indicate Stopped-using-token
#define KDVH320_CI_DCC_L            (u16)2189	//LSD/HSD Command Close
#define KDVH320_CI_DCC_H            (u16)2190	//
#define KDVH320_CI_DCM              (u16)2191	//Data Command MLP

//channel aggregation and restricted network situations
#define KDVH320_CI_AggIN            (u16)2192
#define KDVH320_CI_NII              (u16)2193	//network indicate incompatible-aggregators
#define KDVH320_CI_RIR              (u16)2194	//Restricted_network Indicate Restrict
#define KDVH320_CI_RID              (u16)2195	//Restricted_network Indicate Denied
#define KDVH320_CI_RIU              (u16)2196	//Restricted network Indicate Unrestrict

//used in the transfer of network addresses
#define KDVH320_CI_NIAm             (u16)2197	//network indicate address
#define KDVH320_CI_NCAi             (u16)2198	//network command send_address-inital
#define KDVH320_CI_NCAa             (u16)2199	//network command send_address-additional
#define KDVH320_CI_NIAs             (u16)2200	//network indicate address
#define KDVH320_CI_NIS              (u16)2201	//network indicate same_addresses
#define KDVH320_CI_NIC              (u16)2202	//network indicate consecutive_addresses
#define KDVH320_CI_NID              (u16)2203	//network indicate double_addresses
#define KDVH320_CI_NIQs             (u16)2204	//network indicate query_address
#define KDVH320_CI_NIQm             (u16)2205	//network indicate query_address
#define KDVH320_CI_NIR              (u16)2206	//network indicate refuse_address

//IIS type define
//n = 0: reserved
//n = 1: password
//n = 2: identity (person or terminal)
//n = 3: conference identity
//n = 4: extension address
//n = 5 to 31: reserved
#define IIS_TYPE_RESERVED				0x00
#define IIS_TYPE_PASSWORD				0x01
#define IIS_TYPE_IDENTITY				0x02
#define IIS_TYPE_CONFID					0x03
#define IIS_TYPE_EXADDR					0x04

/*
 *	��Ҫ���¶�C&I��ֵ���ж��壬�淶�����壬�ҵ�һ��C&I�궨��ֵ��BAS��ֵ��ֱ��ӳ���ϵ��
    �Ӷ����ⷢ�ͺͽ���C&I(BAS)��ʱ��ĺܶ��switch-case�ıȽϹ��̡�

	BAS�������̣�������������C& I ����룩

	ԭ���ķ�����
	����C&I: ���õ���switch��case�ṹ���ҵ��ϲ�C&I����H320Э��ջ���ϲ�ʹ����ʹ�ã�
	ʹ�ú궨������־����ʵ�ʵ�BAS���ӳ�䣬�ϲ�ʹ�õ�C&I �궨���ֵ��BAS��ֵ��һ�¡�

	���գ����õ���switch��case�ṹ��BAS���ת�Ƶķ������Ƶ���һ�������ϲ�ʹ�õ�C&I.
	H320ϵ�е�BAS���ɴ�Լ����������ɡ���֮������й�����H221��table A.1��һ���ܱ�
	�������е�H221��H230�ı����ͨ��table A.1���Ӷ����� BAS�����������ֻ��1��

    �������ö�ٵ��������������Ե�C&I.���ҶԸ���BAS���񲻼������֡�
 */

#endif ////

//----------------------------------------------------------------------

//end of file



