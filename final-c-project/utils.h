#ifndef __UTILS_H
#define __UTILS_H
#define _CRT_SECURE_NO_WARNINGS

// Librares
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// For IMG_POS
#define X 0
#define Y 1

// Macros
#define abs(a) ((a) < 0 ? -(a) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

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


void memoryAllocFailed();
void printMatrix(char** mat, int rows, int cols);
void skipLine(FILE* fp);
void skipCommentLines(FILE* fp, char current_char);
void makeEmptyTNodeList(TNODE_LIST* list);
bool isEmptyList(TNODE_LIST* list);
TNODE* createTNode(IMG_POS point);
TNODE_LNODE* createTNodeLNode(TNODE* data, TNODE_LNODE* next);
void insertDataToEndList(TNODE_LIST* list, TNODE* data);
#endif