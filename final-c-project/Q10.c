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

void convertPPMToPGM_Bin(char* fname) {
	int rows, cols, depth;
	char gray_level;
	FILE* ppm_fp = fopen(fname, "rb");
	char* new_fname = createPgmFileName(fname);
	FILE* pgm_fp = fopen(new_fname, "wb");
	COLOR_IMAGE* color_file = readBinaryPPM(fname);

	readHeaderFromPicFile(ppm_fp, &rows, &cols, &depth);

	fprintf(pgm_fp, "P5\n%d %d\n%d\n", rows, cols, depth);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gray_level = (color_file->pixels[i][j].r + color_file->pixels[i][j].g + color_file->pixels[i][j].b) / 3;
			fwrite(&gray_level, sizeof(unsigned char), 1, pgm_fp);
		}
	}

	fclose(ppm_fp);
	fclose(pgm_fp);
	free(new_fname);
}
