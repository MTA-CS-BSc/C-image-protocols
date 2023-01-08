#ifndef __Q5_H
#define __Q5_H
#include "utils.h"

// Receives a segments list ref, it's size, and refs for rows and cols to update.
// Finds the maximum row number and col number.
// Assigns the numbers found + 1 for the rows and cols refs received.
void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, unsigned short* rows, unsigned short* cols);

// Receives a gray image ref and allocates it's pixels matrix with default values.
void allocatePixelsMatrix(GRAY_IMAGE* img);

// Receives a segments list ref and it's size.
// Returns a gray image ref with same gray level for each segment (calculated as described in Q5).
GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments, unsigned int size);
#endif