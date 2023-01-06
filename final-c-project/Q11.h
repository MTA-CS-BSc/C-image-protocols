#ifndef __Q11_H
#define __Q11_H
#include "utils.h"
#include "Q9.h"

void readDataFromBinaryPGM(FILE* fp, GRAY_IMAGE* gray_image);
GRAY_IMAGE* readBinaryPGM(char* fname);
void writeMatrixToBinaryFile(FILE* fp, unsigned char** mat, int rows, int cols);
void convertPGMToBW_Bin(char* fname);
#endif