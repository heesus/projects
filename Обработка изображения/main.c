#include "struct.h"

#include "read_png_file.h"
#include "write_png_file.h"
#include "replace_pixels.h"
#include "copy.h"
#include "find_rect.h"
#include "frame.h"


#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int isNumber(char *n){
    for(int i = 0; i < strlen(n); i++)
        if(!isdigit(n[i]))
            return 0;
    return 1; 
}


void printH()
{
    printf("Справка:\n\n");

    printf("--copy_img(-c) - делает копию заданного участка. Участок задается при помощи флагов -L и -R (координатами левого верхнего и правого нижнего углов области-источника соответственно) и -I (координатами левого верхнего угла области-назначения).\n\n");
    printf("*EXAMPLE* --copy_img -L 0 0 -R 40 100 -I 10 10 file_out.png\n\n");

    printf("--replace_pixels(-r) - Заменяет все пиксели одного заданного цвета на другой цвет. Цвет задается в формате RGB с помощью флагов -B для исходного цвета и -A для нового.\n\n");

    printf("*EXAMPLE* --replace_pixels -B 0 0 0 -A 255 255 255 file_out.png\n\n");

    printf("--find_rect(-f) - Поиск всех залитых прямоугольников заданного цвета. Задается цвет прямоугольников -B, цвет обводки -A, толщина линии -W.\n\n");

    printf("*EXAMPLE* --find_rect -B 0 0 0 -A 255 255 255 -W 1 file_out.png\n\n");

    printf("--draw_frame(-d) - Делает рамку в виде узора. Задается цвет узора -A, ширина -W, а тип рамки при помощи -T. \n\n");

    printf("*EXAMPLE* --draw_frame -A 10 32 0 -W 30 -T 2 file_out.png\n\n");

    printf("--left(-L) - считывет координаты *целый числа* верхнего левого угла прямоугольной области\n\n");

    printf("--right(-R) - считывет координаты *целый числа* нижнего правого угла прямоугольной области\n\n");

    printf("--insert(-I) - считывет координаты *целый числа* верхнего левого угла области-назначения\n\n");

    printf("--before(-B) - считывет исходный цвет в формате RGB\n\n");

    printf("--after(-A) - считывет выбранный цвет в формате RGB\n\n");

    printf("--width(-W) - считывает значение ширины в пикселях\n\n");

    printf("--type(-T) - считывает тип рамки (всего возможно 2 типа). По умолчанию стоит рамка с типом 1.\n\n");

	printf("******\n");
    printf("Строка команд должна заканчиваться названием файла вывода\n\n");
	printf("*EXAMPLE* ./myFakePaint file.png --replace_pixels -B 0 0 0 -A 255 255 255 file_out.png\n\n");
}



int main(int argc, char **argv){

    struct Png image;
    struct args arg;

    struct RGBA now;
    struct RGBA newColor;

    int flag = 0;
    int rez = 0;
    int longIndex = -1;

    for(int i = 0; i < 4; i++){
	if(i < 2){
	    arg.left[i] = -1;
	    arg.right[i] = -1;
	    arg.insert[i] = -1;
	}
	arg.before[i] = -1;
	arg.after[i] = -1;
    }

    arg.width = -1;
    arg.type = -1;

    static const char *optString = "crfdhL:R:I:B:A:W:T:";

    struct option longOpts[] = {
            {"copy_img", no_argument, NULL, 'c'},
            {"replace_pixels", no_argument, NULL, 'r'},
            {"find_rectangle", no_argument, NULL, 'f'},
            {"draw_frame", no_argument, NULL, 'd'},
            {"help", no_argument, NULL, 'h'},
            {"left", required_argument, NULL, 'L'},
            {"right", required_argument, NULL, 'R'},
            {"insert", required_argument, NULL, 'I'},
            {"before", required_argument, NULL, 'B'},
            {"after", required_argument, NULL, 'A'},
            {"widht", required_argument, NULL, 'W'},
            {"type", required_argument, NULL, 'T'},
            { NULL, no_argument, NULL, 0 }
    };



    if (strstr(argv[1], ".png") == NULL) {
        printf("Не введено имя файла для открытия. Для получения информации введите:\n");
        printf("./myFakePaint file.png -h\n");
        return 0;
    } else{
        read_png_file(&image, argv[1]);
    }
	
    while ((rez = getopt_long(argc, argv, optString , longOpts, &longIndex)) != -1) {
        switch (rez) {
        	case 'h':
                printH();
                return 0;
                
            case 'L':
                if (!isNumber(optarg)) {
                    printf("Не корректно введены аргументы для флага -L!\n");
                    return 0;
                }
                if (!isNumber(argv[optind])) {
                    printf("Не корректно введены аргументы для флага -L!\n");
                    return 0;
                }
                arg.left[0] = atoi(optarg);
                arg.left[1] = atoi(argv[optind]);
                break;


            case 'R':
                if (!isNumber(optarg) || !isNumber(argv[optind])) {
                    printf("Не корректно введены аргументы для флага -R!\n");
                    return 0;
                }
                arg.right[0] = atoi(optarg);
                arg.right[1] = atoi(argv[optind]);
                break;


            case 'I':
                if (!isNumber(optarg) || !isNumber(argv[optind])) {
                    printf("Не корректно введены аргументы для флага -I!\n");
                    return 0;
                }
                arg.insert[0] = atoi(optarg);
                arg.insert[1] = atoi(argv[optind]);
                break;

            case 'B':
                if(!isNumber(optarg) || !isNumber(argv[optind]) || !isNumber(argv[optind+1]))
                {
                    printf("Не корректно введены аргументы для флага -B!\n");
                    return 0;
                }
                if (atoi(optarg) > 255 || atoi(argv[optind]) > 255 || atoi(argv[optind + 1]) > 255
                    || atoi(optarg) < 0 || atoi(argv[optind]) < 0 || atoi(argv[optind + 1]) < 0)
                {
                    printf("Для флага -B введен несуществующий цвет!\n");
                    return 0;
                }
                arg.before[0] = atoi(optarg);
                arg.before[1] = atoi(argv[optind]);
                arg.before[2] = atoi(argv[optind + 1]);
                arg.before[3] = 255;
                break;

            case 'A':
                if(!isNumber(optarg) || !isNumber(argv[optind]) || !isNumber(argv[optind+1]))
                {
                    printf("Не корректно введены аргументы для флага -A!\n");
                    return 0;
                }
                if (atoi(optarg) > 255 || atoi(argv[optind]) > 255 || atoi(argv[optind + 1]) > 255
                    || atoi(optarg) < 0 || atoi(argv[optind]) < 0 || atoi(argv[optind + 1]) < 0)
                {
                    printf("Для флага -A введен несуществующий цвет!\n");
                    return 0;
                }
                arg.after[0] = atoi(optarg);
                arg.after[1] = atoi(argv[optind]);
                arg.after[2] = atoi(argv[optind + 1]);
                arg.after[3] = 255;
                break;

            case 'W':
                if(!isNumber(optarg))
                {
                    printf("Не корректно введены аргументы для флага -W!\n");
                    return 0;
                }
                if (atoi(optarg) >= MIN(image.width, image.height) / 4 || atoi(optarg) < 0) {
                    printf("Слишком большая толщина узора рамки или она меньше нуля.\n");
                    return 0;
                }
                arg.width = atoi(optarg);
                break;

            case 'T':
                if(!isNumber(optarg))
                {
                    printf("Не корректно введены аргументы для флага -T!\n");
                    return 0;
                }
                if (atoi(optarg) < 0 || atoi(optarg) > 2) {
                    printf("Введен несуществующий тип рамки!\n");
                    return 0;
                }
                arg.type = atoi(optarg);
                break;

            case'c':
                flag = 'c';
                break;

            case 'r':
                flag = 'r';
                break;
                
            case 'f':
                flag = 'f';
                break;
            
            case 'd':
                flag = 'd';
                break;

            default:
                printf("Такого флага не существует!\n");
                return 0;
	
			longIndex = -1;
        }

    }

	
    switch (flag){
    
        case 'c':
            if(arg.right[0] < 0 || arg.right[0] > image.width || arg.right[1] < 0 || arg.right[1] > image.height ||
               arg.left[0] > image.width || arg.left[0] < 0 || arg.left[1] > image.height || arg.left[1] < 0 ||
               arg.left[0] > arg.right[0] || arg.left[1] > arg.right[1] || arg.insert[0] < 0 || arg.insert[1] < 0 ||
               arg.insert[0] > image.width || arg.insert[1] > image.height)
            {
                printf("Область копирования не является корректной\n");
                break;
            }
            copy_img(&image, arg.left[0], arg.left[1], arg.right[0], arg.right[1], arg.insert[0], arg.insert[1]);
            break;

        case 'r':

            now.red = arg.before[0];
            now.green = arg.before[1];
            now.blue = arg.before[2];
            now.alpha = arg.before[3];

            newColor.red = arg.after[0];
            newColor.green = arg.after[1];
            newColor.blue = arg.after[2];
            newColor.alpha = arg.after[3];

            replace_pixels(&image, now, newColor);
            break;

        case 'f':
            now.red = arg.before[0];//цвет прямоугольников
            now.green = arg.before[1];
            now.blue = arg.before[2];
            now.alpha = arg.before[3];

            newColor.red = arg.after[0];//цвет обводки
            newColor.green = arg.after[1];
            newColor.blue = arg.after[2];
            newColor.alpha = arg.after[3];

            find_rectangle(&image, now, newColor, arg.width);
            break;
            
        case 'd':

            newColor.red = arg.after[0];//цвет обводки
            newColor.green = arg.after[1];
            newColor.blue = arg.after[2];
            newColor.alpha = arg.after[3];

            draw_frame(&image, newColor, arg.width, arg.type);
            break;

    }

    if (strstr(argv[argc - 1], ".png") == NULL) {
        printf("Не введено имя файла для записи\n");
        return 0;
    } else{
        write_png_file(&image, argv[argc - 1] );
    }

}
