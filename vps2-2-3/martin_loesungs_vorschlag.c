#include <mpi.h>

void merge_sort_do(int* values, int length, MPI_Comm comm);
void merge_sort(int* values, int length);
void merge(int *values, int* left, int left_size, int* right, int right_size);

int main (int argc,char** argv) {
	int myid, numprocs;
	int  namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	const int values = 64;
	int* bla = (int*) malloc(sizeof(int) * values);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);
	
	if(myid == 0) {
		int i;
		for(i = 0; i < values; ++i) {
			bla[i] = rand() % 100 + 1;
			printf("random value: %d\n", bla[i]);
		}
	}
	
	if(numprocs % 2 == 0 || numprocs == 1) {
		int i;
		merge_sort_do(bla, values, MPI_COMM_WORLD);
		for(i = 0; i < values; ++i) {
			printf("%d\n", bla[i]);
		}
	} else if(myid == 0) {
		printf("please specify an even amount of processors or only one");
	}
	
	MPI_Finalize();	
}

void merge_sort_do(int* values, int length, MPI_Comm comm) {
	int numprocs;
	int rank;
	int in_lower_half;
	int* recv;
	int* rec_data;
	int elements_per_proc;
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &rank);
	if(numprocs > 1) {
		MPI_Comm new_comm;
		int i;
		int j;
		elements_per_proc = length / numprocs;
		recv = values + rank * elements_per_proc;
		
		MPI_Scatter(values, elements_per_proc, MPI_INTEGER,
			recv, elements_per_proc, MPI_INTEGER, 0, comm);
			
		in_lower_half = rank < (numprocs / 2);
		rec_data = (in_lower_half) ? values : values + (numprocs / 2);
		MPI_Comm_split(comm, in_lower_half, rank, &new_comm);
		
		merge_sort_do(rec_data, length / 2, new_comm);
		
		MPI_Gather(recv, elements_per_proc, MPI_INTEGER, values,
			elements_per_proc, MPI_INTEGER, 0, comm);
		
		merge(values, values, length / 2, values + (length / 2), (length + 1) / 2);
	} else {
		int i;
		for(i = 0; i < length; ++i) {
			printf("%d ", values[i]);
		}
		printf("only one process left in comm. start sorting\n");
		merge_sort(values, length);
	}
}

void merge_sort(int* values, int length) {
	if(length > 1) {
		int* left = (int*) malloc(sizeof(int) * (length / 2));
		int* right = (int*) malloc(sizeof(int) * ((length + 1) / 2));
		int i;
		for(i = 0; i < length / 2; ++i) {
			left[i] = values[i];
		}
		for(i = length / 2; i < length ; ++i) {
			right[i - length / 2] = values[i];
		}
		merge_sort(left, length / 2);
		merge_sort(right, (length + 1) / 2);	

		merge(values, left, length / 2, right, (length + 1) / 2);
		
		free(left);
		free(right);
	}
}


void merge(int * values, int* left, int left_size, int* right, int right_size) {
	int length = right_size + left_size;
	int i;
	int left_pos = 0;
	int right_pos = 0;
	int done = 0;
	for(i = 0; i < length; ++i) {
		if(done !=  2 && left[left_pos] <= right[right_pos] || done == 1) {
			values[i] = left[left_pos];
			if(left_pos == length / 2 - 1) {
				done = 2;
			} else {
				++left_pos;
			}
		} else {
			values[i] = right[right_pos];
			if(right_pos == length - 1) {
				done = 1;
			} else {
				++right_pos;
			}
		}
	}
}