cmake_minimum_required(VERSION 3.20)
project(server C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

if (Threads_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
endif(Threads_FOUND)

add_executable(${CMAKE_PROJECT_NAME} main.c src/configs/read_rules.c headers/configs/read_rules.h src/communication/communication.c headers/communication/communication.h src/configs/configurator.c headers/configs/configurator.h headers/utils/string_utils.h src/utils/string_utils.c src/communication/commands.c headers/communication/commands.h headers/game/core.h src/game/core.c headers/utils/files_utils.h src/utils/files_utils.c headers/results/writefile.h src/results/writefile.c src/connectivity/server.c headers/connectivity/server.h)