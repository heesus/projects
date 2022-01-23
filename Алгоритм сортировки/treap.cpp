#include "treap.h"
#include <bits/stdc++.h>

Treap Merge(Treap L, Treap R)//���������� ����� ��������, ��������� �� 2(��� ����� � ����� �������� ������ ������ � ������)
{
    if (L == NULL) return R;//���� ����� �������� �����, �� ������� �������� - ������
    if (R == NULL) return L;//���� ������ �������� �����, �� ������� �������� - �����

    if (L->y > R->y)//��������� �� ����������
    {
        Treap newR = Merge(L->Right, R);//���������� �������� �������
        return new treap(L->x, L->y, L->Left, newR);//���������� ������������ ��������
    }
    else
    {
        Treap newL = Merge(L, R->Left);//���������� �������� �������
        return new treap(R->x, R->y, newL, R->Right);//���������� ������������ ��������
    }
}

Treap Split(int X, Treap T)//����� �������� �� ��� �� �������� �.
{
    if(T == NULL) //���� �������� �������� �����
    {
        Treap TT = new treap(0,0,NULL,NULL);
        return TT;
    }
    else if (T->x <= X)//���� �� ����� ����� ������� ��������
    {
        Treap TT = Split(X, T->Right);
        T->Right = TT->Left;//"����������" ������� ���� �������� �������� �� ����� ��������
        Treap TTT = new treap(0,0,T,TT->Right);//������� ����� ��������
        return TTT;
    }
    else
    {
        Treap TT = Split(X, T->Left);
        T->Left = TT->Right;//"����������" ������ ���� �������� �������� �� ����� ��������
        Treap TTT = new treap(0,0,TT->Left,T);//������� ����� ��������
        return TTT;
    }

}

Treap Add(int x, int y, Treap T)//���������� � ��������� ������ ������ ��������
{
    Treap l;//����� �������� �� ����� �
    Treap r;//������ �������� �� ����� �
    Treap TT = Split(x, T);//����� �������� �� ����� �
    Treap m = new treap(x, y);//������� ����� �������� �� ������ �������� �� ��������� �����������
    T = Merge(Merge(TT->Left, m), TT->Right);//��������� ���������� ��������
    return T;
}

void Write_Treap(Treap T)//������� ��������� ������
{
    if(T == NULL)
        std::cout<<"(T - NULL) ";
    else
    {
        std::cout<<"("<<T->x<<", "<<T->y<<"): ";
        if(T->Left == NULL)
        {
            std::cout<<"Left - NULL / ";
        }
        else
            std::cout<<"Left - ("<<T->Left->x<<", "<<T->Left->y<<") / ";

        if(T->Right == NULL)
        {
            std::cout<<"Right - NULL\n";
        }
        else
            std::cout<<"Right - ("<<T->Right->x<<", "<<T->Right->y<<")\n";
        if(T->Left != NULL)
            Write_Treap(T->Left);
        if(T->Right != NULL)
            Write_Treap(T->Right);
    }
}

Treap Build_add(int xs[], int n)//���������� ��������
{
    Treap tree = new treap(1, xs[0]);//������� ������ �������
    for(int i = 1; i < n; i++)
    {
        tree = Add(i+1, xs[i], tree);//� ������� ������� Add ��������� ����� ������� � ��������
    }
    return tree;
}

Treap Build_rand(int xs[], int n)
{
    Treap tree = new treap(1 + rand() % (n), xs[0]);//������� ������ �������
    for(int i = 1; i < n; i++)
    {
        tree = Add(1 + rand() % (n), xs[i], tree);//� ������� ������� Add ��������� ����� ������� � ��������
    }
    return tree;
}

Treap Remove(Treap T)//������� �������� ������� ��������
{
    Treap TT = T->Left;
    Treap TTT = T->Right;
    delete T;
    return Merge(TT, TTT);
}

void treapSort(int n, int inx[])
{
    Treap T = Build_add(inx, n);//������� ��������� ������

    for(int i = n-1; i >= 0; i--)
    {
        inx[i] = T->y;//���������� ������
        T = Remove(T);//������� ������
    }

    destroy_treap(T);//������ ������
}

void randTreapSort(int n, int inx[])
{
    Treap T = Build_rand(inx, n);//������� ����������������� ��������

    for(int i = n-1; i >= 0; i--)
    {
        inx[i] = T->y;//���������� ������
        T = Remove(T);//������� ������
    }
    destroy_treap(T);//������ ������
}

void destroy_treap(Treap T)
{
    //������� ������
    if (T != NULL)
    {
        if (T->Left != NULL)
        {
            destroy_treap(T->Left);
        }
        if (T->Right != NULL)
        {
            destroy_treap(T->Right);
        }
        delete T;
    }
}
