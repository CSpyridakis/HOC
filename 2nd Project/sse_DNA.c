#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <xmmintrin.h>

double gettime(void) {
    struct timeval ttime;
    gettimeofday(&ttime, NULL);
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

float randpval() {
    int vr = rand();
    int vm = rand() % vr;
    float r = ((float) vm) / (float) vr;
    assert(r >= 0.0 && r <= 1.00001);
    return r;
}

int main(int argc, char **argv) {

    if (argc !=2 ){
        printf("\nERROR... Input example:\n$ ./sseR 1000\n");
        return -1;
    }

    //Needed Variables to make things easy
    int N = atoi(argv[1]);
    int alignb=16;
    int iters = 1000;

    srand(1);

    /*
     * Allocate variables memory
     * malloc changed to _mm_malloc (aligned allocation, better performance without errors)
    */
    float *mVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(mVec != NULL);
    float *nVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(nVec != NULL);
    float *LVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(LVec != NULL);
    float *RVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(RVec != NULL);
    float *CVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(CVec != NULL);
    float *FVec = (float *) _mm_malloc(sizeof(float) * N,alignb);
    assert(FVec != NULL);

    /*
     * Init variables
     */
    for (int i = 0; i < N; i++) {
        mVec[i] = (float) (2 + rand() % 10);
        nVec[i] = (float) (2 + rand() % 10);
        LVec[i] = 0.0;
        for (int j = 0; j < mVec[i]; j++) {
            LVec[i] += randpval();
        }
        RVec[i] = 0.0;
        for (int j = 0; j < nVec[i]; j++) {
            RVec[i] += randpval();
        }
        CVec[i] = 0.0;
        for (int j = 0; j < mVec[i] * nVec[i]; j++) {
            CVec[i] += randpval();
        }
        FVec[i] = 0.0;

        assert(mVec[i] >= 2.0 && mVec[i] <= 12.0);
        assert(nVec[i] >= 2.0 && nVec[i] <= 12.0);
        assert(LVec[i] > 0.0 && LVec[i] <= 1.0 * mVec[i]);
        assert(RVec[i] > 0.0 && RVec[i] <= 1.0 * nVec[i]);
        assert(CVec[i] > 0.0 && CVec[i] <= 1.0 * mVec[i] * nVec[i]);
    }
    float maxF = 0.0f;
    double timeTotal = 0.0f;
    //Float number vectors needed for calculations
    __m128 _1 = _mm_set_ps1(1.0f), _2 = _mm_set_ps1(2.0f), _001 = _mm_set_ps1(0.01f);

    // "Copy" arrays to vectors
    __m128 * _mVec = (__m128 *)mVec;
    __m128 * _nVec = (__m128 *)nVec;
    __m128 * _LVec = (__m128 *)LVec;
    __m128 * _RVec = (__m128 *)RVec;
    __m128 * _CVec = (__m128 *)CVec;
    __m128 * _FVec = (__m128 *)FVec;

    //TODO : SSE
    __m128 _num_0,_num_1,_num_2,_num,_den_0,_den_1,_den;
    for (int j = 0; j < iters; j++) {

        double time0 = gettime();
        for (int i = 0; i < N; i++) {
            _num_0 = _mm_add_ps(_LVec[i],_RVec[i]);        //float num_0 = LVec[i] + RVec[i];
            //_num_1 =        //float num_1 = mVec[i] * (mVec[i] - 1.0) / 2.0;
            //_num_2 =        //float num_2 = nVec[i] * (nVec[i] - 1.0) / 2.0;
            //_num   =        //float num = num_0 / (num_1 + num_2);

                    //float den_0 = CVec[i] - LVec[i] - RVec[i];
                    //float den_1 = mVec[i] * nVec[i];
                    //float den = den_0 / den_1;

                    //FVec[i] = num / (den + 0.01);

                    //maxF = FVec[i] > maxF ? FVec[i] : maxF;
        }

        //TODO: tail data
//        for (int i = 0; i < N; i++) {
//            float num_0 = LVec[i] + RVec[i];
//            float num_1 = mVec[i] * (mVec[i] - 1.0) / 2.0;
//            float num_2 = nVec[i] * (nVec[i] - 1.0) / 2.0;
//            float num = num_0 / (num_1 + num_2);
//
//            float den_0 = CVec[i] - LVec[i] - RVec[i];
//            float den_1 = mVec[i] * nVec[i];
//            float den = den_0 / den_1;
//
//            FVec[i] = num / (den + 0.01);
//
//            maxF = FVec[i] > maxF ? FVec[i] : maxF;
//        }

        double time1 = gettime();
        timeTotal += time1 - time0;
    }

    /*
     * De-alloc and prints
     */
    printf("\nSSE\n");
    printf("Time %f Max %f\n", timeTotal / iters, maxF);
    _mm_free(mVec);
    _mm_free(nVec);
    _mm_free(LVec);
    _mm_free(RVec);
    _mm_free(CVec);
    _mm_free(FVec);
}