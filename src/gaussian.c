#include <stdlib.h>
#include "gaussian.h"

unsigned char* gaussianBlur(unsigned char *src, int w, int h) {
    unsigned char *out = malloc(w*h);

    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    for(int y=1;y<h-1;y++){
        for(int x=1;x<w-1;x++){
            int sum = 0;
            for(int j=-1;j<=1;j++)
                for(int i=-1;i<=1;i++)
                    sum += src[(y+j)*w + (x+i)] * kernel[j+1][i+1];

            out[y*w+x] = sum / 16;
        }
    }

    for(int x=0;x<w;x++){
        out[x] = src[x];
        out[(h-1)*w + x] = src[(h-1)*w + x];
    }
    for(int y=0;y<h;y++){
        out[y*w] = src[y*w];
        out[y*w+(w-1)] = src[y*w+(w-1)];
    }

    return out;
}
