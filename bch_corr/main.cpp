#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bch.h"

// Look up table of errors pattern
#include "bch_63_51_s_38_26.h"

//unsigned char codeword[] = {0x95, 0xC0, 0x05, 0xC5, 0x44}; // No errors
unsigned char codeword[] = {0x85, 0xC0, 0x05, 0xC5, 0x44}; // 1 error
//unsigned char codeword[] = {0x85, 0xC0, 0x15, 0xC5, 0x44}; // 2 errors
//unsigned char codeword[] = {0x95, 0xC0, 0x20, 0xC5, 0x44}; // 3 errors

unsigned char errorPatern[5] = "";

int main(int argc, char *argv[])
{
	unsigned int i = 0;
	unsigned int synd = 0;
	
	printf("\nReceived codeword: \t");
	
	PrintChar2Bits(codeword, 5);
	
	// Calculate syndrome
	synd = CalculateSyndrome(codeword, 5);
	
	printf(" | Syndrome: ");
	
	PrintInt2Bits(synd);
	
	printf(" (0x%X)", synd);
	
	printf("\n");
	
	// Errors ? (syndrom != 0)
	if(synd)
	{
		memcpy(errorPatern, s[synd], 5);
		
		// Error patern != 0
		if((errorPatern[0] != 0) || (errorPatern[1] != 0) || (errorPatern[2] != 0) || (errorPatern[3] != 0) || (errorPatern[4] != 0))
		{
			printf("Error pattern: \t\t");
			
			PrintChar2Bits(errorPatern, 5);
			
			// codeword XOR error patern
			for(i = 0; i < 5; i++)
			{
				codeword[i] = codeword[i] ^ errorPatern[i];
			}
			
			printf("\nCorrected codeword: \t");
			
			PrintChar2Bits(codeword, 5);
		}
		else
		{
			printf("\n=> /!\\ Fail to correct the received codeword (errors > 2)");
		}
	}
	else
	{
		printf("\n=> Well done, no errors !!!\n");
	}
	
	return 0;
}

