#ifndef PARALLEL_PTHREADSHAMMING_H
#define PARALLEL_PTHREADSHAMMING_H

#include "mystructs.h"

/**
 * @brief Calculate Hamming Distance using Pthreads. Parallel calculation of each String, Cell, Row
 *
 * @param src                    Struct where all needed info is located
 * @param serialHammingSum       Hamming Distances (Used for validate purpose)
 * @param task                   case task==TASK_A Parallel calculation of each String
 *                               case task==TASK_B Parallel calculation of each Cell
 *                               case task==TASK_C Parallel calculation of each Row
 *
 * @return (double) calculation time. In case hamming distance is wrong return -1
 */
double pthreadsHamm_task(structs *src, unsigned long long serialHammingSum, type task);

#endif //PARALLEL_PTHREADSHAMMING_H
