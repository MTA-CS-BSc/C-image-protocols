#include "Q6.h"

// Shift given new_p number according to bits_required to the left
//								[b1b2b3b4 b5000] -> or [0000 0011]
// [0000 0111] -> [0011 1000] -> [1100 0000]

// [b1b2b3b4 b5b6b7b8] -> available = 8
// [b1b2b3b4 b5b6b7b8] -> available = 4
// [0011		1000]
// Shift right (with SAVER) to get according to available
// left_splitted = [0000 0011]
//					[b1b2b3

// update available bits in current byte
// if (available_bits = 0)
// increase size of bytes array and reset available_bits to 8

int calcPNew(unsigned char p_value, unsigned char max_gray_level) {
	return ((p_value * max_gray_level) / 255);
}

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

	return 8 - amount_of_leading_zeros;
}

void insertNewPToBytesArray(unsigned char new_p, unsigned char bits_required, BYTE* bytes_array,
	unsigned int* bytes_array_size, unsigned int* current_byte_available_bits) {

	unsigned char shifted_p = new_p << (8 - bits_required); // [1111 1000]
	unsigned char left_splitted_p = shifted_p >> (8 - *current_byte_available_bits); // [1111 1000]
	unsigned char right_splitted_p = shifted_p << (*current_byte_available_bits); // [0000 0000]
	unsigned int bits_written;

	bytes_array[*bytes_array_size] |= left_splitted_p;

	bits_written = min(bits_required, *current_byte_available_bits);

	*current_byte_available_bits -= bits_written;

	if (*current_byte_available_bits <= 0) {
		(*bytes_array_size)++;
		*current_byte_available_bits = 8;
	}

	if (bits_required - bits_written > 0) {
		bytes_array[*bytes_array_size] |= right_splitted_p;
		*current_byte_available_bits = 8 - (bits_required - bits_written);
	}
		
	
	// min(bits_required, current_byte_available_bits) -> how much i wrote
	// if (current_byte_available_bits - how much i wrote) <= 0
	// Increment byte_array_size and set current_byte_available_bits = 8

	// if (bits_required - how much i wrote > 0) 
	// bytes_array[*bytes_array_size] |= right_splitted_p;

}

void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel) {
	BYTE* bytes_array = (BYTE*)calloc(image->rows * image->cols, sizeof(BYTE));
	unsigned int bytes_array_size = 0;
	unsigned int current_byte_available_bits = 8;
	unsigned char bits_required = amountOfBitsNeeded(maxGrayLevel), new_p;
	FILE* fp = fopen(fname, "wb");

	if (!fp) {
		printf("Couldn't open file for writing!\n");
		exit(1);
	}

	else {
		fwrite(&(image->rows), sizeof(unsigned short), 1, fp);
		fwrite(&(image->cols), sizeof(unsigned short), 1, fp);

		fwrite(&maxGrayLevel, sizeof(unsigned char), 1, fp);

		for (int i = 0; i < image->rows; i++) {
			for (int j = 0; j < image->cols; j++) {
				new_p = (unsigned char)calcPNew(image->pixels[i][j], maxGrayLevel);
				insertNewPToBytesArray(new_p, bits_required, bytes_array, &bytes_array_size, &current_byte_available_bits);
			}
		}

		bytes_array = (BYTE*)realloc(bytes_array, sizeof(BYTE) * bytes_array_size);

		if (!bytes_array)
			memoryAllocFailed();

		for (int i = 0; i < bytes_array_size; i++)
			fwrite(&bytes_array[i], sizeof(BYTE), 1, fp);

		fclose(fp);

		free(bytes_array);
	}
}