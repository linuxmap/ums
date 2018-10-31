/***************************************************************************************
�ļ���	    �� TIimageprocess.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ��ṩͼ����Ķ���ӿ�.

����		��������
�汾		��4.0
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
04/29/2006	4.0         ������                 ����
***************************************************************************************/
#ifndef  _TIIMAGEPROCESS_H_
#define  _TIIMAGEPROCESS_H_

#include "algorithmtype.h"
#include "videocommondefines.h"

#ifdef __cplusplus
extern "C"
{
#endif 
	

/*====================================================================
������      �� YUV422PlaneToYUV420AndTFInit_c
����        �� ͼ��YUV422ת��ΪYUV420������ʱ���˲��ĳ�ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void **ppvHandle   : ָ��ͼ��ǰ��������ʱ���˲��ľ����ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/29    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422PlaneToYUV420AndTFInit_c(void **ppvHandle, l32 l32SrcWidth, l32 l32SrcHeight, l32 l32SrcStride,
					   l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);



/*====================================================================
������      �� YUV422PlaneToYUV420AndTF_c
����        ��ͼ��YUV422ת��ΪYUV420������ʱ���˲��Ĵ���
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              u8   *pu8Src     : ָ��Դͼ�����ݵ�ָ��
			  u8   *pu8Dst     : ָ��Ŀ��ͼ�����ݵ�ָ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ���VIDEOFAILURE;
�������ر�˵����ֻ֧�ֱַ���720*576��YUV422ת���ֱ���720*576,352*576, 352*288��YUV420ͼ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/29    1.0        ZouWenYi         ����
====================================================================*/
l32 YUV422PlaneToYUV420AndTF_c(void *pvHandle, u8 *pu8Src, u8 *pu8Dst);

/*====================================================================
������      �� YUV422PlaneToYUV420andTFClose_c
����        ���ͷ�ǰ����ľ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle  : ͼ��YUV422תΪYUV420������ʱ���˲��ľ��

����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/29    1.0        ZouWenYi         ����
====================================================================*/	
l32 YUV422PlaneToYUV420andTFClose_c(void *pvHandle);

/*====================================================================
������      �� YUV422PlaneToYUV420SetParamAndTF_c
����        ��ͼ��YUV422ת��YUV420��ʱ���˲��Ĳ�������
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ����ʱ���˲��ľ����ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/29    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422PlaneToYUV420SetParamAndTF_c(void *pvHandle, l32 l32SrcWidth, l32 l32SrcHeight, l32 l32SrcStride,
					   l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);

#define  YUV422PlaneToYUV420AndTFInit      YUV422PlaneToYUV420AndTFInit_c
#define  YUV422PlaneToYUV420AndTF          YUV422PlaneToYUV420AndTF_c
#define  YUV422PlaneToYUV420andTFClose     YUV422PlaneToYUV420andTFClose_c
#define  YUV422PlaneToYUV420SetParamAndTF  YUV422PlaneToYUV420SetParamAndTF_c


#ifdef __cplusplus
};
#endif 

#endif // _TIIMAGEPROCESS_H_


