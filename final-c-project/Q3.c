#include "Q3.h"

void findRelevantNeighbors(GRAY_IMAGE* img, TNODE* current_root, IMG_POS start,
	int threshold, bool** pixels_flags) {
	IMG_POS current;

	int iarr[MAX_NEIGHBORS] = { -1, -1, 0, +1, +1, +1, 0, -1 };
	int jarr[MAX_NEIGHBORS] = { 0, +1, +1, +1, 0, -1, -1, -1 };
	int x, y;

	for (int i = 0; i < MAX_NEIGHBORS; i++) {
		x = current_root->position[X] + iarr[i];
		y = current_root->position[Y] + jarr[i];

		if (isInRange(x, y, img)) {
			current[X] = x;
			current[Y] = y;
			if (checkIfTresholdOk(img, start,
					current, threshold) && !pixels_flags[x][y]) {
				pixels_flags[x][y] = true;
				insertDataToEndTNodeList(&(current_root->nextPossiblePositions), createTNode(current));
			}
		}
	}
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

	pixels_flags[start[X]][start[Y]] = true;

	findSingleSegmentHelper(img, start, threshold, pixels_flags, root);

	freePixelsFlags(pixels_flags, (int)img->rows, (int)img->cols);

	segment.root = root;
	return segment;
}

