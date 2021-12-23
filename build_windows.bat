# Build script for the Unix version of the application
echo -e "Building the Windows version of the application...\n"
md output
echo -e "Preparing the build environment for the client...\n"
cd client || exit
md build
cd build || exit
echo -e "Building the client...\n"
cmake ..
make all
cd ../..
cp client/build/client output/client
echo -e "Build of the client finished.\n"


echo -e "Preparing the build environment for the server...\n"
cd server || exit
md build
cd build || exit
echo -e "Building the client...\n"
cmake ..
make all
cd ../..
cp server/build/server output/server
echo -e "Build of the server finished.\n"

echo -e "Building the application finished.\n"
echo -e "Preparing configuration files...\n"
md output/client_config
md output/server_config
cp client/config/config.json output/client_config/config.json
cp server/config/rules_config.json output/server_config/rules_config.json
cp server/config/server_config.json output/server_config/server_config.json
echo -e "Configuration files prepared.\n"

echo -e "Application build finished.\n"

