#include "pic_files_utils.h"

void skipLine(FILE* fp) {
	char current_char = fgetc(fp);

	while (current_char != '\n')
		current_char = fgetc(fp);
}

void skipCommentLines(FILE* fp, char* current_char) {
	bool entered = false;
	while (*current_char == '#') {
		entered = true;
		skipLine(fp);
		*current_char = fgetc(fp);
	}

	if (entered)
		fseek(fp, -1, SEEK_CUR);
}

void skipUntilOk(FILE* fp) {
	char current_char;

	skipLine(fp);
	current_char = fgetc(fp);

	if (current_char == '#')
		skipCommentLines(fp, &current_char);

	else
		fseek(fp, -1, SEEK_CUR);
}

void readHeaderFromPicFile(FILE* fp, int* rows, int* cols, int* depth) {
	char current_char = fgetc(fp);

	// There are two options:
	// First char can be #, or P

	if (current_char == '#') {
		skipCommentLines(fp, &current_char);
		current_char = fgetc(fp);
	}

	current_char = fgetc(fp);

	skipUntilOk(fp);

	fscanf(fp, "%d %d", cols, rows);

	skipUntilOk(fp);

	fscanf(fp, "%d", depth);

	skipUntilOk(fp);
}