#include "Input.h"

void Input(struct Text *text)
{
    wchar_t c = '1';
    int max_size_t = 20, max_size_s = 100, i = 0, j = 0, start = 0;
    float k = 0.0;
    text->sentence=(struct Sentence*)malloc(sizeof(struct Sentence)*max_size_t);
    text->size_text = 0;
    while((c=getwchar())!='\n')
    {
        if((c == ' ' || c == '\t') && start == 0)
        {
            continue;
        }
        start = 1;
        if(text->size_text == max_size_t-3)   //добавление памяти для новых предложений
        {
            max_size_t *= 2;
            text->sentence = (struct Sentence*)realloc(text->sentence,sizeof(struct Sentence)*max_size_t);
        }
        if(j == 0)
        {
            text->sentence[i].sentence = (wchar_t*)malloc(sizeof(wchar_t)*max_size_s); //выделение памяти для нового предложения
        }
        if(text->sentence[i].size_sentence = max_size_s-2)   //добавление памяти для новых символов в i-ом предложении
        {
            max_size_s += 10;
            text->sentence[i].sentence = (wchar_t*)realloc(text->sentence[i].sentence, sizeof(wchar_t)*max_size_s);
        }
        if(c!=' ')
        {
            k+=1.0;
        }
        if(c==' ' || c=='.')
        {
            text->sentence[i].words++;
        }
        text->sentence[i].sentence[j] = c;
        j++;
        if(c==L'.')
        {
            text->sentence[i].sentence[j] = '\0';
            text->sentence[i].size_sentence = j;
            text->sentence[i].av_len = (k-1) / text->sentence[i].words;
            text->size_text ++;
            k=0;
            j=0;
            i++;
            start = 0;
        }
    }
}
