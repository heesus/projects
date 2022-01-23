#include "randBinTree.h"


int getsize(Node p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
    if(p == NULL) return 0;
    return p->size;
}

void fixsize(Node p) // установление корректного размера дерева
{
    if(p != NULL)
        p->size = getsize(p->left)+getsize(p->right)+1;
}

Node insert(Node p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
    if(p == NULL) return new node(k);//если дерево пустое - создаем его
    if(rand()%(p->size + 1) == 0)//с вероятностью 1/(n+1) вставляем сюда элемент
        return insertroot(p,k);
    if(p->key > k)//иначе ищем место для элемента
        p->left = insert(p->left, k);//вставляем в левого сына
    else
        p->right = insert(p->right, k);//вставляем в правого сына
    fixsize(p);
    return p;
}

Node rotateright(Node p) // правый поворот вокруг узла p
{
    Node q = p->left;
    if(q == NULL) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);//обновляем размеры
    fixsize(q);
    return q;
}

Node rotateleft(Node q) // левый поворот вокруг узла q
{
    Node p = q->right;
    if(p == NULL) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);//обновляем размеры
    fixsize(p);
    return p;
}

Node insertroot(Node p, int k) // вставка нового узла с ключом k в корень дерева p
{
    if(p == NULL) return new node(k);//если дерево пустое - создаем его
    if( k < p->key )
    {
        p->left = insertroot(p->left, k);//вставляем элемент в левого сына
        return rotateright(p);//чиним БДП
    }
    else
    {
        p->right = insertroot(p->right, k);//вставляем элемент в правого сына
        return rotateleft(p);//чиним БДП
    }
}

void destroy_node(Node p)
{
    //очистка памяти
    if (p != NULL)
    {
        if (p->left != NULL)
        {
            destroy_node(p->left);
        }

        if (p->right != NULL)
        {
            destroy_node(p->right);
        }

        delete p;
    }
}

Node build_RBST(int n, int inx[])//строим БДП
{
    Node P = new node(inx[0]);
    for(int i = 1; i < n; i++)
    {
        P = insert(P, inx[i]);
    }
    return P;
}

void Write_RBST(Node p)//выводит декартово дерево
{
    if(p == NULL)
        std::cout<<"(p - NULL) ";
    else
    {
        std::cout<<"("<<p->key<<"): ";
        if(p->left == NULL)
        {
            std::cout<<"left - NULL / ";
        }
        else
            std::cout<<"left - ("<<p->left->key<<") / ";

        if(p->right == NULL)
        {
            std::cout<<"right - NULL\n";
        }
        else
            std::cout<<"right - ("<<p->right->key<<")\n";
        if(p->left != NULL)
            Write_RBST(p->left);
        if(p->right != NULL)
            Write_RBST(p->right);
    }
}

int counter = 0;

void dfs(Node p, int inx[]){//рекурсивный обход в глубину графа
    if(p->left != NULL)
        dfs(p->left, inx);

    inx[counter] = p->key;
    counter++;

    if(p->right != NULL)
        dfs(p->right, inx);
}

void RBSTSort(int n, int inx[]){//сортировка
    Node p = build_RBST(n, inx);//строим дерево

    counter = 0;
    dfs(p, inx);//вызываем обход

    destroy_node(p);//чистим память
}
