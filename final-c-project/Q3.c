#include "Q3.h"
#include <math.h>

bool checkIfTresholdOk(GRAY_IMAGE* img, IMG_POS n1, IMG_POS n2, int threshold) {
	return ((img->pixels[n1[X]][n1[Y]] - img->pixels[n2[X]][n2[Y]]) <= threshold);
}

bool** createPixelsFlagsMatrix(GRAY_IMAGE* img) {
	bool ** pixels_flags = (bool**)malloc(sizeof(bool*) * img->rows);

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

bool isInRange(int row, int col, GRAY_IMAGE* img) {
	return (row >= 0 && row < img->rows&& col >= 0 && col < img->cols);
}
void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
	int threshold, bool** pixels_flags) {
	IMG_POS current;

	int iarr[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };
	int jarr[8] = { 0, +1, +1, +1, 0, -1, -1, -1 };
	int x, y;

	for (int i = 0; i < 8; i++) {
		x = current_root->position[X] + iarr[i];
		y = current_root->position[Y] + jarr[i];

		if (isInRange(x, y, img)) {
			current[X] = x;
			current[Y] = y;
			if (checkIfTresholdOk(img, start,
					current, threshold) && !pixels_flags[x][y]) {
				pixels_flags[x][y] = true;
				insertDataToEndList(&(current_root->nextPossiblePositions), createTNode(current));
			}
		}


	}
	//for (int x = max(0, i - 1); x <= min(i + 1, img->rows - 1); x++) {
	//	for (int y = max(0, j - 1); y <= min(j + 1, img->cols - 1); y++) {
	//		if (x != i || y != j) {
	//			current[X] = x;
	//			current[Y] = y;

	//			if (checkIfTresholdOk(img, start,
	//					current, threshold) && !pixels_flags[x][y]) {
	//				pixels_flags[x][y] = true;
	//				insertDataToEndList(&(current_root->nextPossiblePositions), createTNode(current));
	//			}
	//		}
	//	}
	//}
}

void findSingleSegmentHelper(GRAY_IMAGE* img, IMG_POS start,
	unsigned char threshold, bool** pixels_flags, TNODE* current_root) {
	TNODE_LNODE* current_neighbor;

	findRelevantNeighbors(img, current_root, start, threshold, pixels_flags);

	current_neighbor = current_root->nextPossiblePositions.head;

	while (current_neighbor != NULL) {
		findSingleSegmentHelper(img,start, threshold, pixels_flags, current_neighbor->node);
		current_neighbor = current_neighbor->next;
	}
}

SEGMENT findSingleSegment(GRAY_IMAGE* img,
	IMG_POS start, unsigned char threshold) {
	SEGMENT segment;
	bool** pixels_flags = createPixelsFlagsMatrix(img);
	TNODE* root = createTNode(start);

	makeEmptyTNodeList(&(root->nextPossiblePositions));
	pixels_flags[start[X]][start[Y]] = true;

	findSingleSegmentHelper(img, start, threshold, pixels_flags, root);

	segment.root = root;
	return segment;
}
