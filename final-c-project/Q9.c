#include "Q9.h"

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

void updateMat(unsigned char** new_vals, char current_val, char **mask_matrix, int start_x, int i, int start_y, int j) {
	if (current_val > mask_matrix[i][j])
		new_vals[start_x + i][start_y + j] = 1;

	else
		new_vals[start_x + i][start_y + j] = 0;
}

void updateNewValsMatrix(GRAY_IMAGE* gray_image, int depth, int start_x, int start_y, int k, unsigned char** new_vals) {
	int divider = (int)(ceil((double)depth / (k * k))), current_val;
	char** mask_matrix = createMaskMatrix(k);

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (isInRange(start_x + i, start_y + j, gray_image)) {
				current_val = gray_image->pixels[start_x + i][start_y + j] / divider;
				updateMat(new_vals, current_val, mask_matrix, start_x, i, start_y, j);
			}
		}
	}

	freeMat(mask_matrix, k);
}

void convertPGMToBWGeneric(char* fname, bool is_ascii) {
	int rows, cols, depth;
	unsigned char** new_vals;
	GRAY_IMAGE* gray_image = readPGMGeneric(fname, is_ascii);
	FILE* orig_f = fopen(fname, is_ascii ? "r" : "rb");

	if (!orig_f)
		printf("Couldn't read file!\n");

	else {
		readHeaderFromPicFile(orig_f, &rows, &cols, &depth);

		for (int k = 2; k <= 4; k++) {
			new_vals = createMatrix(rows, cols);
			char* k_file_name = get_bw_file_name(fname, k);
			FILE* bw_fp = fopen(k_file_name, is_ascii ? "w" : "wb");

			if (!bw_fp) {
				printf("Couldn't open file for writing!");
				exit(1);
			}

			if (is_ascii)
				fprintf(bw_fp, "P2\n%d %d\n%d\n", cols, rows, 1);

			else
				fprintf(bw_fp, "P5\n%d %d\n%d\n", cols, rows, 1);

			for (int i = 0; i < rows; i += k)
				for (int j = 0; j < cols; j += k)
					updateNewValsMatrix(gray_image, depth, i, j, k, new_vals);

			writeMatrixToFile(bw_fp, new_vals, rows, cols, is_ascii);
			fclose(bw_fp);
			free(k_file_name);
			freeMat(new_vals, rows);
		}

		fclose(orig_f);
	}
}

void convertPGMToBW(char* fname) {
	convertPGMToBWGeneric(fname, true);
}
