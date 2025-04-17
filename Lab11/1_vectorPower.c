#include <openmpi/mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int N;
int printLevel;
int *v;
int *outV;

void getArgs(int argc, char **argv)
{
	if (argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

void displayVectors(int *v, int *outV)
{
	int i;
	int max = 1;
	for (i = 0; i < N; i++) {
		if (max < log10(v[i]))
			max = log10(v[i]);
		if (max < log10(outV[i]))
			max = log10(outV[i]);
	}
	int displayWidth = 2 + max;

	printf("Original vector:\n");
	for (i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
		if (!((i + 1) % 20))
			printf("\n");
	}

	printf("Power vector:\n");
	for (i = 0; i < N; i++) {
		printf("%*i", displayWidth, outV[i]);
		if (!((i + 1) % 20))
			printf("\n");
	}
	printf("\n");
}

void printAll()
{
	displayVectors(v, outV);
}

void print()
{
	if (printLevel == 0)
		return;
	else
		printAll();
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);

	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	v = malloc(sizeof(int) * N);
	outV = malloc(sizeof(int) * N);

	if(rank == 0){
		for (int i = 0; i < N; i++)
			v[i] = rand() % 1000;
	}
	
	MPI_Scatter(v, N / nProcesses, MPI_INT, v, N / nProcesses, MPI_INT, 0, MPI_COMM_WORLD);
	int rez = 42;
	for (int i = 0; i< N/nProcesses; i++) {
		rez = 42;
		for (int j = 1; j <= v[i]; j++)
			rez = (rez * 42) % 1000;
		outV[i] = rez;
	}
	MPI_Gather(outV, N / nProcesses, MPI_INT, outV, N / nProcesses, MPI_INT, 0, MPI_COMM_WORLD);
	
	if(rank == 0){
		print();
		free(v);
		free(outV);
	}
	MPI_Finalize();

	return 0;
}