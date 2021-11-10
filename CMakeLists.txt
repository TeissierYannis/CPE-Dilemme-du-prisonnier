cmake_minimum_required(VERSION 3.20)
project(client C)

set(CMAKE_C_STANDARD 99)

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
add_executable(${CMAKE_PROJECT_NAME} main.c headers/client.h src/client.c headers/gui.h src/gui.c headers/lien.h src/lien.c headers/board.h src/board.c src/configs/configurator.c headers/configs/configurator.h headers/utils/files_utils.h headers/utils/string_utils.h src/utils/files_utils.c src/utils/string_utils.c headers/affichage.h src/affichage.c headers/connexion.h src/connexion.c headers/communication.h src/communication.c headers/structures.h headers/outils.h src/outils.c)

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTK3_LIBRARIES})
