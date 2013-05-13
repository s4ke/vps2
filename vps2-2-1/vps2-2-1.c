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
	int n,i;

	
	double* data_a = NULL;
	double* data_b = NULL;
	double* get_data_a, *get_data_b, *result_all;
	double result;
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	if(argc != 2)
	{
		if(rank==0)
			printf("Please give me Vector length as first Argument!\n");
		return 0;
	}
	n = atoi(argv[1]);
	if(rank == 0)
	{
		srand((unsigned int)time(NULL));
		//hold 2 vectors of size n.
		data_a = (double*)malloc(n*sizeof(double));
		data_b = (double*)malloc(n*sizeof(double));
		i = 0;
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
	get_data_a = (double*)malloc(sizeof(double)*elements_per_proc);
	get_data_b = (double*)malloc(sizeof(double)*elements_per_proc);
	MPI_Scatter(data_a,elements_per_proc,MPI_DOUBLE,get_data_a,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Scatter(data_b,elements_per_proc,MPI_DOUBLE,get_data_b,elements_per_proc,MPI_DOUBLE,0,MPI_COMM_WORLD);
	i = 0;
	result = 0.0;
	while(i<elements_per_proc)
	{
		if(rank*elements_per_proc+i >= n)
			break;
		result += get_data_a[i]*get_data_b[i];
		++i;
	}
	result_all = NULL;
	if(rank == 0)
	{
		result_all = malloc(sizeof(float)*mpi_size);
	}	
	MPI_Reduce(&result,result_all,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("result is %f !",result_all[0]);
	}
	MPI_Finalize();
	return 0;
}


