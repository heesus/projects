#include "structs.h"
#ifndef DEL_AND_SHIFT_H
#define DEL_AND_SHIFT_H

int cmp_for_del_and_shift(const void* a, const void* b);

void del_and_shift(int* index, int* k, struct Text *text);

#endif
