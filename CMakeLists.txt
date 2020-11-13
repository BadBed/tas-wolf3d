cmake_minimum_required(VERSION 3.16)
project(TasWolf3D)

find_package(OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES . src/*.cpp)
add_executable(TasWolf3D ${SOURCES})
target_link_libraries(TasWolf3D -lglut -lglfw3 -lGL -lGLU)