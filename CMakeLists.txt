cmake_minimum_required(VERSION 3.13)

project(Velo LANGUAGES CXX)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(console)
add_subdirectory(generic)
add_subdirectory(geometry)
add_subdirectory(network)
add_subdirectory(system)
add_subdirectory(utility)

