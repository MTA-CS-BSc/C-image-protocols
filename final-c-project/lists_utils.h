#ifndef __LISTS_UTILS_H
#define __LISTS_UTILS_H
#include "utils.h"

void makeEmptyTNodeList(TNODE_LIST* list);
void makeEmptyImgPosList(IMG_POS_LIST* list);
bool isEmptyTNodeList(TNODE_LIST* list);
bool isEmptyImgPosList(IMG_POS_LIST* list);
TNODE* createTNode(IMG_POS point);
TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next);
IMG_POS_NODE* createImgPosNode(IMG_POS data, IMG_POS_NODE* next, IMG_POS_NODE* prev);
void insertNodeToEndTNodeList(TNODE_LIST* list, TNODE_LNODE* node);
void insertDataToEndTNodeList(TNODE_LIST* list, TNODE* data);
void insertNodeToEndImgPosList(IMG_POS_LIST* list, IMG_POS_NODE* node);
void insertDataToEndImgPosList(IMG_POS_LIST* list, IMG_POS data);

#endif
