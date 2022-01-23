#include "check_index.h"

int check_index(int* n, int* index, int* k)
{
    for(int i = 0; i < *k; i++)
    {
        if(index[i] == *n)
            return 0;
    }
    return 1;
}
