GCC = gcc
OMP_FLAGS = -fopenmp
PTHREADS_FLAGS= -lpthread

PATH_TO_BIN=./bin/
PATH_TO_SRC=./src/
PATH_TO_BUILD=./build/


all:
	$(GCC) -c $(PATH_TO_SRC)main.c $(PATH_TO_SRC)mystructs.c $(PATH_TO_SRC)serialHamming.c
	$(GCC) $(OMP_FLAGS) -c $(PATH_TO_SRC)openMpHamming.c
	$(GCC) $(PTHREADS_FLAGS)$(PTHREADS_FLAGS) -c $(PATH_TO_SRC)pthreadsHamming.c
	$(GCC) $(OMP_FLAGS) $(PTHREADS_FLAGS) main.o mystructs.o serialHamming.o openMpHamming.o pthreadsHamming.o -o run
	mv *.o $(PATH_TO_BUILD)

clean:
	$(RM) $(PATH_TO_BUILD)*.o
	$(RM) run
