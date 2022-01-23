#include "treap.h"
#include "randBinTree.h"
#include "mergSort.cpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <bits/stdc++.h>


class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

using namespace std;

int main()
{
    srand(time(0));

    int n = 70000;
    int inx[n], iny[n], inz[n], inc[n], ina[n];
    for(int i = 0; i < n; i++){
        inx[i] = 1 + rand() % 3200000;
        //inx[i] = i;
        iny[i] = inx[i];
        inz[i] = inx[i];
        ina[i] = inx[i];
    }

    std::cout << "Array size: " << n << '\n';

    Timer t;
    mergSort(n, inx);//вызов сортировки естественным слиянием
    std::cout << "Time taken for merge sort: " << t.elapsed() << '\n';

    Timer t2;
    treapSort(n, iny);//вызов сортировки декартовым деревом
    std::cout << "Time taken for treap sort: " << t2.elapsed() << '\n';

    Timer t4;
    randTreapSort(n, ina);//вызов сортировки рандомизированной дерамидой
    std::cout << "Time taken for randTreap sort: " << t4.elapsed() << '\n';

    Timer t1;
    RBSTSort(n, inz);//вызов сортировки случайным БДП
    std::cout << "Time taken for RBST sort: " << t1.elapsed() << '\n';

    return 0;
}
