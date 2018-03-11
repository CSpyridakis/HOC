#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "pthreadsHamming.h"
#include "mystructs.h"

double pthreadsHamm_taskA(structs *src, int **serialhammingValue) {

    printf("PThreads task A...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm()) {
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Time of execution:%f sec\n",(double) (end - begin) / CLOCKS_PER_SEC);
    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double pthreadsHamm_taskB(structs *src, int **serialhammingValue) {

    printf("PThreads task B...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm()) {
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Time of execution:%f sec\n",(double) (end - begin) / CLOCKS_PER_SEC);
    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double pthreadsHamm_taskC(structs *src, int **serialhammingValue) {

    printf("PThreads task C...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm()) {
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Time of execution:%f sec\n",(double) (end - begin) / CLOCKS_PER_SEC);
    return (double) (end - begin) / CLOCKS_PER_SEC;
}
