#include "Q12.h"

void printMenu() {
	char actions[] = "1. Read an image file in PPM(p3) format\n2. Read an image file in PGM(p2) format\n3. Find all segments\n4. Color the segments\n5. Save the colored image to PGM\n6. Compress and save the original image in a compressed format\n7. Convert a compressed image to PGM format\n8. Convert PPM to PGM(p3->p2)\n9. Convert PGM to BW(p2->p2)\n10.Convert PPM to PGM(p6->p5)\n11.Convert PGM to BW(p5->p5)\n\0";
	printf("Please enter the number of the desired action, and -1 to exit:\n");
	printf("%s", actions);
}

COLOR_IMAGE* readP3Image() {
	COLOR_IMAGE* color_image;
	char* file_name;
	printf("Please enter a P3 PPM file name:\n");
	file_name = readLineFromUser();

	color_image = readPPM(file_name);
	free(file_name);
	return color_image;
}

GRAY_IMAGE* readP2Image() {
	GRAY_IMAGE* gray_image;
	char* file_name;
	printf("Please enter a P2 PGM file name:\n");
	file_name = readLineFromUser();

	gray_image = readPPM(file_name);
	free(file_name);
	return gray_image;
}

void findSegments(IMG_POS_LIST** segments, GRAY_IMAGE* p2_image, int* segments_amount) {
	unsigned int threshold;
	if (!p2_image) {
		printf("No P2 image was loaded! Please load an image first:\n");
		p2_image = readP2Image();
	}

	printf("Please enter the threshold:\n");
	scanf("%u", &threshold);

	*segments_amount = findAllSegments(p2_image, threshold, segments);
}

GRAY_IMAGE* colorWithSameGrayLevel(IMG_POS_LIST** segments, GRAY_IMAGE* p2_image,
	int* segments_amount) {
	GRAY_IMAGE* image_with_same_gray_level;

	if (!(*segments)) {
		printf("No segments loaded! Attempting to load segments...\n");
		findSegments(segments, p2_image, segments_amount);
	}

	image_with_same_gray_level = colorSegments(*segments, (unsigned int)(*segments_amount));

	return image_with_same_gray_level;
}
