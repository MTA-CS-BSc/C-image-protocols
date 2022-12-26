#include "utils.h"

void memoryAllocFailed() {
	printf("Memory allocation failed!\n");
	exit(1);
}

void printMatrix(char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", mat[i][j]);
		}

		printf("\n");
	}
}

void skipLine(FILE* fp) {
	char current_char = fgetc(fp);

	while (current_char != '\n')
		current_char = fgetc(fp);
}

void skipCommentLines(FILE* fp, char current_char) {
	while (current_char == '#') {
		skipLine(fp);
		current_char = fgetc(fp);
	}
}

void makeEmptyTNodeList(TNODE_LIST* list) {
	list->head = list->tail = NULL;
}

TNODE* createTNode(IMG_POS point) {
	TNODE* node = (TNODE*)malloc(sizeof(TNODE));

	if (!node)
		memoryAllocFailed();

	node->position[X] = point[X];
	node->position[Y] = point[Y];
	makeEmptyTNodeList(&(node->nextPossiblePositions));

	return node;
}

bool isEmptyList(TNODE_LIST* list) {
	return list->head == NULL;
}

TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next) {
	TNODE_LNODE* lnode = (TNODE_LNODE*)malloc(sizeof(TNODE_LNODE));

	if (!lnode)
		memoryAllocFailed();

	lnode->node = data;
	lnode->next = next;

	return lnode;
}

void insertDataToEndList(TNODE_LIST* list, TNODE* data) {
	TNODE_LNODE* node = createTNodeLNode(data, NULL);

	if (isEmptyList(list))
		list->head = list->tail = node;

	else {
		list->tail->next = node;
		list->tail = node;
	}
}