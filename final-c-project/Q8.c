#include "Q8.h"

void convertPPMToPGMGeneric(char* fname, bool is_ascii) {
	int rows, cols, depth;
	char* new_fname = createPgmFileName(fname), gray_level;
	FILE* ppm_fp = fopen(fname, is_ascii ? "r" : "rb");
	FILE* pgm_fp = fopen(new_fname, is_ascii ? "w" : "wb");
	COLOR_IMAGE* color_file = readPPMGeneric(fname, is_ascii);

	if (!pgm_fp || !ppm_fp)
		printf("Couldn't read one or more of the files!\n");

	else {
		readHeaderFromPicFile(ppm_fp, &rows, &cols, &depth);

		if (is_ascii)
			fprintf(pgm_fp, "P2\n%d %d\n%d\n", cols, rows, depth);

		else
			fprintf(pgm_fp, "P5\n%d %d\n%d\n", cols, rows, depth);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				gray_level = (color_file->pixels[i][j].r + color_file->pixels[i][j].g + color_file->pixels[i][j].b) / 3;

				if (is_ascii)
					fprintf(pgm_fp, "%d ", gray_level);

				else
					fwrite(&gray_level, sizeof(unsigned char), 1, pgm_fp);
			}

			if (is_ascii)
				fputc('\n', pgm_fp);
		}

		fclose(ppm_fp);
		fclose(pgm_fp);
	}

	free(new_fname);
}

void convertPPMToPGM(char* fname) {
	convertPPMToPGMGeneric(fname, true);
}
