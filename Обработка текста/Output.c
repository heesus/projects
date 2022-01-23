#include "Output.h"

void Output(struct Text *text)
{
    fwprintf(stdout, L"%s\n======================================TEXT======================================%s\n\n",RED,NON);
    for(int i = 0; i < text->size_text; i++)
    {
        fputws(text->sentence[i].sentence,stdout);
    }
    fwprintf(stdout, L"%s\n\n================================================================================%s\n\n",RED,NON);
}
