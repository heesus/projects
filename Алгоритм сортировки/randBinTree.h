#pragma once

#include <bits/stdc++.h>

typedef class node* Node;

struct node
{
public:
    int key;//ключ
	int size;//размер дерева
	Node left;//левый сын
	Node right;//правый сын
	node(int k) { key = k; left = right = 0; size = 1; }
};

int getsize(Node p);//узнать размер дерева
void fixsize(Node p);//обновить размер дерева
Node insert(Node p, int k);//добавить элемент дерева
Node rotateright(Node p);//поворот вправо
Node rotateleft(Node q);//поворот влево
Node insertroot(Node p, int k);//установить элемент в корень и починить дерево
void destroy_node(Node p);//очитка памяти
Node build_RBST(int n, int inx[]);//построить случайное БДП
void Write_RBST(Node p);//вывести БДП
void RBSTSort(int n, int inx[]);//сортировка
