#include "Q7.h"

void getHeaderFromCompressed(FILE* compressed, unsigned int* rows, unsigned int* cols, unsigned char* max_gray_level) {
    fread(rows, sizeof(unsigned short), 1, compressed);
    fread(cols, sizeof(unsigned short), 1, compressed);
    fread(max_gray_level, sizeof(unsigned char), 1, compressed);
}

void getDataFromByte(BYTE* current_byte, int *current_number,
    unsigned int* bits_read_from_current_byte, unsigned char* required_bits,
    unsigned int* bit_counter, unsigned int* bits_read_for_current_insert_index,
    int* insert_j, int cols, FILE* fp, FILE* p2) {
    
    BYTE mask_for_extract = 0;
    BYTE without_read_bits;

    unsigned int bits_to_read = MIN(*required_bits - *bits_read_for_current_insert_index, CHAR_BIT - *bits_read_from_current_byte);
    mask_for_extract = setBitsInRange(mask_for_extract, *bits_read_from_current_byte + 1,
        *bits_read_from_current_byte + bits_to_read);

    without_read_bits = *current_byte & mask_for_extract;

    without_read_bits >>= (CHAR_BIT - (*bits_read_from_current_byte + bits_to_read)); // push to end
    *current_number <<= (*required_bits - *bits_read_for_current_insert_index);
    *current_number |= without_read_bits;

    *bits_read_from_current_byte += bits_to_read;
    *bits_read_for_current_insert_index += bits_to_read;
    
    if (*bits_read_from_current_byte == CHAR_BIT) {
        fread(current_byte, sizeof(BYTE), 1, fp);
        *bits_read_from_current_byte = 0;
        *bit_counter += CHAR_BIT;
    }

    if (*bits_read_for_current_insert_index == *required_bits) {
        fprintf(p2, "%d ", *current_number);

        (*insert_j)++;

        if (*insert_j == cols) {
            *insert_j = 0;
            fputc('\n', p2);
        }

        *bits_read_for_current_insert_index = 0;
        *current_number = 0x0;
    }
}

void convertCompressedToPGM(char* fname) {
    unsigned short rows, cols;
    unsigned char max_gray_level;
    unsigned int required_bits;
    char* p2_file_name = createNewFileExtension(fname, ".pgm");
    BYTE current_byte_read;
    unsigned int bits_read_from_current_byte = 0;
    unsigned int total_bits_to_read;
    unsigned int bit_counter = 0;
    unsigned int bits_read_for_current_insert_index = 0;
    unsigned int current_number = 0;

    FILE* p2 = fopen(p2_file_name, "w");
    FILE* compressed = fopen(fname, "rb");

    if (!p2 || !compressed)
        printf("Couldn't read file!\n");
    
    else {
        getHeaderFromCompressed(compressed, &rows, &cols, &max_gray_level);

        fprintf(p2, "P2\n%d %d\n%d\n", cols, rows, max_gray_level);

        required_bits = amountOfBitsNeeded(max_gray_level);
        total_bits_to_read = rows * cols * required_bits;

        fread(&current_byte_read, sizeof(BYTE), 1, compressed);
        bit_counter += CHAR_BIT;

        int insert_i = 0, insert_j = 0;

        while (bit_counter <= total_bits_to_read) {
            getDataFromByte(&current_byte_read, &current_number, 
                &bits_read_from_current_byte, &required_bits, &bit_counter
                ,&bits_read_for_current_insert_index, &insert_j, cols, compressed, p2);
        }

        fclose(p2);
        fclose(compressed);
    }
    
    free(p2_file_name);
}