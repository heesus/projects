#include "main.h"

int main()
{
    setlocale(LC_ALL, "");
    struct Text text;
    fputws(L"Введите текст:\n",stdout);
    Input(&text);
    del_sent(&text);
    Output(&text);
    int n;
    while((n = menu()) != 0)
    {
        switch(n)
        {
        case 1:
            Output(&text);
            break;
        case 2:
            mask_check(&text, get_mask());
            break;
        case 3:
            av_l_sort(&text);
            fwprintf(stdout, L"\n%sDONE!%s\n",GREEN,NON);
            break;
        case 4:
            convert_sent(&text);
            fwprintf(stdout, L"\n%sDONE!%s\n",GREEN,NON);
            break;
        case 5:
            del_m5_l2(&text);
            fwprintf(stdout, L"\n%sDONE!%s\n",GREEN,NON);
            break;
        default:
            fputws(L"Введенный символ не опознан. Введите корректное значение!\n",stdout);
            break;
        }
    }
    for(int i = 0; i < text.size_text; i++)
    {
        free(text.sentence[i].sentence);
    }
    free(text.sentence);
    return 0;
}
