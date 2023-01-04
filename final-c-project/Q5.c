#include "Q5.h"

void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, int* rows, int* cols) {
	if (size == 0)
		return;

	IMG_POS_NODE* curr;
	int max_x = segments[0].head->position[X];
	int max_y = segments[0].head->position[Y];

	for (int i = 0; i < size; i++) {
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
	}
}

GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments,
	unsigned int size) {
	unsigned char gray_level;
	IMG_POS_NODE* current;
	GRAY_IMAGE* gray_image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));

	if (!gray_image)
		memoryAllocFailed();

	findMatrixSize(segments, size, &(gray_image->rows), &(gray_image->cols));
	
	allocatePixelsMatrix(gray_image);

	for (int i = 0; i < (int)size; i++) {
		gray_level = (i * 255) / (unsigned char)(size - 1); // Calculation described in Q5
		current = segments[i].head;

		while (current != NULL) {
			gray_image->pixels[current->position[X]][current->position[Y]] = gray_level;
			current = current->next;
		}
	}

	return gray_image;
}

