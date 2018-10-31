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

//以下 将20000-22000之间的端口空出来，因为有其他底层模块可能会占用
#define UMS_VMP_BEGIN_PORT		10000	//每个板子使用400个端口，最大共16个板子  共6400   到16400
#define UMS_AUD_MIX_BEGIN_PORT	22000	//每个混音器40个，64个混音器 共占用2560 这里只保留38个混音器的端口，因为实际项目配不了这么多混音器。到23520		
#define UMS_AUD_BAS_BEGIN_PORT	16400	//每个适配器占用210个，16个适配器，共占用3360     到19760
#define UMS_MPU2TP_BEGIN_PORT	23520	//mpu2tp 通道占用起始端口，每个vmp-tp占用15个，最大共32个板子，480 到24000
#define UMS_BAS_BEGIN_PORT		24000	//每个板子使用1000个端口，最大共16个板子 共16000  到40000

//从10000 到 40000，用于外设板卡，目前还剩余1000端口， 其中适配板占用较多（16000），应该可以继续优化

//从40000开始，用于会场接收
#define UMS_EP_TRANS_BEGIN_PORT		40000
#define UMS_EP_TRANS_END_PORT		60000


// bFcp 端口段
#define  UMS_BFCP_BEGIN_PORT	60010
#define  UMS_BFCP_END_PORT		60026

// mcu
#define UMS_MCU_LISTEN_PORT		3337

// Fecc
#define UMS_FECC_BEGIN_PORT		60030
#define UMS_FECC_END_PORT		62078

/* H.224终端，除了它可能支持的其他LSD或HSD速率外，必须宣告其进行6400 bit/s LSD信道操作的
H.221 能力。具有加密能力的终端还必须宣告其进行4800 bit/s LSD操作的能力。 H.224终端，除了它可能
支持的其他MLP速率外，必须宣告其进行6400 bit/s MLP数据信道操作的H.221 能力
标准里的。
H.224就是远摇
*/
// 可咨询 协议组 liuna
#define	H244_H221_SAMPLE_RATE		6400
#define	H244_ENTRY_SAMPLE_RATE		4800


#define KedaManuProductNameDefine		"KedaManuProduct"
#define KedaManuProductValueDefine		"UMS"

#define BRD_PID_IS2_KedaManu   		 		0x04DD      // Is2.2板卡渠道版本PID
#define BRD_PID_MPC2_KedaManu   		 	0x04DE      // MPC2板卡渠道版本PID

enum EmDiscussModleObj
{
	emDiscussObjForSpeakerEp = 0,   // 讨论内发言会场
	emDiscussObjForThreeScrEp,      // 讨论内外三屏
	emDiscussObjForSingleScrEp,     // 讨论内外单屏
		
	emDiscussObjEnd,
};

//外设类型
enum EmServiceType
{
	em_unknow_service,
	em_mpu2tp_service,
};


//注册组别类型
enum EmRegGroupNum
{
	em_FirstGroup, //第一组
	em_SecondGroup,//第二组注册
	em_ThirdGroup,
	em_FourthGroup,
		
		
	em_AllGroup,   //全部注册
};

enum EmScreenNo
{
	em_Screen_Left,
	em_Screen_Mid,
	em_Screen_Right,
	em_Screen_All,		
};

//每包数据的注册状态
enum EmUmsRegState
{
	em_un_reg,			//未注册
	em_reging,			//正在注册
	em_reg_success,		//注册成功
	em_reg_failed,		//注册失败
};

//注册类型
enum EmRegType
{
	em_Sip_reg_type,
	em_Gk_reg_type,
	em_reg_type_end,
};

enum EmRecFileType
{
	em_recfile_unknow,
	em_recfile_normal,	//单格式文件
	em_recfile_dstream,	//双格式文件
};

enum EmRecChanType
{
	em_rec_unknow_chan = 0,		//未知的通道类型
	em_rec_recorder_chan = 1,	//录像通道
	em_rec_play_chan = 2,		//放像通道
};

enum EmRecChanState
{
	em_state_idle = 0,			/*表明是一个未用通道*/
	em_state_rec_ready = 11,		/*准备录像状态  */
	em_state_recordint = 12,		/*正在录像  */
	em_state_rec_pause = 13,		/*暂停录像状态*/
		
	em_state_play_ready = 21,	/*准备播放状态 */
	em_state_play_readyplay = 22, /*作好播放准备状态*/
	em_state_playing = 23,	    /*正在或播放*/
	em_state_play_pause = 24,	/*暂停播放*/
	em_state_ff = 25,			/*快进(仅播放通道有效)*/
	em_state_fb = 26,			/*快退(仅播放通道有效)*/
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

//各种类型通道句柄起始值
enum EmChannelHandle
{
	em_video_send_handle     =	1,		//视频发送句柄
	em_video_recv_handle     =	50,		//视频接收句柄
	em_audio_send_handle	 =	100,	//音频发送句柄
	em_audio_recv_handle     =	150,	//音频接收句柄
	em_audio_send_mix_handle =	200,	//混音通道
	em_audio_recv_mix_handle =	201,	//混音通道
	
	em_second_vidsnd_handle	 =	250,	//双流通道
	em_second_vidrcv_handle	 =	251,	//双流通道
	em_second_audsnd_handle	 =	252,	//双流通道
	em_second_audrcv_handle	 =	253,	//双流通道
	
	em_channel_handle_end	 =	300,
};

enum EmDisChnOprType
{
	EmDisChnAllStart,//统一开启讨论
	EmDisChnAddEp,//添加会场
	EmDisChnDelEp,//删除会场
	EmDisChnEpConnect,//会场上线
	EmDisChnEpDisConnect,//会场掉线
	EmDisChnEpChangeSeat,//切换坐席
	EmDisChnChangeSpeakerEp,
	
	EmDisChnOprTypeEnd,
};

//业务操作的类型
enum EmServiceOpType
{
	em_Normal_Op,		//普通的处理
	em_Assgin_Service,
	em_Start_Service,	//启动业务
	em_Stop_Service,	//停止业务
	em_Mdy_Service,		//修改业务参数
	em_Frame_Service,	//请求关键帧
};

enum EmServiceRes
{
	em_Res_Success,		//开启成功
	em_Start_Failed,		//开启失败
	em_Stop_Failed,			//停止失败
	em_Mdy_Failed,			//修改失败
	em_Invalid_ServiceID,	//无效的业务ID
	em_Service_Working,		//业务已经处于工作状态
	em_Service_No_Working,	//业务未处于工作状态
	em_Service_No_Reg,		//业务未注册
	em_Invalid_Param,		//无效的参数
	em_Set_Param_Failed,	//设置参数出错
};

enum EmRollCallChnOprType
{
	EmRollCallChnAllStart,//统一开启点名
		EmRollCallChnAddEp,//添加会场
		EmRollCallChnDelEp,//删除会场
		EmRollCallChnEpConnect,//会场上线
		EmRollCallChnEpDisConnect,//会场掉线
		EmRollCallChnEpChangeSeat,//切换坐席
		EmRollCallChnChangeSpeakerEp,
		
		EmRollCallChnOprTypeEnd,
};


//各种类型外设的最大数量
#define MAX_ADAPTER_MDL_NUM		2
#define MAX_DATASWITCH_MDL_NUM	6	//转发板最大数量
#define MAX_NETBUF_MDL_NUM		1
#define MAX_AUDMIX_MDL_NUM		64
#define MAX_MPC_MDL_NUM			2
#define TP_UMS_MAX_VMP_NUM		16	//合成器Eqp最大数量
#define TP_UMS_MAX_BAS_NUM		16	//适配器Eqp最大数量
#define TP_UMS_MAX_HDU_NUM		56	//电视墙HDU2最大数量
#define TP_UMS_MAX_AUD_BAS_NUM	16	//音频适配器Eqp最大数量

#define MCU_NO	192						//MCU NO 针对323更新会场列表的时候使用
#define UMS_MCU_PORT_PORTSPAN	10		//接入mcu板子 端口间隔10

#define DEFAULT_NETMAX_INDEX1	1
#define DEFAULT_NETMAX_INDEX0	0


//外设起始外设ID
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


//在此添加其他外设
#define EQP_ID_TOTAL_END	EQP_ID_AUD_BAS_END + 1

//适配通道各类型的通道能力
#define BAS_ENCRES_3000		3000
#define BAS_ENCRES_1500		1500
#define BAS_ENCRES_1000		1000

#define BAS_CHN_MAX_NUM_EHANCED	7			
#define BAS_CHN_MAX_NUM_BASIC	4

#define AUD_BAS_MAX_CHNL_NUM		7//每个音频适配器最大支持7个适配通道
#define AUD_BAS_MAX_OUT_CHNL_NUM	3//每个适配通道最大支持出3中音频格式	

#define MC0_BRD_UI_SLOT					0
#define MC1_BRD_UI_SLOT					9
#define NORMAL_BRD_UI_SLOT_DOWN_BOUNDS	8
#define NORMAL_BRD_UI_SLOT_UPBOUNDS		9

#define REC_MAX_CHANNEL					32
#define REC_MAX_STREAM_NUM				5
#define REC_USE_MEDIA					1
#define MPU2TP_USE_MEDIA				1
#define INVALID_REC_CHANNEL				REC_MAX_CHANNEL		

#define UPDATE_TOOLS                    (u8)1         // mpu2升级完后重启需要知道谁发起单板升级


//电视墙最后画面显示黑屏
#define TWLP_SHOW_BLACK_MODE         0
//电视墙最后画面显示最后一帧
#define TWLP_SHOW_LASTFRAME_MODE     1
//电视墙最后画面显示默认图片
#define TWLP_SHOW_DEFPIC_MODE        2
//电视墙最后画面显示自定义图片       
#define TWLP_SHOW_USERDEFPIC_MODE    3

//录播文件名的实际长度
#define REC_FILE_FILE_LENGTH	64

//产品ID 长度
#define TP_UMS_PRDUT_ID		64
//最大外设业务数量
#define UMS_MAX_SERVICE_NUM		32

#define UMS_AUDBAS_ENC_NUM		3

//////////////////////////////////////////////////////////////////////////
//视频格式定义
#define     VIDEO_FORMAT_INVALID            255
#define		VIDEO_FORMAT_SQCIF				1   //SQCIF(128*96)
#define		VIDEO_FORMAT_QCIF				2   //SCIF(176*144)
#define		VIDEO_FORMAT_CIF                3   //CIF(352*288)  - P制
#define     VIDEO_FORMAT_2CIF               4   //2CIF(352*576) - p
#define		VIDEO_FORMAT_4CIF               5   //4CIF(704*576) - P制(H264下此宏指代D1(720*576)   - P制（N制D1：720*480）)
#define		VIDEO_FORMAT_16CIF				6   //16CIF(1408*1152)
#define		VIDEO_FORMAT_AUTO				7   //自适应，仅用于MPEG4

#define		VIDEO_FORMAT_SIF                8   //SIF(352*240)  - N制
#define     VIDEO_FORMAT_2SIF               9   //2SIF
#define		VIDEO_FORMAT_4SIF               10  //4SIF(704*480) - N制

#define     VIDEO_FORMAT_VGA                11  //VGA(640*480)
#define		VIDEO_FORMAT_SVGA               12  //SVGA(800*600)
#define		VIDEO_FORMAT_XGA                13  //XGA(1024*768)
#define     VIDEO_FORMAT_WXGA               14  //WXGA(1280*768 | 1280*800)

//仅用于终端分辨率改变
#define		VIDEO_FORMAT_SQCIF_112x96       21  //SQCIF(112*96)
#define		VIDEO_FORMAT_SQCIF_96x80        22  //SQCIF(96*80)

// 高清分辨率
#define     VIDEO_FORMAT_W4CIF              31  //Wide 4CIF(1024*576)
#define     VIDEO_FORMAT_HD720              32  //720 1280*720
#define     VIDEO_FORMAT_SXGA               33  //SXGA 1280*1024
#define     VIDEO_FORMAT_UXGA               34  //UXGA 1600*1200
#define     VIDEO_FORMAT_HD1080             35  //1080  1920*1088(p) 1920*544(i)

//非标分辨率（1080p底图）－用于终端分辨率改变
#define     VIDEO_FORMAT_1440x816           41  //1440×816(3/4)
#define     VIDEO_FORMAT_1280x720           42  //1280×720(2/3)
#define     VIDEO_FORMAT_960x544            43  // 960×544(1/2)
#define     VIDEO_FORMAT_640x368            44  // 640×368(1/3)
#define     VIDEO_FORMAT_480x272            45  // 480×272(1/4)

//非标分辨率（720p底图） －用于终端分辨率改变
#define     VIDEO_FORMAT_720_960x544        51  //960×544(3/4)
#define     VIDEO_FORMAT_720_864x480        52  //864×480(2/3)
#define     VIDEO_FORMAT_720_640x368        53  //640×368(1/2)
#define     VIDEO_FORMAT_720_432x240        54  //432×240(1/3)
#define     VIDEO_FORMAT_720_320x192        55  //320×192(1/4)


#endif // _h_umsinnertype_h__
