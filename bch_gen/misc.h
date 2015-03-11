#ifndef __MISC_H
#define __MISC_H

/* includes ----------------------------------------------------------------- */
#include <stdio.h>

/* defines ------------------------------------------------------------------ */

char BitShiftLeft(int shift, unsigned char* data, int length);
int BitWeight(unsigned long long value);
void PrintChar2Bits(unsigned char* buffer, int length);
void PrintInt2Bits(int value);
void PrintLong2Bits(unsigned long long value);

#endif
