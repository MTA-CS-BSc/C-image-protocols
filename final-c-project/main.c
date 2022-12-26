#include "Q1.h"
#include "Q2.h"
#include "Q3.h"

void main() {
	GRAY_IMAGE* iimg;
	IMG_POS start = { 3, 15 };
	iimg = readPGM("pgm.txt");
	printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
	findSingleSegment(iimg, start, 10);
}