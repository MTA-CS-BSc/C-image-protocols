#include "matrices_utils.h"

void freeRGBMat(RGB** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

void freeMat(char** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

void freeGrayImage(GRAY_IMAGE* img) {
	if (img) {
		if (img->pixels)
			freeMat(img->pixels, img->rows);

		free(img);
	}
}

void freeColorImage(COLOR_IMAGE* img) {
	if (img) {
		if (img->pixels)
			freeRGBMat(img->pixels, img->rows);

		free(img);
	}
}

void freePixelsFlags(bool** flags, int rows) {
	for (int i = 0; i < rows; i++)
		free(flags[i]);

	free(flags);
}

char** createMatrix(int rows, int cols) {
	char** new_vals = (char**)malloc(sizeof(char*) * rows);

	if (!new_vals)
		memoryAllocFailed();

	for (int i = 0; i < rows; i++) {
		new_vals[i] = (char*)malloc(cols * sizeof(char));

		if (!new_vals[i])
			memoryAllocFailed();

		for (int j = 0; j < cols; j++)
			new_vals[i][j] = 0;
	}

	return new_vals;
}

bool** createPixelsFlagsMatrix(GRAY_IMAGE* img) {
	bool** pixels_flags = (bool**)malloc(sizeof(bool*) * img->rows);

	if (!pixels_flags)
		memoryAllocFailed();

	for (int i = 0; i < img->rows; i++) {
		pixels_flags[i] = (bool*)malloc(sizeof(bool) * img->cols);

		if (!pixels_flags[i])
			memoryAllocFailed();

		for (int j = 0; j < img->cols; j++)
			pixels_flags[i][j] = false;
	}

	return pixels_flags;
}

void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, unsigned short* rows, unsigned short* cols) {
	if (size == 0)
		return;

	IMG_POS_NODE* curr;
	unsigned short max_x = segments[0].head->position[X];
	unsigned short max_y = segments[0].head->position[Y];

	for (unsigned i = 0; i < size; i++) {
		curr = segments[i].head;

		while (curr != NULL)
		{
			if (curr->position[X] > max_x)
				max_x = curr->position[X];

			if (curr->position[Y] > max_y)
				max_y = curr->position[Y];

			curr = curr->next;
		}

	}
	*rows = max_x + 1;
	*cols = max_y + 1;
}

void allocatePixelsMatrix(GRAY_IMAGE* img) {
	img->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * img->rows);

	if (!img->pixels)
		memoryAllocFailed();

	for (int i = 0; i < img->rows; i++) {
		img->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char) * img->cols);

		if (!img->pixels[i])
			memoryAllocFailed();

		for (int j = 0; j < img->cols; j++)
			img->pixels[i][j] = 0;
	}
}