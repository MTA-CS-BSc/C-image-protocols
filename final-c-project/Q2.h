#ifndef __Q2_H
#define __Q2_H
#include "utils.h"

// Receives a file ref, a gray image ref and a flag to determine whether the file is a binary file or a text file. 
// The function reads the data (the pixels) from the file and inserts them into gray image pixels data.
void readDataFromPGM(FILE* fp, GRAY_IMAGE* gray_image, bool is_ascii);

// Receives a valid P2/P5 PGM file, and a flag to determine whether the file is a binary file or a text file.
// Feads the file's data to a GRAY_IMAGE and returns the image's ref.
GRAY_IMAGE* readPGMGeneric(char* fname, bool is_ascii);

// Receives a valid P2 PGM file, reads the file's data to a GRAY_IMAGE and returns the image's ref.
GRAY_IMAGE* readPGM(char*);
#endif
