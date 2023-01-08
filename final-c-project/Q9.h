#ifndef __Q9_H
#define __Q9_H
#include "utils.h"
#include "Q2.h"

char* get_bw_file_name(char* fname, int k);
char** createMaskMatrix(int k);
void writeMatrixToFile(FILE* fp, unsigned char** mat, int rows, int cols, bool is_ascii);
void updateMat(unsigned char** new_vals, char current_val, char** mask_matrix, int start_x, int i, int start_y, int j);
void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, unsigned char** new_vals);
void convertPGMToBWGeneric(char* fname, bool is_ascii);
void convertPGMToBW(char* fname);
#endif