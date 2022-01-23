#include "del_and_shift.h"

int cmp_for_del_and_shift(const void* a, const void* b)
{
    const int* arg1 = a;
    const int* arg2 = b;
    return *arg1 - *arg2;
}

void del_and_shift(int* index, int* k, struct Text *text)
{
    int del = 0, m;
    qsort(index, *k, sizeof(int), cmp_for_del_and_shift);
    for (int i = 0 ; i<*k; i++)
    {
        m=index[i]-del;
        for(int j = 0 ; text->sentence[m].sentence[j]; j++)
        {
            text->sentence[m].sentence[j]='\0';
        }
        for (int j = m ; j < (text->size_text)-1; j++)
        {
            if(text->sentence[j].size_sentence < text->sentence[j+1].size_sentence)
            {
                text->sentence[j].sentence = realloc(text->sentence[j].sentence, sizeof(wchar_t) * (text->sentence[j+1].size_sentence + 10));
            }
            text->sentence[j].size_sentence = text->sentence[j+1].size_sentence;
            text->sentence[j].av_len = text->sentence[j+1].av_len;
            text->sentence[j].words = text->sentence[j+1].words;
            wcscpy(text->sentence[j].sentence,text->sentence[j+1].sentence);
        }
        del+=1;
        text->size_text--;
    }
}
