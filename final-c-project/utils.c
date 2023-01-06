#include "utils.h"

char* readLineFromUser() {
	char* str;
	char ch;
	int physical_size = 0, len = 0;

	str = (char*)malloc(sizeof(char));

	if (!str)
		memoryAllocFailed();

	scanf(" %c", &ch);

	while (ch != '\n' && ch != '\0') {
		str = (char*)realloc(str, ++physical_size + 1);

		if (!str)
			memoryAllocFailed();

		str[len++] = ch;
		scanf("%c", &ch);
	}

	str[len] = '\0';

	return str;
}

void memoryAllocFailed() {
	printf("Memory allocation failed!\n");
	exit(1);
}

void freeRGBMat(RGB** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

void freeMat(char** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

char* getFirstTokenUntilDot(char* fname) {
	return strtok(fname, ".");
}

char* createNewFileExtension(char* fname, char* ext) {
	char* fname_dup = _strdup(fname);
	char* name_wo_ext = getFirstTokenUntilDot(fname_dup);
	char* new_file_name = (char*)malloc((strlen(name_wo_ext) + strlen(ext) + 1) * sizeof(char));

	if (!new_file_name)
		memoryAllocFailed();

	new_file_name[0] = '\0';

	strcat(new_file_name, name_wo_ext);
	strcat(new_file_name, ext);

	free(fname_dup);

	return new_file_name;
}

char* createPgmFileName(char* fname) {
	return createNewFileExtension(fname, ".pgm");
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
	bool entered = false;
	while (*current_char == '#') {
		entered = true;
		skipLine(fp);
		*current_char = fgetc(fp);
	}

	if (entered)
		fseek(fp, -1, SEEK_CUR);
}

void makeEmptyTNodeList(TNODE_LIST* list) {
	list->head = list->tail = NULL;
}

void makeEmptyImgPosList(IMG_POS_LIST* list) {
	list->head = list->tail = NULL;
}

bool isEmptyTNodeList(TNODE_LIST* list) {
	return list->head == NULL;
}

bool isEmptyImgPosList(IMG_POS_LIST* list) {
	return list->head == NULL;
}

char** createMatrix(int rows, int cols) {
	char** new_vals = (char**)malloc(sizeof(char*) * rows);

	if (!new_vals)
		memoryAllocFailed();

	for (int i = 0; i < rows; i++) {
		new_vals[i] = (char*)malloc(sizeof(char) * cols);

		if (!new_vals[i])
			memoryAllocFailed();
	}

	return new_vals;
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

void skipUntilOk(FILE* fp) {
	char current_char;

	skipLine(fp);
	current_char = fgetc(fp);

	if (current_char == '#')
		skipCommentLines(fp, &current_char);

	else
		fseek(fp, -1, SEEK_CUR);
}

void readHeaderFromPicFile(FILE* fp, int* rows, int* cols, int* depth) {
	char current_char = fgetc(fp);

	// There are two options:
	// First char can be #, or P

	if (current_char == '#') {
		skipCommentLines(fp, &current_char);
		current_char = fgetc(fp);
	}
		
	current_char = fgetc(fp);
	
	//if (current_char == '2' || current_char == '3') {
		skipUntilOk(fp);

		fscanf(fp, "%d %d", cols, rows);

		skipUntilOk(fp);

		fscanf(fp, "%d", depth);

		skipUntilOk(fp);
	//}
}

void insertNodeToEndTNodeList(TNODE_LIST* list, TNODE_LNODE* node) {
	if (isEmptyTNodeList(list))
		list->head = list->tail = node;

	else {
		list->tail->next = node;
		list->tail = node;
	}
}

void insertDataToEndTNodeList(TNODE_LIST* list, TNODE* data) {
	TNODE_LNODE* node = createTNodeLNode(data, NULL);
	insertNodeToEndTNodeList(list, node);
}

void insertNodeToEndImgPosList(IMG_POS_LIST* list, IMG_POS_NODE* node) {
	if (isEmptyImgPosList(list))
		list->head = list->tail = node;

	else {
		list->tail->next = node;
		node->prev = list->tail;
		node->next = NULL;
		list->tail = node;
	}


}

void insertDataToEndImgPosList(IMG_POS_LIST* list, IMG_POS data) {
	IMG_POS_NODE* node = createImgPosNode(data, NULL, NULL);
	insertNodeToEndImgPosList(list, node);
}

bool checkIfTresholdOk(GRAY_IMAGE* img, IMG_POS n1, IMG_POS n2, int threshold) {
	return (abs((img->pixels[n1[X]][n1[Y]] - img->pixels[n2[X]][n2[Y]])) <= threshold);
}

bool** createPixelsFlagsMatrix(GRAY_IMAGE* img) {
	bool** pixels_flags = (bool**)malloc(sizeof(bool*) * img->rows);

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

IMG_POS_NODE* createImgPosNode(IMG_POS data, IMG_POS_NODE* next, IMG_POS_NODE* prev) {
	IMG_POS_NODE* node = (IMG_POS_NODE*)malloc(sizeof(IMG_POS_NODE));

	if (!node)
		memoryAllocFailed();

	node->prev = prev;
	node->next = next;
	node->position[X] = data[X];
	node->position[Y] = data[Y];

	return node;
}

void freePixelsFlags(bool** flags, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		free(flags[i]);

	free(flags);
}
