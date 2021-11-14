cmake_minimum_required(VERSION 3.20)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(${CMAKE_PROJECT_NAME} main.c headers/srvcxnmanager.h src/srvcxnmanager.c src/communication_translater.c headers/communication_translater.h src/configurator.c headers/configurator.h headers/string_utils.h src/string_utils.c src/commands.c headers/commands.h)