#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int Merge_Sort_Rec(int* data, int count, MPI_Comm comm);

int main (int argc, char** argv)
{
	int i,rank;
	int data[64];


	MPI_Init(&argc,&argv);


	for(i = 0; i< 64; ++i)
	{
		data[i] = rand();
	}

	Merge_Sort_Rec(data, 64, MPI_COMM_WORLD);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0)
	{
		for(i = 0; i< 64; ++i)
		{
			printf("%i\n", data[i]);
		}
	}

	MPI_Finalize();
	return 0;
}

int Merge_Sort_Rec(int* data, int count, MPI_Comm comm)
{
	int global_size;
	int global_rank;
	int local_rank, local_size;
	int gather_rank;
	MPI_Comm sub_comm = MPI_COMM_NULL, gather_comm;
	int color;
	int i,j, tmp;
	int elements_per_proc;
	int* recv_ptr = NULL, *send_ptr = NULL;

	MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &global_size);

	MPI_Comm_rank(comm, &local_rank);
	MPI_Comm_size(comm, &local_size);

	elements_per_proc = count / global_size;
	send_ptr = data + (global_rank * elements_per_proc);

	if(local_size == global_size)
	{
		recv_ptr = (int*) malloc(sizeof(int) * elements_per_proc);

		MPI_Scatter(data, elements_per_proc, MPI_INTEGER, 
			recv_ptr, elements_per_proc, MPI_INTEGER, 
			0, MPI_COMM_WORLD);
		memcpy(send_ptr, recv_ptr, sizeof(int) * elements_per_proc);

		free(recv_ptr);		
	}

	if(local_size > 1)
	{
		color = local_rank < (local_size / 2);
		MPI_Comm_split(comm, color, local_rank, &sub_comm);
		color = (local_rank % (local_size / 2)) == 0;
		MPI_Comm_split(comm, color, local_rank, &gather_comm);

		elements_per_proc = Merge_Sort_Rec(data, count, sub_comm);



		if(color)
		{
			MPI_Comm_rank(gather_comm, &gather_rank);

			if(gather_rank == 0)
			{
				recv_ptr = (int*) malloc(sizeof(int) * elements_per_proc * 2);
			}

			MPI_Gather(send_ptr, elements_per_proc, MPI_INTEGER,
				recv_ptr, elements_per_proc, MPI_INTEGER,
				0, gather_comm);

			if(gather_rank == 0)
			{
				//Merge

				count = elements_per_proc * 2;
				i = 0;
				j = count / 2;
				tmp = 0;

				while(tmp < count)
				{
					
					if(i < (count / 2) && (j == count || recv_ptr[i] <= recv_ptr[j]))
					{
						send_ptr[tmp] = recv_ptr[i];
						++i;
					}
					else
					{
						
						send_ptr[tmp] = recv_ptr[j];
						++j;
					}
					++tmp;
				}


				free(recv_ptr);
			}
		}



		return elements_per_proc * 2;
	}
	else
	{

		//BubbleSort (why in C ?, why? )
		//std::sort




		for(i = elements_per_proc - 1; i > 0; --i)
		{
			for(j = 0; j < i; ++j)
			{
				if(send_ptr[j] > send_ptr[j+1])
				{
					tmp = send_ptr[j+1];
					send_ptr[j+1] = send_ptr[j];
					send_ptr[j] = tmp;
				}
			}
		}

		return elements_per_proc;
	}


}
