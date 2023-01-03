#include "Q8.h"

char* createPgmFileName(char* fname)
{
	char* newFname = (char*)malloc((strlen(fname) + strlen(".pgm") + 1) * sizeof(char));
	
	if (!newFname)
		memoryAllocFailed();

	sprintf(newFname, "%s%s", fname, ".pgm");

	return newFname;
}

void convertPPMToPGM(char* fname) {
	int rows, cols, depth, gray_level;
	FILE *ppmFp = fopen(fname, "r");
	FILE *pgmFp = fopen(createPgmFileName(fname), "w");
	COLOR_IMAGE* colorFile = readPPM(fname);

	readHeaderFromPicFile(ppmFp, &rows, &cols, &depth);
	
	fprintf(pgmFp, "P3\n%d %d\n%d\n", rows, cols, depth);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gray_level = (colorFile->pixels[i][j].r + colorFile->pixels[i][j].g + colorFile->pixels[i][j].b) / 3;

			fprintf(pgmFp, "%d", gray_level);

			if (j == cols - 1)
				fputc('\n', pgmFp);

			else
				fputc(' ', pgmFp);
			

		}
	}

	fclose(ppmFp);
	fclose(pgmFp);
}
