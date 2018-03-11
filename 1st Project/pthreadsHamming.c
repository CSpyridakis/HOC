#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "pthreadsHamming.h"
#include "mystructs.h"

double pthreadsHamm_taskA(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
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
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Hamming Time:%f sec | Sum Value:%d | Sum Calculation:%f | Total time:%f\n",calcTime,sum,sumTime,(calcTime+sumTime));
    return calcTime+sumTime;
}

double pthreadsHamm_taskB(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
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
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Hamming Time:%f sec | Sum Value:%d | Sum Calculation:%f | Total time:%f\n",calcTime,sum,sumTime,(calcTime+sumTime));
    return calcTime+sumTime;
}

double pthreadsHamm_taskC(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
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
        printf("Error!\n");
        return (double) (-1);
    }

    printf("finished\t Hamming Time:%f sec | Sum Value:%d | Sum Calculation:%f | Total time:%f\n",calcTime,sum,sumTime,(calcTime+sumTime));
    return calcTime+sumTime;
}
