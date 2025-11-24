#ifndef GRAY_H
#define GRAY_H

#include "ppm.h"

unsigned char* toGray(PPM img);
void contrastStretch(unsigned char *g, int n);

#endif
