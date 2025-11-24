#include <stdlib.h>
#include <string.h>
#include "noise.h"

void removeSmallNoise(unsigned char *bin,int w,int h){
    unsigned char *copy=malloc(w*h);
    memcpy(copy,bin,w*h);
    for(int y=1;y<h-1;y++){
        for(int x=1;x<w-1;x++){
            int count=0;
            for(int j=-1;j<=1;j++)
                for(int i=-1;i<=1;i++)
                    if(copy[(y+j)*w + (x+i)]==255) count++;
            if(count<=3) bin[y*w+x]=0;
        }
    }
    free(copy);
}
