#!/bin/sh
red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
reset=`tput sgr0`

if ! which mpiexec >/dev/null ; then
    echo "${red}MPICH is not installed ${reset}"
    echo "If you are in a Debian-Based system install it by executing: ${yellow} sudo apt-get install mpich ${reset}"
    exit 1
fi

if [ $# -eq 0 ] ; then
	echo "${yellow}Building project...${reset}"
	make

	# Run for N=100 AND P=2,4,8
	echo ; echo "${green}********** N=100 **********${reset}"
	./serialR 100
	./sseR 100
	mpiexec -n 2 ./mpiR 100
	mpiexec -n 4 ./mpiR 100
	mpiexec -n 8 ./mpiR 100

	# Run for N=1000 AND P=2,4,8
	echo ; echo "${green}********** N=1000 **********${reset}"
	./serialR 1000
	./sseR 1000
	mpiexec -n 2 ./mpiR 1000
	mpiexec -n 4 ./mpiR 1000
	mpiexec -n 8 ./mpiR 1000

	# Run for N=10000 AND P=2,4,8
	echo ; echo "${green}********** N=10000 **********${reset}"
	./serialR 10000
	./sseR 10000
	mpiexec -n 2 ./mpiR 10000
	mpiexec -n 4 ./mpiR 10000
	mpiexec -n 8 ./mpiR 10000

	# Run for N=100000 AND P=2,4,8
	echo ; echo "${green}********** N=100000 **********${reset}"
	./serialR 100000
	./sseR 100000
	mpiexec -n 2 ./mpiR 100000
	mpiexec -n 4 ./mpiR 100000
	mpiexec -n 8 ./mpiR 100000

	echo ; echo "${yellow}Cleaning project...${reset}"; make clean
	exit 0
fi

if [ $# != 2 ] ; then
    echo "${red}Wrong number of arguments${reset}"
    echo "1) If you want to run all cases execute run.sh script without arguments"
    echo "2) Or execute run.sh {Number of DNA elements} {Processes}"
    echo "E.g. ${green} $ ${reset} sh run.sh 100 2"
    exit 2
fi

make

./serialR $1
./sseR $1
mpiexec -n $2 ./mpiR $1

echo ; make clean

