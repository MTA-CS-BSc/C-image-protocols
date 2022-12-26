#include "Q3.h"

//unsigned char abs(char number) {
//	return number >= 0 ? number : -number;
//}
#include <math.h>

bool checkIfTresholdOk(unsigned char** pixels, IMG_POS n1, IMG_POS n2, int threshold) {
	return (pixels[n1[X]][n1[Y]] - pixels[n2[X]][n2[Y]] <= threshold);
}

bool isInRange(GRAY_IMAGE* img, IMG_POS current) {
	if (current[X] < 0 || current[X] >= img->rows || current[Y] < 0 || current[Y] >= img->cols)
		return false;

	return true;
}

void findSingleSegmentHelper(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold, bool** pixels_flags,
	TNODE* current_root) {

	IMG_POS current;
	TNODE_LNODE* current_neighbor;

	int i = current_root->position[X];
	int j = current_root->position[Y];

	if (img->rows > 0) {
		for (int x = max(0, i - 1); x <= min(i + 1, img->rows); x++) {
			for (int y = max(0, j - 1); y <= min(j + 1, img->cols); y++) {
				if (x != i || y != j) {
					current[X] = x;
					current[Y] = y;

					if (checkIfTresholdOk(img->pixels, start, current, threshold)
						&& !pixels_flags[x][y]) {
						pixels_flags[x][y] = true;
						insertDataToEndList(&(current_root->nextPossiblePositions), createTNode(current));
					}
				}
			}
		}
	}

	current_neighbor = current_root->nextPossiblePositions.head;

	while (current_neighbor != NULL) {
		findSingleSegmentHelper(img,start, threshold, pixels_flags, current_neighbor->node);
		current_neighbor = current_neighbor->next;
	}
}

SEGMENT findSingleSegment(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold) {
	TNODE* root = NULL;
	SEGMENT segment;
	bool** pixels_flags = (bool**)malloc(sizeof(bool*) * img->rows);
	
	if (!pixels_flags)
		memoryAllocFailed();

	root = createTNode(start);
	makeEmptyTNodeList(&(root->nextPossiblePositions));

	for (int i = 0; i < img->rows; i++) {
		pixels_flags[i] = (bool*)malloc(sizeof(bool) * img->cols);
		
		if (!pixels_flags[i])
			memoryAllocFailed();

		for (int j = 0; j < img->cols; j++)
			pixels_flags[i][j] = false;
	}

	pixels_flags[start[X]][start[Y]] = true;
	findSingleSegmentHelper(img, start, threshold, pixels_flags, root);

	segment.root = root;
	return segment;
}