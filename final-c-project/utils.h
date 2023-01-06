#ifndef __UTILS_H
#define __UTILS_H
#define _CRT_SECURE_NO_WARNINGS

// Librares
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For IMG_POS
#define X 0
#define Y 1
#define MAX_NEIGHBORS 8
// Macros
//#define abs(a) ((a) < 0 ? -(a) : (a))
//#define max(a, b) (((a) > (b)) ? (a) : (b))
//#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct tnode TNODE;

typedef unsigned short IMG_POS[2];

typedef struct rgb {
	unsigned char r, g, b;
} RGB;

typedef struct tnode_lnode {
	TNODE* node;
	struct tnode_lnode* next;
} TNODE_LNODE;

typedef struct tnode_list {
	TNODE_LNODE* head;
	TNODE_LNODE* tail;
} TNODE_LIST;

typedef struct colorImage {
	unsigned short rows, cols;
	RGB** pixels;
} COLOR_IMAGE;

typedef struct grayImage {
	unsigned short rows, cols;
	unsigned char** pixels;
} GRAY_IMAGE;

typedef struct tnode {
	IMG_POS position;
	TNODE_LIST nextPossiblePositions;
} TNODE;

typedef struct segment {
	TNODE* root;
} SEGMENT;

typedef struct img_pos_node {
	IMG_POS position;
	struct img_pos_node* next, * prev;
} IMG_POS_NODE;

typedef struct img_pos_list {
	IMG_POS_NODE* head;
	IMG_POS_NODE* tail;
} IMG_POS_LIST;

char* readLineFromUser();
void memoryAllocFailed();
void freeRGBMat(RGB** matrix, int rows);
void freeMat(char** matrix, int rows);
char* getFirstTokenUntilDot(char* fname);
char* createNewFileExtension(char* fname, char* ext);
char* createPgmFileName(char* fname);
void printGrayMatrix(unsigned char** mat, int rows, int cols);
void printRGBMatrix(RGB** arr, int rows, int cols);
void skipLine(FILE* fp);
void skipCommentLines(FILE* fp, char *current_char);
void makeEmptyTNodeList(TNODE_LIST* list);
void makeEmptyImgPosList(IMG_POS_LIST* list);
void skipUntilOk(FILE* fp);
void readHeaderFromPicFile(FILE* fp, int* rows, int* cols, int* depth);
bool isEmptyTNodeList(TNODE_LIST* list);
bool isEmptyImgPosList(IMG_POS_LIST* list);
char** createMatrix(int rows, int cols);
TNODE* createTNode(IMG_POS point);
TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next);
IMG_POS_NODE* createImgPosNode(IMG_POS data, IMG_POS_NODE* next, IMG_POS_NODE* prev);
bool** createPixelsFlagsMatrix(GRAY_IMAGE* img);
void insertNodeToEndTNodeList(TNODE_LIST* list, TNODE_LNODE* node);
void insertDataToEndTNodeList(TNODE_LIST* list, TNODE* data);
void insertNodeToEndImgPosList(IMG_POS_LIST* list, IMG_POS_NODE* node);
void insertDataToEndImgPosList(IMG_POS_LIST* list, IMG_POS data);
bool checkIfTresholdOk(GRAY_IMAGE* img, IMG_POS n1, IMG_POS n2, int threshold);
bool isInRange(int row, int col, GRAY_IMAGE* img);
void freePixelsFlags(bool** flags, int rows, int cols);
#endif