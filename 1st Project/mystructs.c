#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mystructs.h"

void structsGenerate(structs *src, int alen, int blen, int strlen) {

    int i, j;
    int row = alen;
    int col = strlen;

    /// Copy main Values
    src->Alen = alen;
    src->Blen = blen;
    src->Strlen = strlen;

    // Initialize random
    srand(time(NULL));

    /// Create two two dimension RANDOM char arrays
    src->A = (char **) malloc(sizeof(char *) * src->Alen);
    src->B = (char **) malloc(sizeof(char *) * src->Blen);
    for (i = 0; i < row; i++) {
        src->A[i] = (char *) malloc(sizeof(char) * src->Strlen);
        src->B[i] = (char *) malloc(sizeof(char) * src->Strlen);
        for (j = 0; j < col; j++) {
            src->A[i][j] = (rand() % 2) + '0';
            src->B[i][j] = (rand() % 2) + '0';
        }
    }
}

void deallsrc(structs *src) {
    int i;
    for (i = 0; i < src->Alen; i++) {
        free(src->A[i]);
        free(src->B[i]);
    }
    free(src->A);
    free(src->B);
    free(src);
}

void printResults(int srcL, int strL, hammingTimes *hammT) {
    //TODO MAIN LOGIC
}

void displayHammingValues(int alen, int blen, int **serV) {
    int i, j;
    for (i = 0; i < alen; i++) {
        for (j = 0; j < blen; j++) {
            printf("|%6d", serV[i][j]);
        }
        printf("|\n");
    }

}

bool validateHamm() {
    //TODO MAIN LOGIC
    return true;
}

void deallser(int **serV, int a) {
    int i;
    for (i = 0; i < a; i++) {
        free(serV[i]);
    }
    free(serV);
}