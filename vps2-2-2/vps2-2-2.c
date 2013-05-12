#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void Gather_ring_theory (float x[],int blocksize, float []);

int main (int argc,char** argv)
{
	int myid, numprocs;
	double startwtime = 0.0, endwtime;
	int  namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	const int blocksize = 1;
	float *x;
	float *y;
	char *output = "";
	char *tmp;
	int i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);
	
	x = (float*) malloc(sizeof(float) * blocksize * numprocs);
	y = (float*) malloc(sizeof(float) * blocksize * numprocs);
	
	for(i = 0; i < numprocs; ++i) {
		x[i] = myid;
		y[i] = myid;
	}
	
	for(i = 0; i < numprocs; ++i) {
		itoa(y[i], tmp, 10);
		strcat(output, " ");
		strcat(output, tmp);
	}
	
	printf("(Before) Process %d of %d is on %s: %s\n", myid, numprocs, processor_name, output);
	
	*output = '\0';
	
	Gather_ring_theory(x, blocksize, y);
	
	for(i = 0; i < numprocs; ++i) {
		itoa(y[i], tmp, 10);
		strcat(output, " ");
		strcat(output, tmp);
	}

	printf("(After) Process %d of %d is on %s: %s\n", myid, numprocs, processor_name, output);
	
	free(x);
	free(y);
	
	MPI_Finalize();
}

void Gather_ring_theory (float x[], int blocksize, float y[])
{ 
   //Idee zum Theorie-Teil der Aufgabe:
   //wuerde nicht blockieren, wenn genau Prozess in
   //exakt entgegengesetzter Art und Weise sendet und empfaengt,
   //als die anderen. Das Problem ist aehnlich wie das
   //Philosophenproblem, das man exakt so loesen kann.
   //
   //Beispiel fuer 3 Prozesse:
   //
   //1. Schritt:
   //Prozess #0 wartet auf die Daten von Prozess #2, die er von Prozess #2 bekommt
   //Prozess #1 sendet die Daten von Prozess #1 an Prozess #2
   //Prozess #2 sendet die Daten von Prozess #2 an Prozess #0
   //Prozess #0 sendet die Daten von Prozess #0 an Prozess #1
   //Prozess #1 wartet auf die Daten von Prozess #0, die er von Prozess #0 bekommt
   //Prozess #2 wartet auf die Daten von Prozess #1, die er von Prozess #1 bekommt
   //...
   //der zweite Schritt laeuft analog dazu ab, nur dass die Daten, die uebertragen werden
   //nicht mehr die eigenen sind.
   //Der Deadlock kann hier nicht auftreten, weil die Prozesse [#0] 
   //(Aequivalenzklasse) immer die Vorkondition fuer das Empfangen 
   //in den anderen Prozessen bereitstellt waehrend die Prozesse [#1]
   //die Daten schon geschickt haben.
   int i, num_nodes, my_rank, succ, pred;
   int send_offset, recv_offset;
   MPI_Status status;
   MPI_Comm_size (MPI_COMM_WORLD, &num_nodes);
   MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
   for (i=0; i<blocksize; i++) {
      y[i+my_rank * blocksize] = x[i];
	}
   succ = (my_rank+1) % num_nodes;
   pred = (my_rank-1+num_nodes) % num_nodes;
   for (i=0; i < num_nodes-1; i++) {
      send_offset = ((my_rank-i+num_nodes) % num_nodes) * blocksize;
      recv_offset = ((my_rank-i-1+num_nodes) % num_nodes) * blocksize;
	  if(my_rank % 2 == 0) {			
			MPI_Recv (y+recv_offset, blocksize, MPI_FLOAT, pred, 0,
				MPI_COMM_WORLD, &status);
			MPI_Send (y+send_offset, blocksize, MPI_FLOAT, succ, 0,
				MPI_COMM_WORLD);
	  } else {
			MPI_Send (y+send_offset, blocksize, MPI_FLOAT, succ, 0,
				MPI_COMM_WORLD);
			MPI_Recv (y+recv_offset, blocksize, MPI_FLOAT, pred, 0,
				MPI_COMM_WORLD, &status);
	  }
   }
}
