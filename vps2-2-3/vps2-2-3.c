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
	int data[64];
	
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);

	
	for(i = 0; i< 64; ++i)
	{
		data[i] = rand();
	}

	Merge_Sort_Rec(data, 64, MPI_COMM_WORLD);

	for(i = 0; i< 64; ++i)
	{
		printf("%i\n", data[i]);
	}
	
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
	int i,j, tmp;
	int elements_per_proc;
	int* recv_ptr;

	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &mpi_size);

	if(mpi_size > 1)
	{
		elements_per_proc = count / mpi_size;
		recv_ptr = data + rank * elements_per_proc;
		MPI_Scatter(
			data, elements_per_proc, MPI_INTEGER, 
			recv_ptr, elements_per_proc, MPI_INTEGER, 
			0, comm);

		in_lower_half = rank < (mpi_size / 2);
		rec_data = (in_lower_half) ? data : data + (mpi_size/2);
		MPI_Comm_split(comm, in_lower_half, rank, &sub_comm);
		
		Merge_Sort_Rec(rec_data, count / 2, sub_comm);

		MPI_Gather(recv_ptr, elements_per_proc, MPI_INTEGER,
		data, elements_per_proc, MPI_INTEGER,
		0, comm);

		//Merge
		i = 0;
		j = count / 2;
	
		while(j < count && i < count)
		{
			tmp = data[i];
			if(tmp <= data[j])
			{
				data[i] = tmp;
			}
			else
			{
				data[i] = data[j];
				data[j] = tmp;
				++j;
			}	
			++i;
		}
	}
	else
	{
		//BubbleSort (why in C ?, why? )
		//std::sort

		for(i = count - 1; i > 0; --i)
		{
			for(j = 0; j < i; ++j)
			{
				if(data[j] > data[j+1])
				{
					tmp = data[j+1];
					data[j+1] = data[j];
					data[j] = tmp;
				}
			}
		}
	}

	
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

	MPI_Gather(recv_ptr, elements_per_proc, MPI_INTEGER,
		data, elements_per_proc, MPI_INTEGER,
		0, comm);
}
