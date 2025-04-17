#include <openmpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	int a = 2;
	int b = 0;
	if (rank == 0)
		b = 100;
	else if (rank == nProcesses - 1)
		b = 1000;
	printf("Hello World: %i\n", (a << rank) + b);

	MPI_Finalize();
	return 0;
}