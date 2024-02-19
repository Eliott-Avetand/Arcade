cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    arcade_sfml
    DESCRIPTION "Arcade graphics : sfml"
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../lib/)

set(ROOT_FOLDER "${PROJECT_SOURCE_DIR}/../../../")

set(
    SOURCES
    "${PROJECT_SOURCE_DIR}/src/LibSFML.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibSFMLMenu.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibSFMLGame.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibSFMLErrors.cpp"
)

set(
    HEADERS_FOLDERS
    "${PROJECT_SOURCE_DIR}/include/"
    "${ROOT_FOLDER}/include"
    "${ROOT_FOLDER}/include/Interface"
    "${ROOT_FOLDER}/include/Interface/Entity"
    "${ROOT_FOLDER}/include/Utils"
)

add_library(arcade_sfml SHARED ${SOURCES})

set_target_properties(arcade_sfml PROPERTIES PREFIX "")

target_include_directories(
    arcade_sfml PRIVATE ${HEADERS_FOLDERS}
)