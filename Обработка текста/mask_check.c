#include "mask_check.h"

void mask_check(struct Text *text, wchar_t* patern)
{
    wchar_t *str, **new_str;
    wchar_t *buffer;
    wchar_t *exit_str;
    wchar_t *rp, *rs=0, *p;
    int j = 0;
    int exit = 0;
    fputws(L"\nПредложения, в которых каждое слово удовлетворяет введенной маске:\n",stdout);
    fwprintf(stdout, L"%s\n======================================TEXT======================================%s\n\n",RED,NON);
    for(int i = 0; i < text->size_text; i++)
    {
        str = malloc(sizeof(wchar_t)*(text->sentence[i].size_sentence+15));
        wcscpy(str,text->sentence[i].sentence);
        wchar_t* istr = wcstok(str, L" ,.", &buffer);
        while (istr != NULL)
        {
            p = patern;
            while(1)
            {
                if(*p == '*')
                {
                    rs = istr;
                    rp = ++p;
                }
                else if(!*istr)
                {
                    if(!*p)
                    {
                        exit +=1;
                        break;
                    }
                }
                else if(*istr == *p || *p == '?')
                {
                    ++istr;
                    ++p;
                }
                else if(rs)
                {
                    istr = ++rs;
                    p = rp;
                }
                else
                {
                    break;
                }
            }
            rs = 0;
            rp = 0;
            istr = wcstok(NULL, L" .,", &buffer);
        }
        free(str);
        if(exit == text->sentence[i].words)
        {
            fputws(text->sentence[i].sentence,stdout);
        }
        exit = 0;
    }
    fwprintf(stdout, L"%s\n\n================================================================================%s\n",RED,NON);
}

wchar_t* get_mask()
{
    fputws(L"\nВведите вашу маску (маска может содержать только один символ \"*\"):\n", stdout);
    wchar_t *mask, c;
    int max_size_m = 100, size_m = 0, i = 0;
    mask = malloc(max_size_m*sizeof(wchar_t));
    while((c = getwchar()) != '\n')
    {
        if(max_size_m - 3 == size_m)
        {
            max_size_m *= 2;
            mask = realloc(mask, max_size_m*sizeof(wchar_t));
        }
        mask[i] = c;
        i++;
    }
    mask[i] = '\0';
    return mask;
}
