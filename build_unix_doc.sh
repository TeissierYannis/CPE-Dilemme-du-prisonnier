#!/bin/sh

rm -rf documentation
# Build script for the Unix version of the application
printf "Building the documentation...\n"
printf "Preparing environment for the client...\n"
cd client || exit
mkdir build
cd build || exit
printf "Building documentation for the client...\n"
cmake ..
make doc
cd ../..
printf "Build of the client documentation finished.\n"

printf "Preparing environment for the server...\n"
cd server || exit
mkdir build
cd build || exit
printf "Building the client documentation...\n"
cmake ..
make doc
cd ../..
printf "Build of the server documentation finished.\n"

mkdir documentation
printf "Copying the client documentation...\n"
mkdir documentation/client
cp -r client/doc/html documentation/client
printf "Copying the server documentation...\n"
mkdir documentation/server
cp -r server/doc/html documentation/server
printf "Building the application documentation finished.\n"

