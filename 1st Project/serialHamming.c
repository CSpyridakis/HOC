#include "mystructs.h"
#include <stdio.h>
#include "serialHamming.h"

double serialHamm(structs *src, unsigned long long *serialSum) {
    /// Init Serial Sum
    (*serialSum)=0;

    /// Save hamming distances
    int **serialhammingValues = init2dArray(src->Alen, src->Blen);//TODO DE-ALLOCATE MEMORY

    /// Calculate Hamming Distance in NON-optimized (Serial) way
    printf("Serial............");
    double begin = gettime();
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
    double end = gettime();
    double calcTime=end - begin;

    // Display Serial Hamming values
    //displayHammingValues(src->Alen, src->Blen, serialhammingValues);

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec | Sum Value:%lld\n",calcTime,(*serialSum));
    return calcTime;
}


