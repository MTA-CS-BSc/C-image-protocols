#ifndef __BITS_UTILS_H
#define __BITS_UTILS_H

#include <stdbool.h>
#include <stdio.h>

#define BITS_IN_CHAR 8

typedef unsigned char BYTE;

// Returns 0 if the I-th bit is not set, not 0 otherwise (translated as bool).
int isIBitSet(BYTE ch, int i);

// Receives a number (< 127) and returns the amount of bits needed to write it.
int amountOfBitsNeeded(unsigned char max_gray_level);

// Receives a byte and an index of a bit and returns a byte with the i-index set.
BYTE setBit(BYTE ch, int i);

// Receives a byte and left & right indexes and sets all the bits in the range.
BYTE setBitsInRange(BYTE ch, int l, int r);
#endif