#ifndef PARALLEL_PTHREADSHAMMING_H
#define PARALLEL_PTHREADSHAMMING_H

#include "mystructs.h"

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src
 * @param serialhammingValue
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskA(structs *src, int **serialhammingValue);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskB(structs *src, int **serialhammingValue);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskC(structs *src, int **serialhammingValue);


#endif //PARALLEL_PTHREADSHAMMING_H
