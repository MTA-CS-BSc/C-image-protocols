#ifndef __Q2_H
#define __Q2_H
#include "utils.h"

GRAY_IMAGE* readPGM(char*);
void readHeaderFromPGM(FILE*, int*, int*, int*);
void readDataFromPGM(FILE*, GRAY_IMAGE*);

#endif
