#ifndef __Q5_H
#define __Q5_H
#include "matrices_utils.h"
#include "utils.h"

// Receives a segments list ref and it's size.
// Returns a gray image ref with same gray level for each segment (calculated as described in Q5).
GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments, unsigned int size);
#endif