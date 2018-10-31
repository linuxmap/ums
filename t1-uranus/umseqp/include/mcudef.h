#ifndef _MCUDEF_H_
#define _MCUDEF_H_
#include "kdvtype.h"
#include "tpsys.h"

#ifdef WIN32
#pragma pack( push )
#pragma pack( 1 )
#endif

#define		MAXLEN_EQP_ALIAS				16

//OS����
#define     OS_TYPE_VXWORKS                 1   //Vx
#define     OS_TYPE_LINUX                   2   //Linux
#define     OS_TYPE_WIN32                   3   //Windows

//�豸���ඨ��
#define		TYPE_MCU                     	 1   //MCU
#define		TYPE_MCUPERI                     2   //MCU����
#define		TYPE_MT                          3   //�ն�

//�������� ���ṹ���е�brdID
#define     BRD_TYPE_HDU2                   0x25
#define     BRD_TYPE_MPU2					0x26
#define     BRD_TYPE_MPU2ECARD				0x27
#define		BRD_TYPE_APU2					0x28

//����ģʽ
#define     TYPE_MPU2BAS_ENHANCED			17   //MPU2 Bas(Enhanced)����ģʽ
#define     TYPE_MPU2BAS_BASIC				18   //MPU2 Bas(Basic)����ģʽ
#define     TYPE_MPU2VMP_ENHANCED			19   //MPU2 VMP(Enhanced)����ģʽ
#define     TYPE_MPU2VMP_BASIC				20   //MPU2 VMP(Basic)����ģʽ

//����������
#define     MPU2_VMP_BASIC					(u8)8	//MPU2 vmp-basic
#define		MPU2_VMP_ENHACED				(u8)9	//MPU2 vmp-enhanced
#define		TYPE_MPU2_ENHANCED				(u8)5	//MPU2-Enhanced
#define		TYPE_MPU2_BASIC					(u8)6	//MPU2-Basic

#define		MAXNUM_BRD_EQP					5    //�������ܵ����������Ŀ
#define		MAXLEN_BRDALIAS					8	 //���������

#define		MAXNUM_MAP						5	//�������map��

//�豸���ඨ��---�������Ͷ���
#define		EQP_TYPE_MIXER					 1   //������
#define		EQP_TYPE_VMP                     2   //ͼ��ϳ���
#define		EQP_TYPE_RECORDER                3   //¼���
#define		EQP_TYPE_BAS                     4   //����������
#define		EQP_TYPE_TVWALL                  5   //����ǽ
#define     EQP_TYPE_HDU2					 10	 //�������ֵ���ǽ2��

//conf id len
#define     MAXLEN_CONFID                   16
#define     LOCAL_MCUID                     192					//����MCU ID 
#define		LOCAL_MCUIDX					19200				//����MCU IDX
#define		INVALID_MCUIDX					0xffff				//�Ƿ�mcuidx��

#define     MAXLEN_KEY                      16   //���ļ���key����

//������ܷ�ʽ����
#define     CONF_ENCRYPTMODE_NONE            0 //������
#define     CONF_ENCRYPTMODE_DES             1 //des����
#define     CONF_ENCRYPTMODE_AES             2 //aes����
#define     CONF_ENCRYPTMODE_QT              3 //���Ӽ���
#define		GETBBYTE(b)						((b)?1:0)

//��Ϣ�������
#define      SERV_MSG_LEN					0x7000  //��Ϣ����
#define      SERV_MSGHEAD_LEN				0x30    //��Ϣͷ����

//����ϳɲ������
#define		MAXNUM_VMP_MEMBER				25  //����ϳ��������
#define		MAXNUM_MPU2VMP_CHANNEL         (u8)9

//����ϳɳ�Ա���Ͷ���
#define		VMP_MEMBERTYPE_NULL				 0  //û��ָ����Ա
#define		VMP_MEMBERTYPE_MCSSPEC           1  //���ָ�� 
#define		VMP_MEMBERTYPE_SPEAKER           2  //�����˸���
#define		VMP_MEMBERTYPE_CHAIRMAN          3  //��ϯ����
#define		VMP_MEMBERTYPE_POLL              4  //��ѯ��Ƶ����
#define		VMP_MEMBERTYPE_VAC               5	//��������(��ز�Ҫ�ô�����)
#define		VMP_MEMBERTYPE_VMPCHLPOLL        6  //vmp��ͨ����ѯ
#define		VMP_MEMBERTYPE_DSTREAM           7  //˫������


#define		TYPE_APU2_BAS					(u8)8	//APU2 BAS����
#define		TYPE_8KI_VID_BAS				(u8)9   //8KI ��ƵBAS�������Ͷ���
#define		TYPE_8KI_AUD_BAS				(u8)10  //8KI ��ƵBAS�������Ͷ���

#define		MAXNUM_APU2_BASCHN					(u8)7		//apu2����֧����������ͨ����
#define		MAXNUM_8KI_AUD_BASCHN				(u8)4		//8kI aud bas����֧����������ͨ����

//����ϳɷ��Ĭ��RGBֵ
#define     VMPSTYLE_DEFCOLOR               (u32)(246|(246<<8)|(246<<16))// r|(g<<8)|(b<<16)
//����ϳ���󷽰�����
#define     MAX_VMPSTYLE_NUM                5
//HDUԤ����󷽰�����
#define   MAX_HDUSTYLE_NUM                  16
// ����ϳɷ���������󳤶�
#define  MAX_VMPSTYLE_ALIASLEN              32   
// ����ϳ��������
// ����
#define FONT_HEI    (u8)01 // ����
#define FONT_SONG   (u8)02 // ���� (Ĭ��)
#define FONT_KAI    (u8)03 // ����
// �ֺ�
#define FONT_SIZE_24  24	// 24*24 (Ĭ��)
#define FONT_SIZE_32  32	// 32*32
// ���뷽ʽ
#define LEFT_ALIGN    (u8)1  // ��
#define MIDDLE_ALIGN  (u8)2  // ��
#define RIGHT_ALIGN   (u8)3  // ��

// VMP����ͨ����ʾģʽ
// VMP����ͨ����ʾΪ��ɫ
#define VMP_SHOW_BLACK_MODE           0
// VMP����ͨ����ʾ���һ֡
#define VMP_SHOW_LASTFRAME_MODE       1
// VMP����ͨ����ʾĬ��ͼƬ��480*272
#define VMP_SHOW_DEFPIC_MODE          2 
// VMP����ͨ����ʾ�û��Զ���ͼƬ
#define VMP_SHOW_USERDEFPIC_MODE      3
// End

// ����ϳ�����Ĭ��������ɫ
#define DEFAULT_TEXT_COLOR  (u32)(44|(94<<8)|(180<<16))  // blue
// ����ϳ�����Ĭ�ϱ���ɫ
#define DEFAULT_BACKGROUND_COLOR (u32)(255|(255<<8)|(255<<16)) // white
// ����ϳ�����Ĭ��͸����
#define DEFAULT_DIAPHANEITY   0 // 
// ����ϳ�����Ĭ���ı�����
#define DEFAULT_TEXT_LEN     (u8)32 
// ����ϳ�����Ĭ�ϸ߶�
#define wDEFAULT_BMP_HEIGHT  (u16)50 
// BMP�ļ������С
#define  MAX_BMPFILE_SIZE   (u32)800*600  
// ���BMP�ļ����ݴ�С
#define  MAX_BMPDATA_BUFFER (u32)720*576  

//����ϳɷ����
#define		VMP_STYLE_DYNAMIC                0   //��̬����(���Զ��ϳ�ʱ��Ч)
#define		VMP_STYLE_ONE                    1   //һ����
#define		VMP_STYLE_VTWO                   2   //�����棺���ҷ� 
#define		VMP_STYLE_HTWO                   3   //������: һ��һС
#define		VMP_STYLE_THREE                  4   //������
#define		VMP_STYLE_FOUR                   5   //�Ļ���
#define		VMP_STYLE_SIX                    6   //������ 
#define		VMP_STYLE_EIGHT                  7   //�˻���
#define		VMP_STYLE_NINE                   8   //�Ż���
#define		VMP_STYLE_TEN                    9   //ʮ����
#define		VMP_STYLE_THIRTEEN               10  //ʮ������
#define		VMP_STYLE_SIXTEEN                11  //ʮ������
#define		VMP_STYLE_SPECFOUR               12  //�����Ļ��� 
#define		VMP_STYLE_SEVEN                  13  //�߻���
#define		VMP_STYLE_TWENTY				 14  //��ʮ����
#define		VMP_STYLE_TEN_H  				 15  //ˮƽ�ָ��ʮ����(��2��8)
#define     VMP_STYLE_SIX_L2UP_S4DOWN        16  //����������(��2��4)  
#define     VMP_STYLE_FOURTEEN               17  //ʮ�Ļ���
#define     VMP_STYLE_TEN_M                  18  //ʮ����(��4��2��4)
#define     VMP_STYLE_THIRTEEN_M             19  //ʮ������(һ�����м�)
#define     VMP_STYLE_FIFTEEN                20  //ʮ�廭��
#define     VMP_STYLE_SIX_DIVIDE             21  //������(�ȷ�)
#define     VMP_STYLE_THREE_2BOTTOMRIGHT	 22  //�����棬2��С���ڵײ�����
#define     VMP_STYLE_THREE_2BOTTOM2SIDE     23  //�����棬2��С���ڵײ�����
#define     VMP_STYLE_THREE_2BOTTOMLEFT      24  //�����棬2��С���ڵײ�����
#define     VMP_STYLE_THREE_VERTICAL         25  //�����棬��ֱ�ȴ�
#define     VMP_STYLE_FOUR_3BOTTOMMIDDLE     26  //�Ļ��棬3���ڵײ�����
#define     VMP_STYLE_TWENTYFIVE			 27  //��ʮ�廭��

#define		VMPSTYLE_NUMBER					 (VMP_STYLE_TWENTYFIVE+1)
#define     VMP_STYLE_NONE                  0xff //��֧�ֵĸ�ʽ

//�������ز���

//��������ͨ�����Ͷ���
#define     TYPE_MAU_NORMAL                 (u8)0   //��ͨMAU
#define     TYPE_MAU_H263PLUS               (u8)1   //ΪH263plus���Ƶ�MAU
#define     TYPE_MPU                        (u8)2   //MPU
#define     TYPE_8KE_BAS					(u8)3   //[03/01/2010] zjl add
#define     TYPE_MPU_H						(u8)4   //MPU_H
#define		TYPE_MPU2_ENHANCED				(u8)5	//MPU2-Enhanced
#define		TYPE_MPU2_BASIC					(u8)6	//MPU2-Basic
#define		TYPE_8KH_BAS					(u8)7	//[03/31/2011] nzj add

#define MAXNUM_MPU_CHN                      (u8)4
#define MAXNUM_MPU_H_CHN					(u8)2       //mpu_h�������ͨ����
#define MAXNUM_MPU2_BASIC_CHN               (u8)4		//mpu2 basic�������ͨ����
#define MAXNUM_MPU2_EHANCED_CHN				(u8)7       //mpu2 enhanced�������ͨ����

//����ͨ������
#define MPU2_BAS_CHN_MV						(u8)9       //HDBAS MPU2 ����ͨ��
#define MPU2_BAS_CHN_DS						(u8)10      //HDBAS MPU2 ˫��ͨ��
#define MPU2_BAS_CHN_SEL					(u8)11      //HDBAS MPU2 ѡ��ͨ��

#define     MAXNUM_BASOUTCHN				(u8)12	    //bas������ͨ����

//����ǽ��ز���
#define		MAXNUM_HDU_CHANNEL              2   //һ��HDU�����ͨ����
//HDU����ģʽ
#define STARTMODE_HDU_M						(u8)0      //hduԭ��ģʽ
#define STARTMODE_HDU_H						(u8)1      //hdu��ͨ��ģʽ
#define STARTMODE_HDU_L						(u8)2	   //hdu������ģʽ
#define STARTMODE_HDU2						(u8)3	   //hdu2������
#define STARTMODE_HDU2_L					(u8)4	   //hdu2-L������
#define STARTMODE_HDU2_S					(u8)5	   //hdu2-S������, ����������ϳ�

#define DEVVER_HDU			(u16)4501
#define DEVVER_HDU2			(u16)4701
#define DEVVER_HDU2_L	    (u16)4702
#define DEVVER_HDU2_S	    (u16)4703 


#define HDUCHN_MODE_ONE						(u8)0   //һ������ģʽ
#define HDUCHN_MODE_FOUR					(u8)1   //�Ļ�����ģʽ						

//¼������

// MCUǰ���������������
#define		FECTYPE_NONE					(u8)(0x00)
#define		FECTYPE_RAID5					(u8)(0x01)
#define		FECTYPE_RAID6					(u8)(0x02)

//�ϲ���Ƶ֡�ʶ���(���ڷ�H.264��H.264ֱ����VIDEO_FPS_USRDEFINED+��ֵ��ʾ֡��)
#define     VIDEO_FPS_2997_1                1   //30 ֡/s
#define     VIDEO_FPS_25                    2   //25 ֡/s(�ײ㰴30֡����)
#define     VIDEO_FPS_2997_2                3   //15 ֡/s
#define     VIDEO_FPS_2997_3                4   //10 ֡/s
#define     VIDEO_FPS_2997_4                5   //7.5֡/s
#define     VIDEO_FPS_2997_5                6   //6  ֡/s
#define     VIDEO_FPS_2997_6                7   //5  ֡/s
#define     VIDEO_FPS_2997_30               8   //1  ֡/s
#define     VIDEO_FPS_2997_7P5              9   //4  ֡/s
#define     VIDEO_FPS_2997_10               10  //3  ֡/s
#define     VIDEO_FPS_2997_15               11  //2  ֡/s
#define     VIDEO_FPS_USRDEFINED            128 //�Զ���֡��(>=128,��ȥ128��Ϊʵ��֡��)

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
#define     VIDEO_FORMAT_384x272            46  // 384��272(1/5)

//�Ǳ�ֱ��ʣ�720p��ͼ�� �������ն˷ֱ��ʸı�
#define     VIDEO_FORMAT_720_960x544        51  //960��544(3/4)
#define     VIDEO_FORMAT_720_864x480        52  //864��480(2/3)
#define     VIDEO_FORMAT_720_640x368        53  //640��368(1/2)
#define     VIDEO_FORMAT_720_432x240        54  //432��240(1/3)
#define     VIDEO_FORMAT_720_320x192        55  //320��192(1/4)

//�Ǳ�ֱ��ʣ�1080p��ͼ���������ն˷ֱ��ʸı�
#define		VIDEO_FORMAT_640x544			56	//640x544
#define		VIDEO_FORMAT_320x272			57	//320x272

//////////////////////////////////////////////////////////////////////////
//�ṹ�嶨��

/* ������ݽṹ���� */
typedef struct tTagBrdPos 
{
    u8 byBrdID;                      /* ����ID�� */
    u8 byBrdLayer;                   /* �������ڲ�ţ��豸��֧��ʱ����0������0�㴦�� */
    u8 byBrdSlot;                    /* �������ڲ�λ�ţ��豸��֧��ʱ����0������0�۴���;
									 �����豸������֮�֣���slot�����֣�0=����1=�� */
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
    s8 m_achAlias[MAXLEN_EQP_ALIAS+1]; // zw 20090309 ��ʱû���õ�
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

//����Žṹ (len:16)
struct CConfId
{
protected:
	u8  	m_abyConfId[MAXLEN_CONFID];
	
public:
	u8   GetConfId( u8   * pbyConfId, u8   byBufLen ) const; //��û��������
	void CreateConfId( u8 byUsrGrpId );                               //���������
	void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const;//��û�����ַ���
	void SetConfId( const CConfId & cConfId );                  //���û����
	u8   SetConfId( const u8   * pbyConfId, u8   byBufLen );          //���û��������
	u8   SetConfId( LPCSTR lpszConfId );                          //���û��������	
	BOOL IsNull( void ) const;                                  //�жϻ�����Ƿ�Ϊ��
	void SetNull( void );                                       //���û����Ϊ��
	BOOL operator == ( const CConfId & cConfId ) const;         //����������
    // ���񻪣���CConfId�������û������Ϣ
    u8   GetUsrGrpId() const 
    {
        return m_abyConfId[MAXLEN_CONFID-1];
    }
    void SetUsrGrpId(u8 byGrpId)
    {
        m_abyConfId[MAXLEN_CONFID-1] = byGrpId;
    }
	
	//fuxiuhua,���ӻ��鷢����Ϣ
	//����ID����ɣ�MCU��(2Byte)/��������(1Byte)/��������ֵ(1Byte)/����Ų�������(4Byte)/
	//              δ��(6Byte)/��������(1Byte)/���(1Byte)
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
//ҵ����Ϣ�࣬�����28K������Ϣ
class CServMsg
{
protected:
	u16     m_wSerialNO;            //��ˮ��
	u8      m_bySrcDriId;           //ԴDRI���
	u8      m_bySrcMtId;            //Դ�ն˺�
	u8      m_bySrcSsnId;           //Դ�Ự��
	u8      m_byDstDriId;           //Ŀ��DRI���
    u8      m_byDstMtId;            //Ŀ���ն˺�
	u8      m_byMcuId;              //MCU��
	u8      m_byChnIndex;           //ͨ��������
    u8      m_byConfIdx;            //����������
	CConfId m_cConfId;              //�����
	u16		m_wEventId;             //�¼���
	u16		m_wTimer;               //��ʱ
	u16		m_wErrorCode;           //������
	u16		m_wMsgBodyLen;          //��Ϣ�峤��
    u8      m_byTotalPktNum;        //�ܰ�����������Ҫ�а����͵���Ϣ��
    u8      m_byCurPktIdx;          //��ǰ����������0��ʼ��
	u8      m_abyReserverd[12];     //�����ֽ�
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //��Ϣ��
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
	void ClearHdr( void );//��Ϣͷ����
	CConfId GetConfId( void ) const;//��ȡ�������Ϣ
	void SetConfId( const CConfId & cConfId );//���û������Ϣ
	void SetNullConfId( void );//���û������ϢΪ��
	u16  GetMsgBodyLen( void ) const;//��ȡ��Ϣ�峤����Ϣ
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//��ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
	u8   * const GetMsgBody( void ) const;//��ȡ��Ϣ��ָ�룬�û������ṩBUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//������Ϣ��
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//�����Ϣ��
	u16  GetServMsgLen( void ) const;//��ȡ������Ϣ����
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//��ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
	u8   * const GetServMsg( void ) const;//��ȡ������Ϣָ�룬�û������ṩBUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//����������Ϣ
	const CServMsg & operator= ( const CServMsg & cServMsg );//����������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, Ҫ��ֵ����Ϣָ��
				  u16 wMsgLen, Ҫ��ֵ����Ϣ���ȣ�������ڵ��� SERV_MSGHEAD_LEN
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
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
    ������      ��~CServMsg
    ����        ��distructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    ������      ��Init
    ����        ��BUFFER��ʼ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//����
}

/*====================================================================
    ������      ��ClearHdr
    ����        ����Ϣͷ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//����
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    ������      ��GetConfId
    ����        ����ȡ�������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ������ţ�ȫ0��ʾ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline CConfId CServMsg::GetConfId( void ) const
{
	return( m_cConfId );
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId������ţ�ȫ0��ʾ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline void CServMsg::SetConfId( const CConfId & cConfId )
{
	m_cConfId = cConfId;
}

/*====================================================================
    ������      ��SetNullConfId
    ����        �����û������ϢΪ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/06    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CConfId		cConfId;
	
	cConfId.SetNull();
	SetConfId( cConfId );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ��Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    ������      ��SetMsgBodyLen
    ����        ��������Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMsgBodyLen, ��Ϣ�峤��
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ��ָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ������Ϣ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��������Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBodyBuf, ���ص���Ϣ��
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    ������      ��SetMsgBody
    ����        ��������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
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
    ������      ��CatMsgBody
    ����        �������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/11/07    1.0         Liaoweijiang  ����
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
    ������      ��GetMsgBody
    ����        ����ȡ������Ϣָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    ������      ��GetServMsg
    ����        ����ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBuf, ���ص���Ϣ
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    ������      ��SetServMsg
    ����        ������������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, �����������Ϣ
				  u16 wMsgLen, �������Ϣ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
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
    ������      ��operator=
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����CServMsg & cServMsg, ��ֵ����Ϣ����
    ����ֵ˵��  ��CServMsg����Ӧ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
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
    ������      ��GetConfId
    ����        ����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyConfId, �����BUFFER����ָ�룬�������ػ����
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline u8 CConfId::GetConfId( u8 * pbyConfId, u8 byBufLen ) const
{
	u8	byLen = min( sizeof( m_abyConfId ), byBufLen );
	memcpy( pbyConfId, m_abyConfId, byLen );

	return( byLen );
}

/*====================================================================
    ������      ��GetConfIdString
    ����        ����û�����ַ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����LPSTR lpszConfId, ������ַ���BUFFER����ָ�룬����
	                   ����0��β������ַ���
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
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
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId, ��������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline void CConfId::SetConfId( const CConfId & cConfId )
{
	cConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const u8 * pbyConfId, ���������ָ��
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�����������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline u8 CConfId::SetConfId( const u8 * pbyConfId, u8 byBufLen )
{
	u8	bySize = min( byBufLen, sizeof( m_abyConfId ) );
	
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	memcpy( m_abyConfId, pbyConfId, bySize );

	return( bySize );
}
	
/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����LPCSTR lpszConfId, ����Ļ�����ַ���
    ����ֵ˵��  ��ʵ�����������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
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
    ������      ��CreateConfId
    ����        �����������
    �㷨ʵ��    �����ݵ�ǰʱ������ֵ
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/06    1.0         LI Yi         ����
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

    // ���� [6/21/2006]
    // ���λ��ʾ��ID
    SetUsrGrpId( byUsrGrpId );
}

/*====================================================================
    ������      ��IsNull
    ����        ���жϻ�����Ƿ�Ϊ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/03/31    1.0         LI Yi         ����
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
    ������      ��SetNull
    ����        �����û����Ϊ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/03/31    1.0         LI Yi         ����
====================================================================*/
inline void CConfId::SetNull( void )
{
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
}

/*====================================================================
    ������      ��operator==
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId, ��������
    ����ֵ˵��  ����ȷ���TRUE�����򷵻�FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
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
//�����MCU���ն˻�����ṹ (len:6)
struct TMtNoConstruct
{
protected:
    u8          m_byMainType;   //�豸����
    u8  		m_bySubType;	//�豸����
	u8  		m_byMcuId;		//MCU��
	u8  		m_byEqpId;	    //�豸��	
	u8          m_byConfDriId;  //DRI���
    u8          m_byConfIdx;    //���������ţ�������ʵ���� 1 - MAXNUM_MCU_CONF

public:
	// ���ýṹ����
	void   SetType( u8   byType )
	{ 
		m_byMainType = ( (m_byMainType & 0xf0) | (byType & 0xf) ) ; 
	}         

	// �õ��ṹ����
	u8     GetType( void ) const { return m_byMainType & 0xf; }     
	
	// fxh ��GetMcuIdƥ�����������ԭu8ͬ������
	void   SetMcuId( u16  wMcuId )	{ SetMcuIdx(wMcuId); } 
    
	// �õ�McuId
	u16     GetMcuId( void ) const { return GetMcuIdx(); }

	// �ж�TMtNoConstruct��TMtNoConstruct�Ƿ����
	BOOL   operator ==( const TMtNoConstruct & tObj ) const;    

	//����MCU����
	//����MCU
	void   SetMcu( u16   wMcuIdx );                         
	void   SetMcuType( u8  byMcuType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCU); 
		m_bySubType = ((m_byMainType & 0xf0)| (byMcuType&0xf) ); 
	}

	u8     GetMcuType( void ) const { return m_bySubType & 0xf; }

	// �������躯��
	// ����MCU����
	void   SetMcuEqp( u8   byMcuId, u8   byEqpId, u8   byEqpType );  
	
	// ����MCU��������
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
	
	//�����ն˺���
	void   SetMt( u16   wMcuIdx, u8   byMtId, u8   m_byDriId = 0, u8   m_byConfIdx = 0);
	void   SetMt( TMt tMt);
	void   SetMtId( u8   byMtId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);	
		m_byEqpId = byMtId; 
	}
	u8     GetMtId( void ) const { return m_byEqpId; }//�����ն�
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

	// ��LOCAL_MCUIDX��ΪLOCAL_MCUID
	BOOL   IsLocal() const 
	{
		// [11/9/2010 liuxu] ���趼�Ǳ����ã�ֱ�ӷ���TRUE
		if (TYPE_MCUPERI == GetType())
		{
			return TRUE;
		}
		
		return (GetMcuIdx() == LOCAL_MCUIDX );		
	}

//[0901]fxh����mcuidx�����걸mcu��ʶ���б��ػ����ɱ���mcuid����ʵ��ϸ�ڽ��з�װ�����ɽ׶Σ����������ӿڽ�ֹ������ã�֮��Ὣ��˽�л�
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
//�����MCU���ն˻�����ṹ (len:6)
struct TMt : public TMtNoConstruct
{
	// [5/25/2011 liuxu] Tmt��TMtNoConstruct��ȡ���׽ṹ,���ݻ���һ��, ά��������,
	// Ҳ���ںܴ������. �����������������. TMtNoConstruct��ʱ���ܱ��ϳ�,ԭ��(Դ��zjj):
	// ���ǵĴ������õ��˺ܶ�������ṹ,�����������г�Ա�����й��캯��,��Tmt���ڹ��캯��
	// ����������Ҫ�������캯����TMtNoConstruct.
	
public:
	// ���캯��
	TMt()
	{
		memset( this,0,sizeof(TMt) );
		SetMcuIdx( INVALID_MCUIDX );
	}
	
	// ���캯��
	TMt( const TMtNoConstruct& tOther )
	{
		memcpy( this, &tOther, sizeof(TMtNoConstruct) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//�����ն˽ṹ
typedef TMt TEqp;
typedef TMtNoConstruct TEqpNoConstruct;
//����ע��������Ϣ��
struct TPeriEqpRegReq : public TEqp
{
protected:
	u32   		m_dwIpAddr;		//����IP��ַ
	u16 		m_wStartPort;	//������ʼ���ն˿�
	u8  		m_byChannlNum;	//��������ŵ���
	s8          m_achAlias[MAXLEN_EQP_ALIAS];
    //4.0R3��չ�ֶ�
    u16         m_wVersion;     //�汾��Ϣ
    //4.5������չ�ֶ�
    BOOL        m_bHDEqp;       //�Ƿ��������
	
public:
    TPeriEqpRegReq(void) { memset(this, 0, sizeof(TPeriEqpRegReq)); }
    //��������IP��ַ
    //���룺IP��ַ(������)
	void SetPeriEqpIpAddr( const u32    &dwIpAddr )	{ m_dwIpAddr = dwIpAddr; }
    //�������IP��ַ
    //����ֵ��IP��ַ(������)
	u32    GetPeriEqpIpAddr() const	{ return m_dwIpAddr; }
	//�������������ʼ�˿�
	void SetStartPort( const u16  & wStartPort )	{ m_wStartPort = htons(wStartPort); }
	//������������ʼ�˿�
	u16  GetStartPort() const	{ return ntohs( m_wStartPort ); }
	//������������ŵ���Ŀ
	void SetChnnlNum( const u8   & byChannlNum )	{ m_byChannlNum = byChannlNum; }
	//�����������ŵ���Ŀ
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
//��������Ǽǳɹ���Ϣ�ṹ
struct TPeriEqpRegAck
{
protected:
	u32   		m_dwIpAddr;			//MCU���յ�ַ
	u16 		m_wStartPort;		//MCU������ʼ�˿ں�
    u32         m_dwAnotherMpcIp;   //����ʱ������һ��mpc���ַ���������������õı���mpc��ַ����У�飩
	u32         m_dwMsSSrc;         //����ʱ�����ڱ�עһ��ϵͳ���У�ֻҪ��ֵ�仯��˵������������ͬʱ����
	
public:
	//�õ��ϼ�MCU������������IP��ַ
    u32    GetMcuIpAddr( void ) const { return ntohl(m_dwIpAddr); }
	
	//�����ϼ�MCU������������IP��ַ
    void SetMcuIpAddr( u32    dwIpAddr ) { m_dwIpAddr = htonl(dwIpAddr); }
	
	//�õ��ϼ�MCU�����������ݶ˿ں�
    u16  GetMcuStartPort( void ) const { return ntohs(m_wStartPort); }
	
    //�����ϼ�MCU�����������ݶ˿ں�
    void SetMcuStartPort( u16  wPort ) { m_wStartPort = htons(wPort); }
	
    //����һ��mpc���ַ
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
//�ش�ʱ���Ƚṹ (len:16)
struct TPrsTimeSpan
{
    TPrsTimeSpan()
    {
        memset(this, 0, sizeof(TPrsTimeSpan));
    }
    u16  m_wFirstTimeSpan;	  //��һ���ش�����
	u16  m_wSecondTimeSpan;   //�ڶ����ش�����
	u16  m_wThirdTimeSpan;    //�������ش�����
	u16  m_wRejectTimeSpan;   //���ڶ�����ʱ����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�������û���
struct TEqpCfgInfo
{
protected:    
    s8  m_szAlias[MAXLEN_EQP_ALIAS];		//����
    u16 m_wMcuStartPort;					//mcu������ʼ�˿ں�
    u16 m_wEqpStartPort;					//���������ʼ�˿ں�    
    u8  m_byEqpId;							//�豸ID
    u8  m_bySwitchBrdIndex;					//����������     
    u8  m_byRunningBrdIndex;				//���а�����
    u8  m_byMapCount;						//ʹ�õ�MAP����
    u8  m_abyMapId[MAXNUM_MAP];				//Map�������
	
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
	
    //���з��������������MAU���⴦����
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

//����hdu�����ṹ��  ��Χ 0 -- 31
struct THduVolumeInfo:public TEqp
{
protected:
	u8  m_byChnlIdx;    // ͨ��������
	u8  m_byVolume;     // ������С
	u8  m_byIsMute;  // �Ƿ���  
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
	// 1)���ֶε�2λ��ʹ�ã����ڱ�ʶScalingMode [11/29/2011 chendaiwei]
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 


//���崫���ַ�ṹ(len:6)
struct TTransportAddr
{
public:
	u32   		m_dwIpAddr;		//IP��ַ, ������
	u16 		m_wPort;		//�˿ں�, ������
public:
	void   SetNull(void)
	{
		m_dwIpAddr = 0;
		m_wPort = 0;
	}
	
	// [6/2/2011 liuxu] ����ж�
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
	u8  m_byEncryptMode;         //����ģʽ : CONF_ENCRYPTMODE_NONE,CONF_ENCRYPTMODE_DES, CONF_ENCRYPT_AES
    s32 m_nKeyLen;               //����key�ĳ���
	u8  m_abyEncKey[MAXLEN_KEY]; //����key
	u8  m_byReserve;             //����
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
    TTransportAddr m_tVidRtcpBackAddr; //��ƵRTCP������ַ
//	TTransportAddr m_tAudRtcpBackAddr; //��ƵRtcp������ַ
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
	
	//[liu lijiu][20100919]����RTCP������ַ
	//������Ƶ��RTCP������ַ
	void SetVidRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
    {
        m_tVidRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
        m_tVidRtcpBackAddr.SetPort(wRtcpBackPort);
		return;
    }
	
	//��ȡ��Ƶ��RTCP������ַ
    void GetVidRtcpBackAddr(u32 & dwRtcpBackIp, u16 & wRtcpBackPort)
    {
        dwRtcpBackIp = m_tVidRtcpBackAddr.GetIpAddr();
        wRtcpBackPort = m_tVidRtcpBackAddr.GetPort();
        return;
    }
	
	//������Ƶ��RTCP������ַ
// 	void SetAudRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
//     {
//         m_tAudRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
//         m_tAudRtcpBackAddr.SetPort(wRtcpBackPort);
// 		return;
//     }
// 	
// 	//��ȡ��Ƶ��RTCP������ַ
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
//4.6�¼� �汾 jlb
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

//��¼¼���������(��λ:��)
struct  TRecProg
{
protected:
	u32   		m_dwCurProg;	//��ǰ����
	u32   		m_dwTotalTime;	//�ܳ��ȣ����ڷ���ʱ��Ч
	
public:
	//���õ�ǰ����λ�ã���λ���룩
	void SetCurProg( u32    dwCurProg )	{ m_dwCurProg = htonl( dwCurProg ); }
	//��ȡ��ǰ����λ�ã���λ���룩
	u32    GetCurProg( void ) const	{ return ntohl( m_dwCurProg ); }
	//�����ܳ��ȣ����Է�����Ч����λ���룩
	void SetTotalTime( u32    dwTotalTime )	{ m_dwTotalTime = htonl( dwTotalTime ); }
	//��ȡ�ܳ��ȣ����Է�����Ч����λ���룩
	u32    GetTotalTime( void ) const	{ return ntohl( m_dwTotalTime ); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//˫�غ�
struct TDoublePayload
{
protected:
	u8  m_byRealPayload;    //ԭý���ʽ
	u8  m_byActivePayload;  //�ý���ʽ
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

// H264��������(HP/BP) [12/8/2011 chendaiwei]
enum emProfileAttrb
{
	emBpAttrb,	//BP
	emHpAttrb,	//HP
};

#define ISHDFORMAT(byRes) \
	(VIDEO_FORMAT_W4CIF == byRes || VIDEO_FORMAT_HD720 == byRes || \
	VIDEO_FORMAT_SXGA == byRes || VIDEO_FORMAT_UXGA == byRes || \
         VIDEO_FORMAT_HD1080 == byRes)

//������Ƶý���ʽ������(len:5)
struct TVideoStreamCap
{
protected:
    u16		m_wMaxBitRate;  // ���λ��ʶHP/BP���ԣ�Ϊ1��ʶHP��Ϊ0��ʾBP [12/2/2011 chendaiwei]
    u8		m_byMediaType;   
    u8      m_byResolution;	//�ֱ��� VIDEO_FORMAT_AUTO, ...
	u8      m_byFrameRate;  //֡�� MPI������ H.264 ���� FPS
    
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

    // guzh [12/1/2007] �Զ���֡�ʵı���/��ȡ
    void    SetUserDefFrameRate(u8 byActFrameRate) { m_byFrameRate = VIDEO_FPS_USRDEFINED+byActFrameRate; }
    BOOL32  IsFrameRateUserDefined() const {return (m_byFrameRate>VIDEO_FPS_USRDEFINED); }
    u8      GetUserDefFrameRate(void) const { return IsFrameRateUserDefined() ? m_byFrameRate-VIDEO_FPS_USRDEFINED : m_byFrameRate; }
    
	// m_wMaxBitRate�ĵ�15λ��ʶbitRate [12/2/2011 chendaiwei]
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
	������      ��SetH264ProfileAttrb
	����        ������H264��HP/BP����

	�㷨ʵ��    ��
	����ȫ�ֱ�����
	�������˵����[IN]emProfileAttrb emAttb��ʶHP/BP����

	����ֵ˵��  ��
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��      �汾        �޸���        �޸�����
	2011/11/28  4.0         chendaiwei       ����
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
	������      :GetH264ProfileAttrb
	����        ����ȡH264��HP/BP����

	�㷨ʵ��    ��
	����ȫ�ֱ�����
	�������˵����

	����ֵ˵��  ��[OUT]emProfileAttrb emAttb��ʶHP/BP����
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��      �汾        �޸���        �޸�����
	2011/11/28  4.0         chendaiwei       ����
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

	//TODO �Ƿ����HP/BP�ıȽ� [12/2/2011 chendaiwei]
	BOOL32 IsH264CapLower(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// ����֡��>30, ֡�ʰ�ʵ��25�Ƚ�
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
	
	//�ж������Ƿ����
	BOOL32 IsH264CapEqual(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// ����֡��>30, ֡�ʰ�ʵ��25�Ƚ�
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
	// ����ֱ���֡�ʳ˻����Ƚϴ�С [2012/09/12 nizhijun]
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

	// ����ֱ��ʳ˻����Ƚϴ�С [1/16/2012 chendaiwei]
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

	// ������ӡ [12/12/2011 chendaiwei]
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
        
            //���ھ����ܲ��ſ��ǣ�����ȡ��ֵ
            wWidth = 704;
            wHeight = 576;
            break;
        
        case VIDEO_FORMAT_16CIF:
            wWidth = 1048;
            wHeight = 1152;
            break;
        
        case VIDEO_FORMAT_AUTO:
            //������
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
			//�Ǳ�ֱ��ʣ�1080p��ͼ��
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

			//�Ǳ�ֱ��ʣ�720p��ͼ��
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
        //����������
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

//��������չ�ṹ
struct TCapSupportEx
{
protected:
	u8 m_byVideoFECType;
	u8 m_byAudioFECType;
	u8 m_byDVideoFECType;
    TVideoStreamCap tSecDSCap;      //�ڶ�˫��������H239�������һ˫����������
	
public:
    TCapSupportEx(): m_byVideoFECType(FECTYPE_NONE),
                     m_byAudioFECType(FECTYPE_NONE),
                     m_byDVideoFECType(FECTYPE_NONE)
	{
        tSecDSCap.Clear();
	}

public: //���ʹ�ã��ն������������ն˵�ʱ��ģ���̶ȵ�ͬ�ڻ�أ�Ҳ�øýӿ�.
	void	SetFECType(u8 byFECType)
	{
		m_byVideoFECType = byFECType; 
		m_byAudioFECType = FECTYPE_NONE;
		m_byDVideoFECType = byFECType;
	}

public: //MCUʹ��

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

	// ����˫˫�������� [12/15/2011 chendaiwei]
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
    u32  m_tVideoIp;      //��ƵRTCP������ַ
    u16  m_tVideoPort;    //��ƵRTCP�����˿�
    u32  m_tAudioIp;      //��ƵRTCP������ַ
    u16  m_tAudioPort;    //��ƵRTCP�����˿�
    u32  m_tDStreamIp;    //˫��RTCP������ַ
    u16  m_tDStreamPort;  //˫��RTCP�����˿�
	
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
// // VMP����ͨ����ʾģʽ
// // VMP����ͨ����ʾΪ��ɫ
// #define VMP_SHOW_BLACK_MODE           0
// // VMP����ͨ����ʾ���һ֡
// #define VMP_SHOW_LASTFRAME_MODE       1
// // VMP����ͨ����ʾĬ��ͼƬ��480*272
// #define VMP_SHOW_DEFPIC_MODE          2 
// // VMP����ͨ����ʾ�û��Զ���ͼƬ
// #define VMP_SHOW_USERDEFPIC_MODE      3
// // End

//  [1/8/2010 pengjie] Modify 
// HDU��չ����
struct THDUExCfgInfo
{
	u8  m_byIdleChlShowMode;  // ����ͨ����ʾģʽ HDU_SHOW_GRAY_MODE ...
	
	u8  m_byReserved; // �����ֶ�
	u16 m_wReserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*----------------------------------------------------------------------
�ṹ����THduChnStatus
��;  ��
----------------------------------------------------------------------*/
struct THduChnStatus
{
    enum EHduChnStatus
    {
        eIDLE   = 0, //����
			eREADY  = 1, //׼��
			eNORMAL = 2,  //����,��ʾHDU�豸������
			eRUNNING= 3  //��ʾHDU��ĳ��ͨ�����ڱ���ʹ�� [nizhijun 2010/10/27] add
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
    u8 m_bySchemeIdx; // ���ڱ�ʹ��Ԥ���������� 
    u8 m_byVolume;
	u8 m_byMute;      // �Ƿ���
    TEqpNoConstruct m_tHdu;
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TEqpEntryParam
{
protected:
    u32 m_dwMcuIp;		    /*������Ҫ���ӵ�MCU��IP��ַ ������*/
    u16 m_wMcuPort;			/*������Ҫ���ӵ�MCU�Ķ˿ں� ������*/
    u8  m_byMcuId;		    /*������Ҫ���ӵ�MCU���*/
    
    u8  m_byType;			/*�����������ֵ*/
    u8  m_byConnectState;	/*�����������״̬*/
    u8  m_byExist;			/*�Ƿ�ʹ�øñ���*/

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

//���������Ϣ	
struct TEqpBasicInfo
{
protected:
    u8 m_byEqpId;                       //�豸ID
    s8 m_achAlias[MAXLEN_EQP_ALIAS+1];  //�豸����
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

//�������а������Ϣ
struct TEqpRunBrdInfo
{
protected:
    u8  m_byRunBrdId;       //���а�ID
    u16 m_wEqpRecvPort;     //���а�(����)�������ʼ�˿ں� ������
    u32 m_dwIpAddr;         //���а�Ip
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

//����map�����Ϣ
struct TEqpMapInfo
{
protected:
    u8 m_abyUsedMapId[MAXNUM_MAP];
    u8 m_byMapNum;
public:
    TEqpMapInfo() : m_byMapNum(0){ memset(m_abyUsedMapId, 0, sizeof(m_abyUsedMapId));  }
	
	// ��set����ֻ��Ӧ˳�δ�С����д��
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
    u8 byBrdID;                      // ����ID�� 
    u8 byBrdLayer;                   // �������ڲ��
    u8 byBrdSlot;                    // �������ڲ�λ��
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//4.6������
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

//���廭��ϳɳ�Ա�ṹ (len:8)
struct TVMPMember: public TMtNoConstruct
{
protected:
    u8   m_byMemberType;     //����ϳɳ�Ա����,�μ�vccommon.h�л���ϳɳ�Ա���Ͷ���
    u8   m_byMemStatus;      //��Ա״̬(MT_STATUS_CHAIRMAN, MT_STATUS_SPEAKER, MT_STATUS_AUDIENCE)
	
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

//���廭��ϳɲ����ṹ (len:136 + 4*8 = 168)
struct TVMPParam
{
protected:
	u8      m_byVMPAuto;      //�Ƿ����Զ�����ϳ� 0-�� 1-��
	u8      m_byVMPBrdst;     //�ϳ�ͼ���Ƿ����ն˹㲥 0-�� 1-�� 
	u8      m_byVMPStyle;     //����ϳɷ��,�μ�mcuconst.h�л���ϳɷ����
    u8      m_byVMPSchemeId;  //�ϳɷ�񷽰����,���֧��5�׷���,1-5
    u8      m_byVMPMode;      //ͼ�񸴺Ϸ�ʽ: 0-��ͼ�񸴺� 1-��ػ���ϯ����ͼ�񸴺� 2-�Զ�ͼ�񸴺�(��̬���������ó�Ա)
	u8		m_byRimEnabled;	  //�Ƿ�ʹ�ñ߿�: 0-��ʹ��(Ĭ��) 1-ʹ��;
							  //���ֶ�Ŀǰֻ�Է���0��Ч, ���������ݲ��漰���ֶε����ú��ж�
	//u8		m_byReserved1;	  //�����ֶ�
	//u8		m_byReserved2;	  //�����ֶ�
	u8		m_byVMPBatchPoll; // xliang [12/18/2008] �Ƿ���������ѯ 0-��
	u8		m_byVMPSeeByChairman;	// �Ƿ���ϯMTѡ��	0-��
	TVMPMember  m_atVMPMember[MAXNUM_VMP_MEMBER]; //����ϳɳ�Ա
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
			// ����˫������ͨ��
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
	
	//�ж�����VmpParam�Ƿ����
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

	//����ϳ����зǱ����ĳ�Ա���Ҹó�Ա�ǲ���ָ����memtype
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
	// [3/30/2010 xliang] bLast �����������һ���ҵ���λ��; byFilterPos����Ҫ���˵�ͨ�������ҵ����Ǹ�ͨ���������
	u8 GetChlOfMtInMember( TMt tMt, BOOL32 bLast = FALSE, u8 byFilterPos = MAXNUM_VMP_MEMBER, u8 *pbyPos = NULL, u8 *byPosNum = NULL ) const
	{
        //[zhushz 20110722]�ҳ��ն���������ͨ��
        if( pbyPos != NULL && byPosNum != NULL )
        {
            *byPosNum = 0;
            u8 *pbyTmp = pbyPos;
            for( u8 byIndx = 0; byIndx < GetMaxMemberNum(); byIndx++)
            {
				//����˫������ͨ��
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
			
			//����˫������ͨ��
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
	
	//zhouyiliang 20101019 Ѱ�����ǰ�������һ��mcuindx���ն˵�λ��,bLast = false ʱ���ʼ���Ǹ�
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

//����ϳ���״̬
struct TVmpStatus
{
	enum EnumUseState 
	{ 
		IDLE,		//δ��ռ��
			RESERVE,    //Ԥ��
			WAIT_START, //�ȴ���ʼ��Ӧ
			START,      //�����л���ϳ�
			WAIT_STOP,  //�ȴ�������Ӧ
	};
public:	
	u8        m_byUseState;	    //ʹ��״̬ 0-δʹ�� 1-ʹ��
	u8        m_byChlNum;       //ͨ����
#ifdef _ZGCDEBUG_
	u8		  m_byEncodeNum;	//����·��, zgc, 2007-06-20
#endif
    TVMPParam m_tVMPParam;      //�ϳɲ���
	u8		  m_bySubType;		//vmp�����ͣ����mcuconst.h�еĶ���// xliang [12/29/2008] 
	u8		  m_byBoardVer;		//����MPU A��/B��
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//modify bas 2
//���������������ṹ
struct TAdaptParam
{
    enum EVideoType
    {
        vNONE  = MEDIA_TYPE_NULL,//��Ƶ����������
        vMPEG4 = MEDIA_TYPE_MP4,
        vH261  = MEDIA_TYPE_H261,
        vH263  = MEDIA_TYPE_H263,
        vH264  = MEDIA_TYPE_H264,
    };
    enum EAudioType
    {
        aNONE  = MEDIA_TYPE_NULL,//��Ƶ����������
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

	// [11/1/2011 liuxu] ��ӡ����
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
    u8         m_byAudCodeType;  //������Ƶ�������
    u8         m_byVidCodeType;  //������Ƶ�������
    u8         m_byAudActiveType;//������Ƶ�����̬�غ�����
    u8         m_byVidActiveType;//������Ƶ�����̬�غ�����
    
    u16 	   m_wBitRate;//��������
    u16 	   m_wWidth; //ͼ����
    u16 	   m_wHeight;//ͼ����
    
    u8         m_byNeedPrs;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;
/*----------------------------------------------------------------------
�ṹ����THDAdaptParam
��;  ��HD�������
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
	
	// [11/1/2011 liuxu] ��ӡ����
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
�ṹ����THDBasChnStatus
��;  ��HDBas����ͨ��
----------------------------------------------------------------------*/
struct THDBasChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0,    //����
			READY  = 1,    //׼������
			RUNING = 2,    //��������
			WAIT_START = 3 //�ȴ�����
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
		// [11/4/2011 liuxu] ��ӡ����
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
�ṹ����THDBasVidChnStatus
��;  ��HDBas��Ƶͨ����¼״̬
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
		// [11/1/2011 liuxu] ��ӡ����
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
�ṹ����TMpu2BasStatus
��;  ��Mpu2Bas״̬�࣬�ӽ�TPeriEqpStatus
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
�ṹ����TMpuBasStatus
��;  ��MpuBas״̬�࣬�ӽ�TPeriEqpStatus
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
    u8  byMemberType;     //��Ա����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [5/25/2011 liuxu] ����Ҫ�ٶ���THduMember, ֱ�Ӹ���TTWMember����
typedef TTWMember THduMember;
//HDU״̬�ṹ
struct THduStatus
{
    u8        byOutputMode;  //HDU_OUTPUTMODE_AUDIO : ֻ�����Ƶ
	//HDU_OUTPUTMODE_VIDEO : ֻ�����Ƶ
	//HDU_OUTPUTMODE_BOTH  : ͬʱ�������Ƶ
    u8        byChnnlNum;    //�ŵ���
	
    THduMember atVideoMt[MAXNUM_HDU_CHANNEL]; //ÿ���ŵ���Ӧ�նˣ�MCU��Ϊ0��ʾ�� //???
	
	THduChnStatus atHduChnStatus[MAXNUM_HDU_CHANNEL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;
//�������ֵ���ǽ״̬�ṹ
struct TTvWallStatus
{
    u8        byOutputMode;  //TW_OUTPUTMODE_AUDIO : ֻ�����Ƶ
	//TW_OUTPUTMODE_VIDEO : ֻ�����Ƶ
	//TW_OUTPUTMODE_BOTH  : ͬʱ�������Ƶ
    u8        byChnnlNum;    //�ŵ���
    TTWMember atVideoMt[16]; //ÿ���ŵ���Ӧ�նˣ�MCU��Ϊ0��ʾ��
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//������״̬
struct TMixerGrpStatus
{
	enum EState 
	{ 
		IDLE   = 0,		//�û�����δʹ�� 
		READY  = 1,		//���鴴��,��δ��ʼ����
		MIXING = 2,		//���ڻ���
        WAIT_BEGIN = 200,
        WAIT_START_SPECMIX = 201,   //�ȴ���Ӧ״̬
        WAIT_START_AUTOMIX = 202,
        WAIT_START_VAC = 203,
        WAIT_STOP = 204,
		WAIT_START_AUTOMIXANDVAC = 205,
	};

	u8       m_byGrpId;		  //������ID(0-4)
	u8       m_byGrpState;	  //��״̬
	u8       m_byGrpMixDepth; //�������
    u8       m_byConfId;      //����ID
protected:
    u8       m_abyMixMmb[192>>3];//���뾺��������Ա�б�
    u8       m_abyActiveMmb[10];//��ѡ�еĻ�����Ա�б�,0��ʾ��Ч��Ա
public:
	u8       m_byMixGrpChnNum ;//tianzhiyong 100201 EAPU�¸����������ͨ����Ŀ
	//����״̬��λ
	void Reset()
	{
		m_byGrpId       = 0xff;
		m_byGrpState    = IDLE;
		m_byGrpMixDepth = 0;
		memset( m_abyMixMmb ,0 ,sizeof(m_abyMixMmb) );
		memset( m_abyActiveMmb ,0 ,sizeof(m_abyActiveMmb) );
	}
    //��Ӳ��뾺���Ļ�����Ա
	// ���ó�ԱID�Ϸ�����TRUE,���򷵻�FALSE
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

	//ɾ�����뾺���Ļ�����Ա
	// ���ó�ԱID�Ϸ�����TRUE,���򷵻�FALSE
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

	//���ĳ��Ա�Ƿ�����ڲ��뾺���ı��У�
	//������ڷ���TRUE ,���򷵻�FALSE
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

	//������ڲ��뾺����������ĳ�Ա����
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

	//������ڲ��뾺���Ļ�����ԱID
	//��� - abyMmb[] ���ڴ洢�μӻ����ĳ�ԱID
	//���� - bySize abyMmb[] �Ĵ�С
	//���� �μӻ����ĳ�Ա��
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
	
	//�ж�ָ����Ա�Ƿ�ѡ�л���
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
	
	//��ñ�ѡ�л�����Ա����
	u8   GetActiveMmbNum()
	{
		u8   byCount=0;
		for( u8   byIdx =0 ;byIdx< 10 ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )byCount++;
		return byCount;
	}
	
	//��ñ�ѡ�л�����Ա
	//���: abyMmb[] - �洢��ѡ�л�����ԱID
	//����: bySize   - abyMmb ��С
	//����: abyMmb����Ч��Ա����
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

//������״̬
struct TMixerStatus
{
	u8 m_byGrpNum; //����������
	TMixerGrpStatus	m_atGrpStatus[5];
	u8  m_bIsMultiFormat; //tianzhiyong 100201  ��Ǹû������Ƿ�֧�ֶ��ʽ
	u8  m_byMixOffChnNum ;//tianzhiyong 100201 EAPU�¸����������ƫ��ͨ����Ŀ
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//¼����ŵ�״̬
struct TRecChnnlStatus
{
	/*ͨ����״̬*/
	enum ERecChnnlState
	{
		STATE_IDLE       = 0,	  /*������һ��δ��ͨ��*/
			
			STATE_RECREADY   = 11,	  /*׼��¼��״̬  */
			STATE_RECORDING  = 12,	  /*����¼��  */
			STATE_RECPAUSE   = 13,	  /*��ͣ¼��״̬*/
			
			STATE_PLAYREADY  = 21,	  /*׼������״̬ */
			STATE_PLAYREADYPLAY = 22,   /*���ò���׼��״̬*/
			STATE_PLAYING    = 23,	  /*���ڻ򲥷�*/
			STATE_PLAYPAUSE  = 24,	  /*��ͣ����*/
			STATE_FF         = 25,	  /*���(������ͨ����Ч)*/
			STATE_FB         = 26	  /*����(������ͨ����Ч)*/
	};
	
	/*ͨ�����Ͷ���*/
	enum ERecChnnlType
	{
		TYPE_UNUSE      =  0,	/*δʼ�õ�ͨ��*/
			TYPE_RECORD     =  1,	/*¼��ͨ��  */   
			TYPE_PLAY       =  2	/*����ͨ��  */
	};
	
	//¼��ʽ
	enum ERecMode
	{
		MODE_SKIPFRAME = 0,//��֡¼��
			MODE_REALTIME  = 1  //ʵʱ¼��
	};
public:
	u8  		m_byType;		//ͨ�����ͣ�ERecChnnlType
	u8  		m_byState;		//ͨ��״̬��ERecChnnlState
	u8          m_byRecMode;    //¼��ʽ:
	u32   		m_dwCurProg;	//��ǰ����
	u32   		m_dwTotalTime;	//�ܳ��ȣ����ڷ���ʱ��Ч
	TMtNoConstruct			m_tSrc;
protected:
	char	m_achRecordName[64];//��¼��
	
public:
	//��ȡ��¼��
	LPCSTR GetRecordName( void ) const	{ return m_achRecordName; }
	//���ü�¼��
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
//¼���״̬, size = 2412
struct TRecStatus
{
protected:
	u8  	m_byRecChnnlNum;		//¼���ŵ�������
	u8  	m_byPlayChnnlNum;		//�����ŵ�������
	u8      m_bSupportPublic;       // �Ƿ�֧�ַ���(TRUE: ֧��, FALSE:��֧��)
	u8      m_byRemain;             // ����
 	u32   	m_dwFreeSpace;        //¼���ʣ����̿ռ�(��λΪMB)
	u32   	m_dwTotalSpace;		//¼����ܴ��̿ռ�(��λΪMB)
	TRecChnnlStatus m_tChnnlStatus[32];	//��¼���ŵ�������ŵ�

public:
	//��ȡ¼��ͨ������
	u8   GetRecChnnlNum( void ) const	{ return( m_byRecChnnlNum ); }
	//��ȡ����ͨ������
	u8   GetPlayChnnlNum( void ) const	{ return( m_byPlayChnnlNum ); }
	//����ͨ������¼��ͷ���ͨ���������벻����MAXNUM_RECORDER_CHNNL
	//ʧ�ܷ���FALSE
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
    ����        ������¼���ʣ����̿ռ�
    �������˵����u32    dwFreeSpace  - ʣ��ռ��С(��λ Mb)
    ����ֵ˵��  ����
	====================================================================*/
	void SetFreeSpaceSize( u32    dwFreeSpace )
	{
		m_dwFreeSpace  = htonl(dwFreeSpace);
	}
	
	/*====================================================================
    ����        ����ȡ¼���ʣ����̿ռ�
    �������˵������
    ����ֵ˵��  ��ʣ��ռ��С(��λ MB)
	====================================================================*/
	u32    GetFreeSpaceSize( void ) const	{ return ntohl( m_dwFreeSpace ); }

		/*====================================================================
    ����        ������¼����ܴ��̿ռ�
    �������˵����u32    dwTotalSpace  - �ܿռ��С(��λ MB)
    ����ֵ˵��  ����
	====================================================================*/
	void SetTotalSpaceSize( u32    dwTotalSpace )
	{
		m_dwTotalSpace  = htonl( dwTotalSpace );
	}
	// �Ƿ�֧�ַ���
	BOOL IsSupportPublic() const { return m_bSupportPublic;}
    // �����Ƿ�֧�ַ���
	void SetPublicAttribute(BOOL bSupportPublic ) { m_bSupportPublic = bSupportPublic;}

	/*====================================================================
    ����        ����ȡ¼����ܴ��̿ռ�
    �������˵������
    ����ֵ˵��  ���ܿռ��С(��λ MB)
	====================================================================*/
	u32    GetTotalSpaceSize( void ) const	{ return ntohl( m_dwTotalSpace ); }

	//����¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
	BOOL SetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, const TRecChnnlStatus * ptStatus );
	//����¼����ŵ�״̬��Ϣ������������¼�����ŵ����ٵ��ô˺���
	BOOL GetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, TRecChnnlStatus * ptStatus ) const;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//¼��ʽ����
#define		 REC_MODE_NORMAL				0   /* ʵʱ¼�� */
#define	     REC_MODE_SKIPFRAME				1	/* ��֡¼�� */

//�йط�����ʽ����
#define      PUBLISH_MODE_NONE				0	//������
#define      PUBLISH_MODE_IMMED				1	//��������
#define      PUBLISH_MODE_FIN				2	//¼�����֮�󷢲�

//��������
#define      PUBLISH_LEVEL_NORMAL			0	//��������
#define      PUBLISH_LEVEL_SECRET			1	//���ܷ���

//¼���ļ�����
#define      RECFILE_NORMAL                 0   //����ʽ¼���ļ�
#define      RECFILE_DSTREAM                1   //˫��ʽ¼���ļ�

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

// zgc, 2008-08-02, MCU�ķ����ļ�ý����Ϣ
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
    //���ĸ���
    u8 m_byNum;
    //��������
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
    u8   m_byRecMode;         //¼��ģʽ
    u8   m_byPublishMode;     //����ģʽ
    u8   m_byPublishLevel;    //�������
    u8   m_byIsRecLowStream;  //�Ƿ�¼��������
    u8   m_byIsRecMainVideo;  //�Ƿ�¼����ʽ��Ƶ����
    u8   m_byIsRecMainAudio;  //�Ƿ�¼����ʽ��Ƶ����
    u8   m_byIsRecDStream;    //�Ƿ�¼˫��
	u16  m_wRecBitrate;       //¼������
    u16  m_wRecBitrateSec;    //¼��˫������

public:
	//lukunpeng 2010/07/14 �˽ṹ��ŵ�Union�У������й��캯��
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

#define     MAXLEN_RECORD_NAME              64  //�ϱ�����״̬ʱ¼���ļ����ĳ���
#define		MAXLEN_CONFNAME                 64   //��������󳤶�
#define		RECLIST_PACKSIZE					(u8)16
struct TRecFileListNotify
{
	u16 wListSize;//¼������ļ�����
	u16 wStartIdx;//��֪ͨ����ʼ�ļ����
	u16 wEndIdx;  //��֪ͨ�н����ļ����
    
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

	//��ȡ¼�����¼����
	u16 GetListSize()
	{
		return ntohs(wListSize);
	}
	
	//��ȡ��֪ͨ����ʼ�ļ����
	u16 GetStartIdx()
	{
		return ntohs(wStartIdx);
	}

	//��ȡ��֪ͨ����ʼ�ļ����
	u16 GetEndIdx()
	{
		return ntohs(wEndIdx);
	}

	//���ָ����ŵ��ļ���,�粻���ڷ���NULL
	char* GetFileName(u16 wIdx )
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return NULL;
		return achFileName[wIdx - GetStartIdx()];
	}

	//�ж�ָ����ŵ��ļ��Ƿ񷢲�
	BOOL IsPublic(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;
		return abyStatus[wIdx - GetStartIdx()]&0x1 ? TRUE:FALSE;
	}

	//����ָ����ŵ��ļ�����
	BOOL Public(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;

		abyStatus[wIdx - GetStartIdx()] |=0x1;
		return TRUE;
	}

	/////////////////////////////////////////////
	//����¼�����¼����
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
	
	//���ñ�֪ͨ����ʼ�ļ����
	void SetStartIdx( u16 wIdx)
	{
		wStartIdx = htons(wIdx);
	}

	//���ñ�֪ͨ����ʼ�ļ����
	void SetEndIdx( u16 wIdx)
	{
		wEndIdx = htons(wIdx);
	}

	// ����ļ�
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

        // ����Զ�����
        SetEndIdx( GetEndIdx() + 1 );
		return TRUE;
	}

	//�жϻ����Ƿ�����
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

//������������ģ��
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

//������ͨ��״̬�ṹ
struct TBasChnStatus : TAdaptParam
{
    enum EBasStatus
    {
        IDLE   = 0,		//����
			READY  = 1,		//׼������
			RUNING = 2,		//��������
			WAIT_START = 3  //�ȴ�����
    };
	
protected:
    u8 m_byStatus;
	u8 m_byReserved;    //�Ƿ�Ϊ����ͨ��
    u8 m_byChanType;    //��Ƶͨ��: 1(BAS_CHAN_AUDIO)  ��Ƶͨ��: 2(BAS_CHAN_VIDEO)
	
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

//������ͨ��״̬�ṹ
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

//�ش��豸״̬ (len:3)
struct TPrsPerChStatus
{
public:
	u8  byUsed;         //0--δ������1--����
	u8	byCount;	    //���ٸ�������
	u8  byChlReserved;  //�Ƿ�Ϊ����ͨ��
	u8  byConfIndex;		//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
public:
    void   SetUsed( void ){ byUsed = 1; }
    void   SetIdle( void ){ byUsed = 0; }
    BOOL   IsUsed( void ){ return byUsed; }
    
    u8     GetFeedNum( void ){ return byCount; }
    void   FeedNumAdd( void ){ byCount++; }
    void   FeedNumDec( void ){ byCount--; }
	
	void   SetReserved( BOOL bReserved ){ byChlReserved = bReserved; }
	BOOL   IsReserved( void ){ return byChlReserved; }
	
	//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
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
//�ش��ṹ
struct TPrsStatus
{
public:
	TPrsPerChStatus   m_tPerChStatus[16];		//���ؽ���RTP/RTCP���ĵ�ַ
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
	
	//��¼ͨ������Ļ���Idx, zgc, 2007/04/24
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
�ṹ����THDBasChnStatus
��;  ��HDBas����ͨ��
----------------------------------------------------------------------*/
struct TBasBaseChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0,    //����
			READY  = 1,    //׼������
			RUNING = 2,    //��������
			WAIT_START = 3 //�ȴ�����
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
// 		// [11/4/2011 liuxu] ��ӡ����
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
	//������Ƶ��������
	void SetAudCodeType( u8 byAudCodeType )
	{
		m_byAudCodeType = byAudCodeType;
	}
	
	u8 GetAudCodeType()
	{
		return m_byAudCodeType;
	}
	
	//������Ƶ�����غ�
	void SetAudActiveType( u8 byAudActiveType )
	{
		m_byAudActiveTpye = byAudActiveType;
	}
	
	u8 GetAudActiveType()
	{
		return m_byAudActiveTpye;
	}
	
	//������Ƶ����������
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

//BAS��Ƶͨ��״̬
struct TAudBasChnStatus:public TBasBaseChnStatus
{
public:
    TAudAdaptParam  m_atOutPutAudParam[MAXNUM_BASOUTCHN];   //����ͨ�������������
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

//apu2-bas����״̬
struct TApu2BasStatus
{
public:
    TAudBasChnStatus m_atAudChnStatus[MAXNUM_APU2_BASCHN];  //APU2 BAS����ͨ������
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





//apu2-bas����״̬
struct T8kiAudBasStatus
{
public:
    TAudBasChnStatus m_atAudChnStatus[MAXNUM_8KI_AUD_BASCHN];  //APU2 BAS����ͨ������
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
		u8 m_abyArray[910];//zjj20130922 Ϊ�˺�hdbas�ṹ��Сһ��(Ҫ�������m_byType),������������ṹ
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

//��������״̬�ṹ, size = 2435(TRecStatus = 2412)
struct TPeriEqpStatus : public TEqp
{
public:
	u8  	m_byOnline;		//�Ƿ�����
	union UStatus
	{
		TTvWallStatus	tTvWall;//�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
		TMixerStatus	tMixer; //�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
		TVmpStatus      tVmp;	
		TRecStatus		tRecorder;//�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
		TBasStatus		tBas;//�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
		TPrsStatus		tPrs;//�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
        THdBasStatus    tHdBas;
		THduStatus      tHdu;//�˽ṹ�壬���Ҫʹ�ã����Լ���mcu��ȡ���˴����岻׼ȷ   ums  diaolei
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
	
	//��ȡ�������
	const s8 * GetAlias() const 
	{ 
		return m_achAlias;
	}
	
	//�����������
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
// ����ϳɳ�Ա�ṹ(Mcu -- Vmp)
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

//����ϳ�������Ϣ
struct TVmpStyleCfgInfo
{
#define MAX_VMPSTYLE_ALIASLEN 32
protected:
    u8  m_bySchemeId;                   //����id��1��5
	u8	m_byRimEnabled;					//�Ƿ�ʹ�ñ߿�: 0-��ʹ��(Ĭ��) 1-ʹ��;
										//���ֶ�Ŀǰֻ�Է���0��Ч, ���������ݲ��漰���ֶε����ú��ж�
	u8	m_byReserved1;					//�����ֶ�1
	u8	m_byReserved2;					//�����ֶ�2
    u32 m_dwBackgroundColor;            //ͼ�񱳾�ɫ
    u32 m_dwFrameColor;                 //ͼ��߿�ɫ
    u32 m_dwSpeakerFrameColor;          //�����˱߿�ɫ
    u32 m_dwChairFrameColor;            //��ϯ�߿�ɫ 
	u8  m_byFontType;                   // �ϳ���������
	u8  m_byFontSize;					// �ϳ������ֺ�
	u8  m_byAlignment;                  // ���뷽ʽ
	u32  m_dwTextColor;                  // �ϳ�����������ɫ
	u32  m_dwTopicBkColor;               // �ϳ����ⱳ��ɫ
	u32  m_dwDiaphaneity;                // �ϳ�����͸����
    s8  m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN];  // ����ϳɷ�������

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

// VMP��չ����
struct TVMPExCfgInfo
{
	u8 m_byIdleChlShowMode;  // ����ͨ����ʾģʽ VMP_SHOW_GRAY_MODE
	
	u8  m_byIsDisplayMmbAlias; // �Ƿ���ʾ������1 Ϊ��ʾ��0Ϊ����ʾ��
	u16 m_wReserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
struct TVmpCommonAttrb
{
	u8	m_byVmpStyle;	//�ϳɷ��
	u8	m_byMemberNum;	//��Ա����
	u8	m_byNeedPrs;	//�Ƿ���ҪPRS
	TVMPMemberEx		m_atMtMember[MAXNUM_VMP_MEMBER];		//���ϳ�Ա
	TMediaEncrypt		m_tVideoEncrypt[MAXNUM_VMP_MEMBER];     //��Ƶ���ܲ���
	TDoublePayload		m_tDoublePayload[MAXNUM_VMP_MEMBER];	//˫�غ�
	TVmpStyleCfgInfo	m_tVmpStyleCfgInfo;		//������Ϣ
	TVMPExCfgInfo		m_tVmpExCfgInfo;		//��չ������Ϣ
	
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

//VMP���������(MCU��VMPͨѶ��)
class CKDVVMPOutMember
{
private:
	u8    	        m_byEncType;		//ͼ���������
	u8    	        m_byProfileType;	//BP/HP
	u8				m_byFrameRate;		//֡��
	u16             m_wBitRate;			//���������(Kbps)
	u16   	        m_wVideoWidth;		//ͼ����(default:720)
	u16   		    m_wVideoHeight;		//ͼ��߶�(default:576)
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

//Hdu��Ϣ
struct TEqpHduInfo: public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpMapInfo
{
protected:
	
	THduChnlModePortAgt atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	u8  m_byStartMode; //����ģʽ(0: hdu_2, 1: hdu_1, 2: hdu_L)	
public:
	TEqpHduInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
		SetStartMode(STARTMODE_HDU_M); //Ĭ��Ϊhdu_2
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

//4.6���¼��������ṹ
//HDU������뿨
struct TEqpHduEntry : public TEqpHduInfo,
					  public TEqpEntryParam
{
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ����bas����Ϣ
//�豸id,����,mcu��ʼ�˿�,�豸��ʼ�˿�,����������,���а�����,����bas��ip
struct TEqpBasHDCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//Ip��ַ
	
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
//apu2 �ṹ��
/************************************************************************/
/*						CEqpCfg���������ඨ��						    */
/************************************************************************/
#define		MAXLEN_ALIAS			        128  //MCU���ն˼������127����ĸ��63������

//����������ýṹ(��map��Ϣ)
struct TEqpBasicCfg
{
	char  achAlias[ MAXLEN_ALIAS+1 ];
	u8    byEqpId;          //����ID
	u8    byEqpType;        //��������
	
	u32   dwLocalIP;        //����IP��ַ
	u32   dwConnectIP;      //����MCUIP��ַ
	u16   wConnectPort;     //����MCU ͨ�Ŷ˿�
	u16   wMcuId;           //MCU id ��
	u16   wRcvStartPort;    //������ʼ�˿ں�
	
	
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
	u32  dwCoreSpd;     // Map�ں��ٶ�
	u32  dwMemSpd;      // �ڴ��ٶ�
	u32  dwMemSize;     // �ڴ��С
	u8   byMapId;	    // Map���
	u32   dwPort;	    // Map�˿ں�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//����������ýṹ
struct TEqpCfg:public TEqpBasicCfg
{
	
	u16   wMAPCount;        //ʹ�õ�MAP����
	TMAPParam m_atMap[MAXNUM_MAP];	//map��Ϣ
	
    TEqpCfg(void) { memset(this, 0, sizeof(TEqpCfg)); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Qos ��Ϣ
struct TMcuQosCfgInfo
{	
protected:
    u8  m_byQosType;					// Qos ����
    u8  m_byAudLevel;					// ��Ƶ�ȼ�
    u8  m_byVidLevel;					// ��Ƶ�ȼ�
    u8  m_byDataLevel;					// ���ݵȼ�
    u8  m_bySignalLevel;				// �źŵȼ�
    u8  m_byIpServiceType;				// IP��������
	
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
	u32 m_dwMcuNodeA;				//����McuA����
	u32 m_dwMcuIIdA;				//��McuAͨ��IID
	u32 m_dwMcuNodeB;				//����McuB����
	u32 m_dwMcuIIdB;				//��McuBͨ��IID
	u32 m_dwServerNode;             //�������Խ���
    u32 m_dwServerIId;				//��������IID
	u32 m_dwMpcSSrc;				//Ψһ�ỰԴ
	u32 m_dwMcuRcvIp;               //McuΪ��������ת����IP
	u16 m_wMcuRcvStartPort;         //McuΪ��������ת����˿�
	u16 m_wEqpVer;					//����汾
	u8  m_byRegAckNum;				//ע��ɴ���
	TPrsTimeSpan m_tPrsTimeSpan;    //�ش�����
	TMcuQosCfgInfo m_tQosInfo;      
};

#define  MIXER_APU2_CHN_MINNUM  (u8)2				//APU2��С����ͨ����
#define  BRD_APU2_SNDPORT       (u16)10000          //APU2������ʼ���Ͷ˿�

	/************************************************************************/
	/*							CApu2Cfg�����ඨ��							*/
	/*																		*/
	/*        ˵����һ��Apu2���2����������ÿ�����������ö�ӦCApu2Cfg		*/
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
	u8     m_byMemberNum;		//���ó�Ա����
	u8     m_bySndOff;			//���Ͷ���ƫ��
	u8     m_byIsMultiFormat;	//�Ƿ���ʽ
	u8     m_byIsSimuApu;       //�Ƿ�ģ��Apu
	u16    m_wSimApuVer;		//ģ��Apu�汾
	u8	   m_byQualityLvl;		//���ʵȼ�
	
};

	/************************************************************************/
	/*							CApu2Cfg�����ඨ��							*/
	/*																		*/
	/*					˵����һ��Apu2�豸��ӦTApu2EqpCfg					*/
	/************************************************************************/
struct TApu2EqpCfg
{
public:
	BOOL32        m_bIsProductTest;					   //�Ƿ���������
	u8		      m_byMixerNum;						   //Apu2�豸���˼���������
	CApu2MixerCfg m_acMixerCfg[MIXER_APU2_CHN_MINNUM]; //ÿ������������
public:
	TApu2EqpCfg()
	{
		m_bIsProductTest = FALSE;
		m_byMixerNum     = 0;
	}
};
#define     MIXER_INVALID_GRPID				255 //��Ч�������
#define     MIXER_INVALID_CHNNLID			255 //��Ч�����ŵ���
struct TMixerStart
{
protected:
    u8 m_byMixGroupId; //������Id
    u8 m_byMixDepth;   //�������
    u8 m_byAudioMode;  //������ʽ
    u8 m_byAudioMode2; //�ڶ�������ʽ(����Ϊ����Ϊ˫������ʽ)
    u8 m_byIsAllMix;   //ȫ�����
    TMediaEncrypt m_tAudioEncrypt;	//���ܲ���
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

//���轻���������Ϣ
struct TEqpSwitchBrdInfo
{
protected:
    u8  m_bySwitchBrdId;     //������ID
    u16 m_wMcuRecvPort;      //������(MCU)�������ʼ�˿ں� ������
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

// 2.Mixer ��Ϣ
struct TEqpMixerInfo : public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpSwitchBrdInfo,
public TEqpMapInfo
{
protected:
    u8  m_byMaxChannelInGrp;			// ���������ͨ����
	u8	m_byIsSendRedundancy;			// �Ƿ����෢��, zgc, 2007-0725
	
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

// [2]. ������
struct TEqpMixerEntry : public TEqpMixerInfo,
						public TEqpEntryParam 
{
protected:
    u8  m_byMaxMixGroupNum;	/*�����������*/
	u8	m_byIsSendRedundancy;	// �Ƿ����෢��, zgc, 2007-0725
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

//FTP TELNET ����
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
//MpuBas��Ϣ�ṹ
struct TEqpMpuBasInfo: public TEqpBasicInfo,
public TEqpRunBrdInfo,
public TEqpSwitchBrdInfo,
public TEqpMapInfo
{
	u8 m_byStartMode; //����ģʽ(0: bap_4, 1:bap_2)
	
	TEqpMpuBasInfo()
	{
		SetStartMode (TYPE_MPUBAS); //Ĭ��ΪTYPE_MPUBAS
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

//������Ա�ṹ
struct TMixMember
{
    TMt m_tMember;
    u8  m_byVolume;                 //��Ա����
    u8  m_byAudioType;              //ý������
    TTransportAddr m_tAddr;         //��Ա�Ĵ����ַ
    TTransportAddr m_tRtcpBackAddr; //RTCP������ַ
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
#define PACKED __attribute__((__packed__))	// ȡ�����������Ż�����
#endif
#endif


///��Ƶ��ʽ����[2/8/2012 chendaiwei]
struct TAudioTypeDesc
{
private:
	u8 m_byAudioMediaType; //��Ƶ����
	u8 m_byAudioTrackNum;  //��Ƶ������Ŀ��������Ϊ1,˫����Ϊ2��
	
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

//��Ƶ������Ϣ
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

#define     MAXNUM_MIXER_DEPTH				10  //���������������

// zw [06/27/2008] AAC LC����
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

/*****************************�����붨��**********************************/
const u32 ERR_MIXER_BGN = 24501;
#define ERR_MIXER_NONE               ( ERR_MIXER_BGN  )     //�޴��� 
#define ERR_MIXER_CALLDEVICE         ( ERR_MIXER_BGN + 1 )  //���õײ㺯��ʧ��
#define ERR_MIXER_MIXING             ( ERR_MIXER_BGN + 2 )  //���ڻ���״̬
#define ERR_MIXER_NOTMIXING          ( ERR_MIXER_BGN + 3 )  //δ����״̬
#define ERR_MIXER_ERRCONFID          ( ERR_MIXER_BGN + 4 )  //��Ч�Ļ���ID
#define ERR_MIXER_CHNINVALID         ( ERR_MIXER_BGN + 5 )  //���ͨ��ʧ��
#define ERR_MIXER_STATUIDLE          ( ERR_MIXER_BGN + 6 )  //������״̬����

//////////////////////////////////////////////////////////////////////////
//�������������� ��Ϣ����
#define  MAXVALUE_APU2_VOLUME     (u8)31              //Apu2�������������ֵ

/*----------  ����Ϊ��������Ϣ�Ŷ���(26301-26400)  -----------*/
const u32 EV_MCUMIXER_BGN = 26301;
//��������MCU����ע������MIXER->MCU����Ϣ��ΪTPeriEqpRegReq�ṹ
OSPEVENT( UMS_MIXER_MCU_REG_REQ,				EV_MCUMIXER_BGN );
//MCU����Ӧ��MCU->MIXER����Ϣ��ΪTPeriEqpRegAck + TPrsTimeSpan + u16(MTU size) + u8(IsSendRedundancy)
OSPEVENT( UMS_MCU_MIXER_REG_ACK,				EV_MCUMIXER_BGN + 1 );
//MCU�ܾ�Ӧ��MCU->MIXER������Ϣ��
OSPEVENT( UMS_MCU_MIXER_REG_NACK,				EV_MCUMIXER_BGN + 2 );
//������״̬֪ͨ��MIXER->MCU����Ϣ��ΪTPeriEqpStatus
OSPEVENT( UMS_MIXER_MCU_MIXERSTATUS_NOTIF,		EV_MCUMIXER_BGN + 3 );

//MCU��ʼ��������MCU->MIXER ��Ϣ��: TMixerStart+TDoublePayload+TCapSupportEx
OSPEVENT( UMS_MCU_MIXER_STARTMIX_REQ,			EV_MCUMIXER_BGN + 5 );
//ͬ�⿪ʼ����Ӧ��MIXER->MCU����Ϣ��: 1 byte(������Id)+ 1 byte(�������)
OSPEVENT( UMS_MIXER_MCU_STARTMIX_ACK,			EV_MCUMIXER_BGN + 6 );
//�ܾ���ʼ����Ӧ��MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_STARTMIX_NACK,			EV_MCUMIXER_BGN + 7 );

//������״̬֪ͨ��MIXER->MCU����Ϣ��ΪTMixerGrpStatus
OSPEVENT( UMS_MIXER_MCU_GRPSTATUS_NOTIF,		EV_MCUMIXER_BGN + 10 );

//MCUֹͣ��������MCU->MIXER����Ϣ��: 1 byte(������Id)
OSPEVENT( UMS_MCU_MIXER_STOPMIX_REQ,			EV_MCUMIXER_BGN + 15 );
//ͬ��ֹͣ����Ӧ��MIXER->MCU����Ϣ��: 1 byte(������Id)
OSPEVENT( UMS_MIXER_MCU_STOPMIX_ACK,			EV_MCUMIXER_BGN + 16 );
//�ܾ�ֹͣ����Ӧ��MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_STOPMIX_NACK,			EV_MCUMIXER_BGN + 17 );

//�����Ա����MCU->MIXER����Ϣ��:1 byte(������Id)+ TMixMember + 1 byte(��Ա����ԭʼ��ʽ)
//  m_tMember,m_tAddr,��Ч
OSPEVENT( UMS_MCU_MIXER_ADDMEMBER_REQ,			EV_MCUMIXER_BGN + 20 );
//�����ԱӦ����Ϣ��MIXER->MCU����Ϣ��: 1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_ADDMEMBER_ACK,			EV_MCUMIXER_BGN + 21 );
//�����ԱӦ����Ϣ��MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_ADDMEMBER_NACK,			EV_MCUMIXER_BGN + 22 );


//ɾ����Ա����MCU->MIXER����Ϣ��:1 byte(������Id)+ TMixMember	
//  m_tMember, m_byGrpId ��Ч
OSPEVENT( UMS_MCU_MIXER_REMOVEMEMBER_REQ,		EV_MCUMIXER_BGN + 25 );
//ɾ����ԱӦ����Ϣ��MIXER->MCU����Ϣ��: 1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_REMOVEMEMBER_ACK,		EV_MCUMIXER_BGN + 26 );
//ɾ����ԱӦ����Ϣ��MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_REMOVEMEMBER_NACK,		EV_MCUMIXER_BGN + 27 );

//����������Ա�ı�֪ͨ,MIXER->MCU ,��Ϣ�� u8    abyActiveMmb[MAXNUM_MIXER_GROUP]
//0��ʾ��Ч��Ա
OSPEVENT( UMS_MIXER_MCU_ACTIVEMMBCHANGE_NOTIF,	EV_MCUMIXER_BGN + 30 );

//���û�����Ա��MCU->MIXER����Ϣ��:1 byte(������Id)+ 192 byte(ÿ�ֽڶ�Ӧһ�ն�)	
OSPEVENT( UMS_MCU_MIXER_SETMEMBER_CMD,			EV_MCUMIXER_BGN + 32 );

//ǿ�Ƴ�Ա���� ,MCU->MIXER����Ϣ��:1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MCU_MIXER_FORCEACTIVE_REQ,		EV_MCUMIXER_BGN + 35 );
//ǿ�Ƴ�Ա����Ӧ��MIXER->MCU����Ϣ��:1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_FORCEACTIVE_ACK,		EV_MCUMIXER_BGN + 36 );
//ǿ�Ƴ�Ա�����ܾ���MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_FORCEACTIVE_NACK,		EV_MCUMIXER_BGN + 37 );

//ȡ����Աǿ�ƻ��� ,MCU->MIXER����Ϣ��:1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MCU_MIXER_CANCELFORCEACTIVE_REQ,	EV_MCUMIXER_BGN + 40 );
//ȡ����Աǿ�ƻ���Ӧ��MIXER->MCU����Ϣ��:1 byte(������Id)+ TMixMember
OSPEVENT( UMS_MIXER_MCU_CANCELFORCEACTIVE_ACK,	EV_MCUMIXER_BGN + 41 );
//ȡ����Աǿ�ƻ����ܾ���MIXER->MCU������Ϣ��
OSPEVENT( UMS_MIXER_MCU_CANCELFORCEACTIVE_NACK,	EV_MCUMIXER_BGN + 42 );

//����ĳͨ��������Ϣ��MCU->MIXER����Ϣ��1 byte(������Id)+ TMixMember
//  m_tMember, m_byGrpId ,m_byVolume ��Ч
OSPEVENT( UMS_MCU_MIXER_SETCHNNLVOL_CMD,		EV_MCUMIXER_BGN + 45 );
//ĳͨ������֪ͨ��Ϣ��MIXER->MCU����Ϣ��ΪTMixMember
OSPEVENT( UMS_MIXER_MCU_CHNNLVOL_NOTIF,			EV_MCUMIXER_BGN + 50 );

//���û������������Ϣ��MCU->MIX����Ϣ��: 1 byte(������Id) + 1 byte(�������)
OSPEVENT( UMS_MCU_MIXER_SETMIXDEPTH_REQ,		EV_MCUMIXER_BGN + 55 );
//���û������Ӧ����Ϣ��MIXER->MCU����Ϣ��: 1 byte(������Id) + 1 byte(�������)
OSPEVENT( UMS_MIXER_MCU_SETMIXDEPTH_ACK,		EV_MCUMIXER_BGN + 56 );
//���û�����Ⱦܾ���Ϣ��MIXER->MCU��
OSPEVENT( UMS_MIXER_MCU_SETMIXDEPTH_NACK,		EV_MCUMIXER_BGN + 57 );

//MCU�����������Ƿ�Ҫ��������֪ͨ,��Ϣ��: 1 byte(������Id) + 1 byte(0:����,1��)
OSPEVENT( UMS_MCU_MIXER_SEND_NOTIFY,			EV_MCUMIXER_BGN + 60 );

//��������������ʱ����ʱ����Ϣ, MCU->MIXER, ��Ϣ��: 1 byte(������Id) + 4 byte(u32 ����ʱ�� ������)
OSPEVENT( UMS_MCU_MIXER_VACKEEPTIME_CMD,		EV_MCUMIXER_BGN + 65 );

//������ʱ����,��Ϣ�壺u8��������id�� �� u16�����룩
OSPEVENT( UMS_MCU_MIXER_CHANGEMIXDELAY_CMD,		EV_MCUMIXER_BGN + 66 );

// stop mixer map, zgc, 2007/04/24
OSPEVENT( UMS_MCU_MIXER_STOPEQP_CMD,			EV_MCUMIXER_BGN + 67 );
// start mixer map, zgc, 2007/04/26
OSPEVENT( UMS_MCU_MIXER_STARTEQP_CMD,			EV_MCUMIXER_BGN + 68 );

//tianzhiyong 2010/05/19  ���ӿ����͹ر�EAPU����������������������
//����EAPU���������������������MCU->MIXER��
//��Ϣ��: ������������ʱΪTMixerStart+TDoublePayload+TCapSupportEx ����Ϊ��
OSPEVENT( UMS_MCU_MIXER_STARTVAC_CMD,		EV_MCUMIXER_BGN + 69 );
//�ر�EAPU���������������������MCU->MIXER����Ϣ��: ��
OSPEVENT( UMS_MCU_MIXER_STOPVAC_CMD,		EV_MCUMIXER_BGN + 70 );
//����ͬ��ͨ�� u8 chnl
OSPEVENT( UMS_MCU_MIXER_SYNCCHNL_CMD,		EV_MCUMIXER_BGN + 71 );
//ɾ��ͬ��ͨ�� u8 chnl
OSPEVENT( UMS_MCU_MIXER_SYNCCHNL_DEL,		EV_MCUMIXER_BGN + 72 );
/*----------  MCU�ͻ�������Ϣ�Ŷ������(26301-26400)  -----------*/

//���ӣ�����������Կ   ��Ϣ��: TQTMediaKeyInfo
OSPEVENT( UMS_MCU_MIXER_SETMEDIAKEY_CMD,		EV_MCUMIXER_BGN + 73 );

//////////////////////////////////////////////////////////////////////////
//�����
const u16     ERR_MCU_BGN = 20001;

#define DefineError(err, num )   \
const u16 err = num;
//�������ѵǼ�
DefineError( ERR_MCU_PERIEQP_REGISTERED		   , ERR_MCU_BGN + 15)

//�����ڵ�ͨ�Ű汾��MCU��һ�£������룺20017��ע������ϰ汾�����ܸ��ģ�
DefineError( ERR_MCU_VER_UNMATCH               , ERR_MCU_BGN + 16)

//�޿��������������
DefineError(ERR_MCU_NOIDLEEQPSSN               , ERR_MCU_BGN + 21)

//ָ�����費����
DefineError( ERR_MCU_EQPOFFLINE				   , ERR_MCU_BGN + 50)

// ָ�������費�Ϸ�
DefineError( ERR_MCU_WRONGEQP				   , ERR_MCU_BGN + 51)

// �������ӵ�����Ƿ�
DefineError( ERR_MCU_REGEQP_INVALID			   , ERR_MCU_BGN + 52)


//////////////////////////////////////////////////////////////////////////
//��Ϣ�Լ�APP����

//#define AID_TP_MCUBRD_SSN_APP		AID_MCU_BGN + 27	//78 mcu���������ҵ����App  ��Ҫ��MCUͬ��
//#define AID_TP_MCUBRD_REG_APP		AID_MCU_BGN + 6     //57 mcu���������ע�ᴦ��App  ��Ҫ��MCUͬ��
#define AID_TP_MPU2_APP				AID_MCU_BGN + 37    //�������ע�ᴦ��App  ��Ҫ��MCUͬ��

const u16    EV_UMS_MCUBRD_BGN = 20001;
//ע�ᵥ��
//�����ע����Ϣ����Ϣ��ΪTBrdPosition+u32(����IP)+u8(���ں�)+u8(OsType)
OSPEVENT( UMS_BOARD_MPC_REG,			    EV_UMS_MCUBRD_BGN + 401 );
OSPEVENT( UMS_MPC_BOARD_REG_ACK,		    EV_UMS_MCUBRD_BGN + 402 );
OSPEVENT( UMS_MPC_BOARD_REG_NACK,		    EV_UMS_MCUBRD_BGN + 403 );

//��ȡ����������Ϣ
OSPEVENT( UMS_BOARD_MPC_GET_CONFIG,		    EV_UMS_MCUBRD_BGN + 404 );
//��Ϣ��Ϊ u8(�������)+TTPEqpHduEntry
OSPEVENT( UMS_MPC_BOARD_GET_CONFIG_ACK,	    EV_UMS_MCUBRD_BGN + 405 );
OSPEVENT( UMS_MPC_BOARD_GET_CONFIG_NACK,    EV_UMS_MCUBRD_BGN + 406 );

//������������
OSPEVENT( UMS_MPC_BOARD_RESET_CMD,			    EV_UMS_MCUBRD_BGN + 413 );
//��ȡ����汾��Ϣ����Ϣ  ��Ϣ���ݣ���
OSPEVENT( UMS_MPC_BOARD_GET_VERSION_REQ,		EV_UMS_MCUBRD_BGN + 420 );
//����汾��ϢӦ��        ��Ϣ���ݣ�TBrdPos + "Hardware %d| FPGA %d"
OSPEVENT( UMS_BOARD_MPC_GET_VERSION_ACK,		EV_UMS_MCUBRD_BGN + 421 );

//�������������µ���Ϣ
//��Ϣ��: u8(��������) + u8(Դ�ļ�������) + u8(�ļ�������) + s8[](�ļ���)  //ע��(linux�ļ�����������·��)
OSPEVENT( UMS_MPC_BOARD_UPDATE_SOFTWARE_CMD,	EV_UMS_MCUBRD_BGN + 425 );

//�汾���½��֪ͨ����Ϣ�壺u8(��������) + u8(�ļ���) + u8[](�Ƿ�ɹ�<�Ի��>) 
// + u8(�ļ�����) + s8[](�ļ���) + u8 + s8[] + ...
OSPEVENT( UMS_BOARD_MPC_UPDATE_NOTIFY,			EV_UMS_MCUBRD_BGN + 426 );

// APU2 TELNET FTP ����
OSPEVENT( UMS_MPC_BOARD_FTP_TELNET_SWITCH,	    EV_UMS_MCUBRD_BGN + 551 );//TMcuBoardSwitchInfo

//APU2 FTP TELNET ����״̬nty
OSPEVENT( UMS_MPC_BOARD_FTP_TELNET_SWITCH_NTY,	    EV_UMS_MCUBRD_BGN + 552 );//TMcuBoardSwitchNty


/*----------    ���渴������Ϣ�������(26701-26800)  ----------*/
//����ϳ�
const u16     EV_MCUVMP_BGN = 26701;
const u16     EV_MCUVMP_END = EV_MCUVMP_BGN + 74;

//VMP��MCUע������VMP->MCU����Ϣ��ΪTPeriEqpRegReq�ṹ
OSPEVENT( UMS_VMP_MCU_REGISTER_REQ,				EV_MCUVMP_BGN );
//MCU��VMPע��ȷ��,MCU->VMP����Ϣ��ΪTPeriEqpRegAck + TPrsTimeSpan + u16(MTU size)��
OSPEVENT( UMS_MCU_VMP_REGISTER_ACK,				EV_MCUVMP_BGN + 1 );
//MCU��VMPע��ܾ�,MCU->VMP������Ϣ��
OSPEVENT( UMS_MCU_VMP_REGISTER_NACK,			EV_MCUVMP_BGN + 2 );
//VMP��MCU��״̬�ϱ�,VMP->MCU����Ϣ��:TPeriEqpStatus
OSPEVENT( UMS_VMP_MCU_VMPSTATUS_NOTIF,			EV_MCUVMP_BGN + 3 );

//MCU���û���ϳɷ��, ��Ϣ��:TVmpStyleCfgInfo
OSPEVENT( UMS_MCU_VMP_SETSTYLE_CMD,				EV_MCUVMP_BGN + 4 );
//MCU����VMPֹͣMAP, ��Ϣ��: ��, zgc, 2007/04/24
OSPEVENT( UMS_MCU_VMP_STOPMAP_CMD,				EV_MCUVMP_BGN + 5 );
//MCU���������޸ķ���IP��ַ, ��Ϣ�壺u32
OSPEVENT( UMS_MCU_EQP_MODSENDADDR_CMD,          EV_MCUVMP_BGN + 6 );

//MCU����VMP��ʼ����,MCU->VMP����Ϣ��ΪCKDVVMPParam+CKDVVMPParam+u8(�Ƿ�prs)+TVmpStyleCfgInfo+TCapSupportEx
OSPEVENT( UMS_MCU_VMP_STARTVIDMIX_REQ,			EV_MCUVMP_BGN + 11 );
//VMP��MCU��ʼ����ȷ��,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_ACK,			EV_MCUVMP_BGN + 12 );
//VMP��MCU��ʼ�����ܾ�,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_NACK,			EV_MCUVMP_BGN + 13 );
//VMP��MCU�Ŀ�ʼ�����VMP->MCU,��Ϣ���
OSPEVENT( UMS_VMP_MCU_STARTVIDMIX_NOTIF,		EV_MCUVMP_BGN + 14 );

//MCU����VMPֹͣ����,MCU->VMP������Ϣ��
OSPEVENT( UMS_MCU_VMP_STOPVIDMIX_REQ,			EV_MCUVMP_BGN + 21 );
//VMP��MCUֹͣ����ȷ��,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_ACK,			EV_MCUVMP_BGN + 22 );
//VMP��MCUֹͣ�����ܾ�,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_NACK,			EV_MCUVMP_BGN + 23 );
//VMP��MCU��ֹͣ�����VMP->MCU,��Ϣ���
OSPEVENT( UMS_VMP_MCU_STOPVIDMIX_NOTIF,			EV_MCUVMP_BGN + 24 );

//MCU����VMP�ı临�ϲ���,MCU->VMP����Ϣ��ΪCKDVVMPParam+CKDVVMPParam+u8(�Ƿ�prs)+TVmpStyleCfgInfo
OSPEVENT( UMS_MCU_VMP_CHANGEVIDMIXPARAM_REQ,	EV_MCUVMP_BGN + 31 );
//VMP��MCU�ı临�ϲ���ȷ��,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_CHANGEVIDMIXPARAM_ACK,	EV_MCUVMP_BGN + 32 );
//VMP��MCU�ı临�ϲ����ܾ�,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_CHANGEVIDMIXPARAM_NACK,	EV_MCUVMP_BGN + 33 );
//VMP��MCU��״̬�ı�����VMP->MCU,��Ϣ��CKDVVMPParam�ṹ
OSPEVENT( UMS_VMP_MCU_CHANGESTATUS_NOTIF,		EV_MCUVMP_BGN + 34 );

OSPEVENT( UMS_MCU_VMP_UPDATAVMPENCRYPTPARAM_REQ,EV_MCUVMP_BGN + 35 );

OSPEVENT( UMS_MCU_VMP_FASTUPDATEPIC_CMD,		EV_MCUVMP_BGN + 36 );

//MCU�Ժϳ�ͨ��LOG�Ĳ�������, ��Ϣ�壺u8( 0 - ȡ��LOG�� 1 - ����LOG )
OSPEVENT( UMS_MCU_VMP_CHNNLLOGOPR_CMD,          EV_MCUVMP_BGN + 37 );
//MCU ��VMPĳͨ������̨����� ��Ϣ�壺s8 * aliasname
OSPEVENT( UMS_MCU_VMP_CHANGEMEMALIAS_CMD,		EV_MCUVMP_BGN + 38 );

//MCU����VMP���͸��ϲ���,MCU->VMP������Ϣ��
OSPEVENT( UMS_MCU_VMP_GETVIDMIXPARAM_REQ,		EV_MCUVMP_BGN + 41 );
//VMP��MCU���͸��ϲ���ȷ��,VMP->MCU����Ϣ��ΪCKDVVMPParam�ṹ
OSPEVENT( UMS_VMP_MCU_GETVIDMIXPARAM_ACK,		EV_MCUVMP_BGN + 42 );
//VMP��MCU���͸��ϲ����ܾ�,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_GETVIDMIXPARAM_NACK,		EV_MCUVMP_BGN + 43 );
//����VMP��ʼ��
OSPEVENT( EV_VMP_INIT,	  	  				EV_MCUVMP_BGN + 50 );
//��ʾ���е�ͳ�ƺ�״̬
OSPEVENT( EV_VMP_DISPLAYALL,	  			EV_MCUVMP_BGN + 60 );
//��ʾVMP�ڲ��ĺϳɲ���
OSPEVENT( EV_VMP_SHOWPARAM,					EV_MCUVMP_BGN + 61 );
//MCU����VMP���͸��ϲ���,MCU->VMP����Ϣ��u16�����ʣ�CServMsg.SetChnIndex()[1 or 2]
OSPEVENT( UMS_MCU_VMP_SETCHANNELBITRATE_REQ,	EV_MCUVMP_BGN + 65 );
//VMP��MCU���͸��ϲ���ȷ��,VMP->MCU����Ϣ��ΪCKDVVMPParam�ṹ
OSPEVENT( UMS_VMP_MCU_SETCHANNELBITRATE_ACK,	EV_MCUVMP_BGN + 66 );
//VMP��MCU���͸��ϲ����ܾ�,VMP->MCU������Ϣ��
OSPEVENT( UMS_VMP_MCU_SETCHANNELBITRATE_NACK,	EV_MCUVMP_BGN + 67 );
//����I֡,CServMsg.GetChnIndexΪ�����ͨ����
OSPEVENT( UMS_VMP_MCU_NEEDIFRAME_CMD,			EV_MCUVMP_BGN + 70 );
//��������Ƿ��������VMP�ڲ�ʹ�ã���Ϣ�壺u8: 0�����ã�1����
OSPEVENT( EV_VMP_BACKBOARD_OUT_CMD,         EV_MCUVMP_BGN + 71 );
//����VMP֡��
OSPEVENT( EV_VMP_SETFRAMERATE_CMD,			EV_MCUVMP_BGN + 72 );
//MCU֪ͨVMP���ӻ�ɾ��ͨ��(������ͣ��Ӧͨ���Ľ���)�����Ϣ�壺u8: channelidx, u8 byAdd
OSPEVENT( UMS_MCU_VMP_ADDREMOVECHNNL_CMD,		EV_MCUVMP_BGN + 73 );
//MCU֪ͨVMPͣ��ĳһ���ͨ�������Ϣ�壺u8 chnnelIdx,u8 byActive
OSPEVENT( UMS_MCU_VMP_STARTSTOPCHNNL_CMD,		EV_MCUVMP_BGN + 74 );

OSPEVENT( UMS_MCU_VMP_SETQTMEDIAKEY_CMD,		EV_MCUVMP_BGN + 75 );
/*----------    ���渴������Ϣ�������(26701-26800)  ----------*/

//////////////////////////////////////////////////////////////////////////
//��������������Ϣ
/*MCU��BAS��ҵ��ӿ���Ϣ(26601-26700)*/
const u16     EV_UMS_MCUBAS_BGN = 26601;
const u16     EV_UMS_MCUBAS_END = EV_UMS_MCUBAS_BGN + 99;

//������������MCU����ע������BAS->MCU����Ϣ��ΪTPeriEqpRegReq�ṹ
OSPEVENT( UMS_BAS_MCU_REG_REQ,					EV_UMS_MCUBAS_BGN );
//MCU����Ӧ��MCU->BAS����Ϣ��Ϊ��Ϣ��ΪTPeriEqpRegAck + TPrsTimeSpan + u16(MTU size)
OSPEVENT( UMS_MCU_BAS_REG_ACK,					EV_UMS_MCUBAS_BGN + 1 );
//MCU�ܾ�Ӧ��MCU->BAS������Ϣ��
OSPEVENT( UMS_MCU_BAS_REG_NACK,					EV_UMS_MCUBAS_BGN + 2 );
//������״̬֪ͨ��BAS->MCU����Ϣ��ΪTPeriEqpStatus
OSPEVENT( UMS_BAS_MCU_BASSTATUS_NOTIF,			EV_UMS_MCUBAS_BGN + 3 );

//MCU������������MCU->BAS����Ϣ��ΪTAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)+
//                       TMediaEncrypt(audio)+TDoublePayload(Audio)�ṹ+TCapSupportEx,
//     ҵ����Ϣ��ͨ��������ָ��ͨ�� 1�� MAXNUM_RTPHDR_CHNNL ΪRTPͷ����ͨ��������Ϊ����ͨ��
//apu2 ��Ƶ��������ʱ����Ϣ��ΪTAudAdaptParam*byOutNum+TMediaEncrypt+TDoublePayload
OSPEVENT( UMS_MCU_BAS_STARTADAPT_REQ,			EV_UMS_MCUBAS_BGN + 5 );
//��������Ӧ����Ϣ��BAS->MCU����Ϣ��: TEqp
OSPEVENT( UMS_BAS_MCU_STARTADAPT_ACK,			EV_UMS_MCUBAS_BGN + 6 );
//��������Ӧ����Ϣ��BAS->MCU����Ϣ��: TEqp
OSPEVENT( UMS_BAS_MCU_STARTADAPT_NACK,			EV_UMS_MCUBAS_BGN + 7 );

//MCUֹͣ�������MCU->BAS������Ϣ�壬ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_MCU_BAS_STOPADAPT_REQ,			EV_UMS_MCUBAS_BGN + 10 );
//ֹͣ����Ӧ����Ϣ��BAS->MCU������Ϣ��
OSPEVENT( UMS_BAS_MCU_STOPADAPT_ACK,			EV_UMS_MCUBAS_BGN + 11 );
//ֹͣ����Ӧ����Ϣ��BAS->MCU������Ϣ��
OSPEVENT( UMS_BAS_MCU_STOPADAPT_NACK,			EV_UMS_MCUBAS_BGN + 12 );

//MCU�ı������������MCU->BAS����Ϣ��ΪTAdaptParam�ṹ,ҵ����Ϣ��ͨ��������ָ��ͨ��
//TAdaptParam �е�����Ƶ������Ч
OSPEVENT( UMS_MCU_BAS_SETADAPTPARAM_CMD,		EV_UMS_MCUBAS_BGN + 15 );
OSPEVENT( UMS_MCU_BAS_CHANGEAUDPARAM_REQ,		EV_UMS_MCUBAS_BGN + 16 );
OSPEVENT( UMS_BAS_MCU_CHANGEAUDPARAM_ACK,		EV_UMS_MCUBAS_BGN + 17 );
OSPEVENT( UMS_BAS_MCU_CHANGEAUDPARAM_NACK,		EV_UMS_MCUBAS_BGN + 18 );
//����������ͨ��״̬֪ͨ��BAS-> MCU ����Ϣ��BYTE(����ID) + TBasChnStatus,ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_BAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 20 );

//��Ƶ������ͨ��״̬֪ͨ AUDBAS->MCU����Ϣ��u8(�������ͣ�APU2_BAS_CHN) + TAudBasChnStatus
OSPEVENT( UMS_AUDBAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 46 );

//��Ϣ�壺THDAdaptParam+THDAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)
//        ҵ����Ϣ��ͨ��������ָ��ͨ��, ����˫��ͨ��������TAdaptParam��ȫһ��
OSPEVENT( UMS_MCU_HDBAS_STARTADAPT_REQ,         EV_UMS_MCUBAS_BGN + 30 );
//��������Ӧ����Ϣ��HDBAS->MCU����Ϣ��: TEqp, ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_HDBAS_MCU_STARTADAPT_ACK,         EV_UMS_MCUBAS_BGN + 31 );
//��������Ӧ����Ϣ��HDBAS->MCU����Ϣ��: TEqp, ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_HDBAS_MCU_STARTADAPT_NACK,        EV_UMS_MCUBAS_BGN + 32 );
//������״̬֪ͨ��HDBAS->MCU����Ϣ��: TPeriEqpStatus
OSPEVENT( UMS_HDBAS_MCU_BASSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 33 );

//MCUֹͣ�������MCU->HDBAS������Ϣ�壬ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_MCU_HDBAS_STOPADAPT_REQ,          EV_UMS_MCUBAS_BGN + 35 );
//ֹͣ����Ӧ����Ϣ��HDBAS->MCU������Ϣ��
OSPEVENT( UMS_HDBAS_MCU_STOPADAPT_ACK,          EV_UMS_MCUBAS_BGN + 36 );
//ֹͣ����Ӧ����Ϣ��HDBAS->MCU������Ϣ��
OSPEVENT( UMS_HDBAS_MCU_STOPADAPT_NACK,         EV_UMS_MCUBAS_BGN + 37 );

//��Ϣ�壺THDAdaptParam+THDAdaptParam+TMediaEncrypt(video)+TDoublePayload(video)
//        ҵ����Ϣ��ͨ��������ָ��ͨ��, ����˫��ͨ��������TAdaptParam��ȫһ��
OSPEVENT( UMS_MCU_HDBAS_SETADAPTPARAM_CMD,		EV_UMS_MCUBAS_BGN + 40 );
//����������ͨ��״̬֪ͨ��HDBAS-> MCU ����Ϣ��: BYTE(ͨ������) + THDBasVidChnStatus/THDBasDVidChnStatus,ҵ����Ϣ��ͨ��������ָ��ͨ��
OSPEVENT( UMS_HDBAS_MCU_CHNNLSTATUS_NOTIF,		EV_UMS_MCUBAS_BGN + 45 );

OSPEVENT( UMS_MCU_BAS_FASTUPDATEPIC_CMD,			EV_UMS_MCUBAS_BGN + 25 );
OSPEVENT( UMS_BAS_MCU_NEEDIFRAME_CMD,				EV_UMS_MCUBAS_BGN + 26 );

OSPEVENT( UMS_BAS_AUD_SET_SYNC_CMD,					EV_UMS_MCUBAS_BGN + 27 );

OSPEVENT( UMS_BAS_AUD_SET_MEDIA_KEY_CMD,			EV_UMS_MCUBAS_BGN + 28 );

OSPEVENT( UMS_MCU_HDBAS_QTENCRYPT_CMD,	     		EV_UMS_MCUBAS_BGN + 55 );

//////////////////////////////////////////////////////////////////////////
//¼������������Ϣ
/*MCU��REC��ҵ��ӿ���Ϣ(26101-26300)*/
const u16     EV_UMS_MCUREC_BGN = 26101;
const u16     EV_UMS_MCUREC_END = 26300;

//¼�����UMS����ע������REC->UMS����Ϣ��ΪTPeriEqpRegReq�ṹ
OSPEVENT( REC_UMS_REG_REQ,					EV_UMS_MCUREC_BGN );
//MCU����Ӧ��UMS->REC����Ϣ��Ϊ��Ϣ��ΪTPeriEqpRegAck
OSPEVENT( UMS_REC_REG_ACK,					EV_UMS_MCUREC_BGN + 1 );
//MCU�ܾ�Ӧ��UMS->REC������Ϣ��
OSPEVENT( UMS_REC_REG_NACK,					EV_UMS_MCUREC_BGN + 2 );

//UMS������¼���״̬����, UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_GETRECSTATUS_REQ,			EV_UMS_MCUREC_BGN + 5 );
//����¼���״̬��REC->UMS����Ϣ��TPeriEqpStatus
OSPEVENT( REC_UMS_GETRECSTATUS_ACK,			EV_UMS_MCUREC_BGN + 6 );
//�ܾ�����¼���״̬��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_GETRECSTATUS_NACK,		EV_UMS_MCUREC_BGN + 7 );
//¼���״̬֪ͨ��REC->UMS����Ϣ��ΪTPeriEqpStatus
OSPEVENT( REC_UMS_RECSTATUS_NOTIF,			EV_UMS_MCUREC_BGN + 8 );

/*
 *¼���б�������Ϣ��
 *¼����յ��������䷢��¼���ļ�֪ͨ��ȫ��������Ϻ���ACK��Ϣ
 *��¼����ܾ������б��������NACK��Ϣ��
 */
//UMS����¼�������¼���б����UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_LISTALLRECORD_REQ,		EV_UMS_MCUREC_BGN + 10 );
//¼�����Ӧ��(���)��Ϣ��REC->UMS,��Ϣ��ΪTEqp
OSPEVENT( REC_UMS_LISTALLRECORD_ACK,		EV_UMS_MCUREC_BGN + 11 );
//¼����ܾ�¼���б�����REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_LISTALLRECORD_NACK,		EV_UMS_MCUREC_BGN + 12 );
//¼����б�֪ͨ��Ϣ��REC->UMS, ��Ϣ��ΪTEqp+TRecFileListNotify
OSPEVENT( REC_UMS_LISTALLRECORD_NOTIF,		EV_UMS_MCUREC_BGN + 13 );

//UMS������¼���¼��ͨ��״̬����, UMS->REC, ��Ϣ��ΪTEqp���ŵ���λ����Ϣͷ��
OSPEVENT( UMS_REC_GETRECORDCHNSTATUS_REQ,	EV_UMS_MCUREC_BGN + 15 );
//����¼����ŵ�״̬��REC->UMS����Ϣ��TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_GETRECORDCHNSTATUS_ACK,	EV_UMS_MCUREC_BGN + 16 );
//�ܾ�����¼����ŵ�״̬��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_GETRECORDCHNSTATUS_NACK,	EV_UMS_MCUREC_BGN + 17 );
//¼���¼���ŵ�״̬֪ͨ��REC->UMS����Ϣ��ΪTEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_RECORDCHNSTATUS_NOTIF,	EV_UMS_MCUREC_BGN + 18 );


//MCU������¼�������ͨ��״̬����, UMS->REC, ��Ϣ��ΪTEqp���ŵ���λ����Ϣͷ��
OSPEVENT( UMS_REC_GETPLAYCHNSTATUS_REQ,		EV_UMS_MCUREC_BGN + 20 );
//����¼����ŵ�״̬��REC->UMS����Ϣ��TEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_GETPLAYCHNSTATUS_ACK,		EV_UMS_MCUREC_BGN + 21 );
//�ܾ�����¼����ŵ�״̬��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_GETPLAYCHNSTATUS_NACK,	EV_UMS_MCUREC_BGN + 22 );
//¼��������ŵ�״̬֪ͨ��REC->UMS����Ϣ��ΪTEqp+TRecChnnlStatus
OSPEVENT( REC_UMS_PLAYCHNSTATUS_NOTIF,		EV_UMS_MCUREC_BGN + 23 );

//��ȡ¼����ȣ���Ϣ�壺�� (�ŵ���λ����Ϣͷ)
OSPEVENT( UMS_REC_GETRECPROG_CMD,           EV_UMS_MCUREC_BGN + 24 );
//¼�����ǰ¼�����֪ͨ��Ϣ��REC->UMS����Ϣ��ΪTEqp+TRecProg���ŵ���λ����Ϣͷ
OSPEVENT( REC_UMS_RECORDPROG_NOTIF,			EV_UMS_MCUREC_BGN + 25 );

//��ȡ������ȣ���Ϣ�壺�� (�ŵ���λ����Ϣͷ)
OSPEVENT( UMS_REC_GETPLAYPROG_CMD,          EV_UMS_MCUREC_BGN + 26 );
//¼�����ǰ�������֪ͨ��Ϣ��REC->UMS����Ϣ��ΪTEqp+TRecProg���ŵ���λ����Ϣͷ
OSPEVENT( REC_UMS_PLAYPROG_NOTIF,			EV_UMS_MCUREC_BGN + 27 );
//¼����쳣֪ͨ��Ϣ��REC->UMS����Ϣ��ΪTEqp���ŵ��źʹ�����λ����Ϣͷ
OSPEVENT( REC_UMS_EXCPT_NOTIF,				EV_UMS_MCUREC_BGN + 28 );


/////////////////
//������Ϣ

//UMS���󲥷ţ�UMS->REC����Ϣ��ΪTEqp + TMediaEncrypt(video) + TDoublePayload(main video) +
//                TMediaEncrypt(audio) + TDoublePayload(main audio) + 
//                TDoublePayload(second video) + TDoublePayload(second audio) +
//				  u8(byDStreamMediaType) +
//                TRecProg(�������) + ¼���� + TCapSupportEx
OSPEVENT( UMS_REC_STARTPLAY_REQ,			EV_UMS_MCUREC_BGN + 30 );
//ͬ��MCU��������Ӧ��REC->UMS����Ϣ��ΪTEqp + TPlayFileAttrib(�����ļ�����) + TPlayFileMediaInfo(�����ļ�ý����Ϣ)
//���ص��ŵ���λ����Ϣͷ
OSPEVENT( REC_UMS_STARTPLAY_ACK,			EV_UMS_MCUREC_BGN + 31 );
//�ܾ�MCU����Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STARTPLAY_NACK,			EV_UMS_MCUREC_BGN + 32 );

//UMS������ͣ��UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_PAUSEPLAY_REQ,			EV_UMS_MCUREC_BGN + 35 );
//RECͬ����ͣ����REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_PAUSEPLAY_ACK,			EV_UMS_MCUREC_BGN + 36 );
//REC�ܾ���ͣ����REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_PAUSEPLAY_NACK,			EV_UMS_MCUREC_BGN + 37 );

//������������UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_RESUMEPLAY_REQ,			EV_UMS_MCUREC_BGN + 40 );
//ͬ��������ţ�REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RESUMEPLAY_ACK,			EV_UMS_MCUREC_BGN + 41 );
//�ܾ��������ţ�REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RESUMEPLAY_NACK,			EV_UMS_MCUREC_BGN + 42 );

//ֹͣ��������UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_STOPPLAY_REQ,				EV_UMS_MCUREC_BGN + 45 );
//ͬ��ֹͣ����Ӧ��,REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STOPPLAY_ACK,				EV_UMS_MCUREC_BGN + 46 );
//�ܾ�ֹͣ����Ӧ��,REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STOPPLAY_NACK,			EV_UMS_MCUREC_BGN + 47 );

//�����Կ����ʽ���ţ�UMS->REC����Ϣ��ΪTEqp+�������(u8)
OSPEVENT( UMS_REC_FFPLAY_REQ,				EV_UMS_MCUREC_BGN + 50 );
//ͬ������ʽ����Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_FFPLAY_ACK,				EV_UMS_MCUREC_BGN + 51 );
//�ܾ������ʽ����Ӧ��,REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_FFPLAY_NACK,				EV_UMS_MCUREC_BGN + 52 );

//�����Կ��˷�ʽ���ţ�UMS->REC����Ϣ��ΪTEqp+���˱���(u8)
OSPEVENT( UMS_REC_FBPLAY_REQ,				EV_UMS_MCUREC_BGN + 55 );
//ͬ����˷�ʽ����Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_FBPLAY_ACK,				EV_UMS_MCUREC_BGN + 56 );
//�ܾ����˷�ʽ����Ӧ��,REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_FBPLAY_NACK,				EV_UMS_MCUREC_BGN + 57 );

//UMS���󽫲��Ž��ȵ������µ�λ�ã���Ϣ��ΪTEqp+TRecProg
OSPEVENT( UMS_REC_SEEK_REQ,					EV_UMS_MCUREC_BGN + 60 );
//ͬ�����Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_SEEK_ACK,					EV_UMS_MCUREC_BGN + 61 );
//�����ܾ���REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_SEEK_NACK,				EV_UMS_MCUREC_BGN + 62 );
//����¼���RTCP������UMS->REC����Ϣ�壺TEqp+Ҫ���õڼ�·����(u8)+TRecRtcpBack
OSPEVENT( UMS_REC_SETRTCP_NFY,				EV_UMS_MCUREC_BGN + 29 );


////////////////
//¼����Ϣ
//��Ϣ��ΪTMt(��¼����նˣ����UMS��Ϊ�գ���ʾ�Ի���¼����������ͬ)
// + TEqp( ��Ҫʹ�õ�¼���) + TRecStartPara + TMediaEncrypt(video) +
//TDoublePayload(video) + TMediaEncrypt(audio) + TDoublePayload(video) +
//TMediaEncrypt(double video) + TDoublePayload(double video) + ¼���� + TCapSupportEx
OSPEVENT( UMS_REC_STARTREC_REQ,				EV_UMS_MCUREC_BGN + 70 );
//ͬ��UMS¼������Ӧ��REC->UMS����Ϣ��ΪTEqp�����ص��ŵ���λ����Ϣͷ
OSPEVENT( REC_UMS_STARTREC_ACK,				EV_UMS_MCUREC_BGN + 71 );
//�ܾ�UMS¼��Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STARTREC_NACK,			EV_UMS_MCUREC_BGN + 72 );

//UMS������ͣ¼��UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_PAUSEREC_REQ,				EV_UMS_MCUREC_BGN + 75 );
//RECͬ����ͣ¼������REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_PAUSEREC_ACK,				EV_UMS_MCUREC_BGN + 76 );
//REC�ܾ���ͣ¼������REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_PAUSEREC_NACK,			EV_UMS_MCUREC_BGN + 77 );

//����¼������UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_RESUMEREC_REQ,			EV_UMS_MCUREC_BGN + 80 );
//ͬ�����¼��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RESUMEREC_ACK,			EV_UMS_MCUREC_BGN + 81 );
//�ܾ�����¼��,REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RESUMEREC_NACK,			EV_UMS_MCUREC_BGN + 82 );

//ֹͣ¼������UMS->REC����Ϣ��ΪTEqp
OSPEVENT( UMS_REC_STOPREC_REQ,				EV_UMS_MCUREC_BGN + 85 );
//ͬ��ֹͣ¼��Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STOPREC_ACK,				EV_UMS_MCUREC_BGN + 86 );
//�ܾ�ֹͣ¼��Ӧ��REC->UMS����Ϣ��ΪTEqp
OSPEVENT( REC_UMS_STOPREC_NACK,				EV_UMS_MCUREC_BGN + 87 );

//�ı�¼��ģʽ����, ��Ϣ��TMt �� u8( REC_MODE_NORMAL, REC_MODE_SKIPFRAME )
OSPEVENT( UMS_REC_CHANGERECMODE_REQ,		EV_UMS_MCUREC_BGN + 90 );
//ͬ�⣬UMS->MCS����Ϣ��Ϊ TMt 
OSPEVENT( REC_UMS_CHANGERECMODE_ACK,		EV_UMS_MCUREC_BGN + 91 );
//���ԣ�UMS->MCS����Ϣ��Ϊ TMt 
OSPEVENT( REC_UMS_CHANGERECMODE_NACK,		EV_UMS_MCUREC_BGN + 92 );

//UMS ����ɾ��¼����еļ�¼��UMS->REC ,��Ϣ��ΪTEqp+��¼��(0��β�ַ���)
OSPEVENT( UMS_REC_DELETERECORD_REQ,			EV_UMS_MCUREC_BGN + 93 );
//¼���ͬ�Ⲣ�ɹ�ɾ��¼���ļ�Ӧ��
//��Ϣ��ΪTEqp
OSPEVENT( REC_UMS_DELETERECORD_ACK,			EV_UMS_MCUREC_BGN + 94);
//¼����ܾ�ɾ��¼�� ��Ϣ��TEqp
OSPEVENT( REC_UMS_DELETERECORD_NACK,		EV_UMS_MCUREC_BGN + 95 );

//UMS������ļ�¼�ļ�, UMS->REC
//��Ϣ��ΪTEqp + u8(�ɼ�¼������) + �ɼ�¼�� + u8(�¼�¼������) + �¼�¼��
OSPEVENT( UMS_REC_RENAMERECORD_REQ,			EV_UMS_MCUREC_BGN + 96 );
//ͬ�⣬��Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RENAMERECORD_ACK,			EV_UMS_MCUREC_BGN + 97 );
//���ԣ���Ϣ��ΪTEqp
OSPEVENT( REC_UMS_RENAMERECORD_NACK,		EV_UMS_MCUREC_BGN + 98 );


//ȡ������¼������ UMS->REC����Ϣ��ΪTEqp +  ¼����
OSPEVENT( UMS_REC_CANCELPUBLISHREC_REQ,		EV_UMS_MCUREC_BGN + 105 );
//ͬ�⣬REC->UMS����Ϣ��Ϊ TEqp
OSPEVENT( REC_UMS_CANCELPUBLISHREC_ACK,		EV_UMS_MCUREC_BGN + 106 );
//���ԣ�REC->UMS����Ϣ��Ϊ TEqp
OSPEVENT( REC_UMS_CANCELPUBLISHREC_NACK,	EV_UMS_MCUREC_BGN + 107 );
//¼�������ؼ�֡
OSPEVENT( REC_UMS_NEEDIFRAME_CMD,	        EV_UMS_MCUREC_BGN + 108 );
//����¼��Դ��BACKRTCP
/*OSPEVENT( UMS_REC_ADJUST_BACKRTCP_CMD,	        EV_MCUREC_BGN + 109 );*/

//֪ͨ���������ɹ�
OSPEVENT(UMS_EQP_SWITCHSTART_NOTIF,			26035);

//¼���������
#define ERR_REC_BGN				24001

#define ERR_REC_NOERROR         ERR_REC_BGN + 0        //û�д���
#define ERR_REC_NORECORD        ERR_REC_BGN + 1        //û�м�¼
#define ERR_REC_OPENRECORD      ERR_REC_BGN + 2        //�򿪼�¼ʧ��
#define ERR_REC_UMMATCHCMD      ERR_REC_BGN + 3        //��ƥ������������һ�������豸��ʼ¼��
#define ERR_REC_VALIDCHN        ERR_REC_BGN + 4        //��Ч��ͨ��
#define ERR_REC_RECORDING       ERR_REC_BGN + 5        //����¼��
#define ERR_REC_PLAYING         ERR_REC_BGN + 6        //���ڲ���
#define ERR_REC_NOTPLAY         ERR_REC_BGN + 7        //����ͨ��û�ڲ��� 
#define ERR_REC_NOTRECORD       ERR_REC_BGN + 8        //¼��ͨ��û��¼��
#define ERR_REC_ACTFAIL         ERR_REC_BGN + 9        //ִ��ָ����������ʧ��
#define ERR_REC_CURDOING        ERR_REC_BGN + 10       //����Ķ�����ǰ����ִ��
#define ERR_REC_RCMD_TO_PCHN    ERR_REC_BGN + 11       //һ������ͨ�������¼��ͨ��
#define ERR_REC_PCMD_TO_RCHN    ERR_REC_BGN + 12       //һ��¼��ͨ�����������ͨ��
#define ERR_REC_DISKFULL        ERR_REC_BGN + 13       //������
#define ERR_REC_FILEDAMAGE      ERR_REC_BGN + 14       //�ļ���
#define ERR_REC_FILEEMPTY       ERR_REC_BGN + 15       //���ļ�
#define ERR_REC_FILEUSING       ERR_REC_BGN + 16       //ָ���ļ����ڱ�����
#define ERR_REC_FILENOTEXIST    ERR_REC_BGN + 17       //ָ���ļ�������
#define ERR_REC_PUBLICFAILED    ERR_REC_BGN + 18       //����ʧ��
#define ERR_REC_RENAMEFILE      ERR_REC_BGN + 19       //�ļ�����ͻ,�����ļ���ʧ��
#define ERR_REC_FILEEXISTED     ERR_REC_BGN + 20       //�ļ�����ͻ,�޷�¼��
#define ERR_REC_PLAYERRPAYLOAD  ERR_REC_BGN + 21       //�����ļ�ý���غ���������鲻ƥ��
#define ERR_REC_CALLLIBFAILED   ERR_REC_BGN + 22       //����¼���ʧ��,�������°�װ
#define ERR_REC_SETMOTHODFAILED ERR_REC_BGN + 23       //¼��ʽ����ʧ��
#define ERR_REC_PALYFILERES		ERR_REC_BGN + 24	   //¼���ļ��ֱ���ƫ��
#define ERR_REC_FILENAMETOOLONG ERR_REC_BGN + 25       //�����ļ�������    // add by jlb  081026
#define ERR_REC_HAS_UNDERLINE	ERR_REC_BGN + 26       //�û�����¼���ļ��ļ����а����»����ַ� // [8/1/2011 liuxu]
#define ERR_REC_WRITE_FILE_ERR	ERR_REC_BGN + 27       //д�ļ�����, ¼����ֹ // [8/1/2011 liuxu]
#define ERR_REC_CREATE_SNDSOCK  ERR_REC_BGN + 28    //����ģ�鴴��socketʧ�� // [pengjie 2011/8/25]
#define ERR_REC_PLAYFILE_HPDISMATCH  ERR_REC_BGN + 29    //���鲻֧�ַ����ļ���high profile����[zhouyiliang 20120309]

#ifdef WIN32
#pragma pack( pop )
#endif

#endif