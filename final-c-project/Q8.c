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
	FILE *ppm_fp = fopen(fname, "r");
	FILE *pgm_fp = fopen(createPgmFileName(fname), "w");
	COLOR_IMAGE* colorFile = readPPM(fname);

	readHeaderFromPicFile(ppm_fp, &rows, &cols, &depth);
	
	fprintf(pgm_fp, "P3\n%d %d\n%d\n", rows, cols, depth);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gray_level = (colorFile->pixels[i][j].r + colorFile->pixels[i][j].g + colorFile->pixels[i][j].b) / 3;

			fprintf(pgm_fp, "%d", gray_level);

			if (j == cols - 1)
				fputc('\n', pgm_fp);

			else
				fputc(' ', pgm_fp);
			

		}
	}

	fclose(ppm_fp);
	fclose(pgm_fp);
}
