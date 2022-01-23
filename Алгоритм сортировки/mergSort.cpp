#include "mergSort.h"

using namespace std;
template<typename T>

void mergSort(ll n, T inp[])
{
    T first[n];//������ ����
    T second[n];//������ ����
    int cf = 0;//������� ������ ����
    int cs = 0;//������� ������ ����
    bool tape = true;//�������, ������������, ����� ���� ����������
    int subarray = 0;//������� ����� ��������������� �����������
    queue <int> qfirst;//������� ������ ��������������� ����������� ������ ����
    queue <int> qsecond;//������� ������ ��������������� ����������� ������ ����
    int a = 0,b = 0;
    do
    {
        for(int i = 0; i < n; i++)
        {
            first[i] = INF;//��������� ���� �������� �������
            second[i] = INF;
        }
        for(int i = 0; i < n; i++)//���������� �� ������� ���� ��� ��������������� ����������
        {
            if(tape)//���������� ����������, ���� ����
            {
                first[cf] = inp[i];
                cf++;
            }
            else
            {
                second[cs] = inp[i];
                cs++;
            }
            if(i!=n-1)
            {
                if(inp[i+1]<inp[i])
                {
                    if(tape)
                    {
                        qfirst.push(cf-1);//���������� ����� �����������
                    }
                    else
                    {
                        qsecond.push(cs-1);//���������� ����� �����������
                    }
                    tape = !tape;//������ ����
                }
            }
            else
            {
                if(tape)
                {
                    qfirst.push(cf-1);
                }
                else
                {
                    qsecond.push(cs-1);
                }
            }
        }
        if(second[0] != INF)//���� ������ ��� �� ������������
        {
            for(ll i = 0; i < n; i++)
            {
                if(subarray == 0)
                {
                    inp[i] = min(first[a],second[b]);//��������� ������, ������� ����������� �� ���� ������������
                    if(inp[i] == first[a])
                    {
                        a++;
                        if(qfirst.empty() || qfirst.front() == a-1)//���� ���������� ��������� �� ������ ����
                        {
                            subarray = 1;
                            qfirst.pop();
                        }
                    }
                    else
                    {
                        b++;
                        if(qsecond.empty() || qsecond.front() == b-1)//���� ���������� ��������� �� ������ ����
                        {
                            subarray = 2;
                            qsecond.pop();
                        }
                    }
                }
                else
                {
                    if(subarray == 1)//���� ���������� ��������� �� ������ ����
                    {
                        inp[i] = second[b];
                        b++;
                        if(qsecond.empty() || qsecond.front() == b-1)
                        {
                            subarray = 0;
                            qsecond.pop();
                        }
                    }
                    if(subarray == 2)//���� ���������� ��������� �� ������ ����
                    {
                        inp[i] = first[a];
                        a++;
                        if(qfirst.empty() || qfirst.front() == a-1)
                        {
                            subarray = 0;
                            qfirst.pop();
                        }
                    }
                }
            }
        }
        tape = true;//�������� ����������
        subarray = 0;
        a = 0;
        b = 0;
        cf = 0;
        cs = 0;
    }
    while(second[0] != INF);//���������, ���� ������ �� ����� ������������
}
