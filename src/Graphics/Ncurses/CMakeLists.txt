cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    arcade_ncurses
    DESCRIPTION "Arcade graphics : ncurses"
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lncurses")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../lib/)

set(ROOT_FOLDER "${PROJECT_SOURCE_DIR}/../../../")

set(
    SOURCES
    "${PROJECT_SOURCE_DIR}/src/LibNcurses.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibNcursesMenu.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibNcursesGames.cpp"
    "${PROJECT_SOURCE_DIR}/src/Ncurses.cpp"
)

set(
    HEADERS_FOLDERS
    "${PROJECT_SOURCE_DIR}/include/"
    "${ROOT_FOLDER}/include"
    "${ROOT_FOLDER}/include/Interface"
    "${ROOT_FOLDER}/include/Interface/Entity"
    "${ROOT_FOLDER}/include/Utils"
)

add_library(arcade_ncurses SHARED ${SOURCES})

set_target_properties(arcade_ncurses PROPERTIES PREFIX "")

target_include_directories(
    arcade_ncurses PRIVATE ${HEADERS_FOLDERS}
)