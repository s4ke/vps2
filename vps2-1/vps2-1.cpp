// vps2-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <iostream>

int _tmain(int argc, char* argv[])
{
	using namespace std;

	int n, myid, numprocs;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI::Init(argc,argv);
    numprocs = MPI::COMM_WORLD.Get_size();
    myid     = MPI::COMM_WORLD.Get_rank();
    MPI::Get_processor_name(processor_name,namelen);

    cout << "Process " << myid << " of " << numprocs << " is on " <<
	processor_name << endl;

    n = 10000;			/* default # of rectangles */
    if (myid == 0)
	startwtime = MPI::Wtime();

    MPI::COMM_WORLD.Bcast(&n, 1, MPI_INT, 0);

    if (myid == 0) {
	endwtime = MPI::Wtime();
	cout << "wall clock time = " << endwtime-startwtime << endl;
    }

    MPI::Finalize();
    return 0;
}

