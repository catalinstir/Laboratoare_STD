#include <mpi/mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	if (rank == 0){
		srand(time(0));

		int x[100];
        for(int i=0;i<100;i++){
            x[i]=i+1;
        }

		MPI_Send(x, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process %i sent a vector\n", rank);

	}

	if (rank == 1){
		int y[100]={0};
		MPI_Recv(y, 100, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %i received the vector\n", rank);

		
        for(int i=0;i<100;i++){
            printf("%d ",y[i]);
        }
        printf("\n");
		
	}

	MPI_Finalize();
	return 0;
}
