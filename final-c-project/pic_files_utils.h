#ifndef __PIC_FILES_UTILS
#define __PIC_FILES_UTILS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

void skipLine(FILE* fp);
void skipCommentLines(FILE* fp, char* current_char);
void skipUntilOk(FILE* fp);
void readHeaderFromPicFile(FILE* fp, int* rows, int* cols, int* depth);
#endif