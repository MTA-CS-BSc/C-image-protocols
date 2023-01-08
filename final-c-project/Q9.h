#ifndef __Q9_H
#define __Q9_H
#include "matrices_utils.h"
#include "pic_files_utils.h"
#include "utils.h"
#include "Q2.h"

// Receives a file name and a number k.
// Returns a new file name that concats the file name received, k, and .bw.pgm.
char* get_bw_file_name(char* fname, int k);

// Receives a number k, 2 <= k <= 4 and returns the relevant k * k mask matrix.
char** createMaskMatrix(int k);

// Receives a file ref, a pixels matrix, the matrix rows and cols amount and a flag to determine whether the file
// is a binary file or a test file.
// The function writes the matrix pixels values to the file.
void writeMatrixToFile(FILE* fp, unsigned char** mat, int rows, int cols, bool is_ascii);

// Receives a matrix to update, a value, a mask matrix, start_x, start_y and i, j indexes.
// If the value of current val and mask_matrix[i][j], the function inserts 1 to new_vals[start_x + i][start_y + j],
// and 0 otherwise.
void updateMat(unsigned char** new_vals, char current_val, char** mask_matrix, int start_x, int i, int start_y, int j);

// Receives a gray image ref, it's depth, a starting point (start_x, start_y), a number k and a matrix to update.
// The function splits the gray_image->pixels matrix to k * k matrices (or smaller if out of bounds),
// and updates the new_vals matrix as described in Q9.
void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, unsigned char** new_vals);

// Receives a P2/P5 PGM file name and creates 3 black & white PGM files out of it.
void convertPGMToBWGeneric(char* fname, bool is_ascii);

// Receives a P2 PGM file name and creates 3 black & white PGM files out of it.
void convertPGMToBW(char* fname);
#endif