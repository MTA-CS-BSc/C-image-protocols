#include "Q6.h"

int calcPNew(unsigned char p_value, unsigned char max_gray_level) {
	return ((p_value * max_gray_level) / 255);
}

void insertPNewToBytesArray(unsigned char new_p, unsigned char bits_required, BYTE* bytes_array,
	unsigned int* bytes_array_size, unsigned int* current_byte_available_bits) {

	unsigned char shifted_p = new_p << (CHAR_BIT - bits_required); // remove leading zeroes to have the needed bits
	unsigned char left_splitted_p = shifted_p >> (CHAR_BIT - *current_byte_available_bits); // get the first 8 - available bits
	unsigned char right_splitted_p = shifted_p << (*current_byte_available_bits); // the rest
	unsigned int bits_written;

	bytes_array[*bytes_array_size] |= left_splitted_p; // insert the left splitted to the current index

	bits_written = min(bits_required, *current_byte_available_bits); // calculate the amount of bits written

	*current_byte_available_bits -= bits_written; // decrease byte available bits

	if (*current_byte_available_bits <= 0) { // if we're done reading the byte
		(*bytes_array_size)++;
		*current_byte_available_bits = CHAR_BIT;
	}

	if (bits_required - bits_written > 0) { // If we wrote less than bits_required
		bytes_array[*bytes_array_size] |= right_splitted_p;
		*current_byte_available_bits = CHAR_BIT - (bits_required - bits_written);
	}
}

void writeHeaderToCompressed(FILE* fp, unsigned int* rows, unsigned int* cols, unsigned int* max_gray_level) {
	fwrite(rows, sizeof(unsigned short), 1, fp);
	fwrite(cols, sizeof(unsigned short), 1, fp);

	fwrite(max_gray_level, sizeof(unsigned char), 1, fp);
}

void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel) {
	BYTE* bytes_array = (BYTE*)calloc(image->rows * image->cols, sizeof(BYTE));
	unsigned int bytes_array_size = 0;
	unsigned int current_byte_available_bits = CHAR_BIT;
	unsigned char bits_required = amountOfBitsNeeded(maxGrayLevel), new_p;
	FILE* fp = fopen(fname, "wb");

	if (!fp) {
		printf("Couldn't open file for writing!\n");
		exit(1);
	}

	else {
		writeHeaderToCompressed(fp, &(image->rows), &(image->cols), &maxGrayLevel);

		for (int i = 0; i < image->rows; i++) {
			for (int j = 0; j < image->cols; j++) {
				new_p = (unsigned char)calcPNew(image->pixels[i][j], maxGrayLevel);
				insertPNewToBytesArray(new_p, bits_required, bytes_array, &bytes_array_size, &current_byte_available_bits);
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