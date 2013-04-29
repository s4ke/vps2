#include <mpi.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	int i = 0;
	const size_t minsize = 8;
	const size_t shifts = 10;
	int size;
	int rank;
	int mpi_size;	
	double startwtime = 0.0;
	double endwtime;
	int *data = (int*) malloc(sizeof(int) * (minsize << shifts));	
	MPI_Status stat;
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	for (i = 0; i < shifts; i++) {
		size = minsize << i;

		if(rank == 0) {
			startwtime = MPI_Wtime();
			MPI_Send(data, size, MPI_INT, 1, 0, MPI_COMM_WORLD);
			endwtime = MPI_Wtime();
			printf("Send %d : %f\n", size, endwtime - startwtime);			

			startwtime = MPI_Wtime();
			MPI_Ssend(data, size, MPI_INT, 1, 0, MPI_COMM_WORLD);
			endwtime = MPI_Wtime();
			printf("SSend %d : %f\n", size, endwtime - startwtime);				
		} else if (rank == 1) {
			MPI_Recv(data, size, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
			MPI_Recv(data, size, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
		}
	}

	MPI_Finalize();
	return 0;
}

