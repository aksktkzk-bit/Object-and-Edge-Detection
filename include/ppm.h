#ifndef PPM_H
#define PPM_H

typedef struct {
    int width, height, maxval;
    unsigned char *data;
} PPM;

PPM readPPM(const char *filename);
void savePPM(const char *filename, unsigned char *rgb, int w, int h);

#endif
