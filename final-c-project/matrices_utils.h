#ifndef __MATRICES_UTILS_H
#define __MATRICES_UTILS_H
#include "utils.h"

void freeRGBMat(RGB** matrix, int rows);
void freeMat(char** matrix, int rows);
void freePixelsFlags(bool** flags, int rows);
void printGrayMatrix(unsigned char** mat, int rows, int cols);
void printRGBMatrix(RGB** arr, int rows, int cols);
char** createMatrix(int rows, int cols);
bool** createPixelsFlagsMatrix(GRAY_IMAGE* img);

// Receives a segments list ref, it's size, and refs for rows and cols to update.
// Finds the maximum row number and col number.
// Assigns the numbers found + 1 for the rows and cols refs received.
void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, unsigned short* rows, unsigned short* cols);

// Receives a gray image ref and allocates it's pixels matrix with default values.
void allocatePixelsMatrix(GRAY_IMAGE* img);
#endif