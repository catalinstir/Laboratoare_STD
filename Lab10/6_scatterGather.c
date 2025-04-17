#include <openmpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	int vec[100];
	if(rank == 0){
		for(int i = 0; i < 100; i++){
			vec[i] = i;
		}
	}
	MPI_Scatter(vec, 25, MPI_INT, vec, 25, MPI_INT, 0, MPI_COMM_WORLD);
	for(int i = 0; i < 25; i++){
		vec[i]+=42;
		printf("Rank %d: vec[%d] = %d (original value: %d)\n", rank, i, vec[i], vec[i] - 42);
	}

	MPI_Gather(vec, 25, MPI_INT, vec, 25, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
        printf("Processed vec:\n");
        for (int i = 0; i < 100; i++) {
            printf("%d ", vec[i]);
        }
        printf("\n");
    }
	
	MPI_Finalize();
	return 0;
}