#ifndef PARALLEL_SERIALHAMMING_H
#define PARALLEL_SERIALHAMMING_H

#include "mystructs.h"

/**
 * @brief Calculate Hamming Values of Arrays src->A and src->B in NON-optimized (Serial) way
 *
 * @param src                   Struct where all needed info is located
 * @param serialhammingValue    Hamming Distances (Used for validate purpose)
 *
 * @return (double) seconds of execution
 */
double serialHamm(structs *src, int *serialhammingValue);

#endif //PARALLEL_SERIALHAMMING_H
