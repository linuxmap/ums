#ifndef _h_umsinnertype_h__
#define _h_umsinnertype_h__

#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif

#ifndef localmin
#define localmin(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef localmax
#define localmax(a,b) ((a)>(b)?(a):(b))
#endif

#define UMS_CONF_MAX_DS_NUM 3
#define TP_MAX_ALIAS_NUM 128
#define HandleChannle	s32

//���� ��20000-22000֮��Ķ˿ڿճ�������Ϊ�������ײ�ģ����ܻ�ռ��
#define UMS_VMP_BEGIN_PORT		10000	//ÿ������ʹ��400���˿ڣ����16������  ��6400   ��16400
#define UMS_AUD_MIX_BEGIN_PORT	22000	//ÿ��������40����64�������� ��ռ��2560 ����ֻ����38���������Ķ˿ڣ���Ϊʵ����Ŀ�䲻����ô�����������23520		
#define UMS_AUD_BAS_BEGIN_PORT	16400	//ÿ��������ռ��210����16������������ռ��3360     ��19760
#define UMS_MPU2TP_BEGIN_PORT	23520	//mpu2tp ͨ��ռ����ʼ�˿ڣ�ÿ��vmp-tpռ��15�������32�����ӣ�480 ��24000
#define UMS_BAS_BEGIN_PORT		24000	//ÿ������ʹ��1000���˿ڣ����16������ ��16000  ��40000

//��10000 �� 40000����������忨��Ŀǰ��ʣ��1000�˿ڣ� ���������ռ�ý϶ࣨ16000����Ӧ�ÿ��Լ����Ż�

//��40000��ʼ�����ڻ᳡����
#define UMS_EP_TRANS_BEGIN_PORT		40000
#define UMS_EP_TRANS_END_PORT		60000


// bFcp �˿ڶ�
#define  UMS_BFCP_BEGIN_PORT	60010
#define  UMS_BFCP_END_PORT		60026

// mcu
#define UMS_MCU_LISTEN_PORT		3337

// Fecc
#define UMS_FECC_BEGIN_PORT		60030
#define UMS_FECC_END_PORT		62078

/* H.224�նˣ�����������֧�ֵ�����LSD��HSD�����⣬�������������6400 bit/s LSD�ŵ�������
H.221 ���������м����������ն˻��������������4800 bit/s LSD������������ H.224�նˣ�����������
֧�ֵ�����MLP�����⣬�������������6400 bit/s MLP�����ŵ�������H.221 ����
��׼��ġ�
H.224����Զҡ
*/
// ����ѯ Э���� liuna
#define	H244_H221_SAMPLE_RATE		6400
#define	H244_ENTRY_SAMPLE_RATE		4800


#define KedaManuProductNameDefine		"KedaManuProduct"
#define KedaManuProductValueDefine		"UMS"

#define BRD_PID_IS2_KedaManu   		 		0x04DD      // Is2.2�忨�����汾PID
#define BRD_PID_MPC2_KedaManu   		 	0x04DE      // MPC2�忨�����汾PID

enum EmDiscussModleObj
{
	emDiscussObjForSpeakerEp = 0,   // �����ڷ��Ի᳡
	emDiscussObjForThreeScrEp,      // ������������
	emDiscussObjForSingleScrEp,     // �������ⵥ��
		
	emDiscussObjEnd,
};

//��������
enum EmServiceType
{
	em_unknow_service,
	em_mpu2tp_service,
};


//ע���������
enum EmRegGroupNum
{
	em_FirstGroup, //��һ��
	em_SecondGroup,//�ڶ���ע��
	em_ThirdGroup,
	em_FourthGroup,
		
		
	em_AllGroup,   //ȫ��ע��
};

enum EmScreenNo
{
	em_Screen_Left,
	em_Screen_Mid,
	em_Screen_Right,
	em_Screen_All,		
};

//ÿ�����ݵ�ע��״̬
enum EmUmsRegState
{
	em_un_reg,			//δע��
	em_reging,			//����ע��
	em_reg_success,		//ע��ɹ�
	em_reg_failed,		//ע��ʧ��
};

//ע������
enum EmRegType
{
	em_Sip_reg_type,
	em_Gk_reg_type,
	em_reg_type_end,
};

enum EmRecFileType
{
	em_recfile_unknow,
	em_recfile_normal,	//����ʽ�ļ�
	em_recfile_dstream,	//˫��ʽ�ļ�
};

enum EmRecChanType
{
	em_rec_unknow_chan = 0,		//δ֪��ͨ������
	em_rec_recorder_chan = 1,	//¼��ͨ��
	em_rec_play_chan = 2,		//����ͨ��
};

enum EmRecChanState
{
	em_state_idle = 0,			/*������һ��δ��ͨ��*/
	em_state_rec_ready = 11,		/*׼��¼��״̬  */
	em_state_recordint = 12,		/*����¼��  */
	em_state_rec_pause = 13,		/*��ͣ¼��״̬*/
		
	em_state_play_ready = 21,	/*׼������״̬ */
	em_state_play_readyplay = 22, /*���ò���׼��״̬*/
	em_state_playing = 23,	    /*���ڻ򲥷�*/
	em_state_play_pause = 24,	/*��ͣ����*/
	em_state_ff = 25,			/*���(������ͨ����Ч)*/
	em_state_fb = 26,			/*����(������ͨ����Ч)*/
};

enum EmUmsCodecType
{
	ums_CodecType_unknow,
	ums_CodecType_vid_dec,
	ums_CodecType_vid_enc,
	ums_CodecType_aud_dec,
	ums_CodecType_aud_enc,
	ums_CodecType_Mix_dec,
	ums_CodecType_Mix_enc,
	ums_CodecType_vid_dec_dual,
	ums_CodecType_vid_enc_dual,
};

//��������ͨ�������ʼֵ
enum EmChannelHandle
{
	em_video_send_handle     =	1,		//��Ƶ���;��
	em_video_recv_handle     =	50,		//��Ƶ���վ��
	em_audio_send_handle	 =	100,	//��Ƶ���;��
	em_audio_recv_handle     =	150,	//��Ƶ���վ��
	em_audio_send_mix_handle =	200,	//����ͨ��
	em_audio_recv_mix_handle =	201,	//����ͨ��
	
	em_second_vidsnd_handle	 =	250,	//˫��ͨ��
	em_second_vidrcv_handle	 =	251,	//˫��ͨ��
	em_second_audsnd_handle	 =	252,	//˫��ͨ��
	em_second_audrcv_handle	 =	253,	//˫��ͨ��
	
	em_channel_handle_end	 =	300,
};

enum EmDisChnOprType
{
	EmDisChnAllStart,//ͳһ��������
	EmDisChnAddEp,//��ӻ᳡
	EmDisChnDelEp,//ɾ���᳡
	EmDisChnEpConnect,//�᳡����
	EmDisChnEpDisConnect,//�᳡����
	EmDisChnEpChangeSeat,//�л���ϯ
	EmDisChnChangeSpeakerEp,
	
	EmDisChnOprTypeEnd,
};

//ҵ�����������
enum EmServiceOpType
{
	em_Normal_Op,		//��ͨ�Ĵ���
	em_Assgin_Service,
	em_Start_Service,	//����ҵ��
	em_Stop_Service,	//ֹͣҵ��
	em_Mdy_Service,		//�޸�ҵ�����
	em_Frame_Service,	//����ؼ�֡
};

enum EmServiceRes
{
	em_Res_Success,		//�����ɹ�
	em_Start_Failed,		//����ʧ��
	em_Stop_Failed,			//ֹͣʧ��
	em_Mdy_Failed,			//�޸�ʧ��
	em_Invalid_ServiceID,	//��Ч��ҵ��ID
	em_Service_Working,		//ҵ���Ѿ����ڹ���״̬
	em_Service_No_Working,	//ҵ��δ���ڹ���״̬
	em_Service_No_Reg,		//ҵ��δע��
	em_Invalid_Param,		//��Ч�Ĳ���
	em_Set_Param_Failed,	//���ò�������
};

enum EmRollCallChnOprType
{
	EmRollCallChnAllStart,//ͳһ��������
		EmRollCallChnAddEp,//��ӻ᳡
		EmRollCallChnDelEp,//ɾ���᳡
		EmRollCallChnEpConnect,//�᳡����
		EmRollCallChnEpDisConnect,//�᳡����
		EmRollCallChnEpChangeSeat,//�л���ϯ
		EmRollCallChnChangeSpeakerEp,
		
		EmRollCallChnOprTypeEnd,
};


//��������������������
#define MAX_ADAPTER_MDL_NUM		2
#define MAX_DATASWITCH_MDL_NUM	6	//ת�����������
#define MAX_NETBUF_MDL_NUM		1
#define MAX_AUDMIX_MDL_NUM		64
#define MAX_MPC_MDL_NUM			2
#define TP_UMS_MAX_VMP_NUM		16	//�ϳ���Eqp�������
#define TP_UMS_MAX_BAS_NUM		16	//������Eqp�������
#define TP_UMS_MAX_HDU_NUM		56	//����ǽHDU2�������
#define TP_UMS_MAX_AUD_BAS_NUM	16	//��Ƶ������Eqp�������

#define MCU_NO	192						//MCU NO ���323���»᳡�б��ʱ��ʹ��
#define UMS_MCU_PORT_PORTSPAN	10		//����mcu���� �˿ڼ��10

#define DEFAULT_NETMAX_INDEX1	1
#define DEFAULT_NETMAX_INDEX0	0


//������ʼ����ID
#define EQP_ID_REC_BEG		17
#define EQP_ID_REC_END		32

#define EQP_ID_HDU_BEG		37
#define EQP_ID_HDU_END		106

#define EQP_ID_VMP_BEG		107
#define EQP_ID_VMP_END		122

#define EQP_ID_BAS_BEG		123
#define EQP_ID_BAS_END		138

#define EQP_ID_AUD_MIX_BEG		139
#define EQP_ID_AUD_MIX_END		202

#define EQP_ID_AUD_BAS_BEG		203
#define EQP_ID_AUD_BAS_END		218


//�ڴ������������
#define EQP_ID_TOTAL_END	EQP_ID_AUD_BAS_END + 1

//����ͨ�������͵�ͨ������
#define BAS_ENCRES_3000		3000
#define BAS_ENCRES_1500		1500
#define BAS_ENCRES_1000		1000

#define BAS_CHN_MAX_NUM_EHANCED	7			
#define BAS_CHN_MAX_NUM_BASIC	4

#define AUD_BAS_MAX_CHNL_NUM		7//ÿ����Ƶ���������֧��7������ͨ��
#define AUD_BAS_MAX_OUT_CHNL_NUM	3//ÿ������ͨ�����֧�ֳ�3����Ƶ��ʽ	

#define MC0_BRD_UI_SLOT					0
#define MC1_BRD_UI_SLOT					9
#define NORMAL_BRD_UI_SLOT_DOWN_BOUNDS	8
#define NORMAL_BRD_UI_SLOT_UPBOUNDS		9

#define REC_MAX_CHANNEL					32
#define REC_MAX_STREAM_NUM				5
#define REC_USE_MEDIA					1
#define MPU2TP_USE_MEDIA				1
#define INVALID_REC_CHANNEL				REC_MAX_CHANNEL		

#define UPDATE_TOOLS                    (u8)1         // mpu2�������������Ҫ֪��˭���𵥰�����


//����ǽ�������ʾ����
#define TWLP_SHOW_BLACK_MODE         0
//����ǽ�������ʾ���һ֡
#define TWLP_SHOW_LASTFRAME_MODE     1
//����ǽ�������ʾĬ��ͼƬ
#define TWLP_SHOW_DEFPIC_MODE        2
//����ǽ�������ʾ�Զ���ͼƬ       
#define TWLP_SHOW_USERDEFPIC_MODE    3

//¼���ļ�����ʵ�ʳ���
#define REC_FILE_FILE_LENGTH	64

//��ƷID ����
#define TP_UMS_PRDUT_ID		64
//�������ҵ������
#define UMS_MAX_SERVICE_NUM		32

#define UMS_AUDBAS_ENC_NUM		3

//////////////////////////////////////////////////////////////////////////
//��Ƶ��ʽ����
#define     VIDEO_FORMAT_INVALID            255
#define		VIDEO_FORMAT_SQCIF				1   //SQCIF(128*96)
#define		VIDEO_FORMAT_QCIF				2   //SCIF(176*144)
#define		VIDEO_FORMAT_CIF                3   //CIF(352*288)  - P��
#define     VIDEO_FORMAT_2CIF               4   //2CIF(352*576) - p
#define		VIDEO_FORMAT_4CIF               5   //4CIF(704*576) - P��(H264�´˺�ָ��D1(720*576)   - P�ƣ�N��D1��720*480��)
#define		VIDEO_FORMAT_16CIF				6   //16CIF(1408*1152)
#define		VIDEO_FORMAT_AUTO				7   //����Ӧ��������MPEG4

#define		VIDEO_FORMAT_SIF                8   //SIF(352*240)  - N��
#define     VIDEO_FORMAT_2SIF               9   //2SIF
#define		VIDEO_FORMAT_4SIF               10  //4SIF(704*480) - N��

#define     VIDEO_FORMAT_VGA                11  //VGA(640*480)
#define		VIDEO_FORMAT_SVGA               12  //SVGA(800*600)
#define		VIDEO_FORMAT_XGA                13  //XGA(1024*768)
#define     VIDEO_FORMAT_WXGA               14  //WXGA(1280*768 | 1280*800)

//�������ն˷ֱ��ʸı�
#define		VIDEO_FORMAT_SQCIF_112x96       21  //SQCIF(112*96)
#define		VIDEO_FORMAT_SQCIF_96x80        22  //SQCIF(96*80)

// ����ֱ���
#define     VIDEO_FORMAT_W4CIF              31  //Wide 4CIF(1024*576)
#define     VIDEO_FORMAT_HD720              32  //720 1280*720
#define     VIDEO_FORMAT_SXGA               33  //SXGA 1280*1024
#define     VIDEO_FORMAT_UXGA               34  //UXGA 1600*1200
#define     VIDEO_FORMAT_HD1080             35  //1080  1920*1088(p) 1920*544(i)

//�Ǳ�ֱ��ʣ�1080p��ͼ���������ն˷ֱ��ʸı�
#define     VIDEO_FORMAT_1440x816           41  //1440��816(3/4)
#define     VIDEO_FORMAT_1280x720           42  //1280��720(2/3)
#define     VIDEO_FORMAT_960x544            43  // 960��544(1/2)
#define     VIDEO_FORMAT_640x368            44  // 640��368(1/3)
#define     VIDEO_FORMAT_480x272            45  // 480��272(1/4)

//�Ǳ�ֱ��ʣ�720p��ͼ�� �������ն˷ֱ��ʸı�
#define     VIDEO_FORMAT_720_960x544        51  //960��544(3/4)
#define     VIDEO_FORMAT_720_864x480        52  //864��480(2/3)
#define     VIDEO_FORMAT_720_640x368        53  //640��368(1/2)
#define     VIDEO_FORMAT_720_432x240        54  //432��240(1/3)
#define     VIDEO_FORMAT_720_320x192        55  //320��192(1/4)


#endif // _h_umsinnertype_h__
