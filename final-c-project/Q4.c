#include "Q4.h"

void getImgPosListFromSegmentHelper(TNODE* root, IMG_POS_LIST* list) {
	if (!root)
		return;

	TNODE_LNODE* current = root->nextPossiblePositions.head;
	insertDataToEndImgPosList(list, root->position);

	while (current != NULL) {
		getImgPosListFromSegmentHelper(current->node, list);
		current = current->next;
	}
		
}

IMG_POS_LIST* getImgPosListFromSegment(TNODE* segment_root) {
	IMG_POS_LIST *img_pos_list = (IMG_POS_LIST*)malloc(sizeof(IMG_POS_LIST));
	makeEmptyImgPosList(img_pos_list);

	getImgPosListFromSegmentHelper(segment_root, img_pos_list);

	return img_pos_list;
}

int findAllSegments(GRAY_IMAGE* img,
	unsigned char threshold, IMG_POS_LIST** segments) {
	bool** pixels_flags = createPixelsFlagsMatrix(img);
	IMG_POS current_pos;
	IMG_POS_LIST *current_img_pos_list;
	TNODE* current_root = NULL;
	int current_size = 0;
	segments = (IMG_POS_LIST**)malloc(sizeof(IMG_POS_LIST*) * (current_size + 1));

	if (!segments)
		memoryAllocFailed();


	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->cols; j++) {
			if (!pixels_flags[i][j]) {
				current_pos[X] = i;
				current_pos[Y] = j;

				current_root = createTNode(current_pos);
				pixels_flags[current_pos[X]][current_pos[Y]] = true;

				findSingleSegmentHelper(img, current_pos, threshold, pixels_flags, current_root);

				current_img_pos_list = getImgPosListFromSegment(current_root);
				segments = (IMG_POS_LIST**)realloc(segments, sizeof(IMG_POS_LIST*) * (current_size + 1));

				if (!segments)
					memoryAllocFailed();

				segments[current_size++] = current_img_pos_list;
				current_root = NULL;
			}
		}
	}

	return current_size;
}