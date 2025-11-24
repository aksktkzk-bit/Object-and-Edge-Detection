#include <stdlib.h>
#include "color.h"

unsigned char* grayToRGB(unsigned char *gray, int n) {
    unsigned char *rgb = malloc(n * 3);
    for (int i = 0; i < n; i++) {
        rgb[3*i]   = gray[i];
        rgb[3*i+1] = gray[i];
        rgb[3*i+2] = gray[i];
    }
    return rgb;
}

void colorDarkPixelsRed(unsigned char *rgb, unsigned char *bin, int w, int h) {
    int n = w * h;
    for (int i = 0; i < n; i++) {
        if (bin[i] == 0) { // dark pixel
            rgb[3*i]   = 255;
            rgb[3*i+1] = 0;
            rgb[3*i+2] = 0;
        }
    }
}

unsigned char* makeRedMask(unsigned char *bin, int w, int h) {
    int n = w * h;
    unsigned char *rgb = malloc(n * 3);
    for (int i = 0; i < n; i++) {
        if (bin[i] == 0) {
            rgb[3*i]   = 255;
            rgb[3*i+1] = 0;
            rgb[3*i+2] = 0;
        } else {
            rgb[3*i]   = 0;
            rgb[3*i+1] = 0;
            rgb[3*i+2] = 0;
        }
    }
    return rgb;
}
