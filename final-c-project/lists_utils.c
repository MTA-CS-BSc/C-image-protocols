#include "lists_utils.h"

void freeTNodeList(TNODE_LIST* list) {
	TNODE_LNODE* current = list->head;
	TNODE_LNODE* saver;
	while (current != NULL) {
		saver = current->next;
		freeTNodeList(&(current->node->nextPossiblePositions));
		free(current);
		current = saver;
	}
}

void freeImgPosList(IMG_POS_LIST* list) {
	IMG_POS_NODE* current = list->head, *saver;

	while (current != NULL) {
		saver = current->next;
		free(current);
		current = saver;
	}
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