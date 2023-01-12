#ifndef __Q7_H
#define __Q7_H

#include "utils.h"
#include "bits_utils.h"
#include "matrices_utils.h"

void getHeaderFromCompressed(FILE* compressed, unsigned int* rows, unsigned int* cols, unsigned char* max_gray_level);
void insertDataToMat(BYTE* current_byte,
    unsigned int* bits_read_from_current_byte, unsigned char* required_bits,
    unsigned int* bit_counter, unsigned int* bits_read_for_current_insert_index,
    char** matrix, int* insert_i, int* insert_j, int cols, FILE* fp);
void convertCompressedToPGM(char* fname);
#endif