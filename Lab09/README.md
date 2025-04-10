# Laborator 9 - MPI

## 1. Introducere
Avem nevoie de WSL.

Acceesam fisierul laboratorului din WSL daca ne-am conectat la WSL din VSCode:
> /mnt/c/PATH_TO_DIR...

Ne instalam niste dependinte ale __mpi__-ului:
```sh
sudo apt-get update
sudo apt-get install gcc make gdb sshfs ssh 
```

Si acum instalam mpi-ul:
```sh
sudo apt-get install libopenmpi-dev openmpi-bin
sudo apt-get install openmpi-doc openmpi-common
```

Testam instalarea cu `mpicc`.
```sh
gcc: fatal error: no input files
compilation terminated.
```
Arhiva de laborator contine:
- 1_helloWorld.c
- 2_numCores.c
- 3_print100.c
- 4_twoDifferentProcesses.c
- 5_firstAndLast.c
- 6_varriables.c
- Makefile

## 2. Hello world
Avem fisierul sursa __1_helloWorld.c__:
```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello World from %i/%i \n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}
```

Un exemplu simplu de compilare ar fi pentru 1_helloWorld:
> mpicc 1_helloWorld.c -o 1_helloWorld
Output `./1_helloWorld`:
```sh
Hello World from 0/1 
```

Pentru un exemplu de rulare, avem:
> mpirun -n 4 ./1_helloWorld
Output:
```sh
Hello World from 2/4 
Hello World from 3/4 
Hello World from 0/4 
Hello World from 1/4
```

> [!NOTE]
> Numarul de 'workeri' dat de flag-ul `-n` este limitat de numarul de core-uri. Putem suprascrie limitarea asta folosind flag-ul `--oversubscribe`

