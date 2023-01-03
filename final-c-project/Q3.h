#ifndef __Q3_H
#define __Q3_H
#include "utils.h"
#define MAX_NEIGHBORS 8

void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
	int threshold, bool** pixels_flags);

void findSingleSegmentHelper(GRAY_IMAGE* img, IMG_POS start,
	unsigned char threshold, bool** pixels_flags, TNODE* current_root);

SEGMENT findSingleSegment(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold);

#endif