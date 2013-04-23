// vps2-1-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <iostream>
#include <Windows.h>

int _tmain(int argc, char* argv[])
{
	using namespace std;

	int test = 1;

	int myid, numprocs;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI::Init(argc,argv);
    numprocs = MPI::COMM_WORLD.Get_size();
    myid     = MPI::COMM_WORLD.Get_rank();
    MPI::Get_processor_name(processor_name,namelen);

    cout << "Process " << myid << " of " << numprocs << " is on " <<
	processor_name << endl;

    
    if (myid == 0)
	{
		startwtime = MPI::Wtime();
		MPI::COMM_WORLD.Send(&test, 1, MPI_INTEGER, 1, 0);
		test = 2;
		endwtime = MPI::Wtime();
		cout << "wall clock time = " << endwtime-startwtime << endl;
    }
	else if(myid == 1)
	{
		test = 0;
		Sleep(1000);
		MPI::COMM_WORLD.Recv(&test, 1, MPI_INTEGER, 0, 0);

		cout << "Test = " << test << endl;
	}

    MPI::Finalize();
    return 0;
}

