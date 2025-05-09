#include <openmpi/mpi.h>
#include <stdio.h>

void printHelloWorld()
{
	printf("Hello World\n");
}
void printSomethingElse()
{
	printf("Something Else...\n");
}

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	if (rank == 0)
		printHelloWorld();
	else if (rank == 1)
		printSomethingElse();

	MPI_Finalize();
	return 0;
}
