#include "Q5.h"

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

