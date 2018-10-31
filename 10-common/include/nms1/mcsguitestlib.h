/********************************************************************
ģ����:      �������̨������Կ�
�ļ���:      McsGuiTestLib.h
����ļ�:    McsGuiTestCom.h	GuiUnit.h	kdvType.h	kdvDef.h
�ļ�ʵ�ֹ��� �������̨���ɲ��Խ����ӿڶ���
���ߣ�       ���  
�汾��       4.0
------------------------------------------------------------------------
�޸ļ�¼:
��		��	�汾	�޸���	�߶���	�޸�����
2004/11/22	3.5		���			����
2005/07/08  4.0     ����          ����4.0����
*********************************************************************/

/*********************************************************************
							ʹ��˵��

1.������
	a.���� GuiRunMcs(LPCTSTR szPath) �ӿ�, ����������̨Ӧ�ó���·����,
		��Ӧ�ó����Ѿ�����������c, ����ת��b

	b.���� ConnectMcu(LPCTSTR szIp, LPCTSTR szUser, LPCTSTR szPwd),
		����������̨Ҫ���ӵ�MCU�Ĳ���, �������̨���Զ����Ӹ�MCU��Ȼ��ת��d

	c.���� GetMcuProcessIDByAlias(const s8 *pszMcuName, const s8 *pszProcessName = MCSUI_PROCESS_NAME),
		�������ӵ�MCU���ͽ�����, �Զ������������Ļ������̨��Ȼ��ת��d

	d.���ӿ���̨�ɹ���,�ٵ��� GuiInitUIHandle()�ӿڶԽ���Ԫ�ؽ��г�ʼ��, 
		��c.������ʧ�ܻ�d.�в���ʧ�ܽ����ʼ��ʧ�ܡ�Ȼ��ת��e��ֱ��ת��f

	e.��ѡ������ SetOprDelay(BOOL bDelay = TRUE) ���þ�������Ƿ���ʱ, Ĭ��Ϊ����ʱ��Ȼ��ת��f

	f.�����þ���ӿڽ��н������.

2.�������֮ǰ���л�������������

3.�����ն�ʱ, ֱ���ڱ���MCU������, ���з�ʽ�̶�
*********************************************************************/

#ifndef	__MCSUITESTLIB_H
#define __MCSUITESTLIB_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h>
#include "osp.h"
#include "vccommon.h"
#include "mcuconst.h"
#include "McsGuiTestCom.h"
#include "GuiUnit.h"
#include "addrbook.h"

//	�ն˲���
typedef struct tagMtCfg
{
    tagMtCfg()
    {
        byAliasType = mtAliasTypeH323ID;
        ZeroMemory(aszAlias, sizeof (aszAlias));
        ZeroMemory(reserved, sizeof (reserved));
    }
	u8	byAliasType;		            //	�ն˱�������, mtAliasTypeTransportAddress, mtAliasTypeE164, mtAliasTypeH323ID, mtAliasTypeH320ID
	s8	aszAlias[MAXLEN_DISP_ALIAS];	//	������ H320�ǽضϺ�ı���
    u32  reserved[16];                  //  ����, ��type��320ID��[0] = ��ţ�[1] = �ۺţ� [2] = ͨ����
} TMtCfg;

//	H320�ն˲���
typedef struct tagH320MtCfg
{
    tagH320MtCfg()
    {
        byLayer = 0;
        bySlot = 0;
        byChannel = 0;
    }   
	s8  byLayer;                        // ���
    s8  bySlot;                         // �ۺ�
    s8  byChannel;                      // ͨ����

} TH320MtCfg;

// ����ն�ʱ�Ĳ���
typedef struct tagAddMtCfg
{
    tagAddMtCfg()
    {
        ZeroMemory(aszMtAlias, sizeof (aszMtAlias));
        byAddToAddr = 0;
        wMtBitrate  = 0;
    }
    s8     aszMtAlias[MAXLEN_DISP_ALIAS];      //  �ն˱���
    u8     byAddToAddr;                        //  �Ƿ񱣴浽��ַ��, 0 - ������, 1- ����
    u16    wMtBitrate;                         //  �ն�����
} TAddMtCfg;

// ���H320�ն�ʱ�Ĳ���
typedef struct tagAddH320MtCfg
{
    tagAddH320MtCfg()
    {
        byAddToAddr = 0;
    }
    tagH320MtCfg m_tCfg;                               //  �ն���Ϣ 
    u8           byAddToAddr;                          //  �Ƿ񱣴浽��ַ��, 0 - ������, 1- ����
} TAddH320MtCfg;

//	�ն˲�������
typedef struct tagMtList
{
    tagMtList()
    {
        byMtNum = 0;
        ZeroMemory(aszMtList, sizeof (aszMtList));
        ZeroMemory(reserved, sizeof(reserved));
    }
	u8	byMtNum;					        //	�˴β����ն˸���
	s8	aszMtList[16][MAXLEN_DISP_ALIAS];	//	�ն˱���, ����H320�ն�ʱ,�ǽ���ضϺ����ʾ�ַ���
    u32 reserved [16];
} TMtList;

//	����ϳ��ն˲���
typedef struct tagVmpMt
{
    tagVmpMt()
    {
        ZeroMemory(aszMtAlias, sizeof (aszMtAlias));
        byChannel       = 0;
        byMemberType    = VMP_MEMBERTYPE_MCSSPEC;
    }
	s8	aszMtAlias[MAXLEN_DISP_ALIAS];	//	�ն˱���
	u8	byChannel;					    //	������һ��ͨ��
    u8	byMemberType;				    //	���淽ʽ
} TVmpMt;

typedef struct tagVideoSrc
{
    tagVideoSrc()
    {
        ZeroMemory(aszMtAlias, sizeof (aszMtAlias));
        byPort = 1;
    }
    s8  aszMtAlias[MAXLEN_DISP_ALIAS];      //  �ն���
    u8  byPort;                             //  ��ƵԴ�˿�
} TVideoSrc;

//	¼�����
typedef struct tagRecorderCfg
{
    tagRecorderCfg()
    {
        ZeroMemory(aszMtAlias,  sizeof (aszMtAlias));
        ZeroMemory(aszRecName,  sizeof (aszRecName));
        ZeroMemory(aszFileName, sizeof (aszFileName));
        byRecMode   = REC_MODE_NORMAL;
        byRecInLowBitrate   = 0;
        byPublishMode   = PUBLISH_MODE_NONE;
        byPublishLevel  = PUBLISH_LEVEL_NORMAL;
    }
	s8	aszMtAlias[MAXLEN_DISP_ALIAS];	//¼���ն���
	s8	aszRecName[32];					//¼�����
	s8	aszFileName[MAX_PATH];			//¼���ļ���
	u8	byRecMode;						//REC_MODE_NORMAL, REC_MODE_SKIPFRAME
	u8	byRecInLowBitrate;				//�Ƿ�¼�Ƶ�����ͼ��
	u8	byPublishMode;					//PUBLISH_MODE_NONE, PUBLISH_MODE_IMMED, PUBLISH_MODE_FIN
	u8	byPublishLevel;					//PUBLISH_LEVEL_NORMAL, PUBLISH_LEVEL_SECRET
} TRecorderCfg;

typedef struct tagVideoSrcPoll
{
    tagVideoSrcPoll()
    {
        ZeroMemory(aszMtAlias, sizeof (aszMtAlias));
        byPortNum = 0;
        ZeroMemory(aaszPort, sizeof (aaszPort));
        ZeroMemory(abyTime, sizeof (abyTime));
    }
    s8  aszMtAlias[MAXLEN_DISP_ALIAS];                          //  �ն���
    u8  byPortNum;                                              //  �˿�����
    s8  aaszPort[MATRIX_MAX_PORT][MATRIX_PORTNAME_LEN + 1];     //  �˿���
    u8  abyTime[MATRIX_MAX_PORT];                               //  ÿ���˿ڵ���ѯ���
} TVideoSrcPoll;




// Mcu �����򵼵Ĵ����������IP��ַΪ������
typedef struct tagMcuWizardSetting
{
    tagMcuWizardSetting()
    {
        dwMcuIP    = 0;
        dwMcuMask  = 0;
        dwGatewayIP= 0;

        chRegGk    = 0;
        dwGkIP     = 0;
        
        ZeroMemory(&szMcuAlias, sizeof(szMcuAlias));
        ZeroMemory(&szMcuE164, sizeof(szMcuE164));
        
    }

    u32 dwMcuIP;                                                  // Mcu IP
    u32 dwMcuMask;                                                // Mcu ��������
    u32 dwGatewayIP;                                              // ���� IP

    s8  chRegGk;                                                  // �Ƿ�ע��Gk, 
                                                                  // 0= ���޸�, 1 = yes, -1 = no
    //  ��ע�ᵽ Gk ʱ����Ҫ��Gk Ip
    u32 dwGkIP;                                                   // Gk IP

    s8  szMcuAlias[MAXLEN_ALIAS];			                      // Mcu ����
    s8  szMcuE164[MAXLEN_E164];			                          // E164 ��

    BOOL32 bReboot;                                               // �Ƿ�������������
} TMcuWizardSetting;

// Mcu �������ò�����IP��ַΪ������
typedef struct tagMcuNetworkSetting
{
    tagMcuNetworkSetting()
    {
        dwMcuIP    = 0;
        dwMcuMask  = 0;
        dwGatewayIP= 0;
            
        chRegGk    = 0;
        dwGkIP     = 0;

        dwMcAddr   = 0;
        dwMcPort   = 0;
        dwDPort    = 0;
        dwHPort    = 0;
            
        wMaxMtNum  = 0;

        ZeroMemory(&szMcuAlias, sizeof(szMcuAlias));
        ZeroMemory(&szMcuE164, sizeof(szMcuE164));
    }

    u32 dwMcuIP;                                                  // Mcu IP
    u32 dwMcuMask;                                                // Mcu ��������
    u32 dwGatewayIP;                                              // ���� IP

    s8  chRegGk;                                                  // �Ƿ�ע��Gk, 
                                                                  // 0= ���޸�, 1 = yes, -1 = no  
    //  ��ע�ᵽ Gk ʱ����Ҫ��Gk Ip
                                                                  
    u32 dwGkIP;                                                   // Gk IP
    s8  szMcuAlias[MAXLEN_ALIAS];			                      // Mcu ����
    s8  szMcuE164[MAXLEN_E164];			                          // E164 ��


    u32  dwMcAddr;                                                //  �鲥��ַ
    u32  dwMcPort;                                                //  �鲥��ʼ�˿�
    u32  dwDPort;                                                 //  ������ʼ�˿�
    u32  dwHPort;                                                 //  H225��ʼ�˿�   

    u16  wMaxMtNum;                                               //  ��������ն���
  
} TMcuNetworkSetting;

// QoS  ������Ϣ
typedef struct tagMcuQosSetting
{
    tagMcuQosSetting()
    {
        m_byQosType  = MCUQOS_SERV; 
        m_byAudLevel = 0;
        m_byVidLevel = 0;
        m_byDataLevel   = 0;
        m_bySignalLevel = 0;
        m_byIpServiceType = IPSERVICETYPE_LOW_DELAY;  
        
        m_bReset = FALSE;
    }

    u8  m_byQosType;					// Qos ���� MCUQOS_SERV, MCUQOS_IP
    u8  m_byAudLevel;					// ��Ƶ�ȼ�
    u8  m_byVidLevel;					// ��Ƶ�ȼ�
    u8  m_byDataLevel;					// ���ݵȼ�
    u8  m_bySignalLevel;				// �źŵȼ�
    u8  m_byIpServiceType;				// IP�������ͣ��ɸ����������������
                                        // IPSERVICETYPE_LOW_DELAY
                                        // IPSERVICETYPE_HIGH_THROUGHPUT
                                        // IPSERVICETYPE_HIGH_RELIABILITY
                                        // IPSERVICETYPE_LOW_EXPENSE
                                        // IPSERVICETYPE_NONE ��ʾ����

    

    BOOL32 m_bReset;                    // TRUE ��ʾ�ָ���Ĭ��ֵ, �������������ֶο��Բ�����д
} TMcuQosSetting;

// SNMP  ������Ϣ
typedef struct tagMcuSnmpSetting
{
    tagMcuSnmpSetting()
    {
        m_dwTrapIp = 0;
        m_wReadWritePort = 0;
        m_wSendTrapPort = 0;
        ZeroMemory(&m_szReadCom, MAXLEN_TRAP_COMMUNITY);
        ZeroMemory(&m_szWriteCom, MAXLEN_TRAP_COMMUNITY);
    }
    u32  m_dwTrapIp;							// Ip    
    u16  m_wReadWritePort;						// ��д�˿�
    u16  m_wSendTrapPort;						// ��Trap�˿�
    s8   m_szReadCom[MAXLEN_TRAP_COMMUNITY];	// ����ͬ��
    s8   m_szWriteCom[MAXLEN_TRAP_COMMUNITY];	// д��ͬ��

} TMcuSnmpSetting;

// Mcu ���õ�����
typedef struct tagMcuNetMiscSetting
{
    tagMcuNetMiscSetting()
    {
        chSaveBw   = 0;
        chSmoothSend = 0;
        dwChainChkTime = 0;
        dwChainChkTimes = 0;
        dwMtRefTime = 0;
        dwAudRefTime = 0;
        dwVidRefTime = 0;

        dwDcsIp      = 0;


        bMPCTran   = FALSE;
        bMPCStack  = FALSE;

        byNetSynType = 0;
        byDri      = 0;
        byE1       = 0;

        bResetToDefault = FALSE;

    }

    s8  chSaveBw;                                                 // �Ƿ��ʡ���跢���������ն˵��������
                                                                  // 0= ���޸�, 1 = yes, -1 = no
    s8  chSmoothSend;                                             // �Ƿ�ƽ������
                                                                  // 0= ���޸�, 1 = yes, -1 = no
    u32 dwChainChkTime;                                           // ���������ʱ��(��)
    u32 dwChainChkTimes;                                          // ����������
    u32 dwMtRefTime;                                              // ���������ն��б�ˢ�¼��(��)
    u32 dwAudRefTime;                                             // ����������ƵԴˢ�¼��(��)
    u32 dwVidRefTime;                                             // ����������ƵԴˢ�¼��(��)

    u32 dwDcsIp;                                                  // ���ݻ��������Ip (0 Ϊ������)
                                                                  // ������

    BOOL32 bMPCTran;                                              //  �Ƿ�MPC ת��
    BOOL32 bMPCStack;                                             //  �Ƿ�MPC����Э��ջ

    u8   byNetSynType;                                            //  ����ͬ��ģʽ 
                                                                  //  MCUSYNMODE_VIBRATE ,  MCUSYNMODE_TRACK
                                                                  //  ����ʱ��������2��
    u8   byDri;                                                   //  DRI ��� 
    u8   byE1;                                                    //  E1 ͨ����

    BOOL32 bResetToDefault;                      //  �Ƿ�ָ���Ĭ��ֵ��
                                                 //  ������˴˲��� TRUE��������ز�����������

} TMcuNetMiscSetting;


typedef struct tagVmpStyleCfg
{
    tagVmpStyleCfg()
    {

        bySchemaId = 0;
        ZeroMemory(aszSchemaName, sizeof(aszSchemaName));

        cBgColor = 0;
        cMtColor = 0;
        cCmColor = 0;
        cSpColor = 0;
    }
/*
    u32      dwFontIndex;                                       // ��������ֵ(δ��)
    u32      dwAlphaIndex;                                      // ͸��������(δ��)
    u32      dwSizeIndex;                                       // ��С����(δ��)
    COLORREF cTextForeColor;                                    // ����ǰ��ɫ
    COLORREF cTextBkColor;                                      // ���屳��ɫ
*/
    u8       bySchemaId;                                        // ���������� 1-5
    s8       aszSchemaName[16];                                 // ������

    COLORREF cBgColor;                                          // ����ɫ
    COLORREF cMtColor;                                          // һ���ն˱߿�ɫ
    COLORREF cCmColor;                                          // ��ϯ�ն˱߿�ɫ
    COLORREF cSpColor;                                          // �����˱߿�ɫ
} TVmpStyleCfg;

// Mcu ���ش��豸���ò���
typedef struct tagMcuPrsSetting
{
    tagMcuPrsSetting()
    {
        dwTime1 = 0;
        dwTime2 = 0;
        dwTime3 = 0;
        dwTime4 = 0;

        bResetToDefault = FALSE;
    }
    u32  dwTime1;                                                //  ��1�ش�(ms)
    u32  dwTime2;                                                //  ��2�ش�(ms)
    u32  dwTime3;                                                //  ��3�ش�(ms)
    u32  dwTime4;                                                //  ����ʱ��(ms)

    BOOL32 bResetToDefault;                                      //  �Ƿ�ָ���Ĭ��ֵ
} TMcuPrsSetting;


// ����ģ������ã�����ģ��ѡ����Ӧ�Ĳ��֡��������ռ��ɡ�
typedef struct tagMcuChipModuleCfg
{
    tagMcuChipModuleCfg()
    {
        byModuleType = 0;
        ZeroMemory(aszModuleName, sizeof(aszModuleName));
        dwMcuStartPort = 0;
        bySwitchBrdIdx = 0;
        dwRecvStartPort = 0;
        for (s32 nIndex = 0; nIndex < 5; nIndex ++)
        {
            bUseMap[nIndex] = FALSE;
        }
        byMaxMinChnl = 0;
        byVideoPipe = 1;
    }

    u8      byModuleType;                   // ģ������, MIXER_MASK  REC_MASK
                                            // TVWALL_MASK, ADAPTER_MASK
                                            // VMP_MASK, PRS_MASK, MULTITVWALL_MASK
    TCHAR   aszModuleName[MAXLEN_NAME];     // ����ģ�����
    u32     dwMcuStartPort;                 // Mcu ��ʼ�˿ں�
    u8      bySwitchBrdIdx;                 // ������������
    u32     dwRecvStartPort;                // ����������ʼ�˿ں�
    BOOL32  bUseMap[5];                     // 0-4�Ƿ�������Ӧ��Map

    // ����4����һ��union�����ֻҪ��һ��
    u8      byMaxMinChnl;                   // ������ͨ����
    u8      byVideoPipe;                    // 1��2����Ƶ����·��
    TMcuPrsSetting tPrsCfg;                 // �����ش�����
    u32     dwRecIp;                        // ¼���IP��ַ
} TMcuChipModuleCfg;

// ����������Ϣ��IP��ַΪ������
typedef struct tagMcuChipCfg
{
    tagMcuChipCfg()
    {
        byChipType = -1;
        dwIP = 0;
        byLayer = 0;
        bySlot = 0;
        for (s32 nIndex = 0; nIndex < 5; nIndex++)
        {
            bUseMod[nIndex] = FALSE;
        }
        byLanIf = 0;
        bBroadcast = FALSE;

    }
    s8  byChipType;                       // ������ 
                                          // MCUCHIP_MPC
                                          // MCUCHIP_APU
                                          // MCUCHIP_VPU  
                                          // MCUCHIP_DEC5 
                                          // MCUCHIP_CRI  
                                          // MCUCHIP_DRI  
                                          // MCUCHIP_MMP

    u32 dwIP;                             // IP��ַ
	u8  byLayer;                          // ���
    u8  bySlot;                           // �ۺ�

    u8  byLanIf;                          // ����ѡ��0:ǰ���ڣ�1: �����ڣ�8000Bֻ��ѡǰ����
    BOOL32 bBroadcast;                    // �Ƿ��鲥��ֻ��Mpc��Cri��Dri����Ч����ÿ�����α���Ҫ��һ����鲥

    BOOL32 bUseMod[5];                    // �Ƿ�������Ӧģ��,TRUE ����
    TMcuChipModuleCfg tModuleCfg[5];      // ģ��������Ϣ
}TMcuChipCfg;



class CMcsIntTestUI
{
public:
	CMcsIntTestUI();
	virtual ~CMcsIntTestUI();

public:
	//-----------------------------------------------------------------------------
	//	���������ʼ������
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ���� GuiRunMcs
	��    �ܣ� ���л������̨����
	��    ���� LPCTSTR szPath					[in] �������̨·����
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL GuiRunMcs(LPCTSTR szPath);

	/*=============================================================================
	�� �� ���� SetGuiMainWindow
	��    �ܣ� ����Ӧ�ó����Ƿ���ڣ�����������GuiUnit�������ھ��
				Ӧ���ں���GuiRunMcs���ú��ٵ��ô˺���
	��    ���� s32 nTimeOut					[in] ����Ӧ�ó���ʱʱ��(ʱ�䵥λ������)
	˵    ���� ��ΪӦ�ó���������Ҫһ��ʱ�䣬���ڴ�ʱ���ڻ�û�в�׽��Ӧ�ó��򽫷���false
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL SetGuiMainWindow(s32 nTimeOut = 0);

	/*=============================================================================
	�� �� ���� GuiInitUIHandle
	��    �ܣ� ��¼���ʼ������Ԫ�ؾ��
	��    ����
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL GuiInitUIHandle();

	/*=============================================================================
	�� �� ���� SetOprDelay
	��    �ܣ� �����Ƿ������ʱ��Ĭ��Ϊ��ʱ��
	��    ���� BOOL bDelay					[in]	true-��ʱ, false-����ʱ
	�� �� ֵ�� void
	=============================================================================*/
	inline void SetOprDelay(BOOL bDelay = TRUE)
	{
		m_bOprDelay = bDelay;
	}

	/*=============================================================================
	�� �� ���� GuiActive
	��    �ܣ� ���������̨��Ϊ��ǰ���� 
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL GuiActive();

	/*=============================================================================
	�� �� ����GetMcuProcessIDByAlias
	��    �ܣ����������ӵ�MCU���ͽ��������ý���ID
	��    ���� 	pszMcuName					[in]	MCU��
				pszProcessName				[in]	������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GetMcuProcessIDByAlias(const s8 *pszMcuName, const s8 *pszProcessName = MCSUI_APP_EXE_NAME);

    /*=============================================================================
	�� �� ����CloseMcs
	��    �ܣ��ر�MCS
	��    ������
	�� �� ֵ����
	=============================================================================*/
    virtual void CloseMcs(void);

public:
	//-----------------------------------------------------------------------------
	//	�������
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//	1. MCU����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ���� ConnectMcu
	��    �ܣ� �������̨����MCU
	��    ����	LPCTSTR szIp				[in]	IP��ַ
				LPCTSTR szUser				[in]	�û���
				LPCTSTR szPwd				[in]	����
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL ConnectMcu(LPCTSTR szIp, LPCTSTR szUser, LPCTSTR szPwd);

	/*=============================================================================
	�� �� ����DisconnectMcu
	��    �ܣ��Ͽ�MCU����
	��    ����pszMcu						[in]	MCU��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DisconnectMcu(const s8 *pszMcu = NULL);

	/*=============================================================================
	�� �� ���� SelectMcu
	��    �ܣ� ѡ��Mcu
	��    ���� pszMcu					[in]	MCU��(�������̨MCUѡ����������)
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL SelectMcu(const s8 *pszMcu);

	//-----------------------------------------------------------------------------
	//	2. ����ȷ�ϲ���
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����KillWarningDlg
	��    �ܣ��رյ����ľ����
	��    ����hParent				[in]	���Ի�����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL KillWarningDlg(HWND hParent = NULL);

    /*=============================================================================
	�� �� ����KillAllWarningDlg
	��    �ܣ��ر����е����ľ����
	��    ������
	�� �� ֵ����
	=============================================================================*/
    virtual void KillAllWarningDlg();

	/*=============================================================================
	�� �� ����ConfirmOperation
	��    �ܣ�ȷ����Ϣ�Ի�����ȷ����ȡ��
	��    ����bConfirm				[in]	���ȷ����ȡ����TRUE��ʾȷ����FALSEȡ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ConfirmOperation(BOOL bConfirm = TRUE);

	/*=============================================================================
	�� �� ����ConfirmPwd
	��    �ܣ�ȷ������
	��    ����	pszPwd							[in]	����
				hParent							[in]	�����ھ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ConfirmPwd(const s8 *pszPwd, HWND hParent = NULL);

	//-----------------------------------------------------------------------------
	//	3. �����л�����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����GuiTemplate
	��    �ܣ��л���ģ��������
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/06	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiTemplate();

	/*=============================================================================
	�� �� ����GuiConfList
	��    �ܣ��л��������б����
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/06	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiConfList();

	/*=============================================================================
	�� �� ����GuiSimConf
	��    �ܣ��л���ģ��᳡����
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/06	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiSimConf();

	/*=============================================================================
	�� �� ����GuiMonitor
	��    �ܣ��л�����ؽ���
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/13	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiMonitor();

	/*=============================================================================
	�� �� ����GuiAddrbook
	��    �ܣ��л�����ַ������
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/13	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiAddrbook();

	/*=============================================================================
	�� �� ����GuiUser
	��    �ܣ��л����û��������
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/13	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiUser();

	/*=============================================================================
	�� �� ����GuiDevManage
	��    �ܣ��л����豸�������
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2004/12/13	3.5		���			����
	=============================================================================*/
	virtual BOOL GuiDevManage();

    /*=============================================================================
	�� �� ����GuiUserSetting
	��    �ܣ��л����û����ý���
	��    ������
	�� �� ֵ��BOOL
	-----------------------------------------------------------------------------
	�޸ļ�¼��
	��		��	�汾	�޸���	�߶���	�޸�����
	2005/03/11	3.6		���			����
	=============================================================================*/
    virtual BOOL32 GuiUserSetting();

    // ���¼��������л�������4.0�����ӵġ�

    /*============================================================================
    �� �� ����GuiMcuManage
    ��    �ܣ��л���Mcu������Ϣ�������
    ��    ������
    �� �� ֵ��BOOL
    ============================================================================*/
    virtual BOOL GuiMcuManage();

    /*============================================================================
    �� �� ����GuiMcuConfig
    ��    �ܣ��л���Mcu���ý���
    ��    ������
    �� �� ֵ��BOOL
    ============================================================================*/
    virtual BOOL GuiMcuConfig();


	/*=============================================================================
	�� �� ����ChangeViewType
	��    �ܣ������ͼ��ť, �л���ͼģʽ
	��    ����byType							[in]	0:ƽ�̴�ͼ�� 1:���� 2:ƽ��Сͼ��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeViewType(u8 byType);

    
	//-----------------------------------------------------------------------------
	//	4.�������
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ���� SelectConf
	��    �ܣ� ��ģ��᳡��ѡ�����
	��    ����	pszConfName				[in]	������
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL SelectConf(const s8 *pszConfName);


	/*=============================================================================
	�� �� ����CreateTemplate
	��    �ܣ���������ģ��
	��    ����	ptConfInfo							[in]	���鴴������
				wMtNum								[in]	�ն˸���
				ptAddMtCfg							[in]	�ն˲���
                wH320MtNum                          [in]	H320�ն˸���
                ptAddH320MtCfg                      [in]	H320�ն˲���
				ptVmpModule							[in]	����ϳɲ���
                pszTwName                           [in]    ���õĵ���ǽ����
				ptTvModule							[in]	����ǽ����
                bUseMainDlg                         [in]    TRUE��ʾ����ʹ�����Ի��������Ϣ����
                                                            FALSE��ʾ�����õ���ʽ�Ի�������
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
	virtual BOOL32 CreateTemplate(const TConfInfo *ptConfInfo, 
                                u16 wMtNum, const TAddMtCfg *ptAddMtCfg,
                                u16 wH320MtNum, const TAddH320MtCfg *ptAddH320MtCfg,
                                const TVmpModule *ptVmpModule = NULL,
                                const s8 *pszTwName = _T(""),
                                const TTvWallModule *ptTvModule = NULL,
                                const BOOL32 bUseMainDlg = TRUE);
    

	/*=============================================================================
	�� �� ����CreateConf
	��    �ܣ�����ģ�崴������
	��    ����	pszConfName			[in]	������
                tStartTime          [in]    ԤԼ�����ʱ��
				bSchedule           [in]    TRUE ��ʾԤԼ���飬FALSE ��ʾ��ʱ����
                bUseWizard          [in]    TRUE ��ʾͨ���򵼴�����FALSE��ʾģ����洴��
	˵    ������ʱ���鲻��Ҫ�� tStartTime
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CreateConf(const s8 *pszConfName, const SYSTEMTIME tStartTime, 
                            BOOL32 bSchedule = FALSE, 
                            BOOL32 bUseWizard = FALSE);


	/*=============================================================================
	�� �� ���� ReleaseConf
	��    �ܣ� ��������
	��    ����	ptszMcu				[in]	��������MCU��(�������̨MCUѡ����������)
				pszConfName			[in]	������
				byTakeMode			[in]	����ģʽ 0:ԤԼ����CONF_TAKEMODE_SCHEDULED
												 	 1:��ʱ����CONF_TAKEMODE_ONGOING
													 2:����ģ��CONF_TAKEMODE_TEMPLATE
	˵    ��������ģ�壬ֻ����ģ���������������ʱ������ģ��᳡�����������δ�ҵ������ڻ����б���������ԤԼ����ֻ�ڻ����б�������
	�� �� ֵ�� BOOL
	=============================================================================*/
	virtual BOOL ReleaseConf(const s8 *pszConfName, u8 byTakeMode);



	/*=============================================================================
	�� �� ����ModifyConf
	��    �ܣ��޸�ԤԼ����
	��    ����	pszConfName							[in]	��Ҫ�޸Ļ���Ļ�����
                tStartTime                          [in]    �µ�ԤԼ�����ʱ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ModifyConf(const s8 *pszConfName, const SYSTEMTIME tStartTime);

	/*=============================================================================
	�� �� ����SaveConf
	��    �ܣ��������
	��    ����	pszConfName							[in]	������
				bSaveAsDefault						[in]	�Ƿ��Ϊȱʡ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SaveConf(const s8 *pszConfName, BOOL bSaveAsDefault = FALSE);


    // �ն˲���


	/*=============================================================================
	�� �� ����AddMt
	��    �ܣ������ն�
	��    ����	pszConfName							[in]	������
				ptAddMtCfg							[in]	Ҫ��ӵ��ն�
				nMtNum								[in]	�ն˸���
				pszMcuAlias							[in]	��Ҫ�����ն˵�MCU, ΪNULL��Ĭ�ϱ���MCU
				bAddFromAddr						[in]	�ӵ�ַ�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/


	virtual BOOL AddMt(const s8 *pszConfName, const TAddMtCfg *ptAddMtCfg, 
						s32 nMtNum = 1, const s8 *pszMcuAlias = NULL,
                        BOOL bAddFromAddr = FALSE);


    //���º����������ӵ�,�����Ҫ�ӵ�ַ����Ӿ�ֱ����AddMt()�Ϳ�����.
    /*============================================================================
    �� �� ����AddH320Mt
    ��    �ܣ�����H320�ն�
    ��    ����	pszConfName					[in]	������
			    ptH320MtCfg 				[in]	Ҫ��ӵ��ն�
			    nMtNum						[in]	�ն˸���
			    pszMcuAlias					[in]	��Ҫ�����ն˵�MCU, ΪNULL��Ĭ�ϱ���MCU
    ˵    ����
    �� �� ֵ��BOOL
    ============================================================================*/
    virtual BOOL AddH320Mt(const s8 *pszConfName, const TAddH320MtCfg *ptH320MtCfg, 
					    s32 nMtNum = 1, const s8 *pszMcuAlias = NULL);

	/*=============================================================================
	�� �� ����DelMt
	��    �ܣ�ɾ���ն�
	��    ����	pszConfName								[in]	������
				ptMtAlias								[in]	Ҫɾ�����ն˱�����
                                                                ����H320�ǽضϺ�ı���
				bySendWarning							[in]	�Ƿ�֪ͨ���Ҷ��ն�
																1: ֪ͨ; 0: ��֪ͨ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DelMt(const s8 *pszConfName, const s8 *ptMtAlias, u8 bySendWarning = 1);



	/*=============================================================================
	�� �� ����CallMt
	��    �ܣ������ն�
	��    ����	pszConfName								[in]	������
				ptMtAlias								[in]	Ҫ���е��ն�
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CallMt(const s8 *pszConfName, const s8 *ptMtAlias);

	/*=============================================================================
	�� �� ����DropMt
	��    �ܣ��Ҷ��ն�
	��    ����	pszConfName								[in]	������
				ptMtAlias								[in]	Ҫ�Ҷϵ��ն�
				bySendWarning							[in]	�Ƿ�֪ͨ���Ҷ��ն�
																1: ֪ͨ; 0: ��֪ͨ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DropMt(const s8 *pszConfName, const s8 *ptMtAlias, u8 bySendWarning = 1);

	/*=============================================================================
	�� �� ����SpecChairman
	��    �ܣ�ָ����ϯ
	��    ����	pszConfName					[in]	������
				pszMtAlias					[in]	�ն˱���
				byType						[in]	0:���ն��ϵ���Ҽ�ѡ��ָ��;
													1:�϶��ն˵���ϯָ̨��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SpecChairman(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����CancelChairman
	��    �ܣ�ȡ����ϯ
	��    ����	pszConfName				[in]	������
				byType					[in]	0:���ն��ϵ���Ҽ�ѡ��ȡ��;
												1:�ӵ���ϯ̨�϶��ն�ȡ��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelChairman(const s8 *pszConfName, u8 byType = 0);

	/*=============================================================================
	�� �� ����SpecSpeaker
	��    �ܣ�ָ��������
	��    ����	pszConfName					[in]	������
				pszMtAlias					[in]	�ն˱���
				byType						[in]	0:���ն��ϵ���Ҽ�ѡ��ָ��;
													1:�϶��ն˵���ϯָ̨��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SpecSpeaker(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����CancelSpeaker
	��    �ܣ�ȡ��������
	��    ����	pszConfName				[in]	������
				byType					[in]	0:���ն��ϵ���Ҽ�ѡ��ȡ��;
												1:�ӵ���ϯ̨�϶��ն�ȡ��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelSpeaker(const s8 *pszConfName, u8 byType = 0);

	/*=============================================================================
	�� �� ����SendMsg
	��    �ܣ����Ͷ���Ϣ
	��    ����	pszConfName						[in]	������
				ptMtList						[in]	�ն��б�
				nRollTimes						[in]	��������
				byMsgType						[in]	ROLLMSG_TYPE_SMS��ROLLMSG_TYPE_PAGETITLE��ROLLMSG_TYPE_ROLLTITLE
				byRollSpeed						[in]	ROLL_SPEED_1��ROLL_SPEED_2��ROLL_SPEED_3
                pszMsg							[in]	����Ϣ����
                pszFileName                     [in]    ����Ϣ�ļ�
                pszLoadMsg                      [in]    ѡ�ö���Ϣ
                bSaveToFile                     [in]    ��Ϊ���ö���Ϣ
	˵    ���������ж�pszFileName, ��ΪNULL���ļ�����;
              Ȼ���ж�pszLoadMsg, ��ΪNULL��ѡ�ö���Ϣ;
              ��������pszMsg
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SendMsg(const s8 *pszConfName, const TMtList *ptMtList,
                        s32 nRollTimes = 1, u8 byMsgType = ROLLMSG_TYPE_SMS,
                        u8 byRollSpeed = ROLL_SPEED_1, const s8 *pszMsg = NULL, 
                        const s8 *pszFileName = NULL, const s8 *pszLoadMsg = NULL,
                        BOOL32 bSaveToFile = FALSE);

    /*=============================================================================
	�� �� ����DeleteMsg
	��    �ܣ�ɾ������Ϣ
	��    ����	pszConfName						[in]	������
				pszMsg						    [in]	����Ϣ����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 DeleteMsg(const s8 *pszConfName, const s8 *pszMsg);

	/*=============================================================================
	�� �� ����StartPoll
	��    �ܣ���ʼ��ѯ
	��    ����	pszConfName			[in]	������
				ptMtList						[in]	�ն��б�
				wPollTime						[in]	��ѯ���                
				bEnableAudio					[in]	�Ƿ����Ƶ
                wPollTimes                      [in]    ��ѯ����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartPoll(const s8 *pszConfName, const TMtList *ptMtList, 
                           u16 wPollTime, BOOL bEnableAudio,
                           u16 wPollTimes);

	/*=============================================================================
	�� �� ����StopPoll
	��    �ܣ�ֹͣ��ѯ
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopPoll(const s8 *pszConfName);

    //4.0 ֧�ֵ���ǽ��ѯ����
	/*=============================================================================
	�� �� ����StartTwPoll
	��    �ܣ���ʼ����ǽ��ѯ
	��    ����	pszConfName         			[in]	������
				ptMtList						[in]	�ն��б�
                byTvWallIdx                     [in]    ѡ��ComboBox���ĸ�����ǽ  
                byTvWallChannel                 [in]    ѡ���ĸ�ͨ��
				wPollTime						[in]	��ѯ���
				wPollTimes                      [in]    ��ѯ����
	˵    ����
	�� �� ֵ��BOOL32
    -----------------------------------------------------------------------------
    �޸ļ�¼��
    ��		��	�汾	�޸���	�߶���	�޸�����
    2005/12/26	4.0		����			����
	=============================================================================*/
	virtual BOOL32 StartTwPoll(const s8 *pszConfName, const TMtList *ptMtList, 
                               u8  byTvWallIdx, u8 byTvWallChannel,
                               u16 wPollTime,
                               u16 wPollTimes);

	/*=============================================================================
	�� �� ����StopTwPoll
	��    �ܣ�ֹͣ����ǽ��ѯ
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL32
    -----------------------------------------------------------------------------
    �޸ļ�¼��
    ��		��	�汾	�޸���	�߶���	�޸�����
    2005/12/26	4.0		����			����
	=============================================================================*/
    virtual BOOL32 StopTwPoll(const s8 *pszConfName,
                              u8  byTvWallIdx, u8 byTvWallChannel);

	/*=============================================================================
	�� �� ����OpenConfCallDlg
	��    �ܣ��򿪻�������Ի���
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL OpenConfCallDlg(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����SetCaller
	��    �ܣ����õ�����
	��    ����pszMtAlias								[in]	������
	˵    ���������ȴ򿪵����Ի���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SetCaller(const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����SetCallee
	��    �ܣ����ñ�������
	��    ����pszMtAlias								[in]	��������
	˵    ���������ȴ򿪵����Ի���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SetCallee(const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����StartConfCall
	��    �ܣ���ʼ����
	��    ����	pszConfName								[in]	������
				pszCaller								[in]	������
				pszCallee								[in]	��������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartConfCall(const s8 *pszConfName, const s8 *pszCaller, const s8 *pszCallee);

	/*=============================================================================
	�� �� ����StopConfCall
	��    �ܣ�ֹͣ����
	��    ������
	˵    ���������ȴ򿪵����Ի���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopConfCall();

	/*=============================================================================
	�� �� ����ChangeLockMode
	��    �ܣ��ı�����ģʽ
	��    ����	pszConfName						[in]	������
				byLockMode						[in]	CONF_LOCKMODE_NONE
														CONF_LOCKMODE_NEEDPWD
														CONF_LOCKMODE_LOCK
				aszOldPwd						[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeLockMode(const s8 *pszConfName, u8 byLockMode, const s8 *aszOldPwd = NULL);

    /*=============================================================================
	�� �� ����LockSMcu
	��    �ܣ������¼�MCU
	��    ����	pszConfName						[in]	������
                pszMcuName                      [in]    MCU��
				bLock						    [in]	����/����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL LockSMcu(const s8 *pszConfName, const s8 *pszMcuName, BOOL32 bLock);

	/*=============================================================================
	�� �� ����ChangePwd
	��    �ܣ���������
	��    ����	pszConfName							[in]	������
				pszOldPwd							[in]	�ɻ�������
				pszNewPwd							[in]	�»�������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangePwd(const s8 *pszConfName, const s8 *pszOldPwd, const s8 *pszNewPwd);

	/*=============================================================================
	�� �� ����StartDiscuss
	��    �ܣ���ʼ����
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartDiscuss(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����StopDiscuss
	��    �ܣ�ֹͣ����
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopDiscuss(const s8 *pszConfName);

    /*=============================================================================
    �� �� ����MixDelaySet
    ��    �ܣ�������ʱ����
    ��    ����pszConfName							[in]	������
              wDelayTime                            [in]    ��ʱʱ��,ms
    ˵    ����
    �� �� ֵ��BOOL32
    =============================================================================*/
    virtual BOOL32 MixDelaySet(const s8 *pszConfName, u16 wDelayTime);

	/*=============================================================================
	�� �� ����ForceSpeaker
	��    �ܣ�ǿ�Ʒ�����
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ForceSpeaker(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����CancelForceSpeaker
	��    �ܣ�ȡ��ǿ�Ʒ�����
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelForceSpeaker(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����VoiceVac
	��    �ܣ���������
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL VoiceVac(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����CancelVoiceVac
	��    �ܣ�ȡ����������
	��    ����pszConfName							[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelVoiceVac(const s8 *pszConfName);


	/*=============================================================================
	�� �� ����ConfDelay
	��    �ܣ�������ʱ
	��    ����	pszConfName							[in]	������
				wDelayTime							[in]	�ӳ�ʱ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ConfDelay(const s8 *pszConfName, u16 wDelayTime);

	/*=============================================================================
	�� �� ����VoiceVacTime
	��    �ܣ���������ʱ������
	��    ����	pszConfName								[in]	������
				byVacTime								[in]	����ʱ�� 5, 10, 15, 20, 30
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL VoiceVacTime(const s8 *pszConfName, u8 byVacTime);

    /*=============================================================================
	�� �� ����LocalMtQuiet
	��    �ܣ����ñ����ն˾���
	��    ����	pszConfName								[in]	������
				bQuiet								    [in]	����/ȡ��
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 LocalMtQuiet(const s8 *pszConfName, BOOL32 bQuiet);

    /*=============================================================================
	�� �� ����LocalMtMute
	��    �ܣ����ñ����ն�����
	��    ����	pszConfName								[in]	������
				bMute								    [in]	����/ȡ��
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 LocalMtMute(const s8 *pszConfName, BOOL32 bMute);

    /*=============================================================================
	�� �� ����ChangeCallType
	��    �ܣ����ĵ����鿴����
	��    ����byCallType					[in]	0:�����˺ͱ������˺ϳɣ�
                                                    1:�����˷���, ������ѡ����������
                                                    2:�������˷���
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 ChangeCallType(u8 byCallType);

	//-----------------------------------------------------------------------------
	//	5.�������
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����StartRec
	��    �ܣ���ʼ¼��
	��    ����	pszConfName						[in]	������
				tRecCfg							[in]	¼�����
	˵    �����ն���Ϊ�������¼��, �����ն�¼��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartRec(const s8 *pszConfName, const TRecorderCfg tRecCfg);

	/*=============================================================================
	�� �� ����PauseRec
	��    �ܣ���ͣ¼��
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
				pszMtAlias						[in]	ΪNULL��Ϊ�������¼��, �����ն�¼��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL PauseRec(const s8 *pszConfName, const s8 *pszRecName, const s8 *pszMtAlias = NULL);

	/*=============================================================================
	�� �� ����ResumeRec
	��    �ܣ��ָ�¼��
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
				pszMtAlias						[in]	ΪNULL��Ϊ�������¼��, �����ն�¼��
	˵    ������������ͣ¼��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ResumeRec(const s8 *pszConfName, const s8 *pszRecName, const s8 *pszMtAlias = NULL);

	/*=============================================================================
	�� �� ����StopRec
	��    �ܣ�ֹͣ¼��
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
				pszMtAlias						[in]	ΪNULL��Ϊ�������¼��, �����ն�¼��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopRec(const s8 *pszConfName, const s8 *pszRecName, const s8 *pszMtAlias = NULL);

	/*=============================================================================
	�� �� ����PublishRecFile
	��    �ܣ�����¼���ļ�
	��    ����	pszRecName						[in]	¼�����
				pszFileName						[in]	¼���ļ���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL PublishRecFile(const s8 *pszRecName, const s8 *pszFileName);

	/*=============================================================================
	�� �� ����CancelPubRecFile
	��    �ܣ�ȡ��¼���ļ�����
	��    ����	pszRecName						[in]	¼�����
				pszFileName						[in]	¼���ļ���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelPubRecFile(const s8 *pszRecName, const s8 *pszFileName);

	/*=============================================================================
	�� �� ����DeleteRecFile
	��    �ܣ�ɾ��¼���ļ�
	��    ����	pszRecName						[in]	¼�����
				pszFileName						[in]	¼���ļ���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DeleteRecFile(const s8 *pszRecName, const s8 *pszFileName);

    /*=============================================================================
	�� �� ����StartPlay
	��    �ܣ���ʼ����
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
                pszFileName                     [in]    �ļ���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 StartPlay(const s8 *pszConfName, const s8 *pszRecName,
                             const s8 *pszFileName);

    /*=============================================================================
	�� �� ����PausePlay
	��    �ܣ���ͣ����
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 PausePlay(const s8 *pszConfName, const s8 *pszRecName);

    /*=============================================================================
	�� �� ����ResumePlay
	��    �ܣ��ָ�����
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 ResumePlay(const s8 *pszConfName, const s8 *pszRecName);

    /*=============================================================================
	�� �� ����StopPlay
	��    �ܣ�ֹͣ����
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 StopPlay(const s8 *pszConfName, const s8 *pszRecName);

    /*=============================================================================
	�� �� ����DragPlay
	��    �ܣ������϶�
	��    ����	pszConfName						[in]	������
				pszRecName						[in]	¼�����
                fProg                           [in]    �϶��ٷ���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 DragPlay(const s8 *pszConfName, const s8 *pszRecName,
                            float fProg);

	/*=============================================================================
	�� �� ����StartVmp
	��    �ܣ���ʼ����ϳ�
	��    ����	pszConfName			[in]	������
				byMtNum				[in]	�μӻ���ϳɵ��ն˸���
				ptVmpMt				[in]	�μӻ���ϳɵ��ն�
				byStyle				[in]	VMP_STYLE_DYNAMIC, VMP_STYLE_ONE,
											VMP_STYLE_VTWO, VMP_STYLE_HTWO,
											VMP_STYLE_THREE, VMP_STYLE_FOUR,
											VMP_STYLE_SIX, VMP_STYLE_EIGHT,
											VMP_STYLE_NINE, VMP_STYLE_TEN,
											VMP_STYLE_THIRTEEN, VMP_STYLE_SIXTEEN,
											VMP_STYLE_SPECFOUR, VMP_STYLE_SEVEN
                bySchemaId          [in]    �ϳɷ���1-5, 0 ������
				bBroad				[in]	�Ƿ�㲥
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartVmp(const s8 *pszConfName, u8 byMtNum, const TVmpMt *ptVmpMt, 
                          u8 byStyle, u8 bySchemaId, 
                          BOOL bBroad = TRUE);

	/*=============================================================================
	�� �� ����ChangeVmpMt
	��    �ܣ��л�����ϳ��ն�
	��    ����	pszConfName				[in]	������
				pszMtAlias				[in]	�ն˱���, ΪNULL��Ϊ����ֹͣ��ͨ���Ļ���ϳ�
				byChannel				[in]	which channel to replace
				byStyle					[in]	VMP_STYLE_DYNAMIC, VMP_STYLE_ONE,
												VMP_STYLE_VTWO, VMP_STYLE_HTWO,
												VMP_STYLE_THREE, VMP_STYLE_FOUR,
												VMP_STYLE_SIX, VMP_STYLE_EIGHT,
												VMP_STYLE_NINE, VMP_STYLE_TEN,
												VMP_STYLE_THIRTEEN, VMP_STYLE_SIXTEEN,
												VMP_STYLE_SPECFOUR, VMP_STYLE_SEVEN
                bySchemaId              [in]    �ϳɷ���1-5, 0 ������
				bBroad					[in]	�Ƿ�㲥
				byMemberType			[in]	���淽ʽ
												VMP_MEMBERTYPE_MCSSPEC
												VMP_MEMBERTYPE_SPEAKER
												VMP_MEMBERTYPE_CHAIRMAN
												VMP_MEMBERTYPE_POLL
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeVmpMt(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel, 
                             u8 byStyle, u8 bySchemaId, 
                             BOOL bBroad = TRUE, u8 byMemberType = VMP_MEMBERTYPE_MCSSPEC);

	/*=============================================================================
	�� �� ����StopVmp
	��    �ܣ�ֹͣ����ϳ�
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopVmp(const s8 *pszConfName);

	/*=============================================================================
	�� �� ����StartTvWall
	��    �ܣ���ʼ����ǽ
	��    ����	pszConfName				[in]	������
				ptMtList				[in]	���е���ǽ���ն��б�
				byTvNum					[in]	ѡ����һ������ǽ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartTvWall(const s8 *pszConfName, const TMtList *ptMtList, u8 byTvNum);

	/*=============================================================================
	�� �� ����ChangeTvWallMt
	��    �ܣ��л�����ǽ�ն�
	��    ����	pszConfName			    [in]	������
				pszMtAlias				[in]	�ն˱���, ΪNULL��Ϊ����ֹͣ��ͨ���ĵ���ǽ
				byTvNum					[in]	which tvwall to switch
				byChannel				[in]	which channel to replace
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeTvWallMt(const s8 *pszConfName, const s8 *pszMtAlias, u8 byTvNum, u8 byChannel);

    /*=============================================================================
	�� �� ����ChangeTvWallMt
	��    �ܣ��л�����ǽ���淽ʽ
	��    ����	pszConfName			    [in]	������
                byMemberType            [in]    ���淽ʽ
				byTvNum					[in]	which tvwall to switch
				byChannel				[in]	which channel to replace
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 ChangeTvWallMt(const s8 *pszConfName, u8 byTvNum,
                                  u8 byChannel, u8 byMemberType);

	/*=============================================================================
	�� �� ����StopTvWall
	��    �ܣ�ֹͣ����ǽ
	��    ����	pszConfName				[in]	������
				byTvNum					[in]	ֹͣ��һ������ǽ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopTvWall(const s8 *pszConfName, u8 byTvNum);

    // 4.0 ���Ӷ໭�����ǽ���� 2005.10.24
	/*=============================================================================
	�� �� ����StartVmpTw
	��    �ܣ���ʼ�໭�����ǽ
	��    ����	pszConfName			[in]	������
				byMtNum				[in]	�μӻ���ϳɵ��ն˸���
				ptVmpTwMt			[in]	�μӻ���ϳɵ��ն�
				byStyle				[in]	VMP_STYLE_ONE,
											VMP_STYLE_VTWO, VMP_STYLE_HTWO,
											VMP_STYLE_THREE, VMP_STYLE_FOUR,
											VMP_STYLE_SIX, VMP_STYLE_EIGHT,
											VMP_STYLE_NINE, VMP_STYLE_TEN,
											VMP_STYLE_THIRTEEN, VMP_STYLE_SIXTEEN,
											VMP_STYLE_SPECFOUR, VMP_STYLE_SEVEN
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
	virtual BOOL32 StartVmpTw(const s8 *pszConfName, u8 byMtNum, const TVmpMt *ptVmpTwMt, 
                            u8 byStyle);

	/*=============================================================================
	�� �� ����ChangeVmpTwMt
	��    �ܣ��л��໭�����ǽ�ն�
	��    ����	pszConfName				[in]	������
				pszMtAlias				[in]	�ն˱���, ΪNULL��Ϊ����ֹͣ��ͨ���Ļ���ϳ�
				byChannel				[in]	Ҫ�滻��ͨ��
				byStyle					[in]	VMP_STYLE_ONE,
												VMP_STYLE_VTWO, VMP_STYLE_HTWO,
												VMP_STYLE_THREE, VMP_STYLE_FOUR,
												VMP_STYLE_SIX, VMP_STYLE_EIGHT,
												VMP_STYLE_NINE, VMP_STYLE_TEN,
												VMP_STYLE_THIRTEEN, VMP_STYLE_SIXTEEN,
												VMP_STYLE_SPECFOUR, VMP_STYLE_SEVEN
				byMemberType			[in]	���淽ʽ
												VMP_MEMBERTYPE_MCSSPEC
												VMP_MEMBERTYPE_SPEAKER
												VMP_MEMBERTYPE_CHAIRMAN
												VMP_MEMBERTYPE_POLL
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
	virtual BOOL32 ChangeVmpTwMt(const s8 *pszConfName, const s8 *pszMtAlias, 
                                 u8 byChannel, u8 byStyle, 
                                 u8 byMemberType = VMP_MEMBERTYPE_MCSSPEC);

	/*=============================================================================
	�� �� ����StopVmpTw
	��    �ܣ�ֹͣ�໭�����ǽ
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
	virtual BOOL32 StopVmpTw(const s8 *pszConfName);
    

	/*=============================================================================
	�� �� ����StartMix
	��    �ܣ���ʼ����
	��    ����	pszConfName				[in]	������
				ptMtList				[in]	���л������ն��б�
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartMix(const s8 *pszConfName, const TMtList *ptMtList);

	/*=============================================================================
	�� �� ����ChangeMixMt
	��    �ܣ��л������ն�
	��    ����	pszConfName					[in]	������
				pszMtAlias					[in]	�ն˱���, ΪNULL��Ϊ����ֹͣ��ͨ���Ļ���
				byChannel					[in]	which channel to replace
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeMixMt(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel);

	/*=============================================================================
	�� �� ����StopMix
	��    �ܣ�ֹͣ����
	��    ����pszConfName			[in]	������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopMix(const s8 *pszConfName);

	//-----------------------------------------------------------------------------
	//	6.���
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����StartMonitor
	��    �ܣ���ʼ�ն˼��
	��    ����	pszConfName			[in]	������
				ptMtList			[in]	��Ҫ��ص��ն��б�
				byMonitorPos		[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ������һ��ͨ�������϶�
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StartMonitor(const s8 *pszConfName, const TMtList * ptMtList, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����ChangeMonitorMt
	��    �ܣ��л�����ն�
	��    ����	pszConfName				[in]	������
				pszMtAlias				[in]	�ն˱���
				byChannel				[in]	which channel to replace
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeMonitorMt(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����RealMonitor
	��    �ܣ�ʵʱ���
	��    ����	byChannel				[in]	ʵʱ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL RealMonitor(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����CancelRealMonitor
	��    �ܣ�ȡ��ʵʱ����ն�
	��    ����	byChannel				[in]	ʵʱ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelRealMonitor(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����QuietMonitor
	��    �ܣ���ؾ���
	��    ����	byChannel				[in]	��ؾ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL QuietMonitor(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����CancelQuietMonitor
	��    �ܣ�ȡ����ؾ���
	��    ����	byChannel				[in]	��ؾ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CancelQuietMonitor(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����MonitorInfo
	��    �ܣ������Ϣ
	��    ����	byChannel				[in]	��ؾ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
				pszVideoSrc				[out]	��ƵԴ
				pszAudioSrc				[out]	��ƵԴ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MonitorInfo(u8 byChannel, u8 byMonitorPos, s8 *pszVideoSrc, s8 *pszAudioSrc);

	/*=============================================================================
	�� �� ����FullScreenMonitor
	��    �ܣ�ȫ�����
	��    ����	byChannel				[in]	��ؾ���ͨ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����ȫ�����2����Զ��л�ԭʼ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL FullScreenMonitor(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����SaveMonitorPic
	��    �ܣ�������ͼƬ
	��    ����	byChannel				[in]	��ؾ���ͨ��
				pszPicFullName			[in]	ͼƬ����λ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SaveMonitorPic(u8 byChannel, const s8 *pszPicFullName, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����MonitorCameraCtrl
	��    �ܣ���ش�������ͷң��
	��    ����	byChannel				[in]	��ؾ���ͨ��
				pszPicFullName			[in]	ͼƬ����λ��
				byMonitorPos			[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    �������򿪴���Ȼ��ر�, ��������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MonitorCameraCtrl(u8 byChannel, u8 byMonitorPos);

	/*=============================================================================
	�� �� ����StopMonitor
	��    �ܣ�ֹͣ�ն˼��
	��    ����	byChannel			[in]	ֹͣ��صĿؼ�λ��
				byMonitorPos		[in]	���λ�� 0:ģ��᳡ 1:��ش���
	˵    ����ֹֻͣһ�������ж��, ��Ҫ��ε��øú���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopMonitor(u8 byChannel, u8 byMonitorPos);

	//-----------------------------------------------------------------------------
	//	7.�ն˲���
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����MtInspect
	��    �ܣ��ն�ѡ��
	��    ����	pszConfName						[in]	������
				pszSrcMt						[in]	Դ�ն�
				pszDesMt						[in]	Ŀ���ն�
				byInspectType					[in]	ѡ������
				byOperationType					[in]	0:����ѡ������ 1:����ѡ��
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtInspect(const s8 *pszConfName, const s8 *pszSrcMt, const s8 *pszDesMt,
							u8 byInspectType = MODE_BOTH, u8 byOperationType = 1);

	/*=============================================================================
	�� �� ����StopInspect
	��    �ܣ�ֹͣ�ն�ѡ��
	��    ����	pszConfName							[in]	������
				pszInspectMt						[in]	ѡ���ն�
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL StopInspect(const s8 *pszConfName, const s8 *pszInspectMt);

	/*=============================================================================
	�� �� ����MtSendBitrate
	��    �ܣ��޸��ն˷�������
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				wBitrate								[in]	��������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtSendBitrate(const s8 *pszConfName, const s8 *pszMtAlias, u16 wBitrate);

	/*=============================================================================
	�� �� ����MtQuiet
	��    �ܣ��ն˾���
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				byType									[in]	0:�����ť����
																1:���ն��ϵ����˵�ѡ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtQuiet(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����MtCancelQuiet
	��    �ܣ�ȡ���ն˾���
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				byType									[in]	0:�����ť����
																1:���ն��ϵ����˵�ѡ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtCancelQuiet(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����MtMute
	��    �ܣ��ն�����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				byType									[in]	0:�����ť����
																1:���ն��ϵ����˵�ѡ������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtMute(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����MtCancelMute
	��    �ܣ�ȡ���ն�����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				byType									[in]	0:�����ť����
																1:���ն��ϵ����˵�ѡ������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL MtCancelMute(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType = 0);

	/*=============================================================================
	�� �� ����UpdateAlias
	��    �ܣ�ˢ�±���
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL UpdateAlias(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����SaveToAddr
	��    �ܣ������ն˵���ַ��
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SaveToAddr(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����ChangeCallMode
	��    �ܣ��ı���з�ʽ
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				byCallMode						[in]	CONF_CALLMODE_NONE,
														CONF_CALLMODE_ONCE,
														CONF_CALLMODE_TIMER
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeCallMode(const s8 *pszConfName, const s8 *pszMtAlias, u8 byCallMode);

	/*=============================================================================
	�� �� ����ChangeVideoSrc
	��    �ܣ��л���ƵԴ
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
				byChannel								[in]	ͨ��0: S����
																1: ��ƵԴ1
																2: ��ƵԴ2
																3: ��ƵԴ3
																4: ��ƵԴ4
																5: ��ƵԴ5
																6: ��ƵԴ6
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeVideoSrc(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel);

    /*=============================================================================
	�� �� ����ChangeVideoSrc
	��    �ܣ��л���ƵԴ
	��    ����	pszConfName								[in]	������
				nMtNum								    [in]	�ն˸���
				ptVideoSrc								[in]	��ƵԴ�ṹ
                bSave                                   [in]    �Ƿ񱣴淽��
                pszScheName                             [in]    ������
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 ChangeVideoSrc(const s8 *pszConfName, s32 nMtNum,
                                const TVideoSrc *ptVideoSrc, BOOL32 bSave = FALSE,
                                const s8 *pszScheName = NULL);

    /*=============================================================================
	�� �� ����LoadVideoSrcSche
	��    �ܣ���ȡ��ƵԴ�����л���ƵԴ
	��    ����	pszConfName								[in]	������
                pszScheName                             [in]    ������
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 LoadVideosrcSche(const s8 *pszConfName, const s8 *pszScheName);

    /*=============================================================================
	�� �� ����DeleteVideoSrcSche
	��    �ܣ�ɾ����ƵԴ����
	��    ����	pszConfName								[in]	������
                pszScheName                             [in]    ������
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 DeleteVideoSrcSche(const s8 *pszConfName, const s8 *pszScheName);

	/*=============================================================================
	�� �� ����ChangeMatrix
	��    �ܣ����¾���
	��    ����	pszConfName							[in]	������
				pszMtAlias							[in]	�ն���
				nSrcPort							[in]	Դ�˿�
				nDesPort							[in]	Ŀ�Ķ˿�
				byMode								[in]	0: ��Ƶ, 1: ��Ƶ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ChangeMatrix(const s8 *pszConfName, const s8 *pszMtAlias, s32 nSrcPort, s32 nDesPort, u8 byMode = 0);

	/*=============================================================================
	�� �� ����SaveMatrix
	��    �ܣ��������
	��    ����	pszConfName							[in]	������
				pszMtAlias							[in]	�ն���
				nMatrixNo							[in]	���󷽰����
				pszMatrixName						[in]	������
				byMode								[in]	0: ��Ƶ, 1: ��Ƶ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SaveMatrix(const s8 *pszConfName, const s8 *pszMtAlias, s32 nMatrixNo, const s8 *pszMatrixName, u8 byMode);

	/*=============================================================================
	�� �� ����SetMatrixPortIcon
	��    �ܣ����ľ���˿�ͼ��
	��    ����	pszConfName							[in]	������
				pszMtAlias							[in]	�ն���
				nPort								[in]	�˿�
				byMode								[in]	0: ��Ƶ����, 1: ��Ƶ����, 2: ��Ƶ���, 3: ��Ƶ���
				nIcon								[in]	ͼ���
				pszPortName							[in]	�˿�����, NULL��ʹ��Ĭ������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL SetMatrixPortIcon(const s8 *pszConfName, const s8 *pszMtAlias, s32 nPort,
									u8 byMode, s32 nIcon = 0, const s8 *pszPortName = NULL);

    /*=============================================================================
	�� �� ����RefreshMcu
	��    �ܣ�ˢ��MCU
	��    ����	pszConfName							[in]	������
				pszMcuAlias							[in]	MCU��
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL RefreshMcu(const s8 *pszConfName, const s8 *pszMcuAlias);

    //-----------------------------------------------------------------------------
	//	8.����ͷ����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����CameraUp
	��    �ܣ�����ͷ����
	��    ����	pszConfName							[in]	������
				pszMtAlias							[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraUp(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����CameraDown
	��    �ܣ�����ͷ����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraDown(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����CameraLeft
	��    �ܣ�����ͷ����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraLeft(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����CameraRight
	��    �ܣ�����ͷ����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraRight(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����CameraAutoFocus
	��    �ܣ�����ͷ�Զ�����
	��    ����	pszConfName								[in]	������
				pszMtAlias								[in]	�ն���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraAutoFocus(const s8 *pszConfName, const s8 *pszMtAlias);

	/*=============================================================================
	�� �� ����CameraFocus
	��    �ܣ�����ͷ����
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				bIncrease						[in]	TRUE: increase, FALSE decrease
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraFocus(const s8 *pszConfName, const s8 *pszMtAlias, BOOL bIncrease);

	/*=============================================================================
	�� �� ����CameraZoom
	��    �ܣ�����ͷ����Ұ
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				bIncrease						[in]	TRUE: increase, FALSE decrease
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraZoom(const s8 *pszConfName, const s8 *pszMtAlias, BOOL bIncrease);

	/*=============================================================================
	�� �� ����CameraBright
	��    �ܣ�����ͷ������
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				bIncrease						[in]	TRUE: increase, FALSE decrease
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraBright(const s8 *pszConfName, const s8 *pszMtAlias, BOOL bIncrease);

	/*=============================================================================
	�� �� ����CameraSavePos
	��    �ܣ�����ͷλ�ñ���
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				byChannel						[in]	which position to save the file
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraSavePos(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel);

	/*=============================================================================
	�� �� ����CameraLoadPos
	��    �ܣ�����ͷ��ȡԤ��λ��
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				byChannel						[in]	which position to load the file
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL CameraLoadPos(const s8 *pszConfName, const s8 *pszMtAlias, u8 byChannel);

	//-----------------------------------------------------------------------------
	//	9.�û�����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����AddUser
	��    �ܣ�����û�
	��    ����	pszUserName						[in]	�û���
				pszPwd							[in]	����
				pszFullName						[in]	�û�ȫ��
				byUserType						[in]	�û����� UM_ADMIN, UM_OPERATOR
				pszDescription					[in]	�û�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL AddUser(const s8 *pszUserName, const s8 *pszPwd, const s8 *pszFullName,
						u8 byUserType = UM_ADMIN, const s8 *pszDescription = NULL);

	/*=============================================================================
	�� �� ����ModifyUser
	��    �ܣ��޸��û�
	��    ����	pszUserName						[in]	�û���
				pszPwd							[in]	�޸�����
				pszFullName						[in]	�޸��û�ȫ��
				byUserType						[in]	�޸��û����� UM_ADMIN, UM_OPERATOR
				pszDescription					[in]	�޸��û�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ModifyUser(const s8 *pszUserName, const s8 *pszPwd, const s8 *pszFullName,
							u8 byUserType = UM_ADMIN, const s8 *pszDescription = NULL);

	/*=============================================================================
	�� �� ����DelUser
	��    �ܣ�ɾ���û�
	��    ����pszUserName						[in]	�û���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DelUser(const s8 *pszUserName);

	/*=============================================================================
	�� �� ����EmptyUser
	��    �ܣ�ɾ����Admin֮�������û�
	��    ������
	˵    ����
	�� �� ֵ����
	=============================================================================*/
	virtual void EmptyUser();

	//-----------------------------------------------------------------------------
	//	10.��ַ������
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����AddMtToAddrbook
	��    �ܣ����ӵ�ַ���ն�
	��    ����ptAddrEntryInfo						[in]	�����ն���Ϣ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL AddMtToAddrbook(const TADDRENTRYINFO *ptAddrEntryInfo);

	/*=============================================================================
	�� �� ����DelMtInAddrbook
	��    �ܣ��ӵ�ַ��ɾ���ն�
	��    ����ptAddrEntryInfo						[in]	ɾ���ն�
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DelMtInAddrbook(const TADDRENTRYINFO *ptAddrEntryInfo);

	/*=============================================================================
	�� �� ����ModifyMtInAddrbook
	��    �ܣ��޸ĵ�ַ���ն�
	��    ����	ptSrcInfo							[in]	�ն�ԭʼ��Ϣ
				ptModifyInfo						[in]	�޸���Ϣ
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL ModifyMtInAddrbook(const TADDRENTRYINFO *ptSrcInfo,
                                const TADDRENTRYINFO *ptModifyInfo);

	/*=============================================================================
	�� �� ����AddGroup
	��    �ܣ���ӻ�����
	��    ����	ptAddrGroup						[in]	��������Ϣ
				ptEntryTable					[in]	��Ҫ������������Ŀ
				nEntryNum						[in]	��Ŀ����
	˵    ����	1. ptEntryTable == NULL �� nEntryNum == 0, ��������������Ŀ��
				2. ��Ŀ�����Ѵ����ڵ�ַ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL AddGroup(const TMULTISETENTRYINFO *ptAddrGroup, const TADDRENTRYINFO *ptEntryTable = NULL, s32 nEntryNum = 0);

	/*=============================================================================
	�� �� ����DelGroup
	��    �ܣ�ɾ��������
	��    ����pszGroupName						[in]	����������
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL DelGroup(const s8 *pszGroupName);

	/*=============================================================================
	�� �� ����ModifyGroup
	��    �ܣ��޸Ļ�����
	��    ����	pszGroupName					[in]	��Ҫ�޸ĵĻ���������
				ptAddrGroup						[in]	�޸�����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL ModifyGroup(const s8 *pszGroupName, const TMULTISETENTRYINFO *ptAddrGroup);

	/*=============================================================================
	�� �� ����GroupAddEntry
	��    �ܣ�������������Ŀ
	��    ����	pszGroupName					[in]	����������
				ptEntryTable					[in]	��Ҫ������������Ŀ
				nEntryNum						[in]	��Ŀ����
	˵    ������Ŀ�����Ѵ����ڵ�ַ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GroupAddEntry(const s8 *pszGroupName, const TADDRENTRYINFO *ptEntryTable, s32 nEntryNum);

	/*=============================================================================
	�� �� ����GroupDelEntry
	��    �ܣ��ӻ�������ɾ����Ŀ
	��    ����	pszGroupName					[in]	����������
				ptEntryTable					[in]	��Ҫɾ�����������Ŀ
				nEntryNum						[in]	��Ŀ����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GroupDelEntry(const s8 *pszGroupName, const TADDRENTRYINFO *ptEntryTable, s32 nEntryNum);

	/*=============================================================================
	�� �� ����EmptyAddrEntry
	��    �ܣ�ɾ�����е�ַ����Ŀ
	��    ������
	˵    ����
	�� �� ֵ����
	=============================================================================*/
	virtual void EmptyAddrEntry();

	/*=============================================================================
	�� �� ����EmptyAddrGroup
	��    �ܣ�ɾ�����л�����
	��    ������
	˵    ����
	�� �� ֵ����
	=============================================================================*/
	virtual void EmptyAddrGroup();


    //-----------------------------------------------------------------------------
	//	11.MCU���ò���
	//-----------------------------------------------------------------------------

    /*============================================================================
    �� �� ����McuWizardCfg
    ��    �ܣ�Mcu����������
    ��    ����ptMcuWizardCfg       			[in]	��������ò���
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuWizardCfg (const tagMcuWizardSetting *ptMcuWizardSetting);    

    /*============================================================================
    �� �� ����McuExportConfig
    ��    �ܣ�����Mcu����
    ��    ����pszFilename  					[in]	�����Ŀ���ļ���
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuExportConfig (const s8 * pszFilename);

    /*============================================================================
    �� �� ����McuImportConfig
    ��    �ܣ�����Mcu����
    ��    ����pszFilename  					[in]	�����ļ���
    ˵    ����
    �� �� ֵ��BOOL
    ============================================================================*/
    virtual BOOL32 McuImportConfig (const s8 * pszFilename);


    /*============================================================================
    �� �� ����RefreshMcuStatus
    ��    �ܣ�ˢ��Mcu��Ϣ
    ��    ������
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 RefreshMcuStatus ();

    /*============================================================================
    �� �� ����SynMcuTime
    ��    �ܣ�ͬ��Mcuʱ��ɱ���ʱ��
    ��    ������
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 SynMcuTime ();

    /*============================================================================
    �� �� ����RebootMcu
    ��    �ܣ�����Mcu
    ��    ����bConfirm                      [in] �Ƿ���Ҫ����,TRUE ��ʾȷ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 RebootMcu (BOOL bConfirm = TRUE);


    /*============================================================================
    �� �� ����McuNetworkSet
    ��    �ܣ����� Mcu �������ã�������
    ��    ����ptNetworkSetting       			[in]	�������õĲ���
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuNetworkSet (const tagMcuNetworkSetting *ptNetworkSetting);


    /*============================================================================
    �� �� ����AddMcuSnmp
    ��    �ܣ����SNMP������
    ��    ����ptSnmpSetting 				[in]	SNMP ����������
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 AddMcuSnmp (const tagMcuSnmpSetting *ptSnmpSetting);

    /*============================================================================
    �� �� ����DelMcuSnmp
    ��    �ܣ�ɾ��SNMP������
    ��    ����dwIP       					[in]	SNMP �� IP ��ַ
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 DelMcuSnmp (u32 dwIP);

    /*============================================================================
    �� �� ����EditMcuSnmp
    ��    �ܣ��༭SNMP������
    ��    ����dwOldIP     					[in]	Ҫ�༭��SNMP �� IP
              ptSnmpSetting					[in]	�µ�SNMP ��������Ϣ
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 EditMcuSnmp (u32 dwOldIP, const tagMcuSnmpSetting *ptSnmpSetting);
    

    /*============================================================================
    �� �� ����McuDeviceQos
    ��    �ܣ�����QoS����
    ��    ����tagMcuQosSetting              [in]    QoS����

    ˵    �����ȼ���ֵ���չ����Ҫ��ķ�Χ��д
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuDeviceQos (const tagMcuQosSetting *ptQosSetting);

    /*============================================================================
    �� �� ����McuNetMisc
    ��    �ܣ�Mcu������������
    ��    ����tagMcuNetMiscSetting              [in]    Mcu�����������ò���

    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuNetMisc (const tagMcuNetMiscSetting *ptNetMiscSetting);


    /*============================================================================
    �� �� ����McuVmpConfig
    ��    �ܣ����û���ϳ�
    ��    ����ptVmpCfg              [in]    ����ϳ����ò���
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuVmpConfig (const TVmpStyleCfg* ptVmpCfg);


    /*============================================================================
    �� �� ����McuChipAdd
    ��    �ܣ���������-����
    ��    ����ptMcuChipCfg                  [in]    ���ӵĵ������
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipAdd (const TMcuChipCfg* ptMcuChipCfg);

    /*============================================================================
    �� �� ����McuChipModuleEdit
    ��    �ܣ���������-����ģ��
    ��    ����byLayer                       [in]    Ҫ���õİ����ڲ�� 
              bySlot                        [in]    Ҫ���õİ����ڲۺ�
              ptModuleCfg                   [in]    �µ�ģ�����
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipModuleAdd (u8 byLayer, u8 bySlot,
                                     const TMcuChipModuleCfg *ptModuleCfg);

    /*============================================================================
    �� �� ����McuRecAdd
    ��    �ܣ�¼�������
    ��    ����ptRecCfg                       [in]    ���ӵ�¼�������
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuRecAdd (const TMcuChipModuleCfg* ptRecCfg);

    /*============================================================================
    �� �� ����McuChipDel
    ��    �ܣ���������-ɾ��
    ��    ����byLayer                       [in]    Ҫɾ���İ����ڲ�� 
              bySlot                        [in]    Ҫɾ���İ����ڲۺ�
              bConfirm                      [in]    TRUE��ʾȷ��ɾ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipDel (u8 byLayer, u8 bySlot, BOOL32 bConfirm = TRUE);

    /*============================================================================
    �� �� ����McuChipModuleDel
    ��    �ܣ���������-ɾ��ģ��
    ��    ����byLayer                       [in]    Ҫɾ����ģ�����ڵ�������ڲ�� 
              bySlot                        [in]    Ҫɾ����ģ�����ڵ������ڲۺ�
              cstrOldName                   [in]    ��ģ��ı���
              bConfirm                      [in]    TRUE��ʾȷ��ɾ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipModuleDel (u8 byLayer, u8 bySlot, CString cstrOldName,
                                     BOOL32 bConfirm = TRUE);

    /*============================================================================
    �� �� ����McuRecDel
    ��    �ܣ���������-ɾ��¼���
    ��    ����dwIp                          [in]    ¼�����IP��ַ
              bConfirm                      [in]    TRUE��ʾȷ��ɾ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuRecDel (u32 dwIp, BOOL32 bConfirm = TRUE);

    /*============================================================================
    �� �� ����McuChipEdit
    ��    �ܣ���������-�޸�
    ��    ����ptMcuChipCfg                  [in]    �µĵ������
    ˵    ��������Ĳ�ۺŲ����޸ģ��������Ͳ����޸ģ�
              ģ�鲻�����޸�(��س�ԱtModuleCfg����Ҫ��ֵ)��
              ¼������ܴ˷����޸ģ�
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipEdit (const TMcuChipCfg *ptMcuChipCfg);

    /*============================================================================
    �� �� ����McuChipReboot
    ��    �ܣ���������-����
    ��    ����ptMcuChipCfg                  [in]    �������,ֻ��Ҫ��д��źͲۺ�
              bConfirm                      [in]    �Ƿ�ȷ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipReboot (const TMcuChipCfg *ptMcuChipCfg, BOOL32 bConfirm = TRUE);

    /*============================================================================
    �� �� ����McuChipModuleEdit
    ��    �ܣ���������-�޸�ģ��
    ��    ����byLayer                       [in]    Ҫ���õİ����ڲ�� 
              bySlot                        [in]    Ҫ���õİ����ڲۺ�
              cstrOldName                   [in]    ��ģ��ԭ���ı���
              ptModuleCfg                   [in]    �µ�ģ�����
    ˵    ����ģ�����Ͳ����޸ģ�¼��������ô˷����޸�
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuChipModuleEdit (u8 byLayer, u8 bySlot, CString cstrOldName, 
                                      const TMcuChipModuleCfg *ptModuleCfg);

    /*============================================================================
    �� �� ����McuRecEdit
    ��    �ܣ���������-�޸�¼���ģ��
    ��    ����dwIp                          [in]    Ҫ����¼���ԭ����IP
              ptModuleCfg                   [in]    �µ�¼�������
    ˵    ����¼����ô˷����޸�
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuRecEdit (u32 dwIp, const TMcuChipModuleCfg *ptModuleCfg);

    /*============================================================================
    �� �� ����McuSaveAllCfg
    ��    �ܣ���������MCU����
    ��    ����bConfirm                      [in]    �Ƿ�ȷ����TRUE��ʾȷ��
    ˵    ����
    �� �� ֵ��BOOL32
    ============================================================================*/
    virtual BOOL32 McuSaveAllCfg (BOOL32 bConfirm = TRUE);
    
    //-----------------------------------------------------------------------------
	//	12.�û����ò���
	//-----------------------------------------------------------------------------


    /*=============================================================================
	�� �� ����SetCallingType
	��    �ܣ����õ���ѡ������
	��    ����byType                        [in]    0:�������뱻�����˻���ϳ�
                                                    1:�����˿���������, ������������
                                                    2:�������˿�������, ��������������
	�� �� ֵ��BOOL32
	=============================================================================*/
    virtual BOOL32 SetCallingType(u8 byType);


    /*=============================================================================
	�� �� ����SetLanguage
	��    �ܣ���������
	��    ����byIndex                       [in]    LANG_CHS, LANG_EN
	�� �� ֵ��BOOL32
	=============================================================================*/
    virtual BOOL32 SetLanguage(u8 byIndex);

    /*=============================================================================
	�� �� ����DisablePersonMenu
	��    �ܣ�ȡ���û��Զ���˵���һ���ڲ���ģ��᳡����ǰ��������ã�
              ����ᵼ�²˵�ѡ����Ϊ�û��Զ����ʧ��
	��    ������
	�� �� ֵ��BOOL32
	=============================================================================*/
    virtual BOOL32 DisablePersonMenu();

    //-----------------------------------------------------------------------------
	//	13.�ն���ƵԴ��ѯ����
	//-----------------------------------------------------------------------------

    /*=============================================================================
	�� �� ����StartVideoSrcPoll
	��    �ܣ���ʼ��ƵԴ��ѯ
	��    ����pszConfName                       [in]    ������
              nMtNum                            [in]    �ն˸���
              ptVideoSrcPoll                    [in]    �ն���Ϣ
              bSaveToScheme                     [in]    �Ƿ񱣴�Ϊ����
              pszSchemeName                     [in]    ������
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 StartVideoSrcPoll(const s8 *pszConfName, s32 nMtNum,
                                     TVideoSrcPoll *ptVideoSrcPoll,
                                     BOOL32 bSaveToScheme = FALSE,
                                     const s8 *pszSchemeName = NULL);

    /*=============================================================================
	�� �� ����StartVideoSrcPoll
	��    �ܣ���ʼ��ƵԴ��ѯ
	��    ����pszConfName                       [in]    ������
              pszSchemeName                     [in]    ������
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 StartVideoSrcPoll(const s8 *pszConfName,
                                     const s8 *pszSchemeName);

    /*=============================================================================
	�� �� ����DeleteVideoSrcPollScheme
	��    �ܣ�ɾ����ƵԴ��ѯ����
	��    ����pszSchemeName                     [in]    ������
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 DeleteVideoSrcPollScheme(const s8 *pszSchemeName);

    /*=============================================================================
	�� �� ����PauseVideoSrcPoll
	��    �ܣ���ͣ��ƵԴ��ѯ
	��    ����pszMtAlias                        [in]    �ն���, Ϊ������ͣ������ѯ
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 PauseVideoSrcPoll(const s8 *pszMtAlias = NULL);

    /*=============================================================================
	�� �� ����ResumeVideoSrcPoll
	��    �ܣ��ָ���ƵԴ��ѯ
	��    ����pszMtAlias                        [in]    �ն���, Ϊ����ָ�������ѯ
    ˵    �����ú��������˳���ѯ����
              ��������ͣ��ѯ
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 ResumeVideoSrcPoll(const s8 *pszMtAlias = NULL);

    /*=============================================================================
	�� �� ����StopVideoSrcPoll
	��    �ܣ�ֹͣ��ƵԴ��ѯ
	��    ����pszMtAlias                        [in]    �ն���, Ϊ����ֹͣ������ѯ
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 StopVideoSrcPoll(const s8 *pszMtAlias = NULL);

    /*=============================================================================
	�� �� ����RestartVideoSrcPoll
	��    �ܣ����¿�ʼ��ƵԴ��ѯ
	��    ����pszMtAlias                        [in]    �ն���, Ϊ�������¿�ʼ������ѯ
    ˵    �����ú��������˳���ѯ����
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 RestartVideoSrcPoll(const s8 *pszMtAlias = NULL);

    /*=============================================================================
	�� �� ����QuitVideoSrcPollDlg
	��    �ܣ��˳���ƵԴ��ѯ����
	��    ������
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 QuitVideoSrcPollDlg();

public:
	//-----------------------------------------------------------------------------
	//	��ѯ
	//-----------------------------------------------------------------------------


	/*=============================================================================
	�� �� ����GetUserName
	��    �ܣ���ѯ�û��б�ĳһ����û���
	��    ����	nItemCount							[in]	�����
				aszUserName							[out]	�û���
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GetUserName(s32 nItemCount, s8 aszUserName[32]);


    /*=============================================================================
	�� �� ����GetConfIDByName
	��    �ܣ���ѯ����Id
	��    ����  pszConfName                         [in]   Ҫ��ѯ������
	            cConfId                             [out]  ����Id 
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GetConfIDByName(const s8 *pszConfName, CConfId &cConfId);

protected:
	//-----------------------------------------------------------------------------
	//	�ڲ�����
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//	1.��װCGuiUnit����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ���� MoveBtnClick
	��    �ܣ� ģ������ƶ�����ť�ϵ��� 
	��    ���� HWND hWnd					[in] ��ť���
	�� �� ֵ�� void
	=============================================================================*/
	void MoveBtnClick(HWND hWnd);

	/*=============================================================================
	�� �� ���� MoveTextInput
	��    �ܣ� ģ������ƶ���Edit�ؼ��������ı� 
	��    ����	CString strData				[in] ������ı�
				HWND hWnd					[in] Edit�ؼ����
	�� �� ֵ�� void
	=============================================================================*/
	void MoveTextInput(CString strData, HWND hWnd);	


    /*=============================================================================
	�� �� ����MoveBtnCheck
	��    �ܣ����õ����ʽѡ��/ȡ��ѡ��Checkbox
	��    ����  hCk                            [in]    Checkbox ���
                bCheck                         [in]    �Ƿ�ѡ��
	˵    ����
	�� �� ֵ��void
	=============================================================================*/
    void MoveBtnCheck(HWND hCk, BOOL32 bCheck);

	/*=============================================================================
	�� �� ���� CbEditChange
	��    �ܣ� edit�ؼ����ݷ����仯ʱ������Ϣ֪ͨ(��ΪGuiUnit����û�з��ʹ���Ϣ)
	��    ����	UINT uCtrlId				[in]�ؼ�id
				UINT uMsg					[in]Ҫ���͵���Ϣid
				HWND hCtrl					[in]�ؼ����
				HWND hParent				[in]�ؼ����ڸ����ھ��
	�� �� ֵ��	BOOL
	=============================================================================*/
	BOOL EditChange(UINT uCtrlId, UINT uMsg, HWND hCtrl, HWND hParent);

	/*=============================================================================
	�� �� ���� MoveListCtrlClick
	��    �ܣ� ѡ��listctrl�ؼ��е�ĳһ��
	��    ����	HWND hCtrl					[in]listctrl�ؼ����
				s32  nItem					[in]ѡ����
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL MoveListCtrlClick(HWND hWnd, s32 nItem);

	/*=============================================================================
	�� �� ����ListCtrlSelect
	��    �ܣ���ListCtrl��ѡ��ĳһ��
	��    ����	HWND hWnd						[in]	listctrl�ؼ����
				s32  nItem						[in]	ѡ����
	�� �� ֵ����
	=============================================================================*/
	void ListCtrlSelect(HWND hWnd, s32 nItem);

	/*=============================================================================
	�� �� ����SelectMcuChip
	��    �ܣ���Mcu�����б�����ѡ��ĳһ����/��
	��    ����	HWND hTabWnd					[in]	tab�ؼ����
                HWND hListWnd					[in]	listctrl�ؼ����
				u8  byLayer						[in]	���
                u8  bySlot                      [in]    �ۺ�
                u8  byType                      [in]    ������
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 SelectMcuChip(HWND hTabWnd, HWND hListWnd, u8 byLayer, u8 bySlot, u8 byType);

	//-----------------------------------------------------------------------------
	//	2.���鴴������
	//-----------------------------------------------------------------------------


    // ������4.0����
	/*=============================================================================
	�� �� ����CreateNormalConf
	��    �ܣ�������������
	��    ����	ptConfInfo							[in]	���鴴������
				wMtNum								[in]	�ն˸���
				ptAddMtCfg							[in]	�ն˲���
				ptVmpModule							[in]	����ϳɲ���
				ptTvModule							[in]	����ǽ����
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================
	virtual BOOL CreateNormalConf(const TConfInfo *ptConfInfo, u16 wMtNum,
                                  const TAddMtCfg *ptAddMtCfg,
                                  const TVmpModule *ptVmpModule = NULL,
                                  const TTvWallModule *ptTvModule = NULL);         */

	/*=============================================================================
	�� �� ����AddMtWhenCreateConf
	��    �ܣ���ӻ���ʱ���ն��б���д���ն�
	��    ����	ptConfInfo                          [in]    ������Ϣ
                wMtNum								[in]	��ͨ�ն˸���
				ptAddMtCfg							[in]	��ͨ�ն˲���
                wH320MtNum                          [in]	H320�ն˸���
                ptAddH320MtCfg                      [in]	H320�ն˲���
                hCallTypeBtn                        [in]    �������Ͱ�ť
                hMtList                             [in]    �ն��б�
				hAliasEt							[in]	���������
                hAddToAddrCk                        [in]    ��ӵ���ַ��
				hBtnAdd								[in]	��Ӱ�ť
                hBtnAddH320                         [in]    ���H320��ť 
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL AddMtWhenCreateConf(const TConfInfo *ptConfInfo,
                             u16 wMtNum, const TAddMtCfg *ptAddMtCfg,
                             u16 wH320MtNum, const TAddH320MtCfg *ptAddH320MtCfg,
                             HWND hCallTypeBtn,  HWND hMtList, 
                             HWND hAliasEt, HWND hAddToAddrCk,
                             HWND hBtnAdd, HWND hBtnAddH320);

	/*=============================================================================
	�� �� ����SetMediaType
	��    �ܣ�����ý������
	��    ����	hVideo								[in]	��Ƶ���;��
				hAudio								[in]	��Ƶ���;��
				byVideoType							[in]	��Ƶ����
				byAudioType							[in]	��Ƶ����
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL SetMediaType(HWND hVideo, HWND hAudio, u8 byVideoType, u8 byAudioType);

	/*=============================================================================
	�� �� ����SetVideoFormat
	��    �ܣ�������Ƶ��ʽ
	��    ����	hVideo								[in]	��Ƶ��ʽ���
				byVideoFormat						[in]	��Ƶ��ʽ
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL SetVideoFormat(HWND hVideo, u8 byVideoFormat);

    /*=============================================================================
    �� �� ����SelectFrameRate
    ��    �ܣ�������Ƶ����
    ��    ����	hVideoFr							[in]	��Ƶ֡��Combobox���
			    byVideoFr   						[in]	��Ƶ֡��

    ˵    �����ڲ�ʹ��
    �� �� ֵ��BOOL32
    -----------------------------------------------------------------------------
    �޸ļ�¼��
    ��		��	�汾	�޸���	�߶���	�޸�����
    2005/12/27	4.0		����			����
    =============================================================================*/
    BOOL32 SelectFrameRate(HWND hVideoFr, u8 byVideoFr);

	//-----------------------------------------------------------------------------
	//	3.�������
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����ClickConfSettingBtn
	��    �ܣ���� �����趨 ��ť, ���ڵ����˵�����ѡ��
	��    ����	nMenuItem							[in]	ѡ��˵���
				uMenuState							[in]	Ԥ�ڲ˵��Ƿ�CHECK
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL ClickConfSettingBtn(s32 nMenuItem, UINT uMenuState = -1);

	/*=============================================================================
	�� �� ����SetVmpStyle
	��    �ܣ�ѡ����ϳ�ģʽ
	��    ����	hStyleCb						[in]	����ϳ�ģʽ��������
				byStyle							[in]	����ϳ�ģʽ
                bVmpTw                          [in]    TRUE ��ʾ�Ƕ໭�����ǽ
                bMcu8000B                       [in]    TRUE ��ʾ��8000B��MCU
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL SetVmpStyle(HWND hStyleCb, u8 byStyle, BOOL32 bVmpTw = FALSE, 
                     BOOL32 bMcu8000B = FALSE);

	/*=============================================================================
	�� �� ����OpenRecDlg
	��    �ܣ���¼��Ի���
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���, ΪNULL��������¼��
				bChecked						[in]	�˵��Ƿ���Ҫ��CHECK��
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL OpenRecDlg(const s8 *pszConfName, const s8 *pszMtAlias, BOOL bChecked);

	/*=============================================================================
	�� �� ����Spec
	��    �ܣ�ָ�� ��ϯ/������
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն˱���
				byType							[in]	0:���ն��ϵ���Ҽ�ѡ��ָ��;
														1:�϶��ն˵���ϯָ̨��
				nIndex							[in]	�˵���λ��
	˵    ����
	�� �� ֵ����
	=============================================================================*/
	BOOL Spec(const s8 *pszConfName, const s8 *pszMtAlias, u8 byType, s32 nIndex);

	/*=============================================================================
	�� �� ����Cancel
	��    �ܣ�ȡ�� ��ϯ/����
	��    ����	pszConfName						[in]	������
				byType							[in]	0:���ն��ϵ���Ҽ�ѡ��ȡ��;
														1:�ӵ���ϯ̨�϶��ն�ȡ��
				nIndex							[in]	�˵���λ��
	˵    ����
	�� �� ֵ����
	=============================================================================*/
	BOOL Cancel(const s8 *pszConfName, u8 byType, s32 nIndex);

	/*=============================================================================
	�� �� ����AddMtFromAddr
	��    �ܣ��ӵ�ַ�������ն�
	��    ����	ptAddMtCfg							[in]	Ҫ��ӵ��ն�
				nMtNum								[in]	�ն˸���
	˵    ����
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL AddMtFromAddr(const TAddMtCfg *ptMtCfg, s32 nMtNum);

    /*=============================================================================
	�� �� ����SaveScheme
	��    �ܣ����淽��
	��    ����pszSchemeName                         [in]	������
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 SaveScheme(const s8 *pszSchemeName);

    /*=============================================================================
	�� �� ����McuChipModuleCfg
	��    �ܣ�����MCU�����ģ�����ã��ڲ�ʹ��
	��    ����ptModuleCfg                           [in]    ģ�����
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 McuChipModuleCfg(const TMcuChipModuleCfg *ptModuleCfg);
    
    
	//-----------------------------------------------------------------------------
	//	4.������������ʼ��
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����InitSimMonitorHandle
	��    �ܣ���ʼ��ģ��᳡��ز��־��
	��    ����	hLeftBtn						[out]	����ť���
				hRightBtn						[out]	���Ұ�ť���
				ahMonitorStatic					[out]	��ش��ھ��
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL InitSimMonitorHandle(HWND &hLeftBtn, HWND &hRightBtn, HWND ahMonitorStatic[6]);

	/*=============================================================================
	�� �� ����InitMonitroHandle
	��    �ܣ���ʼ����ش��ھ��
	��    ����	hConfCb							[out]	����ѡ�����
				hMtList							[out]	�ն��б���
				ahModeBtn						[out]	ģʽѡ����
				ahMonitorStatic					[out]	��ش��ھ��
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL InitMonitroHandle(HWND &hConfCb, HWND &hMtList, HWND ahModeBtn[6], HWND ahMonitorStatic[9]);

	/*=============================================================================
	�� �� ����InitVmpHandle
	��    �ܣ���ʼ������ϳɴ��ھ��
	��    ����	hStyleCb						[out]	�ϳɷ��ѡ�����
                hSchemdIdCb                     [out]	�ϳɷ���ѡ�����
				hBroadCk						[out]	�Ƿ�㲥��ť���
				hStartBtn						[out]	��ʼ�ϳɰ�ť���
				hStopBtn						[out]	ֹͣ�ϳɾ��
				hCancelBtn						[out]	�˳���ť���
				ahVmpBtn						[out]	�ϳɰ�ť���
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL InitVmpHandle(HWND &hStyleCb, HWND &hSchemdIdCb, 
                       HWND &hBroadCk, HWND &hStartBtn, HWND &hStopBtn, 
                       HWND &hCancelBtn, HWND ahVmpBtn[16]);

	/*=============================================================================
	�� �� ����InitTvWallHandle
	��    �ܣ���ʼ������ǽ���ھ��
	��    ����	hTvWallList						[out]	����ǽ�б���
				hQuitBtn						[out]	�˳���ť���
				ahTvBtn							[out]	����ǽ��ť���
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL InitTvWallHandle(HWND &hTvWallList, HWND &hQuitBtn, HWND ahTvBtn[16]);

	/*=============================================================================
	�� �� ����InitTvWallHandle
	��    �ܣ���ʼ������ǽ���ھ��
	��    ����	hStyleCb						[out]	�������ѡ�����
				hStartBtn						[out]	��ʼ������ť���
				hStopBtn						[out]	ֹͣ������ť���
				hQuitBtn						[out]	�˳���ť���
				ahMixBtn						[out]	������ť���
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL InitMixHandle(HWND &hStyleCb, HWND &hStartBtn, HWND &hStopBtn, HWND &hQuitBtn, HWND ahMixBtn[16]);

	/*=============================================================================
	�� �� ����OpenInitMatrix
	��    �ܣ��򿪲���ʼ�����󴰿ھ��
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				hVideoSchCb						[out]	��Ƶ����ѡ�����
				hVideoSaveBtn					[out]	������Ƶ����ť���
				hAudioSchCb						[out]	��Ƶ����ѡ�����
				hAudioSaveBtn					[out]	������Ƶ����ť���
				ahVideoInBtn					[out]	��Ƶ����˿ھ��
				ahVideoOutBtn					[out]	��Ƶ����˿ھ��
				ahAudioInBtn					[out]	��Ƶ����˿ھ��
				ahAudioOutBtn					[out]	��Ƶ����˿ھ��
				hQuitBtn						[out]	�˳���ť���
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL OpenInitMatrix(const s8 *pszConfName, const s8 *pszMtAlias,
						HWND &hVideoSchCb, HWND &hVideoSaveBtn, HWND &hAudioSchCb,
						HWND &hAudioSaveBtn, HWND ahVideoInBtn[16], HWND ahVideoOutBtn[16],
						HWND ahAudioInBtn[16], HWND ahAudioOutBtn[16], HWND &hQuitBtn);


    /*=============================================================================
	�� �� ����InitVideoSrcHandle
	��    �ܣ���ʼ���л��ն���ƵԴ�˿ھ��
	��    ����	hScheNameCb						[out]	����ѡ����
				hSaveScheBtn					[out]	���淽����ť���
				hDelScheBtn						[out]	ɾ��������ť���
				hPortCb					        [out]	��ƵԴ�˿�ѡ�����
				hConfMtList					    [out]	�����ն��б���
				hVideoMtList					[out]	���úõ��ն��б���
				hAddOneBtn					    [out]	ѡ���ն˰�ť���
				hOkBtn					        [out]	ȷ����ť���
				hCancelBtn						[out]	�˳���ť���
                hLoadScheBtn                    [out]   ���뷽����ť���
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitVideoSrcHandle(HWND &hScheNameCb, HWND &hSaveScheBtn, HWND &hDelScheBtn,
                              HWND &hPortCb, HWND &hConfMtList, HWND &hVideoMtList,
                              HWND &hAddOneBtn, HWND &hOkBtn, HWND &hCancelBtn,
                              HWND &hLoadScheBtn);


    // ���³�ʼ��������4.0������

    /*=============================================================================
    �� �� ����InitMcuWizardHandle
    ��    �ܣ���ʼ��MCU�����򵼾��
    ��    ����	hCfgRdo                         [out]   ����Mcu����Radiobox ���
                hImportRdo                      [out]   Import ����Radiobox ���
                hExportRdo                      [out]   Export ����Radiobox ���
                hMcuIp   						[out]	Mcu IP��ַ���
			    hMcuMaskIp    					[out]	Mcu ����������
			    hMcuGatewayIp   				[out]	Mcu ����IP���
			    hRegGkCk					    [out]	�Ƿ�ע�ᵽGK��ť���
                hGkIp                           [out]   GK IP���    
                hAliasEt                        [out]   Mcu �����������
                hE164Et                         [out]   Mcu E164�������
                hRebootCk                       [out]   ����Reboot Checkbox���
                hFilenameEt                     [out]   �����ļ����������
                hFileBrowseBtn                  [out]   ����ļ���ť���
                hNextBtn                        [out]   ��һ����ť���
                hPrevBtn                        [out]   ��һ����ť���    
			    hCancelBtn						[out]	�˳���ť���

    �� �� ֵ��BOOL32
    =============================================================================*/
    BOOL32 InitMcuWizardHandle(HWND &hCfgRdo, HWND &hImportRdo, HWND &hExportRdo,
                                   HWND &hMcuIp, HWND &hMcuMaskIp, HWND &hMcuGatewayIp,
                                   HWND &hRegGkCk, HWND &hGkIp,HWND &hAliasEt, HWND &hE164Et,  
                                   HWND &hRebootCk,
                                   HWND &hFilenameEt, HWND &hFileBrowseBtn, 
                                   HWND &hNextBtn, HWND &hPrevBtn, HWND &hCancelBtn
                                   );

    /*=============================================================================
	�� �� ����InitSnmpCfgHandle
	��    �ܣ���ʼ��Snmp���������öԻ�����
	��    ����	hSnmpIp 						[out]	������Ip���
				hRCommEt    					[out]	����ͬ��Edit���
				hWCommEt    					[out]	д��ͬ��Edit���
				hDPortEt    			        [out]	��д�˿�Edit���
				hTrapEt  					    [out]	��Trap�˿�Edit���
				hOkBtn					        [out]	ȷ����ť���
				hCancelBtn						[out]	�˳���ť���
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitSnmpCfgHandle(HWND &hSnmpIp, HWND &hRCommEt, HWND &hWCommEt,
                               HWND &hDPortEt, HWND &hTrapEt,
                               HWND &hOkBtn, HWND &hCancelBtn
                               );
    
    
    /*=============================================================================
    �� �� ����InitVmpConfigHandle
    ��    �ܣ���ʼ������ϳ����þ��������
    ��    ����	hEnableCk    			        [out]	�Ƿ��������ð�ť���
                hSelBgBtn                       [out]   ѡ���汳��ɫ��ť���
                hSelMtBtn                       [out]   ѡ����һ���ն˱߿�ɫ��ť���
                hSelCmBtn                       [out]   ѡ������ϯ�ն˱߿�ɫ��ť���    
                hSelSpBtn                       [out]   ѡ���淢���ն˱߿�ɫ��ť���
			    hOkBtn					        [out]	ȷ����ť���
			    hCancelBtn						[out]	�˳���ť���
    �� �� ֵ��BOOL32
    =============================================================================*/
    BOOL32 InitVmpConfigHandle(HWND &hEnableCk,
                               HWND &hSelBgBtn, HWND &hSelMtBtn, HWND &hSelCmBtn,
                               HWND &hSelSpBtn,
                               HWND &hOkBtn, HWND &hCancelBtn
                               );

    /*=============================================================================
    �� �� ����InitMcuChipCfgHandle
    ��    �ܣ���ʼ��MCU �������þ��
    ��    ����	hMcuChipCb 						[out]	Mcu ��������ѡ�����
			    hLayerEt    					[out]	�����ű༭����
			    hSlotEt         				[out]	����ۺű༭����
			    hChipIp   						[out]	Mcu ����IP��ַ���
			    hLanIfCb       					[out]	����ѡ����
			    hBrdCk            				[out]	�Ƿ��鲥Checkbox���         
            
                hOkBtn
                hCancelBtn

    �� �� ֵ��BOOL32
    =============================================================================*/
    BOOL32 InitMcuChipCfgHandle(HWND &hMcuChipCb, 
                                   HWND &hLayerEt, HWND &hSlotEt, 
                                   HWND &hChipIp, 
                                   HWND &hLanIfCb, HWND &hBrdCk, 
                                   HWND &hOkBtn, HWND &hCancelBtn
                                   );

    /*=============================================================================
    �� �� ����InitMcuChipModuleCfgHandle
    ��    �ܣ���ʼ��MCU ����ģ�����öԻ�����
    ��    ����	hModuleTypeCb                   [out]   ģ������Combobox���
                hModuleAliasEt    				[out]	ģ������༭����
			    hMcuStartPortEt					[out]	ģ��Mcu��ʼ�˿ںű༭����
			    hSwitchBrdIdxEt    				[out]	ģ�齻���������ű༭����
			    hRunningBrdIdxEt  				[out]	ģ�����а������ű༭����
			    hRecvStartPortEt				[out]	ģ�����������ʼ�˿ںű༭����
			    ahUseMapCk            		    [out]	ʹ��Map Checkbox���
            
                hOkBtn
                hCancelBtn

    ˵    ����
    �� �� ֵ��BOOL32
    =============================================================================*/
    BOOL32 InitMcuChipModuleCfgHandle(HWND &hModuleTypeCb, 
                                   HWND &hModuleAliasEt, 
                                   HWND &hMcuStartPortEt, 
                                   HWND &hSwitchBrdIdxEt, 
                                   HWND &hRunningBrdIdxEt, 
                                   HWND &hRecvStartPortEt,
                                   HWND ahUseMapCk[5],
                                   HWND &hOkBtn, HWND &hCancelBtn
                                   );

    /*=============================================================================
	�� �� ����InitModBasicHandle
	��    �ܣ���ʼ��ģ�������Ϣ�Ի�����
	��    ����	hConfNameEt                         [out]   �������༭����
                hConfE164Et                         [out]   ����E164�ű༭����
                hBitrateCb                          [out]   ��������Combo���
                hBitAdvBtn                          [out]   �������ʸ߼����ð�ť���
                hBitDefaultBtn                      [out]   ���ʴ�ΪĬ�ϰ�ť���
                hDoubleBitCk                        [out]   ˫�ٻ���Checkbox���
                hLowBtiBrdCk                        [out]   ���������鲥Checkbox���
                hLowBitrateCb                       [out]   ��������Combo���
                hConfHourEt                         [out]   �������Сʱ�༭����
                hConfMinuteEt                       [out]   ����������ӱ༭����
                hEndManualCk                        [out]   �ֹ�����Checkbox���
                hAdvBtn                             [out]   �򿪸߼����öԻ���ť���
                hOkBtn
                hCancelBtn

    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitModBasicHandle(HWND &hConfNameEt, HWND &hConfE164Et, 
                              HWND &hBitrateCb, HWND &hBitAdvBtn, HWND &hBitDefaultBtn, 
                              HWND &hDoubleBitCk, HWND &hLowBitBrdCk, HWND &hLowBitrateCb,
                              HWND &hConfHourEt, HWND &hConfMinuteEt, HWND &hEndManualCk,
                              HWND &hAdvBtn,
                              HWND &hOkBtn, HWND &hCancelBtn);
                              


    /*=============================================================================
	�� �� ����InitModMediaHandle
	��    �ܣ���ʼ��ģ��ý����Ϣ�Ի�����
	��    ����hMainVFmtCb	                         [out]   ����Ƶ��ʽCombo���
              hMainResCb                             [out]   ����Ƶ�ֱ���Combo���
              hMainFrCb                              [out]   ����Ƶ֡��Combo���
              hMainAFmtCb	                         [out]   ����Ƶ��ʽombo���
              hSecVFmtCb	                         [out]   ����Ƶ��ʽCombo���
              hSecResCb                              [out]   ����Ƶ�ֱ���Combo���
              hSecFrCb                               [out]   ����Ƶ֡��Combo���
              hSecAFmtCb	                         [out]   ����Ƶ��ʽombo���
              hDStreamVFmtCb                         [out]   ˫����ʽCombo���
              hDStreamResCb                          [out]   ˫���ֱ���Combo���
              hDsFrCb                                [out]   ˫����Ƶ֡��Combo���
              hSensitivityCb                         [out]   �����������ж�Combo���
              hSpeakerSrcCb                          [out]   ��������Combo���
              hSpeakerAudioCk                        [out]   �Ƿ������ƵCheckbox
              hMixDelayEt                            [out]   ������ʱEdit
              hOkBtn
              hCancelBtn


    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitModMediaHandle(HWND &hMainVFmtCb, HWND &hMainResCb, HWND &hMainFrCb, HWND &hMainAFmtCb, 
                              HWND &hSecVFmtCb, HWND &hSecResCb, HWND &hSecFrCb, HWND &hSecAFmtCb,
                              HWND &hDStreamVFmtCb, HWND &hDStreamResCb, HWND &hDsFrCb, 
                              HWND &hSensitivityCb, 
                              HWND &hSpeakerSrcCb, HWND &hSpeakerAudioCk,
                              HWND &hMixDelayEt,
                              HWND &hOkBtn, HWND &hCancelBtn);

    

    /*=============================================================================
	�� �� ����InitModMtHandle
	��    �ܣ���ʼ��ģ���ն���Ϣ�Ի�����
	��    ����	hMtAliasEt                          [out]   Mt��������༭����
                hAddMtBtn                           [out]   ����ն˰�ť���
                hAddH320MtBtn                       [out]   ���H320��ť���
                hAddToAddrCk                        [out]   �Ƿ�ͬʱ��ӵ���ַ��Checkbox���
                hAddrbookBtn                        [out]   �򿪵�ַ����ť���
                hMtList                             [out]   �ն��б� List���
                hDelMtBtn                           [out]   ɾ���ն˰�ť���
                hCallTypeCfgBtn                     [out]   �����������ð�ť���
                hVmpCfgBtn                          [out]   ���û���ϳ���/����ǽ��ť���

                hUseVmpCk                           [out]   ����Vmp Checkbox���
                hBrdVmpCk                           [out]   �㲥Vmp ����Checkbox���
                hVmpStyleCb                         [out]   ����ϳɷ��Combobox���
                hVmpSchemaCb                        [out]   ����ϳɷ���Combobox���
                ahVmpBtn[16]                        [out]   16������ϳɰ�ť���
                hUseTvwallCk                        [out]   ���õ���ǽCheckbox���
                hTvwallCb                           [out]   ����ǽѡ��Combobox���
                ahTvwallBtn[16]                     [out]   16������ǽ��ť���

                hOkBtn
                hCancelBtn                

    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitModMtHandle(HWND &hMtAliasEt, HWND &hAddMtBtn, HWND &hAddH320MtBtn, 
                           HWND &hAddToAddrCk, HWND &hAddrBookBtn,
                           HWND &hMtList, HWND &hDelMtBtn, 
                           HWND &hCallTypeCfgBtn, HWND &hVmpCfgBtn, 
                           HWND &hUseVmpCk, HWND &hBrdVmpCk,
                           HWND &hVmpStyleCb, HWND &hVmpSchemaCb, 
                           HWND ahVmpBtn[16], 
                           HWND &hUseTvwallCk, 
                           HWND &hTvwallCb,
                           HWND ahTvwallBtn[16],  
                           HWND &hOkBtn, HWND &hCancelBtn );

    /*=============================================================================
	�� �� ����InitModAdvHandle
	��    �ܣ���ʼ��ģ��߼���Ϣ�Ի�����
	��    ����	hConfCtrlCk                         [out]   �Ƿ��ؼ��ܾ��
                hOpenModeCb                         [out]   ���鿪��ģʽCombobox���
                hConfPwdEt                          [out]   ��������Edit���
                hConfPwdCfmEt                       [out]   ��������ȷ��Edit���
                hEncryptTransCb                     [out]   ���ܴ���Combobox���
                
                hCascadeModeCk                      [out]   ����Checkbox���
                hMulticastCk                        [out]   �鲥����Checkbox���
                hDataConfCk                         [out]   �����ݻ���Checkbox���
                hQosCk                              [out]   Qos Checkbox���
                hVideoPrioityCk                     [out]   ��Ƶ����Checkbox���
                hAdapterCk                          [out]   ����������Checkbox���
                hRetransferCk                       [out]   �����ش�Checkbox���
                hUniformModeCk                      [out]   ��һ����Checkbox���
                hConfMuteCk                         [out]   ��ʼ����Checkbox���
                hDiscussCk                          [out]   ���ۻ���Checkbox���
                hAutoEndCk                          [out]   �Զ�����Checkbox���
                hDataConfIp                         [out]   ���ݻ���IP �ؼ����
                hOkBtn
                hCancelBtn
                
    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitModAdvHandle(HWND &hConfCtrlCk, HWND &hOpenModeCb, 
                            HWND &hConfPwdEt, HWND &hConfPwdCfmEt, 
                            HWND &hEncryptTransCb, 
                            HWND &hCascadeModeCk, HWND &hMulticastCk,HWND &hDataConfCk, 
                            HWND &hQosCk, HWND &hVideoPriorityCk, 
                            HWND &hAdapterCk, HWND &hRetransferCk, HWND &hUniformModeCk, 
                            HWND &hConfMuteCk, HWND &hDiscussCk, 
                            HWND &hAutoEndCk,
                            HWND &hDataConfIp, 
                            HWND &hCallCb, HWND &hCallNumEt, HWND &hCallTimerEt,
                            HWND &hOkBtn, HWND &hCancelBtn);


    /*=============================================================================
	�� �� ����InitModMtAdvHandle
	��    �ܣ���ʼ��ģ�����/�ն˺��з�ʽ�Ի�����,�ѷ���
	��    ����	hMtBitrateCk                        [out]   �����ն˺�������Check���
                hMtBitrateEt                        [out]   �ն˺�������Edit���
                hMtCallCb                           [out]   ���з�ʽCombo���
                hCallNumEt                          [out]   ���д���Edit���
                hCallTimerEt                        [out]   ���м��Edit���
                hOkBtn
                hCancelBtn                

    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================
    BOOL32 InitModMtAdvHandle(HWND &hMtBitrateCk, HWND &hMtBitrateEt, 
                              HWND &hMtCallCb, HWND &hCallNumEt, HWND &hCallTimerEt,
                              HWND &hOkBtn, HWND &hCancelBtn); */
    

    /*=============================================================================
	�� �� ����InitAddH320Handle
	��    �ܣ���ʼ�����H320�Ի���ؼ����
	��    ����	hLayerEt                            [out]   �������༭����
                hSlotEt                             [out]   �ۺ�����༭����
                hChannelEt                          [out]   ͨ��������༭����
                hAddToAddrCk                        [out]   ��ӵ���ַ��Check���
                hOkBtn            

    ˵    �������ڲ�ʹ��
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 InitAddH320Handle(HWND &hLayerEt, HWND &hSlotEt, HWND &hChannelEt,
                             HWND &hAddToAddrCk,
                             HWND &hOkBtn);

    
	//-----------------------------------------------------------------------------
	//	5.����ͷң��
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����Camera
	��    �ܣ�����ͷң�ؿ���
	��    ����	pszConfName						[in]	������
				pszMtAlias						[in]	�ն���
				nClickButton					[in]	���°�ť��
				byChannel						[in]	����λ��
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL Camera(const s8 *pszConfName, const s8 *pszMtAlias, s32 nClickButton, u8 byChannel = 0);

	//-----------------------------------------------------------------------------
	//	6.��ز���׼��
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����Monitor
	��    �ܣ����Ԥ����
	��    ����	byChannel			[in]	ֹͣ��صĿؼ�λ��
				byMonitorPos		[in]	���λ�� 0:ģ��᳡ 1:��ش���
				ahMonitorBtn		[out]	��ش��ھ��
	�� �� ֵ��BOOL
	=============================================================================*/
	BOOL Monitor(u8 &byChannel, u8 byMonitorPos, HWND ahMonitorBtn[9]);

private:
	//-----------------------------------------------------------------------------
	//	7.����
	//-----------------------------------------------------------------------------

	/*=============================================================================
	�� �� ����GetTextFromTMtAlias
	��    �ܣ���TMtAlias�ṹ���ȡ�ַ���
	��    ����	ptMtAlias						[in]	�����ṹ
	˵    ��������ΪIP��ַʱ, ��u32תΪ�ַ���;���򷵻ر����ṹ����ַ���
	�� �� ֵ����
	=============================================================================*/
	CString GetTextFromTMtAlias(const TMtAlias *ptMtAlias);

	/*=============================================================================
	�� �� ����GetAudPlatHandle
	��    �ܣ����ݵ�ǰ�ɼ�����, ��ȡģ��᳡�����ϯ����ϯ̨���
	��    ������
	˵    ����0: LISTCTRL; 1: TREECTRL;
	�� �� ֵ����
	=============================================================================*/
	s32 GetAudPlatHandle();

	/*=============================================================================
	�� �� ����GetSubItem
	��    �ܣ����ݴ����������ȷ��ListCtrl������λ��
	��    ����	byAliasType						[in]	��������
				bAddr							[in]	ListCtrl�Ƿ����ַ���й�
	˵    ����
	�� �� ֵ������λ��
	=============================================================================*/
	s32 GetSubItem(u8 byAliasType, BOOL bAddr = FALSE);

    /*=============================================================================
	�� �� ����FindAddrEntry
	��    �ܣ��ҳ���ַ����Ŀλ��
	��    ����  hWnd                            [in]    ��Ŀ�ؼ����
                tAddrEntry						[in]	��ַ����Ŀ
	˵    ����
	�� �� ֵ����Ŀλ��, û���ҵ�����Ŀ�򷵻�-1
	=============================================================================*/
    s32 FindAddrEntry(HWND hWnd, const TADDRENTRYINFO &tAddrEntry);


    /*=============================================================================
	�� �� ����ColorDialogInput
	��    �ܣ�����ɫѡ��Ի�����ѡ����ɫ
	��    ����  color                            [in]    Ҫѡ�����ɫRGBֵ
	˵    ����
	�� �� ֵ��BOOL32
	=============================================================================*/
    BOOL32 ColorDialogInput(COLORREF color);




protected:
	CGuiUnit			m_cGuiUnit;			//����������ӿ�
	s32					m_nCurGuiPos;		//��ǰ���ڽ���λ��
	s32					m_nCurGuiSubPos;	//��ǰ�����ӽ���λ��
	BOOL				m_bOprDelay;		//�Ƿ���ʱ�Ŀ���,Ĭ��Ϊ��ʱ
	s32					m_nCurState;		//��ǰ��������״̬

	HWND				m_hCallingDlg;		//����������
    HWND                m_hVideoSrcPollDlg; //��ƵԴ��ѯ������

//	HWND				m_hPollDlg;			//��ѯ������
//	HWND				m_hMsgDlg;			//����Ϣ������
//	HWND				m_hVmpDlg;			//����ϳɽ�����
//	HWND				m_hTvWallDlg;		//����ǽ������
//	HWND				m_hMixDlg;			//���ƻ���������
    
	HWND				m_hAudience;		//ģ��᳡����ϯ���
	HWND				m_hPlatform;		//ģ��᳡��ϯ̨���
	HWND				m_hAudience1;		//ģ��᳡����ϯListCtrl���
	HWND				m_hAudience2;		//ģ��᳡����ϯTreeCtrl���
	HWND				m_hPlatform1;		//ģ��᳡ƽ��״̬ListCtrl���
	HWND				m_hPlatform2;		//ģ��᳡����״̬ListCtrl���
	HWND				m_hHelpSt;			//������ʾ���, ����������ٲ˵�

	HWND				m_hConfManageBtn;	//�������ť���
	HWND				m_hSimConfBtn;		//ģ��᳡��ť���
	HWND				m_hMonitorBtn;		//��ذ�ť���
	HWND				m_hSysManageBtn;	//ϵͳ����ť���
	HWND				m_hMcuManageBtn;	//MCU�豸����ť���
	HWND				m_hConfList;		//������Ϣ���

	HWND				m_hTemplateList;	//����ģ���б���

	HWND				m_hMcuCb;			//����MCU��������
	HWND				m_hConnectBtn;		//����MCU��ť���
	HWND				m_hDisconnectBtn;	//�Ͽ�MCU��ť���
	HWND				m_hConfCb;			//������������
	HWND				m_hQueitCk;			//�ն˾�����ť���
	HWND				m_hMuteCk;			//�ն�������ť���
	HWND				m_hConfSettingBtn;	//�������ð�ť���
	HWND				m_hConfCallingBtn;	//���������ť���
	HWND				m_hConfPollBtn;		//������ѯ��ť���
	HWND				m_hShortMsgBtn;		//����Ϣ��ť���
	HWND				m_hViewBigBtn;		//��ͼ����ʾ��ť���
	HWND				m_hViewSmallBtn;	//Сͼ����ʾ��ť���
	HWND				m_hViewTreeBtn;		//������ʾ��ť���
    HWND                m_hLocalQuietBtn;      //�����ն˾�����ť���
    HWND                m_hLocalCancelQuietBtn;//����ȡ��������ť���
    HWND                m_hLocalMuteBtn;       //�����ն�������ť���
    HWND                m_hLocalCancelMuteBtn; //����ȡ��������ť���
	HWND				m_hTodayConfList;	//���ջ����б���
	HWND				m_hAddrbookList;	//��ַ���б���
	HWND				m_hAddrGroupList;	//��ַ���������б���
	HWND				m_hUserList;		//�û��б���
	HWND				m_hAddrBtn;			//��ַ����ť���
	HWND				m_hUserBtn;			//�û�����ť���
	HWND				m_hUserAddBtn;		//����û���ť���
	HWND				m_hUserDelBtn;		//ɾ���û���ť���
	HWND				m_hUserEditBtn;		//�޸��û���ť���
	HWND				m_hAddEntryBtn;		//��ӵ�ַ����Ŀ��ť���
    HWND				m_hAddEntryH320Btn;	//��ӵ�ַ��H320��Ŀ��ť���
	HWND				m_hEditEntryBtn;	//�޸ĵ�ַ����Ŀ��ť���
	HWND				m_hDelEntryBtn;		//ɾ����ַ����Ŀ��ť���
	HWND				m_hAddGroupBtn;		//��ӵ�ַ�������鰴ť���
	HWND				m_hEditGroupBtn;	//�޸ĵ�ַ�������鰴ť���
	HWND				m_hDelGroupBtn;		//ɾ����ַ�������鰴ť���
	HWND				m_hAddMemberBtn;	//��ӻ�������Ŀ��ť���
	HWND				m_hDelMemberBtn;	//ɾ����������Ŀ��ť���
    HWND                m_hCreateConfBtn;   //�������鰴ť���

    HWND                m_hUserSettingBtn;  //�û����ð�ť���

    HWND                m_hCallVmpCk;       //�����˺ͱ������˺ϳ�Check box���
    HWND                m_hCallerCk;        //������Check box���
    HWND                m_hCalleeCk;        //��������Check box���

    HWND                m_hLangCb;          //����ѡ��Combobox
    HWND                m_hApplyLanBtn;     //Ӧ������
    HWND                m_hPersonMenuCk;    //ʹ�ø��Ի��˵�Checkbox
    HWND                m_hPersonMenuBtn;   //���ø��Ի��˵���ť


    // ������Mcu��������еĿؼ�    
    HWND                m_hMcuBasic;        // Mcu���û�����Ϣ����
    HWND                m_hMcuNetwork;      // Mcu�����������ý���
    HWND                m_hMcuChip;         // Mcu���õ�����������ý���
    HWND                m_hMcuDev;          // Mcu��������״̬����
    // HWND                m_hMcuWizard;       // Mcu�����򵼶Ի���

    HWND                m_hRefreshMcuBtn;   // ˢ��Mcu��Ϣ��ť
    HWND                m_hRebootMcuBtn;    // ����Mcu��ť
    HWND                m_hSynTimeBtn;      // ͬ��ʱ�䰴ť

    // Mcu ����

    HWND                m_hMcuCfgTab;       // Mcu ����Tab�ؼ�

    HWND                m_hMcuNetSaveBtn;   // �����������ð�ť
    HWND                m_hCfgWizardBtn;    // �����򵼰�ť

    HWND                m_hMcuNetIp;        // Mcu Ip��ַ
    HWND                m_hMcuNetMask;      // Mcu ��������
    HWND                m_hMcuNetGw;        // Mcu ���ص�ַ
    HWND                m_hMcuRegGkCk;      // �Ƿ�ע�ᵽGk��Checkbox
    HWND                m_hMcuRegGkIp;      // Gk Ip
    HWND                m_hMcuAliasEt;      // Mcu ����
    HWND                m_hMcuE164Et;       // Mcu E164 ��

    HWND                m_hMcuBrdIp;        // �鲥IP��ַ
    HWND                m_hMcuBrdPortEt;    // �鲥��ʼ�˿�
    HWND                m_hMcuDataPortEt;   // ����������ʼ�˿�
    HWND                m_hMcuH225PortEt;   // H225��ʼ�˿�

    HWND                m_hMcuMaxMtNumEt;   // ��������ն���


    // SNMP tab
    HWND                m_hSnmpLs;          // SNMP ������List
    HWND                m_hMcuSnmpAddBtn;   // Add Snmp
    HWND                m_hMcuSnmpDelBtn;   // Del Snmp
    HWND                m_hMcuSnmpEditBtn;  // Edit Snmp

    // QoS Tab
    HWND                m_hMcuQosTypeCb;    // QoS ���� Combo

    HWND                m_hMcuQosIpLDCk;    // Qos IP Low Delay Check
    HWND                m_hMcuQosIpHTCk;    // Qos IP High Throu Check
    HWND                m_hMcuQosIpHRCk;    // Qos IP High Reliab Check
    HWND                m_hMcuQosIpLECk;    // Qos IP Low Expense Check

    HWND                m_hMcuQosIpAudioEt; // ��Ƶ����ȼ�
    HWND                m_hMcuQosIpVideoEt; // ��Ƶ����ȼ�
    HWND                m_hMcuQosIpCmdEt;   // �������ȼ�
    HWND                m_hMcuQosIpDataEt;  // ���ݷ���ȼ�
    HWND                m_hMcuQosDefaultBtn;// �ָ���QoSĬ��ֵ��ť

    // Misc Tab
    HWND                m_hMcuMiscSaveBwCk; // �Ƿ��ʡ����Checkbox
    HWND                m_hMcuMiscChainCkEt;// ���������
    HWND                m_hMcuMiscChainCkTimesEt;// ����������
    HWND                m_hMcuMiscMtRefRateEt; // �¼��ն��б�ˢ�¼��
    HWND                m_hMcuMiscAudRefRateEt;// �¼���ƵԴˢ�¼��
    HWND                m_hMcuMiscVidRefRateEt;// �¼���ƵԴˢ�¼��

    HWND                m_hMcuMpcCk;        // ʹ��Mpcת������Check
    HWND                m_hMcuMpcStackCk;   // ʹ��MpcЭ��ջ
    HWND                m_hMcuSymModeCb;    // ͬ��ģʽ
    HWND                m_hMcuDriEt;        // Dri ���
    HWND                m_hMcuE1Et;         // E1 ͨ����    

    HWND                m_hMcuMiscDcsCk;    // ����DCS
    HWND                m_hMcuMiscDcsIp;    // DCS IP

    HWND                m_hMcuMiscResetBtn;    // �ָ�������Miscѡ��Ĭ��ֵ��ť

    // Vmp Tab
    HWND                m_hMcuVmpSchCb;     // ����ѡ��Combbo
    HWND                m_hMcuVmpSchSaveBtn;// ��������Btn
    HWND                m_hMcuVmpSchRenameBtn; // ��������Btn

    HWND                m_hMcuVmpBgCp;      // ����ɫColorPicker
    HWND                m_hMcuVmpMtCp;      // �ն�ɫColorPicker
    HWND                m_hMcuVmpSpCp;      // ������ɫColorPicker
    HWND                m_hMcuVmpCmCp;      // ��ϯɫColorPicker
        
    // ��������
    HWND                m_hMcuChipTab;      // ������Ϣ�л�Tab
    HWND                m_hMcuChipLs;       // ������Ϣ�б�
    HWND                m_hMcuChipAddBtn;   // ��ӵ��尴ť
    HWND                m_hMcuChipEditBtn;  // �༭���尴ť
    HWND                m_hMcuChipDelBtn;   // ɾ�����尴ť
    HWND                m_hMcuChipRebootBtn;// �������尴ť

    HWND                m_hMcuChipModuleLs; // ��������ģ���б�
    HWND                m_hMcuChipModAddBtn;// ���ģ�鰴ť
    HWND                m_hMcuChipModEditBtn; // ����ģ�鰴ť
    HWND                m_hMcuChipModDelBtn;// ɾ��ģ�鰴ť
    
    HWND                m_hMcuRecLs;        // ¼����б�
    HWND                m_hMcuRedAddBtn;    // ���¼�����ť
    HWND                m_hMcuRedEditBtn;   // ����¼�����ť
    HWND                m_hMcuRedDelBtn;    // ɾ��¼�����ť
    
    
    // �������
    HWND                m_hDevManageList;   // �����б�List
   
};

#endif	//	#define __MCSUITESTLIB_H