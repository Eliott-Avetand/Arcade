cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    arcade_pacman
    DESCRIPTION "Arcade game : pacman"
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../lib/)

set(ROOT_FOLDER "${PROJECT_SOURCE_DIR}/../../../")

set(
    SOURCES
    "${PROJECT_SOURCE_DIR}/src/GamePacman.cpp"
    "${PROJECT_SOURCE_DIR}/src/Entities/GenericEntity.cpp"
    "${PROJECT_SOURCE_DIR}/src/Entities/Player.cpp"
    "${PROJECT_SOURCE_DIR}/src/Entities/Enemy.cpp"
    "${ROOT_FOLDER}/src/Errors/Errors.cpp"
)

set(
    HEADERS_FOLDERS
    "${ROOT_FOLDER}/include"
    "${ROOT_FOLDER}/include/Utils"
    "${ROOT_FOLDER}/include/Interface"
    "${ROOT_FOLDER}/include/Interface/Entity"
    "${PROJECT_SOURCE_DIR}/include/"
    "${PROJECT_SOURCE_DIR}/include/Entities/"
    "${PROJECT_SOURCE_DIR}/include/MapElement/"
)

add_library(arcade_pacman SHARED ${SOURCES})

set_target_properties(arcade_pacman PROPERTIES PREFIX "")

target_include_directories(
    arcade_pacman PRIVATE ${HEADERS_FOLDERS}
)