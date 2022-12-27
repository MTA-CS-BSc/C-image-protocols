#include "Q5.h"

void findMatrixSize(IMG_POS_LIST* segments, unsigned int size, int* maxX, int* maxY)
{
	IMG_POS_NODE * curr;
	int i;
	if (size == 0)
		return;
	int max_x = segments[0].head->position[X];
	int max_y = segments[0].head->position[Y];

	for (i = 0; i < size; i++)
	{
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
	*maxX = max_x;
	*maxY = max_y;
	
}
unsigned char calSegmentGrayLevel(int i, unsigned int size)
{
	return ((unsigned char)(i * 255) / (size - 1));
}

GRAY_IMAGE* colorSegments(IMG_POS_LIST* segments,
	unsigned int size) {
	int i;
	unsigned char grayLevel;
	IMG_POS_NODE* curr;

	GRAY_IMAGE* gray_image;
	gray_image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));
	if (!gray_image)
		memoryAllocFailed();
	findMatrixSize(segments, size, &(gray_image->rows), &(gray_image->cols));
	gray_image->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * gray_image->rows);
	if (!gray_image->pixels)
		memoryAllocFailed();
	for (i = 0; i < gray_image->rows; i++)
	{
		gray_image->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char) * gray_image->cols);
		if (!gray_image->pixels[i])
			memoryAllocFailed();
	}

	for (i = 0; i < size; i++)
	{
		grayLevel = calSegmentGrayLevel(i, size);
		curr = segments[i].head;
		while (curr != NULL)
		{
			gray_image->pixels[curr->position[X]][curr->position[Y]] = grayLevel;
			curr = curr->next;
		}
	}

	return gray_image;



}

