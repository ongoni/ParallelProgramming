#pragma once
#include "stdafx.h"
#include "Lab6.h"
#include <iostream>
#include "mpi.h"

using namespace std;

namespace SixthLab {

	Lab6::Lab6() { }

	Lab6::~Lab6() { }

	void Lab6::task1() {
		int NProc, ProcId;
		MPI_Init(NULL, NULL);
		MPI_Comm_size(MPI_COMM_WORLD, &NProc);
		MPI_Comm_rank(MPI_COMM_WORLD, &ProcId);

		cout << "Process total: " << NProc << " Process id: " << ProcId << endl;

		MPI_Finalize();
	}

	void Lab6::task2() {
		MPI_Init(NULL, NULL);
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

		if (Rank == 0) {
			double value = 13.37;

			int BufSize = sizeof(double) + MPI_BSEND_OVERHEAD;

			void *Buff = malloc(BufSize);
			MPI_Buffer_attach(Buff, BufSize);
			MPI_Bsend(&value, 1, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
			MPI_Buffer_detach(Buff, &BufSize);

			if (!Buff) {
				free(Buff);
			}
			
			cout << "Process 0 has sent the data" << endl;
		} else {
			if (Rank == 1) {
				double value = 0;
				MPI_Status Status;
				MPI_Recv(&value, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &Status);
				
				cout << "Process 1 has accepted data - " << value << endl;
			} else {
				cout << "Process " << Rank << " does not accept any data" << endl;
			}
		}

		MPI_Finalize();
	}
	
	void Lab6::task3() {
		MPI_Init(NULL, NULL);
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

		if (Rank == 0) {
			double doubleValue = 0;
			int intValue = 0;
			MPI_Status St;

			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);
			if (St.MPI_TAG == 5) {
				MPI_Recv(&doubleValue, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process " << St.MPI_SOURCE << " double - " << doubleValue << endl;
			}
			if (St.MPI_TAG == 6) {
				MPI_Recv(&intValue, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process " << St.MPI_SOURCE << " int - " << intValue << endl;
			}

			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);
			if (St.MPI_TAG == 5) {
				MPI_Recv(&doubleValue, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process " << St.MPI_SOURCE << " double - " << doubleValue << endl;
			}
			if (St.MPI_TAG == 6) {
				MPI_Recv(&intValue, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process " << St.MPI_SOURCE << " int - " << intValue << endl;
			}
		}

		if (Rank == 1) {
			double value = 7.7;
			MPI_Send(&value, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
		}

		if (Rank == 2) {
			int value = 3;
			MPI_Send(&value, 1, MPI_INTEGER, 0, 6, MPI_COMM_WORLD);
		}

		MPI_Finalize();
	}
}