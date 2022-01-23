#pragma once

#include <bits/stdc++.h>

using ll = long long;


typedef class treap* Treap;
class treap
{
public:
    int x;//преоритет
    int y;//ключ
    Treap Left;//левый сын
    Treap Right;//правый сын
    treap(int x, int y, Treap left = NULL, Treap right = NULL)
    {
        this->x = x;
        this->y = y;
        this->Left = left;
        this->Right = right;
    }
};

Treap Merge(Treap L, Treap R);//склеивание
Treap Split(int X, Treap T);//разрез
Treap Remove(Treap T);//удаление корня
void Write_Treap(Treap T);//вывод дерамиды
Treap Add(int x, int y, Treap T);//добавить элемент
Treap Build_add(int xs[], int n);//построение декартового дерева
Treap Build_rand(int xs[], int n);//построение рандомизированной дерамиды
void randTreapSort(int n, int inx[]);//сортировка рандомизированной дерамидой
void treapSort(int n, int inx[]);//сортировка декартовым деревом
void destroy_treap(Treap T);//очистка памяти

