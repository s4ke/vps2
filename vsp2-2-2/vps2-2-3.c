#include <stdio.h>
#include <mpi.h>

void Gather_ring (float x[],int blocksize, float []);

int main (int argc,char** argv)
{


}
//Vorlage von Homepage
void Gather_ring (float x[], int blocksize, float y[])
{ 
   int i, num_nodes, my_rank, succ, pred;
   int send_offset, recv_offset;
   MPI_Status status;
   MPI_Comm_size (MPI_COMM_WORLD, &num_nodes);
   MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
   for (i=0; i<blocksize; i++)
      y[i+my_rank * blocksize] = x[i];
   succ = (my_rank+1) % num_nodes;
   pred = (my_rank-1+num_nodes) % pnum_nodes;
   for (i=0; i<p-1; i++) {
      send_offset = ((my_rank-i+num_nodes) % num_nodes) * blocksize;
      recv_offset = ((my_rank-i-1+num_nodes) % num_nodes) * blocksize;
      //muss man hier nicht einfach z.b. if (rank == 0) rec first und dann send? 
      //das ist das das philisophenproblem und das wäre dann sozusagen ein fix mit vorlassen
      MPI_Send (y+send_offset, blocksize, MPI_FLOAT, succ, 0,
               MPI_COMM_WORLD);
      MPI_Recv (y+recv_offset, blocksize, MPI_FLOAT, pred, 0,
               MPI_COMM_WORLD, &status);
   }
}
