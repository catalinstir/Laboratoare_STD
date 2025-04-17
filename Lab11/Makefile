VECTOR_RUN_n=2
VECTOR_RUN_N=1000

helloWorld: 0_helloWorld.c
	mpicc -o helloWorld 0_helloWorld.c -Wall -O3

vectorPower: 1_vectorPower.c
	mpicc -o vectorPower 1_vectorPower.c -Wall -O3 -lm

rankSort: 3_rankSort.c
	mpicc -o rankSort 3_rankSort.c -Wall -O3 -lm
