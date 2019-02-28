#include "../include/pthreadsHamming.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <assert.h>

//Pthreads variables
pthread_mutex_t lock;
pthread_mutex_t *hammIlock;
int NUM_THREADS;

//Global Variables, Shared between Threads
unsigned long long sum_GLOBAL;
int **hammingValues_GLOBAL;
structs *src_GLOBAL;

void *taskA(void *tid) {
    int i, j, k, t;
    unsigned long long psum = 0;
    int id = *((int *) tid);
    int isum;

    for (t = 0; t < NUM_THREADS; t++) {
        int start = (t + id) % NUM_THREADS;
        /// Pseudo - random Access
        for (i = start; i < src_GLOBAL->Alen; i = i + NUM_THREADS) {
            for (j = 0; j < src_GLOBAL->Blen; j++) {
                /// Parallel section
                isum = 0;
                for (k = id; k < src_GLOBAL->Strlen; k = k + NUM_THREADS) {
                    if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                        psum++;
                        isum++;
                    }
                }
                // Mutex lock for data races
                pthread_mutex_lock(&hammIlock[i]);
                hammingValues_GLOBAL[i][j] += isum;
                pthread_mutex_unlock(&hammIlock[i]);
            }
        }
    }

    // Mutex lock for data races
    pthread_mutex_lock(&lock);
    sum_GLOBAL += psum;
    pthread_mutex_unlock(&lock);
}

void *taskB(void *tid) {

    int i, j, k;
    unsigned long long psum = 0;
    int id = *((int *) tid);

    /// Parallel section
    int index;
    for (index = id; index < src_GLOBAL->Alen * src_GLOBAL->Blen; index = index + NUM_THREADS) {

        //Calculate i and j
        if (src_GLOBAL->Alen == 1) {
            i = 0;
            j = index;
        } else if (src_GLOBAL->Blen == 1) {
            j = 0;
            i = index;
        } else {
            i = index % src_GLOBAL->Alen;
            j = index / src_GLOBAL->Alen;
        }

        for (k = 0; k < src_GLOBAL->Strlen; k++) {
            if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                hammingValues_GLOBAL[i][j]++;
                psum++;
            }
        }
    }

    pthread_mutex_lock(&lock);
    sum_GLOBAL += psum;
    pthread_mutex_unlock(&lock);
}

void *taskC(void *tid) {
    int i, j, k;
    unsigned long long psum = 0;
    int id = *((int *) tid);

    for (i = 0; i < src_GLOBAL->Alen; i++) {
        for (k = 0; k < src_GLOBAL->Strlen; k++) {
            /// Parallel section
            for (j = id; j < src_GLOBAL->Blen; j = j + NUM_THREADS) {
                if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                    hammingValues_GLOBAL[i][j]++;
                    psum++;
                }
            }
        }
    }

    pthread_mutex_lock(&lock);
    sum_GLOBAL += psum;
    pthread_mutex_unlock(&lock);
}

/**
 * @brief Copy attribute src into a global src
 *
 * @param src
 */
void structcpy(structs *src) {
    int i, j;

    src_GLOBAL->Alen = src->Alen;
    src_GLOBAL->Blen = src->Blen;
    src_GLOBAL->Strlen = src->Strlen;

    src_GLOBAL->A = (char **) malloc(sizeof(char *) * src_GLOBAL->Alen);
    for (i = 0; i < src_GLOBAL->Alen; i++) {
        src_GLOBAL->A[i] = (char *) malloc(sizeof(char) * src_GLOBAL->Strlen);
        for (j = 0; j < src_GLOBAL->Strlen; j++) {
            src_GLOBAL->A[i][j] = src->A[i][j];
        }
    }
    src_GLOBAL->B = (char **) malloc(sizeof(char *) * src_GLOBAL->Blen);
    for (i = 0; i < src_GLOBAL->Blen; i++) {
        src_GLOBAL->B[i] = (char *) malloc(sizeof(char) * src_GLOBAL->Strlen);
        for (j = 0; j < src_GLOBAL->Strlen; j++) {
            src_GLOBAL->B[i][j] = src->B[i][j];
        }
    }

}

double pthreadsHamm_task(structs *src, unsigned long long serialHammingSum, type task) {

    int i;

    if (task == TASK_A) { printf("PThreads task A..."); }
    else if (task == TASK_B) { printf("PThreads task B..."); }
    else { printf("PThreads task C..."); }

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf(ANSI_RED"MUTEX INIT FAILED"ANSI_RESET"\n");
        return -1;
    }

    hammIlock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * src->Alen);
    for (i = 0; i < src->Alen; i++) {
        if (pthread_mutex_init(&hammIlock[i], NULL) != 0) {
            printf(ANSI_RED"MUTEX INIT FAILED"ANSI_RESET"\n");
            return -1;
        }
    }

    //Copy local src
    src_GLOBAL = (structs *) malloc(sizeof(structs));
    structcpy(src);

    //Thread needed variables
    if(THREADS==BEST){
        NUM_THREADS = get_nprocs();
    }
    else{
        NUM_THREADS= THREADS;
    }
    pthread_t threads[NUM_THREADS];
    int tid[NUM_THREADS];
    int ptd;

    //Initialize variables
    unsigned long long sum = 0;
    sum_GLOBAL = 0;
    hammingValues_GLOBAL = init2dArray(src->Alen, src->Blen);

    double begin;
    {
        if (task == TASK_A) {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i] = i;
                ptd = pthread_create(&threads[i], NULL, taskA, (void *) &tid[i]);
                assert(!ptd);
            }
        } else if (task == TASK_B) {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i] = i;
                ptd = pthread_create(&threads[i], NULL, taskB, (void *) &tid[i]);
                assert(!ptd);
            }
        } else {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i] = i;
                ptd = pthread_create(&threads[i], NULL, taskC, (void *) &tid[i]);
                assert(!ptd);
            }
        }

        // Wait each thread to finish
        for (i = 0; i < NUM_THREADS; i++) {
            ptd = pthread_join(threads[i], NULL);
            assert(!ptd);
        }
    }
    double end = gettime();
    double calcTime = end - begin;


    deallsrc(src_GLOBAL);
    sum = sum_GLOBAL;
    pthread_mutex_destroy(&lock);
    for (i = 0; i < src->Alen; i++) {
        pthread_mutex_destroy(&hammIlock[i]);
    }

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    //Print results
    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    if (DEBUG) { printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues_GLOBAL)); }
    printf("\n");

    dealhamm(src_GLOBAL->Alen, src_GLOBAL->Blen, hammingValues_GLOBAL);//If you need hamming table comment out this line
    return calcTime;
}