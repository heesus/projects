#include "treap.h"
#include <bits/stdc++.h>

Treap Merge(Treap L, Treap R)//возвращает новую дерамиду, скле€нную из 2(все ключи в левой дерамиде меньше ключей в правой)
{
    if (L == NULL) return R;//если лева€ дерамида пуста, то искома€ дерамида - права€
    if (R == NULL) return L;//если права€ дерамида пуста, то искома€ дерамида - лева€

    if (L->y > R->y)//сравнение по приоритету
    {
        Treap newR = Merge(L->Right, R);//рекурсивно вызываем функцию
        return new treap(L->x, L->y, L->Left, newR);//возвращаем получивщуюс€ дерамиду
    }
    else
    {
        Treap newL = Merge(L, R->Left);//рекурсивно вызываем функцию
        return new treap(R->x, R->y, newL, R->Right);//возвращаем получивщуюс€ дерамиду
    }
}

Treap Split(int X, Treap T)//делит дерамиду на две по значению ’.
{
    if(T == NULL) //если исходна€ дерамида пуста
    {
        Treap TT = new treap(0,0,NULL,NULL);
        return TT;
    }
    else if (T->x <= X)//если мы нашли место делени€ дерамиды
    {
        Treap TT = Split(X, T->Right);
        T->Right = TT->Left;//"навешиваем" правого сына исходной дерамиды на новую дерамиду
        Treap TTT = new treap(0,0,T,TT->Right);//создаем новую дерамиду
        return TTT;
    }
    else
    {
        Treap TT = Split(X, T->Left);
        T->Left = TT->Right;//"навешиваем" левого сына исходной дерамиды на новую дерамиду
        Treap TTT = new treap(0,0,TT->Left,T);//создаем новую дерамиду
        return TTT;
    }

}

Treap Add(int x, int y, Treap T)//добавление в декартово дерево нового элемента
{
    Treap l;//лева€ дерамида по ключу х
    Treap r;//права€ дерамида по ключу х
    Treap TT = Split(x, T);//делим дерамиду по ключу х
    Treap m = new treap(x, y);//создаем новую дерамиду из одного элемента со случайным приоритетом
    T = Merge(Merge(TT->Left, m), TT->Right);//склеиваем поочередно дерамиды
    return T;
}

void Write_Treap(Treap T)//выводит декартово дерево
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

Treap Build_add(int xs[], int n)//построение дерамиды
{
    Treap tree = new treap(1, xs[0]);//создаем первый элемент
    for(int i = 1; i < n; i++)
    {
        tree = Add(i+1, xs[i], tree);//с помощью функции Add добавл€ем новые вершины в дерамиду
    }
    return tree;
}

Treap Build_rand(int xs[], int n)
{
    Treap tree = new treap(1 + rand() % (n), xs[0]);//создаем первый элемент
    for(int i = 1; i < n; i++)
    {
        tree = Add(1 + rand() % (n), xs[i], tree);//с помощью функции Add добавл€ем новые вершины в дерамиду
    }
    return tree;
}

Treap Remove(Treap T)//удал€ет корневой элемент дерамиды
{
    Treap TT = T->Left;
    Treap TTT = T->Right;
    delete T;
    return Merge(TT, TTT);
}

void treapSort(int n, int inx[])
{
    Treap T = Build_add(inx, n);//создаем декартово дерево

    for(int i = n-1; i >= 0; i--)
    {
        inx[i] = T->y;//запоминаем корень
        T = Remove(T);//удал€ем корень
    }

    destroy_treap(T);//чистим пам€ть
}

void randTreapSort(int n, int inx[])
{
    Treap T = Build_rand(inx, n);//создаем рандомизированную дерамиду

    for(int i = n-1; i >= 0; i--)
    {
        inx[i] = T->y;//запоминаем корень
        T = Remove(T);//удал€ем корень
    }
    destroy_treap(T);//чистим пам€ть
}

void destroy_treap(Treap T)
{
    //очистка пам€ти
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
