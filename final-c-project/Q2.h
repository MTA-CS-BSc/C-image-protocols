#ifndef __Q2_H
#define __Q2_H
#include "utils.h"

void readDataFromPGM(FILE* fp, GRAY_IMAGE* gray_image, bool is_ascii);
GRAY_IMAGE* readPGMGeneric(char* fname, bool is_ascii);
// Receives a file name that contains PGM data.
// Creates and returns the gray image read from the file.
GRAY_IMAGE* readPGM(char*);
#endif
