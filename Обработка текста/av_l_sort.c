#include "av_l_sort.h"

int cmp_for_av_l_sort(const void* a, const void *b)
{
    const struct Sentence *aa  = a;
    const struct Sentence *bb  = b;
    if(aa->av_len > bb->av_len)
        return 1;
    if(aa->av_len < bb->av_len)
        return -1;
    if(aa->av_len == bb->av_len)
        return 0;
}

void av_l_sort(struct Text * text)
{
    qsort(text->sentence, text->size_text, sizeof(struct Sentence), cmp_for_av_l_sort);
}
