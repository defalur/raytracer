cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer src/main.cpp src/color.h src/vector3.cpp src/vector3.h src/vector4.cpp src/vector4.h src/image.cpp src/image.h)