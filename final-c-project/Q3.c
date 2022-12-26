#include "Q3.h"

bool checkIfTresholdOk(unsigned char** pixels, IMG_POS n1, IMG_POS n2, int threshold) {
	return ((pixels[n1[X]][n1[Y]] - pixels[n2[X]][n2[Y]]) <= threshold);
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

//void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
//	int threshold, bool** pixels_flags) {
//	IMG_POS current;
//	int i = current_root->position[X];
//	int j = current_root->position[Y];
//
//	for (int x = max(0, i - 1); x <= min(i + 1, img->rows); x++) {
//		for (int y = max(0, j - 1); y <= min(j + 1, img->cols); y++) {
//			if (x != i || y != j) {
//				current[X] = x;
//				current[Y] = y;
//
//				if (checkIfTresholdOk(img->pixels, start,
//						current, threshold) && !pixels_flags[x][y]) {
//					pixels_flags[x][y] = true;
//					insertDataToEndList(&(current_root->nextPossiblePositions), createTNode(current));
//				}
//			}
//		}
//	}
//}

void findSingleSegmentHelper(GRAY_IMAGE* img, IMG_POS start,
	unsigned char threshold, bool** pixels_flags, TNODE* current_root) {
	TNODE_LNODE* current_neighbor;

	IMG_POS current;
	int i = current_root->position[X];
	int j = current_root->position[Y];

	for (int x = max(0, i - 1); x < min(i + 1, img->rows); x++) {
		for (int y = max(0, j - 1); y < min(j + 1, img->cols); y++) {
			if (x != i || y != j) {
				current[X] = x;
				current[Y] = y;

				if (checkIfTresholdOk(img->pixels, start,
					current, threshold) && !pixels_flags[x][y]) {
					pixels_flags[x][y] = true;
					insertDataToEndList(&(current_root->nextPossiblePositions), createTNode(current));
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
	SEGMENT segment;
	bool** pixels_flags = createPixelsFlagsMatrix(img);
	TNODE* root = createTNode(start);

	makeEmptyTNodeList(&(root->nextPossiblePositions));
	pixels_flags[start[X]][start[Y]] = true;

	findSingleSegmentHelper(img, start, threshold, pixels_flags, root);

	segment.root = root;
	return segment;
}
