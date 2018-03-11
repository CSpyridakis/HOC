#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "openMpHamming.h"
#include "mystructs.h"

double openMpHamm_taskA(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
    printf("OpenMP task A...");
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

double openMpHamm_taskB(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
    printf("OpenMP task B...");
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

double openMpHamm_taskC(structs *src, int serialHammingSum) {

    int ** hammingValues=init2dArray(src->Alen, src->Blen);
    printf("OpenMP task C...");
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

