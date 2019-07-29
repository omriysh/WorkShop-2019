cmake_minimum_required(VERSION 2.8)
project(Workshop CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONs OFF)
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-8.3.0")
set(CMAKE_C_COMPILER "/usr/local/bin/gcc-8.3.0")
add_library(Workshop
         Victim.cpp Victim.h Attacker.cpp Attacker.h Measurements.cpp Measurements.h MemoryAccess.h)

# add_executable(execfile execfile.cpp
# target_link_libraries(execffile Workshop)