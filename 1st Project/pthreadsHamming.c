#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "pthreadsHamming.h"
#include "costum_structs.h"

double pthreadsHamm_taskA(structs *src, int **serialhammingValue) {
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double pthreadsHamm_taskB(structs *src, int **serialhammingValue) {
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double pthreadsHamm_taskC(structs *src, int **serialhammingValue) {
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}
