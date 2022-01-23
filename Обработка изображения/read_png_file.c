#include "struct.h"
#include "read_png_file.h"


void read_png_file(struct Png* image, const char *file_name) {

    char header[8];    // 8 is the maximum size that can be checked
    int is_png;

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp) { 
		return;
	}

    fread(header, 1, 8, fp);
    is_png = !png_sig_cmp((png_const_bytep)(header), 0, 8); // по первым 8 битам определяем png ли это файл

    if (!is_png) { 
       	fclose(fp);
    	return; 
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); // иницилизация структуры png_structp
    if (!image->png_ptr) { 
    	fclose(fp);
    	return; 
    }

    image->info_ptr = png_create_info_struct(image->png_ptr); // иницилизауия структуры png_infop
    if (!image->info_ptr) {
        png_destroy_read_struct (&image->png_ptr,(png_infopp) NULL, (png_infopp) NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(image->png_ptr))) {
        png_destroy_read_struct(&image->png_ptr, (png_infopp)(&image->png_ptr), (png_infopp) NULL);
        fclose(fp);
        return;
    }

    png_init_io(image->png_ptr, fp); // говорю libpng, что дальше буду работать с этим файлом
    png_set_sig_bytes(image->png_ptr, 8); //сообщаем libpng, что считывали часть байтов для проверки подписи

    png_read_info(image->png_ptr, image->info_ptr); //read all the file information up to the actual image data

    image->width = png_get_image_width(image->png_ptr, image->info_ptr); // ширина
    image->height = png_get_image_height(image->png_ptr, image->info_ptr); // высота
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr); //тип
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr); // глубина


    if(image->bit_depth == 16)
        png_set_strip_16(image->png_ptr); //если глубин 16, то сужаем до 8

    if(image->bit_depth == PNG_COLOR_TYPE_PALETTE) // если присутсвтует палитра, то прегоняем к rgb
        png_set_palette_to_rgb(image->png_ptr);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(image->color_type == PNG_COLOR_TYPE_GRAY && image->bit_depth < 8) // если серый, то и глубина меньше 8
        png_set_expand_gray_1_2_4_to_8(image->png_ptr);

    if(png_get_valid(image->png_ptr, image->info_ptr, PNG_INFO_tRNS)) // если tRNS, то перегоняем в alpha
        png_set_tRNS_to_alpha(image->png_ptr);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(image->color_type == PNG_COLOR_TYPE_RGB ||
       image->color_type == PNG_COLOR_TYPE_GRAY ||
       image->color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(image->png_ptr, 0xFF, PNG_FILLER_AFTER); // даем всем типам alpha

    if(image->color_type == PNG_COLOR_TYPE_GRAY ||
       image->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(image->png_ptr); // серый перегоняем в RGB

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    image->color_type = 6;

    /* read file */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        return;
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (int i = 0; i < image->height; i++)
        image->row_pointers[i] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    image->pixel = (struct RGBA**)malloc(sizeof(struct RGBA*) * image->height);

    for (int i = 0; i < image->height; i++){
        image->pixel[i] = (struct RGBA*)malloc(sizeof(struct RGBA) * image->width);
    }

    for (int y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *ptr = &(row[x * 4]);
            image->pixel[y][x].red = ptr[0];
            image->pixel[y][x].green = ptr[1];
            image->pixel[y][x].blue = ptr[2];
            image->pixel[y][x].alpha = ptr[3];
        }
    }
    fclose(fp);
}
