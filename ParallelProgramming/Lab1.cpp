#pragma once
#include "stdafx.h"
#include "Lab1.h"
#include <iostream>
#include <omp.h>

using namespace std;

namespace FirstLab {

	Lab1::Lab1() { }

	Lab1::~Lab1() { }

	void Lab1::task1() {
<<<<<<< HEAD
		printf("lab 1 task 1:\n");
=======
>>>>>>> 0e0dc989f5f440f2f865995bb1bdafedf49acbde
		printf("hello world!\n");

#pragma omp parallel
		printf("hello parallel world!\n");
	}

	void Lab1::task2() {
<<<<<<< HEAD
		printf("lab 1 task 2:\n");

=======
>>>>>>> 0e0dc989f5f440f2f865995bb1bdafedf49acbde
		printf("hello world!\n");
		omp_set_num_threads(2);

#pragma omp parallel
		printf("hello parallel world!\n");

#pragma omp parallel num_threads(4) 
		printf("hello parallel world!\n");
	}

	void Lab1::task3() {
<<<<<<< HEAD
		printf("lab 1 task 3:\n");

=======
>>>>>>> 0e0dc989f5f440f2f865995bb1bdafedf49acbde
		printf("default - %d\n", omp_get_dynamic());

#pragma omp parallel num_threads(16)
#pragma omp master
		printf("thread number - %d\n", omp_get_num_threads());

		omp_set_dynamic(1);

		printf("custom - %d\n", omp_get_dynamic());

#pragma omp parallel num_threads(16)
#pragma omp master
		printf("thread number - %d\n", omp_get_num_threads());
	}

}
