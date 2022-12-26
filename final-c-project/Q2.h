#ifndef __Q2_H
#define __Q2_H
#include "utils.h"

// Receives a file name that contains PGM data.
// Creates and returns the gray image read from the file.
GRAY_IMAGE* readPGM(char*);

// Receives a file, and refs to rows, cols and depth.
// The function reads the header data from the file and updates the parameters' data.
void readHeaderFromPGM(FILE*, int*, int*, int*);

// Receives a file and a gray image ref, inserts the data from the file to the pixels array.
void readDataFromPGM(FILE*, GRAY_IMAGE*);

#endif
