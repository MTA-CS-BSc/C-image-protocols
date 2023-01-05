#include "Q10.h"

void main() {
	//GRAY_IMAGE* iimg;
	//IMG_POS start = { 3, 15 };
	//iimg = readPGM("pgm.txt");

	////readPGM("pgm.txt");
	//printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);

	//convertPGMToBW("pgmTest.txt");

	COLOR_IMAGE* mat = readBinaryPPM("example4p6.ppm");

	printRGBMatrix(mat->pixels, mat->rows, mat->cols);
	/*IMG_POS_LIST** list = NULL;*/
	//IMG_POS_LIST* array = (IMG_POS_LIST*)malloc(sizeof(IMG_POS_LIST) * 4);

	//iimg = readPGM("pgm.txt");
	////printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
	//int size = findAllSegments(iimg, 10, &array);
	//iimg = colorSegments(array, size);
	//printGrayMatrix(iimg->pixels, iimg->rows, iimg->cols);
}