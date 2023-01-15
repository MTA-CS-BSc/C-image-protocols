#include "Q6.h"

int calcPNew(unsigned char p_value, unsigned char max_gray_level) {
	return ((p_value * max_gray_level) / 255);
}

void insertPNewToBytesArray(unsigned char new_p, unsigned char bits_required, BYTE* current_byte,
	unsigned int* bytes_written_amount, unsigned int* current_byte_available_bits, FILE* fp) {
	
	unsigned char shifted_p = new_p << (BITS_IN_CHAR - bits_required); // remove leading zeroes to have the needed bits at the beginning
	unsigned char left_splitted_p = shifted_p >> (BITS_IN_CHAR - *current_byte_available_bits); // get the first 8 - available bits (pushed to end)
	unsigned char right_splitted_p = shifted_p << (*current_byte_available_bits); // the rest (pushed to start)
	unsigned int bits_written;

	*current_byte |= left_splitted_p; // insert the left splitted to the current index

	bits_written = min(bits_required, *current_byte_available_bits); // calculate the amount of bits written

	*current_byte_available_bits -= bits_written; // decrease byte available bits

	if (*current_byte_available_bits == 0) { // if we're done writing the byte
		fwrite(current_byte, sizeof(BYTE), 1, fp);
		*current_byte_available_bits = BITS_IN_CHAR;
		*current_byte = 0x0;
	}

	if (bits_required - bits_written > 0) { // If we wrote less than bits_required
		*current_byte |= right_splitted_p;
		*current_byte_available_bits = BITS_IN_CHAR - (bits_required - bits_written);
	}
}

void writeHeaderToCompressed(FILE* fp, unsigned int* rows, unsigned int* cols, unsigned int* max_gray_level) {
	fwrite(rows, sizeof(unsigned short), 1, fp);
	fwrite(cols, sizeof(unsigned short), 1, fp);

	fwrite(max_gray_level, sizeof(unsigned char), 1, fp);
}

void saveCompressed(char* fname, GRAY_IMAGE* image,
	unsigned char maxGrayLevel) {
	BYTE current_byte = 0x0;
	unsigned int bytes_written_amount = 0;
	unsigned int current_byte_available_bits = BITS_IN_CHAR;
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
				insertPNewToBytesArray(new_p, bits_required, &current_byte, &bytes_written_amount, &current_byte_available_bits, fp);
			}
		}

		fclose(fp);
	}
}