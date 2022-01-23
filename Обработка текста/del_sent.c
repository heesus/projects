#include "del_sent.h"

void del_sent(struct Text *text)
{
    int k = 0;
    int max_size_i = 100;
    int* index = malloc(sizeof(int)*max_size_i);
    for(int i = 0; i < text->size_text-1; i++)
    {
        for(int j = i+1; j < text->size_text; j++)
        {
            if(text->sentence[i].size_sentence == text->sentence[j].size_sentence)
            {
                if(!wcscasecmp(text->sentence[i].sentence,text->sentence[j].sentence))
                {
                    if(check_index(&j,index,&k))
                    {
                        if(k == max_size_i - 2)
                        {
                            max_size_i *= 2;
                            index = realloc(index, sizeof(int)*max_size_i);
                        }
                        index[k] = j;
                        k++;
                    }
                }
            }
        }
    }

    del_and_shift(index, &k, text);
    free(index);
}
