#!/bin/sh

mkdir build
cd build || exit
cmake ..
make all
mkdir -p server_config
cp ../server_config/* server_config/
cd .. || exit
./build/server
