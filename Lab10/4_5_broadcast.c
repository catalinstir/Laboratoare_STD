#include <mpi/mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	int x[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	if (rank == 2){
		printf("Vector initialized in process %d:\n", rank);
        for(int i=0;i<100;i++){
            x[i]=i+1;
			printf("%d ",x[i]);
        }
		printf("\n");

	}

	MPI_Bcast(&x, 100, MPI_INT, 2, MPI_COMM_WORLD);

    for (int i = 0; i < 10; ++i) {
        printf("Process %d Received %d from process 2\n",rank, x[i]);
    }
    printf(". . . elements 11 - 89 of process %d\n", rank);
    for (int i = 89; i < 100; ++i) {
        printf("Process %d Received %d from process 2\n",rank, x[i]);
    }

	
	MPI_Finalize();
	return 0;
}
