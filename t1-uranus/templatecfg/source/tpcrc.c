

#include <stdio.h>

#include "tpcrc.h"

//Ѱַ���ֽڶ��壬����CRC4��ֵ�������
typedef union
{
	u8 m_byVal;
	struct
	{
#ifdef WIN32
		u8 bit0:1;
		u8 bit1:1;
		u8 bit2:1;
		u8 bit3:1;
		u8 bit4:1;
		u8 bit5:1;
		u8 bit6:1;
		u8 bit7:1;
#else
		u8 bit7:1;
		u8 bit6:1;
		u8 bit5:1;
		u8 bit4:1;
		u8 bit3:1;
		u8 bit2:1;
		u8 bit1:1;
		u8 bit0:1;
		
#endif
	}bits;

} BITBYTE;

//λѰַ���ֶ��壬����BAS��˫�ݴ���������
typedef union
{
	u16 m_wVal;
	struct
	{
#ifdef WIN32
		u16 bit0:1;
		u16 bit1:1;
		u16 bit2:1;
		u16 bit3:1;
		u16 bit4:1;
		u16 bit5:1;
		u16 bit6:1;
		u16 bit7:1;
		u16 bit8:1;
		u16 bit9:1;
		u16 bit10:1;
		u16 bit11:1;
		u16 bit12:1;
		u16 bit13:1;
		u16 bit14:1;
		u16 bit15:1;
#else
		u16 bit15:1;
		u16 bit14:1;
		u16 bit13:1;
		u16 bit12:1;
		u16 bit11:1;
		u16 bit10:1;
		u16 bit9:1;
		u16 bit8:1;
		u16 bit7:1;
		u16 bit6:1;
		u16 bit5:1;
		u16 bit4:1;
		u16 bit3:1;
		u16 bit2:1;
		u16 bit1:1;
		u16 bit0:1;
		
#endif
	}bits;
} BITWORD;


static u32 g_abyCrc4RemTbl[256];

static u32 g_dwPolynomial = 0x04c11db7;

static u32 Reflect( u32 dwRef, char ch )
{	
	int i;
	u32 dwValue = 0;
	/* ����bit0��bit7��bit1��bit6������*/
	for( i = 1; i < ( ch + 1 ); i++ )
	{	
		if ( dwRef & 1 )
			dwValue |= 1 << ( ch - i );
	   	dwRef >>= 1;	
	}
	return dwValue;
}



/*====================================================================
	������  	��TpGenCrc4ReTbl
	����		������crc4��ֵ��
	�㷨ʵ��	������ʽģ2����:  g(x)=x4+x+1 
	����ȫ�ֱ�����
	�������˵����
	����ֵ˵��  ��
====================================================================*/
void TpGenCrc4RemTbl()
{
	BITBYTE byCrc4Reg;
	BITWORD wWord;
    u16 wCurCh;
	u8  byNum;
	//256 characters
	for( wCurCh=0;wCurCh<256;wCurCh++)
	{
		byCrc4Reg.m_byVal = 0;
		wWord.m_wVal      = (u16)(wCurCh<<8); //ȡ����Ч�ַ�
		for( byNum = 0; byNum < 12; byNum++)//��������ʱ���油4��0��������8��4λ
		{
			byCrc4Reg.m_byVal <<= 1;
			byCrc4Reg.bits.bit0 = (u8)wWord.bits.bit15;
			wWord.m_wVal      <<= 1;
			if(byCrc4Reg.bits.bit4) //���λΪ1ʱ�Ž���ģ2��������
			{
				byCrc4Reg.m_byVal = (u8)(byCrc4Reg.m_byVal^0x13);
			}
		}
		g_abyCrc4RemTbl[wCurCh] = byCrc4Reg.m_byVal&0x0f;//�õ���������crc4��
	}

	return;
}


/*====================================================================
	������  	��TpGenCrc4Code
	����		�����ٲ��������������������ݵ�crc4У����
	�㷨ʵ��	������ʽģ2����
	����ȫ�ֱ�����
	�������˵����pbyBuf    ���ݻ����������������ֽ�
				  wDataLen  ���ݳ���

	����ֵ˵��  ��������crc4У���룬������λ��Ч
====================================================================*/
u8 TpGenCrc4Code( const u8 *pbyBuf, u32 dwDataLen )
{
	u8 byByte = 0;
	u32 dwNum;
	if( (NULL == pbyBuf) || (0 == dwDataLen) )
	{	
		return byByte;
	}

	byByte = (u8)g_abyCrc4RemTbl[pbyBuf[0]];
	for(dwNum=1; dwNum<dwDataLen; dwNum++)
	{
		byByte = (u8)g_abyCrc4RemTbl[(byByte<<4)|(pbyBuf[dwNum]>>4)];
		byByte = (u8)g_abyCrc4RemTbl[(byByte<<4)|(pbyBuf[dwNum]&0x0f)];
	}
	
	byByte = (u8)g_abyCrc4RemTbl[byByte<<4];

	return byByte;
}

BOOL32 TpIsValidCRC4( u8 *pDataBuf, u32 dwLen, u8 byCheckCode )
{
	u8 byOldCheckCode = TpGenCrc4Code( pDataBuf, dwLen );
	return ( byOldCheckCode == byCheckCode );
}

