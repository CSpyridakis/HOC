#include <stdio.h>
#include <stdlib.h>
#include "mystructs.h"
#include "serialHamming.h"
#include "openMpHamming.h"
#include "pthreadsHamming.h"

int main() {

    /// Save Hamming Calculation times for each case
    hammingTimes hammT[ARRAY_A][ARRAY_B][STRINGS_L];

    int i, j, k = 0;
    for (i = 0; i < ARRAY_A; i++) {
        for (j = 0; j < ARRAY_B; j++) {
            for (k = 0; k < STRINGS_L; k++) {

                /// Create Struct that holds A and B for each case
                structs *newStruct = (structs *) malloc(sizeof(structs));
                // Random Generate new Structs
                structsGenerate(newStruct, aLength[i], bLength[j], stringLength[k]);
                /// Save Hamming values of serial calculation
                int **serialhammingValues;

                // Print loop information
                printf("\n\nCalculating Hamming distances for m:%d n:%d l:%d\n", newStruct->Alen, newStruct->Blen,
                       newStruct->Strlen);

                /// Serial Hamming Calculation
                hammT[i][j][k].serial = serialHamm(newStruct, serialhammingValues);

                /// OpenMp Hamming Calculation
                hammT[i][j][k].openMp[TASK_A] = openMpHamm_taskA(newStruct, serialhammingValues);
                hammT[i][j][k].openMp[TASK_B] = openMpHamm_taskB(newStruct, serialhammingValues);
                hammT[i][j][k].openMp[TASK_C] = openMpHamm_taskC(newStruct, serialhammingValues);

                /// Pthreads Hamming Calculation
                hammT[i][j][k].pthreads[TASK_A] = pthreadsHamm_taskA(newStruct, serialhammingValues);
                hammT[i][j][k].pthreads[TASK_B] = pthreadsHamm_taskB(newStruct, serialhammingValues);
                hammT[i][j][k].pthreads[TASK_C] = pthreadsHamm_taskC(newStruct, serialhammingValues);

//                deallser(serialhammingValues,newStruct->Alen);
                deallsrc(newStruct);
            }
        }
    }

    //Display Results for each case
    printResults(ARRAY_A, ARRAY_B, STRINGS_L, (hammingTimes *) hammT);

    return 0;
}