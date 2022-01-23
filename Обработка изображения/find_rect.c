#include "struct.h"
#include "find_rect.h"

int comp(struct RGBA now, struct RGBA new){

    if (now.red == new.red && now.green == new.green && now.blue == new.blue && now.alpha == new.alpha)
        return 1;
    return 0;
}

int checBord(struct Png* image, int leftX, int leftY, int rightX, int rightY, struct RGBA now){

    if (leftX != 0)
        for (int i = leftY; i < rightY; i++) {
            if (comp(now, image->pixel[i][leftX - 1]))
                return 1;
        }

    if (leftY != 0)
        for (int j = leftX; rightX < j; j++) {
            if (comp(now, image->pixel[leftY - 1][j]))
                return 1;
        }
        
    if (rightX != image->width)
        for (int i = leftY; i < rightY; i++) {
            if (comp(now, image->pixel[i][rightX]))
                return 1;
        }
        
    if (rightY != image->height)
        for (int j = leftX; j < rightX; j++){
            if (comp(now, image->pixel[rightY][j]))
                return 1;
        }
        
    return 0;
}

void find_pixels(struct Png* image, int x, int y, struct RGBA now) {
    image->pixel[y][x].flag = 2;

    //размеры изображения
    int w = image->width;
    int h = image->height;

    // Выделим памяти для координат, которые надо проверить
    int STACK_SIZE = (w+2)*(h+2);
    int *pixelsX = (int*)malloc(STACK_SIZE*sizeof(int));
    int *pixelsY = (int*)malloc(STACK_SIZE*sizeof(int));


    int start = 0;
    int next = 0;


    pixelsX[start] = x;
    pixelsY[start] = y;
    start++;

    // Пока не кончится память или точки на изображении
    while (start < STACK_SIZE && start > next) { //проверим все точки нужного цвета, окруженные рамкой
        x = pixelsX[next];
        y = pixelsY[next];
        next++;

        if (x >= 0 && y >= 0 && x < w && y < h) {
            if (x + 1 == w)
                continue;
            if (image->pixel[y][x + 1].red == now.red &&
                image->pixel[y][x + 1].green == now.green &&
                image->pixel[y][x + 1].blue == now.blue &&
                image->pixel[y][x + 1].alpha == now.alpha &&
                image->pixel[y][x + 1].flag == 0) {

                pixelsX[start] = x + 1;
                pixelsY[start] = y;
                image->pixel[y][x + 1].flag = 2;

                start++;
            }
            
            if (x - 1 == -1)
                continue;
            if (image->pixel[y][x - 1].red == now.red &&
                image->pixel[y][x - 1].green == now.green &&
                image->pixel[y][x - 1].blue == now.blue &&
                image->pixel[y][x - 1].alpha == now.alpha &&
                image->pixel[y][x - 1].flag == 0) {

                pixelsX[start] = x - 1;
                pixelsY[start] = y;

                image->pixel[y][x - 1].flag = 2;
                start++;
            }

            if (y + 1 == h)
                continue;
            if (image->pixel[y + 1][x].red == now.red &&
                image->pixel[y + 1][x].green == now.green &&
                image->pixel[y + 1][x].blue == now.blue &&
                image->pixel[y + 1][x].alpha == now.alpha &&
                image->pixel[y + 1][x].flag == 0) {

                pixelsX[start] = x;
                pixelsY[start] = y + 1;
                image->pixel[y + 1][x].flag = 2;
                start++;
            }

            if (y - 1 == -1)
                continue;
            if (image->pixel[y - 1][x].red == now.red &&
                image->pixel[y - 1][x].green == now.green &&
                image->pixel[y - 1][x].blue == now.blue &&
                image->pixel[y - 1][x].alpha == now.alpha &&
                image->pixel[y - 1][x].flag == 0) {

                pixelsX[start] = x;
                pixelsY[start] = y - 1;
                image->pixel[y - 1][x].flag = 2;
                start++;
            }
        }
    }
    
    free(pixelsY);
    free(pixelsX);
}

struct Point find_clr(struct Png* image, struct RGBA now){
    int x, y;
    struct Point tmp;
    tmp.x = -1;

    for (y = 0; y < image->height; y++) {
        for (x = 0; x < image->width; x++) {
            if (comp(image->pixel[y][x], now) && image->pixel[y][x].flag == 0) {
                tmp.x = x;
                tmp.y = y;
                find_pixels(image, x, y, now);
                return tmp;
            }
        }
    }
    return tmp;
}		




void find_rectangle(struct Png* image, struct RGBA now, struct RGBA newColor, int size){

    int x = 0, y = 0;
    int i = 0, j = 0;

    int leftX;
    int leftY;
    int rightX;
    int rightY;

    int sizeXL;
    int sizeYL;
    int sizeXR;
    int sizeYR;

    int flag = 0;
    int count = 1;

    struct Rectangle* rect = NULL;
    struct Point tmp = find_clr(image, now);


    while(tmp.x != -1){
        leftY = tmp.y;
        leftX = tmp.x;
        i = 0;
        j = 0;
        flag = 0;

        while(leftY + i < image->height && image->pixel[leftY + i][leftX].flag  == 2){//ищем предпологаемую границу
            i++;
        }
        rightY = leftY + i;

        while(leftX + j < image->width && image->pixel[leftY][leftX + j].flag == 2){//ищем предпологаемую границу
            j++;
        }
        rightX = leftX + j;


        for (y = leftY; y < rightY; y++) {
            for (x = leftX; x < rightX; x++)
                if (image->pixel[y][x].flag != 2) {
                    flag = 1;
                    break;
                }
            if (flag)
                break;
        }

        if (checBord(image, leftX, leftY, rightX, rightY, now))//проверяем, является ли найденная обл границей прямоугольника
            flag = 1;


        if (flag != 1) {//если да, то запоминаем координаты
            rect = (struct Rectangle*)realloc(rect, count * sizeof(struct Rectangle));
            rect[count - 1].leftY = leftY;
            rect[count - 1].leftX = leftX;
            rect[count - 1].rightY = rightY;
            rect[count - 1].rightX = rightX;
            count++;
        }
        
       tmp = find_clr(image, now);
    }


    for (int l = 0; l < count - 1; l++){
    	//проверка на выход обводки за пределы изображения
		if(rect[l].leftX - size < 0){
			sizeXL = 0;
		}else{
			sizeXL = rect[l].leftX - size;
		}
		
		if(rect[l].leftY - size < 0){
			sizeYL = 0;
		}else{
			sizeYL = rect[l].leftY - size;
		}
		
		if(rect[l].rightX + size > image->width){
			sizeXR = image->width;
		}else{
			sizeXR = rect[l].rightX + size;
		}
		
		if(rect[l].rightY + size > image->height){
			sizeYR = image->height;
		}else{
			sizeYR = rect[l].rightY + size;
		}

		//обводим прямоугольники
        for (j = sizeYL; j < rect[l].leftY; j++)
            for (i = sizeXL; i < sizeXR; i++)
                image->pixel[j][i] = newColor;

        for (j = rect[l].rightY; j < sizeYR; j++)
            for (i = sizeXL; i < sizeXR; i++)
                image->pixel[j][i] = newColor;

        for (i = sizeXL; i < rect[l].leftX; i++)
            for (j = rect[l].leftY; j < rect[l].rightY; j++)
                image->pixel[j][i] = newColor;

        for (i = rect[l].rightX; i < sizeXR; i++)
            for (j = rect[l].leftY; j < rect[l].rightY; j++)
                image->pixel[j][i] = newColor;

    }

    for (int l = 0; l < count - 1; l++) // если обводка наехала на какой-нибудь прямоугольник, то мы заливаем этот прямоугольник
        for (j = rect[l].leftY; j < rect[l].rightY; j++)
            for (i = rect[l].leftX; i < rect[l].rightX; i++)
                image->pixel[j][i] = now;


}
