#ifndef PARALLEL_OPENMPHAMMING_H
#define PARALLEL_OPENMPHAMMING_H

#include "costum_structs.h"

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskA(structs *src, int **serialhammingValue);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskB(structs *src, int **serialhammingValue);

/**
 * @brief Calculate Hamming Distance using OpenMP//TODO
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double openMpHamm_taskC(structs *src, int **serialhammingValue);

#endif //PARALLEL_OPENMPHAMMING_H
