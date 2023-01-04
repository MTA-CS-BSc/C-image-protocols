#include "Q9.h"
#include "Q2.h"

char* get_bw_file_name(char* fname, int k) {
	int ext_length = strlen(".bw.pgm");
	char* returned_fname;
	char* new_ext = (char*)malloc(sizeof(char) * (ext_length + 2));

	if (!new_ext)
		memoryAllocFailed();
	
	new_ext[0] = (char)k + '0';
	new_ext[1] = '\0';

	strcat(new_ext, ".bw.pgm");
	new_ext[ext_length + 1] = '\0';

	returned_fname = createNewFileExtension(fname, new_ext);

	free(new_ext);

	return returned_fname;
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

	freeMat(mask_matrix, k);
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
