#include "Q12.h"

void main() {
	COLOR_IMAGE* p3_image = NULL;
	GRAY_IMAGE* p2_image = NULL;
	GRAY_IMAGE* p2_with_same_gray_level = NULL;
	IMG_POS_LIST* segments = NULL;
	int segments_amount;
	int threshold;
	int desired_action = 0;

	printMenu();
	scanf("%d", &desired_action);

	while (desired_action != -1) {
		printf("\n");
		switch (desired_action) {
		case 1:
			if (p3_image)
				freeColorImage(p3_image);
				
			p3_image = readP3Image();
			break;
		case 2:
			if (p2_image)
				freeGrayImage(p2_image);

			p2_image = readP2Image();
			break;
		case 3:
			if (segments)
				freeImgPosList(segments);
			
			findSegments(&segments, &p2_image, &segments_amount);
			break;
		case 4:
			if (p2_with_same_gray_level)
				freeGrayImage(p2_with_same_gray_level);

			colorWithSameGrayLevel(&segments, &p2_image, &segments_amount, &p2_with_same_gray_level);
			break;
		case 5:
			saveSameGrayColoredToPgm(&p2_with_same_gray_level, &segments, &p2_image, &segments_amount);
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

	freeGrayImage(p2_image);
	freeGrayImage(p2_with_same_gray_level);
	freeColorImage(p3_image);

	if (segments)
		freeImgPosList(segments);
}
