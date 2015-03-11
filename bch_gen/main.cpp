#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "bch.h"

#define USE_DEBUG

using namespace std;

// Codeword = data (26 bits) + ecc (12 bits) = 38 bits

unsigned char s[4096][5]; 	// 2^12 = 4096 (ecc => 12 bits)
unsigned char data[5] = ""; //  38 bits => 4.75 bytes => 5 bytes

// Text file
std::string filenameSyndromArray = "bch_63_51_s_38_26.h";
std::ofstream fileSyndromArray;

int main(int argc, char *argv[])
{
	clock_t time = clock();
	
	unsigned int i = 0;
	unsigned int synd = 0;
	
	unsigned long long a = 1;
	unsigned long long b = 0;
	unsigned long long c = 0;
	
	// Open the file in write mode
    fileSyndromArray.open(filenameSyndromArray.c_str(), ios::trunc | ios::out);
    
    fileSyndromArray << "/* Generate a look up table in order to decode and correct any bch(38,26) which is a shortened form of bch(63,51)." << endl;
    fileSyndromArray << "   This BCH error correcting code (ecc) permit to correcting up to 2 errors max." << endl << endl;
    fileSyndromArray << "   The generator polynomial used as a basis for this code is: \n" << endl << "   g(x) = (1 + x + x6) (1 + x + x2 + x4+ x6)" << endl;
	fileSyndromArray << "        = (1 + x3 + x4 + x5 + x8 + x10 + x12)" << endl << endl;
	fileSyndromArray << "   Which can be traduct by 1010100111001" << endl << endl;
    fileSyndromArray << "   The generator polynomial can be find with Matlab or in \"Error Correcting Code\" by Shu Lin and Daniel J. Costello, Jr (Appendix C)." << endl << endl;
    fileSyndromArray << "   Matlab example: " << endl << endl;
	fileSyndromArray << "   \t% BCH[63,51] => m = 6 and k = 51\n" << endl << "   \tm = 6;" << endl << "   \tn = 2^m-1; % Codeword length (total length)" << endl << "   \tk = 51; % Message length\n" << endl;
	fileSyndromArray << "	% Get generator polynomial and error-correction capability." << endl << "   \t[genpoly,t] = bchgenpoly(n,k)" << endl;
	fileSyndromArray << "*/" << endl << endl;
    
    fileSyndromArray << "unsigned char s[4096][5] = \n{" << endl;
	
	cout << "Generate error paterns array..." << endl;
	
	// Syndromes computation
	while(c != 0x3000000000)
	{
		// Generate error patterns
		c = a | b;
		
		if(b != (a >> 1))
		{
			if(b)
			{
				b = b << 1;
			}
			else
			{
				b = 1;
			}
		}
		else
		{
			a = a << 1;
			b = 0;
		}
		
		i++;
		
		// Compute syndrome (c is shifted of 2 bits, because data are left aligned)
		data[0] = ((c << 2) & 0x000000FF00000000) >> 32;
		data[1] = ((c << 2) & 0x00000000FF000000) >> 24;
		data[2] = ((c << 2) & 0x0000000000FF0000) >> 16;
		data[3] = ((c << 2) & 0x000000000000FF00) >> 8;
		data[4] = ((c << 2) & 0x00000000000000FF);
		
		synd = CalculateSyndrome(data, 5);
		
#ifdef USE_DEBUG
		PrintChar2Bits(data, 5);	
		
		printf(" | ");
		
		PrintInt2Bits(synd);
		
		printf("\n");
#endif
		
		// Insert syndrome into syndrome array
		memcpy(s[synd], data, 5);
	}
	
	printf("\nIterations: %d\n", i);
	
	// Insert errorPatern(syndrom) into text file
	for(i = 0; i < 4096; i++)
	{
		char buffer[256] = "";
		
		sprintf(buffer, "0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X, 0x%.2X", s[i][0], s[i][1], s[i][2], s[i][3], s[i][4]);
		
		if(i != (4096-1)) 
		{
			fileSyndromArray << buffer << "," << endl;
		}
		else
		{
			fileSyndromArray << buffer << endl << "};" << endl;
		}
	}
	
	fileSyndromArray.close();
	
	cout << "\nFile " << filenameSyndromArray.c_str() << " is generated !" << endl; 
	
	cout << "\nFinish ! (" << ((clock() - time) / (double) (CLOCKS_PER_SEC / 1000)) << " ms)\n";
	
	return 0;
}

