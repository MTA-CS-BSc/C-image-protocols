#ifndef __Q8_H
#define __Q8_H
#include "utils.h"
#include "Q1.h"

// Receives a P3/P6 PPM file name and a flag to determine whether the file is a binary file or a text file.
// The function converts the PPM file to a PGM file (P2 or P5, depends on the input).
void convertPPMToPGMGeneric(char* fname, bool is_ascii);

// Receives a P3 PPM file name and converts it to a P2 PGM file.
void convertPPMToPGM(char* fname);
#endif
