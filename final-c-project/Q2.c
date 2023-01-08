#include "Q2.h"

GRAY_IMAGE* readPGM(char* fname) {
	return readPGMGeneric(fname, true);
}
