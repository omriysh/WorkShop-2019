cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONs OFF)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "gcc")

project(Workshop CXX)

include(../cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/../cmake
        ${PROJECT_BINARY_DIR}/googletest
)
enable_testing()

add_library(Workshop
        Victim.cpp Victim.h Attacker.cpp Attacker.h Measurements.cpp Measurements.h MemoryAccess.h FRAttacker.h FRAttacker.cpp
        PPAttacker.h PPAttacker.cpp)

add_executable(VictimClassTesting ../GoogleTesting/VictimTest.cpp)
target_link_libraries(VictimClassTesting gtest_main Workshop)

add_executable(MeasurementsClassTesting ../GoogleTesting/MeasurementsTest.cpp)
target_link_libraries(MeasurementsClassTesting gtest_main Workshop)

add_executable(FRAttackerClassTesting ../GoogleTesting/FRAttackerTest.cpp)
target_link_libraries(FRAttackerClassTesting gtest_main Workshop)

#add_test(
#        NAME
#        FindInFile
#        COMMAND
#        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/VictimClassTesting
#)