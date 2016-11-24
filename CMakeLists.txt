cmake_minimum_required(VERSION 3.3)
project(Classification_GA_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Individual.cpp Individual.h Support.cpp Support.h Population.cpp Population.h)
add_executable(Classification_GA_2 ${SOURCE_FILES})