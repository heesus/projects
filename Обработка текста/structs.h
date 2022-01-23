#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#define GREEN "\033[4;32m"
#define NON "\033[0m"
#define RED "\033[0;31m"

#ifndef STRUCTS_H
#define STRUCTS_H

struct Sentence
{
    wchar_t *sentence;
    float av_len;
    int words;
    int size_sentence;
};

struct Text
{
    struct Sentence *sentence;
    int size_text;
};

#endif
