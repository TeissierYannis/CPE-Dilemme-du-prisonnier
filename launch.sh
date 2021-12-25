#!/bin/sh
mkdir build
cd build
cmake ..
make all
mkdir -p client_config
cp -r ../client_config/* client_config
cd .. || exit
./build/client