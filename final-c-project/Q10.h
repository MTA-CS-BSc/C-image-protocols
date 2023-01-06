#ifndef __Q10_H
#define __Q10_H
#include "utils.h"

void readDataFromBinaryPPM(FILE* fp, COLOR_IMAGE* color_image);

COLOR_IMAGE* readBinaryPPM(char* fname);

void convertPPMToPGM_Bin(char* fname);
#endif
