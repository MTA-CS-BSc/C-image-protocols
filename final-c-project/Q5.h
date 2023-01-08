#ifndef __Q5_H
#define __Q5_H
#include "utils.h"

void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, unsigned short* rows, unsigned short* cols);

void allocatePixelsMatrix(GRAY_IMAGE* img);

GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments, unsigned int size);

#endif