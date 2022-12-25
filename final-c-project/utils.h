#ifndef __UTILS_H
#define __UTILS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

#endif