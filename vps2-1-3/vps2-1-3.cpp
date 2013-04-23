// vps2-1-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <iostream>
#include <Windows.h>

void BcastSim(const MPI::Intracomm& comm, void* data, int count, const MPI::Datatype &type, int root )
{
	const int myrank = comm.Get_rank();
	const int range = comm.Get_size();
	const int bcast_tag = 12345;

	if(myrank == root)
	{
		if(range > 1)
		{
			comm.Send(data, count, type, 1, bcast_tag);
		}
	}
	else
	{
		comm.Recv(data, count, type, myrank / 2, bcast_tag);
		const int rank2 = myrank * 2;
		if(range > rank2)
			comm.Send(data, count, type, rank2, bcast_tag);

		if(range > (rank2 + 1))
			comm.Send(data, count, type, rank2 + 1, bcast_tag);
	}
}

int _tmain(int argc, char* argv[])
{
	using namespace std;

	int myid, numprocs;
	double startwtime = 0.0, endwtime;
	int  namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI::Init(argc,argv);
	numprocs = MPI::COMM_WORLD.Get_size();
	myid     = MPI::COMM_WORLD.Get_rank();
	MPI::Get_processor_name(processor_name,namelen);

	cout << "Process " << myid << " of " << numprocs << " is on " << processor_name << endl;

	BcastSim(MPI::COMM_WORLD, &myid, 1, MPI_INTEGER, 0);
	cout << "Test = " << myid << endl;

	MPI::Finalize();
	return 0;
}

