#!/bin/sh

if [ $# != 2 ] ; then
    echo "Wrong number of arguments"
    echo "E.g. $ sh run.sh 100 2"
    exit 1
fi

if ! which mpiexec >/dev/null ; then
    echo "" ; echo "MPICH is not installed"
    echo "If you are in a Debian-Based system install it by executing: sudo apt-get install mpich"
    exit 2
fi

make

./serialR $1
./sseR $1
mpiexec -n $2 ./mpiR $1

echo ; make clean

