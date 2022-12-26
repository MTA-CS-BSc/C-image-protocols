#include "Q2.h"

void readDataFromPGM(FILE* fp, GRAY_IMAGE* gray_image) {
	gray_image->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * gray_image->rows);
	
	if (!(gray_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < gray_image->rows; i++) {
		gray_image->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char) * gray_image->cols);

		if (!(gray_image->pixels[i]))
			memoryAllocFailed();

		for (int j = 0; j < gray_image->cols; j++)
			fscanf(fp, "%d", &(gray_image->pixels[i][j]));
	}
		
}

GRAY_IMAGE* readPGM(char* fname) {
	FILE* fp = fopen(fname, "r");
	char current_char;
	int cols, rows, depth;
	GRAY_IMAGE *gray_image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));

	if (!gray_image)
		memoryAllocFailed();

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPicFile(fp, &cols, &rows, &depth);

	gray_image->cols = cols;
	gray_image->rows = rows;

	readDataFromPGM(fp, gray_image);

	fclose(fp);

	return gray_image;
}
