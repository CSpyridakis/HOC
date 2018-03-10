#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "serialHamming.h"
#include "costum_structs.h"

int **initSerial(int a, int b) {
    int i, j;

    int **serV;

    serV = (int **) malloc(sizeof(int *) * a);
    for (i = 0; i < a; i++) {
        serV[i] = (int *) malloc(sizeof(int) * b);
    }

    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++) {
            serV[i][j] = 0;
        }
    }

    return serV;
}

double serialHamm(structs *src, int **serialhammingValue) {

    serialhammingValue = initSerial(src->Alen, src->Blen);

    clock_t begin = clock();
    int i, j, k;

    for (i = 0; i < src->Alen; i++) {
        for (j = 0; j < src->Blen; j++) {
            for (k = 0; k < src->Strlen; k++) {
                if (src->A[i][k] != src->B[j][k]) {
                    serialhammingValue[i][j]++;
                }
            }
        }
    }

    clock_t end = clock();

    // Display Serial Hamming values
//    displayHammingValues(src->Alen, src->Blen, serialhammingValue);

    return (double) (end - begin) / CLOCKS_PER_SEC;
}

