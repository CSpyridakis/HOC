#include <stdio.h>
#include <stdlib.h>
#include "mystructs.h"
#include "serialHamming.h"
#include "openMpHamming.h"
#include "pthreadsHamming.h"

int main() {

    /// Save Hamming Calculation times for each case
    hammingTimes hammT[ARRAYS_L][STRINGS_L];

    //For each struct length
    int i, j, k = 0;
    for (i = 0; i < ARRAYS_L; i++) {

        //For each string length
        for (j = 0; j < STRINGS_L; j++) {

            /// Create Struct that holds A and B for each case
            structs *newStruct = (structs *) malloc(sizeof(structs));
            // Random Generate new Structs
            structsGenerate(newStruct, aLength[i], bLength[i], stringLength[j]);

            /// Save Hamming values of serial calculation
            int **serialhammingValues;

            /// Serial Hamming Calculation
            hammT[i][j].serial = serialHamm(newStruct, serialhammingValues);

            /// OpenMp Hamming Calculation
            hammT[i][j].openMp[TASK_A] = openMpHamm_taskA(newStruct, serialhammingValues);
            hammT[i][j].openMp[TASK_B] = openMpHamm_taskB(newStruct, serialhammingValues);
            hammT[i][j].openMp[TASK_C] = openMpHamm_taskC(newStruct, serialhammingValues);

            /// Pthreads Hamming Calculation
            hammT[i][j].pthreads[TASK_A] = pthreadsHamm_taskA(newStruct, serialhammingValues);
            hammT[i][j].pthreads[TASK_B] = pthreadsHamm_taskB(newStruct, serialhammingValues);
            hammT[i][j].pthreads[TASK_C] = pthreadsHamm_taskC(newStruct, serialhammingValues);

            printf("%d\n",k++);

//           deallser(serialhammingValues,newStruct->Alen);
            deallsrc(newStruct);
        }
    }

    //Display Results for each case
    printResults(ARRAYS_L, STRINGS_L, (hammingTimes *) hammT);

    return 0;
}