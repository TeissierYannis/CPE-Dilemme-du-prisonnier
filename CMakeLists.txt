cmake_minimum_required(VERSION 3.20)
project(client C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

find_package(Threads REQUIRED)

if (Threads_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
endif(Threads_FOUND)

MESSAGE(STATUS "GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
MESSAGE(STATUS "GTK3_LIBRARY_DIRS: ${GTK3_LIBRARY_DIRS}")

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
add_definitions(${GTK3_CFLAGS_OTHER})
add_executable(${CMAKE_PROJECT_NAME} main.c headers/client.h src/client.c headers/gui.h src/gui.c headers/lien.h src/lien.c)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTK3_LIBRARIES})
