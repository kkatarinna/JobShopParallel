cmake_minimum_required(VERSION 3.24)
project(Projekat)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekat main.cpp Chromosome.cpp Chromosome.h constants.h ParmeterFns.cpp ParmeterFns.h)
