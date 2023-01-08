#include "Q2.h"

void readDataFromPGM(FILE* fp, GRAY_IMAGE* gray_image, bool is_ascii) {
	gray_image->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * gray_image->rows);

	if (!(gray_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < gray_image->rows; i++) {
		gray_image->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char) * gray_image->cols);

		if (!(gray_image->pixels[i]))
			memoryAllocFailed();

		for (int j = 0; j < gray_image->cols; j++) {
			if (is_ascii)
				fscanf(fp, "%d", &(gray_image->pixels[i][j]));

			else
				fread(&(gray_image->pixels[i][j]), sizeof(unsigned char), 1, fp);
		}
	}
}

GRAY_IMAGE* readPGMGeneric(char* fname, bool is_ascii) {
	FILE* fp = fopen(fname, is_ascii ? "r" : "rb");
	char current_char;
	int cols, rows, depth;
	GRAY_IMAGE* gray_image = NULL;

	if (!fp)
		printf("Couldn't read file!\n");
		//exit(1);

	else {
		gray_image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));

		if (!gray_image)
			memoryAllocFailed();

		readHeaderFromPicFile(fp, &rows, &cols, &depth);

		gray_image->cols = cols;
		gray_image->rows = rows;
		gray_image->pixels = NULL;

		readDataFromPGM(fp, gray_image, is_ascii);

		fclose(fp);
	}

	return gray_image;
}

GRAY_IMAGE* readPGM(char* fname) {
	return readPGMGeneric(fname, true);
}
