#ifndef _h_iframecheck_h__
#define _h_iframecheck_h__


u32 RcvFilterCallBackFun(u32 dwRecvIP, u16 wRecvPort, u32 dwSrcIP, u16 wSrcPort, u8* pData, u32 uLen);

void SndFilterCallBackFun(u32 dwRecvIP, u16 wRecvPort, u32 dwSrcIP,  u16 wSrcPort,
						  TNetSndMember *ptSends,            // ת��Ŀ���б�
						  u16* pwSendNum,                    // ת��Ŀ����� 
						  u8* pUdpData, u32* pdwUdpLen);

#endif // _h_iframecheck_h__
