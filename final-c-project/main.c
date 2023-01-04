#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q9.h"
void main() {
	GRAY_IMAGE* iimg;
	IMG_POS start = { 3, 15 };
	iimg = readPGM("pgm.txt");

	//readPGM("pgm.txt");
	printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);

	convertPGMToBW("pgmTest.txt");
	/*IMG_POS_LIST** list = NULL;*/
	//IMG_POS_LIST* array = (IMG_POS_LIST*)malloc(sizeof(IMG_POS_LIST) * 4);

	//iimg = readPGM("pgm.txt");
	////printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
	//int size = findAllSegments(iimg, 10, &array);
	//iimg = colorSegments(array, size);
	//printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
}