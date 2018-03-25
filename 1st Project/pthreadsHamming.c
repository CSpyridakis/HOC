#include "pthreadsHamming.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <assert.h>

pthread_mutex_t lock;
int NUM_THREADS;

//Global Variables, Shared between Threads
unsigned long long sum_GLOBAL;
int **hammingValues_GLOBAL;
structs *src_GLOBAL;

//TODO : SUM WORKING , MUTEX LOCK PROBLEM
void *taskA(void *tid) {
    int i,j,k,t;
    unsigned long long psum=0;
    int id=*((int *)tid);

    for(t=0;t<NUM_THREADS;t++){
        int start=(t+id)%NUM_THREADS;
        /// Pseudo - random Access
        for(i=start;i<src_GLOBAL->Alen;i=i+NUM_THREADS){
            for (j = 0; j < src_GLOBAL->Blen; j++) {
                /// Parallel loop
                for (k = id; k < src_GLOBAL->Strlen; k=k+NUM_THREADS) {
                    if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                        psum++;

                        // Mutex lock for data races
 //                       pthread_mutex_lock(&lock);
 //                       hammingValues_GLOBAL[i][j]++;
 //                       pthread_mutex_unlock(&lock);
                    }
                }
            }
        }
    }

    // Mutex lock for data races
    pthread_mutex_lock(&lock);
    sum_GLOBAL+=psum;
    pthread_mutex_unlock(&lock);
}

void *taskB(void *tid) {
    int i,j,k,psum=0;
    int id=*((int *)tid);

    int index;
    for(index=id;index<src_GLOBAL->Alen*src_GLOBAL->Blen;index=index+NUM_THREADS){
        i=index/src_GLOBAL->Alen;
        j=index%src_GLOBAL->Alen;
        for(k=0;k<src_GLOBAL->Strlen;k++){
            if (src_GLOBAL->A[i][k] != src_GLOBAL->B[j][k]) {
                hammingValues_GLOBAL[i][j]++;
                psum++;
            }
        }
    }

    pthread_mutex_lock(&lock);
    sum_GLOBAL+=psum;
    pthread_mutex_unlock(&lock);
}

void *taskC(void *tid) {
    int i,j,k,psum=0;
    int id=*((int *)tid);

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



void structcpy(structs *src){
    int i,j;

    src_GLOBAL->Alen=src->Alen;
    src_GLOBAL->Blen=src->Blen;
    src_GLOBAL->Strlen=src->Strlen;

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

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n"ANSI_RED"MUTEX INIT FAILED"ANSI_RESET"\n");
        return -1;
    }

    src_GLOBAL= (structs *) malloc(sizeof(structs));
    structcpy(src);

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
    deallsrc(src_GLOBAL);
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