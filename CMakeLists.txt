cmake_minimum_required(VERSION 3.17)
project(TasWolf3D)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES . src/*.cpp)
add_executable(TasWolf3D ${SOURCES})