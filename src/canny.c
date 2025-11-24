#include <stdlib.h>
#include <math.h>
#include "canny.h"
#include "gaussian.h"

static unsigned char* nonMaxSuppression(int *gx, int *gy, unsigned char *mag, int w, int h) {
    unsigned char *nms = calloc(w*h, 1);

    for (int y = 1; y < h-1; y++) {
        for (int x = 1; x < w-1; x++) {
            int idx = y*w + x;

            float angle = atan2(gy[idx], gx[idx]) * 180.0 / M_PI;
            if (angle < 0) angle += 180;

            int m = mag[idx];
            int m1 = 0, m2 = 0;

            if ((angle >=   0 && angle < 22.5) || (angle >= 157.5 && angle <= 180)) {
                m1 = mag[idx - 1];
                m2 = mag[idx + 1];
            }
            else if (angle >= 22.5 && angle < 67.5) {
                m1 = mag[(y-1)*w + (x+1)];
                m2 = mag[(y+1)*w + (x-1)];
            }
            else if (angle >= 67.5 && angle < 112.5) {
                m1 = mag[(y-1)*w + x];
                m2 = mag[(y+1)*w + x];
            }
            else if (angle >= 112.5 && angle < 157.5) {
                m1 = mag[(y-1)*w + (x-1)];
                m2 = mag[(y+1)*w + (x+1)];
            }

            if (m >= m1 && m >= m2)
                nms[idx] = m;
            else
                nms[idx] = 0;
        }
    }

    return nms;
}

unsigned char* cannyEdge(unsigned char *src, int w, int h) {

    unsigned char *blur = gaussianBlur(src, w, h);

    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    int *gx = calloc(w*h,sizeof(int));
    int *gy = calloc(w*h,sizeof(int));
    unsigned char *mag = malloc(w*h);

    for(int y=1;y<h-1;y++){
        for(int x=1;x<w-1;x++){
            int sx=0, sy=0;
            for(int j=-1;j<=1;j++)
                for(int i=-1;i<=1;i++){
                    int p = blur[(y+j)*w + (x+i)];
                    sx += p * Gx[j+1][i+1];
                    sy += p * Gy[j+1][i+1];
                }
            gx[y*w+x] = sx;
            gy[y*w+x] = sy;

            int m = sqrt(sx*sx + sy*sy);
            if (m > 255) m = 255;
            mag[y*w+x] = m;
        }
    }

    free(blur);

    unsigned char *nms = nonMaxSuppression(gx, gy, mag, w, h);

    unsigned char *edges = calloc(w*h,1);
    int high = 80;
    int low  = 40;

    for(int i=0;i<w*h;i++)
        if(nms[i] >= high)
            edges[i] = 255;

    for(int i=0;i<w*h;i++){
        if(nms[i] >= low && edges[i]==0){
            int y=i/w, x=i%w;
            for(int j=-1;j<=1;j++)
                for(int k=-1;k<=1;k++){
                    int yy=y+j, xx=x+k;
                    if(yy<0||yy>=h||xx<0||xx>=w) continue;
                    if(nms[yy*w+xx] >= high)
                        edges[i] = 255;
                }
        }
    }

    free(gx); free(gy); free(mag); free(nms);

    return edges;
}
