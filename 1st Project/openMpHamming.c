#include "openMpHamming.h"
#include <stdio.h>
#include <omp.h>


double openMpHamm_taskA(structs *src, int serialHammingSum) {

    int sum = 0;

    int **hammingValues = init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY

    printf("OpenMP task A.....");
    double begin = gettime();
    #pragma omp parallel
    {
        int i, j, k, su = 0;
        for (i = 0; i < src->Alen; i++) {
            for (j = 0; j < src->Blen; j++) {
                #pragma omp for
                for (k = 0; k < src->Strlen; k++) {
                    if (src->A[i][k] != src->B[j][k]) {
                        su++;
                    }
                }
            }
        }

        #pragma omp critical
        {
            sum += su;
        }
    }
    double end = gettime();
    double calcTime = end - begin;

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec\n", calcTime);
    return calcTime;
}

double openMpHamm_taskB(structs *src, int serialHammingSum) {

    int sum = 0;

    int **hammingValues = init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY

    printf("OpenMP task B.....");
    double begin = gettime();

    //TODO MAIN LOGIC
    //TODO sum++

    double end = gettime();
    double calcTime = (double) (end - begin);

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec\n", calcTime);
    return calcTime;
}

double openMpHamm_taskC(structs *src, int serialHammingSum) {

    int sum = 0;

    int **hammingValues = init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY

    printf("OpenMP task C.....");
    double begin = gettime();

    //TODO MAIN LOGIC
    //TODO sum++

    double end = gettime();
    double calcTime = (double) (end - begin);


    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec\n", calcTime);
    return calcTime;
}