#include "utils.h"

void memoryAllocFailed() {
	printf("Memory allocation failed!\n");
	exit(1);
}

void printMatrix(unsigned char** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", mat[i][j]);
		}

		printf("\n");
	}
}

void skipLine(FILE* fp) {
	char current_char = fgetc(fp);

	while (current_char != '\n')
		current_char = fgetc(fp);
}

void skipCommentLines(FILE* fp, char current_char) {
	while (current_char == '#') {
		skipLine(fp);
		current_char = fgetc(fp);
	}
}
