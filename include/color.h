#ifndef COLOR_H
#define COLOR_H

unsigned char* makeRedMask(unsigned char *bin, int w, int h);
void colorDarkPixelsRed(unsigned char *rgb,unsigned char *bin,int w,int h);
unsigned char* grayToRGB(unsigned char *gray,int n);

#endif
