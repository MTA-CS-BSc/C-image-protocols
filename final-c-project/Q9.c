#include "Q9.h"
#include "Q2.h"
#include <math.h>
//#define K2MAT { {0, 2}, { 3, 1 } }
//#define K3MAT { {2, 6, 4}, {5, 0, 1}, {8, 3, 7} }
//#define K4MAT { {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5 } }

char* get_bw_file_name(char* fname, int k) {
	char* bw_file_name = (char*)malloc(sizeof(char) * (strlen(fname) + strlen(".bw") + 2));

	if (!bw_file_name)
		memoryAllocFailed();

	sprintf(bw_file_name, "%s%d%s", fname, k, ".bw");

	bw_file_name[strlen(fname) + 1 + strlen(".bw")] = '\0';

	return bw_file_name;
}

//char** getMaskMatrix(int k) {
//	char matrix2[2][2] = { {0, 2}, {3, 1} };
//	char matrix3[3][3] = { {2, 6, 4}, {5, 0, 1}, {8, 3, 7} };
//	char matrix4[4][4] = { {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5 } };
//
//	if (k == 2)
//		return &matrix2;
//
//	else if (k == 3)
//		return &matrix3;
//
//	else if (k == 4)
//		return &matrix4;
//}

void writeMatrixToFile(FILE* fp, char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			fprintf(fp, "%d ", mat[i][j]);

		fputc('\n', fp);
	}
}

//if (current_val > mask_matrix[i][j])
//	new_vals[start_x + i][start_y + j] = 1;

//else
//	new_vals[start_x + i][start_y + j] = 0;

void updateMat(char** new_vals, char current_val, char **mask_matrix, int start_x, int i, int start_y, int j) {
if (current_val > mask_matrix[i][j])
	new_vals[start_x + i][start_y + j] = 1;

else
	new_vals[start_x + i][start_y + j] = 0;
}
void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, char** new_vals) {
	int divider = (int)ceil((double)depth / (k * k));
	int current_val;
	int curr_index = 0;

	//int mask_matrix_2[2][2] = {{0, 2}, {3, 1}};

	char** mask_matrix_2 = (char**)malloc(sizeof(char*) * 2);

	for (int i = 0; i < 2; i++)
		mask_matrix_2[i] = (char*)malloc(sizeof(char) * 2);

	mask_matrix_2[0][0] = 0;
	mask_matrix_2[0][1] = 2;
	mask_matrix_2[1][0] = 3;
	mask_matrix_2[1][1] = 1;


	char** mask_matrix_3 = (char**)malloc(sizeof(char*) * 3);

	for (int i = 0; i < 3; i++)
		mask_matrix_3[i] = (char*)malloc(sizeof(char) * 3);

	mask_matrix_3[0][0] = 2;
	mask_matrix_3[0][1] = 6;
	mask_matrix_3[0][2] = 4;
	mask_matrix_3[1][0] = 5;
	mask_matrix_3[1][1] = 0;
	mask_matrix_3[1][2] = 1;
	mask_matrix_3[2][0] = 8;
	mask_matrix_3[2][1] = 3;
	mask_matrix_3[2][2] = 7;
		
	//int mask_matrix_3[3][3] = { {2, 6, 4}, {5, 0, 1}, {8, 3, 7} };
	//int mask_matrix_4[4][4] = { {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5 } };
	int num;

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (start_x + i < gray_image->rows && start_y + j < gray_image->cols) {
			//sprintf(&num, "%d", gray_image->pixels[start_x + i][start_y + j]);
				
				current_val = gray_image->pixels[start_x + i][start_y + j] / divider;
			if (k == 3)
				updateMat(new_vals, current_val, mask_matrix_3, start_x, i, start_y, j);
				
		/*		else if (k == 3)
					updateMat(new_vals, current_val, mask_matrix_3, start_x, i, start_y, j);

				else if (k == 4)
					updateMat(new_vals, current_val, mask_matrix_4, start_x, i, start_y, j);*/

			}
		}
	}
}

void convertPGMToBW(char* fname) {
	GRAY_IMAGE* gray_image = readPGM(fname);
	int rows, cols, depth;
	FILE* orig_f = fopen(fname, "r");

	readHeaderFromPicFile(orig_f, &rows, &cols, &depth);

	char** new_vals = (char**)malloc(sizeof(char*) * rows);

	if (!new_vals)
		memoryAllocFailed();

	for (int i = 0; i < rows; i++) {
		new_vals[i] = (char*)malloc(sizeof(char) * cols);

		if (!new_vals[i])
			memoryAllocFailed();
	}
	int k = 3;

	//for (int k = 2; k <= 4; k++) {
		char* k_file_name = get_bw_file_name(fname, k);
		FILE* bw_fp = fopen(k_file_name, "w");

		fprintf(bw_fp, "P2\n%d %d\n%d\n", rows, cols, depth);

		for (int i = 0; i < rows; i += k) {
			for (int j = 0; j < cols; j += k) {
				updateNewValsMatrix(gray_image, depth, i, j, k, new_vals);
			}
		}

		writeMatrixToFile(bw_fp, new_vals, rows, cols);
		fclose(bw_fp);
		free(k_file_name);
	//}	
}