#include "utils.h"
#include "Q2.h"
void printMatrix(int rows, int cols, RGB** arr)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%d%d%d     ", arr[i][j].r,arr[i][j].g,arr[i][j].b);
		}
		printf("\n");
	}
}

void readHeaderFromPPM(FILE* fp, int* cols, int* rows, int* depth) {
	char current_char;

	// First we need to read the format of the file from the header:
	// There are two possible cases:
	// - The file can start with comments
	// - The file starts with the file format

	current_char = fgetc(fp);

	skipCommentLines(fp, current_char);

	// Now we are standing on the format
	current_char = fgetc(fp); // Now current_char is holding the identifier

	if (current_char == '3') {
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

void readDataFromPPM(FILE* fp, COLOR_IMAGE* color_image) {
	color_image->pixels = (RGB**)malloc(sizeof(RGB*) * color_image->rows);

	if (!(color_image->pixels))
		memoryAllocFailed();

	for (int i = 0; i < color_image->rows; i++) {
		color_image->pixels[i] = (RGB**)malloc(sizeof(RGB*) * color_image->cols);

		if (!(color_image->pixels[i]))
			memoryAllocFailed();
	}

	for (int i = 0; i < color_image->rows; i++)
		for (int j = 0; j < color_image->cols; j++)
			fscanf(fp, "%d %d %d", (color_image->pixels[i] + j)->r, (color_image->pixels[i] + j)->g , (color_image->pixels[i] + j)->b);
}

COLOR_IMAGE* readPPM(char* fname) {
	FILE* fp = fopen(fname, "r");
	char current_char;
	int cols, rows, depth;
	COLOR_IMAGE* color_image = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));

	if (!color_image)
		memoryAllocFailed();

	if (!fp) {
		printf("Couldn't read file!\n");
		exit(1);
	}

	readHeaderFromPPM(fp, &cols, &rows, &depth);

	color_image->cols = cols;
	color_image->rows = rows;

	readDataFromPPM(fp, color_image);

	fp = fclose;

	return color_image;
}

void main()
{
	COLOR_IMAGE* iimg;
	iimg = readPPM("file.txt");
	printMatrix(iimg->rows, iimg->cols, iimg->pixels);
}


