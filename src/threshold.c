#include <stdlib.h>
#include <math.h>
#include "threshold.h"

int adaptiveThreshold(unsigned char *g, int n, float k) {
    double sum=0;
    for(int i=0;i<n;i++) sum+=g[i];
    double mean=sum/n;
    double s2=0;
    for(int i=0;i<n;i++) { double d=g[i]-mean; s2+=d*d; }
    double sd = sqrt(s2/n);
    int T = (int)(mean + k*sd);
    if (T < 0) {
    T = 0;
    } else if (T > 255) {
        T = 255;
    }
    return T;
}

unsigned char* thresholdImage(unsigned char *g, int n, int t) {
    unsigned char *bin=malloc(n);
    for(int i=0;i<n;i++) bin[i]=(g[i]<t)?255:0;
    return bin;
}
