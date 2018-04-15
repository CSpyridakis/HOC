all: serial #sse mpi 

serial:
	gcc -o serialR serial_DNA.c

sse:
	gcc -msse4.2 -o sseR sse_DNA.c

mpi:
	mpicc -msse4.2 -o mpiR sse-mpi_DNA.c

clean:
	rm -rf *.o
	rm -rf serialR sseR mpiR