# ω Statistic 
Improve execution time of ω statistic calculation using SSE and MPI


## Documentation
If you want more information about the implementation of this project you could read (or just try to read, unfortunately at this point is only in greek language) this [report file](./doc/report.pdf)

## Usage

### Compile and execute code in LINUX-based system

#### MODE A
```
$ chmod +x run.sh # (If it is necessary)
$ mkdir bin
$ sh run.sh {N = Number of DNA elements, N>=1}  {P = Processes number, P=2,4,8}
   
```
e.g:  $ sh run.sh 100 2


#### MODE B (Run all test cases N=100,1000,10000,100000 and P=2,4,8)
```
$ chmod +x run.sh (If it is necessary)
$ mkdir bin
$ sh run.sh
```

### Clean generated files in LINUX-based system
```
make clean
```

## Dependencies:

* Mpich



