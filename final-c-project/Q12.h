#ifndef __Q12_H
#define __Q12_H
#include "utils.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
//#include "Q6.h"
//#include "Q7.h"
#include "Q8.h"
#include "Q9.h"
#include "Q10.h"
#include "Q11.h"
#include <string.h>

void printMenu();
GRAY_IMAGE* readP2Image();
COLOR_IMAGE* readP3Image();
void findSegments(IMG_POS_LIST** segments, GRAY_IMAGE* p2_image, int* segments_amount);
GRAY_IMAGE* colorWithSameGrayLevel(IMG_POS_LIST** segments, GRAY_IMAGE* p2_image,
	int* segments_amount);
void saveGrayImageToP2(GRAY_IMAGE* p2_with_same_gray_level,
	char* file_name);
void saveSameGrayColoredToPgm(GRAY_IMAGE* p2_with_same_gray_level,
	IMG_POS_LIST** segments, GRAY_IMAGE* p2_image,
	int* segments_amount);
void convertP3ToP2();
void convertP2ToBW();
void convertP6ToP5();
void convertP5ToBW();
#endif