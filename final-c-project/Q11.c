#include "Q11.h"

void readDataFromBinaryPGM(FILE* fp, GRAY_IMAGE* gray_image) {
	gray_image->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * gray_image->rows);

	if (!(gray_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < gray_image->rows; i++) {
		gray_image->pixels[i] = (unsigned char*)malloc(sizeof(unsigned char) * gray_image->cols);

		if (!(gray_image->pixels[i]))
			memoryAllocFailed();

		for (int j = 0; j < gray_image->cols; j++)
			fread(&(gray_image->pixels[i][j]), sizeof(unsigned char), 1, fp);
	}

}

GRAY_IMAGE* readBinaryPGM(char* fname) {
	FILE* fp = fopen(fname, "rb");
	char current_char;
	int cols, rows, depth;
	GRAY_IMAGE* gray_image = (GRAY_IMAGE*)malloc(sizeof(GRAY_IMAGE));

	if (!gray_image)
		memoryAllocFailed();

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPicFile(fp, &rows, &cols, &depth);

	gray_image->cols = cols;
	gray_image->rows = rows;

	readDataFromBinaryPGM(fp, gray_image);

	fclose(fp);

	return gray_image;
}

void writeMatrixToBinaryFile(FILE* fp, unsigned char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			fwrite(&(mat[i][j]), sizeof(unsigned char), 1, fp);
			//fprintf(fp, "%d ", mat[i][j]);

		//fputc('\n', fp);
	}
}

void convertPGMToBW_Bin(char* fname) {
	int rows, cols, depth;
	unsigned char** new_vals;
	GRAY_IMAGE* gray_image = readBinaryPGM(fname);
	FILE* orig_f = fopen(fname, "rb");

	readHeaderFromPicFile(orig_f, &rows, &cols, &depth);

	for (int k = 2; k <= 4; k++) {
		new_vals = createMatrix(rows, cols);
		char* k_file_name = get_bw_file_name(fname, k);
		FILE* bw_fp = fopen(k_file_name, "wb");

		fprintf(bw_fp, "P5\n%d %d\n%d\n", rows, cols, 1);

		for (int i = 0; i < rows; i += k)
			for (int j = 0; j < cols; j += k)
				updateNewValsMatrix(gray_image, depth, i, j, k, new_vals);

		writeMatrixToBinaryFile(bw_fp, new_vals, rows, cols);
		fclose(bw_fp);
		free(k_file_name);
		freeMat(new_vals, rows);
	}
}