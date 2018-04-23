all: serial sse #mpi 

serial:
	gcc -o serialR serial_DNA.c -std=c99

sse:
	gcc -msse4.2 -o sseR sse_DNA.c -std=c99

mpi:
	mpicc -msse4.2 -o mpiR sse-mpi_DNA.c -std=c99

clean:
	rm -rf *.o
	rm -rf serialR sseR mpiR
