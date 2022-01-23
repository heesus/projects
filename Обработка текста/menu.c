#include "menu.h"

int menu()
{
    wchar_t inp[90];
    wchar_t *end;
    fputws(L"\nВведите номер:\n\n",stdout);
    fputws(L"1 - Чтобы вывести текст.\n",stdout);
    fputws(L"2 - Чтобы найти все предложения, в которых каждое слово удовлетворяет вашей маске. \n",stdout);
    fputws(L"3 - Чтобы отсортировать предложения по средней длине слов в предложении.\n",stdout);
    fputws(L"4 - Для преобразования предложений так, чтобы слова располагались в порядке уменьшения длины слова.\n",stdout);
    fputws(L"5 - Чтобы удалить все предложения, в которых больше 5 или меньше 2 слов.\n",stdout);
    fputws(L"0 - Для выхода из программы.\n",stdout);
    int k = 0;
    while((inp[k] = getwchar()) != '\n')
    {
        k++;
    }
    if (inp[0] == '\n')
    {
        return 21;
    }
    fputws(L"\n",stdout);
    for (int i = 0; i < k; i++)
    {
        if (iswdigit(inp[i]))
        {
            continue;
        }
        else
        {
            return 21;
            break;
        }
    }
    return (wcstol(inp,&end,10));
}
