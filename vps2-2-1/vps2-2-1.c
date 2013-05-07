#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mpi_vec_mult(double* data, int n);

int main (int argc, char** argv)
{

	int mpi_size;
	int rank;
	int elements_per_proc;
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	double* data_a;
	double* data_b;
	if(argc != 2)
	{
		if(rank==0)
			printf("Please give me Vector length as first Argument!\n");
		return 0;
	}
	int n = atoi(argv[1]);
	if(rank == 0)
	{
		srand(time(NULL));
		//hold 2 vectors of size n.
		data_a = malloc(n*sizeof(double));
		data_b = malloc(n*sizeof(double));
		int i = 0;
		while(i<n) 
		{				
			data_a[i] = rand()/rand();
			data_b[i] = rand()/rand();
			printf("data_a at %i is %f \n",i,data_a[i]);
			printf("data_b at %i is %f \n",i,data_b[i]);
			++i;
		}
			
	}
	elements_per_proc = n / mpi_size;
	//add on so we dont do any mistakes
	elements_per_proc++;
	double* get_data_a = malloc(sizeof(double)*elements_per_proc);
	double* get_data_b = malloc(sizeof(double)*elements_per_proc);
	MPI_Scatter(data_a,elements_per_proc,MPI_DOUBLE,get_data_a,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Scatter(data_b,elements_per_proc,MPI_DOUBLE,get_data_b,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	int i = 0;
	double result;
	while(i<elements_per_proc)
	{
		if(rank*elements_per_proc+i >= n)
			break;
		result += get_data_a[i]*get_data_b[i];
		++i;
	}
	double* result_all = NULL;
	if(rank == 0)
	{
		result_all = malloc(sizeof(float)*mpi_size);
	}	
	MPI_Gather(&result,1,MPI_DOUBLE,result_all,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	i = 1;
	if(rank == 0)
	{
		for(i; i < mpi_size; ++i)
		{
			result += result_all[i];
		}
		printf("result is %f !",result);
	}



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


