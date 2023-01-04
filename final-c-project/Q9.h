#ifndef __Q9_H
#define __Q9_H
#include "utils.h"
#include <string.h>
#include <math.h>

char* get_bw_file_name(char* fname, int k);
char** createMaskMatrix(int k);
void writeMatrixToFile(FILE* fp, char** mat, int rows, int cols);
void updateMat(char** new_vals, char current_val, char** mask_matrix, int start_x, int i, int start_y, int j);
void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, char** new_vals);
void convertPGMToBW(char* fname);
#endif