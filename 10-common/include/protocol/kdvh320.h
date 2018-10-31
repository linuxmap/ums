/*****************************************************************************
ģ����      : Kdv H320
�ļ���      : KdvH320.h
����ļ�    : 
�ļ�ʵ�ֹ���: h.320Э��ջ�ӿ�ͷ�ļ�
����        : ���ؾ�
�汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/04/06  1.0         ���ؾ�      ����
2004/11/08  1.0         ����      ����ع��������Ż�����
******************************************************************************/

#ifndef _KDVH320_H
#define _KDVH320_H

#include "kdvtype.h"
#include "kdvh320def.h"

#ifdef WIN32
#pragma pack(1)
#define H320PACKED 
#else
#define H320PACKED __attribute__((__packed__))	
#endif // WIN32

//Э��ջ״̬�������Զ��ϱ�
typedef struct tagKDVH320State
{
	u16 m_wState;		//״̬����	
	u16 m_wLength;		//���ݳ���
    u8 *m_pbyContent;	//״̬����

}H320PACKED TKDVH320State;

//����ģʽ
typedef struct tagKDVH320MuxMode
{
	u8  m_byTransRate;
	u8  m_byAudType;
	u8  m_byVidType;
	u8  m_byLSDType;
	u8  m_byHSDType;
	u8  m_byMLPType;
	u8  m_byHMLPType;
	u8  m_byEncrypt;

}H320PACKED TKDVH320MuxMode;

//e1������Ϣ
typedef struct tagKDVH320E1Info
{
	u32 m_dwTsMask;						//ʱ϶����
	u8  m_byChanId;						//E1ͨ��id����ӦE1�ۺţ�

}H320PACKED TKDVH320E1Info;

//������
typedef struct tagTKdvH320Cap
{
public:
    BOOL32 IsExistCap(u32 dwCap);   
    BOOL32   AddCap(u32 dwCap);

public:
	u32 m_adwCapList[simplecap_max_num];
	u8  m_byActualNum;
    
}H320PACKED TKdvH320Cap;

// xsl [8/8/2005] ����������������
enum KDVH320_CAPTYPE
{
    CAPTYPE_TRANSRATE = 1,
    CAPTYPE_AUDIO,
    CAPTYPE_VIDEO,
    CAPTYPE_LSD,
    CAPTYPE_HSD,
    CAPTYPE_MLP,
    CAPTYPE_HMLP
};

typedef struct tagTKdvH320CapSet
{
public:    
    void ClearAll();

    BOOL32 AddTransCap(u32 dwCap);
    BOOL32 AddVidCap(u32 dwCap, u32 dwMpi);
    BOOL32 AddAudCap(u32 dwCap);
    BOOL32 AddLsdCap(u32 dwCap);
    BOOL32 AddHsdCap(u32 dwCap);
    BOOL32 AddMlpCap(u32 dwCap);
    BOOL32 AddHmlpCap(u32 dwCap);
    
    BOOL32 IsExistCap(u32 dwCap, u8 byCapType);   

public:
	TKdvH320Cap m_tTransRateCap;    //����������
	TKdvH320Cap m_tAudioCap;        //��Ƶ������
	TKdvH320Cap m_tVideoCap;        //��Ƶ������
	TKdvH320Cap m_tLSDCap;          //lsd
	TKdvH320Cap m_tHSDCap;          //hsd
	TKdvH320Cap m_tMLPCap;          //mlp
	TKdvH320Cap m_tHMLPCap;         //h-mlp
	
	u8   m_byMBECap;                //�Ƿ�֧��mbeָ��Ĵ���
	u8   m_byH224LsdCap;            //H.224 Lsd������fecc
	u8   m_byT120Cap;               //�Ƿ�֧��t.120
	
	u8   m_byEncryptCap;            //�Ƿ�֧��Encrypt
	u8   m_byV120LsdCap;            //�Ƿ�֧��V.120Lsd
	u8   m_byV120HsdCap;            //V.120 hsd
	u8   m_byV14LsdCap;             //V.14 lsd
	u8   m_byV14HsdCap;             //V.14 hsd
	u8   m_byH224MlpCap;            //H.224 Mlp
	u8   m_byH224HsdCap;            //H.224 Hsd
	u8   m_byH224SimCap;            //H.224 sim
	u8   m_byNilDataCap;            //Nil-Data
	u8   m_byH224TokenCap;          //H.224 Token

}H320PACKED TKdvH320CapSet;

typedef struct tagH320IIS
{
    u8  m_byIISType;                //define in kdvh320def.h
    s8  m_szAlias[MAXLEN_EPALIAS];  //alias
    
}H320PACKED TH320IIS;

typedef struct tagH320TIL
{
    u8  m_byMcuId;                  //mcu id
    u8  m_abyMtId[MAXNUM_MT];       //mt id array
    u8  m_byMtNum;                  //mt count

}H320PACKED TH320TIL;

typedef struct tagH320Mt
{
    u8  m_byMcuId;                  //mcu id
    u8  m_byMtId;                   //mt id    

}H320PACKED TH320Mt;

typedef struct tagH320MtExt
{
    TH320Mt m_tMt;
    s8      m_szAlias[MAXLEN_EPALIAS];  //alias

}H320PACKED TH320MtExt;

typedef struct tagH320TIR
{
    TH320Mt m_tLsdTokenMt;
    TH320Mt m_tHsdTokenMt;
    TH320Mt m_tChairTokenMt;

}H320PACKED TH320TIR;

//Э��ջͳ����Ϣ������Э��ջ�����߲�ѯ
typedef struct tagKDVH320Statistics
{
	//capability set
	TKdvH320CapSet  m_tLocalCapSet;
	TKdvH320CapSet  m_tRemoteCapSet;
	TKdvH320CapSet  m_tCommCapSet;
	
	//multiplex&demultiplex mode
	TKDVH320MuxMode m_tLocalMuxMode;
	TKDVH320MuxMode m_tRemoteMuxMode;
	
	u8              m_byConnectted;  //connectted?	
	u8              m_byInConf;      //in conference?
	u32             m_dwMaxVidRate;  //maxium video rate can send
}H320PACKED TKDVH320Statistics;

//Audio/Video... ���ݽ��պ��֪ͨ�ص�
typedef void (*H320DataRcvCB)( u8 *pbyBuff, u32 dwLen, u32 dwContext );

//FECC�ص�
typedef void (*H320FECCProcCB)( u8 byAction, u8 byParam1, u8 byParam2, TH320Mt tDstMt, TH320Mt tSrcMt, u32 dwContext );

//״̬�仯�ص�
typedef void (*H320StateProcCB)( TKDVH320State tState, u32 dwContext );

//ָ��ص�
typedef void (*H320CmdProcCB)( u16 wCmdId, u8 *pbyParam, u16 wParamNum, u32 dwContext );

//��������
class CKdvH320Stack;

//Э��ջ
class CKdvH320
{
public:
	CKdvH320();
	virtual ~CKdvH320();

	//����Э��ջ
	u16 StartUp();
	//�ر�Э��ջ
	u16 Shutdown();

	//���ñ���������
	u16 SetLocalCapSet( TKdvH320CapSet &tLocalCapSet );

    //�������������ȼ�, ��˳���ɸߵ��ͣ�û�����õĲ���Ĭ�����ȼ�
    u16 SetPriCapset(TKdvH320CapSet &tPriCapset);    

	//ע��ص�����	
	u16 RegAudioProcCB( H320DataRcvCB lpCB, u32 dwContext ); //Audio	
	u16 RegVideoProcCB( H320DataRcvCB lpCB, u32 dwContext ); //Video	
	u16 RegHSDProcCB( H320DataRcvCB lpCB, u32 dwContext );   //HSD
	u16 RegCIProcCB( H320CmdProcCB lpCB, u32 dwContext );    //C&I	
	u16 RegFECCProcCB( H320FECCProcCB lpCB, u32 dwContext ); //FECC	
	u16 RegStateChangeProcCB( H320StateProcCB lpCB, u32 dwContext ); //State Change
		
	//���п�ʼ
	u16 CallStart( TKDVH320E1Info &tE1Info, u8 byWorkMode = callmode_unicast);
	//���н���
	u16 CallEnd();    
	
	//Զ������ͷ����	
	u16 StartFECC(); //����fecc����	
	u16 StopFECC();  //ֹͣfecc����	
	u16 StartCamAction( u8 byMcuId, u8 byMtId, u8 byAction, u8 byTimeOut );//����ͷ������ʼ	
	u16 ContinueCamAction( u8 byMcuId, u8 byMtId, u8 byAction );  //����ָ��������ͷ����	
	u16 StopCamAction( u8 byMcuId, u8 byMtId, u8 byAction );      //ָֹͣ��������ͷ����	
	u16 SelectVideoSource( u8 byMcuId, u8 byMtId, u8 byVidSrcNum,  
                           u8 byMode = vidmode_motion );          //ѡ����ƵԴ	
	u16 StorePreset( u8 byMcuId, u8 byMtId, u8 byPresetNum );     //Ԥ��λ����
	u16 ActivatePreset( u8 byMcuId, u8 byMtId, u8 byPresetNum );  //Ԥ��λ����
	
	//h.230 C&I ָ���
	u16 SendCommand( u16 wCmdInd, u8 *pbyParams, u8 byParamNum );
	
	//Audio/Video... ���ݷ���
	u16 SendData( u8 *pbyDataBuf, u32 dwDataLen, u8 byDataType );

    u16 SetVidLoopback(BOOL32 bLoop);
    u8 GetPeriE1Num();

	//��ѯЭ��ջ״̬
	u16 GetStatistics( TKDVH320Statistics &tStatistics );    
   
private:
	CKdvH320Stack *m_pcH320Stack;
	
};

API void h320stackver();                //ver

//���ô�ӡ����
API void h320stacksetlog(u8 byLevel);

//help
API void h320stackhelp();

API void sendaudiodelaytime(s32 nTime); //send
API void setaudiodelaytime(s32 nTime);  //receive

API void h320ss(u8 byChanId);

#if defined(_VXWORKS_) || defined(_LINUX_)
API void pe1Chaninfo(u8 byChanId);
#endif

#endif ////


//----------------------------------------------------------------------

//end of file





