#ifndef __PIC_FILES_UTILS
#define __PIC_FILES_UTILS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

// Receives a file reference. Skips a line starting at the current position.
void skipLine(FILE* fp);

// Receives a file reference and a current char reference. Skips all comments lines.
void skipCommentLines(FILE* fp, char* current_char);

// Receives a file reference and skips until done with the comments.
void skipUntilOk(FILE* fp);

// Receives a file reference and references to rows, cols and depth.
// Reads the header of the file and updates the rows, cols and depth values with the read data.
void readHeaderFromPicFile(FILE* fp, int* rows, int* cols, int* depth);
#endif