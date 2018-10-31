#ifndef _h_cnstruct_h__
#define _h_cnstruct_h__
#include "tpsys.h"
#include <time.h>

#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "osp.h"
#include "cnconst.h"
#include "cnstype.h"

typedef struct tagTTPMCUSelViewReq
{
	TTPTerLabel tTerLabel;
	EmTpCtrlMode emTpCtrlMode;
	u8           byPos;
	
	tagTTPMCUSelViewReq()
	{
		memset(this, 0, sizeof(struct tagTTPMCUSelViewReq));
	}
}TTPMCUSelViewReq;

typedef struct tagTTPShowLogo
{
	s8        achLogoName[TP_MAX_ALIAS_LEN + 1];
	BOOL      bIsShowLogo;
    EmTpColor emColor;
    EmTpSize  emSize;
	EmTpLogoStyle emStyle;
	BOOL      bInit;//��ʶT300��һ������
}TTPShowLogo;

typedef struct tagTTPLogoInfo
{
    TTPShowLogo tFirsLogoInfo;
	TTPShowLogo tSecondLogoInfo;
	TTPShowLogo tThirdLogoInfo;
}TTPLogoInfo;

typedef struct tagTTPShowBanner
{
	s8        achBannerName[TP_MAX_ALIAS_LEN + 1];
    BOOL      bIsShowBanner;
	EmTpColor emColor;
    EmTpSize  emSize;
	EmTpStyle emStyle;
	emTpTransparency emTransparency;
}TTPShowBanner;

typedef struct tagTTPBannerInfo
{
    TTPShowBanner tFirstBannerInfo;
	TTPShowBanner tSeconfBannerInfo;
	TTPShowBanner tThirdBannerInfo;
}TTPBannerInfo;

//add by wangqichang
//��ƵԴ����
typedef struct tagTTPVideoSourceName
{
	EmTPMtVideoPort m_emPortType;
	s8 m_achSourceName[TP_MAX_ALIAS_LEN+1];
	public:
		tagTTPVideoSourceName()
		{
			memset(this, 0 , sizeof( tagTTPVideoSourceName ));
		}
}TTPVideoSourceName;

//ά������������Ƶ����
typedef struct tagTTPVideoInfoTool
{
	EmTPMtVideoPort        m_aemBigVideoSource[emEndMPCodec - 1];//��ͼ����ƵԴ
	EmTPMtVideoPort        m_aemMinVideoSource[emEndMPCodec - 1];//Сͼ����ƵԴ
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid];//��ƵԴ����(6��,ȫ�����������˫��)
	EmVidEncResizeMode     m_emVidEncResizeMode;//����Ƶͼ�������������
	BOOL                   m_bIsH323PipMerge;//H323���黭��ϳ�
	public:
		tagTTPVideoInfoTool(){memset(this,0,sizeof(struct tagTTPVideoInfoTool));}
}TTPVideoInfoTool;

//�пص��ӻ�������Ϣ
typedef struct tagTCentreTVCfg
{
	EmSerialType           emSerialType;  //���ӻ����Ӵ�������
	EmTvPowerMode          emTvPowerMode; //���ӻ�����״̬ 
	EmTVAudVisMode         emAudVisMode; //���ӻ�����ģʽ
	EmTVDisplayMode        emDisMode;    //���ӻ���ʾģʽ
	EmTVInputSelect        emInpSelect;  //��������ѡ��
	EmTvSrcPowerMode	   emTvSrcPowerMode;//���ӻ��ϵ�ǰ����״̬
	EmTVModle			   emTvModle;  //���ӻ��ͺ�   add for B4 ---2015/2/4
    
	public:
		tagTCentreTVCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreTVCfg) );
		}
		
}TCentreTVCfg;

//�пش�����Ϣ
typedef struct tagTCentreCurInfo
{
	BOOL			bCurOpen;
	u8				byCurNum;
	TCentreCurName  tCenCurName[MAX_CURTAIN_NUM];
	public:
		tagTCentreCurInfo()
		{
			memset( this, 0, sizeof(struct tagTCentreCurInfo) );
		}

}TCentreCurInfo;

//ȫ�������Ԥ��λ��
typedef struct tagTPanCamName
{
    s8  achPanCamName[MAX_PANCAMNAME_LEN];
	public:
		tagTPanCamName()
		{
			memset( this, 0, sizeof(struct tagTPanCamName) );
		}
		
}TPanCamName;
//ÿ�������һ��Ԥ��λ���Ϊ16��
typedef struct tagTPanCamGroupName
{
    TPanCamName  tPanCamName[MAX_PRESET_NUM];
	public:
		tagTPanCamGroupName()
		{
			memset( this, 0, sizeof(struct tagTPanCamGroupName) );
		}
		
}TPanCamGroupName;

//ȫ���������Ϣ
typedef struct tagTPanCamInfo
{
	BOOL			  bPanCamOpen[MAX_PAN_NUM]; //ȫ�������״̬
	u8				  byPanCamNum;              //ȫ�����������
	TPanCamGroupName  tPCamGroupName[MAX_PAN_NUM];       
	public:
		tagTPanCamInfo()
		{
			memset( this, 0, sizeof(struct tagTPanCamInfo) );
		}
		
}TPanCamInfo;

//end add

//˫����������
typedef struct tagTTPVAdapterInfo
{
	BOOL    bStartAdapter; //�Ƿ���˫������
	u32     dwProfile;    //Hp or BP
	u32     dwWidth; 	 //����ֱ��ʿ��
	u32     dwHeight;	 //����ֱ��ʸ߶�
	u32     dwFramerate; //����֡��
	public:
		tagTTPVAdapterInfo(){memset(this,0,sizeof(struct tagTTPVAdapterInfo));}
}TTPVAdapterInfo;

#endif //_h_cnstruct_h__