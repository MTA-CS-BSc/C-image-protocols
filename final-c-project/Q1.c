#include "Q1.h"

void readDataFromPPM(FILE* fp, COLOR_IMAGE* color_image, bool is_ascii) {
	color_image->pixels = (RGB**)malloc(sizeof(RGB*) * color_image->rows);

	if (!(color_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < color_image->rows; i++) {
		color_image->pixels[i] = (RGB*)malloc(sizeof(RGB) * color_image->cols);

		if (!(color_image->pixels[i]))
			memoryAllocFailed();

		for (int j = 0; j < color_image->cols; j++) {
			if (is_ascii)
				fscanf(fp, "%d %d %d", &(color_image->pixels[i][j]).r, &(color_image->pixels[i][j]).g, &(color_image->pixels[i][j]).b);

			else {
				fread(&(color_image->pixels[i][j].r), sizeof(unsigned char), 1, fp);
				fread(&(color_image->pixels[i][j].g), sizeof(unsigned char), 1, fp);
				fread(&(color_image->pixels[i][j].b), sizeof(unsigned char), 1, fp);
			}
		}

	}
}

COLOR_IMAGE* readPPMGeneric(char* fname, bool is_ascii) {
	FILE* fp = fopen(fname, is_ascii ? "r" : "rb");
	char current_char;
	int cols, rows, depth;
	COLOR_IMAGE* color_image = NULL;

	if (!fp)
		printf("Couldn't read file!\n");

	else {
		color_image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));

		if (!color_image)
			memoryAllocFailed();

		readHeaderFromPicFile(fp, &rows, &cols, &depth);

		color_image->cols = cols;
		color_image->rows = rows;
		color_image->pixels = NULL;

		readDataFromPPM(fp, color_image, is_ascii);

		fclose(fp);
	}

	return color_image;
}

COLOR_IMAGE* readPPM(char* fname) {
	return readPPMGeneric(fname, true);
}


