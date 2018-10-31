#ifndef _EQPMGR_H_
#define _EQPMGR_H_

#include "umsobject.h"
#include "umseqp.h"
#include "mcudef.h"

typedef struct tagTBrdEntry
{
	BOOL32		m_bUsed;					// �Ƿ�����
             
	//�����ļ���ȡ
	TTPBrdCfg	m_tBrdCfg;					//��������
	
	u8			m_byEqpNum;					// ���е�����������е��������
    TTPEqpCfg	m_atEqpCfg[TP_UMS_BRD_MAXNUM_EQP];// �����ڸõ����ϵ���������
	BOOL32		m_abEqpReg[TP_UMS_BRD_MAXNUM_EQP];

	// ����Ϊ������������
	BOOL32		m_bBrdState;				// �Ƿ�����
	BOOL32		m_bBrdDel;					//�����Ƿ�ɾ��
	BOOL32		m_bMdlDel;					//ģʽ�Ƿ�ɾ��
	u32			m_dwBrdNode;				//��������������OspNode ����Ϊ���ӵ�Ψһ��ʶ
	u32			m_dwBrdIns;                 //���ӵ�Inst��
    EMOsType	m_emOSType;                 // �����OS����
	//�ݶ�Ϊ������������
	u8			m_byPortChoice;				// ����ѡ��
    u8			m_byCastChoice;				// �鲥ѡ��
	tagTBrdEntry()
	{
		memset(this, 0, sizeof(tagTBrdEntry));
		m_bUsed = FALSE;
	}

	void BrdDisConnect()
	{
		m_bBrdState = FALSE;
		m_bBrdDel = FALSE;
		m_bMdlDel = FALSE;
		m_dwBrdNode = INVALID_NODE;
		m_dwBrdIns = INVALID_INS;
		m_emOSType = em_unknow_OsType;
		m_byPortChoice = 0;
		m_byCastChoice = 0;
		memset(m_abEqpReg, 0, sizeof(m_abEqpReg));
	}
	void BrdClear()
	{
		m_bUsed = FALSE;
		m_tBrdCfg.Clear();
		for (u16 wIndex = 0;wIndex < TP_UMS_BRD_MAXNUM_EQP; wIndex++)
		{
			m_atEqpCfg[wIndex].Clear();
			m_abEqpReg[wIndex] = FALSE;
		}
		m_byEqpNum = 0;
	}
	void BrdMdlDel(u16 wMdlIndex)
	{
		m_atEqpCfg[wMdlIndex].m_emEqpType = em_unknow_mdl;
		m_atEqpCfg[wMdlIndex].m_emEqpMdlType = em_unknow_eqp_mdl;
		memset(&m_atEqpCfg[wMdlIndex].m_szEqpAlias, 0, sizeof(m_atEqpCfg[wMdlIndex].m_szEqpAlias));	
		m_atEqpCfg[wMdlIndex].m_byEqpID = 0;
		m_abEqpReg[wMdlIndex] = FALSE;
		m_atEqpCfg[wMdlIndex].m_byAudmixNum = 0;
	}
	//����service��ȡ�����������ö�Ӧλ�õ�������
	void SetBrdCfg(const TTPBrdCfg& tBrdCfg) 
	{
		memcpy(&m_tBrdCfg, &tBrdCfg, sizeof(TTPBrdCfg));
	}
	void SetMdlCfg(u16 wMdlIndex, const TTPMdlCfg& tMdlCfg)
	{
		m_atEqpCfg[wMdlIndex].m_emEqpType = tMdlCfg.m_emEqpType;
		m_atEqpCfg[wMdlIndex].m_emEqpMdlType = tMdlCfg.m_emEqpMdlType;

		memcpy(&m_atEqpCfg[wMdlIndex].m_szEqpAlias, tMdlCfg.m_szEqpAlias, sizeof(m_atEqpCfg[wMdlIndex].m_szEqpAlias));
		m_atEqpCfg[wMdlIndex].m_byEqpID = (u8)tMdlCfg.m_wEqpId;
		m_atEqpCfg[wMdlIndex].m_byAudmixNum = tMdlCfg.m_byAudmixNum;
	}
}TBrdEntry;

class CEqpMgr
{
public:
	CEqpMgr();
	~CEqpMgr();
public:
	virtual void Handle(CTpMsg *const ptMsg);
public:
	void Init(CUmsEqpInst* pEqpInst);//�����������ļ���ȡ����

	TBrdEntry* GetBrdCfg( const TTPBrdPos& tBrdPos );//����Nodeȡ�ð���������Ϣ
	TBrdEntry* GetBrdCfg(const u8 byLayer, const u8 bySlot, const EMBrdType emType);
	TBrdEntry* GetBrdCfg(u32 dwBrdIP);
	TTPEqpCfg* GetEqpCfgByEqpID(u8 byEqpID);

	BOOL32     CheckBrdInfo( TTPBrdRegInfo *const ptBrdInfo, u32 dwNode, u32 dwIns );
	EMEqpType  BrdDisConnect(u32 dwBrdNode);
	void       UpdateBrdUsedState(TTPBrdUsedInfo& tUsed);  //���µ���ʹ��״̬
	void	   UpdateEqpRegState(u32 dwNode, u8 byEqpId, BOOL32 bReg); //��������ע��״̬
	void	   UpdateSysTimeToAllBrd();

	void	   RebootBrd(u32 dwBrdIP);
	
	u16        GetBrdIndex(u8 byBrdLayer, u8 byBrdSlot); //��õ����������ж�Ӧ����
	u16		   GetBrdIndex(u32 dwNode);					 //����node�Ż�ð�������
	u16        GetEqpIndex(u16 wBrdIndex, u8 byEqpId);	 //����eqpid�ҵ���Ӧ����
	void       ShowBrdInfo();

	u32        GetBrdInst(u16 wBrdIndex);  // ����m_atBrdEntry[wBrdIndex]�ĵ���Inst�� add by gaoyong

private:
	void       EventBrdCfgInfo(CTpMsg* const ptMsg);    //����������Ϣ
	void       EventDelHandle(CTpMsg* const ptMsg);     //����ɾ������
	void       EventModifyHandle(CTpMsg* const ptMsg); //�����޸Ĵ���
	void	   EventMdlDelHandle(CTpMsg* const ptMsg); //ģʽɾ��
	void	   EventMdlModifyHandle(CTpMsg* const ptMsg);//ģʽ�޸�
	void	   EventReboot(CTpMsg* const ptMsg);      //��������
	void	   EventUpGrade(CTpMsg* const ptMsg);     //��������
	void	   EventHardVerAck(CTpMsg* const ptMsg);  //����汾����Ӧ
	void	   EventUpdateAck(CTpMsg* const ptMsg);   //����������Ӧ
	void	   EventEqpUsedReq(CTpMsg* const ptMsg);	  //���� ����ϳ� ����ռ�����

    void       EventSwitchTelnetFtp(CTpMsg* const ptMsg); //Telnet Ftp����
	void       EventSwitchTelFtpAck(CTpMsg* const ptMsg);

private:
	void       NotifyBrdInfoToService(u16 wEvent, u8* pbyMsg = NULL, u16 wLen = 0);//֪ͨ������Ϣ��service
	void	   SendMsgToBrd(u32 dwSrcIID, u32 dwNode, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0);
private:
	u16			FindBrdArrayIndex(TTPBrdPos tPos);	//����ע���������Ϣ�ҳ����������е�����
protected:
	CUmsEqpInst*	m_pcEqpInst;
	TBrdEntry		m_atBrdEntry[TP_BOARD_MAX_NUM];//������ӵ����ú�״̬

};

#endif