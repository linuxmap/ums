#ifndef _MCUDEF_H_
#define _MCUDEF_H_
#include "kdvtype.h"
#include "tpsys.h"

#ifdef WIN32
#pragma pack( push )
#pragma pack( 1 )
#endif

#define		MAXLEN_EQP_ALIAS				16

//OS类型
#define     OS_TYPE_VXWORKS                 1   //Vx
#define     OS_TYPE_LINUX                   2   //Linux
#define     OS_TYPE_WIN32                   3   //Windows

//设备主类定义
#define		TYPE_MCU                     	 1   //MCU
#define		TYPE_MCUPERI                     2   //MCU外设
#define		TYPE_MT                          3   //终端

//单板类型 即结构体中的brdID
#define     BRD_TYPE_HDU2                   0x25
#define     BRD_TYPE_MPU2					0x26
#define     BRD_TYPE_MPU2ECARD				0x27
#define		BRD_TYPE_APU2					0x28

//外设模式
#define     TYPE_MPU2BAS_ENHANCED			17   //MPU2 Bas(Enhanced)能力模式
#define     TYPE_MPU2BAS_BASIC				18   //MPU2 Bas(Basic)能力模式
#define     TYPE_MPU2VMP_ENHANCED			19   //MPU2 VMP(Enhanced)能力模式
#define     TYPE_MPU2VMP_BASIC				20   //MPU2 VMP(Basic)能力模式

//外设子类型
#define     MPU2_VMP_BASIC					(u8)8	//MPU2 vmp-basic
#define		MPU2_VMP_ENHACED				(u8)9	//MPU2 vmp-enhanced
#define		TYPE_MPU2_ENHANCED				(u8)5	//MPU2-Enhanced
#define		TYPE_MPU2_BASIC					(u8)6	//MPU2-Basic

#define		MAXNUM_BRD_EQP					5    //单板上跑的最大外设数目
#define		MAXLEN_BRDALIAS					8	 //单板的名字

#define		MAXNUM_MAP						5	//单板最大map数

//设备子类定义---外设类型定义
#define		EQP_TYPE_MIXER					 1   //混音器
#define		EQP_TYPE_VMP                     2   //图像合成器
#define		EQP_TYPE_RECORDER                3   //录像机
#define		EQP_TYPE_BAS                     4   //码流适配器
#define		EQP_TYPE_TVWALL                  5   //电视墙
#define     EQP_TYPE_HDU2					 10	 //高清数字电视墙2代

//conf id len
#define     MAXLEN_CONFID                   16
#define     LOCAL_MCUID                     192					//本地MCU ID 
#define		LOCAL_MCUIDX					19200				//本地MCU IDX
#define		INVALID_MCUIDX					0xffff				//非法mcuidx号

#define     MAXLEN_KEY                      16   //最大的加密key长度

//会议加密方式定义
#define     CONF_ENCRYPTMODE_NONE            0 //不加密
#define     CONF_ENCRYPTMODE_DES             1 //des加密
#define     CONF_ENCRYPTMODE_AES             2 //aes加密
#define     CONF_ENCRYPTMODE_QT              3 //量子加密
#define		GETBBYTE(b)						((b)?1:0)

//消息长度相关
#define      SERV_MSG_LEN					0x7000  //消息长度
#define      SERV_MSGHEAD_LEN				0x30    //消息头长度

//画面合成参数相关
#define		MAXNUM_VMP_MEMBER				25  //画面合成最大数量
#define		MAXNUM_MPU2VMP_CHANNEL         (u8)9

//画面合成成员类型定义
#define		VMP_MEMBERTYPE_NULL				 0  //没有指定成员
#define		VMP_MEMBERTYPE_MCSSPEC           1  //会控指定 
#define		VMP_MEMBERTYPE_SPEAKER           2  //发言人跟随
#define		VMP_MEMBERTYPE_CHAIRMAN          3  //主席跟随
#define		VMP_MEMBERTYPE_POLL              4  //轮询视频跟随
#define		VMP_MEMBERTYPE_VAC               5	//语音激励(会控不要用此类型)
#define		VMP_MEMBERTYPE_VMPCHLPOLL        6  //vmp单通道轮询
#define		VMP_MEMBERTYPE_DSTREAM           7  //双流跟随


#define		TYPE_APU2_BAS					(u8)8	//APU2 BAS类型
#define		TYPE_8KI_VID_BAS				(u8)9   //8KI 视频BAS外设类型定义
#define		TYPE_8KI_AUD_BAS				(u8)10  //8KI 音频BAS外设类型定义

#define		MAXNUM_APU2_BASCHN					(u8)7		//apu2外设支持最大的输入通道数
#define		MAXNUM_8KI_AUD_BASCHN				(u8)4		//8kI aud bas外设支持最大的输入通道数

//画面合成风格默认RGB值
#define     VMPSTYLE_DEFCOLOR               (u32)(246|(246<<8)|(246<<16))// r|(g<<8)|(b<<16)
//画面合成最大方案个数
#define     MAX_VMPSTYLE_NUM                5
//HDU预案最大方案个数
#define   MAX_HDUSTYLE_NUM                  16
// 画面合成方案别名最大长度
#define  MAX_VMPSTYLE_ALIASLEN              32   
// 画面合成主题参数
// 字体
#define FONT_HEI    (u8)01 // 黑体
#define FONT_SONG   (u8)02 // 宋体 (默认)
#define FONT_KAI    (u8)03 // 楷体
// 字号
#define FONT_SIZE_24  24	// 24*24 (默认)
#define FONT_SIZE_32  32	// 32*32
// 对齐方式
#define LEFT_ALIGN    (u8)1  // 左
#define MIDDLE_ALIGN  (u8)2  // 中
#define RIGHT_ALIGN   (u8)3  // 右

// VMP空闲通道显示模式
// VMP空闲通道显示为黑色
#define VMP_SHOW_BLACK_MODE           0
// VMP空闲通道显示最后一帧
#define VMP_SHOW_LASTFRAME_MODE       1
// VMP空闲通道显示默认图片，480*272
#define VMP_SHOW_DEFPIC_MODE          2 
// VMP空闲通道显示用户自定义图片
#define VMP_SHOW_USERDEFPIC_MODE      3
// End

// 画面合成主题默认文字颜色
#define DEFAULT_TEXT_COLOR  (u32)(44|(94<<8)|(180<<16))  // blue
// 画面合成主题默认背景色
#define DEFAULT_BACKGROUND_COLOR (u32)(255|(255<<8)|(255<<16)) // white
// 画面合成主题默认透明度
#define DEFAULT_DIAPHANEITY   0 // 
// 画面合成主题默认文本长度
#define DEFAULT_TEXT_LEN     (u8)32 
// 画面合成主题默认高度
#define wDEFAULT_BMP_HEIGHT  (u16)50 
// BMP文件缓冲大小
#define  MAX_BMPFILE_SIZE   (u32)800*600  
// 最大BMP文件数据大小
#define  MAX_BMPDATA_BUFFER (u32)720*576  

//画面合成风格定义
#define		VMP_STYLE_DYNAMIC                0   //动态分屏(仅自动合成时有效)
#define		VMP_STYLE_ONE                    1   //一画面
#define		VMP_STYLE_VTWO                   2   //两画面：左右分 
#define		VMP_STYLE_HTWO                   3   //两画面: 一大一小
#define		VMP_STYLE_THREE                  4   //三画面
#define		VMP_STYLE_FOUR                   5   //四画面
#define		VMP_STYLE_SIX                    6   //六画面 
#define		VMP_STYLE_EIGHT                  7   //八画面
#define		VMP_STYLE_NINE                   8   //九画面
#define		VMP_STYLE_TEN                    9   //十画面
#define		VMP_STYLE_THIRTEEN               10  //十三画面
#define		VMP_STYLE_SIXTEEN                11  //十六画面
#define		VMP_STYLE_SPECFOUR               12  //特殊四画面 
#define		VMP_STYLE_SEVEN                  13  //七画面
#define		VMP_STYLE_TWENTY				 14  //二十画面
#define		VMP_STYLE_TEN_H  				 15  //水平分割的十画面(上2下8)
#define     VMP_STYLE_SIX_L2UP_S4DOWN        16  //特殊六画面(上2下4)  
#define     VMP_STYLE_FOURTEEN               17  //十四画面
#define     VMP_STYLE_TEN_M                  18  //十画面(上4中2下4)
#define     VMP_STYLE_THIRTEEN_M             19  //十三画面(一大在中间)
#define     VMP_STYLE_FIFTEEN                20  //十五画面
#define     VMP_STYLE_SIX_DIVIDE             21  //六画面(等分)
#define     VMP_STYLE_THREE_2BOTTOMRIGHT	 22  //三画面，2个小的在底部靠右
#define     VMP_STYLE_THREE_2BOTTOM2SIDE     23  //三画面，2个小的在底部两边
#define     VMP_STYLE_THREE_2BOTTOMLEFT      24  //三画面，2个小的在底部靠左
#define     VMP_STYLE_THREE_VERTICAL         25  //三画面，垂直等大
#define     VMP_STYLE_FOUR_3BOTTOMMIDDLE     26  //四画面，3个在底部中央
#define     VMP_STYLE_TWENTYFIVE			 27  //二十五画面

#define		VMPSTYLE_NUMBER					 (VMP_STYLE_TWENTYFIVE+1)
#define     VMP_STYLE_NONE                  0xff //不支持的格式

//适配板相关参数

//高清适配通道类型定义
#define     TYPE_MAU_NORMAL                 (u8)0   //普通MAU
#define     TYPE_MAU_H263PLUS               (u8)1   //为H263plus定制的MAU
#define     TYPE_MPU                        (u8)2   //MPU
#define     TYPE_8KE_BAS					(u8)3   //[03/01/2010] zjl add
#define     TYPE_MPU_H						(u8)4   //MPU_H
#define		TYPE_MPU2_ENHANCED				(u8)5	//MPU2-Enhanced
#define		TYPE_MPU2_BASIC					(u8)6	//MPU2-Basic
#define		TYPE_8KH_BAS					(u8)7	//[03/31/2011] nzj add

#define MAXNUM_MPU_CHN                      (u8)4
#define MAXNUM_MPU_H_CHN					(u8)2       //mpu_h最大输入通道数
#define MAXNUM_MPU2_BASIC_CHN               (u8)4		//mpu2 basic最大输入通道数
#define MAXNUM_MPU2_EHANCED_CHN				(u8)7       //mpu2 enhanced最大输入通道数

//三种通道类型
#define MPU2_BAS_CHN_MV						(u8)9       //HDBAS MPU2 主流通道
#define MPU2_BAS_CHN_DS						(u8)10      //HDBAS MPU2 双流通道
#define MPU2_BAS_CHN_SEL					(u8)11      //HDBAS MPU2 选看通道

#define     MAXNUM_BASOUTCHN				(u8)12	    //bas最大输出通道数

//电视墙相关参数
#define		MAXNUM_HDU_CHANNEL              2   //一个HDU的最大通道数
//HDU启动模式
#define STARTMODE_HDU_M						(u8)0      //hdu原有模式
#define STARTMODE_HDU_H						(u8)1      //hdu单通道模式
#define STARTMODE_HDU_L						(u8)2	   //hdu低能力模式
#define STARTMODE_HDU2						(u8)3	   //hdu2板外设
#define STARTMODE_HDU2_L					(u8)4	   //hdu2-L板外设
#define STARTMODE_HDU2_S					(u8)5	   //hdu2-S板外设, 可用作画面合成

#define DEVVER_HDU			(u16)4501
#define DEVVER_HDU2			(u16)4701
#define DEVVER_HDU2_L	    (u16)4702
#define DEVVER_HDU2_S	    (u16)4703 


#define HDUCHN_MODE_ONE						(u8)0   //一画面风格模式
#define HDUCHN_MODE_FOUR					(u8)1   //四画面风格模式						

//录播定义

// MCU前向纠错能力集类型
#define		FECTYPE_NONE					(u8)(0x00)
#define		FECTYPE_RAID5					(u8)(0x01)
#define		FECTYPE_RAID6					(u8)(0x02)

//上层视频帧率定义(用于非H.264，H.264直接用VIDEO_FPS_USRDEFINED+数值表示帧率)
#define     VIDEO_FPS_2997_1                1   //30 帧/s
#define     VIDEO_FPS_25                    2   //25 帧/s(底层按30帧处理)
#define     VIDEO_FPS_2997_2                3   //15 帧/s
#define     VIDEO_FPS_2997_3                4   //10 帧/s
#define     VIDEO_FPS_2997_4                5   //7.5帧/s
#define     VIDEO_FPS_2997_5                6   //6  帧/s
#define     VIDEO_FPS_2997_6                7   //5  帧/s
#define     VIDEO_FPS_2997_30               8   //1  帧/s
#define     VIDEO_FPS_2997_7P5              9   //4  帧/s
#define     VIDEO_FPS_2997_10               10  //3  帧/s
#define     VIDEO_FPS_2997_15               11  //2  帧/s
#define     VIDEO_FPS_USRDEFINED            128 //自定义帧率(>=128,减去128即为实际帧率)

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
#define     VIDEO_FORMAT_384x272            46  // 384×272(1/5)

//非标分辨率（720p底图） －用于终端分辨率改变
#define     VIDEO_FORMAT_720_960x544        51  //960×544(3/4)
#define     VIDEO_FORMAT_720_864x480        52  //864×480(2/3)
#define     VIDEO_FORMAT_720_640x368        53  //640×368(1/2)
#define     VIDEO_FORMAT_720_432x240        54  //432×240(1/3)
#define     VIDEO_FORMAT_720_320x192        55  //320×192(1/4)

//非标分辨率（1080p底图）－用于终端分辨率改变
#define		VIDEO_FORMAT_640x544			56	//640x544
#define		VIDEO_FORMAT_320x272			57	//320x272

//////////////////////////////////////////////////////////////////////////
//结构体定义

/* 单板身份结构定义 */
typedef struct tTagBrdPos 
{
    u8 byBrdID;                      /* 板子ID号 */
    u8 byBrdLayer;                   /* 板子所在层号，设备不支持时返回0，当作0层处理 */
    u8 byBrdSlot;                    /* 板子所在槽位号，设备不支持时返回0，当作0槽处理;
									 部分设备有主从之分，用slot来区分：0=主；1=从 */
}TBrdPos;

struct TBrdRegAck
{
private:
	u32 dwMpcIpAddrOther;
	u16 wMpcPortOther;
public:
	void SetOtherMpcIp(u32 dwMpcIp) { dwMpcIpAddrOther = htonl(dwMpcIp); }
	u32  GetOtherMpcIp(void) const { return ntohl(dwMpcIpAddrOther); }
	void SetOtherMpcPort(u16 wMpcPort) { wMpcPortOther = htons(wMpcPort); }
	u16  GetOtherMpcPort(void) const { return ntohs(wMpcPortOther); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMpuEBapEVpuConfigAck
{
private:
	u8   m_byEqpType;
	u8   m_byEqpId;
    u8   m_byEqpId2;
    u16  m_wEqpRcvStartPort;
    u16  m_wEqpRcvStartPort2;
    s8 m_achAlias[MAXLEN_EQP_ALIAS+1]; // zw 20090309 暂时没有用到
public:
	void SetEqpType( u8 byEqpType ) { m_byEqpType = byEqpType; }
	u8   GetEqpType( void ) const { return m_byEqpType; }
	void SetEqpId( u8 byEqpId) { m_byEqpId = byEqpId; }
	u8   GetEqpId( void ) const { return m_byEqpId; }
    void SetEqpId2( u8 byEqpId) { m_byEqpId2 = byEqpId; }
	u8   GetEqpId2( void ) const { return m_byEqpId2; }
    void SetEqpRcvStartPort( u16 wEqpRcvStartPort) { m_wEqpRcvStartPort = htons(wEqpRcvStartPort); }
	u16  GetEqpRcvStartPort( void ) const { return ntohs(m_wEqpRcvStartPort); }
    void SetEqpRcvStartPort2( u16 wEqpRcvStartPort) { m_wEqpRcvStartPort2 = htons(wEqpRcvStartPort); }
	u16  GetEqpRcvStartPort2( void ) const { return ntohs(m_wEqpRcvStartPort2); }
    void SetAlias( LPCSTR lpszAlias )
    {
        if ( NULL != lpszAlias )
        {
            strncpy( m_achAlias, lpszAlias, sizeof(m_achAlias) );
            m_achAlias[sizeof(m_achAlias)-1] = '\0';
        }
    }
    LPCSTR GetAlias( void ) { return m_achAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//会议号结构 (len:16)
struct CConfId
{
protected:
	u8  	m_abyConfId[MAXLEN_CONFID];
	
public:
	u8   GetConfId( u8   * pbyConfId, u8   byBufLen ) const; //获得会议号数组
	void CreateConfId( u8 byUsrGrpId );                               //创建会议号
	void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const;//获得会议号字符串
	void SetConfId( const CConfId & cConfId );                  //设置会议号
	u8   SetConfId( const u8   * pbyConfId, u8   byBufLen );          //设置会议号数组
	u8   SetConfId( LPCSTR lpszConfId );                          //设置会议号数组	
	BOOL IsNull( void ) const;                                  //判断会议号是否为空
	void SetNull( void );                                       //设置会议号为空
	BOOL operator == ( const CConfId & cConfId ) const;         //操作符重载
    // 顾振华，在CConfId中内置用户组的信息
    u8   GetUsrGrpId() const 
    {
        return m_abyConfId[MAXLEN_CONFID-1];
    }
    void SetUsrGrpId(u8 byGrpId)
    {
        m_abyConfId[MAXLEN_CONFID-1] = byGrpId;
    }
	
	//fuxiuhua,增加会议发起方信息
	//会议ID的组成：MCU号(2Byte)/会议类型(1Byte)/会议索引值(1Byte)/会议号产生次数(4Byte)/
	//              未用(6Byte)/发起方类型(1Byte)/组号(1Byte)
	void SetConfSource( u8 byConfSource )
	{
		m_abyConfId[MAXLEN_CONFID - 2] = byConfSource;
	}
	u8   GetConfSource()
	{
		return m_abyConfId[MAXLEN_CONFID - 2];
	}
	
	void Print( void ) const
	{
// 		s8 achBuf[MAXLEN_CONFID*2+1];
// 		memset(achBuf, 0, sizeof(achBuf));
// 		GetConfIdString( achBuf, sizeof(achBuf) );
// 		StaticLog("%s\n", achBuf);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//业务消息类，最大处理28K长度消息
class CServMsg
{
protected:
	u16     m_wSerialNO;            //流水号
	u8      m_bySrcDriId;           //源DRI板号
	u8      m_bySrcMtId;            //源终端号
	u8      m_bySrcSsnId;           //源会话号
	u8      m_byDstDriId;           //目的DRI板号
    u8      m_byDstMtId;            //目的终端号
	u8      m_byMcuId;              //MCU号
	u8      m_byChnIndex;           //通道索引号
    u8      m_byConfIdx;            //会议索引号
	CConfId m_cConfId;              //会议号
	u16		m_wEventId;             //事件号
	u16		m_wTimer;               //定时
	u16		m_wErrorCode;           //错误码
	u16		m_wMsgBodyLen;          //消息体长度
    u8      m_byTotalPktNum;        //总包数（用于需要切包发送的消息）
    u8      m_byCurPktIdx;          //当前包索引（从0开始）
	u8      m_abyReserverd[12];     //保留字节
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //消息体
public:
	void  SetSerialNO(u16  wSerialNO){ m_wSerialNO = htons(wSerialNO);} 
    u16   GetSerialNO( void ) const { return ntohs(m_wSerialNO); }
    void  SetSrcDriId(u8   bySrcDriId){ m_bySrcDriId = bySrcDriId;} 
    u8    GetSrcDriId( void ) const { return m_bySrcDriId; }
    void  SetSrcMtId(u8   bySrcMtId){ m_bySrcMtId = bySrcMtId;} 
    u8    GetSrcMtId( void ) const { return m_bySrcMtId; }
    void  SetSrcSsnId(u8   bySrcSsnId){ m_bySrcSsnId = bySrcSsnId;} 
    u8    GetSrcSsnId( void ) const { return m_bySrcSsnId; }
    void  SetDstDriId(u8   byDstDriId){ m_byDstDriId = byDstDriId;} 
    u8    GetDstDriId( void ) const { return m_byDstDriId; }  
    void  SetDstMtId(u8   byDstMtId){ m_byDstMtId = byDstMtId;} 
    u8    GetDstMtId( void ) const { return m_byDstMtId; }
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId;} 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetChnIndex(u8   byChnIndex){ m_byChnIndex = byChnIndex;} 
    u8    GetChnIndex( void ) const { return m_byChnIndex; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx;} 
    u8    GetConfIdx( void ) const { return m_byConfIdx; } 
    void  SetEventId(u16  wEventId){ m_wEventId = htons(wEventId);} 
    u16   GetEventId( void ) const { return ntohs(m_wEventId); }
    void  SetTimer(u16  wTimer){ m_wTimer = htons(wTimer);} 
    u16   GetTimer( void ) const { return ntohs(m_wTimer); }
    void  SetErrorCode(u16  wErrorCode){ m_wErrorCode = htons(wErrorCode);} 
    u16   GetErrorCode( void ) const { return ntohs(m_wErrorCode); }
    void  SetTotalPktNum(u8 byPktNum) { m_byTotalPktNum = byPktNum; }
    u8    GetTotalPktNum( void ) { return m_byTotalPktNum; }
    void  SetCurPktIdx(u8 byPktIdx) { m_byCurPktIdx = byPktIdx; }
    u8    GetCurPktIdx( void ) { return m_byCurPktIdx; }
	
	void Init( void );
	void SetNoSrc(){ SetSrcSsnId( 0 ); }
	void SetMsgBodyLen( u16  wMsgBodyLen );
	CServMsg( void );//constructor
	CServMsg( u8   * const pbyMsg, u16  wMsgLen );//constructor
	~CServMsg( void );//distructor
	void ClearHdr( void );//消息头清零
	CConfId GetConfId( void ) const;//获取会议号信息
	void SetConfId( const CConfId & cConfId );//设置会议号信息
	void SetNullConfId( void );//设置会议号信息为空
	u16  GetMsgBodyLen( void ) const;//获取消息体长度信息
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//获取消息体，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetMsgBody( void ) const;//获取消息体指针，用户不需提供BUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//设置消息体
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//添加消息体
	u16  GetServMsgLen( void ) const;//获取整个消息长度
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//获取整个消息，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetServMsg( void ) const;//获取整个消息指针，用户不需提供BUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//设置整个消息
	const CServMsg & operator= ( const CServMsg & cServMsg );//操作符重载
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 要赋值的消息指针
				  u16 wMsgLen, 要赋值的消息长度，必须大于等于 SERV_MSGHEAD_LEN
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::CServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	Init();
	
	if( wMsgLen < SERV_MSGHEAD_LEN || pbyMsg == NULL )
		return;
	
	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	
	//set length
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：~CServMsg
    功能        ：distructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    函数名      ：Init
    功能        ：BUFFER初始化
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//清零
}

/*====================================================================
    函数名      ：ClearHdr
    功能        ：消息头清零
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//清零
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    函数名      ：GetConfId
    功能        ：获取会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议号，全0表示创建
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline CConfId CServMsg::GetConfId( void ) const
{
	return( m_cConfId );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId，会议号，全0表示创建
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline void CServMsg::SetConfId( const CConfId & cConfId )
{
	m_cConfId = cConfId;
}

/*====================================================================
    函数名      ：SetNullConfId
    功能        ：设置会议号信息为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CConfId		cConfId;
	
	cConfId.SetNull();
	SetConfId( cConfId );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    函数名      ：SetMsgBodyLen
    功能        ：设置消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 wMsgBodyLen, 消息体长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取整个消息长度
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：整个消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBodyBuf, 返回的消息体
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    函数名      ：SetMsgBody
    功能        ：设置消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        SetMsgBodyLen( 0 );
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN );
	memcpy( m_abyMsgBody, pbyMsgBody, wLen );
	SetMsgBodyLen( wLen );
}

/*====================================================================
    函数名      ：CatMsgBody
    功能        ：添加消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/11/07    1.0         Liaoweijiang  创建
====================================================================*/
inline void CServMsg::CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN - GetMsgBodyLen() );
	memcpy( m_abyMsgBody + GetMsgBodyLen(), pbyMsgBody, wLen );
	SetMsgBodyLen( GetMsgBodyLen() + wLen );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取整个消息指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    函数名      ：GetServMsg
    功能        ：获取整个消息，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBuf, 返回的消息
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    函数名      ：SetServMsg
    功能        ：设置整个消息
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 传入的整个消息
				  u16 wMsgLen, 传入的消息长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	if( wMsgLen < SERV_MSGHEAD_LEN )
	{
		OspPrintf( TRUE, FALSE, "CServMsg: SetServMsg() Exception -- invalid MsgLen!\n" );
		return;
	}

	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：operator=
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：CServMsg & cServMsg, 赋值的消息引用
    返回值说明  ：CServMsg对象应用
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline const CServMsg & CServMsg::operator= ( const CServMsg & cServMsg )
{
	u16	wLen = cServMsg.GetServMsgLen();

	memcpy( this, cServMsg.GetServMsg(), wLen );
	return( *this );
}

/*-------------------------------------------------------------------
                               CConfId                                  
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：GetConfId
    功能        ：获得会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyConfId, 传入的BUFFER数组指针，用来返回会议号
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际返回数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::GetConfId( u8 * pbyConfId, u8 byBufLen ) const
{
	u8	byLen = min( sizeof( m_abyConfId ), byBufLen );
	memcpy( pbyConfId, m_abyConfId, byLen );

	return( byLen );
}

/*====================================================================
    函数名      ：GetConfIdString
    功能        ：获得会议号字符串
    算法实现    ：
    引用全局变量：
    输入参数说明：LPSTR lpszConfId, 传入的字符串BUFFER数组指针，用来
	                   返回0结尾会议号字符串
			      u8 byBufLen, BUFFER大小
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::GetConfIdString( LPSTR lpszConfId, u8 byBufLen ) const
{
	u8	byLoop;

	for( byLoop = 0; byLoop < sizeof( m_abyConfId ) && byLoop < ( byBufLen - 1 ) / 2; byLoop++ )
	{
		sprintf( lpszConfId + byLoop * 2, "%.2x", m_abyConfId[byLoop] );
	}
	lpszConfId[byLoop * 2] = '\0';
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId, 输入会议号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::SetConfId( const CConfId & cConfId )
{
	cConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const u8 * pbyConfId, 传入的数组指针
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::SetConfId( const u8 * pbyConfId, u8 byBufLen )
{
	u8	bySize = min( byBufLen, sizeof( m_abyConfId ) );
	
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	memcpy( m_abyConfId, pbyConfId, bySize );

	return( bySize );
}
	
/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfId, 传入的会议号字符串
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::SetConfId( LPCSTR lpszConfId )
{
	LPCSTR	lpszTemp = lpszConfId;
	s8	achTemp[3], *lpszStop;
	u8	byCount = 0;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	while( lpszTemp != NULL && lpszTemp + 1 != NULL && byCount < sizeof( m_abyConfId ) )
	{
		memcpy( achTemp, lpszTemp, 2 );
		achTemp[2] = '\0';
		m_abyConfId[byCount] = ( u8 )strtoul( achTemp, &lpszStop, 16 );
		byCount++;
		lpszTemp += 2;
	}

	return( byCount );
}

/*====================================================================
    函数名      ：CreateConfId
    功能        ：创建会议号
    算法实现    ：根据当前时间和随机值
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::CreateConfId( u8 byUsrGrpId )
{
	struct tm	*ptmCurTime;
	time_t		tCurTime = time( NULL );
	u8	byTemp;
	u16	wTemp;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	
	//get current time
	ptmCurTime = localtime( &tCurTime );
	//year
	wTemp = ptmCurTime->tm_year + 1900;
	memcpy( m_abyConfId, &wTemp, sizeof( u16 ) );
	//month
	byTemp = ptmCurTime->tm_mon + 1;
	memcpy( m_abyConfId + 2, &byTemp, sizeof( u8 ) );
	//day
	byTemp = ptmCurTime->tm_mday;
	memcpy( m_abyConfId + 3, &byTemp, sizeof( u8 ) );
	//hour
	byTemp = ptmCurTime->tm_hour;
	memcpy( m_abyConfId + 4, &byTemp, sizeof( u8 ) );
	//minute
	byTemp = ptmCurTime->tm_min;
	memcpy( m_abyConfId + 5, &byTemp, sizeof( u8 ) );
	//second
	byTemp = ptmCurTime->tm_sec;
	memcpy( m_abyConfId + 6, &byTemp, sizeof( u8 ) );
	//msec
	wTemp = 0;
	memcpy( m_abyConfId + 7, &wTemp, sizeof( u16 ) );

	//rand
	wTemp = rand();
	memcpy( m_abyConfId + 9, &wTemp, sizeof( u16 ) );

    // 顾振华 [6/21/2006]
    // 最低位表示组ID
    SetUsrGrpId( byUsrGrpId );
}

/*====================================================================
    函数名      ：IsNull
    功能        ：判断会议号是否为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
====================================================================*/
inline BOOL CConfId::IsNull( void ) const
{
	u8	abyNull[sizeof( m_abyConfId )];

	memset( abyNull, 0, sizeof( abyNull ) );
	if( memcmp( m_abyConfId, abyNull, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

/*====================================================================
    函数名      ：SetNull
    功能        ：设置会议号为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::SetNull( void )
{
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：operator==
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId, 输入会议号
    返回值说明  ：相等返回TRUE，否则返回FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline BOOL CConfId::operator == ( const CConfId & cConfId ) const
{
	u8	abyTemp[sizeof( m_abyConfId )];

	cConfId.GetConfId( abyTemp, sizeof( abyTemp ) );
	if( memcmp( abyTemp, m_abyConfId, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

struct TMt;
//定义简化MCU、终端或外设结构 (len:6)
struct TMtNoConstruct
{
protected:
    u8          m_byMainType;   //设备主类
    u8  		m_bySubType;	//设备子类
	u8  		m_byMcuId;		//MCU号
	u8  		m_byEqpId;	    //设备号	
	u8          m_byConfDriId;  //DRI板号
    u8          m_byConfIdx;    //会议索引号，即会议实例号 1 - MAXNUM_MCU_CONF

public:
	// 设置结构主类
	void   SetType( u8   byType )
	{ 
		m_byMainType = ( (m_byMainType & 0xf0) | (byType & 0xf) ) ; 
	}         

	// 得到结构主类
	u8     GetType( void ) const { return m_byMainType & 0xf; }     
	
	// fxh 与GetMcuId匹配操作，对于原u8同样兼容
	void   SetMcuId( u16  wMcuId )	{ SetMcuIdx(wMcuId); } 
    
	// 得到McuId
	u16     GetMcuId( void ) const { return GetMcuIdx(); }

	// 判断TMtNoConstruct与TMtNoConstruct是否相等
	BOOL   operator ==( const TMtNoConstruct & tObj ) const;    

	//操作MCU函数
	//设置MCU
	void   SetMcu( u16   wMcuIdx );                         
	void   SetMcuType( u8  byMcuType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCU); 
		m_bySubType = ((m_byMainType & 0xf0)| (byMcuType&0xf) ); 
	}

	u8     GetMcuType( void ) const { return m_bySubType & 0xf; }

	// 操作外设函数
	// 设置MCU外设
	void   SetMcuEqp( u8   byMcuId, u8   byEqpId, u8   byEqpType );  
	
	// 设置MCU外设类型
	void   SetEqpType( u8   byEqpType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCUPERI); 
		m_bySubType = ((m_byMainType & 0xf0)| (byEqpType&0xf) ); 		
	}  
	
	u8     GetEqpType( void ) const { return m_bySubType & 0xf; }
	
	void   SetEqpId( u8   byEqpId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCUPERI);
		m_byEqpId = byEqpId; 
	}

	u8     GetEqpId( void ) const { return m_byEqpId; }
	
	//操作终端函数
	void   SetMt( u16   wMcuIdx, u8   byMtId, u8   m_byDriId = 0, u8   m_byConfIdx = 0);
	void   SetMt( TMt tMt);
	void   SetMtId( u8   byMtId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);	
		m_byEqpId = byMtId; 
	}
	u8     GetMtId( void ) const { return m_byEqpId; }//设置终端
	void   SetMtType( u8   byMtType ) 
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);		
		m_bySubType = ( (m_bySubType & 0xf0 ) | ( byMtType & 0xf ) );
	}
	u8     GetMtType( void ) const { return m_bySubType & 0xf; }  	
    void   SetDriId(u8   byDriId){ m_byConfDriId = byDriId; }
    u8     GetDriId( void ) const { return m_byConfDriId; }
    void   SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx; } 
    u8     GetConfIdx( void ) const { return m_byConfIdx; }
	void   SetNull( void ){ 
		m_byMainType = m_bySubType = m_byMcuId = m_byEqpId = m_byConfDriId = 0;
		SetMcuIdx( INVALID_MCUIDX );
	}
	BOOL   IsNull ( void ) const{ return ( TYPE_MCU != GetType() && m_byEqpId == 0 ) || GetMcuIdx() == INVALID_MCUIDX; }
	BOOL   IsMcuIdLocal() const {	return (m_byMcuId == LOCAL_MCUID );	}

	// 将LOCAL_MCUIDX改为LOCAL_MCUID
	BOOL   IsLocal() const 
	{
		// [11/9/2010 liuxu] 外设都是本级得，直接返回TRUE
		if (TYPE_MCUPERI == GetType())
		{
			return TRUE;
		}
		
		return (GetMcuIdx() == LOCAL_MCUIDX );		
	}

//[0901]fxh对于mcuidx是由完备mcu标识进行本地化构成本地mcuid，该实现细节进行封装，过渡阶段，以下两个接口禁止对象调用，之后会将其私有化
// private:
	u16	   GetMcuIdx() const {
		return ( (( m_byMainType & 0xf0 ) << 8 ) 
			+ (( m_bySubType & 0xf0) << 4 ) 
			+ m_byMcuId );
	}

	void   SetMcuIdx( u16 wMcuIdx ){ 
		m_byMainType = m_byMainType & 0x0f;
		m_bySubType = m_bySubType & 0x0f;

		m_byMainType |= ( ( wMcuIdx >> 8 ) & 0xf0 );
		m_bySubType |= ( ( wMcuIdx & 0xf00 ) >> 4 );
		m_byMcuId = (wMcuIdx & 0xff);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//定义简化MCU、终端或外设结构 (len:6)
struct TMt : public TMtNoConstruct
{
	// [5/25/2011 liuxu] Tmt和TMtNoConstruct采取两套结构,内容基本一致, 维护不方便,
	// 也存在很大的冗余. 于是在这里进行整理. TMtNoConstruct暂时不能被废除,原因(源自zjj):
	// 我们的代码中用到了很多联合体结构,但是联合体中成员不能有构造函数,但Tmt存在构造函数
	// 所以我们需要不带构造函数的TMtNoConstruct.
	
public:
	// 构造函数
	TMt()
	{
		memset( this,0,sizeof(TMt) );
		SetMcuIdx( INVALID_MCUIDX );
	}
	
	// 构造函数
	TMt( const TMtNoConstruct& tOther )
	{
		memcpy( this, &tOther, sizeof(TMtNoConstruct) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//定义终端结构
typedef TMt TEqp;
typedef TMtNoConstruct TEqpNoConstruct;
//外设注册请求消息类
struct TPeriEqpRegReq : public TEqp
{
protected:
	u32   		m_dwIpAddr;		//外设IP地址
	u16 		m_wStartPort;	//外设起始接收端口
	u8  		m_byChannlNum;	//外设接收信道数
	s8          m_achAlias[MAXLEN_EQP_ALIAS];
    //4.0R3扩展字段
    u16         m_wVersion;     //版本信息
    //4.5高清扩展字段
    BOOL        m_bHDEqp;       //是否高清外设
	
public:
    TPeriEqpRegReq(void) { memset(this, 0, sizeof(TPeriEqpRegReq)); }
    //设置外设IP地址
    //输入：IP地址(网络序)
	void SetPeriEqpIpAddr( const u32    &dwIpAddr )	{ m_dwIpAddr = dwIpAddr; }
    //获得外设IP地址
    //返回值：IP地址(网络序)
	u32    GetPeriEqpIpAddr() const	{ return m_dwIpAddr; }
	//设置外设接收起始端口
	void SetStartPort( const u16  & wStartPort )	{ m_wStartPort = htons(wStartPort); }
	//获得外设接收起始端口
	u16  GetStartPort() const	{ return ntohs( m_wStartPort ); }
	//设置外设接收信道数目
	void SetChnnlNum( const u8   & byChannlNum )	{ m_byChannlNum = byChannlNum; }
	//获得外设接收信道数目
	u8   GetChnnlNum() const	{ return m_byChannlNum; }
	
	void SetEqpAlias(char* szAlias)
	{
		strncpy( m_achAlias ,szAlias ,sizeof(m_achAlias) );
		m_achAlias[MAXLEN_EQP_ALIAS-1] ='\0';
	}
	
	LPCSTR GetEqpAlias()
	{
		return m_achAlias;
	}
	
    void SetVersion(u16 wVersion)
    {
        m_wVersion = htons(wVersion);
    }
    u16 GetVersion() const
    {
        return ntohs(m_wVersion);
    }
    void SetHDEqp(BOOL bHD)
    {
        m_bHDEqp = bHD;
    }
	
    BOOL IsHDEqp() const
    {
        return m_bHDEqp;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//定义外设登记成功信息结构
struct TPeriEqpRegAck
{
protected:
	u32   		m_dwIpAddr;			//MCU接收地址
	u16 		m_wStartPort;		//MCU接收起始端口号
    u32         m_dwAnotherMpcIp;   //主备时：另外一块mpc板地址（用来对外设配置的备板mpc地址进行校验）
	u32         m_dwMsSSrc;         //主备时：用于标注一次系统运行，只要该值变化就说明发生过主备同时重启
	
public:
	//得到上级MCU交换接收数据IP地址
    u32    GetMcuIpAddr( void ) const { return ntohl(m_dwIpAddr); }
	
	//设置上级MCU交换接收数据IP地址
    void SetMcuIpAddr( u32    dwIpAddr ) { m_dwIpAddr = htonl(dwIpAddr); }
	
	//得到上级MCU交换接收数据端口号
    u16  GetMcuStartPort( void ) const { return ntohs(m_wStartPort); }
	
    //设置上级MCU交换接收数据端口号
    void SetMcuStartPort( u16  wPort ) { m_wStartPort = htons(wPort); }
	
    //另外一块mpc板地址
    u32  GetAnotherMpcIp( void ) const { return ntohl(m_dwAnotherMpcIp); }
    void SetAnotherMpcIp( u32 dwIpAddr ) { m_dwAnotherMpcIp = htonl(dwIpAddr); }
	
	void SetMSSsrc(u32 dwSSrc)
    {
        m_dwMsSSrc = htonl(dwSSrc);
    }
    u32 GetMSSsrc(void) const
    {
        return ntohl(m_dwMsSSrc);
    }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//重传时间跨度结构 (len:16)
struct TPrsTimeSpan
{
    TPrsTimeSpan()
    {
        memset(this, 0, sizeof(TPrsTimeSpan));
    }
    u16  m_wFirstTimeSpan;	  //第一个重传检测点
	u16  m_wSecondTimeSpan;   //第二个重传检测点
	u16  m_wThirdTimeSpan;    //第三个重传检测点
	u16  m_wRejectTimeSpan;   //过期丢弃的时间跨度
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设配置基类
struct TEqpCfgInfo
{
protected:    
    s8  m_szAlias[MAXLEN_EQP_ALIAS];		//别名
    u16 m_wMcuStartPort;					//mcu接收起始端口号
    u16 m_wEqpStartPort;					//外设接收起始端口号    
    u8  m_byEqpId;							//设备ID
    u8  m_bySwitchBrdIndex;					//交换板索引     
    u8  m_byRunningBrdIndex;				//运行板索引
    u8  m_byMapCount;						//使用的MAP个数
    u8  m_abyMapId[MAXNUM_MAP];				//Map编号数组
	
public:
    TEqpCfgInfo(void) { memset(this, 0, sizeof(TEqpCfgInfo)); }
	
    void    SetEqpId(u8 byEqpId) { m_byEqpId = byEqpId; }
    u8      GetEqpId(void) { return m_byEqpId; }
    void    SetMcuStartPort(u16 wPort) { m_wMcuStartPort = htons(wPort); }
    u16     GetMcuStartPort(void)   { return ntohs(m_wMcuStartPort); } 
    void    SetEqpStartPort(u16 wPort) { m_wEqpStartPort = htons(wPort); }
    u16     GetEqpStartPort(void) { return ntohs(m_wEqpStartPort); }
    void    SetSwitchBrdIndex(u8 byIndex) { m_bySwitchBrdIndex = byIndex; }
    u8      GetSwitchBrdIndex(void) { return m_bySwitchBrdIndex; }
    void    SetRunningBrdIndex(u8 byIndex) { m_byRunningBrdIndex = byIndex; }
    u8      GetRunningBrdIndex(void)    { return m_byRunningBrdIndex; }
	
    //下列方法仅供子类高清MAU特殊处理用
protected:
    void    SetMapCount(u8 byCount) { m_byMapCount = byCount; }
    u8      GetMapCount(void) const { return m_byMapCount; }
	
public:
    void    SetAlias(LPCSTR lpszAlias)
    {
        if(NULL != lpszAlias)
        {
            strncpy(m_szAlias, lpszAlias, sizeof(m_szAlias));
            m_szAlias[sizeof(m_szAlias) - 1] = '\0';
        }        
    }
    const s8* GetAlias(void) { return m_szAlias; }
	
    BOOL32    SetMapId(u8 *pbyMapId, u8 byCount)
    {
        if(NULL == pbyMapId || byCount > MAXNUM_MAP)
            return FALSE;
        
        memcpy(m_abyMapId, pbyMapId, byCount);
        m_byMapCount = byCount;
        return TRUE;
    }
    BOOL32     GetMapId(u8 *pbyMapId, u8 &byCount)
    {
        if(NULL == pbyMapId)
            return FALSE;
        
        memcpy(pbyMapId, m_abyMapId, m_byMapCount);
        byCount = m_byMapCount;
        return TRUE;
    }
	
    void PrintMap(void)
    {
//        StaticLog( "MapCount: %d, MapId: %d,%d,%d,%d,%d\n", 
 //           m_byMapCount, m_abyMapId[0], m_abyMapId[1], m_abyMapId[2], m_abyMapId[3], m_abyMapId[4]);
        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#define HDU_VOLUME_DEFAULT (u8)24

//设置hdu音量结构体  范围 0 -- 31
struct THduVolumeInfo:public TEqp
{
protected:
	u8  m_byChnlIdx;    // 通道索引号
	u8  m_byVolume;     // 音量大小
	u8  m_byIsMute;  // 是否静音  
	u8  m_byReserved[5];
	
public:
    THduVolumeInfo()
	{
        memset(this, 0x0, sizeof(THduVolumeInfo));
		m_byVolume = HDU_VOLUME_DEFAULT;
	}
	
	u8   GetChnlIdx( void ){ return m_byChnlIdx; }
	void SetChnlIdx( u8 byChnlIdx ){ m_byChnlIdx = byChnlIdx; }
	
	u8   GetVolume( void ){ return m_byVolume; }
	void SetVolume( u8 byVolume ){ m_byVolume = byVolume; }
	
	BOOL32   GetIsMute( void ){ return m_byIsMute; }
	void SetIsMute( BOOL32 byIsMute ){ m_byIsMute = GETBBYTE(byIsMute); }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct THduChnlModePort
{
public:
	THduChnlModePort()
	{
		memset(this, 0x0, sizeof(THduChnlModePort));
	}
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }

    u8 GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8 GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }
	
	u8 GetScalingMode() const { return (reserved & 0x03);}
	void SetScalingMode(u8 byMode) { reserved = (reserved | 0x03) & (byMode | 0xFC); }

private:
    u8 byOutPortType;
    u8 byOutModeType;
    u8 byZoomRate;
	// 1)该字段低2位已使用，用于标识ScalingMode [11/29/2011 chendaiwei]
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 


//定义传输地址结构(len:6)
struct TTransportAddr
{
public:
	u32   		m_dwIpAddr;		//IP地址, 网络序
	u16 		m_wPort;		//端口号, 网络序
public:
	void   SetNull(void)
	{
		m_dwIpAddr = 0;
		m_wPort = 0;
	}
	
	// [6/2/2011 liuxu] 添加判断
	BOOL32 IsNull()
	{
		return GetIpAddr() == 0 || GetIpAddr() == ~0 || GetPort() == 0;
	}
	
    void   SetNetSeqIpAddr(u32    dwIpAddr){ m_dwIpAddr = dwIpAddr; } 
    u32    GetNetSeqIpAddr( void ) const { return m_dwIpAddr; }
    void   SetIpAddr(u32    dwIpAddr){ m_dwIpAddr = htonl(dwIpAddr); } 
    u32    GetIpAddr( void ) const { return ntohl(m_dwIpAddr); }
    void   SetPort(u16  wPort){ m_wPort = htons(wPort); } 
    u16    GetPort( void ) const { return ntohs(m_wPort); }
	BOOL32 operator == (const TTransportAddr &tTransportAddr)
	{
		return m_dwIpAddr == tTransportAddr.GetIpAddr() && m_wPort == tTransportAddr.GetPort() ;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//(len:22)
struct TMediaEncrypt
{
protected:
	u8  m_byEncryptMode;         //加密模式 : CONF_ENCRYPTMODE_NONE,CONF_ENCRYPTMODE_DES, CONF_ENCRYPT_AES
    s32 m_nKeyLen;               //加密key的长度
	u8  m_abyEncKey[MAXLEN_KEY]; //加密key
	u8  m_byReserve;             //保留
public:
	TMediaEncrypt()
	{
		Reset();
	}
	void Reset()
	{
        memset( &m_abyEncKey, 0, MAXLEN_KEY );
		m_byEncryptMode = CONF_ENCRYPTMODE_NONE;
		m_nKeyLen = 0;
	}
	
	void SetEncryptMode(u8 byEncMode)
	{
		m_byEncryptMode = byEncMode;
	}
    u8  GetEncryptMode()
	{
		return m_byEncryptMode;
	}
	void SetEncryptKey(u8 *pbyKey, s32 nLen)
	{
		m_nKeyLen = (nLen > MAXLEN_KEY ? MAXLEN_KEY : nLen);
		if(m_nKeyLen > 0)
			memcpy(m_abyEncKey, pbyKey, m_nKeyLen); 
		m_nKeyLen = htonl(m_nKeyLen);
	}
	
	void GetEncryptKey(u8 *pbyKey, s32* pnLen)
	{
		if(pnLen != NULL) *pnLen = ntohl(m_nKeyLen);
		if(pbyKey != NULL) memcpy(pbyKey, m_abyEncKey, ntohl(m_nKeyLen));
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTvWallStartPlay
{
protected:
    TMt m_tMt;
    TTransportAddr m_tVidRtcpBackAddr; //视频RTCP回馈地址
//	TTransportAddr m_tAudRtcpBackAddr; //音频Rtcp回馈地址
    u8  m_byNeedPrs;
    TMediaEncrypt m_tVideoEncrypt;
	
public:
    TTvWallStartPlay(void)
    {
        Reset();
    }
	
    void Reset(void)
    {
		m_byNeedPrs = 0;
		m_tVidRtcpBackAddr.SetNull();
//		m_tAudRtcpBackAddr.SetNull();
        m_tMt.SetNull();
        m_tVideoEncrypt.Reset();
    }
	
    void SetMt(const TMt &tMt)
    {
        m_tMt  = tMt;
    }
	
    TMt& GetMt(void)
    {
        return m_tMt;
    }
	
    TMediaEncrypt& GetVideoEncrypt(void)
    {
        return m_tVideoEncrypt;
    }
	
    void SetVideoEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tVideoEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }
	
    void SetIsNeedByPrs(BOOL bNeedPrs)
    {
        m_byNeedPrs = bNeedPrs==TRUE?1:0;
    }
	
    BOOL IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }
	
	//[liu lijiu][20100919]增加RTCP回馈地址
	//设置视频的RTCP回馈地址
	void SetVidRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
    {
        m_tVidRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
        m_tVidRtcpBackAddr.SetPort(wRtcpBackPort);
		return;
    }
	
	//获取视频的RTCP回馈地址
    void GetVidRtcpBackAddr(u32 & dwRtcpBackIp, u16 & wRtcpBackPort)
    {
        dwRtcpBackIp = m_tVidRtcpBackAddr.GetIpAddr();
        wRtcpBackPort = m_tVidRtcpBackAddr.GetPort();
        return;
    }
	
	//设置音频的RTCP回馈地址
// 	void SetAudRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
//     {
//         m_tAudRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
//         m_tAudRtcpBackAddr.SetPort(wRtcpBackPort);
// 		return;
//     }
// 	
// 	//获取音频的RTCP回馈地址
// 	void GetAudRtcpBackAddr(u32 & dwRtcpBackIp, u16 & wRtcpBackPort)
//     {
//         dwRtcpBackIp = m_tAudRtcpBackAddr.GetIpAddr();
//         wRtcpBackPort = m_tAudRtcpBackAddr.GetPort();
//         return;
//     }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//4.6新加 版本 jlb
struct THduStartPlay: public TTvWallStartPlay
{
protected:
	u8 m_byMode;   // MODE_AUDIO, MODE_VIDEO, MODE_BOTH
	u8 m_byReserved;
public:
	THduStartPlay()
	{
		m_byMode = 0;
		m_byReserved = 0;
	}
	
	void SetMode( u8 byMode ){ m_byMode = byMode; }
    u8   GetMode( void ){ return m_byMode; }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//记录录像或放像进度(单位:秒)
struct  TRecProg
{
protected:
	u32   		m_dwCurProg;	//当前进度
	u32   		m_dwTotalTime;	//总长度，仅在放像时有效
	
public:
	//设置当前进度位置（单位：秒）
	void SetCurProg( u32    dwCurProg )	{ m_dwCurProg = htonl( dwCurProg ); }
	//获取当前进度位置（单位：秒）
	u32    GetCurProg( void ) const	{ return ntohl( m_dwCurProg ); }
	//设置总长度，仅对放像有效（单位：秒）
	void SetTotalTime( u32    dwTotalTime )	{ m_dwTotalTime = htonl( dwTotalTime ); }
	//获取总长度，仅对放像有效（单位：秒）
	u32    GetTotalTime( void ) const	{ return ntohl( m_dwTotalTime ); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//双载荷
struct TDoublePayload
{
protected:
	u8  m_byRealPayload;    //原媒体格式
	u8  m_byActivePayload;  //活动媒体格式
public:
    TDoublePayload()
	{
		Reset();
	}
	void Reset()
	{
		m_byRealPayload = MEDIA_TYPE_NULL;
		m_byActivePayload = MEDIA_TYPE_NULL;
	}
	void SetRealPayLoad(u8 byRealPayload)
	{
		m_byRealPayload = byRealPayload;
	}
	u8 GetRealPayLoad()
	{
		return m_byRealPayload;
	}
	
	void SetActivePayload(u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}
	
	u8 GetActivePayload()
	{
		return m_byActivePayload;
	}
	
	void Print() const
	{
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// H264画质属性(HP/BP) [12/8/2011 chendaiwei]
enum emProfileAttrb
{
	emBpAttrb,	//BP
	emHpAttrb,	//HP
};

#define ISHDFORMAT(byRes) \
	(VIDEO_FORMAT_W4CIF == byRes || VIDEO_FORMAT_HD720 == byRes || \
	VIDEO_FORMAT_SXGA == byRes || VIDEO_FORMAT_UXGA == byRes || \
         VIDEO_FORMAT_HD1080 == byRes)

//定义视频媒体格式的属性(len:5)
struct TVideoStreamCap
{
protected:
    u16		m_wMaxBitRate;  // 最高位标识HP/BP属性，为1标识HP，为0表示BP [12/2/2011 chendaiwei]
    u8		m_byMediaType;   
    u8      m_byResolution;	//分辨率 VIDEO_FORMAT_AUTO, ...
	u8      m_byFrameRate;  //帧率 MPI，对于 H.264 则是 FPS
    
public:
    TVideoStreamCap() { Clear(); }
    TVideoStreamCap(u8 byMediaType,u8 byRes,u8 byFrameRate,emProfileAttrb emAttrb,u16 wMaxRate) 
	{
		SetMediaType(byMediaType);
		SetResolution(byRes);
		MEDIA_TYPE_H264 == byMediaType ? SetUserDefFrameRate(byFrameRate) : SetFrameRate(byFrameRate);
		SetMaxBitRate(wMaxRate);
		SetH264ProfileAttrb(emAttrb);
	}
    
    void    Clear(void)
    {
        m_wMaxBitRate = 0;
        m_byFrameRate = 0;
        m_byMediaType = MEDIA_TYPE_NULL;
        m_byResolution = VIDEO_FORMAT_CIF;
    }   
    
    void	SetMediaType(u8 byMediaType)  {  m_byMediaType = byMediaType; }	
    u8		GetMediaType() const { return m_byMediaType; }
    
    void    SetResolution(u8 byRes) {   m_byResolution = byRes;    }
    u8      GetResolution(void) const   {   return m_byResolution;    }

    void    SetFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_byMediaType )
        {
            //StaticLog("Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_byFrameRate = byFrameRate;
    }
    u8      GetFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_byMediaType )
        {
            //StaticLog("Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_byFrameRate;
    }

    // guzh [12/1/2007] 自定义帧率的保存/获取
    void    SetUserDefFrameRate(u8 byActFrameRate) { m_byFrameRate = VIDEO_FPS_USRDEFINED+byActFrameRate; }
    BOOL32  IsFrameRateUserDefined() const {return (m_byFrameRate>VIDEO_FPS_USRDEFINED); }
    u8      GetUserDefFrameRate(void) const { return IsFrameRateUserDefined() ? m_byFrameRate-VIDEO_FPS_USRDEFINED : m_byFrameRate; }
    
	// m_wMaxBitRate的低15位标识bitRate [12/2/2011 chendaiwei]
    void	SetMaxBitRate(u16 wMaxRate) 
	{ 
		//m_wMaxBitRate = (m_wMaxBitRate & 0x8000) | htons(wMaxRate);
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		wTmpBitRate = (wTmpBitRate & 0x8000) | ( wMaxRate & 0x7FFF );
		m_wMaxBitRate = htons( wTmpBitRate );
	}

    u16		GetMaxBitRate() const 
	{ 
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		wTmpBitRate = wTmpBitRate & 0x7FFF;
		return wTmpBitRate; 
	}

	BOOL32  IsSupportHP() const
	{ 
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		if(wTmpBitRate & 0x8000)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	
	/*====================================================================
	函数名      ：SetH264ProfileAttrb
	功能        ：设置H264的HP/BP属性

	算法实现    ：
	引用全局变量：
	输入参数说明：[IN]emProfileAttrb emAttb标识HP/BP属性

	返回值说明  ：
	----------------------------------------------------------------------
	修改记录    ：
	日  期      版本        修改人        修改内容
	2011/11/28  4.0         chendaiwei       创建
	====================================================================*/
	void SetH264ProfileAttrb(emProfileAttrb emAttrb)
	{
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		switch(emAttrb)
		{
		case emHpAttrb:
			//m_wMaxBitRate = m_wMaxBitRate|0x8000 ;
			wTmpBitRate = wTmpBitRate | 0x8000;			
			break;
		case emBpAttrb:
			//m_wMaxBitRate = m_wMaxBitRate&0x7FFF ;
			wTmpBitRate = wTmpBitRate & 0x7FFF;
			break;
		}
		m_wMaxBitRate = htons( wTmpBitRate );

		return;
	}

		/*====================================================================
	函数名      :GetH264ProfileAttrb
	功能        ：获取H264的HP/BP属性

	算法实现    ：
	引用全局变量：
	输入参数说明：

	返回值说明  ：[OUT]emProfileAttrb emAttb标识HP/BP属性
	----------------------------------------------------------------------
	修改记录    ：
	日  期      版本        修改人        修改内容
	2011/11/28  4.0         chendaiwei       创建
	====================================================================*/
	emProfileAttrb GetH264ProfileAttrb ( void ) const
	{
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		if(wTmpBitRate & 0x8000)
		{
			return emHpAttrb;
		}
		else
		{
			return emBpAttrb;
		}
	}

	//TODO 是否加入HP/BP的比较 [12/2/2011 chendaiwei]
	BOOL32 IsH264CapLower(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// 标清帧率>30, 帧率按实际25比较
		u8 byDstFR = GetUserDefFrameRate();
		if(!ISHDFORMAT(m_byResolution) && byDstFR > 30 )
		{
			byDstFR = 25;
		}
		
		if(!ISHDFORMAT(bySrcRes) && bySrcFR > 30 )
		{
			bySrcFR = 25;
		}
		
		if ((wDstWidth * wDstHeight * byDstFR) < (wSrcWidth * wSrcHeight * bySrcFR))
		{
			return TRUE;
		}
		return FALSE;
	}
	
	//判断能力是否相等
	BOOL32 IsH264CapEqual(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// 标清帧率>30, 帧率按实际25比较
		u8 byDstFR = GetUserDefFrameRate();
		if(!ISHDFORMAT(m_byResolution) && byDstFR > 30 )
		{
			byDstFR = 25;
		}
		
		if(!ISHDFORMAT(bySrcRes) && bySrcFR > 30 )
		{
			bySrcFR = 25;
		}
		
		if ((wDstWidth * wDstHeight * byDstFR) == (wSrcWidth * wSrcHeight * bySrcFR))
		{
			return TRUE;
		}
		return FALSE;
	}

    BOOL32 IsResLower(u8 bySrcRes, u8 byDstRes) const
    {
        if (!IsResMatched(bySrcRes, byDstRes))
        {
            return FALSE;
        }
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;

        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
        if (wSrcWidth < wDstWidth &&
            wSrcHeight < wDstHeight)
        {
            return TRUE;
        }
        return FALSE;
    }

	BOOL32 IsResLowerWithOutMatched(u8 bySrcRes, u8 byDstRes) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
        if (wSrcWidth < wDstWidth &&
            wSrcHeight < wDstHeight)
        {
            return TRUE;
        }
        return FALSE;
    }
	// 计算分辨率帧率乘积，比较大小 [2012/09/12 nizhijun]
	BOOL32 IsSrcCapLowerThanDst(u8 bySrcRes, u8 bySrcFrameRate, u8 byDstRes,u8 byDstFrameRate) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
		u32 wSrcProduct = wSrcWidth*wSrcHeight*bySrcFrameRate;
		u32 wDstProduct = wDstWidth*wDstHeight*byDstFrameRate;
        if ( wSrcProduct < wDstProduct)
        {
            return TRUE;
        }
        return FALSE;
    }

	// 计算分辨率乘积，比较大小 [1/16/2012 chendaiwei]
	BOOL32 IsResLowerInProduct(u8 bySrcRes, u8 byDstRes) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
		u32 wSrcProduct = wSrcWidth*wSrcHeight;
		u32 wDstProduct = wDstWidth*wDstHeight;
        if ( wSrcProduct < wDstProduct)
        {
            return TRUE;
        }
        return FALSE;
    }

    BOOL32   operator ==( const TVideoStreamCap & tVideoStreamCap ) const
    {
        u8 byFrameRate;
        if (MEDIA_TYPE_H264 == tVideoStreamCap.GetMediaType())
        {
            byFrameRate = tVideoStreamCap.GetUserDefFrameRate() + VIDEO_FPS_USRDEFINED;
        }
        else
        {
            byFrameRate = tVideoStreamCap.GetFrameRate();
        }
        if ((tVideoStreamCap.GetMediaType() == m_byMediaType &&
            tVideoStreamCap.GetResolution() == m_byResolution &&
            byFrameRate == m_byFrameRate &&
			tVideoStreamCap.IsSupportHP() == IsSupportHP()) ||
            (tVideoStreamCap.GetMediaType() == MEDIA_TYPE_NULL && m_byMediaType == MEDIA_TYPE_NULL))
        {
            return TRUE;
        }
        
        return FALSE;
    }

	// 新增打印 [12/12/2011 chendaiwei]
	void Print( void )
	{
		//StaticLog("MediaType:%d  Res:%d  HP:%d  FPs:%d  BR:%d\n",
		//	GetMediaType(),GetResolution(),GetH264ProfileAttrb(),GetUserDefFrameRate(),GetMaxBitRate());
	}

private:
    void GetWHByRes(u8 byRes, u16 &wWidth, u16 &wHeight) const
    {
        wWidth = 0;
        wHeight = 0;
    
        switch(byRes)
        {
        case VIDEO_FORMAT_SQCIF_112x96:
            wWidth = 112;
            wHeight = 96;
            break;
        
        case VIDEO_FORMAT_SQCIF_96x80:
            wWidth = 96;
            wHeight = 80;
            break;
        
        case VIDEO_FORMAT_SQCIF:
            wWidth = 128;
            wHeight = 96;
            break;
        
        case VIDEO_FORMAT_QCIF:
            wWidth = 176;
            wHeight = 144;
            break;
        
        case VIDEO_FORMAT_CIF:
            wWidth = 352;
            wHeight = 288;
            break;
        
        case VIDEO_FORMAT_2CIF:
            wWidth = 352;
            wHeight = 576;
            break;
        
        case VIDEO_FORMAT_4CIF:
        
            //基于尽可能播放考虑，这里取大值
            wWidth = 704;
            wHeight = 576;
            break;
        
        case VIDEO_FORMAT_16CIF:
            wWidth = 1048;
            wHeight = 1152;
            break;
        
        case VIDEO_FORMAT_AUTO:
            //不解析
            break;
        
        case VIDEO_FORMAT_SIF:
            wWidth = 352;
            wHeight = 240;
            break;
        
        case VIDEO_FORMAT_2SIF:
            wWidth = 352;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_4SIF:
            wWidth = 704;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_VGA:
            wWidth = 640;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_SVGA:
            wWidth = 800;
            wHeight = 600;
            break;
        
        case VIDEO_FORMAT_XGA:
            wWidth = 1024;
            wHeight = 768;
            break;

        case VIDEO_FORMAT_W4CIF:
            wWidth = 1024;
            wHeight = 576;
            break;

        case VIDEO_FORMAT_HD720:
            wWidth = 1280;
            wHeight = 720;
            break;

        case VIDEO_FORMAT_SXGA:
            wWidth = 1280;
            wHeight = 1024;
            break;

        case VIDEO_FORMAT_UXGA:
            wWidth = 1600;
            wHeight = 1200;
            break;

        case VIDEO_FORMAT_HD1080:
            wWidth = 1920;
            wHeight = 1088;
            break;
			//非标分辨率（1080p底图）
		case VIDEO_FORMAT_1440x816:
			wWidth = 1440;
			wHeight = 816;
			break;
			
		case VIDEO_FORMAT_1280x720:
			wWidth = 1280;
			wHeight = 720;
			break;
			
		case VIDEO_FORMAT_960x544:
			wWidth = 960;
			wHeight = 544;
			break;
			
		case VIDEO_FORMAT_640x368:
			wWidth = 640;
			wHeight =368;
			break;
			
		case VIDEO_FORMAT_480x272:
			wWidth = 480;
			wHeight =272;
			break;
			
		case VIDEO_FORMAT_384x272:
			wWidth = 384;
			wHeight =272;
			break;

			//非标分辨率（720p底图）
		case VIDEO_FORMAT_720_960x544:
			wWidth = 960;
			wHeight =544;
			break;
			
		case VIDEO_FORMAT_720_864x480:
			wWidth = 864;
			wHeight =480;
			break;
			
		case VIDEO_FORMAT_720_640x368:
			wWidth = 640;
			wHeight =368;
			break;
			
		case VIDEO_FORMAT_720_432x240:
			wWidth = 432;
			wHeight =240;
			break;
			
		case VIDEO_FORMAT_720_320x192:
			wWidth = 320;
			wHeight =192;
			break;
		case VIDEO_FORMAT_640x544:
			wWidth = 640;
			wHeight =544;
			break;
		case VIDEO_FORMAT_320x272:
			wWidth = 320;
			wHeight =272;
			break;
        default:
            break;
        }
        if ( 0 == wHeight || 0 == wWidth )
        {
            //StaticLog("[TVideoStreamCap::GetWHByRes] unexpected res.%d, ignore it\n", byRes );
        }
        return;
    }

    BOOL32 IsResMatched(u8 bySrcRes, u8 byDstRes) const
    {
        BOOL32 bMatched = FALSE;
        if (IsResPresentation(bySrcRes) && IsResPresentation(byDstRes))
        {
            bMatched = TRUE;
        }
        else if (IsResLive(bySrcRes) && IsResLive(byDstRes))
        {
            bMatched = TRUE;
        }
        return bMatched;
    }
    
    BOOL32 IsResPresentation(u8 byRes) const
    {
        BOOL32 bPresentation = FALSE;
        
        switch(byRes)
        {
        case VIDEO_FORMAT_VGA:
        case VIDEO_FORMAT_SVGA:
        case VIDEO_FORMAT_XGA:
        case VIDEO_FORMAT_SXGA:
        case VIDEO_FORMAT_UXGA:
            bPresentation = TRUE;
            break;
        default:
            break;
        }
        return bPresentation;
    }
    
    BOOL32 IsResLive(u8 byRes) const 
    {
        BOOL32 bLive = FALSE;
        
        switch(byRes)
        {
        case VIDEO_FORMAT_CIF:
        case VIDEO_FORMAT_2CIF:
        case VIDEO_FORMAT_4CIF:
        case VIDEO_FORMAT_16CIF:
            
        case VIDEO_FORMAT_SIF:
        case VIDEO_FORMAT_2SIF:
        case VIDEO_FORMAT_4SIF:
            
        case VIDEO_FORMAT_W4CIF:
        case VIDEO_FORMAT_HD720:
        case VIDEO_FORMAT_HD1080:
            bLive = TRUE;
            break;
        //不解析以下
        case VIDEO_FORMAT_AUTO:
        case VIDEO_FORMAT_SQCIF_112x96:
        case VIDEO_FORMAT_SQCIF_96x80:
            break;
        default:
            break;
        }
        return bLive;
    }


}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//能力集扩展结构
struct TCapSupportEx
{
protected:
	u8 m_byVideoFECType;
	u8 m_byAudioFECType;
	u8 m_byDVideoFECType;
    TVideoStreamCap tSecDSCap;      //第二双流能力的H239属性向第一双流能力对齐
	
public:
    TCapSupportEx(): m_byVideoFECType(FECTYPE_NONE),
                     m_byAudioFECType(FECTYPE_NONE),
                     m_byDVideoFECType(FECTYPE_NONE)
	{
        tSecDSCap.Clear();
	}

public: //会控使用；终端适配在面向终端的时候模糊程度等同于会控，也用该接口.
	void	SetFECType(u8 byFECType)
	{
		m_byVideoFECType = byFECType; 
		m_byAudioFECType = FECTYPE_NONE;
		m_byDVideoFECType = byFECType;
	}

public: //MCU使用

	void Clear()
	{
		m_byVideoFECType = FECTYPE_NONE;
		m_byAudioFECType = FECTYPE_NONE;
		m_byDVideoFECType = FECTYPE_NONE;
		tSecDSCap.Clear();
	}

	BOOL32	IsNoSupportFEC(void) const 
	        { return ( (FECTYPE_NONE == m_byVideoFECType) &&
                       (FECTYPE_NONE == m_byAudioFECType) &&
                       (FECTYPE_NONE == m_byDVideoFECType) ); }
	BOOL32	IsVideoSupportFEC(void) const { return ( FECTYPE_NONE != m_byVideoFECType ); }
	BOOL32	IsAudioSupportFEC(void) const { return ( FECTYPE_NONE != m_byAudioFECType ); }
	BOOL32	IsDVideoSupportFEC(void) const { return ( FECTYPE_NONE != m_byDVideoFECType ); }
	u8		GetVideoFECType(void) const { return m_byVideoFECType; }
	void	SetVideoFECType(u8 byFECType) { m_byVideoFECType = byFECType; }
	u8		GetAudioFECType(void) const { return m_byAudioFECType; }
	void	SetAudioFECType(u8 byFECType) { m_byAudioFECType = byFECType; }
	u8		GetDVideoFECType(void) const { return m_byDVideoFECType; }
	void	SetDVideoFECType(u8 byFECType) { m_byDVideoFECType = byFECType; }

public:
    void    SetSecDSType(u8 byType){ tSecDSCap.SetMediaType(byType); }
    u8      GetSecDSType(void) const { return tSecDSCap.GetMediaType(); };
    void    SetSecDSRes(u8 byRes) { tSecDSCap.SetResolution(byRes); }
    u8      GetSecDSRes(void) const { return tSecDSCap.GetResolution(); }
    void    SetSecDSBitRate(u16 wBitRate) { tSecDSCap.SetMaxBitRate(wBitRate);  }
    u16     GetSecDSBitRate(void) const { return tSecDSCap.GetMaxBitRate(); }

	BOOL32  IsDDStreamCap( void )const { return (MEDIA_TYPE_NULL != tSecDSCap.GetMediaType() && 0 != tSecDSCap.GetMediaType());  }

    void    SetSecDSFrmRate(u8 byFrmRate)
    {
        if (MEDIA_TYPE_H264 != tSecDSCap.GetMediaType())
        {
            tSecDSCap.SetFrameRate(byFrmRate);
        }
        else
        {
            tSecDSCap.SetUserDefFrameRate(byFrmRate);
        }
    }
    u8      GetSecDSFrmRate(void) const
    {
        if (MEDIA_TYPE_H264 != tSecDSCap.GetMediaType())
        {
            return tSecDSCap.GetFrameRate();
        }
        else
        {
            return tSecDSCap.GetUserDefFrameRate();
        }
    }

    void	FECType2Str( u8 byFECType, s8* pchStr ) const
	{
		switch( byFECType )
		{
		case FECTYPE_NONE:
			memcpy(pchStr, "NONE", sizeof("NONE"));
			break;
		case FECTYPE_RAID5:
			memcpy(pchStr, "RAID5", sizeof("RAID5"));
			break;
		case FECTYPE_RAID6:
			memcpy(pchStr, "RAID6", sizeof("RAID6"));
			break;
		default:
			sprintf(pchStr, "WRONG VALUE<%d>", byFECType );
			break;
		}
	}

	// 返回双双流能力集 [12/15/2011 chendaiwei]
	TVideoStreamCap GetSecDSVideoCap( void ) const
	{
		return tSecDSCap;
	}	

	void	Print(void) const
	{
//         StaticLog("FECType:\n" );
// 		s8 achStr[32];
// 		StaticLog("\tVideo\t\t:");
// 		memset(achStr, 0, sizeof(achStr));
// 		FECType2Str( m_byVideoFECType, achStr );
// 		StaticLog("%s\n", achStr );
// 
// 		StaticLog("\tAudio\t\t:");
// 		memset(achStr, 0, sizeof(achStr));
// 		FECType2Str( m_byAudioFECType, achStr );
// 		StaticLog("%s\n", achStr );
// 
// 		StaticLog("\tDVideo\t\t:");
// 		memset(achStr, 0, sizeof(achStr));
// 		FECType2Str( m_byDVideoFECType, achStr );
// 		StaticLog("%s\n", achStr );
// 
//         StaticLog("TSecDSCap:\n");
//         StaticLog("\tMediaType\t:%d\n", GetSecDSType());
//         StaticLog("\tBitRate\t\t:%d\n", GetSecDSBitRate());
//         StaticLog("\tResolution\t:%d\n", GetSecDSRes());
//         StaticLog("\tFrameRate\t:%d\n", GetSecDSFrmRate());
// 
//         StaticLog("\n");
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TRecRtcpBack
{
protected:
    u32  m_tVideoIp;      //视频RTCP回馈地址
    u16  m_tVideoPort;    //视频RTCP回馈端口
    u32  m_tAudioIp;      //音频RTCP回馈地址
    u16  m_tAudioPort;    //音频RTCP回馈端口
    u32  m_tDStreamIp;    //双流RTCP回馈地址
    u16  m_tDStreamPort;  //双流RTCP回馈端口
	
public:
    TRecRtcpBack(void)
	{
		Reset();
	}
	void Reset(void)
	{
		m_tVideoIp = 0xFFFFFFFF;
        m_tVideoPort = 0xFFFF;
        m_tAudioIp = 0xFFFFFFFF;
        m_tAudioPort = 0xFFFF;
        m_tDStreamIp = 0xFFFFFFFF;
        m_tDStreamPort = 0xFFFF;
	}
	
    void SetVideoAddr(u32 dwVideoIp, u16 wVideoPort)
    {
        m_tVideoIp = htonl(dwVideoIp);
        m_tVideoPort = htons(wVideoPort);
    }
	
    void GetVideoAddr(u32 &dwVideoIp, u16 &wVideoPort)
    {
        dwVideoIp = ntohl(m_tVideoIp);
        wVideoPort = ntohs(m_tVideoPort);
    }
	
    
    void SetAudioAddr(u32 dwAudioIp, u16 wAudioPort)
    {
        m_tAudioIp = htonl(dwAudioIp);
        m_tAudioPort = htons(wAudioPort);
    }
	
    void GetAudioAddr(u32 &dwAudioIp, u16 &wAudioPort)
    {
        dwAudioIp = ntohl(m_tAudioIp);
        wAudioPort = ntohs(m_tAudioPort);
    }
	
    
    void SetDStreamAddr(u32 dwDStreamIp, u16 wDStreamPort)
    {
        m_tDStreamIp = htonl(dwDStreamIp);
        m_tDStreamPort = htons(wDStreamPort);
    }
	
    void GetDStreamAddr(u32 &dwDStreamIp, u16 &wDStreamPort)
    {
        dwDStreamIp = ntohl(m_tDStreamIp);
        wDStreamPort = ntohs(m_tDStreamPort);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

// 
// // VMP空闲通道显示模式
// // VMP空闲通道显示为黑色
// #define VMP_SHOW_BLACK_MODE           0
// // VMP空闲通道显示最后一帧
// #define VMP_SHOW_LASTFRAME_MODE       1
// // VMP空闲通道显示默认图片，480*272
// #define VMP_SHOW_DEFPIC_MODE          2 
// // VMP空闲通道显示用户自定义图片
// #define VMP_SHOW_USERDEFPIC_MODE      3
// // End

//  [1/8/2010 pengjie] Modify 
// HDU扩展配置
struct THDUExCfgInfo
{
	u8  m_byIdleChlShowMode;  // 空闲通道显示模式 HDU_SHOW_GRAY_MODE ...
	
	u8  m_byReserved; // 保留字段
	u16 m_wReserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*----------------------------------------------------------------------
结构名：THduChnStatus
用途  ：
----------------------------------------------------------------------*/
struct THduChnStatus
{
    enum EHduChnStatus
    {
        eIDLE   = 0, //空闲
			eREADY  = 1, //准备
			eNORMAL = 2,  //运行,表示HDU设备在运行
			eRUNNING= 3  //表示HDU的某个通道正在编码使用 [nizhijun 2010/10/27] add
    };
	
public:
	
    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void )  const { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tHdu.IsNull(); }
    void   SetNull( void ) { m_tHdu.SetNull(); }
	
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tHdu ) { m_tHdu = tHdu; }
    TEqp   GetEqp( void ) const { return m_tHdu; }
    u8     GetEqpId( void ) const { return m_tHdu.GetEqpId(); }	
	
    void   SetSchemeIdx( u8 bySchemeIdx ) { m_bySchemeIdx = bySchemeIdx; };
    u8     GetSchemeIdx( void ) { return m_bySchemeIdx; }
	
	u8     GetVolume( void ) const { return m_byVolume; }
	void   SetVolume( u8 byVolume ){ m_byVolume = byVolume; }
	
	BOOL32   GetIsMute( void ) const { return m_byMute; }
	void   SetIsMute( BOOL32 byIsMute ){ m_byMute = GETBBYTE(byIsMute); }
	
private:
	u8 m_byStatus;	  // HduChnStatus
	u8 m_byChnIdx;
    u8 m_bySchemeIdx; // 正在被使用预案的索引号 
    u8 m_byVolume;
	u8 m_byMute;      // 是否静音
    TEqpNoConstruct m_tHdu;
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TEqpEntryParam
{
protected:
    u32 m_dwMcuIp;		    /*本外设要连接的MCU的IP地址 网络序*/
    u16 m_wMcuPort;			/*本外设要连接的MCU的端口号 网络序*/
    u8  m_byMcuId;		    /*本外设要连接的MCU编号*/
    
    u8  m_byType;			/*本外设的类型值*/
    u8  m_byConnectState;	/*本外设的连接状态*/
    u8  m_byExist;			/*是否使用该表项*/

public:    
    TEqpEntryParam() : m_dwMcuIp(0),
                       m_wMcuPort(0),
                       m_byMcuId(0),
                       m_byType(0),
                       m_byConnectState(0),
                       m_byExist(0){}
    void SetMcuIp(u32 dwMcuIp) { m_dwMcuIp = htonl(dwMcuIp);   }
    u32  GetMcuIp(void) const { return ntohl(m_dwMcuIp);  }
    void SetMcuPort(u16 wMcuPort) { m_wMcuPort = htons(wMcuPort);  }
    u16  GetMcuPort(void) const { return ntohs(m_wMcuPort);   }
    void SetMcuId(u8 byMcuId) { m_byMcuId = byMcuId;   }
    u8   GetMcuId(void) const { return m_byMcuId;    }
    void SetType(u8 byType) { m_byType = byType;  }
    u8   GetType(void) const { return m_byType;   }
    void SetState( u8 byState ) {  m_byConnectState = byState;   }
    u8   GetState(void) const { return m_byConnectState;  }
    void SetExist(BOOL32 bExist) { m_byExist = bExist ? 1 : 0;   }
    BOOL32 GetExist(void) { return m_byExist == 1 ? TRUE : FALSE;  }
	
    void SetDefaultEntParam( u8 byEqpType, u32 dwMcuIp, u8 byState = 0 )
    {
        m_byType   = byEqpType;
        m_dwMcuIp  = dwMcuIp;
        m_byConnectState  = byState;
        m_byMcuId  = 191;
        m_wMcuPort = UMS_LISTIONPORT_CMS;
        m_byExist  = 1;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设基本信息	
struct TEqpBasicInfo
{
protected:
    u8 m_byEqpId;                       //设备ID
    s8 m_achAlias[MAXLEN_EQP_ALIAS+1];  //设备别名
public:
    TEqpBasicInfo() : m_byEqpId(0)	{ memset( m_achAlias, 0, sizeof(m_achAlias) );	}
    void SetEqpId(u8 byEqpId) { m_byEqpId = byEqpId;  }
    u8   GetEqpId(void) const { return m_byEqpId;  }
    void SetAlias(LPCSTR lpszAlias)
    {
        if ( NULL != lpszAlias)
        {
            strncpy(m_achAlias, lpszAlias, sizeof(m_achAlias));
            m_achAlias[sizeof(m_achAlias)-1] = '\0';
        }
    }
    LPCSTR GetAlias(void){ return m_achAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设运行板相关信息
struct TEqpRunBrdInfo
{
protected:
    u8  m_byRunBrdId;       //运行板ID
    u16 m_wEqpRecvPort;     //运行板(外设)侧接收起始端口号 网络序
    u32 m_dwIpAddr;         //运行板Ip
public:
    TEqpRunBrdInfo() : m_byRunBrdId(0),
					   m_wEqpRecvPort(0),
                       m_dwIpAddr(0){}
    void SetRunBrdId(u8 byBrdId){ m_byRunBrdId = byBrdId;  }
    u8   GetRunBrdId(void) const { return m_byRunBrdId;  }
    void SetEqpRecvPort(u16 wRecvPort)  { m_wEqpRecvPort = htons(wRecvPort);  }
    u16  GetEqpRecvPort(void) const { return ntohs(m_wEqpRecvPort);  }   
    void SetIpAddr(u32 dwIp){ m_dwIpAddr = htonl(dwIp);    }
    u32  GetIpAddr(void) const { return ntohl(m_dwIpAddr);    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设map相关信息
struct TEqpMapInfo
{
protected:
    u8 m_abyUsedMapId[MAXNUM_MAP];
    u8 m_byMapNum;
public:
    TEqpMapInfo() : m_byMapNum(0){ memset(m_abyUsedMapId, 0, sizeof(m_abyUsedMapId));  }
	
	// 本set函数只适应顺次从小到大写入
    void SetUsedMapId(u8 byMapId )
    {
		if ( m_byMapNum < MAXNUM_MAP )
		{
			m_abyUsedMapId[m_byMapNum] = byMapId;
			m_byMapNum ++;
		}
    }
    u8 GetUsedMapId( u8 byIdx )
	{
		return m_abyUsedMapId[byIdx];
	}
	
    BOOL32 GetUsedMap( u8 * pbyMap, u8 &byMapCount )
    {
        if ( NULL == pbyMap ) 
        {
            return FALSE;
        }
        memcpy(pbyMap, m_abyUsedMapId, m_byMapNum);
        byMapCount = m_byMapNum;
        return TRUE;
    }
    BOOL32 SetUsedMap( u8 * pbyMap, u8 byMapCount )
    {
        if ( NULL == pbyMap || 0 == byMapCount )
        {
            return FALSE;
        }
        memcpy(m_abyUsedMapId, pbyMap, byMapCount);
        m_byMapNum = byMapCount;
        return TRUE;
    }
    void GetUsedMapStr( s8 * pszMapStr )
    {
        if( NULL == pszMapStr )
        {
            return;
        }
		for(u8 nLp = 0; nLp < m_byMapNum; nLp++)
		{
			sprintf(pszMapStr, "%s,%d", pszMapStr, ((s8*)m_abyUsedMapId)[nLp]);
		}
		if ( pszMapStr[0] == ',')
		{
			pszMapStr[0] = ' ';
		}
        return;
    }
    u8   GetUsedMapNum(void) 
    {
        return m_byMapNum;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



struct TBrdPosition
{
    u8 byBrdID;                      // 板子ID号 
    u8 byBrdLayer;                   // 板子所在层号
    u8 byBrdSlot;                    // 板子所在槽位号
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//4.6版外设
struct THduChnlModePortAgt
{
public:
    THduChnlModePortAgt()
	{
		memset(this, 0x0, sizeof(THduChnlModePortAgt));
	}
	
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }
	
    u8 GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8 GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }
	
private:
    u8 byOutPortType;
    u8 byOutModeType;
	u8 byZoomRate;
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义画面合成成员结构 (len:8)
struct TVMPMember: public TMtNoConstruct
{
protected:
    u8   m_byMemberType;     //画面合成成员类型,参见vccommon.h中画面合成成员类型定义
    u8   m_byMemStatus;      //成员状态(MT_STATUS_CHAIRMAN, MT_STATUS_SPEAKER, MT_STATUS_AUDIENCE)
	
public:
    void  SetMemberType(u8   byMemberType){ m_byMemberType = byMemberType;} 
    u8    GetMemberType( void ) const { return m_byMemberType; }
    void  SetMemStatus(u8 byStatus) { m_byMemStatus = byStatus; }
    u8    GetMemStatus(void) const { return m_byMemStatus; }
    void  SetMemberTMt( TMt tMt ){ memcpy( this, &tMt, sizeof(TMt) ); }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义画面合成参数结构 (len:136 + 4*8 = 168)
struct TVMPParam
{
protected:
	u8      m_byVMPAuto;      //是否是自动画面合成 0-否 1-是
	u8      m_byVMPBrdst;     //合成图像是否向终端广播 0-否 1-是 
	u8      m_byVMPStyle;     //画面合成风格,参见mcuconst.h中画面合成风格定义
    u8      m_byVMPSchemeId;  //合成风格方案编号,最大支持5套方案,1-5
    u8      m_byVMPMode;      //图像复合方式: 0-不图像复合 1-会控或主席控制图像复合 2-自动图像复合(动态分屏与设置成员)
	u8		m_byRimEnabled;	  //是否使用边框: 0-不使用(默认) 1-使用;
							  //本字段目前只对方案0有效, 其他方案暂不涉及本字段的设置和判断
	//u8		m_byReserved1;	  //保留字段
	//u8		m_byReserved2;	  //保留字段
	u8		m_byVMPBatchPoll; // xliang [12/18/2008] 是否是批量轮询 0-否
	u8		m_byVMPSeeByChairman;	// 是否被主席MT选看	0-否
	TVMPMember  m_atVMPMember[MAXNUM_VMP_MEMBER]; //画面合成成员
public:
    void   SetVMPAuto(u8   byVMPAuto){ m_byVMPAuto = byVMPAuto;} 
    BOOL   IsVMPAuto( void ) const { return m_byVMPAuto == 0 ? FALSE : TRUE; }
    void   SetVMPBrdst(u8   byVMPBrdst){ m_byVMPBrdst = byVMPBrdst;} 
    BOOL   IsVMPBrdst( void ) const { return m_byVMPBrdst == 0 ? FALSE : TRUE; }
    void   SetVMPStyle(u8   byVMPStyle){ m_byVMPStyle = byVMPStyle;} 
    u8     GetVMPStyle( void ) const { return m_byVMPStyle; }
    void   SetVMPSchemeId(u8 bySchemeId) { m_byVMPSchemeId = bySchemeId; }
    u8     GetVMPSchemeId(void) const { return m_byVMPSchemeId; }
    void   SetVMPMode(u8   byVMPMode){ m_byVMPMode = byVMPMode;} 
    u8     GetVMPMode( void ) const { return m_byVMPMode; }
	void   SetIsRimEnabled(u8 byEnabled){ m_byRimEnabled = byEnabled; }
	BOOL32 GetIsRimEnabled(void) const { return m_byRimEnabled == 1 ? TRUE : FALSE; }
	void	SetVMPBatchPoll(u8 byVMPBatchPoll){m_byVMPBatchPoll = byVMPBatchPoll;} // xliang [12/22/2008] 
	BOOL	IsVMPBatchPoll( void ) const { return m_byVMPBatchPoll == 0 ? FALSE : TRUE;}
	void	SetVMPSeeByChairman(u8 byVMPSeeByMt) { m_byVMPSeeByChairman = byVMPSeeByMt;}
	BOOL	IsVMPSeeByChairman( void ) const {  return m_byVMPSeeByChairman == 0 ? FALSE : TRUE; }
    u8     GetMaxMemberNum( void ) const 
	{
		u8   byMaxMemNum = 1;

		switch( m_byVMPStyle ) 
		{
		case VMP_STYLE_ONE:
			byMaxMemNum = 1;
			break;
		case VMP_STYLE_VTWO:
		case VMP_STYLE_HTWO:
			byMaxMemNum = 2;
			break;
		case VMP_STYLE_THREE:
			byMaxMemNum = 3;
			break;
		case VMP_STYLE_FOUR:
			byMaxMemNum = 4;
			break;
		case VMP_STYLE_SIX:
			byMaxMemNum = 6;
			break;
		case VMP_STYLE_EIGHT:
			byMaxMemNum = 8;
			break;
		case VMP_STYLE_NINE:
			byMaxMemNum = 9;
			break;
		case VMP_STYLE_TEN:
			byMaxMemNum = 10;
			break;
		case VMP_STYLE_THIRTEEN:
			byMaxMemNum = 13;
			break;
		case VMP_STYLE_SIXTEEN:
			byMaxMemNum = 16;
			break;
		case VMP_STYLE_SPECFOUR:
			byMaxMemNum = 4;
			break;
		case VMP_STYLE_SEVEN:
			byMaxMemNum = 7;
			break;
		case VMP_STYLE_TWENTY:
			byMaxMemNum = 20;
			break;
		default:
			byMaxMemNum = 1;
			break;
		}
		return byMaxMemNum;
	}
	void   SetVmpMember( u8   byMemberId, TVMPMember tVMPMember )
	{
		if( byMemberId >= MAXNUM_VMP_MEMBER )return;
		m_atVMPMember[byMemberId] = tVMPMember;
	}
	void   ClearVmpMember( u8 byMemberId )
	{
		if( byMemberId >= MAXNUM_VMP_MEMBER )return;
		m_atVMPMember[byMemberId].SetNull();
        m_atVMPMember[byMemberId].SetMemberType(0);
	}
    TVMPMember *GetVmpMember( u8   byMemberId )
	{
		if( byMemberId >= MAXNUM_VMP_MEMBER )return NULL;
		return &m_atVMPMember[byMemberId];
	}

	BOOL32 FindVmpMember(TMt tMt, u8 &byIndex)
	{
		byIndex = 0;
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() && byLoop < MAXNUM_VMP_MEMBER )
		{
			// 跳过双流跟随通道
			if (VMP_MEMBERTYPE_DSTREAM == m_atVMPMember[byLoop].GetMemberType())
			{
				byLoop++;
				continue;
			}

			if( tMt.GetMtId() == m_atVMPMember[byLoop].GetMtId() && 
				tMt.GetMcuId() == m_atVMPMember[byLoop].GetMcuId() )
			{
				byIndex = byLoop;
				return TRUE;
			}
			
			byLoop++;
		}
		
		return FALSE;
	}
	
	//判断两个VmpParam是否相等
	BOOL32 IsParamEqual(const TVMPParam &tVmpParam)
	{
		if (m_byVMPAuto != tVmpParam.m_byVMPAuto ||
			m_byVMPBrdst != tVmpParam.m_byVMPBrdst ||
			m_byVMPStyle != tVmpParam.m_byVMPStyle ||
			m_byVMPSchemeId != tVmpParam.m_byVMPSchemeId ||
			m_byVMPMode != tVmpParam.m_byVMPMode ||
			m_byRimEnabled != tVmpParam.m_byRimEnabled ||
			m_byVMPBatchPoll != tVmpParam.m_byVMPBatchPoll ||
			m_byVMPSeeByChairman != tVmpParam.m_byVMPSeeByChairman)
		{
			return FALSE;
		}
		for (u8 byIdx=0;byIdx<MAXNUM_VMP_MEMBER;byIdx++)
		{
			if ((m_atVMPMember[byIdx].IsNull() && tVmpParam.m_atVMPMember[byIdx].IsNull())
				|| m_atVMPMember[byIdx] == tVmpParam.m_atVMPMember[byIdx])
			{
				continue;
			}
			return FALSE;
		}
		return TRUE;
	}

	//画面合成中有非本级的成员，且该成员非参数指定的memtype
	BOOL32 HasUnLocalMemberInVmp(u8 byMemType = 0)
	{
		BOOL32 bRet = FALSE;
		for(u8 byLoop = 0; byLoop < MAXNUM_VMP_MEMBER; byLoop ++)
		{
			if(!m_atVMPMember[byLoop].IsNull())
			{
				if( !m_atVMPMember[byLoop].IsLocal() 
					&& m_atVMPMember[byLoop].GetMemberType() != byMemType
					/*m_atVMPMember[byLoop].GetMtType() == MT_TYPE_SMCU*/ 
					)
				{
					bRet = TRUE;
					break;
				}
			}
		}
		return bRet;
	}
	BOOL IsMtInMember( TMt tMt )
	{
		u8 byIndex = 0;
		return FindVmpMember(tMt, byIndex);
	}
    BOOL IsTypeInMember(u8 byType) const
    {
        u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			if( byType == m_atVMPMember[byLoop].GetMemberType() )
			{
				return TRUE;
			}
			byLoop++;
		}

		return FALSE;
    }
	// [3/30/2010 xliang] bLast 表明返回最后一个找到的位置; byFilterPos表需要过滤的通道，即找到的是该通道不予承认
	u8 GetChlOfMtInMember( TMt tMt, BOOL32 bLast = FALSE, u8 byFilterPos = MAXNUM_VMP_MEMBER, u8 *pbyPos = NULL, u8 *byPosNum = NULL ) const
	{
        //[zhushz 20110722]找出终端所在所有通道
        if( pbyPos != NULL && byPosNum != NULL )
        {
            *byPosNum = 0;
            u8 *pbyTmp = pbyPos;
            for( u8 byIndx = 0; byIndx < GetMaxMemberNum(); byIndx++)
            {
				//跳过双流跟随通道
				if (VMP_MEMBERTYPE_DSTREAM == m_atVMPMember[byIndx].GetMemberType())
				{
					continue;
				}

                if (m_atVMPMember[byIndx].GetMcuId() == tMt.GetMcuId()
                    && m_atVMPMember[byIndx].GetMtId() == tMt.GetMtId()
				    && byIndx != byFilterPos)
                {
                    *pbyTmp = byIndx;
                    pbyTmp++;
                    (*byPosNum)++;
                }
            }
        }

		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			u8 byIdx = byLoop;
			if(bLast)
			{
				byIdx = GetMaxMemberNum() - 1 - byLoop;
			}
			
			//跳过双流跟随通道
			if (VMP_MEMBERTYPE_DSTREAM == m_atVMPMember[byIdx].GetMemberType())
			{
				byLoop++;
				continue;
			}

			if(m_atVMPMember[byIdx].GetMcuId() == tMt.GetMcuId()
				&& m_atVMPMember[byIdx].GetMtId() == tMt.GetMtId()
				&& byIdx != byFilterPos)
			{
				return byIdx;
			}

			byLoop++;
		}

		return MAXNUM_VMP_MEMBER;
	}
	u8 GetVMPMemberNum() const
	{
		u8 byCnt = 0;
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			if (!m_atVMPMember[byLoop].IsNull())
			{
				++byCnt;
			}
			byLoop++;
		}
		
		return byCnt;
	}
	u8 GetChlOfMemberType (u8 byMemberType) 
	{
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			if (byMemberType == m_atVMPMember[byLoop].GetMemberType())
			{
				return byLoop;
			}
			byLoop++;
		}

		return MAXNUM_VMP_MEMBER;
	}
	
	//zhouyiliang 20101019 寻找最后前或者最后一个mcuindx的终端的位置,bLast = false 时找最开始的那个
	u8 GetSMcuLastMtMemberPos( u16 wMcuIndx, BOOL32 bLast = TRUE )
	{
		if ( LOCAL_MCUIDX == wMcuIndx || INVALID_MCUIDX == wMcuIndx ) 
		{
			return MAXNUM_VMP_MEMBER;
		}
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			u8 byIdx = byLoop;
			if( bLast )
			{
				byIdx = GetMaxMemberNum() - 1 - byLoop;
			}

			if( !m_atVMPMember[byIdx].IsNull() && m_atVMPMember[byIdx].GetMcuId() == wMcuIndx )
			{
				return byIdx;
			}

			byLoop++;
		}
		return MAXNUM_VMP_MEMBER;
	}

	
	void   Print( u8 byLogLvl = LOG_LVL_DETAIL ) const
	{
		LogPrint(byLogLvl, MID_MCU_VMP, "\nVMPParam:\n");
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPAuto: %d\n", m_byVMPAuto);
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPBrdst: %d\n", m_byVMPBrdst);
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPStyle: %d\n", m_byVMPStyle);
        LogPrint(byLogLvl, MID_MCU_VMP, "m_byVmpSchemeId: %d\n", m_byVMPSchemeId );
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byRimEnabled: %d\n", m_byRimEnabled );
        LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPMode: %d\n", m_byVMPMode );
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPBatchPoll :%d\n", m_byVMPBatchPoll );
		LogPrint(byLogLvl, MID_MCU_VMP, "m_byVMPSeeByChairman : %d\n", m_byVMPSeeByChairman);
		for( int i = 0; i < GetMaxMemberNum(); i ++ )
		{
			LogPrint(byLogLvl, MID_MCU_VMP, "VMP member %d: (%d,%d), Type-%d\n", 
				i, m_atVMPMember[i].GetMcuId(), m_atVMPMember[i].GetMtId(), m_atVMPMember[i].GetMemberType() );            
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成器状态
struct TVmpStatus
{
	enum EnumUseState 
	{ 
		IDLE,		//未被占用
			RESERVE,    //预留
			WAIT_START, //等待开始回应
			START,      //正进行画面合成
			WAIT_STOP,  //等待结束回应
	};
public:	
	u8        m_byUseState;	    //使用状态 0-未使用 1-使用
	u8        m_byChlNum;       //通道数
#ifdef _ZGCDEBUG_
	u8		  m_byEncodeNum;	//编码路数, zgc, 2007-06-20
#endif
    TVMPParam m_tVMPParam;      //合成参数
	u8		  m_bySubType;		//vmp子类型，详见mcuconst.h中的定义// xliang [12/29/2008] 
	u8		  m_byBoardVer;		//表征MPU A板/B板
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//modify bas 2
//适配器启动参数结构
struct TAdaptParam
{
    enum EVideoType
    {
        vNONE  = MEDIA_TYPE_NULL,//视频不进行适配
        vMPEG4 = MEDIA_TYPE_MP4,
        vH261  = MEDIA_TYPE_H261,
        vH263  = MEDIA_TYPE_H263,
        vH264  = MEDIA_TYPE_H264,
    };
    enum EAudioType
    {
        aNONE  = MEDIA_TYPE_NULL,//音频不进行适配
        aMP3   = MEDIA_TYPE_MP3,
        aPCMA  = MEDIA_TYPE_PCMA,
        aPCMU  = MEDIA_TYPE_PCMU,
        aG7231 = MEDIA_TYPE_G7231,
        aG728  = MEDIA_TYPE_G728,
        aG729  = MEDIA_TYPE_G729,
    };

public:
    u16  GetWidth(void) const	{ return (ntohs(m_wWidth)); };
    u16  GetHeight(void) const	{ return (ntohs(m_wHeight)); };
    u16  GetBitrate(void) const { return (ntohs(m_wBitRate));};

    void SetResolution(u16 wWidth, u16 wHeight)
    {
        m_wWidth = htons(wWidth);
        m_wHeight = htons(wHeight);
    }
	
	void SetBitRate(u16 wBitrate)
	{
	    m_wBitRate = htons(wBitrate);
	}
	
	void SetVidType(u8 eType)
	{
		m_byVidCodeType = (u8)eType;
	}
	u8 GetVidType(void){ return m_byVidCodeType ;}
	
	void SetAudType(u8 eType)
	{
		m_byAudCodeType = (u8)eType;
	}
	u8 GetAudType(void){ return m_byAudCodeType; }

	void SetVidActiveType(u8 eType)
	{
		m_byVidActiveType = (u8)eType;
	}
	u8 GetVidActiveType(void){ return m_byVidActiveType; }
	
	void SetAudActiveType(u8 eType)
	{
		m_byAudActiveType = (u8)eType;
	}
	u8 GetAudActiveType(void){ return m_byAudActiveType; }

	void SetIsNeedByPrs(BOOL32 bNeedPrs)
	{
		m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
	}

	BOOL32 IsNeedbyPrs(void)
	{
		return (0 != m_byNeedPrs);
	}

    BOOL32 IsNull(void) const
    {
        return (MEDIA_TYPE_NULL == m_byAudCodeType || 0 == m_byAudCodeType ) &&
               (MEDIA_TYPE_NULL == m_byVidCodeType || 0 == m_byVidCodeType );
    }
    void Clear(void)
    {
        m_byAudCodeType = MEDIA_TYPE_NULL;
        m_byVidCodeType = MEDIA_TYPE_NULL;
        m_byAudActiveType = MEDIA_TYPE_NULL;
        m_byVidActiveType = MEDIA_TYPE_NULL;
        m_wBitRate = 0;
        m_wWidth = 0;
        m_wHeight = 0;
        m_byNeedPrs = 0;
    }

	// [11/1/2011 liuxu] 打印调整
	void PrintTitle() const 
	{
//         StaticLog( "%8s %8s %8s %8s %8s %8s %8s %8s\n", 
// 			"AudCodeT", "VidCodeT", "AudActT", "VidActT",
// 			"Bitrate", "Width", "Height", "NeedPrs" );
	}

    void Print(void) const
    {
// 		StaticLog( "%8d %8d %8d %8d %8d %8d %8d %8d\n", 
// 			m_byAudCodeType, m_byVidCodeType, m_byAudActiveType, m_byVidActiveType,
// 			GetBitrate(), GetWidth(), GetHeight(), m_byNeedPrs );
    }

private:
    u8         m_byAudCodeType;  //适配音频输出类型
    u8         m_byVidCodeType;  //适配视频输出类型
    u8         m_byAudActiveType;//适配音频输出动态载荷类型
    u8         m_byVidActiveType;//适配视频输出动态载荷类型
    
    u16 	   m_wBitRate;//发送码率
    u16 	   m_wWidth; //图像宽度
    u16 	   m_wHeight;//图像宽度
    
    u8         m_byNeedPrs;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;
/*----------------------------------------------------------------------
结构名：THDAdaptParam
用途  ：HD适配参数
----------------------------------------------------------------------*/
struct THDAdaptParam : public TAdaptParam
{
public:
    u8 GetFrameRate( void ) { return m_byFrameRate; }
    void SetFrameRate(u8 byFrameRate) { m_byFrameRate = byFrameRate; }
	
	u8 GetProfileType( void ) { return m_byProfileType; }
    void SetProfileType(u8 byProfileType) { m_byProfileType = byProfileType; }
	
    void Reset(void)
    {
        Clear();
        m_byFrameRate = 0;
        m_byProfileType = 0;
        m_byReserve2 = 0;
        m_byReserve3 = 0;
    }
	
	// [11/1/2011 liuxu] 打印调整
	void PrintTitle() const 
	{
//		StaticLog("--------------------------------------------------------------------------------\n");
//		StaticLog( "%7s ", "FrmRate");
//		StaticLog( "%7s ", "ProType");
		TAdaptParam::PrintTitle();
//		StaticLog("--------------------------------------------------------------------------------\n");
	}
	
    void PrintHd(void) const
   {
 //       StaticLog( "%7d ", m_byFrameRate);
//		StaticLog( "%7d ", m_byProfileType);
		TAdaptParam::Print();
    }
	
private:
    u8 m_byFrameRate;
    u8 m_byProfileType;
    u8 m_byReserve2;
    u8 m_byReserve3;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDBasChnStatus
用途  ：HDBas适配通道
----------------------------------------------------------------------*/
struct THDBasChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0,    //空闲
			READY  = 1,    //准备适配
			RUNING = 2,    //正在适配
			WAIT_START = 3 //等待开启
    };
	
public:
    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tBas.IsNull(); }
    void   SetNull( void ) { m_tBas.SetNull(); }
    
    u8     GetReservedType( void ) { return m_byIsReserved; }
    BOOL32 IsReserved ( void ) const { return ( 1 == m_byIsReserved ); }
    void   SetIsReserved ( BOOL32 bIsReserved ) { m_byIsReserved = bIsReserved ? 1 : 0; }
    BOOL32 IsTempReserved ( void ) const { return ( 2 == m_byIsReserved ); }
    void   SetIsTempReserved ( BOOL32 bIsTempReserved ) { m_byIsReserved = bIsTempReserved ? 2 : 0; } 
    void   UnReserved( void ) { m_byIsReserved = 0; }
    
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tBas ) { m_tBas = tBas; }
    TEqp   GetEqp( void ) const { return m_tBas; }
    u8     GetEqpId( void ) const { return m_tBas.GetEqpId(); }	
    void   SetType( u8 byType ) { m_byType = byType; };
    u8     GetType( void ) { return m_byType; }
	
	
    void   Print() const
    {
		// [11/4/2011 liuxu] 打印调整
//		StaticLog("Bas Eqp:\n");
//		TEqp::PrintTitle();
//		m_tBas.PrintContent();
		
//		StaticLog("\nChnnl Info:\n");
//		StaticLog("--------------------------------------\n");
// 		StaticLog("%10s %8s %8s %8s\n", "EBasStatus", "Reserved", "ChnnlIdx", "BasType");
//		StaticLog("--------------------------------------\n");
//		StaticLog("%10d %8d %8d %8d\n", m_byStatus, m_byIsReserved, m_byChnIdx, m_byType);
    }
	
private:
    TEqpNoConstruct m_tBas;
    u8 m_byStatus;	// EBasStatus
    u8 m_byIsReserved; // 0 -- not reserve, 1 -- reserve, 2 -- temply reserve
	u8 m_byChnIdx;
    u8 m_byType; // zw 20081114
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDBasVidChnStatus
用途  ：HDBas视频通道记录状态
----------------------------------------------------------------------*/
struct THDBasVidChnStatus : public THDBasChnStatus //len:39
{
private:
	THDAdaptParam m_atOutputVidParam[MAXNUM_BASOUTCHN/*MAXNUM_VOUTPUT*/]; //[03/01/2010] zjl modify 
	
public:	
    THDAdaptParam * GetOutputVidParam( u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_BASOUTCHN/*MAXNUM_VOUTPUT*/ ) //[03/01/2010] zjl modify 
        {
            return &m_atOutputVidParam[byChnIdx]; 
        }
        else
        {
            return NULL;
        }
    }
    void SetOutputVidParam(THDAdaptParam &tVidParam, u8 byChnIdx , BOOL32 bH263plusChn = FALSE, u8 byChnType = 0)
    {
		// 		if (BAS_8KECHN_MV !=byChnType && 
		// 			BAS_8KECHN_DS !=byChnType &&
		// 			BAS_8KECHN_SEL !=byChnType &&
		// 			byChnIdx < MAXNUM_VOUTPUT)
		// 		{
		// 			if ((tVidParam.GetVidType() != MEDIA_TYPE_H264 ||
		// 				(tVidParam.GetVidType() == MEDIA_TYPE_H264 && 
		// 				tVidParam.GetWidth() == 352 && tVidParam.GetHeight() == 288)
		// 			 	)
		// 		    	)
		// 			{
		// 				if (0 == byChnIdx && !bH263plusChn)
		// 				{
		// 					byChnIdx = 1;
		// 					OspPrintf(TRUE, FALSE, "[SetOutputVidParam]change outputchanl to 1 automaticly\n");
		// 				} 
		// 			}
		// 			else
		// 			{
		// 				if (byChnIdx == 1)
		// 				{
		// 					byChnIdx = 0;
		// 					OspPrintf(TRUE, FALSE, "[SetOutputVidParam]change outputchanl to 0 automaticly\n");
		// 				}
		// 			}
		// 			m_atOutputVidParam[byChnIdx] = tVidParam;
		// 		}
		// 		else if ((BAS_8KECHN_MV == byChnType || 
		// 			      BAS_8KECHN_DS == byChnType || 
		// 				  BAS_8KECHN_SEL == byChnType ) && 
		// 				  byChnIdx < MAXNUM_8KEBAS_VOUTPUT)
		// 		{
		// 			m_atOutputVidParam[byChnIdx] = tVidParam;
		// 			OspPrintf(TRUE, FALSE, "[SetOutputVidParam] SetOutputVidParam to 8kechn:%d!\n", byChnIdx);
		// 		}
		// 		else
		// 		{
		// 			OspPrintf(TRUE, FALSE, "[SetOutputVidParam] SetOutputVidParam failed! ChnType:%d, ChnIdx:%d, tVidParam<Enctype:%d, Width:%d, Height:%d>\n",
		// 				byChnType, byChnIdx, 
		// 				tVidParam.GetVidType(), tVidParam.GetWidth(), tVidParam.GetHeight());
		// 		}
		m_atOutputVidParam[byChnIdx] = tVidParam;
        return;
    }
	
	void ClrOutputVidParam()
	{
		THDAdaptParam tNullAdpParam;
		tNullAdpParam.Reset();  
		for (u8 byChnlIdx = 0; byChnlIdx < MAXNUM_BASOUTCHN/*MAXNUM_VOUTPUT*/; byChnlIdx++)
		{
			m_atOutputVidParam[byChnlIdx] = tNullAdpParam;
		}
	}
	
    void PrintInfo() const
    {
		// [11/1/2011 liuxu] 打印调整
//        StaticLog( "\nHDBasVidChnStatus info as follows:\n");
        Print();
		
//		StaticLog("\nChnnl Output Param:\n");
		m_atOutputVidParam[0].PrintTitle();
        for(u8 byIdx = 0; byIdx < MAXNUM_BASOUTCHN; byIdx ++)
        {
            m_atOutputVidParam[byIdx].PrintHd();
        }
		
//		StaticLog("\n");
    }
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：TMpu2BasStatus
用途  ：Mpu2Bas状态类，加进TPeriEqpStatus
----------------------------------------------------------------------*/
class TMpu2BasStatus
{
public:
    void SetVidChnStatus (THDBasVidChnStatus &tVidChnStatus, u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU2_EHANCED_CHN )
        {
            m_atVidChnStatus[byChnIdx] = tVidChnStatus;
        }
        return;
    }
	THDBasVidChnStatus * GetVidChnStatus(u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU2_EHANCED_CHN )
        {
            return &m_atVidChnStatus[byChnIdx];
        }
		else
        {
            return NULL;
        }
    }
    void Print() const
    {
//       StaticLog( "TMpu2BasStatus is as follows:\n");
        u8 byIdx = 0;
        for(byIdx = 0; byIdx < MAXNUM_MPU2_EHANCED_CHN; byIdx++)
        {
			if(!m_atVidChnStatus[byIdx].IsNull())
			{
				m_atVidChnStatus[byIdx].PrintInfo();
			}           
        }
    }
private:
    THDBasVidChnStatus m_atVidChnStatus[MAXNUM_MPU2_EHANCED_CHN];
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;
/*----------------------------------------------------------------------
结构名：TMpuBasStatus
用途  ：MpuBas状态类，加进TPeriEqpStatus
----------------------------------------------------------------------*/
class THdBasStatus
{
public:
    union
    {
//      TMauBasStatus tMauBas;
//      TMpuBasStatus tMpuBas;
//		T8keBasStatus t8keBas;  //[03/01/2010] zjl add 8kebas
//		T8khBasStatus t8khBas;	//[03/31/2011] nzj add 8khbas
		TMpu2BasStatus tMpu2Bas; 
    }tStatus;
	
public:
    void SetEqpType(u8 byType)
    {
        if (byType != TYPE_MPU &&
            byType != TYPE_MAU_NORMAL &&
            byType != TYPE_MAU_H263PLUS &&
			byType != TYPE_8KE_BAS &&
			byType != TYPE_8KH_BAS &&
			byType != TYPE_MPU_H &&
			byType != TYPE_MPU2_BASIC &&
			byType != TYPE_MPU2_ENHANCED)
        {
            OspPrintf(TRUE, FALSE, "[THdBasStatus][SetType] unexpected type.%d\n", m_byType);
            return;
        }
        m_byType = byType;
        return;
    }
    u8   GetEqpType(void) const { return m_byType; }
	
public:
    u8 m_byType;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;
struct TTWMember : public TMtNoConstruct
{
    u8  byMemberType;     //成员类型
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [5/25/2011 liuxu] 不必要再定义THduMember, 直接复用TTWMember即可
typedef TTWMember THduMember;
//HDU状态结构
struct THduStatus
{
    u8        byOutputMode;  //HDU_OUTPUTMODE_AUDIO : 只输出音频
	//HDU_OUTPUTMODE_VIDEO : 只输出视频
	//HDU_OUTPUTMODE_BOTH  : 同时输出音视频
    u8        byChnnlNum;    //信道数
	
    THduMember atVideoMt[MAXNUM_HDU_CHANNEL]; //每个信道对应终端，MCU号为0表示无 //???
	
	THduChnStatus atHduChnStatus[MAXNUM_HDU_CHANNEL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;
//定义数字电视墙状态结构
struct TTvWallStatus
{
    u8        byOutputMode;  //TW_OUTPUTMODE_AUDIO : 只输出音频
	//TW_OUTPUTMODE_VIDEO : 只输出视频
	//TW_OUTPUTMODE_BOTH  : 同时输出音视频
    u8        byChnnlNum;    //信道数
    TTWMember atVideoMt[16]; //每个信道对应终端，MCU号为0表示无
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//混音组状态
struct TMixerGrpStatus
{
	enum EState 
	{ 
		IDLE   = 0,		//该混音组未使用 
		READY  = 1,		//该组创建,但未开始混音
		MIXING = 2,		//正在混音
        WAIT_BEGIN = 200,
        WAIT_START_SPECMIX = 201,   //等待回应状态
        WAIT_START_AUTOMIX = 202,
        WAIT_START_VAC = 203,
        WAIT_STOP = 204,
		WAIT_START_AUTOMIXANDVAC = 205,
	};

	u8       m_byGrpId;		  //混音组ID(0-4)
	u8       m_byGrpState;	  //组状态
	u8       m_byGrpMixDepth; //混音深度
    u8       m_byConfId;      //会议ID
protected:
    u8       m_abyMixMmb[192>>3];//参与竞争混音成员列表
    u8       m_abyActiveMmb[10];//被选中的混音成员列表,0表示无效成员
public:
	u8       m_byMixGrpChnNum ;//tianzhiyong 100201 EAPU下各个混音组的通道数目
	//所有状态复位
	void Reset()
	{
		m_byGrpId       = 0xff;
		m_byGrpState    = IDLE;
		m_byGrpMixDepth = 0;
		memset( m_abyMixMmb ,0 ,sizeof(m_abyMixMmb) );
		memset( m_abyActiveMmb ,0 ,sizeof(m_abyActiveMmb) );
	}
    //添加参与竞争的混音成员
	// 若该成员ID合法返回TRUE,否则返回FALSE
    BOOL  AddMmb( u8   byMmbId)
	{
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > 192 ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] |= byMask;

		return TRUE;
	}

	//删除参与竞争的混音成员
	// 若该成员ID合法返回TRUE,否则返回FALSE
	BOOL  RemoveMmb( u8   byMmbId)
	{

		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > 192 ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] &= ~byMask;

		return TRUE;
	}

	//检测某成员是否存在于参与竞争的表中，
	//如果存在返回TRUE ,否则返回FALSE
	BOOL  IsContain( u8   byMmbId )
	{
		
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > 192 ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;
		
		return (m_abyMixMmb[byByteIdx]&byMask)==0 ? FALSE:TRUE;
	}

	//获得正在参与竞争参与混音的成员数量
	u8    GetMmbNum()
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(192>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				byNum += (m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1;
			}
		}
		return byNum;
	}

	//获得正在参与竞争的混音成员ID
	//输出 - abyMmb[] 用于存储参加混音的成员ID
	//输入 - bySize abyMmb[] 的大小
	//返回 参加混音的成员数
	u8    GetMixMmb( u8   abyMmb[] ,u8   bySize)
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(192>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				if((m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1 )
				{
					if( bySize <= byNum )
						return bySize;
					abyMmb[byNum]= byByteIdx*8+byBitIdx+1;
					byNum++;
				}
			}
		}
		return byNum;
	}
	
	//判断指定成员是否被选中混音
	BOOL IsActive( u8   byMmbId )
	{
		if( byMmbId ==0 )return FALSE;
		for( u8   byIdx =0 ;byIdx< 10 ;byIdx++ )
		{
			if( m_abyActiveMmb[byIdx]== byMmbId )
				return TRUE;
		}
		return FALSE;
	}
	
	//获得被选中混音成员个数
	u8   GetActiveMmbNum()
	{
		u8   byCount=0;
		for( u8   byIdx =0 ;byIdx< 10 ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )byCount++;
		return byCount;
	}
	
	//获得被选中混音成员
	//输出: abyMmb[] - 存储被选中混音成员ID
	//输入: bySize   - abyMmb 大小
	//返回: abyMmb中有效成员个数
	u8   GetActiveMmb( u8   abyMmb[] ,u8   bySize )
	{
		u8   byCnt=0;
    	for( u8   byIdx =0 ;byIdx< min(bySize ,10) ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )
			{
				abyMmb[byIdx] = m_abyActiveMmb[byIdx];
				byCnt++;
			}
			return byCnt;		
	}

	BOOL UpdateActiveMmb( u8   abyMmb[10] )
	{
		memcpy( m_abyActiveMmb ,abyMmb ,10);
		return TRUE;
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//混音器状态
struct TMixerStatus
{
	u8 m_byGrpNum; //混音组数量
	TMixerGrpStatus	m_atGrpStatus[5];
	u8  m_bIsMultiFormat; //tianzhiyong 100201  标记该混音器是否支持多格式
	u8  m_byMixOffChnNum ;//tianzhiyong 100201 EAPU下各个混音组的偏移通道数目
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//录像机信道状态
struct TRecChnnlStatus
{
	/*通道的状态*/
	enum ERecChnnlState
	{
		STATE_IDLE       = 0,	  /*表明是一个未用通道*/
			
			STATE_RECREADY   = 11,	  /*准备录像状态  */
			STATE_RECORDING  = 12,	  /*正在录像  */
			STATE_RECPAUSE   = 13,	  /*暂停录像状态*/
			
			STATE_PLAYREADY  = 21,	  /*准备播放状态 */
			STATE_PLAYREADYPLAY = 22,   /*作好播放准备状态*/
			STATE_PLAYING    = 23,	  /*正在或播放*/
			STATE_PLAYPAUSE  = 24,	  /*暂停播放*/
			STATE_FF         = 25,	  /*快进(仅播放通道有效)*/
			STATE_FB         = 26	  /*快退(仅播放通道有效)*/
	};
	
	/*通道类型定义*/
	enum ERecChnnlType
	{
		TYPE_UNUSE      =  0,	/*未始用的通道*/
			TYPE_RECORD     =  1,	/*录像通道  */   
			TYPE_PLAY       =  2	/*播放通道  */
	};
	
	//录像方式
	enum ERecMode
	{
		MODE_SKIPFRAME = 0,//抽帧录像
			MODE_REALTIME  = 1  //实时录像
	};
public:
	u8  		m_byType;		//通道类型：ERecChnnlType
	u8  		m_byState;		//通道状态：ERecChnnlState
	u8          m_byRecMode;    //录像方式:
	u32   		m_dwCurProg;	//当前进度
	u32   		m_dwTotalTime;	//总长度，仅在放像时有效
	TMtNoConstruct			m_tSrc;
protected:
	char	m_achRecordName[64];//记录名
	
public:
	//获取记录名
	LPCSTR GetRecordName( void ) const	{ return m_achRecordName; }
	//设置记录名
	void SetRecordName( LPCSTR lpszName ) 
	{
		strncpy( m_achRecordName, lpszName, sizeof( m_achRecordName ) );
		m_achRecordName[sizeof( m_achRecordName ) - 1] ='\0';
	}
	
	LPCSTR GetStatusStr( u8 eStatus )
	{
		switch(eStatus) 
		{
		case STATE_IDLE:
			return "IDLE";
			break;
		case STATE_RECREADY:
			return "REC Ready";
			break;
		case STATE_RECORDING:
			return "Recording";
			break;
		case STATE_RECPAUSE:
			return "REC Pause";
			break;
		case STATE_PLAYREADY:
			return "PLAY Ready";
			break;
		case STATE_PLAYING:
			return "Playing";
			break;
		case STATE_PLAYPAUSE:
			return "Play Pause";
			break;
		case STATE_FF:
			return "Play FF";
			break;
		case STATE_FB:
			return "Play FB";
		default:
			return "UNKOWN";
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//录像机状态, size = 2412
struct TRecStatus
{
protected:
	u8  	m_byRecChnnlNum;		//录像信道配置数
	u8  	m_byPlayChnnlNum;		//放像信道配置数
	u8      m_bSupportPublic;       // 是否支持发布(TRUE: 支持, FALSE:不支持)
	u8      m_byRemain;             // 保留
 	u32   	m_dwFreeSpace;        //录像机剩余磁盘空间(单位为MB)
	u32   	m_dwTotalSpace;		//录像机总磁盘空间(单位为MB)
	TRecChnnlStatus m_tChnnlStatus[32];	//先录像信道后放像信道

public:
	//获取录像通道配置
	u8   GetRecChnnlNum( void ) const	{ return( m_byRecChnnlNum ); }
	//获取放像通道配置
	u8   GetPlayChnnlNum( void ) const	{ return( m_byPlayChnnlNum ); }
	//配置通道数，录像和放像通道总数必须不大于MAXNUM_RECORDER_CHNNL
	//失败返回FALSE
	BOOL SetChnnlNum( u8   byRecChnnlNum, u8   byPlayChnnlNum )
	{
		if( byRecChnnlNum + byPlayChnnlNum <= 32 )
		{
			m_byRecChnnlNum = byRecChnnlNum;
			m_byPlayChnnlNum = byPlayChnnlNum;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong recorder and play channel number: %u and %u!\n", 
				byRecChnnlNum, byPlayChnnlNum );
			return( FALSE );
		}
	}
		/*====================================================================
    功能        ：设置录像机剩余磁盘空间
    输入参数说明：u32    dwFreeSpace  - 剩余空间大小(单位 Mb)
    返回值说明  ：无
	====================================================================*/
	void SetFreeSpaceSize( u32    dwFreeSpace )
	{
		m_dwFreeSpace  = htonl(dwFreeSpace);
	}
	
	/*====================================================================
    功能        ：获取录像机剩余磁盘空间
    输入参数说明：无
    返回值说明  ：剩余空间大小(单位 MB)
	====================================================================*/
	u32    GetFreeSpaceSize( void ) const	{ return ntohl( m_dwFreeSpace ); }

		/*====================================================================
    功能        ：设置录像机总磁盘空间
    输入参数说明：u32    dwTotalSpace  - 总空间大小(单位 MB)
    返回值说明  ：无
	====================================================================*/
	void SetTotalSpaceSize( u32    dwTotalSpace )
	{
		m_dwTotalSpace  = htonl( dwTotalSpace );
	}
	// 是否支持发布
	BOOL IsSupportPublic() const { return m_bSupportPublic;}
    // 设置是否支持发布
	void SetPublicAttribute(BOOL bSupportPublic ) { m_bSupportPublic = bSupportPublic;}

	/*====================================================================
    功能        ：获取录像机总磁盘空间
    输入参数说明：无
    返回值说明  ：总空间大小(单位 MB)
	====================================================================*/
	u32    GetTotalSpaceSize( void ) const	{ return ntohl( m_dwTotalSpace ); }

	//设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
	BOOL SetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, const TRecChnnlStatus * ptStatus );
	//设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
	BOOL GetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, TRecChnnlStatus * ptStatus ) const;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//录像方式定义
#define		 REC_MODE_NORMAL				0   /* 实时录像 */
#define	     REC_MODE_SKIPFRAME				1	/* 抽帧录像 */

//有关发布方式定义
#define      PUBLISH_MODE_NONE				0	//不发布
#define      PUBLISH_MODE_IMMED				1	//立即发布
#define      PUBLISH_MODE_FIN				2	//录像完毕之后发布

//发布级别
#define      PUBLISH_LEVEL_NORMAL			0	//正常发布
#define      PUBLISH_LEVEL_SECRET			1	//秘密发布

//录像文件类型
#define      RECFILE_NORMAL                 0   //单格式录像文件
#define      RECFILE_DSTREAM                1   //双格式录像文件

struct TPlayFileAttrib
{
protected:
    u8 m_byFileType;
    u8 m_byAudioType;
    u8 m_byVideoType;
    u8 m_byDVideoType;
	
public:
    TPlayFileAttrib(void)
    {
        m_byFileType = RECFILE_NORMAL;
        m_byAudioType = MEDIA_TYPE_NULL;
        m_byVideoType = MEDIA_TYPE_NULL;
        m_byDVideoType = MEDIA_TYPE_NULL;
    }
	
    BOOL32 IsDStreamFile(void) const
    {
        return (RECFILE_DSTREAM == m_byFileType) ? TRUE : FALSE;
    }
    u8 GetFileType(void) const
    {
        return m_byFileType;
    }
    void SetFileType(u8 byFileType)
    {
        m_byFileType = byFileType;
    }
	
    u8 GetAudioType(void) const
    {
        return m_byAudioType;
    }
    void SetAudioType(u8 byAudioType)
    {
        m_byAudioType = byAudioType;
    }
	
    u8 GetVideoType(void) const
    {
        return m_byVideoType;
    }
    void SetVideoType(u8 byVideoType)
    {
        m_byVideoType = byVideoType;
    }
	
    u8 GetDVideoType(void) const
    {
        return m_byDVideoType;
    }
    void SetDVideoType(u8 byDVideoType)
    {
        m_byDVideoType = byDVideoType;
    }
    
    void Print() const
    {
        //StaticLog( "m_byFileType: %d\n", m_byFileType);
        //StaticLog( "m_byAudioType: %d\n", m_byAudioType);
        //StaticLog( "m_byVideoType: %d\n", m_byVideoType);
        //StaticLog( "m_byDVideoType: %d\n", m_byDVideoType);
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

// zgc, 2008-08-02, MCU的放像文件媒体信息
struct TPlayFileMediaInfo
{
    enum emStreamType
    {
        emAudio = 0,
			emVideo,
			emDVideo,
			emEnd
    };
	
private:
    //流的个数
    u8 m_byNum;
    //流的类型
    u8 m_abyMediaType[emEnd];
    u16	m_awWidth[emEnd];
	u16 m_awHeight[emEnd];
	
public:
    void clear( void )
    {
        m_byNum = 0;
        for ( u8 byLop = 0; byLop < emEnd; byLop++ )
        {
            m_abyMediaType[byLop] = MEDIA_TYPE_NULL;
            m_awWidth[byLop] = 0;
            m_awHeight[byLop] = 0;
        }
    }
    void SetStreamNum( u8 byNum ) { m_byNum = byNum; }
    u8   GetStreamNum( void ) const { return m_byNum; }
    void SetAudio( u8 byAudioType ) { m_abyMediaType[emAudio] = byAudioType; }
    u8   GetAudio( void ) const { return m_abyMediaType[emAudio]; }
    void SetVideo( u8 byVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emVideo] = byVideoType; 
        m_awWidth[emVideo] = htons(wWidth);
        m_awHeight[emVideo] = htons(wHeight);
        return;
    }
    void GetVideo( u8 &byVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byVideoType = m_abyMediaType[emVideo]; 
        wWidth = ntohs(m_awWidth[emVideo]);
        wHeight = ntohs(m_awHeight[emVideo]);
        return;
    }
    void SetDVideo( u8 byDVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emDVideo] = byDVideoType; 
        m_awWidth[emDVideo] = htons(wWidth);
        m_awHeight[emDVideo] = htons(wHeight);
        return;
    }
    void GetDVideo( u8 &byDVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byDVideoType = m_abyMediaType[emDVideo]; 
        wWidth = ntohs(m_awWidth[emDVideo]);
        wHeight = ntohs(m_awHeight[emDVideo]);
        return;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

// size = 11
struct TRecStartPara
{
protected:
    u8   m_byRecMode;         //录像模式
    u8   m_byPublishMode;     //发布模式
    u8   m_byPublishLevel;    //发布层次
    u8   m_byIsRecLowStream;  //是否录低速码流
    u8   m_byIsRecMainVideo;  //是否录主格式视频码流
    u8   m_byIsRecMainAudio;  //是否录主格式音频码流
    u8   m_byIsRecDStream;    //是否录双流
	u16  m_wRecBitrate;       //录像码率
    u16  m_wRecBitrateSec;    //录像双流码率

public:
	//lukunpeng 2010/07/14 此结构需放到Union中，不能有构造函数
// 	TRecStartPara()
// 	{
// 		Reset();
// 	}
	void Reset(void)
	{
		m_byRecMode = REC_MODE_NORMAL;
		m_byPublishMode = PUBLISH_MODE_FIN;
		m_byPublishLevel = PUBLISH_LEVEL_NORMAL;
        m_byIsRecMainVideo = 1;
        m_byIsRecMainAudio = 1;
        m_byIsRecDStream   = 1;
        m_byIsRecLowStream = 0;
        m_wRecBitrate      = 0;
        m_wRecBitrateSec   = 0;
	}
	void SetRecMode(u8 byMode)
	{
		m_byRecMode = byMode;
	}
	u8 GetRecMode(void) const
	{
		return m_byRecMode;
	}
	void SetPublishMode(u8 byMode)
	{
		m_byPublishMode = byMode;
	}
	u8 GetPublishMode(void) const
	{
		return m_byPublishMode;
	}
    void SetPublishLevel(u8 byLevel)
	{
		m_byPublishLevel = byLevel;
	}
	u8  GetPublishLevel(void) const
	{
		return m_byPublishLevel;
	}
    void SetIsRecLowStream(BOOL32 bRecLowStream)
	{
		m_byIsRecLowStream = ( bRecLowStream ? 1:0);
	}
	BOOL32 IsRecLowStream(void) const 
	{
		return (m_byIsRecLowStream != 0);
	}

    void SetIsRecMainVideo(BOOL32 bRecMainVideo)
	{
		m_byIsRecMainVideo = (bRecMainVideo ? 1:0);
	}
	BOOL32 IsRecMainVideo(void) const
	{
		return (m_byIsRecMainVideo != 0);
	}

    void SetIsRecMainAudio(BOOL32 bRecMainAudio)
	{
		m_byIsRecMainAudio = (bRecMainAudio ? 1:0);
	}
	BOOL32 IsRecMainAudio(void) const
	{
		return (m_byIsRecMainAudio != 0);
	}

    void SetIsRecDStream(BOOL32 bRecDStream)
	{
		m_byIsRecDStream = (bRecDStream ? 1:0);
	}
	BOOL32 IsRecDStream(void) const
	{
		return (m_byIsRecDStream != 0);
	}

	void SetBitRate(u16 wBitRate)
	{
		m_wRecBitrate = htons(wBitRate);
	}
	u16 GetBitRate(void) const
	{
		return ntohs(m_wRecBitrate);
	}

    void SetSecBitRate(u16 wBitRate)
    {
        m_wRecBitrateSec = htons(wBitRate);
    }
    u16 GetSecBitRate(void) const
    {
        return ntohs(m_wRecBitrateSec);
    }

//     void Print() const
//     {
//         
//         StaticLog("m_byRecMode:        %d\n", GetRecMode());
//         StaticLog("m_byPublishMode:    %d\n", GetPublishMode());
//         StaticLog("m_byPublishLevel:   %d\n", GetPublishLevel());
//         StaticLog("m_byIsRecMainVideo: %d\n", IsRecMainVideo());
//         StaticLog("m_byIsRecMainAudio: %d\n", IsRecMainAudio());
//         StaticLog("m_byIsRecLowStream: %d\n", IsRecLowStream());
//         StaticLog("m_byIsRecDStream:   %d\n", IsRecDStream());
//         StaticLog("m_wRecBitrate:      %d\n", GetBitRate());
//         StaticLog("m_wSecRecBitrate:   %d\n", GetSecBitRate());
// 
//     }

}
#ifndef WIN32
__attribute__((packed))
#endif
;

#define     MAXLEN_RECORD_NAME              64  //上报外设状态时录像文件名的长度
#define		MAXLEN_CONFNAME                 64   //会议名最大长度
#define		RECLIST_PACKSIZE					(u8)16
struct TRecFileListNotify
{
	u16 wListSize;//录像机中文件总数
	u16 wStartIdx;//本通知中起始文件序号
	u16 wEndIdx;  //本通知中结束文件序号
    
	s8 achFileName[RECLIST_PACKSIZE][MAXLEN_CONFNAME+MAXLEN_RECORD_NAME+1];
	u8 abyStatus[RECLIST_PACKSIZE];
public:
	TRecFileListNotify()
	{
		wListSize = 0;
		wStartIdx = 0;
		wEndIdx   = 0;
		memset ( achFileName ,0,sizeof(achFileName) );
		memset( abyStatus ,0 ,sizeof(abyStatus) );
	}

	//获取录像机记录总数
	u16 GetListSize()
	{
		return ntohs(wListSize);
	}
	
	//获取本通知中起始文件序号
	u16 GetStartIdx()
	{
		return ntohs(wStartIdx);
	}

	//获取本通知中起始文件序号
	u16 GetEndIdx()
	{
		return ntohs(wEndIdx);
	}

	//获得指定序号的文件名,如不存在返回NULL
	char* GetFileName(u16 wIdx )
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return NULL;
		return achFileName[wIdx - GetStartIdx()];
	}

	//判断指定序号的文件是否发布
	BOOL IsPublic(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;
		return abyStatus[wIdx - GetStartIdx()]&0x1 ? TRUE:FALSE;
	}

	//设置指定序号的文件发布
	BOOL Public(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;

		abyStatus[wIdx - GetStartIdx()] |=0x1;
		return TRUE;
	}

	/////////////////////////////////////////////
	//设置录像机记录总数
	void Reset()
	{
		wListSize = 0;
	    wStartIdx =0;
	    wEndIdx =0;
	    memset( achFileName,0,sizeof(achFileName) );
		memset( abyStatus , 0,sizeof(abyStatus) );
	}
	void SetListSize( u16 wSize)
	{
		wListSize = htons(wSize);
	}
	
	//设置本通知中起始文件序号
	void SetStartIdx( u16 wIdx)
	{
		wStartIdx = htons(wIdx);
	}

	//设置本通知中起始文件序号
	void SetEndIdx( u16 wIdx)
	{
		wEndIdx = htons(wIdx);
	}

	// 添加文件
	BOOL AddFile(char* filename ,BOOL bPublic = FALSE )
	{
		if ( IsFull() )
			return FALSE;

        u16 wIdx = GetEndIdx() - GetStartIdx();

		strncpy( achFileName[wIdx], filename ,sizeof(achFileName[wIdx]) - 1);
		achFileName[wIdx][sizeof(achFileName)-1]='\0';

		if ( bPublic ) 
        {
            abyStatus[wIdx] |=0x1;
        }
		else 
        {
            abyStatus[wIdx] &=~0x01;
        }

        // 序号自动增量
        SetEndIdx( GetEndIdx() + 1 );
		return TRUE;
	}

	//判断缓存是否已满
	BOOL32 IsFull()
	{
		u16 wSize = GetEndIdx() - GetStartIdx();
		if( wSize >= RECLIST_PACKSIZE )
			return TRUE;
		return FALSE;
	}

    BOOL32 IsEmpty()
    {
        return (GetEndIdx() == GetStartIdx());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//适配器启动的模块
struct TBasCapSet
{
public:
    u8 m_bySupportAudio;
    u8 m_bySupportVideo;
    u8 m_bySupportBitrate;
	
public:
    void SetAudioCapSet(BOOL32 bSupportAudio)
    {
        if (TRUE == bSupportAudio)
        {
            m_bySupportAudio = 1;
        }
        else
        {
            m_bySupportAudio = 0;
        }
    }
	
    BOOL32 IsSupportAudio(void)
    {
        if (0 == m_bySupportAudio)
        {
            return FALSE;
        }
        return TRUE;
    }
	
    void SetVideoCapSet(BOOL32 bSupportVideo)
    {
        if (TRUE == bSupportVideo)
        {
            m_bySupportVideo = 1;
        }
        else
        {
            m_bySupportVideo = 0;
        }
    }
	
    BOOL32 IsSupportVideo(void)
    {
        if (0 == m_bySupportVideo)
        {
            return FALSE;
        }
        return TRUE;
    }
	
    void SetBitrateCapSet(BOOL32 bSupportBitrate)
    {
        if (TRUE == bSupportBitrate)
        {
            m_bySupportBitrate = 1;
        }
        else
        {
            m_bySupportBitrate = 0;
        }
    }
	
    BOOL32 IsSupportBitrate(void)
    {
        if (0 == m_bySupportBitrate)
        {
            return FALSE;
        }
        return TRUE;
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//适配器通道状态结构
struct TBasChnStatus : TAdaptParam
{
    enum EBasStatus
    {
        IDLE   = 0,		//空闲
			READY  = 1,		//准备适配
			RUNING = 2,		//正在适配
			WAIT_START = 3  //等待开启
    };
	
protected:
    u8 m_byStatus;
	u8 m_byReserved;    //是否为保留通道
    u8 m_byChanType;    //音频通道: 1(BAS_CHAN_AUDIO)  视频通道: 2(BAS_CHAN_VIDEO)
	
public:
	
    void SetStatus(u8 byStatus)
    {
        m_byStatus = byStatus;
    }
	
    u8 GetStatus(void)
    {
        return m_byStatus;
    }
	
    void SetReserved(BOOL32 bReserved)
    {
        m_byReserved = (TRUE == bReserved) ? 1 : 0;
    }
	
    BOOL32 IsReserved(void)
    {
        return (0 != m_byReserved);
    }
	
    u8 GetChannelType(void)
    {
        return m_byChanType;
    }
	
    void SetChannelType(u8 byBasChanType)
    {
        m_byChanType = byBasChanType;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

//适配器通道状态结构
struct TBasStatus
{
	u8            byChnNum;
    TBasCapSet    tBasCapSet;
    TBasChnStatus tChnnl[32]; //
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//重传设备状态 (len:3)
struct TPrsPerChStatus
{
public:
	u8  byUsed;         //0--未创建，1--创建
	u8	byCount;	    //多少个反馈端
	u8  byChlReserved;  //是否为保留通道
	u8  byConfIndex;		//记录通道服务的会议Idx, zgc, 2007/04/24
public:
    void   SetUsed( void ){ byUsed = 1; }
    void   SetIdle( void ){ byUsed = 0; }
    BOOL   IsUsed( void ){ return byUsed; }
    
    u8     GetFeedNum( void ){ return byCount; }
    void   FeedNumAdd( void ){ byCount++; }
    void   FeedNumDec( void ){ byCount--; }
	
	void   SetReserved( BOOL bReserved ){ byChlReserved = bReserved; }
	BOOL   IsReserved( void ){ return byChlReserved; }
	
	//记录通道服务的会议Idx, zgc, 2007/04/24
	void   SetConfIdx( u8 byConfIdx )
	{
		if( byConfIdx > 64 )
		{
			OspPrintf( TRUE, FALSE, "The conf idx %d is error!\n", byConfIdx );
			return;
		}
		byConfIndex = byConfIdx; 
	}
	u8	   GetConfIdx( void ){ return byConfIndex; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//重传结构
struct TPrsStatus
{
public:
	TPrsPerChStatus   m_tPerChStatus[16];		//本地接收RTP/RTCP包的地址
	u8 GetIdleChlNum(void)
	{
		u8 nSum = 0;
		for(u8 byLp = 0; byLp < 16; byLp++)
		{
			if( !m_tPerChStatus[byLp].IsReserved() )
			{
				nSum++;
			}
		}
		return nSum;
	}
	
	//记录通道服务的会议Idx, zgc, 2007/04/24
	void SetChnConfIdx( u8 byChnIdx, u8 byConfIdx )
	{ 
		if( byChnIdx > 16 || byConfIdx > 64 )
		{
			OspPrintf( TRUE, FALSE, "The chn idx %d or conf idx %d is error!\n", byChnIdx, byConfIdx );
			return;
		}
		m_tPerChStatus[byChnIdx].SetConfIdx(byConfIdx); 
	}
	u8   GetChnConfIdx( u8 byChnIdx ){ return m_tPerChStatus[byChnIdx].GetConfIdx(); }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDBasChnStatus
用途  ：HDBas适配通道
----------------------------------------------------------------------*/
struct TBasBaseChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0,    //空闲
			READY  = 1,    //准备适配
			RUNING = 2,    //正在适配
			WAIT_START = 3 //等待开启
    };
	
public:
    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tBas.IsNull(); }
    void   SetNull( void ) { m_tBas.SetNull(); }
    
    u8     GetReservedType( void ) { return m_byIsReserved; }
    BOOL32 IsReserved ( void ) const { return ( 1 == m_byIsReserved ); }
    void   SetIsReserved ( BOOL32 bIsReserved ) { m_byIsReserved = bIsReserved ? 1 : 0; }
    BOOL32 IsTempReserved ( void ) const { return ( 2 == m_byIsReserved ); }
    void   SetIsTempReserved ( BOOL32 bIsTempReserved ) { m_byIsReserved = bIsTempReserved ? 2 : 0; } 
    void   UnReserved( void ) { m_byIsReserved = 0; }
    
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tBas ) { m_tBas = tBas; }
    TEqp   GetEqp( void ) const { return m_tBas; }
    u8     GetEqpId( void ) const { return m_tBas.GetEqpId(); }	
    void   SetType( u8 byType ) { m_byType = byType; };
    u8     GetType( void ) { return m_byType; }
	
	
//     void   Print() const
//     {
// 		// [11/4/2011 liuxu] 打印调整
// 		StaticLog("Bas Eqp:\n");
// 		TEqp::PrintTitle();
// 		m_tBas.PrintContent();
// 		
// 		StaticLog("\nChnnl Info:\n");
// 		StaticLog("--------------------------------------\n");
// 		StaticLog("%10s %8s %8s %8s\n", "EBasStatus", "Reserved", "ChnnlIdx", "BasType");
// 		StaticLog("--------------------------------------\n");
// 		StaticLog("%10d %8d %8d %8d\n", m_byStatus, m_byIsReserved, m_byChnIdx, m_byType);
//     }
	
private:
    TEqpNoConstruct m_tBas;
    u8 m_byStatus;	// EBasStatus
    u8 m_byIsReserved; // 0 -- not reserve, 1 -- reserve, 2 -- temply reserve
	u8 m_byChnIdx;
    u8 m_byType; // zw 20081114
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

struct TAudAdaptParam 
{
private:
	u8	m_byAudCodeType;
	u8	m_byAudActiveTpye;
	u8	m_byTrackNum;
	u8  m_byIsNeedPrs;
	u8	m_byReserve1;
	u8	m_byReserve2;
	
public:
	//设置音频编码类型
	void SetAudCodeType( u8 byAudCodeType )
	{
		m_byAudCodeType = byAudCodeType;
	}
	
	u8 GetAudCodeType()
	{
		return m_byAudCodeType;
	}
	
	//设置音频编码活动载荷
	void SetAudActiveType( u8 byAudActiveType )
	{
		m_byAudActiveTpye = byAudActiveType;
	}
	
	u8 GetAudActiveType()
	{
		return m_byAudActiveTpye;
	}
	
	//设置音频编码声道数
	void SetTrackNum( u8 byTrackNum )
	{
		m_byTrackNum = byTrackNum;
	}
	
	u8 GetTrackNum( )
	{
		return m_byTrackNum;
	}
	
	
	void SetIsNeedByPrs(BOOL32 bNeedPrs)
	{
		m_byIsNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
	}
	
	BOOL32 IsNeedbyPrs(void)
	{
		return (0 != m_byIsNeedPrs);
	}
	
	
    void Clear(void)
    {
        m_byAudCodeType = MEDIA_TYPE_NULL;
		m_byAudActiveTpye = MEDIA_TYPE_NULL;
		m_byTrackNum = 0;
    }
	
	BOOL32 IsNull()
	{
		if ( m_byAudCodeType == MEDIA_TYPE_NULL)
		{
			return TRUE;
		}
		return FALSE;
	}
	
// 	void PrintTitle() const 
// 	{
// 		StaticLog("--------------------------------------------------------------------------------\n");
// 		StaticLog( "%7s ", "CodType");
// 		StaticLog( "%7s ", "ActType");
// 		StaticLog( "%7s ", "TrackNm");
// 		StaticLog( "%7s \n","NeedPrs");
// 		StaticLog("--------------------------------------------------------------------------------\n");
// 	}
// 	
//     void PrintParam(void) const
//     {
//         StaticLog( "%7d ", m_byAudCodeType);
// 		StaticLog( "%7d ", m_byAudActiveTpye);
// 		StaticLog( "%7d",  m_byTrackNum);
// 		StaticLog( "%7d\n", m_byIsNeedPrs);
//     }
// 	
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

//BAS音频通道状态
struct TAudBasChnStatus:public TBasBaseChnStatus
{
public:
    TAudAdaptParam  m_atOutPutAudParam[MAXNUM_BASOUTCHN];   //适配通道编码输出数组
public:
    TAudAdaptParam* GetOutputAudParam( u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_BASOUTCHN )
        {
            return &m_atOutPutAudParam[byChnIdx]; 
        }
        else
        {
            return NULL;
        }
    }
    void SetOutputAudParam(TAudAdaptParam &tVidParam, u8 byChnIdx)
    {
        m_atOutPutAudParam[byChnIdx] = tVidParam;
        return;
    }
    
    void ClrOutputAudParam()
    {
        TAudAdaptParam tNullAdpParam;
        tNullAdpParam.Clear();  
        for (u8 byChnlIdx = 0; byChnlIdx < MAXNUM_BASOUTCHN; byChnlIdx++)
        {
            m_atOutPutAudParam[byChnlIdx] = tNullAdpParam;
        }
    }
    
//     void PrintInfo() const
//     {
//         StaticLog( "\nAudChnStatus info as follows:\n");
//         Print();
//         
//         StaticLog("\nChnnl Output Param:\n");
//         m_atOutPutAudParam[0].PrintTitle();
//         for(u8 byIdx = 0; byIdx < MAXNUM_BASOUTCHN; byIdx ++)
//         {
//             m_atOutPutAudParam[byIdx].PrintParam();
//         }
//         
//         StaticLog("\n");
//     }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//apu2-bas外设状态
struct TApu2BasStatus
{
public:
    TAudBasChnStatus m_atAudChnStatus[MAXNUM_APU2_BASCHN];  //APU2 BAS外设通道数组
public:
    void SetAudChnStatus (TAudBasChnStatus &tAudChnStatus, u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_APU2_BASCHN )
        {
            m_atAudChnStatus[byChnIdx] = tAudChnStatus;
        }
        return;
    }
    TAudBasChnStatus * GetAudChnStatus(u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_APU2_BASCHN )
        {
            return &m_atAudChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
//     void Print() const
//     {
//         StaticLog( "TApu2BasStatus is as follows:\n");
//         u8 byIdx = 0;
//         for(byIdx = 0; byIdx < MAXNUM_APU2_BASCHN; byIdx++)
//         {
//             if(!m_atAudChnStatus[byIdx].IsNull())
//             {
//                 m_atAudChnStatus[byIdx].PrintInfo();
//             }           
//         }
//     }
}
#ifndef WIN32
__attribute__((packed))
#endif
;





//apu2-bas外设状态
struct T8kiAudBasStatus
{
public:
    TAudBasChnStatus m_atAudChnStatus[MAXNUM_8KI_AUD_BASCHN];  //APU2 BAS外设通道数组
public:
    void SetAudChnStatus (TAudBasChnStatus &tAudChnStatus, u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_8KI_AUD_BASCHN )
        {
            m_atAudChnStatus[byChnIdx] = tAudChnStatus;
        }
        return;
    }
    TAudBasChnStatus * GetAudChnStatus(u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_8KI_AUD_BASCHN )
        {
            return &m_atAudChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
//     void Print() const
//     {
//         StaticLog( "T8kiAudBasStatus is as follows:\n");
//         u8 byIdx = 0;
//         for(byIdx = 0; byIdx < MAXNUM_8KI_AUD_BASCHN; byIdx++)
//         {
//             if(!m_atAudChnStatus[byIdx].IsNull())
//             {
//                 m_atAudChnStatus[byIdx].PrintInfo();
//             }           
//         }
//     }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

struct TAudBasStatus
{
public:
	union
	{
		u8 m_abyArray[910];//zjj20130922 为了和hdbas结构大小一致(要读下面的m_byType),所以增加这个结构
		TApu2BasStatus m_tApu2BasChnStatus;
		T8kiAudBasStatus m_t8KIAudBasStatus;
	}m_tAudBasStaus;
	
public:
    void SetEqpType(u8 byType)
    {
        if (byType != TYPE_APU2_BAS && byType != TYPE_8KI_AUD_BAS)
        {
            OspPrintf(TRUE, FALSE, "[TAudBasStatus][SetType] unexpected type.%d\n", m_byType);
            return;
        }
        m_byType = byType;
        return;
    }
    u8   GetEqpType(void) const { return m_byType; }
    
public:
    u8 m_byType;
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//定义外设状态结构, size = 2435(TRecStatus = 2412)
struct TPeriEqpStatus : public TEqp
{
public:
	u8  	m_byOnline;		//是否在线
	union UStatus
	{
		TTvWallStatus	tTvWall;//此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
		TMixerStatus	tMixer; //此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
		TVmpStatus      tVmp;	
		TRecStatus		tRecorder;//此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
		TBasStatus		tBas;//此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
		TPrsStatus		tPrs;//此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
        THdBasStatus    tHdBas;
		THduStatus      tHdu;//此结构体，如果要使用，请自己到mcu处取。此处定义不准确   ums  diaolei
		TAudBasStatus	tAudBas;
	} m_tStatus;
	
protected:
	char    m_achAlias[MAXLEN_EQP_ALIAS];
public:
	//constructor
	TPeriEqpStatus( void )
	{
		memset(this, 0, sizeof(TPeriEqpStatus));
	}
	
	//获取外设别名
	const s8 * GetAlias() const 
	{ 
		return m_achAlias;
	}
	
	//设置外设别名
	void SetAlias(const s8 * lpszAlias)
	{ 
		strncpy(m_achAlias, lpszAlias, sizeof(m_achAlias));
		m_achAlias[MAXLEN_EQP_ALIAS-1] = '\0';
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
// 画面合成成员结构(Mcu -- Vmp)
struct TVMPMemberEx : public TVMPMember
{
#define VALIDLEN_ALIAS 16
public:
	void  SetMember( TVMPMember& tMember )
	{
		memcpy(this, &tMember, sizeof(tMember));
	}

	BOOL  SetMbAlias( const s8 *pAlias ) 
    { 
        BOOL bRet = FALSE;
        if( NULL != pAlias )
        {
            memcpy(achMbAlias, pAlias, sizeof(achMbAlias));
            achMbAlias[VALIDLEN_ALIAS] = '\0';
            bRet = TRUE;
        }
		s8 nLen = strlen(achMbAlias);
        s8 nLoop = nLen - 1;
        u8 byWideCharCount = 0;
        while ( (signed char)nLoop >= 0  && (signed char)0 > (signed char)achMbAlias[nLoop])
        {
            byWideCharCount ++;
            nLoop --;
        }
        if ( byWideCharCount % 2 == 1 )
        {
            achMbAlias[nLen-1] = '\0';
        }
        return bRet; 
    }
	const s8* GetMbAlias(void) { return achMbAlias; }

protected:
	s8   achMbAlias[VALIDLEN_ALIAS+1];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成配置信息
struct TVmpStyleCfgInfo
{
#define MAX_VMPSTYLE_ALIASLEN 32
protected:
    u8  m_bySchemeId;                   //方案id，1－5
	u8	m_byRimEnabled;					//是否使用边框: 0-不使用(默认) 1-使用;
										//本字段目前只对方案0有效, 其他方案暂不涉及本字段的设置和判断
	u8	m_byReserved1;					//保留字段1
	u8	m_byReserved2;					//保留字段2
    u32 m_dwBackgroundColor;            //图像背景色
    u32 m_dwFrameColor;                 //图像边框色
    u32 m_dwSpeakerFrameColor;          //发言人边框色
    u32 m_dwChairFrameColor;            //主席边框色 
	u8  m_byFontType;                   // 合成主题字体
	u8  m_byFontSize;					// 合成主题字号
	u8  m_byAlignment;                  // 对齐方式
	u32  m_dwTextColor;                  // 合成主题文字颜色
	u32  m_dwTopicBkColor;               // 合成主题背景色
	u32  m_dwDiaphaneity;                // 合成主题透明度
    s8  m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN];  // 画面合成方案别名

public:
    TVmpStyleCfgInfo(void) { Clear();   }

	void	Clear(void)  { memset(this, 0, sizeof(TVmpStyleCfgInfo)); }
	void	SetNull(void) { Clear(); }
	BOOL32  IsNull(void) 
    { 
        TVmpStyleCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TVmpStyleCfgInfo)));
    }
    void    SetSchemeId(u8 bySchemeId) { m_bySchemeId = bySchemeId; }
    u8      GetSchemeId(void) { return m_bySchemeId; }    
    void    SetBackgroundColor(u32 dwColor) { m_dwBackgroundColor = htonl(dwColor); }
    u32     GetBackgroundColor(void) { return ntohl(m_dwBackgroundColor); }
    void    SetFrameColor(u32 dwColor) { m_dwFrameColor = htonl(dwColor); }
    u32     GetFrameColor(void) { return ntohl(m_dwFrameColor); }
    void    SetSpeakerFrameColor(u32 dwColor) { m_dwSpeakerFrameColor = htonl(dwColor); }
    u32     GetSpeakerFrameColor(void) { return ntohl(m_dwSpeakerFrameColor); }
    void    SetChairFrameColor(u32 dwColor) { m_dwChairFrameColor = htonl(dwColor); }
    u32     GetChairFrameColor(void) { return ntohl(m_dwChairFrameColor); }
	void	SetIsRimEnabled(BOOL32 bEnabled){ m_byRimEnabled = GETBBYTE(bEnabled); }
	BOOL32	GetIsRimEnabled(void) const { return m_byRimEnabled == 1 ? TRUE : FALSE; }
	void    SetFontType(u8 byFontType) { m_byFontType = byFontType;}
	u8      GetFontType(void) { return m_byFontType;}
	void    SetFontSize(u8 byFontSize ) { m_byFontSize = byFontSize;}
	u8      GetFontSize(void) { return m_byFontSize;}
	void    SetAlignment(u8 byValue ) { m_byAlignment = byValue;}
	u8      GetAlignment(void) { return m_byAlignment;}
	void    SetTextColor(u32 dwTextColor ) { m_dwTextColor = htonl(dwTextColor);}
	u32     GetTextColor(void) { return ntohl(m_dwTextColor);}
	void    SetTopicBkColor(u32 dwBkColor) { m_dwTopicBkColor = htonl(dwBkColor);}
	u32     GetTopicBkColor(void) { return ntohl(m_dwTopicBkColor);}
	void    SetDiaphaneity(u32 dwDiaphaneity ) { m_dwDiaphaneity = htonl(dwDiaphaneity); }
	u32     GetDiaphaneity(void) { return ntohl(m_dwDiaphaneity);}

    void    SetSchemeAlias(s8* pchSchemeAlias)
    {
        memcpy(m_achSchemeAlias, pchSchemeAlias, sizeof(m_achSchemeAlias));
        m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN-1] = '\0';
    }
    
    void    GetSchemeAlias(s8* pchSchemeAlias, u8 byBufferLen)
    {
        u8 byAliasLen = (byBufferLen < sizeof(m_achSchemeAlias) ) ? byBufferLen : sizeof(m_achSchemeAlias);
        memcpy(pchSchemeAlias, m_achSchemeAlias, byAliasLen);
    }
    
    void    ResetDefaultColor(void)
    {
        SetBackgroundColor(VMPSTYLE_DEFCOLOR);
        SetSpeakerFrameColor(VMPSTYLE_DEFCOLOR);
        SetChairFrameColor(VMPSTYLE_DEFCOLOR);
        SetFrameColor(VMPSTYLE_DEFCOLOR);
		SetFontType(FONT_SONG);
		SetFontSize(FONT_SIZE_24);
		SetAlignment(MIDDLE_ALIGN);
		SetTextColor(DEFAULT_TEXT_COLOR);
		SetTopicBkColor(DEFAULT_BACKGROUND_COLOR);
		SetDiaphaneity(DEFAULT_DIAPHANEITY);
    }

	inline BOOL operator == (const TVmpStyleCfgInfo& tVmpStyle )
	{
		BOOL bRet = TRUE;
		if( this == &tVmpStyle )
		{
			return bRet;
		}
		
		if ( 0 != memcmp(this, &tVmpStyle, sizeof(TVmpStyleCfgInfo)) )
		{
			bRet = FALSE;
		}
		return bRet;
	}

    void    Print(void)
    {	
//		StaticLog( "VmpStyleInfo(SchemeId:%d)\n BackColor:0x%x, AudienceColor:0x%x, SpeakerColor:0x%x, ChairColor:0x%x, IsRimEnabled:%d\n",
//			GetSchemeId(), GetBackgroundColor(), GetFrameColor(), GetSpeakerFrameColor(), GetChairFrameColor(), GetIsRimEnabled() );
//		StaticLog( "VmpStyleInfo: \n FontType:%d, FontSize:%d, TextColor:0x%x, BkColor:0x%x, Diaphaneity:0x%x\n",
//			GetFontType(), GetFontSize(), GetTextColor(), GetTopicBkColor(), GetDiaphaneity() );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// VMP扩展配置
struct TVMPExCfgInfo
{
	u8 m_byIdleChlShowMode;  // 空闲通道显示模式 VMP_SHOW_GRAY_MODE
	
	u8  m_byIsDisplayMmbAlias; // 是否显示别名（1 为显示；0为不显示）
	u16 m_wReserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
struct TVmpCommonAttrb
{
	u8	m_byVmpStyle;	//合成风格
	u8	m_byMemberNum;	//成员数量
	u8	m_byNeedPrs;	//是否需要PRS
	TVMPMemberEx		m_atMtMember[MAXNUM_VMP_MEMBER];		//复合成员
	TMediaEncrypt		m_tVideoEncrypt[MAXNUM_VMP_MEMBER];     //视频加密参数
	TDoublePayload		m_tDoublePayload[MAXNUM_VMP_MEMBER];	//双载荷
	TVmpStyleCfgInfo	m_tVmpStyleCfgInfo;		//配置信息
	TVMPExCfgInfo		m_tVmpExCfgInfo;		//扩展配置信息
	
	TVmpCommonAttrb()
	{
		memset(this, 0, sizeof(TVmpCommonAttrb));
	}
	
    void Print(void)
    {
//         StaticLog( "VmpStyle:%d, MemberNum:%d, NeedPrs:%d\n",
// 			m_byVmpStyle, m_byMemberNum, m_byNeedPrs);
//         for(u8 byIndex = 0; byIndex < MAXNUM_VMP_MEMBER; byIndex++)
//         {
//             if(0 != m_atMtMember[byIndex].GetMcuId() && 0 != m_atMtMember[byIndex].GetMtId())
//             {
//                 StaticLog( "McuId:%d, MtId:%d, MemType:%d, MemStatus:%d, RealPayLoad:%d, ActPayLoad:%d, EncrptMode:%d\n", 
// 					m_atMtMember[byIndex].GetMcuId(), m_atMtMember[byIndex].GetMtId(), 
// 					m_atMtMember[byIndex].GetMemberType(), m_atMtMember[byIndex].GetMemStatus(),
// 					m_tDoublePayload[byIndex].GetRealPayLoad(), m_tDoublePayload[byIndex].GetActivePayload(),
// 					m_tVideoEncrypt[byIndex].GetEncryptMode());
//             }            
//         }        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//VMP后适配参数(MCU与VMP通讯用)
class CKDVVMPOutMember
{
private:
	u8    	        m_byEncType;		//图像编码类型
	u8    	        m_byProfileType;	//BP/HP
	u8				m_byFrameRate;		//帧率
	u16             m_wBitRate;			//编码比特率(Kbps)
	u16   	        m_wVideoWidth;		//图像宽度(default:720)
	u16   		    m_wVideoHeight;		//图像高度(default:576)
public:
	void Clear() { memset(this, 0, sizeof(CKDVVMPOutMember)); }
	void SetBitRate( u16 wBitRate ) { m_wBitRate = htons( wBitRate); }
	u16  GetBitRate() { return ntohs(m_wBitRate); }
	void SetVideoWidth( u16 wVidWidth ) { m_wVideoWidth = htons(wVidWidth); }
	u16  GetVideoWidth() { return ntohs(m_wVideoWidth); }
	void SetVideoHeight( u16 wVidHeight ) { m_wVideoHeight = htons(wVidHeight); }
	u16	 GetVideoHeight() { return ntohs(m_wVideoHeight); }
	void SetFrameRate( u8 byFrameRate ) { m_byFrameRate = byFrameRate ; }
	u8	 GetFrameRate() { return m_byFrameRate; }
	void SetEncType( u8 byEncType ) { m_byEncType = byEncType ; }
	u8	 GetEncType() { return m_byEncType; }
	void SetProfileType( u8 byProfileType ) { m_byProfileType = byProfileType ; }
	u8	 GetProfileType() { return m_byProfileType; }
	
    void Print(void)
    {
//        StaticLog( "\tEncType:\t%d\n\tProfileType:\t%d\n\tFrameRate:\t%d\n\tBitrate:\t%d\n\tVidWidth:\t%d\n\tVidHeight:\t%d\n",
//			m_byEncType, m_byProfileType, m_byFrameRate, GetBitRate(), GetVideoWidth(), GetVideoHeight());    
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Hdu信息
struct TEqpHduInfo: public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpMapInfo
{
protected:
	
	THduChnlModePortAgt atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	u8  m_byStartMode; //启动模式(0: hdu_2, 1: hdu_1, 2: hdu_L)	
public:
	TEqpHduInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
		SetStartMode(STARTMODE_HDU_M); //默认为hdu_2
	}
	
	void SetStartMode(u8 byStartMode){ m_byStartMode = byStartMode; }
	u8   GetStartMode(){ return m_byStartMode;}
	
	void GetHduChnlModePort( u8 byNum, THduChnlModePortAgt &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			tHduChnModePort.SetOutModeType( atHduChnlModePort[byNum].GetOutModeType() );
			tHduChnModePort.SetOutPortType( atHduChnlModePort[byNum].GetOutPortType() );
			tHduChnModePort.SetZoomRate( atHduChnlModePort[byNum].GetZoomRate() );
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduInfo]:GetHduChnlModePort()'s byNum wrong!\n");
			return;			
		}
		
		return;
	}
	
    void SetHduChnlModePort( u8 byNum, THduChnlModePortAgt &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			atHduChnlModePort[byNum].SetOutModeType( tHduChnModePort.GetOutModeType() );
			atHduChnlModePort[byNum].SetOutPortType( tHduChnModePort.GetOutPortType() );
            atHduChnlModePort[byNum].SetZoomRate( tHduChnModePort.GetZoomRate() );			
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduInfo]:SetHduChnlModePort()'s byNum wrong!\n");
			return;	
		}
		
		return;
	}
	
	void Print(void)
	{
		OspPrintf(TRUE, FALSE, "\nHdu:%s\nEqpId:%d, RunBrd:%d\n, ZoomRate[0] = %d, ZoomRate[1] = %d\nHduOutPortType[0]:%d, HduOutModeType[0]:%d\n,HduOutPortType[1]:%d, HduOutModeType[1]%d:",
			GetAlias(), GetEqpId(), GetRunBrdId(), 
			atHduChnlModePort[0].GetZoomRate(), atHduChnlModePort[1].GetZoomRate(),
			atHduChnlModePort[0].GetOutPortType(), atHduChnlModePort[0].GetOutModeType(),
			atHduChnlModePort[1].GetOutPortType(), atHduChnlModePort[1].GetOutModeType());
        
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//4.6版新加外设表项结构
//HDU高清解码卡
struct TEqpHduEntry : public TEqpHduInfo,
					  public TEqpEntryParam
{
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 高清bas板信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,高清bas板ip
struct TEqpBasHDCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//Ip地址
	
public:
    TEqpBasHDCfgInfo(void):m_dwIpAddr(0) {}
	
    void    SetIpAddr(u32 dwIpAddr)  { m_dwIpAddr = htonl(dwIpAddr); }  //host order
    u32     GetIpAddr(void) { return ntohl(m_dwIpAddr); }
    void    SetType(u8 byType) { SetMapCount(byType); }
    u8      GetType(void) const { return GetMapCount(); }
	
    void    Print(void)
    {
  //      StaticLog( "\nRec:%s\nEqpId:%d, SwitchBrd:%d, McuPort:%d, RecPort:%d, RecIp:0x%x, Type.%d\n",
//			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetMcuStartPort(), 
//			GetEqpStartPort(), GetIpAddr(), GetType());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//////////////////////////////////////////////////////////////////////////
//apu2 结构体
/************************************************************************/
/*						CEqpCfg外设配置类定义						    */
/************************************************************************/
#define		MAXLEN_ALIAS			        128  //MCU或终端假名最多127个字母，63个汉字

//外设基本配置结构(无map信息)
struct TEqpBasicCfg
{
	char  achAlias[ MAXLEN_ALIAS+1 ];
	u8    byEqpId;          //外设ID
	u8    byEqpType;        //外设类型
	
	u32   dwLocalIP;        //本机IP地址
	u32   dwConnectIP;      //连接MCUIP地址
	u16   wConnectPort;     //连接MCU 通信端口
	u16   wMcuId;           //MCU id 号
	u16   wRcvStartPort;    //接收起始端口号
	
	
    u32 dwConnectIpB;
    u16 wConnectPortB;
    u16 wRcvStartPortB;
    TEqpBasicCfg(void) { memset(this, 0, sizeof(TEqpBasicCfg)); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMAPParam
{
	u32  dwCoreSpd;     // Map内核速度
	u32  dwMemSpd;      // 内存速度
	u32  dwMemSize;     // 内存大小
	u8   byMapId;	    // Map编号
	u32   dwPort;	    // Map端口号
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设基本配置结构
struct TEqpCfg:public TEqpBasicCfg
{
	
	u16   wMAPCount;        //使用的MAP个数
	TMAPParam m_atMap[MAXNUM_MAP];	//map信息
	
    TEqpCfg(void) { memset(this, 0, sizeof(TEqpCfg)); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Qos 信息
struct TMcuQosCfgInfo
{	
protected:
    u8  m_byQosType;					// Qos 类型
    u8  m_byAudLevel;					// 音频等级
    u8  m_byVidLevel;					// 视频等级
    u8  m_byDataLevel;					// 数据等级
    u8  m_bySignalLevel;				// 信号等级
    u8  m_byIpServiceType;				// IP服务类型
	
public:
    TMcuQosCfgInfo(void) { memset(this, 0, sizeof(TMcuQosCfgInfo)); }
    BOOL32  IsNull(void) const
    {
        TMcuQosCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuQosCfgInfo)));
    }
	
    void    SetQosType(u8 byType) { m_byQosType = byType; }
    u8      GetQosType(void) const { return m_byQosType; }
    void    SetAudLevel(u8 byLevel) { m_byAudLevel = byLevel; }
    u8      GetAudLevel(void) const { return m_byAudLevel; }
    void    SetVidLevel(u8 byLevel) { m_byVidLevel = byLevel; }
    u8      GetVidLevel(void) const { return m_byVidLevel; }
    void    SetDataLevel(u8 byLevel) { m_byDataLevel = byLevel; }
    u8      GetDataLevel(void) const { return m_byDataLevel; }
    void    SetSignalLevel(u8 byLevel) { m_bySignalLevel = byLevel; }
    u8      GetSignalLevel(void) const { return m_bySignalLevel; }
    void    SetIpServiceType(u8 byType) { m_byIpServiceType = byType; }
    u8      GetIpServiceType(void) const { return m_byIpServiceType; }
	
//     void    Print(void) const
//     {
//         StaticLog( "QosCfg:  QosType:%d, Aud:%d, Vid:%d, Data:%d, Signal:%d, IpServciType:%d\n",
//             GetQosType(), GetAudLevel(), GetVidLevel(), GetDataLevel(), 
//             GetSignalLevel(), GetIpServiceType());
//     }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

class CEqpCfg:public TEqpCfg
{
public:
	CEqpCfg();
	virtual~CEqpCfg();
public:
	void Print();
public:
	u32 m_dwMcuNodeA;				//连接McuA结点号
	u32 m_dwMcuIIdA;				//与McuA通信IID
	u32 m_dwMcuNodeB;				//连接McuB结点号
	u32 m_dwMcuIIdB;				//与McuB通信IID
	u32 m_dwServerNode;             //生产测试结点号
    u32 m_dwServerIId;				//生产测试IID
	u32 m_dwMpcSSrc;				//唯一会话源
	u32 m_dwMcuRcvIp;               //Mcu为外设分配的转发板IP
	u16 m_wMcuRcvStartPort;         //Mcu为外设分配的转发板端口
	u16 m_wEqpVer;					//外设版本
	u8  m_byRegAckNum;				//注册成次数
	TPrsTimeSpan m_tPrsTimeSpan;    //重传参数
	TMcuQosCfgInfo m_tQosInfo;      
};

#define  MIXER_APU2_CHN_MINNUM  (u8)2				//APU2最小配置通道数
#define  BRD_APU2_SNDPORT       (u16)10000          //APU2本地起始发送端口

	/************************************************************************/
	/*							CApu2Cfg配置类定义							*/
	/*																		*/
	/*        说明：一个Apu2拆成2个混音器，每个混音器配置对应CApu2Cfg		*/
	/************************************************************************/
class CApu2MixerCfg:public CEqpCfg
{
public:
	CApu2MixerCfg():m_byMemberNum(0),
					m_bySndOff(0),
					m_byIsMultiFormat(0),
					m_byIsSimuApu(0),
					m_wSimApuVer(0),
					m_byQualityLvl(0)
	{
	
	};
	~CApu2MixerCfg()
	{	
		Clear();
	};
public:

	void Clear()
	{
		m_byMemberNum     = 0;
		m_bySndOff        = 0;
		m_byIsMultiFormat = 0;
		m_byIsSimuApu     = 0;
		m_wSimApuVer      = 0;
		m_byQualityLvl	  = 0;
	}

	void Copy (const CApu2MixerCfg* const pcCfg)
	{
		if (NULL == pcCfg)
		{
			return;
		}
		
		m_byMemberNum      = pcCfg->m_byMemberNum;
		m_bySndOff         = pcCfg->m_bySndOff;
		m_byIsMultiFormat  = pcCfg->m_byIsMultiFormat;
		m_byIsSimuApu	   = pcCfg->m_byIsSimuApu;
		m_wSimApuVer       = pcCfg->m_wSimApuVer;
		m_byQualityLvl	   = pcCfg->m_byQualityLvl;

		m_dwMcuNodeA       = pcCfg->m_dwMcuNodeA;
		m_dwMcuIIdA        = pcCfg->m_dwMcuIIdA;
		m_dwMcuNodeB       = pcCfg->m_dwMcuNodeB;
		m_dwMcuIIdB		   = pcCfg->m_dwMcuIIdB;
		m_dwServerNode     = pcCfg->m_dwServerNode;
		m_dwServerIId      = pcCfg->m_dwServerIId;
		m_dwMpcSSrc		   = pcCfg->m_dwMpcSSrc;
		m_dwMcuRcvIp       = pcCfg->m_dwMcuRcvIp;
		m_wMcuRcvStartPort = pcCfg->m_wMcuRcvStartPort;
		m_wEqpVer		   = pcCfg->m_wEqpVer;
		m_byRegAckNum      = pcCfg->m_byRegAckNum;
		memcpy(&m_tPrsTimeSpan, &pcCfg->m_tPrsTimeSpan, sizeof(m_tPrsTimeSpan));
		memcpy(&m_tQosInfo, &pcCfg->m_tQosInfo, sizeof(m_tQosInfo));

		
		byEqpId			   = pcCfg->byEqpId;
		byEqpType          = pcCfg->byEqpType;
		dwLocalIP		   = pcCfg->dwLocalIP;
		dwConnectIP		   = pcCfg->dwConnectIP;
		wConnectPort	   = pcCfg->wConnectPort;
		wMcuId			   = pcCfg->wMcuId;
		wRcvStartPort	   = pcCfg->wRcvStartPort;
		wMAPCount		   = pcCfg->wMAPCount;
		dwConnectIpB	   = pcCfg->dwConnectIpB;
		wConnectPortB	   = pcCfg->wConnectPortB;
		wRcvStartPortB     = pcCfg->wRcvStartPortB;
		memcpy(achAlias, pcCfg->achAlias, MAXLEN_ALIAS);
		memcpy(m_atMap, pcCfg->m_atMap, sizeof(m_atMap));
		return;
	}

// 	void Print()
// 	{
// 		CEqpCfg::Print();
// 		StaticLog("\nMix \n");
// 		StaticLog("\t MemberNum    : %d\n", m_byMemberNum);
// 		StaticLog("\t m_bySndOff   : %d\n", m_bySndOff);
// 		StaticLog("\t IsMultiFormat: %d\n", m_byIsMultiFormat);
// 		StaticLog("\t m_byIsSimuApu: %d\n", m_byIsSimuApu);
// 		StaticLog("\t m_wSimApuVer: %d\n", m_wSimApuVer);
// 		StaticLog("\t m_byQualityLvl: %d\n", m_byQualityLvl);
// 	}
public:	
	u8     m_byMemberNum;		//配置成员个数
	u8     m_bySndOff;			//发送对象偏移
	u8     m_byIsMultiFormat;	//是否多格式
	u8     m_byIsSimuApu;       //是否模拟Apu
	u16    m_wSimApuVer;		//模拟Apu版本
	u8	   m_byQualityLvl;		//音质等级
	
};

	/************************************************************************/
	/*							CApu2Cfg配置类定义							*/
	/*																		*/
	/*					说明：一个Apu2设备对应TApu2EqpCfg					*/
	/************************************************************************/
struct TApu2EqpCfg
{
public:
	BOOL32        m_bIsProductTest;					   //是否生产测试
	u8		      m_byMixerNum;						   //Apu2设备配了几个混音器
	CApu2MixerCfg m_acMixerCfg[MIXER_APU2_CHN_MINNUM]; //每个混音器配置
public:
	TApu2EqpCfg()
	{
		m_bIsProductTest = FALSE;
		m_byMixerNum     = 0;
	}
};
#define     MIXER_INVALID_GRPID				255 //无效混音组号
#define     MIXER_INVALID_CHNNLID			255 //无效混音信道号
struct TMixerStart
{
protected:
    u8 m_byMixGroupId; //混音组Id
    u8 m_byMixDepth;   //混音深度
    u8 m_byAudioMode;  //语音格式
    u8 m_byAudioMode2; //第二语音格式(若不为空则为双混音格式)
    u8 m_byIsAllMix;   //全体混音
    TMediaEncrypt m_tAudioEncrypt;	//加密参数
    u8 m_byNeedPrs;
public:
    TMixerStart(void)
    {
        Reset();
    }
    void Reset(void)
    {
        m_byMixGroupId = MIXER_INVALID_GRPID;
        m_byMixDepth = 0;
        m_byAudioMode = MEDIA_TYPE_NULL;
        m_byAudioMode2 = MEDIA_TYPE_NULL;
        m_byIsAllMix = 0;
        m_byNeedPrs = 0;
        m_tAudioEncrypt.Reset();
    }

    void SetMixGroupId(u8 byGroupID)
    {
        m_byMixGroupId = byGroupID;
    }
    u8 GetMixGroupId()
    {
        return m_byMixGroupId;
    }
    void SetMixDepth(u8 byDepth)
    {
        m_byMixDepth = byDepth;
    }
    u8 GetMixDepth()
    {
        return m_byMixDepth;
    }
    void SetAudioMode(u8 byAudioMode)
    {
        m_byAudioMode = byAudioMode;
    }
    u8  GetAudioMode()
    {
        return m_byAudioMode;
    }
    void SetSecAudioMode(u8 byAudioMode)
    {
        m_byAudioMode2 = byAudioMode;
    }
    u8  GetSecAudioMode()
    {
        return m_byAudioMode2;
    }

    void SetIsAllMix(BOOL32 bIsAllMix)
    {
        m_byIsAllMix = (bIsAllMix ? 1:0 );
    }
    BOOL32 IsAllMix()
    {
        return (m_byIsAllMix != 0);
    }
    TMediaEncrypt& GetAudioEncrypt()
    {
        return m_tAudioEncrypt;
    }

    void SetAudioEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tAudioEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }

    void SetIsNeedByPrs(BOOL32 bNeedPrs)
    {
        m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
    }

    BOOL32 IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//外设交换板相关信息
struct TEqpSwitchBrdInfo
{
protected:
    u8  m_bySwitchBrdId;     //交换板ID
    u16 m_wMcuRecvPort;      //交换板(MCU)侧接收起始端口号 网络序
public:
    TEqpSwitchBrdInfo() : m_bySwitchBrdId(0),
						  m_wMcuRecvPort(0)	{}
    void SetSwitchBrdId(u8 byBrdId) { m_bySwitchBrdId = byBrdId;  }
    u8   GetSwitchBrdId(void) const { return m_bySwitchBrdId;  }
    void SetMcuRecvPort(u16 wPort) { m_wMcuRecvPort = htons(wPort);  }
    u16  GetMcuRecvPort(void) const { return ntohs(m_wMcuRecvPort);  }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 2.Mixer 信息
struct TEqpMixerInfo : public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpSwitchBrdInfo,
public TEqpMapInfo
{
protected:
    u8  m_byMaxChannelInGrp;			// 混音组最大通道数
	u8	m_byIsSendRedundancy;			// 是否冗余发送, zgc, 2007-0725
	
public:
    TEqpMixerInfo() : m_byMaxChannelInGrp(0){}
    void SetMaxChnInGrp(u8 byChnInGrp) { m_byMaxChannelInGrp = byChnInGrp;   }
    u8   GetMaxChnInGrp(void) { return m_byMaxChannelInGrp;   }
	void SetIsSendRedundancy( BOOL32 IsRedundancy ) { m_byIsSendRedundancy = IsRedundancy ? 1 : 0; }
	BOOL32 IsSendRedundancy(void) const { return ( 1 == m_byIsSendRedundancy ) ? TRUE : FALSE; } 
    
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "MixerId: %d, MixerAlias:%s, RunBrdId: %d, RunBrdIp.0x%x, MixerRecvPort: %d, SwitchBrdId: %d, McuRecvPort: %d, UsedMapNum: %d, MaxChnInGrp: %d, IsSendRedundancy: %d!\n",
			GetEqpId(), GetAlias(), 
			GetRunBrdId(), GetIpAddr(), GetEqpRecvPort(), 
			GetSwitchBrdId(), GetMcuRecvPort(), 
			GetUsedMapNum(), GetMaxChnInGrp(), IsSendRedundancy() );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [2]. 混音器
struct TEqpMixerEntry : public TEqpMixerInfo,
						public TEqpEntryParam 
{
protected:
    u8  m_byMaxMixGroupNum;	/*最大混音组个数*/
	u8	m_byIsSendRedundancy;	// 是否冗余发送, zgc, 2007-0725
public:
    TEqpMixerEntry() : m_byMaxMixGroupNum(0){}
    void SetMaxMixGrpNum(u8 byMaxGrpNum) { m_byMaxMixGroupNum = byMaxGrpNum;   }
    u8   GetMaxMixGrpNum(void) const { return m_byMaxMixGroupNum;    }
	void SetIsSendRedundancy( BOOL32 IsRedundancy ) { m_byIsSendRedundancy = IsRedundancy ? 1 : 0; }
	BOOL32 IsSendRedundancy(void) const { return ( 1 == m_byIsSendRedundancy ) ? TRUE : FALSE; } 
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//FTP TELNET 开关
#define BOARD_SW_TELNET		(u8)0
#define BOARD_SW_FTP		(u8)1
#define BOARD_SW_ALL		(u8)2
#define BOARD_SW_NONE		(u8)0xff


typedef struct TagTMcuBoardSwitchInfo
{
	u16  m_wBrdIndex;
	u8   m_byswtype;
	u8   m_OnOff;
}TMcuBoardSwitchInfo;


typedef struct TagTMcuBoardSwitchNty
{
	u16 m_wBrdIndex;
	u8  m_byswtype;
    u8  m_OnOff;

    TagTMcuBoardSwitchNty()
	{
        m_byswtype = BOARD_SW_NONE;
        m_OnOff = 0;
		m_wBrdIndex = 0;
	}
}TMcuBoardSwitchNty;



#define		TYPE_MPUBAS					13	 //MPU-BAS
//MpuBas信息结构
struct TEqpMpuBasInfo: public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpSwitchBrdInfo,
public TEqpMapInfo
{
	u8 m_byStartMode; //启动模式(0: bap_4, 1:bap_2)
	
	TEqpMpuBasInfo()
	{
		SetStartMode (TYPE_MPUBAS); //默认为TYPE_MPUBAS
	}
	void SetStartMode(u8 byStartMode){ m_byStartMode = byStartMode; }
	u8   GetStartMode(){ return m_byStartMode; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TEqpMpuBasEntry: public TEqpMpuBasInfo,
public TEqpEntryParam
{
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//混音成员结构
struct TMixMember
{
    TMt m_tMember;
    u8  m_byVolume;                 //成员音量
    u8  m_byAudioType;              //媒体类型
    TTransportAddr m_tAddr;         //成员的传输地址
    TTransportAddr m_tRtcpBackAddr; //RTCP回馈地址
}
#ifndef WIN32
__attribute__((packed)) 
#endif
;

#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#define window( x )	x
#define PACKED 
#else
#include <netinet/in.h>
#define window( x )
#if defined(__ETI_linux__)
#define PACKED
#else
#define PACKED __attribute__((__packed__))	// 取消编译器的优化对齐
#endif
#endif


///音频格式描述[2/8/2012 chendaiwei]
struct TAudioTypeDesc
{
private:
	u8 m_byAudioMediaType; //音频类型
	u8 m_byAudioTrackNum;  //音频声道数目（单声道为1,双声道为2）
	
public:
	TAudioTypeDesc( void )
	{
		Clear();
	}
	
	TAudioTypeDesc( u8 byAudioType, u8 byAudioTrackNum)
	{
		m_byAudioMediaType = byAudioType;
		m_byAudioTrackNum = byAudioTrackNum;
	}
	
	void Clear( void )
	{
		m_byAudioMediaType = MEDIA_TYPE_NULL;
		m_byAudioTrackNum = 1; 
	}
	
	u8 GetAudioMediaType( void )
	{
		return m_byAudioMediaType;
	}
	
	u8 GetAudioTrackNum( void )
	{
		return m_byAudioTrackNum;
	}
	
	void SetAudioMediaType( u8 byAudioType)
	{
		m_byAudioMediaType = byAudioType;
	}
	
	void SetAudioTrackNum( u8 byAudioTrackNum)
	{
		m_byAudioTrackNum = byAudioTrackNum;
	}
}
PACKED
;

//音频能力信息
struct TAudioCapInfo
{
private:
	TAudioTypeDesc m_tAudioTypeDesc;
	u8             m_byActivePayload;
	u32            reserved;
public:
	TAudioCapInfo( void )
	{
		Clear();
	}
	void Clear( void )
	{
		m_tAudioTypeDesc.Clear();
		m_byActivePayload = 0;
	}
	void SetAudioMediaType( u8 byAudioType)
	{
		m_tAudioTypeDesc.SetAudioMediaType(byAudioType);
	}
	void SetAudioTrackNum( u8 byAudioTrackNum)
	{
		m_tAudioTypeDesc.SetAudioTrackNum(byAudioTrackNum);
	}
	void SetActivePayLoad( u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}
	u8 GetAudioMediaType( void )
	{
		return m_tAudioTypeDesc.GetAudioMediaType();
	}
	u8 GetAudioTrackNum( void )
	{
		return m_tAudioTypeDesc.GetAudioTrackNum();
	}
	u8 GetActivePayLoad( void )
	{
		return m_byActivePayload;
	}
}
#ifndef WIN32
__attribute__((packed)) 
#endif
;

#define     MAXNUM_MIXER_DEPTH				10  //混音器最大混音深度

// zw [06/27/2008] AAC LC参数
#define AAC_SAMPLE_FRQ_8                (u8)1
#define AAC_SAMPLE_FRQ_11               (u8)2
#define AAC_SAMPLE_FRQ_12               (u8)3
#define AAC_SAMPLE_FRQ_16               (u8)4
#define AAC_SAMPLE_FRQ_22               (u8)5
#define AAC_SAMPLE_FRQ_24               (u8)6
#define AAC_SAMPLE_FRQ_32               (u8)7
#define AAC_SAMPLE_FRQ_44               (u8)8
#define AAC_SAMPLE_FRQ_48               (u8)9
#define AAC_SAMPLE_FRQ_64               (u8)10
#define AAC_SAMPLE_FRQ_88               (u8)11
#define AAC_SAMPLE_FRQ_96               (u8)12

/*****************************错误码定义**********************************/
const u32 ERR_MIXER_BGN = 24501;
#define ERR_MIXER_NONE               ( ERR_MIXER_BGN  )     //无错误 
#define ERR_MIXER_CALLDEVICE         ( ERR_MIXER_BGN + 1 )  //调用底层函数失败
#define ERR_MIXER_MIXING             ( ERR_MIXER_BGN + 2 )  //正在混音状态
#define ERR_MIXER_NOTMIXING          ( ERR_MIXER_BGN + 3 )  //未混音状态
#define ERR_MIXER_ERRCONFID          ( ERR_MIXER_BGN + 4 )  //无效的会议ID
#define ERR_MIXER_CHNINVALID         ( ERR_MIXER_BGN + 5 )  //添加通道失败
#define ERR_MIXER_STATUIDLE          ( ERR_MIXER_BGN + 6 )  //混音器状态空闲

//////////////////////////////////////////////////////////////////////////
//混音和语音激励 消息定义
#define  MAXVALUE_APU2_VOLUME     (u8)31              //Apu2混音器最大音量值

/*----------  以下为混音器消息号定义(26301-26400)  -----------*/
const u32 EV_MCUMIXER_BGN = 26301;
//混音器向MCU发出注册请求，MIXER->MCU，消息体为TPeriEqpRegReq结构
OSPEVENT( UMS_MIXER_MCU_REG_REQ,				EV_MCUMIXER_BGN );
//MCU接受应答，MCU->MIXER，消息体为TPeriEqpRegAck + TPrsTimeSpan + u16(MTU size) + u8(IsSendRedundancy)
OSPEVENT( UMS_MCU_MIXER_REG_ACK,				EV_MCUMIXER_BGN + 1 );
//MCU拒绝应答，MCU->MIXER，无消息体
OSPEVENT( UMS_MCU_MIXER_REG_NACK,				EV_MCUMIXER_BGN + 2 );
//混音器状态通知，MIXER->MCU，消息体为TPeriEqpStatus
OSPEVENT( UMS_MIXER_MCU_MIXERSTATUS_NOTIF,		EV_MCUMIXER_BGN + 3 );

//MCU开始混音请求，MCU->MIXER 消息体: TMixerStart+TDoublePayload+TCapSupportEx
OSPEVENT( UMS_MCU_MIXER_STARTMIX_REQ,			EV_MCUMIXER_BGN + 5 );
//同意开始混音应答，MIXER->MCU，消息体: 1 byte(混音组Id)+ 1 byte(混音深度)
OSPEVENT( UMS_MIXER_MCU_STARTMIX_ACK,			EV_MCUMIXER_BGN + 6 );
//拒绝开始混音应答，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_STARTMIX_NACK,			EV_MCUMIXER_BGN + 7 );

//混音组状态通知，MIXER->MCU，消息体为TMixerGrpStatus
OSPEVENT( UMS_MIXER_MCU_GRPSTATUS_NOTIF,		EV_MCUMIXER_BGN + 10 );

//MCU停止混音请求，MCU->MIXER，消息体: 1 byte(混音组Id)
OSPEVENT( UMS_MCU_MIXER_STOPMIX_REQ,			EV_MCUMIXER_BGN + 15 );
//同意停止混音应答，MIXER->MCU，消息体: 1 byte(混音组Id)
OSPEVENT( UMS_MIXER_MCU_STOPMIX_ACK,			EV_MCUMIXER_BGN + 16 );
//拒绝停止混音应答，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_STOPMIX_NACK,			EV_MCUMIXER_BGN + 17 );

//加入成员请求，MCU->MIXER，消息体:1 byte(混音组Id)+ TMixMember + 1 byte(成员语音原始格式)
//  m_tMember,m_tAddr,有效
OSPEVENT( UMS_MCU_MIXER_ADDMEMBER_REQ,			EV_MCUMIXER_BGN + 20 );
//加入成员应答消息，MIXER->MCU，消息体: 1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_ADDMEMBER_ACK,			EV_MCUMIXER_BGN + 21 );
//加入成员应答消息，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_ADDMEMBER_NACK,			EV_MCUMIXER_BGN + 22 );


//删除成员请求，MCU->MIXER，消息体:1 byte(混音组Id)+ TMixMember	
//  m_tMember, m_byGrpId 有效
OSPEVENT( UMS_MCU_MIXER_REMOVEMEMBER_REQ,		EV_MCUMIXER_BGN + 25 );
//删除成员应答消息，MIXER->MCU，消息体: 1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_REMOVEMEMBER_ACK,		EV_MCUMIXER_BGN + 26 );
//删除成员应答消息，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_REMOVEMEMBER_NACK,		EV_MCUMIXER_BGN + 27 );

//混音激励成员改变通知,MIXER->MCU ,消息体 u8    abyActiveMmb[MAXNUM_MIXER_GROUP]
//0表示无效成员
OSPEVENT( UMS_MIXER_MCU_ACTIVEMMBCHANGE_NOTIF,	EV_MCUMIXER_BGN + 30 );

//设置混音成员，MCU->MIXER，消息体:1 byte(混音组Id)+ 192 byte(每字节对应一终端)	
OSPEVENT( UMS_MCU_MIXER_SETMEMBER_CMD,			EV_MCUMIXER_BGN + 32 );

//强制成员混音 ,MCU->MIXER，消息体:1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MCU_MIXER_FORCEACTIVE_REQ,		EV_MCUMIXER_BGN + 35 );
//强制成员混音应答，MIXER->MCU，消息体:1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_FORCEACTIVE_ACK,		EV_MCUMIXER_BGN + 36 );
//强制成员混音拒绝，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_FORCEACTIVE_NACK,		EV_MCUMIXER_BGN + 37 );

//取消成员强制混音 ,MCU->MIXER，消息体:1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MCU_MIXER_CANCELFORCEACTIVE_REQ,	EV_MCUMIXER_BGN + 40 );
//取消成员强制混音应答，MIXER->MCU，消息体:1 byte(混音组Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_CANCELFORCEACTIVE_ACK,	EV_MCUMIXER_BGN + 41 );
//取消成员强制混音拒绝，MIXER->MCU，无消息体
OSPEVENT( UMS_MIXER_MCU_CANCELFORCEACTIVE_NACK,	EV_MCUMIXER_BGN + 42 );

//设置某通道音量消息，MCU->MIXER，消息体1 byte(混音组Id)+ TMixMember
//  m_tMember, m_byGrpId ,m_byVolume 有效
OSPEVENT( UMS_MCU_MIXER_SETCHNNLVOL_CMD,		EV_MCUMIXER_BGN + 45 );
//某通道音量通知消息，MIXER->MCU，消息体为TMixMember
OSPEVENT( UMS_MIXER_MCU_CHNNLVOL_NOTIF,			EV_MCUMIXER_BGN + 50 );

//设置混音深度请求消息，MCU->MIX，消息体: 1 byte(混音组Id) + 1 byte(混音深度)
OSPEVENT( UMS_MCU_MIXER_SETMIXDEPTH_REQ,		EV_MCUMIXER_BGN + 55 );
//设置混音深度应答消息，MIXER->MCU，消息体: 1 byte(混音组Id) + 1 byte(混音深度)
OSPEVENT( UMS_MIXER_MCU_SETMIXDEPTH_ACK,		EV_MCUMIXER_BGN + 56 );
//设置混音深度拒绝消息，MIXER->MCU，
OSPEVENT( UMS_MIXER_MCU_SETMIXDEPTH_NACK,		EV_MCUMIXER_BGN + 57 );

//MCU给混音器的是否要发送码流通知,消息体: 1 byte(混音组Id) + 1 byte(0:不发,1发)
OSPEVENT( UMS_MCU_MIXER_SEND_NOTIFY,			EV_MCUMIXER_BGN + 60 );

//设置语音激励延时保护时长消息, MCU->MIXER, 消息体: 1 byte(混音组Id) + 4 byte(u32 保护时长 网络序)
OSPEVENT( UMS_MCU_MIXER_VACKEEPTIME_CMD,		EV_MCUMIXER_BGN + 65 );

//混音延时设置,消息体：u8（混音组id） ＋ u16（毫秒）
OSPEVENT( UMS_MCU_MIXER_CHANGEMIXDELAY_CMD,		EV_MCUMIXER_BGN + 66 );

// stop mixer map, zgc, 2007/04/24
OSPEVENT( UMS_MCU_MIXER_STOPEQP_CMD,			EV_MCUMIXER_BGN + 67 );
// start mixer map, zgc, 2007/04/26
OSPEVENT( UMS_MCU_MIXER_STARTEQP_CMD,			EV_MCUMIXER_BGN + 68 );

//tianzhiyong 2010/05/19  增加开启和关闭EAPU混音器语音激励功能命令
//开启EAPU混音器语音激励功能命令，MCU->MIXER，
//消息体: 单开语音激励时为TMixerStart+TDoublePayload+TCapSupportEx 否则为空
OSPEVENT( UMS_MCU_MIXER_STARTVAC_CMD,		EV_MCUMIXER_BGN + 69 );
//关闭EAPU混音器语音激励功能命令，MCU->MIXER，消息体: 空
OSPEVENT( UMS_MCU_MIXER_STOPVAC_CMD,		EV_MCUMIXER_BGN + 70 );
//设置同步通道 u8 chnl
OSPEVENT( UMS_MCU_MIXER_SYNCCHNL_CMD,		EV_MCUMIXER_BGN + 71 );
//删除同步通道 u8 chnl
OSPEVENT( UMS_MCU_MIXER_SYNCCHNL_DEL,		EV_MCUMIXER_BGN + 72 );
/*----------  MCU和混音器消息号定义结束(26301-26400)  -----------*/

//量子：更新码流秘钥   消息体: TQTMediaKeyInfo
OSPEVENT( UMS_MCU_MIXER_SETMEDIAKEY_CMD,		EV_MCUMIXER_BGN + 73 );

//////////////////////////////////////////////////////////////////////////
//错误号
const u16     ERR_MCU_BGN = 20001;

#define DefineError(err, num )   \
const u16 err = num;
//该外设已登记
DefineError( ERR_MCU_PERIEQP_REGISTERED		   , ERR_MCU_BGN + 15)

//建链节点通信版本与MCU不一致（错误码：20017，注意兼容老版本，不能更改）
DefineError( ERR_MCU_VER_UNMATCH               , ERR_MCU_BGN + 16)

//无空闲外设管理能力
DefineError(ERR_MCU_NOIDLEEQPSSN               , ERR_MCU_BGN + 21)

//指定外设不在线
DefineError( ERR_MCU_EQPOFFLINE				   , ERR_MCU_BGN + 50)

// 指定的外设不合法
DefineError( ERR_MCU_WRONGEQP				   , ERR_MCU_BGN + 51)

// 尝试连接的外设非法
DefineError( ERR_MCU_REGEQP_INVALID			   , ERR_MCU_BGN + 52)


//////////////////////////////////////////////////////////////////////////
//消息以及APP定义

//#define AID_TP_MCUBRD_SSN_APP		AID_MCU_BGN + 27	//78 mcu侧外设板子业务处理App  需要与MCU同步
//#define AID_TP_MCUBRD_REG_APP		AID_MCU_BGN + 6     //57 mcu侧外设板子注册处理App  需要与MCU同步
#define AID_TP_MPU2_APP				AID_MCU_BGN + 37    //外设板子注册处理App  需要与MCU同步

const u16    EV_UMS_MCUBRD_BGN = 20001;
//注册单板
//单板的注册消息，消息体为TBrdPosition+u32(单板IP)+u8(网口号)+u8(OsType)
OSPEVENT( UMS_BOARD_MPC_REG,			    EV_UMS_MCUBRD_BGN + 401 );
OSPEVENT( UMS_MPC_BOARD_REG_ACK,		    EV_UMS_MCUBRD_BGN + 402 );
OSPEVENT( UMS_MPC_BOARD_REG_NACK,		    EV_UMS_MCUBRD_BGN + 403 );

//获取单板配置信息
OSPEVENT( UMS_BOARD_MPC_GET_CONFIG,		    EV_UMS_MCUBRD_BGN + 404 );
//消息体为 u8(外设个数)+TTPEqpHduEntry
OSPEVENT( UMS_MPC_BOARD_GET_CONFIG_ACK,	    EV_UMS_MCUBRD_BGN + 405 );
OSPEVENT( UMS_MPC_BOARD_GET_CONFIG_NACK,    EV_UMS_MCUBRD_BGN + 406 );

//单板重启命令
OSPEVENT( UMS_MPC_BOARD_RESET_CMD,			    EV_UMS_MCUBRD_BGN + 413 );
//获取单板版本信息的消息  消息内容：无
OSPEVENT( UMS_MPC_BOARD_GET_VERSION_REQ,		EV_UMS_MCUBRD_BGN + 420 );
//单板版本信息应答        消息内容：TBrdPos + "Hardware %d| FPGA %d"
OSPEVENT( UMS_BOARD_MPC_GET_VERSION_ACK,		EV_UMS_MCUBRD_BGN + 421 );

//单板进行软件更新的消息
//消息体: u8(单板索引) + u8(源文件名个数) + u8(文件名长度) + s8[](文件名)  //注：(linux文件名包含绝对路径)
OSPEVENT( UMS_MPC_BOARD_UPDATE_SOFTWARE_CMD,	EV_UMS_MCUBRD_BGN + 425 );

//版本更新结果通知，消息体：u8(单板索引) + u8(文件数) + u8[](是否成功<对会控>) 
// + u8(文件长度) + s8[](文件名) + u8 + s8[] + ...
OSPEVENT( UMS_BOARD_MPC_UPDATE_NOTIFY,			EV_UMS_MCUBRD_BGN + 426 );

// APU2 TELNET FTP 开关
OSPEVENT( UMS_MPC_BOARD_FTP_TELNET_SWITCH,	    EV_UMS_MCUBRD_BGN + 551 );//TMcuBoardSwitchInfo

//APU2 FTP TELNET 开关状态nty
OSPEVENT( UMS_MPC_BOARD_FTP_TELNET_SWITCH_NTY,	    EV_UMS_MCUBRD_BGN + 552 );//TMcuBoardSwitchNty


/*----------    画面复合器消息定义结束(26701-26800)  ----------*/
//画面合成
const u16     EV_MCUVMP_BGN = 26701;
const u16     EV_MCUVMP_END = EV_MCUVMP_BGN + 74;

//VMP向MCU注册请求，VMP->MCU，消息体为TPeriEqpRegReq结构
OSPEVENT( UMS_VMP_MCU_REGISTER_REQ,				EV_MCUVMP_BGN );
//MCU给VMP注册确认,MCU->VMP，消息体为TPeriEqpRegAck + TPrsTimeSpan + u16(MTU size)　
OSPEVENT( UMS_MCU_VMP_REGISTER_ACK,				EV_MCUVMP_BGN + 1 );
//MCU给VMP注册拒绝,MCU->VMP，无消息体
OSPEVENT( UMS_MCU_VMP_REGISTER_NACK,			EV_MCUVMP_BGN + 2 );
//VMP给MCU的状态上报,VMP->MCU，消息体:TPeriEqpStatus
OSPEVENT( UMS_VMP_MCU_VMPSTATUS_NOTIF,			EV_MCUVMP_BGN + 3 );

//MCU设置画面合成风格, 消息体:TVmpStyleCfgInfo
OSPEVENT( UMS_MCU_VMP_SETSTYLE_CMD,				EV_MCUVMP_BGN + 4 );
//MCU命令VMP停止MAP, 消息体: 无, zgc, 2007/04/24
OSPEVENT( UMS_MCU_VMP_STOPMAP_CMD,				EV_MCUVMP_BGN + 5 );
//MCU命令外设修改发送IP地址, 消息体：u32
OSPEVENT( UMS_MCU_EQP_MODSENDADDR_CMD,          EV_MCUVMP_BGN + 6 );

//MCU请求VMP开始工作,MCU->VMP，消息体为CKDVVMPParam+CKDVVMPParam+u8(是否prs)+TVmpStyleCfgInfo+TCapSupportEx
OSPEVENT( UMS_MCU_VMP_STARTVIDMIX_REQ,			EV_MCUVMP_BGN + 11 );
//VMP给MCU开始工作确认,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_ACK,			EV_MCUVMP_BGN + 12 );
//VMP给MCU开始工作拒绝,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_NACK,			EV_MCUVMP_BGN + 13 );
//VMP给MCU的开始结果，VMP->MCU,消息体空
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_NOTIF,		EV_MCUVMP_BGN + 14 );

//MCU请求VMP停止工作,MCU->VMP，无消息体
OSPEVENT( UMS_MCU_VMP_STOPVIDMIX_REQ,			EV_MCUVMP_BGN + 21 );
//VMP给MCU停止工作确认,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_ACK,			EV_MCUVMP_BGN + 22 );
//VMP给MCU停止工作拒绝,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_NACK,			EV_MCUVMP_BGN + 23 );
//VMP给MCU的停止结果，VMP->MCU,消息体空
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_NOTIF,			EV_MCUVMP_BGN + 24 );

//MCU请求VMP改变复合参数,MCU->VMP，消息体为CKDVVMPParam+CKDVVMPParam+u8(是否prs)+TVmpStyleCfgInfo
OSPEVENT( UMS_MCU_VMP_CHANGEVIDMIXPARAM_REQ,	EV_MCUVMP_BGN + 31 );
//VMP给MCU改变复合参数确认,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_CHANGEVIDMIXPARAM_ACK,	EV_MCUVMP_BGN + 32 );
//VMP给MCU改变复合参数拒绝,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_CHANGEVIDMIXPARAM_NACK,	EV_MCUVMP_BGN + 33 );
//VMP给MCU的状态改变结果，VMP->MCU,消息体CKDVVMPParam结构
OSPEVENT( UMS_VMP_MCU_CHANGESTATUS_NOTIF,		EV_MCUVMP_BGN + 34 );

OSPEVENT( UMS_MCU_VMP_UPDATAVMPENCRYPTPARAM_REQ,EV_MCUVMP_BGN + 35 );

OSPEVENT( UMS_MCU_VMP_FASTUPDATEPIC_CMD,		EV_MCUVMP_BGN + 36 );

//MCU对合成通道LOG的操作命令, 消息体：u8( 0 - 取消LOG， 1 - 增加LOG )
OSPEVENT( UMS_MCU_VMP_CHNNLLOGOPR_CMD,          EV_MCUVMP_BGN + 37 );
//MCU 给VMP某通道设置台标命令， 消息体：s8 * aliasname
OSPEVENT( UMS_MCU_VMP_CHANGEMEMALIAS_CMD,		EV_MCUVMP_BGN + 38 );

//MCU请求VMP回送复合参数,MCU->VMP，无消息体
OSPEVENT( UMS_MCU_VMP_GETVIDMIXPARAM_REQ,		EV_MCUVMP_BGN + 41 );
//VMP给MCU回送复合参数确认,VMP->MCU，消息体为CKDVVMPParam结构
OSPEVENT( UMS_VMP_MCU_GETVIDMIXPARAM_ACK,		EV_MCUVMP_BGN + 42 );
//VMP给MCU回送复合参数拒绝,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_GETVIDMIXPARAM_NACK,		EV_MCUVMP_BGN + 43 );
//启动VMP初始化
OSPEVENT( EV_VMP_INIT,	  	  				EV_MCUVMP_BGN + 50 );
//显示所有的统计和状态
OSPEVENT( EV_VMP_DISPLAYALL,	  			EV_MCUVMP_BGN + 60 );
//显示VMP内部的合成参数
OSPEVENT( EV_VMP_SHOWPARAM,					EV_MCUVMP_BGN + 61 );
//MCU请求VMP回送复合参数,MCU->VMP，消息体u16的码率，CServMsg.SetChnIndex()[1 or 2]
OSPEVENT( UMS_MCU_VMP_SETCHANNELBITRATE_REQ,	EV_MCUVMP_BGN + 65 );
//VMP给MCU回送复合参数确认,VMP->MCU，消息体为CKDVVMPParam结构
OSPEVENT( UMS_VMP_MCU_SETCHANNELBITRATE_ACK,	EV_MCUVMP_BGN + 66 );
//VMP给MCU回送复合参数拒绝,VMP->MCU，无消息体
OSPEVENT( UMS_VMP_MCU_SETCHANNELBITRATE_NACK,	EV_MCUVMP_BGN + 67 );
//请求I帧,CServMsg.GetChnIndex为请求的通道号
OSPEVENT( UMS_VMP_MCU_NEEDIFRAME_CMD,			EV_MCUVMP_BGN + 70 );
//备板输出是否启用命令，VMP内部使用，消息体：u8: 0不启用，1启用
OSPEVENT( EV_VMP_BACKBOARD_OUT_CMD,         EV_MCUVMP_BGN + 71 );
//设置VMP帧率
OSPEVENT( EV_VMP_SETFRAMERATE_CMD,			EV_MCUVMP_BGN + 72 );
//MCU通知VMP增加或删除通道(伴随起停相应通道的接收)命令，消息体：u8: channelidx, u8 byAdd
OSPEVENT( UMS_MCU_VMP_ADDREMOVECHNNL_CMD,		EV_MCUVMP_BGN + 73 );
//MCU通知VMP停或开某一输出通道命令，消息体：u8 chnnelIdx,u8 byActive
OSPEVENT( UMS_MCU_VMP_STARTSTOPCHNNL_CMD,		EV_MCUVMP_BGN + 74 );

OSPEVENT( UMS_MCU_VMP_SETQTMEDIAKEY_CMD,		EV_MCUVMP_BGN + 75 );
/*----------    画面复合器消息定义结束(26701-26800)  ----------*/

//////////////////////////////////////////////////////////////////////////
//码流适配器的消息
/*MCU和BAS间业务接口消息(26601-26700)*/
const u16     EV_UMS_MCUBAS_BGN = 26601;
const u16     EV_UMS_MCUBAS_END = EV_UMS_MCUBAS_BGN + 99;

//码率适配器向MCU发出注册请求，BAS->MCU，消息体为TPeriEqpRegReq结构
OSPEVENT( UMS_BAS_MCU_REG_REQ,					EV_UMS_MCUBAS_BGN );
//MCU接受应答，MCU->BAS，消息体为消息体为TPeriEqpRegAck + TPrsTimeSpan + u16(MTU size)
OSPEVENT( UMS_MCU_BAS_REG_ACK,					EV_UMS_MCUBAS_BGN + 1 );
//MCU拒绝应答，MCU->BAS，无消息体
OSPEVENT( UMS_MCU_BAS_REG_NACK,					EV_UMS_MCUBAS_BGN + 2 );
//适配器状态通知，BAS->MCU，消息体为TPeriEqpStatus
OSPEVENT( UMS_BAS_MCU_BASSTATUS_NOTIF,			EV_UMS_MCUBAS_BGN + 3 );

//MCU启动适配请求，MCU->BAS，消息体为TAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)+
//                       TMediaEncrypt(audio)+TDoublePayload(Audio)结构+TCapSupportEx,
//     业务消息的通道索引号指明通道 1到 MAXNUM_RTPHDR_CHNNL 为RTP头重组通道，其他为适配通道
//apu2 音频适配请求时，消息体为TAudAdaptParam*byOutNum+TMediaEncrypt+TDoublePayload
OSPEVENT( UMS_MCU_BAS_STARTADAPT_REQ,			EV_UMS_MCUBAS_BGN + 5 );
//启动适配应答消息，BAS->MCU，消息体: TEqp
OSPEVENT( UMS_BAS_MCU_STARTADAPT_ACK,			EV_UMS_MCUBAS_BGN + 6 );
//启动适配应答消息，BAS->MCU，消息体: TEqp
OSPEVENT( UMS_BAS_MCU_STARTADAPT_NACK,			EV_UMS_MCUBAS_BGN + 7 );

//MCU停止适配命令，MCU->BAS，无消息体，业务消息的通道索引号指明通道
OSPEVENT( UMS_MCU_BAS_STOPADAPT_REQ,			EV_UMS_MCUBAS_BGN + 10 );
//停止适配应答消息，BAS->MCU，无消息体
OSPEVENT( UMS_BAS_MCU_STOPADAPT_ACK,			EV_UMS_MCUBAS_BGN + 11 );
//停止适配应答消息，BAS->MCU，无消息体
OSPEVENT( UMS_BAS_MCU_STOPADAPT_NACK,			EV_UMS_MCUBAS_BGN + 12 );

//MCU改变适配参数请求，MCU->BAS，消息体为TAdaptParam结构,业务消息的通道索引号指明通道
//TAdaptParam 中的音视频类型无效
OSPEVENT( UMS_MCU_BAS_SETADAPTPARAM_CMD,		EV_UMS_MCUBAS_BGN + 15 );
OSPEVENT( UMS_MCU_BAS_CHANGEAUDPARAM_REQ,		EV_UMS_MCUBAS_BGN + 16 );
OSPEVENT( UMS_BAS_MCU_CHANGEAUDPARAM_ACK,		EV_UMS_MCUBAS_BGN + 17 );
OSPEVENT( UMS_BAS_MCU_CHANGEAUDPARAM_NACK,		EV_UMS_MCUBAS_BGN + 18 );
//码流适配器通道状态通知，BAS-> MCU ，消息体BYTE(外设ID) + TBasChnStatus,业务消息的通道索引号指明通道
OSPEVENT( UMS_BAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 20 );

//音频适配器通道状态通知 AUDBAS->MCU，消息：u8(外设类型：APU2_BAS_CHN) + TAudBasChnStatus
OSPEVENT( UMS_AUDBAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 46 );

//消息体：THDAdaptParam+THDAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)
//        业务消息的通道索引号指明通道, 对于双流通道，两个TAdaptParam完全一致
OSPEVENT( UMS_MCU_HDBAS_STARTADAPT_REQ,         EV_UMS_MCUBAS_BGN + 30 );
//启动适配应答消息，HDBAS->MCU，消息体: TEqp, 业务消息的通道索引号指明通道
OSPEVENT( UMS_HDBAS_MCU_STARTADAPT_ACK,         EV_UMS_MCUBAS_BGN + 31 );
//启动适配应答消息，HDBAS->MCU，消息体: TEqp, 业务消息的通道索引号指明通道
OSPEVENT( UMS_HDBAS_MCU_STARTADAPT_NACK,        EV_UMS_MCUBAS_BGN + 32 );
//适配器状态通知，HDBAS->MCU，消息体: TPeriEqpStatus
OSPEVENT( UMS_HDBAS_MCU_BASSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 33 );

//MCU停止适配命令，MCU->HDBAS，无消息体，业务消息的通道索引号指明通道
OSPEVENT( UMS_MCU_HDBAS_STOPADAPT_REQ,          EV_UMS_MCUBAS_BGN + 35 );
//停止适配应答消息，HDBAS->MCU，无消息体
OSPEVENT( UMS_HDBAS_MCU_STOPADAPT_ACK,          EV_UMS_MCUBAS_BGN + 36 );
//停止适配应答消息，HDBAS->MCU，无消息体
OSPEVENT( UMS_HDBAS_MCU_STOPADAPT_NACK,         EV_UMS_MCUBAS_BGN + 37 );

//消息体：THDAdaptParam+THDAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)
//        业务消息的通道索引号指明通道, 对于双流通道，两个TAdaptParam完全一致
OSPEVENT( UMS_MCU_HDBAS_SETADAPTPARAM_CMD,		EV_UMS_MCUBAS_BGN + 40 );
//码流适配器通道状态通知，HDBAS-> MCU ，消息体: BYTE(通道类型) + THDBasVidChnStatus/THDBasDVidChnStatus,业务消息的通道索引号指明通道
OSPEVENT( UMS_HDBAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 45 );

OSPEVENT( UMS_MCU_BAS_FASTUPDATEPIC_CMD,			EV_UMS_MCUBAS_BGN + 25 );
OSPEVENT( UMS_BAS_MCU_NEEDIFRAME_CMD,				EV_UMS_MCUBAS_BGN + 26 );

OSPEVENT( UMS_BAS_AUD_SET_SYNC_CMD,					EV_UMS_MCUBAS_BGN + 27 );

OSPEVENT( UMS_BAS_AUD_SET_MEDIA_KEY_CMD,			EV_UMS_MCUBAS_BGN + 28 );

OSPEVENT( UMS_MCU_HDBAS_QTENCRYPT_CMD,	     		EV_UMS_MCUBAS_BGN + 55 );

//////////////////////////////////////////////////////////////////////////
//录播服务器的消息
/*MCU和REC间业务接口消息(26101-26300)*/
const u16     EV_UMS_MCUREC_BGN = 26101;
const u16     EV_UMS_MCUREC_END = 26300;

//录像机向UMS发出注册请求，REC->UMS，消息体为TPeriEqpRegReq结构
OSPEVENT( REC_UMS_REG_REQ,					EV_UMS_MCUREC_BGN );
//MCU接受应答，UMS->REC，消息体为消息体为TPeriEqpRegAck
OSPEVENT( UMS_REC_REG_ACK,					EV_UMS_MCUREC_BGN + 1 );
//MCU拒绝应答，UMS->REC，无消息体
OSPEVENT( UMS_REC_REG_NACK,					EV_UMS_MCUREC_BGN + 2 );

//UMS请求获得录像机状态请求, UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_GETRECSTATUS_REQ,			EV_UMS_MCUREC_BGN + 5 );
//回馈录像机状态，REC->UMS，消息体TPeriEqpStatus
OSPEVENT( REC_UMS_GETRECSTATUS_ACK,			EV_UMS_MCUREC_BGN + 6 );
//拒绝回馈录像机状态，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_GETRECSTATUS_NACK,		EV_UMS_MCUREC_BGN + 7 );
//录像机状态通知，REC->UMS，消息体为TPeriEqpStatus
OSPEVENT( REC_UMS_RECSTATUS_NOTIF,			EV_UMS_MCUREC_BGN + 8 );

/*
 *录像列表请求消息：
 *录像机收到请求后分配发送录像文件通知，全部发送完毕后发送ACK消息
 *若录像机拒绝发送列表，则仅发送NACK消息。
 */
//UMS请求录像机给出录像列表命令，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_LISTALLRECORD_REQ,		EV_UMS_MCUREC_BGN + 10 );
//录像机列应答(完毕)消息，REC->UMS,消息体为TEqp
OSPEVENT( REC_UMS_LISTALLRECORD_ACK,		EV_UMS_MCUREC_BGN + 11 );
//录像机拒绝录像列表请求，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_LISTALLRECORD_NACK,		EV_UMS_MCUREC_BGN + 12 );
//录像机列表通知消息，REC->UMS, 消息体为TEqp+TRecFileListNotify
OSPEVENT( REC_UMS_LISTALLRECORD_NOTIF,		EV_UMS_MCUREC_BGN + 13 );

//UMS请求获得录像机录像通道状态请求, UMS->REC, 消息体为TEqp，信道号位于消息头中
OSPEVENT( UMS_REC_GETRECORDCHNSTATUS_REQ,	EV_UMS_MCUREC_BGN + 15 );
//回馈录像机信道状态，REC->UMS，消息体TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_GETRECORDCHNSTATUS_ACK,	EV_UMS_MCUREC_BGN + 16 );
//拒绝回馈录像机信道状态，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_GETRECORDCHNSTATUS_NACK,	EV_UMS_MCUREC_BGN + 17 );
//录像机录像信道状态通知，REC->UMS，消息体为TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_RECORDCHNSTATUS_NOTIF,	EV_UMS_MCUREC_BGN + 18 );


//MCU请求获得录像机放像通道状态请求, UMS->REC, 消息体为TEqp，信道号位于消息头中
OSPEVENT( UMS_REC_GETPLAYCHNSTATUS_REQ,		EV_UMS_MCUREC_BGN + 20 );
//回馈录像机信道状态，REC->UMS，消息体TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_GETPLAYCHNSTATUS_ACK,		EV_UMS_MCUREC_BGN + 21 );
//拒绝回馈录像机信道状态，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_GETPLAYCHNSTATUS_NACK,	EV_UMS_MCUREC_BGN + 22 );
//录像机放像信道状态通知，REC->UMS，消息体为TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_PLAYCHNSTATUS_NOTIF,		EV_UMS_MCUREC_BGN + 23 );

//获取录相进度，消息体：无 (信道号位于消息头)
OSPEVENT( UMS_REC_GETRECPROG_CMD,           EV_UMS_MCUREC_BGN + 24 );
//录像机当前录像进度通知消息，REC->UMS，消息体为TEqp+TRecProg，信道号位于消息头
OSPEVENT( REC_UMS_RECORDPROG_NOTIF,			EV_UMS_MCUREC_BGN + 25 );

//获取放相进度，消息体：无 (信道号位于消息头)
OSPEVENT( UMS_REC_GETPLAYPROG_CMD,          EV_UMS_MCUREC_BGN + 26 );
//录像机当前放像进度通知消息，REC->UMS，消息体为TEqp+TRecProg，信道号位于消息头
OSPEVENT( REC_UMS_PLAYPROG_NOTIF,			EV_UMS_MCUREC_BGN + 27 );
//录像机异常通知消息，REC->UMS，消息体为TEqp，信道号和错误码位于消息头
OSPEVENT( REC_UMS_EXCPT_NOTIF,				EV_UMS_MCUREC_BGN + 28 );


/////////////////
//放像消息

//UMS请求播放，UMS->REC，消息体为TEqp + TMediaEncrypt(video) + TDoublePayload(main video) +
//                TMediaEncrypt(audio) + TDoublePayload(main audio) + 
//                TDoublePayload(second video) + TDoublePayload(second audio) +
//				  u8(byDStreamMediaType) +
//                TRecProg(放像进度) + 录像名 + TCapSupportEx
OSPEVENT( UMS_REC_STARTPLAY_REQ,			EV_UMS_MCUREC_BGN + 30 );
//同意MCU播放请求应答，REC->UMS，消息体为TEqp + TPlayFileAttrib(放像文件属性) + TPlayFileMediaInfo(放象文件媒体信息)
//返回的信道号位于消息头
OSPEVENT( REC_UMS_STARTPLAY_ACK,			EV_UMS_MCUREC_BGN + 31 );
//拒绝MCU播放应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STARTPLAY_NACK,			EV_UMS_MCUREC_BGN + 32 );

//UMS请求暂停，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_PAUSEPLAY_REQ,			EV_UMS_MCUREC_BGN + 35 );
//REC同意暂停请求，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_PAUSEPLAY_ACK,			EV_UMS_MCUREC_BGN + 36 );
//REC拒绝暂停请求，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_PAUSEPLAY_NACK,			EV_UMS_MCUREC_BGN + 37 );

//继续播放请求，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_RESUMEPLAY_REQ,			EV_UMS_MCUREC_BGN + 40 );
//同意继续播放，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_RESUMEPLAY_ACK,			EV_UMS_MCUREC_BGN + 41 );
//拒绝继续播放，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_RESUMEPLAY_NACK,			EV_UMS_MCUREC_BGN + 42 );

//停止播放请求，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_STOPPLAY_REQ,				EV_UMS_MCUREC_BGN + 45 );
//同意停止播放应答,REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STOPPLAY_ACK,				EV_UMS_MCUREC_BGN + 46 );
//拒绝停止播放应答,REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STOPPLAY_NACK,			EV_UMS_MCUREC_BGN + 47 );

//请求以快进方式播放，UMS->REC，消息体为TEqp+快进倍数(u8)
OSPEVENT( UMS_REC_FFPLAY_REQ,				EV_UMS_MCUREC_BGN + 50 );
//同意快进方式播放应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_FFPLAY_ACK,				EV_UMS_MCUREC_BGN + 51 );
//拒绝快进方式播放应答,REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_FFPLAY_NACK,				EV_UMS_MCUREC_BGN + 52 );

//请求以快退方式播放，UMS->REC，消息体为TEqp+快退倍数(u8)
OSPEVENT( UMS_REC_FBPLAY_REQ,				EV_UMS_MCUREC_BGN + 55 );
//同意快退方式播放应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_FBPLAY_ACK,				EV_UMS_MCUREC_BGN + 56 );
//拒绝快退方式播放应答,REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_FBPLAY_NACK,				EV_UMS_MCUREC_BGN + 57 );

//UMS请求将播放进度调整到新的位置，消息体为TEqp+TRecProg
OSPEVENT( UMS_REC_SEEK_REQ,					EV_UMS_MCUREC_BGN + 60 );
//同意调整应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_SEEK_ACK,					EV_UMS_MCUREC_BGN + 61 );
//调整拒绝，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_SEEK_NACK,				EV_UMS_MCUREC_BGN + 62 );
//调整录像机RTCP参数，UMS->REC，消息体：TEqp+要设置第几路参数(u8)+TRecRtcpBack
OSPEVENT( UMS_REC_SETRTCP_NFY,				EV_UMS_MCUREC_BGN + 29 );


////////////////
//录像消息
//消息体为TMt(被录像的终端，如果UMS号为空，表示对会议录像。以下请求同)
// + TEqp( 所要使用得录像机) + TRecStartPara + TMediaEncrypt(video) +
//TDoublePayload(video) + TMediaEncrypt(audio) + TDoublePayload(video) +
//TMediaEncrypt(double video) + TDoublePayload(double video) + 录像名 + TCapSupportEx
OSPEVENT( UMS_REC_STARTREC_REQ,				EV_UMS_MCUREC_BGN + 70 );
//同意UMS录像请求应答，REC->UMS，消息体为TEqp，返回的信道号位于消息头
OSPEVENT( REC_UMS_STARTREC_ACK,				EV_UMS_MCUREC_BGN + 71 );
//拒绝UMS录像应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STARTREC_NACK,			EV_UMS_MCUREC_BGN + 72 );

//UMS请求暂停录像，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_PAUSEREC_REQ,				EV_UMS_MCUREC_BGN + 75 );
//REC同意暂停录像请求，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_PAUSEREC_ACK,				EV_UMS_MCUREC_BGN + 76 );
//REC拒绝暂停录像请求，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_PAUSEREC_NACK,			EV_UMS_MCUREC_BGN + 77 );

//继续录像请求，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_RESUMEREC_REQ,			EV_UMS_MCUREC_BGN + 80 );
//同意继续录像，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_RESUMEREC_ACK,			EV_UMS_MCUREC_BGN + 81 );
//拒绝继续录像,REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_RESUMEREC_NACK,			EV_UMS_MCUREC_BGN + 82 );

//停止录像请求，UMS->REC，消息体为TEqp
OSPEVENT( UMS_REC_STOPREC_REQ,				EV_UMS_MCUREC_BGN + 85 );
//同意停止录像应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STOPREC_ACK,				EV_UMS_MCUREC_BGN + 86 );
//拒绝停止录像应答，REC->UMS，消息体为TEqp
OSPEVENT( REC_UMS_STOPREC_NACK,				EV_UMS_MCUREC_BGN + 87 );

//改变录像模式请求, 消息体TMt ＋ u8( REC_MODE_NORMAL, REC_MODE_SKIPFRAME )
OSPEVENT( UMS_REC_CHANGERECMODE_REQ,		EV_UMS_MCUREC_BGN + 90 );
//同意，UMS->MCS，消息体为 TMt 
OSPEVENT( REC_UMS_CHANGERECMODE_ACK,		EV_UMS_MCUREC_BGN + 91 );
//反对，UMS->MCS，消息体为 TMt 
OSPEVENT( REC_UMS_CHANGERECMODE_NACK,		EV_UMS_MCUREC_BGN + 92 );

//UMS 请求删除录像机中的记录，UMS->REC ,消息体为TEqp+记录名(0结尾字符串)
OSPEVENT( UMS_REC_DELETERECORD_REQ,			EV_UMS_MCUREC_BGN + 93 );
//录像机同意并成功删除录像文件应答
//消息体为TEqp
OSPEVENT( REC_UMS_DELETERECORD_ACK,			EV_UMS_MCUREC_BGN + 94);
//录像机拒绝删除录像 消息体TEqp
OSPEVENT( REC_UMS_DELETERECORD_NACK,		EV_UMS_MCUREC_BGN + 95 );

//UMS请求更改记录文件, UMS->REC
//消息体为TEqp + u8(旧记录名长度) + 旧记录名 + u8(新记录名长度) + 新记录名
OSPEVENT( UMS_REC_RENAMERECORD_REQ,			EV_UMS_MCUREC_BGN + 96 );
//同意，消息体为TEqp
OSPEVENT( REC_UMS_RENAMERECORD_ACK,			EV_UMS_MCUREC_BGN + 97 );
//反对，消息体为TEqp
OSPEVENT( REC_UMS_RENAMERECORD_NACK,		EV_UMS_MCUREC_BGN + 98 );


//取消发布录像请求 UMS->REC，消息体为TEqp +  录像名
OSPEVENT( UMS_REC_CANCELPUBLISHREC_REQ,		EV_UMS_MCUREC_BGN + 105 );
//同意，REC->UMS，消息体为 TEqp
OSPEVENT( REC_UMS_CANCELPUBLISHREC_ACK,		EV_UMS_MCUREC_BGN + 106 );
//反对，REC->UMS，消息体为 TEqp
OSPEVENT( REC_UMS_CANCELPUBLISHREC_NACK,	EV_UMS_MCUREC_BGN + 107 );
//录像机请求关键帧
OSPEVENT( REC_UMS_NEEDIFRAME_CMD,	        EV_UMS_MCUREC_BGN + 108 );
//调整录像源的BACKRTCP
/*OSPEVENT( UMS_REC_ADJUST_BACKRTCP_CMD,	        EV_MCUREC_BGN + 109 );*/

//通知交换建立成功
OSPEVENT(UMS_EQP_SWITCHSTART_NOTIF,			26035);

//录像机错误码
#define ERR_REC_BGN				24001

#define ERR_REC_NOERROR         ERR_REC_BGN + 0        //没有错误
#define ERR_REC_NORECORD        ERR_REC_BGN + 1        //没有记录
#define ERR_REC_OPENRECORD      ERR_REC_BGN + 2        //打开记录失败
#define ERR_REC_UMMATCHCMD      ERR_REC_BGN + 3        //不匹配的命令！例如让一个播放设备开始录像
#define ERR_REC_VALIDCHN        ERR_REC_BGN + 4        //无效的通道
#define ERR_REC_RECORDING       ERR_REC_BGN + 5        //正在录像
#define ERR_REC_PLAYING         ERR_REC_BGN + 6        //正在播放
#define ERR_REC_NOTPLAY         ERR_REC_BGN + 7        //播放通道没在播放 
#define ERR_REC_NOTRECORD       ERR_REC_BGN + 8        //录像通道没在录像
#define ERR_REC_ACTFAIL         ERR_REC_BGN + 9        //执行指定的请求动作失败
#define ERR_REC_CURDOING        ERR_REC_BGN + 10       //请求的动作当前正在执行
#define ERR_REC_RCMD_TO_PCHN    ERR_REC_BGN + 11       //一条播放通道命令发到录像通道
#define ERR_REC_PCMD_TO_RCHN    ERR_REC_BGN + 12       //一条录像通道命令发到播放通道
#define ERR_REC_DISKFULL        ERR_REC_BGN + 13       //磁盘满
#define ERR_REC_FILEDAMAGE      ERR_REC_BGN + 14       //文件损坏
#define ERR_REC_FILEEMPTY       ERR_REC_BGN + 15       //空文件
#define ERR_REC_FILEUSING       ERR_REC_BGN + 16       //指定文件正在被操作
#define ERR_REC_FILENOTEXIST    ERR_REC_BGN + 17       //指定文件不存在
#define ERR_REC_PUBLICFAILED    ERR_REC_BGN + 18       //发布失败
#define ERR_REC_RENAMEFILE      ERR_REC_BGN + 19       //文件名冲突,更改文件名失败
#define ERR_REC_FILEEXISTED     ERR_REC_BGN + 20       //文件名冲突,无法录像
#define ERR_REC_PLAYERRPAYLOAD  ERR_REC_BGN + 21       //放像文件媒体载荷类型与会议不匹配
#define ERR_REC_CALLLIBFAILED   ERR_REC_BGN + 22       //调用录像库失败,建议重新安装
#define ERR_REC_SETMOTHODFAILED ERR_REC_BGN + 23       //录像方式设置失败
#define ERR_REC_PALYFILERES		ERR_REC_BGN + 24	   //录像文件分辨率偏大
#define ERR_REC_FILENAMETOOLONG ERR_REC_BGN + 25       //输入文件名过长    // add by jlb  081026
#define ERR_REC_HAS_UNDERLINE	ERR_REC_BGN + 26       //用户输入录像文件文件名中包含下划线字符 // [8/1/2011 liuxu]
#define ERR_REC_WRITE_FILE_ERR	ERR_REC_BGN + 27       //写文件出错, 录像终止 // [8/1/2011 liuxu]
#define ERR_REC_CREATE_SNDSOCK  ERR_REC_BGN + 28    //发送模块创建socket失败 // [pengjie 2011/8/25]
#define ERR_REC_PLAYFILE_HPDISMATCH  ERR_REC_BGN + 29    //会议不支持放像文件的high profile属性[zhouyiliang 20120309]

#ifdef WIN32
#pragma pack( pop )
#endif

#endif