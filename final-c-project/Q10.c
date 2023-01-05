#include "Q10.h"

void readDataFromBinaryPPM(FILE* fp, COLOR_IMAGE* color_image) {
	color_image->pixels = (RGB**)malloc(sizeof(RGB*) * color_image->rows);

	if (!(color_image->pixels))
		memoryAllocFailed();
	
	for (int i = 0; i < color_image->rows; i++) {
		color_image->pixels[i] = (RGB*)malloc(sizeof(RGB) * color_image->cols);

		if (!(color_image->pixels[i]))
			memoryAllocFailed();
	}

	for (int i = 0; i < color_image->rows; i++)
	{
		for (int j = 0; j < color_image->cols; j++) {
			fread(&(color_image->pixels[i][j].r), sizeof(unsigned char), 1, fp);
			fread(&(color_image->pixels[i][j].g), sizeof(unsigned char), 1, fp);
			fread(&(color_image->pixels[i][j].b), sizeof(unsigned char), 1, fp);
		}

	}
}

COLOR_IMAGE* readBinaryPPM(char* fname) {
	FILE* fp = fopen(fname, "rb");
	char current_char;
	int cols, rows, depth;
	COLOR_IMAGE* color_image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));

	if (!color_image)
		memoryAllocFailed();

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPicFile(fp, &rows, &cols, &depth);

	color_image->cols = cols;
	color_image->rows = rows;

	readDataFromBinaryPPM(fp, color_image);

	fclose(fp);

	return color_image;
}