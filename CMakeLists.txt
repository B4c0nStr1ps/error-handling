cmake_minimum_required(VERSION 3.12)
project(error-handling VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create the target.
add_executable(error-handling main.cpp match.h overload.h result.h types.h)