#include "struct.h"
#include "frame.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void drawLine(struct Png *image, int x1, int y1, int x2, int y2, struct RGBA now) {

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
	int signX;
	int signY;
	
	if(x1<x2){
		signX = 1;
	}
	else{
		signX = -1;
	}
	
	if(y1<y2){
		signY = 1;
	}
	else{
		signY = -1;
	}

    int error = deltaX - deltaY;

    if ((x2 >= 0) && (x2 < image -> width) && (y2 >= 0) && (y2 < image -> height)){
        image->pixel[y2][x2] = now;
    }


    while(x1 != x2 || y1 != y2){
        if ((x1 >= 0) && (x1 < image -> width) && (y1 >= 0) && (y1 < image -> height)){
            image->pixel[y1][x1] = now;
		}
		
        const int error2 = error * 2;

        if(error2 > -deltaY){
            error -= deltaY;
            x1 += signX;
        }

        if(error2 < deltaX){
            error += deltaX;
            y1 += signY;
        }
    }
}

void frameType1(struct Png *image, int width, struct RGBA now) {
    struct RGBA newColor;
    newColor.red = 255 - now.red;
    newColor.green = 255 - now.green;
    newColor.blue = 255 - now.blue;
    newColor.alpha = 255;

    for (int y = image -> height - 1; y>=0 ;y -= 10) {
        drawLine(image, 0, 0, image->width - 1, y, newColor);
    }
    for (int x = image -> width - 1; x>=0 ;x -= 10) {
        drawLine(image, 0, 0, x, image->height - 1, newColor);
    }
    for (int y = 0; y<image->height ;y += 10) {
        drawLine(image, 0, y, image->width, image->height, newColor);
    }
    for (int x = 0; x<image->width ;x += 10) {
        drawLine(image, x, 0, image->width, image->height, newColor);
    }
}

void frameType2(struct Png *image, int width, struct RGBA now) {
    struct RGBA newColor;
    int step = width / 3;
    for (int y = 0; y < image->height; y += step) {
        for (int x = 0; x < image->width; x += step) {
            if(now.red + 30 > 255)
            	newColor.red = rand() % 60 + 194;
            else if(now.red - 30 < 0)
            	newColor.red = rand() % 60;
            else 
            	newColor.red = rand() % 60 + (now.red - 30);
            	
            if(now.green + 30 > 255)
            	newColor.green = rand() % 60 + 194;
            else if(now.green - 30 < 0)
            	newColor.green = rand() % 60;
            else 
            	newColor.green = rand() % 60 + (now.blue - 30);
            	
            if(now.blue + 30 > 255)
            	newColor.blue = rand() % 60 + 194;
            else if(now.blue - 30 < 0)
            	newColor.blue = rand() % 60;
            else 
            	newColor.blue = rand() % 60 + (now.blue - 30);
            	
            newColor.alpha = 255;
		    for (int i = y; i < image -> height; i++)
		        for (int j = x; j < image -> width; j++) {
		            image->pixel[i][j] = newColor;
		        }
        }
    }
}

void draw_frame(struct Png *image, struct RGBA now, int width, int type) {
    int w = image->width;
    int h = image->height;

    int lenX = image->width + 2 * width;
    int lenY = image->height + 2 * width;

    struct RGBA** new_pixel =  (struct RGBA**)malloc(sizeof(struct RGBA*) * h); // выдедения памяти для временного хранения изображения
    for (int i = 0; i < h; i++){
        new_pixel[i] = (struct RGBA*)malloc(sizeof(struct RGBA) * w);
    }

    for(int i = 0; i < h; i++) // заполение буфера
        for (int j = 0; j < w; j++) {
            new_pixel[i][j] = image->pixel[i][j];
        }
    image->pixel = (struct RGBA**)realloc(image->pixel, sizeof(struct RGBA*) * lenY); // расширение изначального изображения под рамку
    for (int i = 0; i < lenY; i++){
        image->pixel[i] = (struct RGBA*)realloc(image->pixel[i], sizeof(struct RGBA) * lenX);
    }

    image->row_pointers = (png_bytep*)realloc(image->row_pointers, lenY * sizeof(png_bytep)); // расширение row_pointers
    for (int i = 0; i < lenY; i++) {
        image->row_pointers[i] = (png_byte*)realloc(image->row_pointers[i], sizeof(png_byte) * 4 * lenX);
    }
    image->width = lenX;
    image->height = lenY;


    for (int i = 0; i < lenY; i++)
        for(int j = 0; j < lenX; j++)
            image->pixel[i][j] = now;

    switch (type) {
        case 1:
            frameType1(image, width, now);
            break;
        case 2:
            frameType2(image, width, now);
            break;
    }

    for (int i = width; i < lenY - width; i++) // помещение изображеня в середину
        for (int j = width; j < lenX - width; j++)
            image->pixel[i][j] = new_pixel[i - width][j - width];

    for (int y = 0; y < h; y++)
        free(new_pixel[y]);
    free(new_pixel);

 }
