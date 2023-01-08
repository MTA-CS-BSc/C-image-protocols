#ifndef __Q1_H
#define __Q1_H
#include "utils.h"

void readDataFromPPM(FILE* fp, COLOR_IMAGE* color_image, bool is_ascii);
COLOR_IMAGE* readPPMGeneric(char* fname, bool is_ascii);
COLOR_IMAGE* readPPM(char* fname);
#endif