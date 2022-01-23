#include "randBinTree.h"


int getsize(Node p) // ������� ��� ���� size, �������� � ������� ��������� (t=NULL)
{
    if(p == NULL) return 0;
    return p->size;
}

void fixsize(Node p) // ������������ ����������� ������� ������
{
    if(p != NULL)
        p->size = getsize(p->left)+getsize(p->right)+1;
}

Node insert(Node p, int k) // ����������������� ������� ������ ���� � ������ k � ������ p
{
    if(p == NULL) return new node(k);//���� ������ ������ - ������� ���
    if(rand()%(p->size + 1) == 0)//� ������������ 1/(n+1) ��������� ���� �������
        return insertroot(p,k);
    if(p->key > k)//����� ���� ����� ��� ��������
        p->left = insert(p->left, k);//��������� � ������ ����
    else
        p->right = insert(p->right, k);//��������� � ������� ����
    fixsize(p);
    return p;
}

Node rotateright(Node p) // ������ ������� ������ ���� p
{
    Node q = p->left;
    if(q == NULL) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);//��������� �������
    fixsize(q);
    return q;
}

Node rotateleft(Node q) // ����� ������� ������ ���� q
{
    Node p = q->right;
    if(p == NULL) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);//��������� �������
    fixsize(p);
    return p;
}

Node insertroot(Node p, int k) // ������� ������ ���� � ������ k � ������ ������ p
{
    if(p == NULL) return new node(k);//���� ������ ������ - ������� ���
    if( k < p->key )
    {
        p->left = insertroot(p->left, k);//��������� ������� � ������ ����
        return rotateright(p);//����� ���
    }
    else
    {
        p->right = insertroot(p->right, k);//��������� ������� � ������� ����
        return rotateleft(p);//����� ���
    }
}

void destroy_node(Node p)
{
    //������� ������
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

Node build_RBST(int n, int inx[])//������ ���
{
    Node P = new node(inx[0]);
    for(int i = 1; i < n; i++)
    {
        P = insert(P, inx[i]);
    }
    return P;
}

void Write_RBST(Node p)//������� ��������� ������
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

void dfs(Node p, int inx[]){//����������� ����� � ������� �����
    if(p->left != NULL)
        dfs(p->left, inx);

    inx[counter] = p->key;
    counter++;

    if(p->right != NULL)
        dfs(p->right, inx);
}

void RBSTSort(int n, int inx[]){//����������
    Node p = build_RBST(n, inx);//������ ������

    counter = 0;
    dfs(p, inx);//�������� �����

    destroy_node(p);//������ ������
}
