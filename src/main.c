#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "gray.h"
#include "threshold.h"
#include "noise.h"
#include "color.h"
#include "canny.h"
#include "components.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: %s input.ppm output_prefix\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *prefix = argv[2];

    PPM img = readPPM(input_file);
    int w = img.width, h = img.height, n = w*h;

    unsigned char *gray = toGray(img);
    contrastStretch(gray, n);

    int T = adaptiveThreshold(gray, n, -0.5);
    unsigned char *bin = thresholdImage(gray, n, T);
    removeSmallNoise(bin, w, h);

    colorDarkPixelsRed(img.data, bin, w, h);

    char darkRedFile[256], maskFile[256], edgesFile[256];
    snprintf(darkRedFile, sizeof(darkRedFile), "%s_dark_pixels_red.ppm", prefix);
    snprintf(maskFile, sizeof(maskFile), "%s_mask_red_only.ppm", prefix);
    snprintf(edgesFile, sizeof(edgesFile), "%s_edges_cleaned.ppm", prefix);

    savePPM(darkRedFile, img.data, w, h);

    unsigned char *mask = makeRedMask(bin, w, h);
    savePPM(maskFile, mask, w, h);

    unsigned char *edges = cannyEdge(bin, w, h);
    removeSmallComponents(edges, w, h, 350);

    unsigned char *edgesRGB = grayToRGB(edges, n);
    savePPM(edgesFile, edgesRGB, w, h);

    printf("Done!\n1. %s\n2. %s\n3. %s\n", darkRedFile, maskFile, edgesFile);

    free(gray); free(bin); free(mask); free(edges); free(edgesRGB); free(img.data);

    return 0;
}
