#include "utils.h"

void memoryAllocFailed() {
	printf("Memory allocation failed!\n");
	exit(1);
}

void printGrayMatrix(unsigned char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) 
			printf("%d ", mat[i][j]);

		printf("\n");
	}
}

void printRGBMatrix(RGB** arr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			printf("%d %d %d\t", arr[i][j].r, arr[i][j].g, arr[i][j].b);

		printf("\n");
	}
}

void skipLine(FILE* fp) {
	char current_char = fgetc(fp);

	while (current_char != '\n')
		current_char = fgetc(fp);
}

void skipCommentLines(FILE* fp, char *current_char) {
	while (*current_char == '#') {
		skipLine(fp);
		*current_char = fgetc(fp);
	}
}

void makeEmptyTNodeList(TNODE_LIST* list) {
	list->head = list->tail = NULL;
}

bool isEmptyList(TNODE_LIST* list) {
	return list->head == NULL;
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

TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next) {
	TNODE_LNODE* lnode = (TNODE_LNODE*)malloc(sizeof(TNODE_LNODE));

	if (!lnode)
		memoryAllocFailed();

	lnode->node = data;
	lnode->next = next;

	return lnode;
}

void readHeaderFromPicFile(FILE* fp, int* cols, int* rows, int* depth) {
	char current_char;

	// First we need to read the format of the file from the header:
	// There are two possible cases:
	// - The file can start with comments
	// - The file starts with the file format

	current_char = fgetc(fp);

	skipCommentLines(fp, &current_char);

	// Now we are standing on the format
	current_char = fgetc(fp); // Now current_char is holding the identifier

	if (current_char == '3' || current_char == '2') {
		// Now we need to get the rows and cols amount from the header

		skipLine(fp);
		current_char = fgetc(fp);

		skipCommentLines(fp, &current_char);

		// To go back to the beginning of the rows cols line
		fseek(fp, -1, SEEK_CUR);

		// Now we should be standing on the cols rows row
		fscanf(fp, "%d %d", cols, rows);

		skipLine(fp);
		current_char = fgetc(fp);

		skipCommentLines(fp, &current_char);

		fseek(fp, -1, SEEK_CUR);
		fscanf(fp, "%d", depth);

		skipLine(fp);

		skipCommentLines(fp, &current_char);

		// Now we're standing at the beginning of the data
	}
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