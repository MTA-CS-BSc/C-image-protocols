#ifndef __Q4_H
#define __Q4_H
#include "utils.h"

void getImgPosListFromSegmentHelper(TNODE* root, IMG_POS_LIST* list);

IMG_POS_LIST* getImgPosListFromSegment(TNODE* segment_root);

int findAllSegments(GRAY_IMAGE* img, unsigned char threshold, IMG_POS_LIST** segments);

#endif