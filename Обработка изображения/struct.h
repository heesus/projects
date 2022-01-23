#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

#include <png.h>

struct RGBA{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    int flag;
};

struct args{
    int left[2];
    int right[2];
    int insert[2];
    int before[4];
    int after[4];
    int width;
    int type;
};

struct Rectangle {
    int leftX;
    int leftY;
    int rightX;
    int rightY;
};


struct Point{
    int x;
    int y;
};

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
    struct RGBA** pixel;
};


#endif
