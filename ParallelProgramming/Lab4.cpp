#pragma once
#include "stdafx.h"
#include "Lab4.h"
#include <iostream>
#include <omp.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

using namespace std;

namespace FourthLab {

	Lab4::Lab4() { }

	Lab4::~Lab4() { }

	void Lab4::task1() {
		int n;
#pragma omp parallel num_threads(4)
#pragma omp critical
		{
			int n = omp_get_thread_num();
			printf("Thread #%d\n", n);
		}
	}

	void Lab4::task2() {
		int n;
		omp_lock_t lock;
		omp_init_lock(&lock);

#pragma omp parallel num_threads(4) private (n)
		{
			n = omp_get_thread_num();
			omp_set_lock(&lock);

			printf("locked section start %d\n", n);
			Sleep(1500);
			printf("locked section end %d\n", n);
			
			omp_unset_lock(&lock);
		}

		omp_destroy_lock(&lock);
	}
	
	double Lab4::f(double x) {
		return 1 / (1 + x * x);
	}

	double Lab4::Simpson(double a, double b, int n) {
		int i = 0;
		double h = (b - a) / (2 * n),
			sum1 = 0,
			sum2 = 0;

#pragma omp parallel for shared(a, h) private(i) reduction(+:sum1) reduction (+:sum2)
			for (i = 1; i < n; i++) {
				sum1 += f(a + h * (2 * i - 1));
				sum2 += f(a + 2 * i * h);
			}
		
		sum1 += f(b - h);

		return 
			(h / 3) * (
				f(a)
				+ f(b)
				+ 4 * sum1
				+ 2 * sum2
			);
	}

	void Lab4::task3() {
		double time = clock();
		double result = Simpson(0, 100000, 100000000);
		time = (clock() - time) / CLOCKS_PER_SEC;

		printf("Simpson formula - %f with time - %f\n", result, time);
		printf("exact value - %f\n", M_PI / 2.0);
	}

}