#include "Q8.h"

void convertPPMToPGM(char* fname) {
	int rows, cols, depth;
	char gray_level;
	FILE *ppm_fp = fopen(fname, "r");
	char* new_fname = createPgmFileName(fname);
	FILE *pgm_fp = fopen(new_fname, "w");
	COLOR_IMAGE* colorFile = readPPM(fname);

	readHeaderFromPicFile(ppm_fp, &rows, &cols, &depth);
	
	fprintf(pgm_fp, "P3\n%d %d\n%d\n", rows, cols, depth);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gray_level = (colorFile->pixels[i][j].r + colorFile->pixels[i][j].g + colorFile->pixels[i][j].b) / 3;
			fprintf(pgm_fp, "%d ", gray_level);
		}

		fputc('\n', pgm_fp);
	}

	fclose(ppm_fp);
	fclose(pgm_fp);
	free(new_fname);
}
