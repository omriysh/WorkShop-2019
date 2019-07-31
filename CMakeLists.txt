# cmake_minimum_required(VERSION <specify CMake version here>)
project(Workshop_2019)

set(CMAKE_CXX_STANDARD 14)

include_directories(Library)

add_executable(Workshop_2019
        Library/Attacker.cpp
        Library/Attacker.h
        Library/FRAttacker.cpp
        Library/FRAttacker.h
        Library/Measurements.cpp
        Library/Measurements.h
        Library/MemoryAccess.h
        Library/PPAttacker.cpp
        Library/PPAttacker.h
        Library/Victim.cpp
        Library/Victim.h
        testing/test1.c
        testing/test2attacker.c
        testing/test2victim.c testing/FRtester.cpp)
