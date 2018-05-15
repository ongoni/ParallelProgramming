#pragma once
#include "stdafx.h"
#include "Lab7.h"
#include <iostream>
#include "mpi.h"

using namespace std;

namespace SeventhLab {

	Lab7::Lab7() { }

	Lab7::~Lab7() { }

	int const NMAX = 9000000, NTIMES = 10;
	double array[NMAX];

	void Lab7::task1() {
		double _2_d20 = pow(2.0, 20);
		int n = 0, lmax = 0;
		double max = 0.0;

		MPI_Init(NULL, NULL);
		int Size;
		MPI_Comm_size(MPI_COMM_WORLD, &Size);
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

		while (n <= NMAX) {
			double time_start = MPI_Wtime();

			for (int i = 0; i<NTIMES; i++) {
				if (Rank == 0) {
					MPI_Status St;
					MPI_Send(array, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
					MPI_Recv(array, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &St);
				}

				if (Rank == 1) {
					MPI_Status St;
					MPI_Recv(array, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &St);
					MPI_Send(array, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
				}
			}

			double time = (MPI_Wtime() - time_start) / (2 * NTIMES);
			double bandwidth = (8.0 * n / _2_d20) / time;

			if (max < bandwidth) {
				max = bandwidth;
				lmax = 8 * n;
			}

			if (Rank == 0) {
				if (n == 0) cout << "latency: " << time << " s" << endl;
				else cout << 8 * n << " bytes" << " bandwidth " << bandwidth << "MB/s" << endl;

			}

			if (n == 0) {
				n = 1;
			} else {
				n *= 2;
			}
		}

		if (Rank == 0) {
			cout << "max bandwidth " << max << " MB/s  length " << lmax << " bytes" << endl;
		}

		MPI_Finalize();
	}

	void Lab7::task2() {
		double a = 0, 
			b = 0, 
			c = 0;

		MPI_Request Req[4];
		MPI_Status St[4];

		MPI_Init(NULL, NULL);
		int Size;
		MPI_Comm_size(MPI_COMM_WORLD, &Size);
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

		int next = (Rank + 1) % Size;
		int previous = Rank ? Rank - 1 : Size - 1;

		a = Rank + 0.7;

		MPI_Isend(&a, 1, MPI_DOUBLE, next, 5, MPI_COMM_WORLD, &Req[0]);
		MPI_Irecv(&b, 1, MPI_DOUBLE, previous, 5, MPI_COMM_WORLD, &Req[1]);
		MPI_Isend(&a, 1, MPI_DOUBLE, previous, 5, MPI_COMM_WORLD, &Req[2]);
		MPI_Irecv(&c, 1, MPI_DOUBLE, next, 5, MPI_COMM_WORLD, &Req[3]);

		MPI_Waitall(4, Req, St);

		cout << "Process " << Rank << " a = " << a << " b = " << b << " c = " << c << endl;

		MPI_Finalize();
	}

	void Lab7::task3() {

	}
}