#include "pthreadsHamming.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <assert.h>


void *taskA() {

}

void *taskB() {

}

void *taskC() {

}

double pthreadsHamm_task(structs *src, unsigned long long serialHammingSum, type task) {

    long sum = 0;
    int **hammingValues = init2dArray(src->Alen, src->Blen);
    int NUM_THREADS = get_nprocs();
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int ptd, i;

    if (task == TASK_A) { printf("PThreads task A..."); }
    else if (task == TASK_B) { printf("PThreads task B..."); }
    else { printf("PThreads task C..."); }

    double begin;
    if (task == TASK_A) {
        begin = gettime();
        // Create threads
        for (i = 0; i < NUM_THREADS; i++) {
            thread_args[i] = i;
            ptd = pthread_create(&threads[i], NULL, taskA, (void *) &thread_args[i]);
            assert(!ptd);
        }
    } else if (task == TASK_B) {
        begin = gettime();
        // Create threads
        for (i = 0; i < NUM_THREADS; i++) {
            thread_args[i] = i;
            ptd = pthread_create(&threads[i], NULL, taskB, (void *) &thread_args[i]);
            assert(!ptd);
        }
    } else {
        begin = gettime();
        // Create threads
        for (i = 0; i < NUM_THREADS; i++) {
            thread_args[i] = i;
            ptd = pthread_create(&threads[i], NULL, taskC, (void *) &thread_args[i]);
            assert(!ptd);
        }
    }

    // Wait each thread to finish
    for (i = 0; i < NUM_THREADS; i++) {
        ptd = pthread_join(threads[i], NULL);
        assert(!ptd);
    }

    double end = gettime();
    double calcTime = end - begin;

    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues));//TODO REMOVE ONLY FOR DEBUGGING DATA RACE
    printf("\n");
    return calcTime;
}