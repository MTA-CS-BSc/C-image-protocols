#include "utils.h"
#include "Q2.h"

void readDataFromPPM(FILE* fp, COLOR_IMAGE* color_image) {
	color_image->pixels = (RGB**)malloc(sizeof(RGB*) * color_image->rows);

	if (!(color_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < color_image->rows; i++) {
		color_image->pixels[i] = (RGB*)malloc(sizeof(RGB) * color_image->cols);

		if (!(color_image->pixels[i]))
			memoryAllocFailed();

		for (int j = 0; j < color_image->cols; j++)
			fscanf(fp, "%d %d %d", &(color_image->pixels[i][j]).r, &(color_image->pixels[i][j]).g, &(color_image->pixels[i][j]).b);
	}		
}

COLOR_IMAGE* readPPM(char* fname) {
	FILE* fp = fopen(fname, "r");
	char current_char;
	int cols, rows, depth;
	COLOR_IMAGE* color_image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));

	if (!color_image)
		memoryAllocFailed();

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPicFile(fp, &cols, &rows, &depth);

	color_image->cols = cols;
	color_image->rows = rows;

	readDataFromPPM(fp, color_image);

	fclose(fp);

	return color_image;
}


