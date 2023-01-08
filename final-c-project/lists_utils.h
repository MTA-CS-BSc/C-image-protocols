#ifndef __LISTS_UTILS_H
#define __LISTS_UTILS_H
#include "utils.h"

// Frees a list of TNODE_LIST.
void freeTNodeList(TNODE_LIST* list);

// Frees a list of IMG_POS_LIST.
void freeImgPosList(IMG_POS_LIST* list);

// Receives a reference to a TNODE_LIST list. Initializes it's head and tail to NULL.
void makeEmptyTNodeList(TNODE_LIST* list);

// Receives a reference to a IMG_POS_LIST list. Initializes it's head and tail to NULL.
void makeEmptyImgPosList(IMG_POS_LIST* list);

// Receives a reference to a TNODE_LIST list.
// Returns true if the list is empty, false otherwise.
bool isEmptyTNodeList(TNODE_LIST* list);

// Receives a reference to a IMG_POS_LIST list.
// Returns true if the list is empty, false otherwise.
bool isEmptyImgPosList(IMG_POS_LIST* list);

// Receives data of a position ([X, Y] array).
// Returns a reference to a new TNODE containing the given data.
TNODE* createTNode(IMG_POS point);

// Receives data of a position ([X, Y] array) and a reference to a next TNodeLNode node.
// Returns a reference to a new TNODE_LNODE containing the given data.
TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next);

// Receives data of a position ([X, Y] array) and references to next and previous IMG_POS_NODE node.
// Returns a reference to a new IMG_POS_NODE containing the given data.
IMG_POS_NODE* createImgPosNode(IMG_POS data, IMG_POS_NODE* next, IMG_POS_NODE* prev);

// Receives a reference to a TNODE_LIST list and a reference to a TNODE_LNODE node.
// Inserts the node at the end of the given list.
void insertNodeToEndTNodeList(TNODE_LIST* list, TNODE_LNODE* node);

// Receives a reference to a TNODE_LIST list and a reference to TNODE node data.
// Creates a node with the given data and inserts it at the end of the given list.
void insertDataToEndTNodeList(TNODE_LIST* list, TNODE* data);

// Receives a reference to a IMG_POS_LIST list and a reference to a IMG_POS_NODE node.
// Inserts the node at the end of the given list.
void insertNodeToEndImgPosList(IMG_POS_LIST* list, IMG_POS_NODE* node);

// Receives a reference to a IMG_POS_LIST list and a position ([X, Y] array).
// Creates a node with the given data and inserts it at the end of the given list.
void insertDataToEndImgPosList(IMG_POS_LIST* list, IMG_POS data);
#endif
