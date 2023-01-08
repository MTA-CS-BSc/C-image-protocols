#include "utils.h"

COLOR_IMAGE* readPPM(char* fname) {
	return readPPMGeneric(fname, true);
}


