#ifndef __Q6_H
#define __Q6_H

#include "utils.h"
#include "Q9.h"
#include <math.h>
typedef unsigned char BYTE;

// Calculates the new value according to the gray level given.
int calcPNew(unsigned char p_value, unsigned char max_gray_level);

// Returns 0 if the I-th bit is not set, not 0 otherwise (translated as bool).
int isIBitSet(BYTE ch, int i);

// Returns the amount of bits without the leading zeros required for a number.
int amountOfBitsNeeded(unsigned char max_gray_level);

// Inserts the new value to the bytes array to the first available place according to the available bits and
// the amount of bites required.
void insertNewPToBytesArray(unsigned char new_p, unsigned char bits_required, BYTE** bytes_array,
	unsigned int* bytes_array_size, unsigned int* current_byte_available_bits);

// Receives a file name to write, a gray image ref and max. gray level.
// Saves the image in a compressed form (as described in Q6) with the required file name.
void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel);
#endif