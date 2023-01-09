#ifndef __MATRICES_UTILS_H
#define __MATRICES_UTILS_H
#include "utils.h"

// Receives a matrix and it's size. Frees it's values.
void freeRGBMat(RGB** matrix, int rows);

// Receives a matrix and it's size. Frees it's values.
void freeMat(char** matrix, int rows);

// Receives a gray image reference and frees it's pixels and the image.
void freeGrayImage(GRAY_IMAGE* img);

// Receives a color image reference and frees it's pixels and the image.
void freeColorImage(COLOR_IMAGE* img);

// Receives a matrix and it's size. Frees it's values.
void freePixelsFlags(bool** flags, int rows);

// Receives rows and cols amounts and returns a char matrix of the given size.
char** createMatrix(int rows, int cols);

// Receives a gray image reference and creates a pixels flags matrix according to the image's rows and cols amount.
bool** createPixelsFlagsMatrix(GRAY_IMAGE* img);

// Receives a segments list ref, it's size, and refs for rows and cols to update.
// Finds the maximum row number and col number.
// Assigns the numbers found + 1 for the rows and cols refs received.
void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, unsigned short* rows, unsigned short* cols);

// Receives a gray image ref and allocates it's pixels matrix with default values.
void allocatePixelsMatrix(GRAY_IMAGE* img);
#endif