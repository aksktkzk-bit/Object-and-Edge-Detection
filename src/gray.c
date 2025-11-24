#include <stdlib.h>
#include "gray.h"

unsigned char* toGray(PPM img) {
    int n = img.width * img.height;
    unsigned char *g = malloc(n);
    for (int i = 0; i < n; i++) {
        int r = img.data[3*i];
        int g2 = img.data[3*i+1];
        int b = img.data[3*i+2];
        g[i] = (r + g2 + b) / 3;
    }
    return g;
}

void contrastStretch(unsigned char *g, int n) {
    unsigned char mn = 255, mx = 0;
    for (int i=0;i<n;i++){
        if(g[i]<mn) mn=g[i];
        if(g[i]>mx) mx=g[i];
    }
    if(mx==mn) return;
    for(int i=0;i<n;i++)
        g[i] = 255.0*(g[i]-mn)/(mx-mn);
}
