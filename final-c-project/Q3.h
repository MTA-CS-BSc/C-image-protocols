#ifndef __Q3_H
#define __Q3_H
#include "utils.h"

bool checkIfTresholdOk(unsigned char** pixels, IMG_POS n1, IMG_POS n2, int threshold);

bool** createPixelsFlagsMatrix(GRAY_IMAGE* img);

//void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
//	int threshold, bool** pixels_flags);

void findSingleSegmentHelper(GRAY_IMAGE* img, IMG_POS start,
	unsigned char threshold, bool** pixels_flags, TNODE* current_root);

SEGMENT findSingleSegment(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold);

#endif