#include <stdio.h>
#include <stdlib.h>
#include "mystructs.h"
#include "serialHamming.h"
#include "openMpHamming.h"
#include "pthreadsHamming.h"

int main(int argc, char ** argv) {

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
                /// Save Hamming sum of serial calculation
                unsigned long long serialsum;

                // Print loop information
                printf("\nCalculating Hamming distances for m:%d n:%d l:%d\n", newStruct->Alen, newStruct->Blen,
                       newStruct->Strlen);

                /// Serial Hamming Calculation
                hammT[i][j][k].serial = serialHamm(newStruct, &serialsum);

                /// OpenMp Hamming Calculation
                hammT[i][j][k].openMp[TASK_A] = openMpHamm_taskA(newStruct, serialsum);
                hammT[i][j][k].openMp[TASK_B] = openMpHamm_taskB(newStruct, serialsum);
                hammT[i][j][k].openMp[TASK_C] = openMpHamm_taskC(newStruct, serialsum);

                /// Pthreads Hamming Calculation
                hammT[i][j][k].pthreads[TASK_A] = pthreadsHamm_task(newStruct, serialsum, TASK_A);
                hammT[i][j][k].pthreads[TASK_B] = pthreadsHamm_task(newStruct, serialsum, TASK_B);
                hammT[i][j][k].pthreads[TASK_C] = pthreadsHamm_task(newStruct, serialsum, TASK_C);

                // De-allocate memory
                deallsrc(newStruct);
            }
        }
    }

    //Display Results for each case
    //printResults((hammingTimes *) hammT); //TODO

    return 0;
}