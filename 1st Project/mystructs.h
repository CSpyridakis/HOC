#ifndef PARALLEL_COSTUM_STRUCTS_H
#define PARALLEL_COSTUM_STRUCTS_H

/**
 * @brief Project input variables
 */
#define ARRAY_A 4
#define ARRAY_B 4
#define STRINGS_L 3
static int aLength[ARRAY_A] = {1, 100, 1000, 10000};             // equals with number m
static int bLength[ARRAY_B] = {1, 100, 1000, 10000};             // equals with number n
static int stringLength[STRINGS_L] = {10, 100, 1000};             // equals with number l

typedef int bool;
#define true 1
#define false 0

#define TASK_A 0
#define TASK_B 1
#define TASK_C 2

#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"

/**
 * @brief Struct where calculation times are stored
 */
typedef struct calcTimes {
    double serial;
    double openMp[3];
    double pthreads[3];
} hammingTimes;

/**
 * @brief Struct that holds two needed arrays
 */
typedef struct structsR {
    char **A;
    int Alen;
    char **B;
    int Blen;
    int Strlen;
} structs;

int **init2dArray(int a, int b);

/**
 * @brief Use this function in order to generate a struct that contains two two dimensional arrays with metadata information
 *
 * @param src       Struct that is created
 * @param alen      Number of columns for array A
 * @param blen      Number of columns for array B
 * @param strlen    Length for each word
 */
void structsGenerate(structs *src, int alen, int blen, int strlen);

/**
 * @brief De-allocate memory of custom Struct that contains data
 *
 * @param src
 */
void deallsrc(structs *src);

/**
 * @brief Just for debugging purpose print Serial calculated Hamming Values
 *
 * @param alen Number of rows of serV array
 * @param blen Number of columns of serV array
 * @param serV Array that holds Hamming Values
 */
void displayHammingValues(int alen, int blen, int **serV);

void printResults(hammingTimes *hammT);

#endif //PARALLEL_COSTUM_STRUCTS_H
