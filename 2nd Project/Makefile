EXECS=serial sse mpi

GCC    = gcc
CFLAGS = -Wall -std=c99


MPICC  = mpicc
MFLAGS = -msse4.2

all: ${EXECS}

serial:
	${GCC} ${CFLAGS} -o serialR serial_DNA.c

sse:
	${GCC} ${CFLAGS} ${MFLAGS} -o sseR sse_DNA.c
	${GCC} ${CFLAGS} ${MFLAGS} -o sseRP sse_DNA_PTR.c

mpi:
	${MPICC} ${CFLAGS} ${MFLAGS} -o mpiR sse-mpi_DNA.c

clean:
	rm -rf *.o
	rm -rf serialR sseR sseRP mpiR
