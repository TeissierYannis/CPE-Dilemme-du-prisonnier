#!/bin/sh
mkdir build
cd build
cmake ..
make all
cd .. || exit
./build/client