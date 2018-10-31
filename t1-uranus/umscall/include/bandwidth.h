#ifndef _h_bandwidth_h__
#define _h_bandwidth_h__

#include "tpsys.h"
#include "callinnerstruct.h"

//������ԣ�
//ÿ�����鶼�����ô����ô�����Ҫ�����ƣ����˷����ˡ���ϯ�Ȼ����㲥��֮��ļ������������ȡ�
//�����Ϊ���к�����
//��Ҫ�����UMS��UMS֮�䣬��UMS�����ж�Ӧ��������UMS�����ߡ����߱��붼���ϲ��ܵ��ø�������
typedef struct tagTBw
{
	u32		m_wBW;

	tagTBw() { memset(this, 0, sizeof(tagTBw)); }
}TBw;

class CBandwidth
{
public:
	CBandwidth() { memset(this, 0, sizeof(CBandwidth)); }
	~CBandwidth() { memset(this, 0, sizeof(CBandwidth)); }

	void StartConf(u32 wUpBW, u32 wDownBW);
	void StopConf();

	BOOL32 AssigneUpBW(u32 wBW, EmViewType eType);
	BOOL32 AssigneDownBW(u32 wBW, EmViewType eType);

	void ReleaseUpBW(u32 wBW, EmViewType eType);
	void ReleaseDownBW(u32 wBW, EmViewType eType);

	u32 GetBwInfoByType(EmViewType eType);
	u32	CurUpBw() { return m_wUpBWCfg - m_wUpBW; }
	u32	CurDownBw() { return m_wDownBWCfg - m_wDownBW; }

	void ShowBW();
public:
	BOOL32 IsUpBw(u32 wBW) { return m_wUpBW + wBW <= m_wUpBWCfg ? TRUE : FALSE; }
	BOOL32 IsDownBw(u32 wBW) { return m_wDownBW + wBW <= m_wDownBWCfg ? TRUE : FALSE; }
private:
	u32 m_wUpBWCfg;					//ģ�����õ�������д���
	u32 m_wDownBWCfg;				//ģ�����õ�������д���

	u32 m_wUpBW;					//��ǰռ�õ�������
	u32 m_wDownBW;					//��ǰռ�õ�������

	TBw m_atUpBW[em_View_End];		//ÿ��ҵ��ռ�õ����д���
	TBw m_atDownBW[em_View_End];	//ÿ��ҵ��ռ�õ����д���
};

#endif//#ifndef _h_bandwidth_h__

