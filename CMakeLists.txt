cmake_minimum_required(VERSION 3.20)
project(server C)

set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)

if (Threads_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
endif(Threads_FOUND)

add_executable(${CMAKE_PROJECT_NAME} main.c src/configs/read_rules.c headers/configs/read_rules.h src/configs/configurator.c headers/configs/configurator.h headers/utils/string_utils.h src/utils/string_utils.c headers/game/core.h src/game/core.c headers/utils/files_utils.h src/utils/files_utils.c headers/results/writefile.h src/results/writefile.c src/connectivity/server.c headers/connectivity/server.h headers/game/rules.h src/game/rules.c)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started.")

    add_custom_target( doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate doxygen documentation")
endif (DOXYGEN_FOUND)