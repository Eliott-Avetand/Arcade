cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    Arcade
    VERSION 0.1
    DESCRIPTION "Our own gaming platform"
    LANGUAGES CXX
)

configure_file(
    "${PROJECT_SOURCE_DIR}/config/ArcadeConfig.hpp"
    "${PROJECT_SOURCE_DIR}/config/ArcadeConfig.hpp.in"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ldl -fno-gnu-unique -g")

set(
    SOURCES
    src/main.cpp
    src/Errors/Errors.cpp
    src/Lib/DlLoader.cpp
    src/Core/Core.cpp
    src/Core/LibScanner.cpp
)

set(
    HEADERS
    "${PROJECT_SOURCE_DIR}/include/Utils/PositionVector.hpp"
    "${PROJECT_SOURCE_DIR}/config/ArcadeConfig.hpp"
    "${PROJECT_SOURCE_DIR}/include/Errors.hpp"
    "${PROJECT_SOURCE_DIR}/include/Lib/DlLoader.hpp"
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/Games/Pacman/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Games/Nibbler/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Graphics/SFML/)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Graphics/Ncurses/)

add_executable(arcade ${SOURCES} ${HEADERS})

target_include_directories(
    arcade PRIVATE
    "${PROJECT_SOURCE_DIR}/config"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/Lib"
    "${PROJECT_SOURCE_DIR}/include/Utils"
    "${PROJECT_SOURCE_DIR}/include/Interface"
    "${PROJECT_SOURCE_DIR}/include/Interface/Entity"
)