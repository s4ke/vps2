#include <mpi.h>
#include <stdio.h>

void mpi_vec_mult(double* data, int n);

int main (int argc, char** argv)
{
	int mpi_size;
	int rank;
	int elements_per_proc;
	int n = 10;
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	double* data_a;
	double* data_b;
	if(rank == 0)
	{
		//hold 2 vectors of size n.
		data_a = malloc(n*sizeof(double));
		data_b = malloc(n*sizeof(double));
		int i = 0;
		while(i<n) 
		{				
			data_a[i] = i;
			data_b[i] = data_a[i]+1;
			++i;
		}
			
	}
	elements_per_proc = n / mpi_size;
	double* get_data_a = malloc(sizeof(double)*elements_per_proc);
	double* get_data_b = malloc(sizeof(double)*elements_per_proc);
	MPI_Scatter(data_a,n,MPI_DOUBLE,get_data_a,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Scatter(data_b,n,MPI_DOUBLE,get_data_b,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	int i = 0;
	double* result = malloc(sizeof(double)*elements_per_proc);
	while(i<elements_per_proc)
	{
		result[i] = get_data_a[i]*get_data_b[i];
		++i;
	}
	double* result_all = NULL;
	if(rank == 0)
	{
		result_all = malloc(sizeof(float)*n);
	}	
	MPI_Gather(result,elements_per_proc,MPI_DOUBLE,result_all,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	



	// delete(get_data_b);
	// delete(get_data_a);
	// delete(result);
	// if(rank == 0)
	// {
	// 	delete(data_a);
	// 	delete(data_b);
	// }
	MPI_Finalize();
	return 0;
}


