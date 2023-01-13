#ifndef __Q7_H
#define __Q7_H

#include "utils.h"
#include "bits_utils.h"

// Receives a compreesed file ref and rows, cols and max gray level refs.
// Reads the rows, cols and max gray level data from the file's header to the given arguments.
void getHeaderFromCompressed(FILE* compressed, unsigned int* rows, unsigned int* cols, unsigned char* max_gray_level);

// Inserts the data from the current byte to the p2 file according to the amount of required bits for each number.
// If any data is present in the matrix's given index, it's shifted left to concat the bits.
void getDataFromByte(BYTE* current_byte, int* current_number,
    unsigned int* bits_read_from_current_byte, unsigned char* required_bits,
    unsigned int* bit_counter, unsigned int* bits_read_for_current_insert_index,
    int* insert_j, int cols, FILE* fp, FILE* p2);

// Receives a compressed binary file name and converts it to a P2 PGM.
void convertCompressedToPGM(char* fname);
#endif