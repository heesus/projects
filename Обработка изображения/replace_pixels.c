#include "struct.h"
#include "replace_pixels.h"

void replace_pixels(struct Png* image, struct RGBA now, struct RGBA newColor){

    int x = 0, y = 0;
    for (y = 0; y < image->height; y++) {
        for (x = 0; x < image->width; x++) {
            if (image->pixel[y][x].red == now.red && image->pixel[y][x].green == now.green && image->pixel[y][x].blue == now.blue && image->pixel[y][x].alpha == now.alpha)
                image->pixel[y][x] = newColor;
        }
    }
}
