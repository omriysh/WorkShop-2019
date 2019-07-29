cmake_minimum_required(VERSION 2.8)
project(Workshop CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONs OFF)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")
add_library(Workshop
         Victim.cpp Victim.h Attacker.cpp Attacker.h Measurements.cpp Measurements.h MemoryAccess.h FRAttacker.h FRAttacker.cpp)

add_executable(AttackerTest1 ../AttackerTest1/main.cpp)
target_link_libraries(AttackerTest1 Workshop)