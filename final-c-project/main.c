#include "Q1.h"
#include "Q2.h"

void main() {
	COLOR_IMAGE* iimg;
	iimg = readPPM("ppm.txt");
	printRGBMatrix(iimg->pixels, iimg->rows, iimg->cols);
}