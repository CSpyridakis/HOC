all:
	gcc -c main.c mystructs.c serialHamming.c
	gcc -fopenmp -c openMpHamming.c
	gcc -lpthread -c pthreadsHamming.c
	gcc -fopenmp -lpthread main.o mystructs.o serialHamming.o openMpHamming.o pthreadsHamming.o -o run

clean:
	rm *.o
	rm run
