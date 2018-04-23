#!/bin/sh

make

./serialR $1
./sseR $1

make clean
