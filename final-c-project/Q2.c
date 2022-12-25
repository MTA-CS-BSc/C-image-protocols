#include "utils.h"

GRAY_IMAGE* readPGM(char* fname);

void skipLine(FILE* fp) {
	char current_char = fgetc(fp);

	while (fgetc(fp) != '\n');
}

GRAY_IMAGE* readPGM(char* fname) {
	FILE* fp = fopen(fname, "r");
	char current_char;

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	// First we need to read the format of the file from the header:
	// There are two possible cases:
	// - The file can start with comments
	// - The file starts with the file format

	current_char = fgetc(fp);

	while (current_char == '#') {
		skipLine(fp);
		current_char = fgetc(fp);
	}

	// Now we are standing on the format

	current_char = fgetc(fp); // Now current_char is holding the identifier

	if (current_char == '2')
		// Do something

	else if (current_char == '5')
		// do something else
	
}