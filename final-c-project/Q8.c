#include "Q8.h"

char* createPgmFileName(char* fname)
{
	char* newFname;
	newFname = (char*)malloc((strlen(fname) + 5)*sizeof(char));
	if (!newFname)
		memoryAllocFailed();
	sprintf(newFname, "%s%s", fname, ".pgm");
	return newFname;
}

void convertPPMToPGM(char* fname)
{
	int i, j;
	char grayLevel;
	FILE* pgmFp,*ppmFp;
	ppmFp = fopen(fname, "r");
	pgmFp = fopen(createPgmFileName(fname), "w");
	COLOR_IMAGE* colorFile = readPPM(fname);
	unsigned short rows, cols,depth;
	readHeaderFromPicFile(ppmFp, &rows, &cols, &depth);
	
	fprintf(pgmFp, "P3\n%d %d\n%d\n", rows, cols, depth);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			grayLevel = (colorFile->pixels[i][j].r + colorFile->pixels[i][j].g + colorFile->pixels[i][j].b) / 3;
			fputc(grayLevel, pgmFp);
			if (j == cols - 1)
				fputc('\n', pgmFp);
			else
				fputc(' ', pgmFp);
			

		}
	}

	fclose(ppmFp);
	fclose(pgmFp);


}
