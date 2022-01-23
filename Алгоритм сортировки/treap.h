#pragma once

#include <bits/stdc++.h>

using ll = long long;


typedef class treap* Treap;
class treap
{
public:
    int x;//���������
    int y;//����
    Treap Left;//����� ���
    Treap Right;//������ ���
    treap(int x, int y, Treap left = NULL, Treap right = NULL)
    {
        this->x = x;
        this->y = y;
        this->Left = left;
        this->Right = right;
    }
};

Treap Merge(Treap L, Treap R);//����������
Treap Split(int X, Treap T);//������
Treap Remove(Treap T);//�������� �����
void Write_Treap(Treap T);//����� ��������
Treap Add(int x, int y, Treap T);//�������� �������
Treap Build_add(int xs[], int n);//���������� ����������� ������
Treap Build_rand(int xs[], int n);//���������� ����������������� ��������
void randTreapSort(int n, int inx[]);//���������� ����������������� ���������
void treapSort(int n, int inx[]);//���������� ���������� �������
void destroy_treap(Treap T);//������� ������

