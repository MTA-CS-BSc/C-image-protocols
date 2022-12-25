#include "utils.h"

COLOR_IMAGE* readPPM(char* fname); 
RGB createPixel(char* line, int* mone); //fun to create one pixel(RGB) from stringInput line
int colorNumber(char* line, int* mone); //fun to calucate the value of each color
void skipSpaces(char* line, int* mone); //fun to skip spaces in the line


void main()
{
	COLOR_IMAGE* iimg;
	iimg = readPPM("file.txt");
}



void skipSpaces(char* line, int* mone)
{
	int moneLine = *mone;
	while (line[moneLine] == ' ')
		moneLine++;
	*mone = moneLine;
}

int colorNumber(char* line, int* mone)
{
	int numDig = 0;
	int value = 0;
	int i;
	int moneLine = *mone;
	while (line[moneLine] != ' '&&line[moneLine]!='\n')
	{
		numDig++;
		moneLine++;
	}
	moneLine -= numDig;
	for (i = numDig - 1; i >= 0; i--)
	{
		value += (line[moneLine] - '0') * pow(10, i);
		moneLine++;
	}

	*mone = moneLine;
	return value;

}

RGB createPixel(char* line, int* mone)
{
	int moneLine = *mone;
	RGB res;
	res.r = colorNumber(line, &moneLine);
	skipSpaces(line, &moneLine);
	res.g = colorNumber(line, &moneLine);
	skipSpaces(line, &moneLine);
	res.b = colorNumber(line, &moneLine);
	skipSpaces(line, &moneLine);

	*mone = moneLine;
	return res;


}

COLOR_IMAGE* readPPM(char* fname)
{
	COLOR_IMAGE* res;
	res = (COLOR_IMAGE*)malloc(sizeof(COLOR_IMAGE));
	char ch;
	FILE* fp;
	char* line;
	unsigned short rows, cols;
	int i, j;
	int rowInd = 0, colInd = 0;
	int mone = 0;
	int monePow = 0;
	int value = 0;
	RGB** pixlesArr;
	bool endOfInput = false;
	fp = fopen(fname, "r");
	fseek(fp, 4, SEEK_SET);
	ch = fgetc(fp);
	if (ch == '#')
	{
		while (ch != '\n')
			ch = fgetc(fp);
		ch = fgetc(fp);
	}
	rows = ch - '0';
	fseek(fp, 2, SEEK_CUR);
	cols = ch - '0';
	pixlesArr = (RGB**)malloc(rows * sizeof(RGB*));
	for (i = 0; i < rows; i++)
		pixlesArr[i] = (RGB**)malloc(cols * sizeof(RGB*));
	line = (char*)malloc(18 * rows * sizeof(char));
	fseek(fp, 6, SEEK_CUR); //to skip the values range
	while (endOfInput == false)
	{
		ch = fgetc(fp);
		if (ch == EOF)
			endOfInput = true;
		else
		{
			fseek(fp, -1, SEEK_CUR);
			mone = 0;
			line = fgets(line, 18 * rows, fp);
			colInd = 0;
			skipSpaces(line, &mone);
			while (line[mone] != '\n')
			{
				skipSpaces(line, &mone);
				pixlesArr[rowInd][colInd] = createPixel(line, &mone);
				colInd++;

			}
			rowInd++;
		}


	}

	fp = fclose(fp);
	res->cols = cols;
	res->rows = rows;
	res->pixels = pixlesArr;
	return res;


}