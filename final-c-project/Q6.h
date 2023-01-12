#ifndef __Q6_H
#define __Q6_H

#include "utils.h"
#include "bits_utils.h"

// Calculates the new value according to the gray level given.
int calcPNew(unsigned char p_value, unsigned char max_gray_level);

// Inserts the new value to the bytes array to the first available place according to the available bits and
// the amount of bites required.
void insertPNewToBytesArray(unsigned char new_p, unsigned char bits_required, BYTE* bytes_array,
	unsigned int* bytes_array_size, unsigned int* current_byte_available_bits);

// Writes the header of a compressed file (rows, cols and max gray level).
void writeHeaderToCompressed(FILE* fp, unsigned int* rows, unsigned int* cols, unsigned int* max_gray_level);

// Receives a file name to write, a gray image ref and max. gray level.
// Saves the image in a compressed form (as described in Q6) with the required file name.
void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel);
#endif