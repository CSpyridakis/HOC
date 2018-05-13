PATH_TO_SRC=./src/
PATH_TO_BIN=./bin/

TARGETS=serial sse mpi
EXECS=$(PATH_TO_BIN)serialR $(PATH_TO_BIN)sseR $(PATH_TO_BIN)sseRP $(PATH_TO_BIN)mpiR

GCC    = gcc
CFLAGS = -Wall -std=c99
MPICC  = mpicc
MFLAGS = -msse4.2

SERIAL_SOURCE=$(PATH_TO_SRC)serial_DNA.c
SSE_SOURSE=$(PATH_TO_SRC)sse_DNA.c
SSE_PTR_SOURCE=$(PATH_TO_SRC)sse_DNA_PTR.c
MPI_SOURCE=$(PATH_TO_SRC)sse-mpi_DNA.c

all: $(TARGETS) move

serial:
	$(GCC) $(CFLAGS) -o serialR $(SERIAL_SOURCE)

sse:
	$(GCC) $(CFLAGS) $(MFLAGS) -o sseR $(SSE_SOURSE)
	$(GCC) $(CFLAGS) $(MFLAGS) -o sseRP $(SSE_PTR_SOURCE)

mpi:
	$(MPICC) $(CFLAGS) $(MFLAGS) -o mpiR $(MPI_SOURCE)

move:
	mv serialR $(PATH_TO_BIN)
	mv sseR $(PATH_TO_BIN)
	mv sseRP $(PATH_TO_BIN)
	mv mpiR $(PATH_TO_BIN)

clean:
	$(RM) $(EXECS)

	