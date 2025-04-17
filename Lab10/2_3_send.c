#include <openmpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	if (rank == 0){
		// 2
		// srand(time(0));
		// int x = rand();
		// MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		// printf("[%d] sent %d!\n", rank, x);

		// 3
		int x[100];
		for(int i = 1;i<=100;i++)x[i-1]=i;
		MPI_Send(x, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("[%d] sent vector\n", rank);
	}
	if (rank == nProcesses - 1){
		// 2
		// int y;
		// MPI_Recv(&y, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		// printf("[%d] received %d!\n", rank, y);

		// 3
		int y[100];
		MPI_Recv(y, 100, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("[%d] received: ", rank);
		for(int i = 0;i<100;i++){
			if(y[i] != i+1){
				printf("Error: %d != %d\n", y[i], i+1);
				break;
			}else{
				y[i] < 100 ? printf("%i, ", y[i]) : printf("%i\n", y[i]);
			}

		}
	}
	MPI_Finalize();
	return 0;
}