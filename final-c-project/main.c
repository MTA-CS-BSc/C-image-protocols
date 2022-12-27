#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"

void main() {
	GRAY_IMAGE* iimg;
	IMG_POS start = { 3, 15 };
	IMG_POS_LIST** list = NULL;

	iimg = readPGM("pgm.txt");
	//printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
	findAllSegments(iimg, 10, list);
}