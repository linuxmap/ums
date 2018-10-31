/***************************************************************************************
�ļ���	    ��H264Dec.h
����ļ�	��H264Dec.c
�ļ�ʵ�ֹ��ܣ������ϲ�Ӧ�ò�ֻ��Ϊ����һ֡�ṩ��MAX_FRAME_BUFFER_LEN��(128k)�Ļ��棬����
			  ������������ָ�֡��������������ó��ȣ�����ʧ�ܣ���Σ��ϵ���ϴ󣬶���һ��
			  352x288��ͼ�񣬱���Ϊ��֡���Դﵽ81k !!! ��λ���ֽ�
����		���ż���
�汾		��2004.8.28
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
01/18/2005	1.0         ����ǿ      �ż���    ����淶��
04/22/2005	1.0         ��ǿ                  ����淶��
***************************************************************************************/
#ifndef H264DEC_H
#define H264DEC_H

#include "algorithmtype.h"

#ifdef _LINUX_
#define H264vDecHandle void *
typedef enum
{
	H264DECDRV_OK,
	H264DECDRV_ERROR,
	H264DECDRV_NOMEM,
	H264DECDRV_NOHEAD,
	H264DECDRV_BADFMT,
	H264DECDRV_MEMFAIL,
	H264DECDRV_INITFAIL,
	H264DECDRV_EXIT,
	H264DECDRV_WRONG_VERSION,
	H264DECDRV_KERNEL_MODULE_PROBLEMS,	
}H264decDrvError_t;

#define	DEC_FAIL	            -1
#define DEC_OK			    H264DECDRV_OK
#define	DEC_MEMORY		    H264DECDRV_NOMEM
#define DEC_NOHEAD                  H264DECDRV_NOHEAD
#define DEC_WRONGVERSION            H264DECDRV_WRONG_VERSION
#define DEC_BAD_FORMAT              H264DECDRV_BADFMT
#define DEC_MEM_FAIL		    H264DECDRV_MEMFAIL
#define DEC_INIT_FAIL		    H264DECDRV_INITFAIL
#define DEC_EXIT		    H264DECDRV_EXIT
#else
#define H264decDrvError_t   l32
#define	DEC_OK		0
#define	DEC_FAIL	-1
#endif //_LINUX_

#define DEC_MAX_FRAME_BUFFER_LEN (128*1024)
#ifndef DEC_MAX_NALU_NUM
#define DEC_MAX_NALU_NUM  128    
#define	DEC_MAX_NALU_UNIT_SIZE	 (4*DEC_MAX_NALU_NUM)
#endif

// interface function declaration
#ifdef __cplusplus
extern "C"
{
#endif 
	
	typedef struct 
	{
		u8	*pu8YUV420;			//����YUV���ݻ��������û��ڵ��ý�����ǰ���з���
		u32	u32YUVLen;          //�����һ֡YUVͼ��ĳ��ȣ��ڰѽ�����YUVͼ�����ʱ�õ�
		u8	*pu8BitStream;		//�������H264һ֡ͼ�������������
		u32	u32BitstreamLen;	//�������H264һ֡ͼ�����������
		u32	u32ReturnWidth;		//��ǰ���ڽ����ͼ��Ŀ��
		u32	u32ReturnHeight;	//��ǰ���ڽ����ͼ��ĸ߶�
		u8  *pu8Output88MV;     //�û��ڽ������ⲿ����һ��396*4*sizeof(u8)���ڴ�ָ����Ϊ����
		                        //���396*4��8x8����˶����𣬿��λ������ͼ
		                        //�˶�����ȡֵ��Χ1-10��ֵԽ���˶�Խ���ң������Ϊ0����ʾû���˶�
		                        //Ŀǰ��֧��4CIF(720 x 576)���˶��������		                        
		                        //ע�⣺�粻��Ҫ�鿴�˶����𣬴˴����봫��NULL !!!!
	} TH264DecFramePara;
	
	//sq 05.4.26 add 88mv
	/*����Ԫ��ָ��ͼ���е�396*4��8x8���λ����ͼ( s16First88BAddr=(l32MBNr/22)*88+(l32MBNr%22)*2 )��

	[0 ][1 ]  [2 ][3 ]  [4 ][5 ]      ......    ......        [42][43]
	[44][45]  [46][47]  [48][49]                              [86][87]
	 ......
	 ......
	[1496][1497]                         ......    ......     [1538][1539]
	[1540][1541]                                              [1582][1583]
    
	*/

	typedef	struct 
	{
		l32 l32Width;		   	//����ͼ����[0,720]����Ϊ16�ı��� CIF:352 QCIF:176
		l32 l32Height;		    //����ͼ��߶�[0,576]����Ϊ16�ı��� CIF:288	QCIF:144
		l32 l32DecMode;         //�������H264��������ʽ�� 0��rtp��ʽ��1��annexb��ʽ 
	} TH264DecPara;
	
	typedef struct  
	{
		s8 *ps8Version;   //�汾��Ϣ
		l32 l32Width;	//ͼ����
		l32 l32Height;	//ͼ��߶�
	} TH264DecStatus;
	
	typedef enum {
		H264_DECODE_OK,
		H264_DECODE_ERROR	
	}TVideoErrNum;
	
#ifndef CHIP_DM642
    //��������ʼ��
	H264decDrvError_t H264DecoderInit(void **ppvHandle, TH264DecPara *ptDecPara);

	//����һ֡ͼ�����Ϊ352*288
	H264decDrvError_t H264DecodeFrame(void *pvHandle, TH264DecFramePara *ptFrmPara);

	//�ͷŽ�������Դ
	H264decDrvError_t H264DecoderClose(void *pvHandle);
		
    //��ȡH264�������汾��Ϣ����
	void GetH264Version(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);
	
	//��Ҫ�����������İ汾��Ϣ�ͱ���ʱ��
	void H264DecHelp(void);	
#else
	
	//��������ʼ��
	TVideoErrNum H264DecoderOpen(void **ppvHandle, TH264DecPara *ptDecPara);
	
	//����һ֡ͼ�����Ϊ352*288
	TVideoErrNum  H264DecoderDecFrame(void *pvHandle, TH264DecFramePara *ptFrmPara);
	
	//�ͷŽ�������Դ
	TVideoErrNum  H264DecoderClose(void *pvHandle);
	
    //��ȡH264�������汾��Ϣ����
	TVideoErrNum  H264DecoderGetStatus(void *pvHandle, TH264DecStatus *ptH264DecStatus);
	
#endif

#ifdef __cplusplus
};
#endif

#endif
