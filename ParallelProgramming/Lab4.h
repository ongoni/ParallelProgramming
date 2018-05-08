#pragma once
#include "Lab4.h"

namespace FourthLab {
	
	class Lab4 {

	public:
		Lab4();
		~Lab4();
		void task1();
		void task2();
		void task3();
	private:
		double Simpson(double a, double b, int n);
		double f(double x);
	};

}
