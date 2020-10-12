# ω Statistic 
Improve execution time of ω statistic calculation using SSE and MPI.


## Documentation
If you want more information about the implementation, you could read - or at least try, unfortunately, is in greek language - this [report file](./doc/Report.pdf) or by reading the inline documentation.

## Dependencies:
* Mpich (for Debian-Based systems, install it by executing: sudo apt install mpich)

## Usage

### For compiling and executing code in a LINUX-based system, run the commands below:
#### MODE A
```
$ chmod +x run.sh # (If it is necessary)
$ sh run.sh N P
```
Where N = Number of DNA elements, N>=1 & P = Processes number, P=2,4,8 <br>
e.g:  $ sh run.sh 100 2

--

#### MODE B (Run all test cases N=100,1000,10000,100000 and P=2,4,8)
```
$ chmod +x run.sh (If it is necessary)
$ sh run.sh
```

### Clean generated files in a LINUX-based system:
```
make clean
```
