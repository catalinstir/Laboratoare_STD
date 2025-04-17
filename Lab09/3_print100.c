#include <openmpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	for (int i = 0; i < 100; i++)
		printf("Hello World from %i/%i at %i\n", rank, nProcesses, i);

	MPI_Finalize();
	return 0;
}