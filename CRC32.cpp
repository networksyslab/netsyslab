#include "stdafx.h"
#include "CRC32.h"
#include <stdlib.h>

void makeCRC32table(unsigned int table[])
{
	int i,j;
	unsigned int c;
	unsigned int poly = 0x04C11DB7;     // CRC32 다항식
	for(i=0; i<256; i++)
	{
		c=i;
		c<<=24;
		for(j=0; j<8; j++)
		{			
			c=(c&0x80000000)?poly^(c<<1):(c<<1);
		}
		table[i]=c;
		//printf("0x%08X ", table[i]);
	}
}

unsigned int calculCRC32(unsigned char data[], unsigned int table[], unsigned short packetlength)
{
	int i;
	unsigned int c=0x00000000;
	for(i=0; i<packetlength; i++)
	{
		c=table[(data[i]^c>>24)&0xFF]^c<<8;
	}
	printf("계산 결과 CRC는 0x%08X\n", c);
	return c;
}

void addCRC32(unsigned char data[], unsigned int crc, unsigned short packetlength)
{
	int i;
	for(i=0; i<4; i++)
	{
		unsigned char c=0;
		c=c^crc>>8*(3-i);
		data[packetlength+i]=c;
		//printf("0x%02X ", data[packetlength+i]);
	}
	//printf("\n");
}

// CRC8table 작성
void makeCRC8table(unsigned char table[])
{
	int i,j;
	static unsigned char poly=0x07;      // CRC-8 다항식
	static unsigned char c;
	for(i=0; i<256; i++)
	{
		c = i;
		for(j=0; j<8; j++)
		{
			if(c&0x80)
			{
				c <<= 1;
				c ^= poly;
			}
			else
				c <<= 1;
		}
		table[i] = c;
		//printf("0x%02X ", table[i]);
	}
	//printf("\n");
}

// CRC8 계산
unsigned char calculCRC8(unsigned char data[], unsigned char table[], unsigned short packetlength)
{
	int i;
	unsigned int c=0x00000000;
	for(i=0; i<packetlength; i++)
	{
		c=table[(data[i]^c)];
	}
	printf("계산 결과 CRC는 0x%02X\n", c);
	return c;
}