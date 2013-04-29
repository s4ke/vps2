#include <stdio.h>
#include <mpi.h>


int main (int argc, char** argv)
{
	int rank,size,root=0;
	MPI_Init (&argc, &argv);	
  	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
  	MPI_Comm_size (MPI_COMM_WORLD, &size);	
	MPI_Status stat;
	int send = 2;
  	if(rank == root)
  	{
  		MPI_Send(&send,1,MPI_INT,1,1,MPI_COMM_WORLD);
  		send = 3;
  		printf("send = %d \n",send);
  	}
  	else
  	{
  		int rec = 0;
  		sleep(2);
  		MPI_Recv(&rec,1,MPI_INT,0,1,MPI_COMM_WORLD,&stat);
  		printf("rec = %d \n",rec);
  	}
  	MPI_Finalize();
	return 0;
}