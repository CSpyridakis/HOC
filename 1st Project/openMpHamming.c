#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "openMpHamming.h"
#include "mystructs.h"

double openMpHamm_taskA(structs *src, int **serialhammingValue) {

    printf("OpenMP task A...");
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

double openMpHamm_taskB(structs *src, int **serialhammingValue) {

    printf("OpenMP task B...");
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

double openMpHamm_taskC(structs *src, int **serialhammingValue) {

    printf("OpenMP task C...");
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

