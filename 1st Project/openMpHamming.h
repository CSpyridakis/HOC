#ifndef PARALLEL_OPENMPHAMMING_H
#define PARALLEL_OPENMPHAMMING_H

#include "mystructs.h"

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialHammingSum      Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskA(structs *src, unsigned long long serialHammingSum);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialHammingSum      Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskB(structs *src, unsigned long long serialHammingSum);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialHammingSum      Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskC(structs *src, unsigned long long serialHammingSum);

#endif //PARALLEL_OPENMPHAMMING_H
