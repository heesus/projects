#include "del_m5_l2.h"

void del_m5_l2(struct Text *text)
{
    int k = 0;
    int del = 0, m;
    int max_size_i = 100;
    int* index = malloc(sizeof(int)*max_size_i);
    for(int i = 0; i < text->size_text; i++)
    {
        if((text->sentence[i].words > 5) || (text->sentence[i].words < 2))
        {
            if(check_index(&i,index,&k))
            {
                if(k == max_size_i - 2)
                {
                    max_size_i *= 2;
                    index = realloc(index, sizeof(int)*max_size_i);
                }

                index[k] = i;
                k++;
            }
        }
    }
    del_and_shift(index, &k, text);
    free(index);
}
