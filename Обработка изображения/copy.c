#include "struct.h"
#include "copy.h"

void copy_img(struct Png* image, int x1, int y1, int x2, int y2, int x3,int y3) {

    struct RGBA** tmp;

    int height = y2 - y1;
    int width = x2 - x1;

    int maxX = 0, maxY = 0;

    if (x1 > image->width || y1 > image->height || x2 > image->width || y2 > image->height || x3 > image->width || y3 > image->height){
        return;
	}
	
	if(width + x3 > image->width){
		maxX = image->width - 1;
	}
	else{
		maxX = width + x3;
	}
	
	if(height + y3 > image->height){
		maxY = image->height - 1;
	}
	else{
		maxY = height + y3;
	}
	
    tmp = (struct RGBA**)malloc(sizeof(struct RGBA*) * height);
    for (int i = 0; i < height; i++){
        tmp[i] = (struct RGBA*)malloc(sizeof(struct RGBA) * width);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            tmp[y][x] = image->pixel[y + y1][x + x1];
        }
    }

    for (int y = y3; y < maxY; y++) {
        for (int x = x3; x < maxX; x++) {
            image->pixel[y][x] = tmp[y - y3][x - x3];
        }
    }
}
