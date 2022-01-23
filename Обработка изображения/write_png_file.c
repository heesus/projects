#include "struct.h"
#include "write_png_file.h"

void write_png_file(struct Png* image, const char *file_name) {

    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {return; }

    /* initialize stuff */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr) { return; }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr) { return; }

    if (setjmp(png_jmpbuf(image->png_ptr))) { return; }

    png_init_io(image->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(image->png_ptr))) { return; }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    /* write bytes */

    for (int y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * 4]);
            ptr[0] = image->pixel[y][x].red;
            ptr[1] = image->pixel[y][x].green;
            ptr[2] = image->pixel[y][x].blue;
            ptr[3] = image->pixel[y][x].alpha;
        }
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) { return; }

    png_write_image(image->png_ptr, image->row_pointers);

    /* end write */
    if (setjmp(png_jmpbuf(image->png_ptr))) { return; }

    png_write_end(image->png_ptr, NULL);

    /* cleanup heap allocation */


    for (int y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    for(int i = 0; i < image->height; i++)
        free(image->pixel[i]);
    free(image->pixel);


    fclose(fp);
}
