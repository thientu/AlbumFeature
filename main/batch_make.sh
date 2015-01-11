#!/bin/bash

rm test
rm log.txt
make clean
make

export LD_LIBRARY_PATH=../lib
valgrind --tool=memcheck --leak-check=full ./test ../data/models/  2>&1 | tee log.txt

