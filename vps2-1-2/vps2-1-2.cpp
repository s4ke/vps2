// vps2-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <iostream>
#include <Windows.h>


int _tmain(int argc, char* argv[])
{
	using namespace std;

	MPI::Init(argc,argv);

	const size_t minsize = 8;
	const size_t shifts = 10;
	const int rank = MPI::COMM_WORLD.Get_rank();
	double startwtime = 0.0, endwtime;

	int data[minsize << shifts];	

	for (int i = 0; i < shifts; i++)
	{
		size_t size = minsize << i;

		if(rank == 0)
		{
			startwtime = MPI::Wtime();
			MPI::COMM_WORLD.Send(data, size, MPI_INTEGER, 1, 0);
			endwtime = MPI::Wtime();
			cout << "Send " << size << ": " << endwtime-startwtime << endl;			

			startwtime = MPI::Wtime();
			MPI::COMM_WORLD.Ssend(data, size, MPI_INTEGER, 1, 0);
			endwtime = MPI::Wtime();
			cout << "Ssend " << size << ": " << endwtime-startwtime << endl;			
		}
		else if (rank == 1)
		{
			MPI::COMM_WORLD.Recv(data, size, MPI_INTEGER, 0, 0);
			MPI::COMM_WORLD.Recv(data, size, MPI_INTEGER, 0, 0);
		}
	}

	MPI::Finalize();
	return 0;
}

