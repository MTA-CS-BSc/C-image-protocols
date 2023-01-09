#ifndef __Q6_H
#define __Q6_H

#include "utils.h"
#include "Q9.h"
#include <math.h>
typedef unsigned char BYTE;
// BYTE* arr, int size_arr, int amount_of_bits
// 
// Of type BYTE, actual_size
// fwrite(&bytes[i], sizeof(unsigned char), bytes_length, fp);

void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel);
#endif