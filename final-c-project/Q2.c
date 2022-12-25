#include "utils.h"
#include "Q2.h"

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

void readHeaderFromPGM(FILE* fp, int* cols, int* rows, int* depth) {
	char current_char;

	// First we need to read the format of the file from the header:
	// There are two possible cases:
	// - The file can start with comments
	// - The file starts with the file format

	current_char = fgetc(fp);

	skipCommentLines(fp, current_char);

	// Now we are standing on the format
	current_char = fgetc(fp); // Now current_char is holding the identifier

	if (current_char == '2') {
		// Now we need to get the rows and cols amount from the header

		skipLine(fp);
		current_char = fgetc(fp);

		skipCommentLines(fp, current_char);

		// To go back to the beginning of the rows cols line
		fseek(fp, -1, SEEK_CUR);

		// Now we should be standing on the cols rows row
		fscanf(fp, "%d %d", cols, rows);

		skipLine(fp);
		current_char = fgetc(fp);

		skipCommentLines(fp, current_char);

		fseek(fp, -1, SEEK_CUR);
		fscanf(fp, "%d", depth);

		skipLine(fp);
		skipCommentLines(fp, current_char);

		// Now we're standing at the beginning of the data
	}
}

GRAY_IMAGE* readPGM(char* fname) {
	FILE* fp = fopen(fname, "r");
	char current_char;
	int cols, rows, depth;

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPGM(fp, &cols, &rows, &depth);	

	printf("%d %d %d", cols, rows, depth);
}