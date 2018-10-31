/******************************************************************************
ģ����	��                        
�ļ���	��g711.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�declare of g711 function
����		��chunbo
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�޸�����
06/04/03    1.0         chunbo      add file header
*******************************************************************************/
#ifndef G711_H
#define G711_H
#include "basetype.h"

uint8_t Linear2Alaw(int16_t nPcmVal);    
int16_t Alaw2Linear(uint8_t ucAval);
uint8_t Linear2Ulaw(int16_t nPcmVal);    
int16_t Ulaw2Linear(uint8_t ucUval);
uint8_t Alaw2Ulaw(uint8_t ucAval);
uint8_t Ulaw2Alaw(uint8_t ucUval);

int32_t Linear2AlawBlock(int16_t *nPcmVal, uint8_t *uAlawVal, int16_t iPcmLen);
int32_t Alaw2LinearBlock(int16_t *nPcmVal, uint8_t *uAlawVal, int16_t iAlawLen);
int32_t Linear2UlawBlock(int16_t *nPcmVal, uint8_t *uUlawVal, int16_t iPcmLen);
int32_t Ulaw2LinearBlock(int16_t *nPcmVal, uint8_t *uUlawVal, int16_t iUlawLen);
int32_t Alaw2UlawBlock(uint8_t ucAval, uint8_t ucUval, int16_t iAlawLen);
int32_t Ulaw2AlawBlock(uint8_t ucAval, uint8_t ucUval, int16_t iUlawLen);
void  GetG711Version(char *Version, int StrLen, int * StrLenUsed);

#endif

