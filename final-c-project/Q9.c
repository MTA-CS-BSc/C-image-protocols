#include "Q9.h"
#include "Q2.h"
#include <math.h>

char* get_bw_file_name(char* fname, int k) {
	char* bw_file_name = (char*)malloc(sizeof(char) * (strlen(fname) + strlen(".bw") + 2));

	if (!bw_file_name)
		memoryAllocFailed();

	sprintf(bw_file_name, "%s%d%s", fname, k, ".bw");

	bw_file_name[strlen(fname) + 1 + strlen(".bw")] = '\0';

	return bw_file_name;
}

void writeMatrixToFile(FILE* fp, char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			fprintf(fp, "%d ", mat[i][j]);

		fputc('\n', fp);
	}
}

void updateMat(char** new_vals, char current_val, char **mask_matrix, int start_x, int i, int start_y, int j) {
	if (current_val > mask_matrix[i][j])
		new_vals[start_x + i][start_y + j] = 1;

	else
		new_vals[start_x + i][start_y + j] = 0;
}

char** createMatrix(int rows, int cols) {
	char** new_vals = (char**)malloc(sizeof(char*) * rows);
	
	if (!new_vals)
		memoryAllocFailed();

	for (int i = 0; i < rows; i++) {
		new_vals[i] = (char*)malloc(sizeof(char) * cols);

		if (!new_vals[i])
			memoryAllocFailed();
	}

	return new_vals;
}

char** createMaskMatrix(int k) {
	char** mask_matrix = createMatrix(k, k);
	char matrix2[2][2] = { {0, 2}, {3, 1} };
	char matrix3[3][3] = { {2, 6, 4}, {5, 0, 1}, {8, 3, 7} };
	char matrix4[4][4] = { {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5 } };
	char* related_matrix;

	switch (k) {
	case 3:
		related_matrix = (char*)matrix3;
		break;
	case 4:
		related_matrix = (char*)matrix4;
		break;
	default:
		related_matrix = (char*)matrix2;
		break;
	}

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			mask_matrix[i][j] = related_matrix[i * k + j];

	return mask_matrix;
}

void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, char** new_vals) {
	int divider = (int)ceil((double)depth / (k * k)), current_val;
	char** mask_matrix = createMaskMatrix(k);

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (start_x + i < gray_image->rows && start_y + j < gray_image->cols) {
				current_val = gray_image->pixels[start_x + i][start_y + j] / divider;
				updateMat(new_vals, current_val, mask_matrix, start_x, i, start_y, j);

			}
		}
	}
}

void freeMat(char** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

void convertPGMToBW(char* fname) {
	int rows, cols, depth;
	char** new_vals;
	GRAY_IMAGE* gray_image = readPGM(fname);
	FILE* orig_f = fopen(fname, "r");

	readHeaderFromPicFile(orig_f, &rows, &cols, &depth);
	new_vals = createMatrix(rows, cols);

	for (int k = 2; k <= 4; k++) {
		char* k_file_name = get_bw_file_name(fname, k);
		FILE* bw_fp = fopen(k_file_name, "w");

		fprintf(bw_fp, "P2\n%d %d\n%d\n", rows, cols, depth);

		for (int i = 0; i < rows; i += k)
			for (int j = 0; j < cols; j += k)
				updateNewValsMatrix(gray_image, depth, i, j, k, new_vals);

		writeMatrixToFile(bw_fp, new_vals, rows, cols);
		fclose(bw_fp);
		free(k_file_name);
	}	

	freeMat(new_vals, rows);
}