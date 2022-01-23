#include "convert_sent.h"

int cmp_for_convert_sent(const void *a, const void *b)
{
    if(wcslen(*(wchar_t**)a) > wcslen(*(wchar_t**)b))
        return -1;
    if(wcslen(*(wchar_t**)a) == wcslen(*(wchar_t**)b))
        return 0;
    if(wcslen(*(wchar_t**)a) < wcslen(*(wchar_t**)b))
        return 1;
}

void convert_sent(struct Text *text)
{
    wchar_t *str, **new_str;
    wchar_t *buffer;
    wchar_t *exit_str;
    int j = 0;
    for(int i = 0; i < text->size_text; i++)
    {
        str = malloc(sizeof(wchar_t)*(text->sentence[i].size_sentence+15));
        wcscpy(str,text->sentence[i].sentence);
        new_str = malloc(sizeof(wchar_t*)*(text->sentence[i].words+15));
        wchar_t* istr = wcstok(str, L" ,.", &buffer);
        while (istr != NULL)
        {
            new_str[j] = istr;
            j++;
            istr = wcstok(NULL, L" .,", &buffer);
        }
        qsort(new_str, j, sizeof(wchar_t*), cmp_for_convert_sent);
        exit_str = malloc(sizeof(wchar_t)*(text->sentence[i].size_sentence+15));
        exit_str[0] = '\0';
        for(int k = 0; k < j; k++)
        {
            wcscat(exit_str,new_str[k]);
            wcscat(exit_str, L" ");
        }
        exit_str[wcslen(exit_str)-1] = '.';
        wcscpy(text->sentence[i].sentence,exit_str);
        j=0;
        free(exit_str);
        free(new_str);
        free(str);
    }
}
