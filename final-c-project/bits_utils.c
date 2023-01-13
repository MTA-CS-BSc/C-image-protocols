#include "bits_utils.h"

int isIBitSet(BYTE ch, int i) {
	BYTE mask = 1 << i;
	return mask & ch;
}

int amountOfBitsNeeded(unsigned char max_gray_level) {
	bool flag = true;
	int amount_of_leading_zeros = 0;

	for (int i = 7; i >= 0 && flag; i--) {
		if (isIBitSet(max_gray_level, i))
			flag = false;

		else
			amount_of_leading_zeros++;
	}

	return BITS_IN_CHAR - amount_of_leading_zeros;
}

BYTE setBit(BYTE ch, int i) {
	BYTE mask = 1 << i;
	return ch | mask;
}

BYTE setBitsInRange(BYTE ch, int l, int r) {
	for (int i = BITS_IN_CHAR - l; i >= BITS_IN_CHAR - r; i--)
		ch = setBit(ch, i);

	return ch;
}
