#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MPI_Merge_Sort(int* data, int count, MPI_Comm comm);
void Merge_Sort_Rec(int* data, int count, MPI_Comm comm);

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

void Merge_Sort_Rec(int* data, int count, MPI_Comm comm)
{
	int mpi_size;
	int rank;
	MPI_Comm sub_comm = MPI_COMM_NULL;
	int in_lower_half;
	int *rec_data;

	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &mpi_size);

	if(mpi_size > 1)
	{
		in_lower_half = rank < (mpi_size / 2);
		rec_data = (in_lower_half) ? data : data + (mpi_size/2);
		MPI_Comm_split(comm, in_lower_half, rank, &sub_comm);
		
		Merge_Sort_Rec(rec_data, count / 2, sub_comm);
	}
	//Sort

}

void MPI_Merge_Sort(int* data, int count, MPI_Comm comm)
{
	int mpi_size;
	int rank;
	int elements_per_proc;
	int* recv_ptr;

	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &mpi_size);

	
	elements_per_proc = count / mpi_size;
	recv_ptr = data + rank * elements_per_proc;
	MPI_Scatter(
		data, elements_per_proc, MPI_INTEGER, 
		recv_ptr, elements_per_proc, MPI_INTEGER, 
		0, comm);

	Merge_Sort_Rec(data, count, comm);
}
