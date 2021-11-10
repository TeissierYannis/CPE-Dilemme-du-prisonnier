#!/bin/sh

mkdir build
cd build
cmake ..
make all
./gtk_test