

#include <stdio.h>

#include "tpcrc.h"

//寻址的字节定义，用于CRC4余值表的生成
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

//位寻址的字定义，用于BAS的双容错码表的生成
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
	/* 交换bit0和bit7，bit1和bit6，类推*/
	for( i = 1; i < ( ch + 1 ); i++ )
	{	
		if ( dwRef & 1 )
			dwValue |= 1 << ( ch - i );
	   	dwRef >>= 1;	
	}
	return dwValue;
}



/*====================================================================
	函数名  	：TpGenCrc4ReTbl
	功能		：产生crc4余值表
	算法实现	：多项式模2除法:  g(x)=x4+x+1 
	引用全局变量：
	输入参数说明：
	返回值说明  ：
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
		wWord.m_wVal      = (u16)(wCurCh<<8); //取出有效字符
		for( byNum = 0; byNum < 12; byNum++)//除法运算时右面补4个0，即左移8＋4位
		{
			byCrc4Reg.m_byVal <<= 1;
			byCrc4Reg.bits.bit0 = (u8)wWord.bits.bit15;
			wWord.m_wVal      <<= 1;
			if(byCrc4Reg.bits.bit4) //最高位为1时才进行模2除法运算
			{
				byCrc4Reg.m_byVal = (u8)(byCrc4Reg.m_byVal^0x13);
			}
		}
		g_abyCrc4RemTbl[wCurCh] = byCrc4Reg.m_byVal&0x0f;//得到余数，即crc4码
	}

	return;
}


/*====================================================================
	函数名  	：TpGenCrc4Code
	功能		：快速查表法计算给定缓冲区内数据的crc4校验码
	算法实现	：多项式模2除法
	引用全局变量：
	输入参数说明：pbyBuf    数据缓冲区，必须是整字节
				  wDataLen  数据长度

	返回值说明  ：产生的crc4校验码，最右四位有效
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

