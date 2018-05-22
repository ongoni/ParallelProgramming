#pragma once
#include "stdafx.h"
#include "Lab2.h"
#include <iostream>
#include <omp.h>

using namespace std;

namespace SecondLab {

	Lab2::Lab2() { }

	Lab2::~Lab2() { }

	void Lab2::task1() {
		printf("lab 2 task 1:\n");

#pragma omp parallel num_threads(4) 
		printf("hello parallel world!\n");

#pragma omp single nowait
		printf("hello another parallel world!\n");

		printf("hello parallel world!\n");
	}

	void Lab2::task2() {
		printf("lab 2 task 2:\n");

		int n = 0;
#pragma omp parallel num_threads(4) private(n)
		{
			n = 0;
#pragma omp master 
			n = 1;
			printf("n = %d\n", n);
#pragma omp barrier
#pragma omp master
			n = 2;

			printf("n = %d\n", n);
		}
	}

	void Lab2::task3() {
		printf("lab 2 task 3:\n");

		const int N = 8;
		int a[N];

		for (int i = 0; i < N; i++) {
			a[i] = 0;
			printf("%d ", a[i]);
		}

#pragma omp parallel num_threads(N) shared(a) 
		{
			int threadNumber = omp_get_thread_num();
			a[threadNumber] = threadNumber;
		}
		printf("\n");

		for (int i = 0; i < N; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
		
	}

}
