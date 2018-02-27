#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;

static class Task1 {

	static void run() {
		cout << "hello world!" << endl;
#pragma omp parallel 
		cout << "hello parallel world!" << endl;
	}

};
