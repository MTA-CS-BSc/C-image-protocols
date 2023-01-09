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

IMG_POS_LIST getImgPosListFromSegment(TNODE* segment_root) {
	IMG_POS_LIST img_pos_list;
	makeEmptyImgPosList(&img_pos_list);

	getImgPosListFromSegmentHelper(segment_root, &img_pos_list);

	return img_pos_list;
}

int findAllSegments(GRAY_IMAGE* img,
	unsigned char threshold, IMG_POS_LIST** segments) {
	bool** pixels_flags = createPixelsFlagsMatrix(img);
	IMG_POS current_pos;
	IMG_POS_LIST current_img_pos_list;
	TNODE* current_root = NULL;
	int current_size = 0;
	IMG_POS_LIST* returned_array_of_lists;

	returned_array_of_lists = (IMG_POS_LIST*)malloc(sizeof(IMG_POS_LIST) * (current_size + 1));

	if (!returned_array_of_lists)
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
				returned_array_of_lists = (IMG_POS_LIST*)realloc(returned_array_of_lists, sizeof(IMG_POS_LIST) * (current_size + 1));

				if (!returned_array_of_lists)
					memoryAllocFailed();

				returned_array_of_lists[current_size++] = current_img_pos_list;
				freeTNodeList(&(current_root->nextPossiblePositions));
				current_root = NULL;
			}
		}
	}

	freePixelsFlags(pixels_flags, (int)img->rows);
	*segments = returned_array_of_lists;
	return current_size;
}