#ifndef __Q4_H
#define __Q4_H
#include "utils.h"

int findAllSegments(GRAY_IMAGE* img,
	unsigned char threshold,
	IMG_POS_LIST** segments);

#endif