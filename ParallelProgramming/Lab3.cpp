#pragma once
#include "stdafx.h"
#include "Lab3.h"
#include <iostream>
#include <omp.h>
#include <windows.h>

using namespace std;

namespace ThirdLab {

	Lab3::Lab3() { }

	Lab3::~Lab3() { }

	void Lab3::task1() {
#pragma omp parallel num_threads(4)
		{
			int threadNumber = omp_get_thread_num();
			if (threadNumber == 0) {
				printf("total thread count - %d\n", omp_get_num_threads());
			} else {
				printf("thread number - %d\n", omp_get_thread_num());
			}
		}
	}

	void Lab3::task2() {
		const int N = 16;
		int i;
#pragma omp parallel num_threads(4) private(i)
		{
#pragma omp for schedule(static, 4)
			for (i = 0; i < N; i++)
			{
				printf("thread #%d did iteration #%d\n", omp_get_thread_num(), i);
				Sleep(1500);
			}
		}
	}

	void Lab3::task3() {
		int n = 0;
#pragma omp parallel num_threads(4) shared(n)
		{
#pragma omp parallel sections lastprivate(n)
			{
#pragma omp section
				{
					n = 1;
				}
#pragma omp section
				{
					n = 2;
				}
#pragma omp section
				{
					n = 3;
				}
#pragma omp section
				{
					n = 4;
				}
			}
			printf("value in thread #%d: %d\n", omp_get_thread_num(), n);
		}
		printf("value in not parallel region: %d\n", n);
	}

}