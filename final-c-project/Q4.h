#ifndef __Q4_H
#define __Q4_H
#include "utils.h"
#include "Q3.h"

// A recursive implementation to get the segment's positions from a given root.
void getImgPosListFromSegmentHelper(TNODE* root, IMG_POS_LIST* list);

// Receives a segment root and returns a list of the segment's positions.
IMG_POS_LIST getImgPosListFromSegment(TNODE* segment_root);

// Receives a gray image ref, a threshold and a reference to a segments array.
// Finds and updates the segments array using it's reference with all of the image's segments.
// Returns the amount of segments found.
int findAllSegments(GRAY_IMAGE* img, unsigned char threshold, IMG_POS_LIST** segments);

#endif