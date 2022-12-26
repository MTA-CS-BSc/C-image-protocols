#include "Q2.h"
#include "Q3.h"
void main() {
	GRAY_IMAGE * gi = readPGM("pgm.txt");
	IMG_POS start = { 3, 14 };

	printMatrix(gi->pixels, gi->rows, gi->cols);

	findSingleSegment(gi, start, 10);
}