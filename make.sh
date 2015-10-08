#!/bin/bash
clang++ main.cpp
echo "Please enter the path to the data file."
read file_path
echo "Output order is: quickSortLast, quickSortFirst, quickSortMiddle, quickSortRandom, heapSort."
./a.out $file_path quickSortLast
./a.out $file_path quickSortFirst
./a.out $file_path quickSortMiddle
./a.out $file_path quickSortRandom
./a.out $file_path heapSort
