#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "serialHamming.h"
#include "mystructs.h"

double serialHamm(structs *src, int *serialSum) {

    int **serialhammingValues = init2dArray(src->Alen, src->Blen);
    printf("Serial...");

    /// Calculate Hamming Distance in NON-optimized (Serial) way
    clock_t begin = clock();
    int i, j, k;
    for (i = 0; i < src->Alen; i++) {
        for (j = 0; j < src->Blen; j++) {
            for (k = 0; k < src->Strlen; k++) {
                if (src->A[i][k] != src->B[j][k]) {
                    serialhammingValues[i][j]++;
                }
            }
        }
    }
    clock_t end = clock();
    double calcTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Calculate sum of array
    begin = clock();
    *serialSum=calcSumOfArray(src->Alen,src->Blen,serialhammingValues);
    end = clock();
    double sumTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Display Serial Hamming values
//    displayHammingValues(src->Alen, src->Blen, serialhammingValue);

    printf("finished\t\t Hamming Time:%f sec | Sum Value:%d | Sum Calculation:%f | Total time:%f\n",calcTime,(*serialSum),sumTime,(calcTime+sumTime));
    return calcTime+sumTime;
}


