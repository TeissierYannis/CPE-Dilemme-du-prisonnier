#!/bin/sh

mkdir build
cd build
cmake ..
make all
clear
./server