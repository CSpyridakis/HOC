#include "pthreadsHamming.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <assert.h>

pthread_mutex_t lock;
int NUM_THREADS;

unsigned long long sum_GLOBAL;
int **hammingValues_GLOBAL;
structs *src_GLOBAL;

//TODO :Mutex needed
void *taskA(void * src_v) {
    structs * src =(structs*) src_v;
    int i,j,k,psum=0;
}

void *taskB(void * src_v) {
    structs * src =(structs*) src_v;
    int i,j,k,psum=0;
}

void *taskC(void *tid) {
    int i,j,k,psum=0;
    int id=*((int *)tid);

//    printf("\nThread id:%d out of %d Threads",id,NUM_THREADS);
   for (i = 0; i < src_GLOBAL->Alen; i++) {
        for (k = 0; k < src_GLOBAL->Strlen; k++) {
            for (j = id; j < src_GLOBAL->Blen; j=j+NUM_THREADS) {
                if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                    hammingValues_GLOBAL[i][j]++;
                    psum++;
                }
            }
        }
    }

    pthread_mutex_lock(&lock);
    sum_GLOBAL+=psum;
    pthread_mutex_unlock(&lock);
}

double pthreadsHamm_task(structs *src, unsigned long long serialHammingSum, type task) {

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n"ANSI_RED"MUTEX INIT FAILED"ANSI_RESET"\n");
        return -1;
    }

    src_GLOBAL= (structs *) malloc(sizeof(structs));
    structsGenerate(src_GLOBAL, src->Alen, src->Blen, src->Strlen);//TODO :REMOVE AFTER TEST

    NUM_THREADS = get_nprocs();
    pthread_t threads[NUM_THREADS];
    int tid[NUM_THREADS];
    int ptd, i;

    unsigned long long sum = 0;
    sum_GLOBAL=0;
    hammingValues_GLOBAL = init2dArray(src->Alen, src->Blen);

    if (task == TASK_A) { printf("PThreads task A..."); }
    else if (task == TASK_B) { printf("PThreads task B..."); }
    else { printf("PThreads task C..."); }

    double begin;
    {
        if (task == TASK_A) {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i]=i;
                ptd = pthread_create(&threads[i], NULL, taskA, (void *) &tid[i]);
                assert(!ptd);
            }
        } else if (task == TASK_B) {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i]=i;
                ptd = pthread_create(&threads[i], NULL, taskB, (void *) &tid[i]);
                assert(!ptd);
            }
        } else {
            begin = gettime();
            // Create threads
            for (i = 0; i < NUM_THREADS; i++) {
                tid[i]=i;
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
    sum=sum_GLOBAL;
    // Validate Hamming Distance
    if (serialHammingSum != sum) {
        printf(ANSI_RED "Error!"ANSI_RESET"\n");
        return (double) (-1);
    }

    printf(ANSI_GREEN"finished"ANSI_RESET"\t ");
    printf("Hamming time:%f sec ", calcTime);
    printf("| Sum Value:%lld", calcSumOfArray(src->Alen, src->Blen, hammingValues_GLOBAL));//TODO REMOVE ONLY FOR DEBUGGING DATA RACE
    printf("\n");
    return calcTime;
}