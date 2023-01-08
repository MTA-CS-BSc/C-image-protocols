#include "utils.h"

char* readLineFromUser() {
	char* str;
	char ch;
	int physical_size = 0, len = 0;

	str = (char*)malloc(sizeof(char));

	if (!str)
		memoryAllocFailed();

	scanf(" %c", &ch);

	while (ch != '\n' && ch != '\0') {
		str = (char*)realloc(str, ++physical_size + 1);

		if (!str)
			memoryAllocFailed();

		str[len++] = ch;
		scanf("%c", &ch);
	}

	str[len] = '\0';

	return str;
}

void memoryAllocFailed() {
	printf("Memory allocation failed!\n");
	exit(1);
}

char* getFirstTokenUntilDot(char* fname) {
	return strtok(fname, ".");
}

char* createNewFileExtension(char* fname, char* ext) {
	char* fname_dup = _strdup(fname);
	char* name_wo_ext = getFirstTokenUntilDot(fname_dup);
	char* new_file_name = (char*)malloc((strlen(name_wo_ext) + strlen(ext) + 1) * sizeof(char));

	if (!new_file_name)
		memoryAllocFailed();

	new_file_name[0] = '\0';

	strcat(new_file_name, name_wo_ext);
	strcat(new_file_name, ext);

	free(fname_dup);

	return new_file_name;
}

char* createPgmFileName(char* fname) {
	return createNewFileExtension(fname, ".pgm");
}

bool checkIfTresholdOk(GRAY_IMAGE* img, IMG_POS n1, IMG_POS n2, int threshold) {
	return (ABS((img->pixels[n1[X]][n1[Y]] - img->pixels[n2[X]][n2[Y]])) <= threshold);
}

bool isInRange(int row, int col, GRAY_IMAGE* img) {
	return (row >= 0 && row < img->rows&& col >= 0 && col < img->cols);
}

bool isExtensionValid(char* fname, char* extension) {
	bool flag = false;
	char* dup = _strdup(fname);
	char* token = strtok(dup, ".");
	token = strtok(NULL, ".");

	if (token && strcmp(token, extension) == 0)
		flag = true;

	free(dup);
	return flag;

}