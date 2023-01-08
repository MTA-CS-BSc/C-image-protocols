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
#define ABS(a) ((a) < 0 ? -(a) : (a))

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

// Reads a line of unknown length from the user.
char* readLineFromUser();

// Informs the user of a failure on memory allocation and exits.
void memoryAllocFailed();

// Receives a file name with an extension.
// Returns the file name without the extension.
char* getFirstTokenUntilDot(char* fname);

// Receives a file name and an extension to concat.
// Returns a concated string of the file name and the extension.
char* createNewFileExtension(char* fname, char* ext);

// Receives a file name and returns a concated string of the file name + ".pgm" extension.
char* createPgmFileName(char* fname);

// Receives a gray image ref, two positions and a threshold.
// Returns true if the difference between the pixels is not greater than threshold, and false otherwise.
bool checkIfTresholdOk(GRAY_IMAGE* img, IMG_POS n1, IMG_POS n2, int threshold);

// Receives a row number, a column number and a gray image ref.
// Returns true if the row & column received are in the image's range, and false otherwise.
bool isInRange(int row, int col, GRAY_IMAGE* img);

// Receives a file name and an extension (without a dot, i.e "txt").
// Returns true if the file name received matches the extension, and false otherwise.
bool isExtensionValid(char* fname, char* extension);
#endif