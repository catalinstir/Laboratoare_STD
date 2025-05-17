#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_SIZE 100
#define NUM_PROCESSES 4
#define CHUNK_SIZE (VECTOR_SIZE / NUM_PROCESSES)

int main(int argc, char **argv)
{
	int rank, size;
	int vector[VECTOR_SIZE];
	int local_chunk[CHUNK_SIZE];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != NUM_PROCESSES)
	{
		if (rank == 0)
		{
			printf("Program needs %d processes!!!\n", NUM_PROCESSES);
		}
		MPI_Finalize();
		return 1;
	}
	if (rank == 0)
	{
		for (int i = 0; i < VECTOR_SIZE; i++)
		{
			vector[i] = i;
		}
	}
	MPI_Scatter(vector, CHUNK_SIZE, MPI_INT,
				local_chunk, CHUNK_SIZE, MPI_INT,
				0, MPI_COMM_WORLD);
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		local_chunk[i] += 42;
	}
	MPI_Gather(local_chunk, CHUNK_SIZE, MPI_INT,
			   vector, CHUNK_SIZE, MPI_INT,
			   0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Reconstructed vector: \n");
		for (int i = 0; i < VECTOR_SIZE; i++)
		{
			printf("%d ", vector[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
	return 0;
}
