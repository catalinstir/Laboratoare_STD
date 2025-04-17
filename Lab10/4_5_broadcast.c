#include <openmpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	// 2
	// int val;

	// 3
	int vec [100];
	if (rank == 1){
		// 2
		// val = 7;
		// printf("Process %d broadcasted value %d with addres %p\n", rank, val, &val);

		// 3
		for (int i = 0; i < 100; i++){
			vec[i] = i + 1;
		}
		printf("Process %d broadcasted vector with address %p\n", rank, &vec);

	}
	// 2
	// MPI_Bcast(&val, 1, MPI_INT, 1, MPI_COMM_WORLD);

	// 3
	MPI_Bcast(vec, 100, MPI_INT, 1, MPI_COMM_WORLD);

	if (rank != 1){
		// 2
		// printf("Process %d received value %d with address %p\n", rank, val, &val);

		// 3
		printf("Process %d received vector: ", rank);
		for (int i = 0; i < 100; i++){
			printf("%d ", vec[i]);
		}
		printf("\n");
	}
	

	MPI_Finalize();
	return 0;
}