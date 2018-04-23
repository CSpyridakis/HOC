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
    int alignb=16;                  //malloc alignment Bits
    int iters = 1000;
    int _4fp=4;                     //4 floating pointer variables
    int _sseL=N-N%4,tail=_sseL;     //Limits for SSE and Tail variables (leftovers)

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
    float * max=(float *) _mm_malloc(sizeof(float) * _4fp,alignb);
    assert(max != NULL);


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


    // SSE Vectors
    __m128 _mVec, _nVec ,_LVec ,_RVec , _CVec ,_FVec;
    __m128 _num_0,_num_1,_num_2,_num,_den_0,_den_1,_den, _tmp, _maxF=_mm_set_ps1(0.0f);
    for (int j = 0; j < 1; j++) {

        double time0 = gettime();
        for (int i = 0; i < _sseL; i+=4) {

            // Load 4 floats from i position to vector
            _mVec=_mm_load_ps(mVec+i);
            _nVec=_mm_load_ps(nVec+i);
            _LVec=_mm_load_ps(LVec+i);
            _RVec=_mm_load_ps(RVec+i);
            _CVec=_mm_load_ps(CVec+i);
            _FVec=_mm_load_ps(FVec+i);

            //Intrinsics
            _num_0   =   _mm_add_ps(_LVec,_RVec);                    //float num_0 = LVec[i] + RVec[i];

            _tmp     =   _mm_sub_ps(_mVec,_1);
            _num_1   =   _mm_div_ps(_mm_mul_ps(_mVec,_tmp),_2);      //float num_1 = mVec[i] * (mVec[i] - 1.0) / 2.0;
            _tmp     =   _mm_sub_ps(_nVec,_1);
            _num_2   =   _mm_div_ps(_mm_mul_ps(_nVec,_tmp),_2);      //float num_2 = nVec[i] * (nVec[i] - 1.0) / 2.0;
            _tmp     =   _mm_add_ps(_num_1,_num_2);
            _num     =   _mm_div_ps(_num_0,_tmp);                    //float num = num_0 / (num_1 + num_2);

            _tmp     =   _mm_sub_ps(_CVec,_LVec);
            _den_0   =   _mm_sub_ps(_tmp,_RVec);                     //float den_0 = CVec[i] - LVec[i] - RVec[i];
            _den_1   =   _mm_mul_ps(_mVec,_nVec);                    //float den_1 = mVec[i] * nVec[i];
            _den     =   _mm_div_ps(_den_0,_den_1);                  //float den = den_0 / den_1;

            _tmp     =  _mm_add_ps(_den,_001);
            _FVec    =  _mm_div_ps(_num,_tmp);                       //FVec[i] = num / (den + 0.01);

            _maxF    =  _mm_max_ps(_FVec,_maxF);                     //maxF = FVec[i] > maxF ? FVec[i] : maxF;

        }

        //Max finder
        _mm_store_ps(max,_maxF);
        for(int i=0;i<_4fp;i++){
            maxF = maxF > max[i] ? maxF : max[i];
        }

        //Tail data
        for (int i = tail; i < N; i++) {
            float num_0 = LVec[i] + RVec[i];
            float num_1 = mVec[i] * (mVec[i] - 1.0) / 2.0;
            float num_2 = nVec[i] * (nVec[i] - 1.0) / 2.0;
            float num = num_0 / (num_1 + num_2);

            float den_0 = CVec[i] - LVec[i] - RVec[i];
            float den_1 = mVec[i] * nVec[i];
            float den = den_0 / den_1;

            FVec[i] = num / (den + 0.01);

            maxF = FVec[i] > maxF ? FVec[i] : maxF;
        }

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
    _mm_free(max);
}