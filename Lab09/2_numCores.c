#include <openmpi/mpi.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello World from %i/%i \n", rank, nProcesses);
	if (rank == 0)
		printf("Number of cores: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	MPI_Finalize();
	return 0;
}