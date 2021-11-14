cmake_minimum_required(VERSION 3.20)
project(client C)

set(CMAKE_C_STANDARD 99)

add_executable(${CMAKE_PROJECT_NAME} main.c src/read_rules.c headers/read_rules.h src/string_utils.c headers/string_utils.h)