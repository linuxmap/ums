/*******************************************************************************
 *  ģ����   : XML�����                                                       *
 *  �ļ���   : xmlengine.h                                                     *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� :                                                                 *
 *  ����     : �����                                                          *
 *  �汾     : V4.0  Copyright(c) 1997-2010 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2010/03/18    4.0         �����      ����                                 *
 *                                                                             *
 *******************************************************************************/

#ifndef _XML_ENGINE_H_
#define _XML_ENGINE_H_

#include "kdvtype.h"

typedef u32 u32_ip;
typedef int BOOL;

struct TXDATANODE
{
	u16   type;        //��em_EmChanType
	u16   pretypesize; //��sizeof(EmChanType)
	char* pretype;     //��EmChanType
	int   arraynum;    //ά��
};

struct TXDATAINFO
{
	char* name;			  //�����ṹ������
	int   type;			  //�����ṹ��������	
	char* membertypename; //�ó�Ա������
	int	  size; 		  //�ó�Ա�������ʹ�С	
	int   arraymembernum; //�ó�Ա���ݸ���	
	int   matrixnum; 	  //����ó�Ա�Ƕ�ά���飬ֵΪ��һά����Ŀ������Ϊ0
	int   offset;		  //�ó�Ա�������ṹ�����ݵ�ַƫ����	
	char* member; 		  //��Ա��������
};

struct TXENUMINFO
{
	char* descrip;
	int   val;
};

#define  XML_ARRAY_SIZE       8
#define  XML_INVALID_INDEX    -1
#define  XML_OffSetOf(s,m)   (size_t)&(((s *)0)->m)
#define  XML_CountOf(array)  (sizeof(array)/sizeof(array[0]))
#define  XML_SizeOfMember(s,m) (size_t)(sizeof((((s *)0)->m)))
#define  XML_SizeOfMatrix(s,type,m) (XML_SizeOfMember(s,m)>1 ? (XML_SizeOfMember(s,m))/(size_t)(sizeof(((s *)0)->m[0])):1)

#ifndef NULL
//#define NULL    ((void *)0)
#define NULL    (0)
#endif

enum EmXMLOpsType
{
	em_XMLNone = 0, 
	em_XMLAuto, 
	em_XMLCompression,  //lzwѹ��
	em_XMLEncryption,   //����
	em_XMLCompAndEnc,   //ѹ���ͼ���
	em_XMLEnd
};

char* GetXmlStructVer();

s32 InitXMLEngine( TXDATAINFO** tAtomDataInfo,   //��ʼ��g_txAtomDataInfo
					  TXDATAINFO** tEnumDataInfo,   //��ʼ��g_txEnumDataInfo
					  TXDATAINFO** tStructDataInfo, //��ʼ��g_txStructDataInfo,
					  u16 wAtomTypeBegin,
					  u16 wEnumTypeBegin,
					  u16 wStructTypeBegin,
					  u16 wDataTypeEnd );
void ExitXMLEngine( s32 nXMLIndex );

void InitAtomType_s32    ( u16 wEmx_s32     );
void InitAtomType_BOOL32 ( u16 wEmx_BOOL32  );
void InitAtomType_BOOL   ( u16 wEmx_BOOL    );
void InitAtomType_u8     ( u16 wEmx_u8      );
void InitAtomType_s8     ( u16 wEmx_s8      );
void InitAtomType_u16    ( u16 wEmx_u16     );
void InitAtomType_u32    ( u16 wEmx_u32     );
void InitAtomType_time_t ( u16 wEmx_time_t );
void InitAtomType_u32_ip ( u16 wEmx_u32_ip  );
void InitAtomType_u8_blob( u16 wEmx_u8_blob );


BOOL32 XML_Encode( TXDATANODE* ptDataNode,	  //�ṹ�﷨������ָ��
				   void* pSrcBuf,             //eventҪ���͵�buffer
				   u32   dwSrcBufLen,         //eventҪ���͵�buffer����
				   EmXMLOpsType emXmlType,    //xml��������(ѹ�������ܵ�)
				   s8*   pDstBuf,             //����xml�������֮�󷵻ص�buffer
				   u32&  dwDstBufLen,         //����xml�������֮�󷵻ص���Чbuffer����
				   u32&  dwOverFlow,          //�����־��0Ϊxml���룬1Ϊѹ����2Ϊ����Ϊ������ѹ��
				   u16   wEvent = 0,
				   s8*   pbyEventName = NULL,
				   u32   dwEventHash = 0,
				   s32   nIndex = 0 ); 

BOOL32 XML_Decode( TXDATANODE* ptDataNode,	  //�ṹ�﷨������ָ��
				   s8*   pSrcBuf,	          //�ӵײ��õ���buffer
				   u32   dwSrcBufLen,         //�ӵײ��õ���buffer����
				   EmXMLOpsType emXmlType,    //xml��������(��ѹ�������ܵ�)
				   void* pDstBuf,             //����xml�������֮�󷵻ص�buffer
				   u32&  dwDstBufLen,         //����xml�������֮�󷵻ص���Чbuffer����
				   u32   dwOverFlow = 0,      //1��ʾ��Ҫ��ѹ��
				   u16   wEvent = 0,
				   s8*   pbyEventName = NULL,
				   s32   nIndex = 0 );

BOOL32 XML_Encode( u16 wDataType,			  //�����ṹ/��������, EmXDataType
				   void* pSrcBuf, 
				   EmXMLOpsType emXmlType, 
				   s8* pDstBuf,
				   u32& dwDstBufLen,
				   u32& dwOverFlow,
				   s32  nIndex = 0 );

BOOL32 XML_Decode( u16 wDataType,			  //�����ṹ/��������, EmXDataType
				   s8* pSrcBuf, 
				   u32 dwSrcBufLen,
				   EmXMLOpsType emXmlType, 
				   void* pDstBuf,
				   u32& dwDstBufLen,
				   u32 dwOverFlow,
				   s32 nIndex = 0 );

BOOL32 XML_GetEventHash( s8* pSrcBuf, u32   dwSrcBufLen, EmXMLOpsType emXmlType, s32& dwHash, u32 dwOverFlow );
BOOL32 XML_GetEventName( s8* pSrcBuf, u32   dwSrcBufLen, EmXMLOpsType emXmlType, s8* pEventName, u32 dwOverFlow );

#endif //_XML_ENGINE_H_


