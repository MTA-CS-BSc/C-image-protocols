#ifndef __Q1_H
#define __Q1_H
#include "utils.h"

// Receives a file ref, a color image ref and a flag to determine whether the file is a binary file or a text file. 
// The function reads the data (the pixels) from the file and inserts them into color image pixels data.
void readDataFromPPM(FILE* fp, COLOR_IMAGE* color_image, bool is_ascii);

// Receives a valid P3/P6 PPM file, and a flag to determine whether the file is a binary file or a text file.
// Feads the file's data to a COLOR_IMAGE and returns the image's ref.
COLOR_IMAGE* readPPMGeneric(char* fname, bool is_ascii);

// Receives a valid P3 PPM file, reads the file's data to a COLOR_IMAGE and returns the image's ref.
COLOR_IMAGE* readPPM(char* fname);
#endif