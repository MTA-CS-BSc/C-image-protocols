#ifndef __Q3_H
#define __Q3_H
#include "lists_utils.h"
#include "matrices_utils.h"
#include "utils.h"

// Receives a gray image ref, a list root (TNODE), a start position and a threshold.
// Finds the relevant (threshold is ok) neighbors around the pixel and inserts them to the current_root children's list.
void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
	int threshold, bool** pixels_flags);

// A recursive implementation to find a single segment starting at a given start position with a given treshold.
// Each pixel is related to one segment only.
void findSingleSegmentHelper(GRAY_IMAGE* img, IMG_POS start,
	unsigned char threshold, bool** pixels_flags, TNODE* current_root);

// Receives a ref to a gray image, a start position and threshold.
// The function returns the relevant segment.
SEGMENT findSingleSegment(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold);
#endif