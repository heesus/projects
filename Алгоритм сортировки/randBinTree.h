#pragma once

#include <bits/stdc++.h>

typedef class node* Node;

struct node
{
public:
    int key;//����
	int size;//������ ������
	Node left;//����� ���
	Node right;//������ ���
	node(int k) { key = k; left = right = 0; size = 1; }
};

int getsize(Node p);//������ ������ ������
void fixsize(Node p);//�������� ������ ������
Node insert(Node p, int k);//�������� ������� ������
Node rotateright(Node p);//������� ������
Node rotateleft(Node q);//������� �����
Node insertroot(Node p, int k);//���������� ������� � ������ � �������� ������
void destroy_node(Node p);//������ ������
Node build_RBST(int n, int inx[]);//��������� ��������� ���
void Write_RBST(Node p);//������� ���
void RBSTSort(int n, int inx[]);//����������
