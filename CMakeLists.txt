# cmake_minimum_required(VERSION <specify CMake version here>)
project(Workshop_2019)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-8.3.0") #/usr/local/bin/g++-8.3.0
set(CMAKE_C_COMPILER "/usr/local/bin/gcc-8.3.0")  #/usr/local/bin/gcc-8.3.0
include_directories(Library)


add_library(Workshop_2019
        Library/Attacker.cpp
        Library/Attacker.h
        Library/FRAttacker.cpp
        Library/FRAttacker.h
        Library/Measurements.cpp
        Library/Measurements.h
        Library/MemoryAccess.h
        Library/Victim.cpp
        Library/Victim.h)

add_executable(FRtester testing/FRtester/main.cpp)
target_link_libraries(FRtester Workshop_2019 -static)