#include <mpi.h>
#include <stdio.h>

void BcastSim(MPI_Comm comm, void* data, int count, MPI_Datatype type, int root)
{
	MPI_Status stat;
	int myrank;
	int rank2;
	int range;
	const int bcast_tag = 12345;
	
	MPI_Comm_rank(comm, &rank2);
	MPI_Comm_size(comm, &range);
	rank2 = myrank * 2;

	if(myrank == root)
	{
		if(range > 1)
		{
			MPI_Send(data, count, type, 1, bcast_tag, comm);
		}
	}
	else
	{
		MPI_Recv(data, count, type, myrank / 2, bcast_tag, comm, &stat);
		if(range > rank2)
			MPI_Send(data, count, type, rank2, bcast_tag, comm);

		if(range > (rank2 + 1))
			MPI_Send(data, count, type, rank2 + 1, bcast_tag, comm);
	}
}

int main(int argc, char **argv)
{
	int myid, numprocs;
	double startwtime = 0.0, endwtime;
	int  namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);

	printf("Process %d of %d is on %s\n", myid, numprocs, processor_name);

	BcastSim(MPI_COMM_WORLD, &myid, 1, MPI_INT, 0);
	printf("Test = %d\n", myid);

	MPI_Finalize();
	return 0;
}

