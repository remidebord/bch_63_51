#include "misc.h"

char BitShiftLeft(int shift, unsigned char* data, int length)
{
	char tmp = 0;
	int i, j;
	
	char carry = 0;
	
	for(i = 0; i < shift; i++)
	{
		for(j = (length-1); j >= 0; j--)
		{
			tmp = (data[j] << 1) + carry;
			
			carry = ((data[j] & 0x80) != 0) ? 1 : 0;
			
			data[j] = tmp;
		}
	}
	
	return carry;
}

void PrintChar2Bits(unsigned char* buffer, int length)
{
	int i = 0;
	int j = 0;
	
	for(i = 0; i < length; i++)
	{
		for(j = 0; j < 8; j++)
		{
			printf("%d", ((buffer[i] & (0x80 >> j)) > 0)); 
		}
	}
}

void PrintInt2Bits(int value)
{
	int i = 0;
	
	for(i = 0; i < 32; i++)
	{
		if(i > (32-13)) printf("%d", ((value & (0x80000000 >> i)) > 0)); 
	}
}

void PrintLong2Bits(unsigned long long value)
{
	int i = 0;
	
	for(i = 0; i < 64; i++)
	{
		printf("%d", ((value & (0x8000000000000000 >> i)) > 0)); 
	}
}
