#ifndef PARALLEL_PTHREADSHAMMING_H
#define PARALLEL_PTHREADSHAMMING_H

#include "mystructs.h"

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src
 * @param serialHammingSum
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskA(structs *src, int serialHammingSum);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialHammingSum    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskB(structs *src, int serialHammingSum);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialHammingSum    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_taskC(structs *src, int serialHammingSum);


#endif //PARALLEL_PTHREADSHAMMING_H
