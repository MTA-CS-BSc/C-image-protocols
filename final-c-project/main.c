#include "Q12.h"

void main() {
	COLOR_IMAGE* p3_image = NULL;
	GRAY_IMAGE* p2_image = NULL;
	GRAY_IMAGE* p2_with_same_gray_level = NULL;
	IMG_POS_LIST* segments = NULL;
	int segments_amount;
	int threshold;
	int gray_level;
	char desired_action = 0;

	printMenu();
	scanf("%d", &desired_action);

	while (desired_action != -1) {
		printf("\n");
		switch (desired_action) {
		case 1:
			p3_image = readP3Image();
			break;
		case 2:
			p2_image = readP2Image();
			break;
		case 3:
			findSegments(&segments, p2_image, &segments_amount);
			break;
		case 4:
			p2_with_same_gray_level = colorWithSameGrayLevel(&segments, p2_image, &segments_amount, &gray_level);
			break;
		case 5:
			saveSameGrayColoredToPgm(p2_with_same_gray_level, &segments, p2_image, &segments_amount, &gray_level);
			break;
		case 6:
			// Q6
			break;
		case 7:
			// Q7
			break;
		case 8:
			convertP3ToP2();
			break;
		case 9:
			convertP2ToBW();
			break;
		case 10:
			convertP6ToP5();
			break;
		case 11:
			convertP5ToBW();
			break;
		default:
			printf("Option not in range!\n");
			break;
		}

		printMenu();
		scanf("%d", &desired_action);
	
	}

	freeMat(p2_image->pixels, p2_image->rows);
	freeMat(p2_with_same_gray_level->pixels, p2_with_same_gray_level->cols);
	freeRGBMat(p3_image->pixels, p3_image->rows);
	free(segments);
}