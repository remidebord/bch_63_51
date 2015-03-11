#include "bch.h"

unsigned int CalculateBCH2(unsigned char* data, int length)
{
	unsigned char buffer[20] = "";
	
	unsigned int m = 0;
	unsigned int g = 0x00001539; // 1010100111001
	unsigned int r = 0;
	
	int i;
	
    for(i = 0; i < 4; i++) buffer[i] = data[i];

    buffer[3] = buffer[3] & 0xC0;
	
	for(i = 0; i < 26; i++)
	{
		if((buffer[0] & 0x80) != 0)
		{
			//PrintChar2Bits(buffer, length);
			
			m = (buffer[0] << 5) + (buffer[1] >> 3);
			
			r = m ^ g;
			
			buffer[0] = (r >> 5) & 0x00FF;
			buffer[1] = ((r << 3) & 0x00FF) + (buffer[1] & 0x07);
			
			//PrintInt2Bits(m);
			//PrintInt2Bits(g);
			//PrintInt2Bits(r);
			//printf("i = %d\n\n", i);
		}
		
		if(i != 25)
		{
			//printf("Shift (%d)!\n", i);
			BitShiftLeft(1, buffer, length);
		}
	}
	
	r = (buffer[0] << 5) + (buffer[1] >> 3);
	
	return r;
}

unsigned int CalculateSyndrome(unsigned char* data, int length)
{
	unsigned char buffer[20] = "";
	
	unsigned int m = 0;
	unsigned int g = 0x00001539; // 1010100111001
	unsigned int r = 0;
	
	int i;
	
    for(i = 0; i < 5; i++) buffer[i] = data[i];
	
	for(i = 0; i < 26; i++)
	{		
		if((buffer[0] & 0x80) != 0)
		{
			//PrintChar2Bits(buffer, length);
			
			m = (buffer[0] << 5) + (buffer[1] >> 3);
			
			r = m ^ g;
			
			buffer[0] = (r >> 5) & 0x00FF;
			buffer[1] = ((r << 3) & 0x00FF) + (buffer[1] & 0x07);
			
			//PrintInt2Bits(m);
			//PrintInt2Bits(g);
			//PrintInt2Bits(r);
			//printf("i = %d\n\n", i);
			
			//PrintInt2Bits(r);
			//printf("\n");
		}
		
		if(i != 25)
		{
			//printf("Shift (%d)!\n", i);
			BitShiftLeft(1, buffer, length);
		}
		
		//PrintChar2Bits(buffer, length);
		//printf("\n");
	}
	
	r = (buffer[0] << 5) + (buffer[1] >> 3);
	
	return r;
}
