#include "Q12.h"

void printMenu() {
	char actions[] = "1. Read an image file in PPM(p3) format\n2. Read an image file in PGM(p2) format\n3. Find all segments\n4. Color the segments\n5. Save the colored image to PGM\n6. Compress and save the original image in a compressed format\n7. Convert a compressed image to PGM format\n8. Convert PPM to PGM(p3->p2)\n9. Convert PGM to BW(p2->p2)\n10.Convert PPM to PGM(p6->p5)\n11.Convert PGM to BW(p5->p5)\n\0";
	printf("Please enter the number of the desired action, and -1 to exit:\n");
	printf("%s", actions);
}

COLOR_IMAGE* readP3Image() {
	COLOR_IMAGE* color_image = NULL;
	char* file_name;
	printf("Please enter a P3 PPM file name:\n");
	file_name = readLineFromUser();

	if (!isExtensionValid(file_name, "ppm"))
		printf("Extension not valid!\n\n");

	else {
		color_image = readPPM(file_name);
		printf("Completed!\n\n");
	}
	
	free(file_name);

	return color_image;
}

GRAY_IMAGE* readP2Image() {
	GRAY_IMAGE* gray_image = NULL;
	char* file_name;
	printf("Please enter a P2 PGM file name:\n");
	file_name = readLineFromUser();

	if (!isExtensionValid(file_name, "pgm"))
		printf("Extension not valid!\n\n");

	else {
		gray_image = readPGM(file_name);
		printf("Completed!\n\n");
	}

	free(file_name);

	return gray_image;
}

void findSegments(IMG_POS_LIST** segments, GRAY_IMAGE** p2_image, int* segments_amount) {
	unsigned int threshold;
	if (!(*p2_image)) {
		printf("No P2 image was loaded! Please load an image first:\n");
		*p2_image = readP2Image();
	}

	if (*p2_image) {
		printf("Please enter the threshold:\n");
		scanf("%u", &threshold);

		*segments_amount = findAllSegments(*p2_image, threshold, segments);

		printf("Completed!\n\n");
	}
}

void colorWithSameGrayLevel(IMG_POS_LIST** segments, GRAY_IMAGE** p2_image,
	int* segments_amount, GRAY_IMAGE **p2_with_same_gray_level) {
	GRAY_IMAGE* image_with_same_gray_level = NULL;

	if (!(*segments)) {
		printf("No segments loaded! Attempting to load segments...\n");
		findSegments(segments, p2_image, segments_amount);
	}

	if (*segments) {
		image_with_same_gray_level = colorSegments(*segments, (unsigned int)(*segments_amount));
		printf("Completed!\n\n");
	}

	*p2_with_same_gray_level = image_with_same_gray_level;
}

void saveGrayImageToP2(GRAY_IMAGE* p2_with_same_gray_level,
	char* file_name) {
	int depth = 255;
	FILE* pgm_fp = fopen(file_name, "w");
	
	if (!pgm_fp) {
		printf("Couldn't open file for writing!\n");
		exit(1);
	}

	else {
		fprintf(pgm_fp, "P2\n%d %d\n%d\n", p2_with_same_gray_level->cols, p2_with_same_gray_level->rows, depth);

		for (int i = 0; i < p2_with_same_gray_level->rows; i++) {
			for (int j = 0; j < p2_with_same_gray_level->cols; j++) {
				fprintf(pgm_fp, "%d ", p2_with_same_gray_level->pixels[i][j]);
			}

			fputc('\n', pgm_fp);
		}

		fclose(pgm_fp);
	}
}

void saveSameGrayColoredToPgm(GRAY_IMAGE** p2_with_same_gray_level,
	IMG_POS_LIST** segments, GRAY_IMAGE** p2_image,
	int* segments_amount) {
	char* file_name;

	if (!(*p2_with_same_gray_level)) {
		printf("No colored image found. Attempting to color...\n");
		colorWithSameGrayLevel(segments,
			p2_image, segments_amount, p2_with_same_gray_level);
	}

	if (*p2_with_same_gray_level) {
		printf("Please enter the desired PGM file name (including .pgm):\n");
		file_name = readLineFromUser();

		if (!isExtensionValid(file_name, "pgm"))
			printf("Extension not valid!\n\n");

		else {
			saveGrayImageToP2(*p2_with_same_gray_level, file_name);
			printf("Completed!\n\n");
		}

		free(file_name);
	}
}

void convertP3ToP2() {
	char* file_name;
	printf("Please enter a file name of P3 file (including .ppm):\n");
	file_name = readLineFromUser();
	
	if (!isExtensionValid(file_name, "ppm"))
		printf("Extension not valid!\n\n");
	
	else {
		convertPPMToPGM(file_name);
		printf("Completed!\n\n");
	}

	free(file_name);
}

void convertP2ToBW() {
	char* file_name;
	printf("Please enter a file name of P2 file (including .pgm):\n");
	file_name = readLineFromUser();

	if (!isExtensionValid(file_name, "pgm"))
		printf("Extension not valid!\n\n");

	else {
		convertPGMToBW(file_name);
		printf("Completed!\n\n");
	}

	free(file_name);
}

void convertP6ToP5() {
	char* file_name;
	printf("Please enter a file name of P6 file (including .ppm):\n");
	file_name = readLineFromUser();

	if (!isExtensionValid(file_name, "ppm"))
		printf("Extension not valid!\n\n");

	else {
		convertPPMToPGM_Bin(file_name);
		printf("Completed!\n\n");
	}

	free(file_name);
}

void convertP5ToBW() {
	char* file_name;
	printf("Please enter a file name of P5 file (including .pgm):\n");
	file_name = readLineFromUser();

	if (!isExtensionValid(file_name, "pgm"))
		printf("Extension not valid!\n\n");

	else {
		convertPGMToBW_Bin(file_name);
		printf("Completed!\n\n");
	}

	free(file_name);	
}

void saveCompressedPGM(GRAY_IMAGE** p2_image) {
	char* file_name;
	int max_gray_level;

	if (!(*p2_image)) {
		printf("No P2 image was loaded! Please load an image first:\n");
		*p2_image = readP2Image();
	}

	if (*p2_image) {
		printf("Please enter a maximum gray level of the given P2:\n");
		scanf("%d", &max_gray_level);

		printf("\nPlease enter the file name to save to:\n");
		file_name = readLineFromUser();

		saveCompressed(file_name, *p2_image, (unsigned char)max_gray_level);

		printf("Completed!\n\n");

		free(file_name);
	}
		
}

