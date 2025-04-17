all: helloWorld

helloWorld: 1_helloWorld.c
	mpicc -o helloWorld 1_helloWorld.c -Wall -O3
run_helloWorld:
	mpirun -np 4 ./helloWorld


send: 2_3_send.c
	mpicc -o send 2_3_send.c -Wall -O3
run_send:
	mpirun -np 2 ./send


broadcast: 4_5_broadcast.c
	mpicc -o broadcast 4_5_broadcast.c -Wall -Og
run_broadcast:
	mpirun -np 4 ./broadcast


scatterGather: 6_scatterGather.c
	mpicc -o scatterGather 6_scatterGather.c -Wall -O3
run_scatterGather:
	mpirun -np 4 ./scatterGather
	

circle: 7_circle.c
	mpicc -o circle 7_circle.c -Wall -O3
run_circle:
	mpirun -np 10 ./circle


anySource: 8_anySource.c
	mpicc -o anySource 8_anySource.c -Wall -O3
run_anySource:
	mpirun -np 4 ./anySource


anyTag: 9_anyTag.c
	mpicc -o anyTag 9_anyTag.c -Wall -O3
run_anyTag:
	mpirun -np 2 ./anyTag
	

findNum: 10_findNum.c
	mpicc -o findNum 10_findNum.c -Wall -O3
run_findNum:
	mpirun -np 10 ./findNum


findNumAuto: 11_findNumAuto.c
	mpicc -o findNumAuto 11_findNumAuto.c -Wall -O3
run_findNumAuto:
	mpirun -np 4 ./findNumAuto

