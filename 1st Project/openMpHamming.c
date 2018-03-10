#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "openMpHamming.h"
#include "costum_structs.h"

double openMpHamm_taskA(structs *src, int **serialhammingValue) {

    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double openMpHamm_taskB(structs *src, int **serialhammingValue) {
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

double openMpHamm_taskC(structs *src, int **serialhammingValue) {
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();

    if (!validateHamm())
        return (double) (-1);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

