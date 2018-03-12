#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "serialHamming.h"
#include "mystructs.h"

double serialHamm(structs *src, int *serialSum) {
    /// Init Serial Sum
    (*serialSum)=0;

    /// Save hamming distances
    int **serialhammingValues = init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY

    /// Calculate Hamming Distance in NON-optimized (Serial) way
    printf("Serial............");
    clock_t begin = clock();
    int i, j, k;
    for (i = 0; i < src->Alen; i++) {
        for (j = 0; j < src->Blen; j++) {
            for (k = 0; k < src->Strlen; k++) {
                if (src->A[i][k] != src->B[j][k]) {
                    serialhammingValues[i][j]++;
                    (*serialSum)++;
                }
            }
        }
    }
    clock_t end = clock();
    double calcTime=(double) (end - begin) / CLOCKS_PER_SEC;

    // Display Serial Hamming values
//    displayHammingValues(src->Alen, src->Blen, serialhammingValues);

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec | Sum Value:%d\n",calcTime,(*serialSum));
    return calcTime;
}


