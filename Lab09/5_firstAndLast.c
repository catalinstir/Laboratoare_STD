#include <openmpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	printf("Hello World\n");
	if (rank == 0)
		printf("Hello from first\n");
	else if (rank == nProcesses - 1)
		printf("Hello from last\n");

	MPI_Finalize();
	return 0;
}