#include "openMpHamming.h"
#include <stdio.h>
#include <omp.h>


double openMpHamm_taskA(structs *src, unsigned long long serialHammingSum) {

    long sum = 0;
    int **hammingValues = init2dArray(src->Alen, src->Blen);

    printf("OpenMP task A.....");
    double begin = gettime();
    #pragma omp parallel
    {
        int i,j,k,t,psum=0;

        int NUM_THREADS=omp_get_num_threads();
        int THREAD_ID=omp_get_thread_num();

        //In order to reduce data races each thread access array of A in pseudo-random order
        for(t=0;t<NUM_THREADS;t++){
            int start=(t+THREAD_ID)%NUM_THREADS;
            for(i=start;i<src->Alen;i=i+NUM_THREADS){
                for (j = 0; j < src->Blen; j++) {
                    #pragma omp for nowait
                    for (k = 0; k < src->Strlen; k++) {
                        if (src->A[i][k] != src->B[j][k]) {
                            psum++;

                            #pragma omp atomic
                            hammingValues[i][j]++;
                        }
                    }
                }
            }
        }

        #pragma omp atomic
        sum += psum;
    }
    double end = gettime();
    double calcTime = end - begin;

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    //Print results
    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues));//TODO REMOVE ONLY FOR DEBUGGING DATA RACE
    printf("\n");
    return calcTime;
}

double openMpHamm_taskB(structs *src, unsigned long long serialHammingSum) {

    long sum = 0;
    int **hammingValues = init2dArray(src->Alen, src->Blen);

    printf("OpenMP task B.....");
    double begin = gettime();
    #pragma omp parallel
    {
        int i, j, k, psum = 0;
        for(k=0;k<src->Strlen;k++){
            #pragma omp for collapse(2) nowait
            for(i=0;i<src->Alen;i++){
                for(j=0;j<src->Blen;j++){
                    if (src->A[i][k] != src->B[j][k]) {
                        hammingValues[i][j]++;
                        psum++;
                    }
                }
            }
        }

        #pragma omp atomic
        sum += psum;

    }
    double end = gettime();
    double calcTime = (double) (end - begin);

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    //Print results
    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues));//TODO REMOVE ONLY FOR DEBUGGING DATA RACE
    printf("\n");
    return calcTime;
}

double openMpHamm_taskC(structs *src, unsigned long long serialHammingSum) {
    long sum = 0;
    int **hammingValues = init2dArray(src->Alen, src->Blen);

    printf("OpenMP task C.....");
    double begin = gettime();
    #pragma omp parallel
    {
        int i, j, k, psum = 0;
        for (i = 0; i < src->Alen; i++) {
            for (k = 0; k < src->Strlen; k++) {
                #pragma omp for nowait
                for (j = 0; j < src->Blen; j++) {
                    if (src->A[i][k] != src->B[j][k]) {
                        hammingValues[i][j]++;
                        psum++;
                    }
                }
            }
        }
        #pragma omp atomic
        sum += psum;
    }
    double end = gettime();
    double calcTime = (double) (end - begin);

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    //Print results
    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues));//TODO REMOVE ONLY FOR DEBUGGING DATA RACE
    printf("\n");
    return calcTime;
}