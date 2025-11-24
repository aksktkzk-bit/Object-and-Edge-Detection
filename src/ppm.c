#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

static void skipComments(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) == '#')
        while(fgetc(fp) != '\n');
    fseek(fp, -1, SEEK_CUR);
}

PPM readPPM(const char *filename) {
    PPM img;
    FILE *fp = fopen(filename, "rb");
    if (!fp) { printf("Error opening %s\n", filename); exit(1); }

    char format[3];
    fscanf(fp, "%2s", format);
    skipComments(fp);
    fscanf(fp, "%d %d", &img.width, &img.height);
    skipComments(fp);
    fscanf(fp, "%d", &img.maxval);
    fgetc(fp);

    img.data = malloc(img.width * img.height * 3);
    fread(img.data, 1, img.width * img.height * 3, fp);
    fclose(fp);
    return img;
}

void savePPM(const char *filename, unsigned char *rgb, int w, int h) {
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    fwrite(rgb, 1, w*h*3, fp);
    fclose(fp);
}
