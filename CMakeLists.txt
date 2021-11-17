cmake_minimum_required(VERSION 3.20)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(${CMAKE_PROJECT_NAME} main.c headers/srvcxnmanager.h src/srvcxnmanager.c src/communication/communication_translater.c headers/communication/communication_translater.h src/configs/configurator.c headers/configs/configurator.h headers/utils/string_utils.h src/utils/string_utils.c src/communication/commands.c headers/communication/commands.h headers/game/core.h src/game/core.c)