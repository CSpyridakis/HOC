TARGETS=serial sse mpi
EXECS=serialR sseR sseRP mpiR

GCC    = gcc
CFLAGS = -Wall -std=c99
MPICC  = mpicc
MFLAGS = -msse4.2

SERIAL_SOURCE=serial_DNA.c
SSE_SOURSE=sse_DNA.c
SSE_PTR_SOURCE=sse_DNA_PTR.c
MPI_SOURCE=sse-mpi_DNA.c

all: $(TARGETS)

serial:
	$(GCC) $(CFLAGS) -o serialR $(SERIAL_SOURCE)

sse:
	$(GCC) $(CFLAGS) $(MFLAGS) -o sseR $(SSE_SOURSE)
	$(GCC) $(CFLAGS) $(MFLAGS) -o sseRP $(SSE_PTR_SOURCE)

mpi:
	$(MPICC) $(CFLAGS) $(MFLAGS) -o mpiR $(MPI_SOURCE)

clean:
	$(RM) $(EXECS)