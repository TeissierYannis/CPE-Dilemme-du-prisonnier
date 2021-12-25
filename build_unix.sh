#!/bin/sh

rm -rf output

# Build script for the Unix version of the application
printf "Building the Unix version of the application...\n"
mkdir output
printf "Preparing the build environment for the client...\n"
cd client || exit
mkdir build
cd build || exit
printf "Building the client...\n"
cmake ..
make all
cd ../..
cp client/build/client output/client
printf "Build of the client finished.\n"


printf "Preparing the build environment for the server...\n"
cd server || exit
mkdir build
cd build || exit
printf "Building the client...\n"
cmake ..
make all
cd ../..
cp server/build/server output/server
printf "Build of the server finished.\n"

printf "Building the application finished.\n"
printf "Preparing configuration files...\n"
mkdir output/client_config
mkdir output/server_config
mkdir output/client_config/images
mkdir output/results

cp client/images/* output/client_config/images/
cp client/glade/glade.glade output/client_config/glade.glade
cp client/client_config/config.json output/client_config/config.json
cp server/server_config/rules_config.json output/server_config/rules_config.json
cp server/server_config/server_config.json output/server_config/server_config.json
printf "Configuration files prepared.\n"

printf "Application build finished.\n"

