#include <stdlib.h>
#include "components.h"

static int floodFill(int *labels,unsigned char *edges,int w,int h,int x,int y,int label){
    if(x<0||x>=w||y<0||y>=h) return 0;
    if(edges[y*w+x]==0 || labels[y*w+x]!=0) return 0;
    labels[y*w+x]=label;
    int size=1;
    for(int j=-1;j<=1;j++)
        for(int i=-1;i<=1;i++)
            size+=floodFill(labels,edges,w,h,x+i,y+j,label);
    return size;
}

void removeSmallComponents(unsigned char *edges,int w,int h,int minSize){
    int *labels=calloc(w*h,sizeof(int));
    int label=1;
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            if(edges[y*w+x]>0 && labels[y*w+x]==0){
                int compSize=floodFill(labels,edges,w,h,x,y,label);
                if(compSize<minSize){
                    for(int i=0;i<w*h;i++) if(labels[i]==label) edges[i]=0;
                }
                label++;
            }
        }
    }
    free(labels);
}
