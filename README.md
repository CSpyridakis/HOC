# HOC ![MIT license](https://img.shields.io/github/license/CSpyridakis/HOC.svg?style=plastic) ![Size](https://img.shields.io/github/repo-size/CSpyridakis/HOC.svg?style=plastic)

This repository contains two separate projects, both of them are about an educational introduction in Parallel and Distributed Computer Architecture. 

## Projects
* [Hamming Distance](./Hamming-Distance) 
In this project, a serial NON-optimized calculation of Hamming distance between two random generated arrays of equal length is calculated. Then using pthreads and OpenMp API try to speed up the calculation time of the this operation. The same process is repeated for different array lengths, word lengths, threads number and some useful results are exported during this procedure.


* [ω Statistic](./Omega-Statistic)
Along the same lines, there is the implementations of the serial, NON-optimized and simplified ω statistic calculation among a population sample of DNA sequence. Then, the same calculation is repeated using Streaming SIMD Extensions (SSE) and Message Passing Interface (MPI). 




