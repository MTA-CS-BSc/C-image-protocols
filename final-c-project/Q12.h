#ifndef __Q12_H
#define __Q12_H
#include "utils.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"
#include "Q7.h"
#include "Q8.h"
#include "Q9.h"
#include "Q10.h"
#include "Q11.h"

// A function to print a menu of options to choose from.
void printMenu();

// Reads a P2 PGM file (file name received from input).
// Creates a GRAY_IMAGE and returns it's ref.
GRAY_IMAGE* readP2Image();

// Reads a P3 PGM file (file name received from input).
// Creates a COLOR_IMAGE and returns it's ref.
COLOR_IMAGE* readP3Image();

// Reads segments from a P2 pgm image with given threshold (receives from input).
// If no image is loaded, the user will be asked to load an image.
void findSegments(IMG_POS_LIST** segments, GRAY_IMAGE** p2_image, int* segments_amount);

// Receives segments of an image and their amount, and a P2 PGM image.
// If no segments are loaded, the function will attempt to load them.
// Creates a new gray image with the same gray level calculated from the segments and the image received.
// Returns the created gray image ref.
void colorWithSameGrayLevel(IMG_POS_LIST** segments, GRAY_IMAGE** p2_image,
	int* segments_amount, GRAY_IMAGE** p2_with_same_gray_level);

// Receives a gray image with same gray level for each segment ref and a file name.
// The function writes the gray image to a P2 PGM file.
void saveGrayImageToP2(GRAY_IMAGE* p2_with_same_gray_level,
	char* file_name);

// Saves a P2 gray image with the same gray level for each segment with a name that is received from the user.
// If no gray image with same gray level is found, the function will attempt to create one.
void saveSameGrayColoredToPgm(GRAY_IMAGE** p2_with_same_gray_level,
	IMG_POS_LIST** segments, GRAY_IMAGE** p2_image,
	int* segments_amount);

// A function to convert a P3 PPM file to a P2 PGM file.
void convertP3ToP2();

// A function to convert a P2 PGM file to black & white files (3 for each 2 <= k <= 4).
void convertP2ToBW();

// A function to convert a P6 PPM file to a P5 PGM file.
void convertP6ToP5();

// A function to convert a P5 PGM file to black & white files (3 for each 2 <= k <= 4).
void convertP5ToBW();

// Receives a P2 PGM ref and saves it in the compressed form described in Q6.
void saveCompressedPGM(GRAY_IMAGE** p2_image);

// Reads a compressed file name from the user and converts it to a P2 PGM file.
void convertCompressedFileToPGM();
#endif