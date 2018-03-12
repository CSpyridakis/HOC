#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "pthreadsHamming.h"
#include "mystructs.h"

double pthreadsHamm_taskA(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY
    printf("PThreads task A...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();
    double calcTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Calculate sum of array
    begin = clock();
    int sum=calcSumOfArray(src->Alen,src->Blen,hammingValues);
    end = clock();
    double sumTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Validate Hamming Distance
    if (serialHammingSum!=sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec | Sum time:%f | Total time:%f\n",calcTime,sumTime,(calcTime+sumTime));
    return calcTime;
}

double pthreadsHamm_taskB(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY
    printf("PThreads task B...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();
    double calcTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Calculate sum of array
    begin = clock();
    int sum=calcSumOfArray(src->Alen,src->Blen,hammingValues);
    end = clock();
    double sumTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Validate Hamming Distance
    if (serialHammingSum!=sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec | Sum time:%f | Total time:%f\n",calcTime,sumTime,(calcTime+sumTime));
    return calcTime;
}

double pthreadsHamm_taskC(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY
    printf("PThreads task C...");
    clock_t begin = clock();

    //TODO MAIN LOGIC

    clock_t end = clock();
    double calcTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Calculate sum of array
    begin = clock();
    int sum=calcSumOfArray(src->Alen,src->Blen,hammingValues);
    end = clock();
    double sumTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Validate Hamming Distance
    if (serialHammingSum!=sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec | Sum time:%f | Total time:%f\n",calcTime,sumTime,(calcTime+sumTime));
    return calcTime;
}
