#include "utils.h"
#include "Q6.h"


void print_bits(const char* filename) {
    FILE* file = fopen(filename, "rb");

    unsigned short rows, cols;
    unsigned char max_gray_level;

    fread(&rows, sizeof(unsigned short), 1, file);
    fread(&cols, sizeof(unsigned short), 1, file);
    fread(&max_gray_level, sizeof(unsigned char), 1, file);

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    unsigned char c;

    while (fread(&c, sizeof(unsigned char), 1, file) == 1) {
        for (int i = 7; i >= 0; i--) {
            putchar((c >> i) & 1 ? '1' : '0');
            if (i == 4)
                printf(" ");
        }

        printf("\n");
    }

    fclose(file);
}

void getHeader(FILE* compressed, unsigned int* rows, unsigned int* cols, unsigned char* max_gray_level) {
    fread(rows, sizeof(unsigned short), 1, compressed);
    fread(cols, sizeof(unsigned short), 1, compressed);
    fread(max_gray_level, sizeof(unsigned char), 1, compressed);
}

BYTE setAllBitInRange(BYTE n, int l, int r)
{
    // calculating a number 'range' having set
    // bits in the range from l to r and all other
    // bits as 0 (or unset).
    int range = (((1 << (l - 1)) - 1) ^
        ((1 << (r)) - 1));

    return (n | range);
}

unsigned int minimum(unsigned int val1, unsigned int val2) {
    return val1 < val2 ? val1 : val2;
}

BYTE setBit(BYTE ch, int i)
{
    BYTE mask = 1 << i;
    return ch | mask;
}

// 1111 1111

// l = 1, r = 5

BYTE setBitsInRange(BYTE ch, int l, int r) {

    for (int i = 8 - l; i >= 8 - r; i--)
        ch = setBit(ch, i);

    return ch;
}
int createMask(unsigned int bits_to_read) {
    
    // 1110 0000
    // 0000 0001
    // 1000 0000
}
// [b1b2b3b4 b5b6b7b8], bits_read = 0/3
// Shift left bits_read bits
// [b1b2b3b4 b5b6b7b8]
// min (required_bits, 8 - bits_read_from_current_byte) -> how much i need to read atm
// extra_to_read_from_next = required_bits - how much i need to read atm
void insertDataToMat(BYTE* current_byte,
    unsigned int* bits_read_from_current_byte, unsigned char* required_bits,
    unsigned int* bit_counter, unsigned int* bits_read_for_current_insert_index,
    char** matrix, int* insert_i, int* insert_j, int cols, FILE* fp) {
    
    BYTE mask_for_extract = 0;
    //BYTE without_read_bits = *current_byte << *bits_read_from_current_byte;
    BYTE without_read_bits;

    unsigned int bits_to_read = minimum(*required_bits - *bits_read_for_current_insert_index, 8 - *bits_read_from_current_byte);
    mask_for_extract = setBitsInRange(mask_for_extract, *bits_read_from_current_byte + 1,
        *bits_read_from_current_byte + bits_to_read);

    // current_byte = [ 0001 1001]
    // mask =           [ 000 0111]

    without_read_bits = *current_byte & mask_for_extract;

    // [0000 b1b2b300]
    // 
    // >> shift right 8 - *bits_read_from_current_byte + bits_to_read
    // [0000 00b1b2b3]
    // matrix[i][j] << *required_bits - bits_to_read;
    // matrix[i] = new_shifted
    // without_read_bits = [ 0000 0001]

    without_read_bits >>= (8 - (*bits_read_from_current_byte + bits_to_read)); // push to end
    matrix[*insert_i][*insert_j] <<= (*required_bits - *bits_read_for_current_insert_index);
    matrix[*insert_i][*insert_j] |= without_read_bits;

    *bits_read_from_current_byte += bits_to_read;
    *bits_read_for_current_insert_index += bits_to_read;
    

    if (*bits_read_from_current_byte == CHAR_BIT) {
        fread(current_byte, sizeof(BYTE), 1, fp);
        *bits_read_from_current_byte = 0;
        *bit_counter += CHAR_BIT;
    }

    if (*bits_read_for_current_insert_index == *required_bits) {
        (*insert_j)++;

        if (*insert_j == cols) {
            *insert_j = 0;
            (*insert_i)++;
        }

        *bits_read_for_current_insert_index = 0;
    }

    
    // bits_to_read = min(8 - bits_read_from_current_byte, required_bits - bits_read_for_current_insert_index)
    // [b1b2b3b4 b5b6b7b8], bits_read = 3
    // shifted = [b4b5b6b7 b8 000], bits_to_read = 2
    // mask =       [1100 0000]

   // shifted = shifted & mask
    // shifted = [b4b5 00 0000]
    // *bits_read_from_current_byte += bits_to_read;
    // *bits_read_for_current_insert_index += bits_to_read;
    // 
    // 
    // if *bits_read_from_current_byte == 8 {
    //  fread(current_byte)
    // *bits_read_from_current_byte = 0
    // *bit_counter += CHAR_BIT
    // 
    // mat[i][j] = [b1b2b3b4 b5b6b7b8] 
    // shifted = shifted >> bits_read_for_current_insert_index (nagid 3)
    // shifted = [ 000 b4b5 000]
    // mat[i][j] |= shifted
    // 
    // if *bits_read_for_current_insert_index == *required_bits
    // *insert_i++;
    // *insert_j++;
    // 





   // if *bits_read_for_current_insert_index == *required_bits
    // 
}

void convertCompressedToPGM(char* fname) {
    print_bits(fname);
    unsigned short rows, cols;
    unsigned char max_gray_level;
    unsigned int required_bits;
    char* p2_file_name = createNewFileExtension(fname, "pgm");
    BYTE current_byte_read;
    unsigned int bits_read_from_current_byte = 0;
    unsigned int total_bits_to_read;
    unsigned int bit_counter = 0;
    unsigned int bits_read_for_current_insert_index = 0;

    FILE* p2 = fopen(p2_file_name, "w");
    FILE* compressed = fopen(fname, "rb");

    getHeader(compressed, &rows, &cols, &max_gray_level);

    fprintf(p2, "P2\n%d %d\n%d\n", cols, rows, max_gray_level);
    
    required_bits = amountOfBitsNeeded(max_gray_level);
    total_bits_to_read = rows * cols * required_bits;
       
    fread(&current_byte_read, sizeof(BYTE), 1, compressed);
    bit_counter += CHAR_BIT;
    
    unsigned char** matrix = createMatrix(rows, cols);
    int insert_i = 0, insert_j = 0;

    while (bit_counter < total_bits_to_read) {
        insertDataToMat(&current_byte_read, &bits_read_from_current_byte, &required_bits, &bit_counter
            ,&bits_read_for_current_insert_index, matrix, &insert_i, &insert_j, cols, compressed);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(p2, "%d ", matrix[i][j]);

        fputc('\n', p2);
    }

    fclose(p2);
    fclose(compressed);
    free(p2_file_name);
}