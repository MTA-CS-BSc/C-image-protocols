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
			// Another function!! IMPLEMENT
			break;
		case 6:
			// Q6
			break;
		case 7:
			// Q7
			break;
		case 8:
			// Q8
			break;
		case 9:
			// Q9
			break;
		case 10:
			// Q10
			break;
		case 11:
			// Q11
			break;
		default:
			printf("Option not in range!\n");
			break;
		}

		printMenu();
		scanf("%d", &desired_action);
	
	}

}