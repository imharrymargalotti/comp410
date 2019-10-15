cmake_minimum_required(VERSION 3.14)
project(comp410Proj)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp RBTree.cpp RBTree.h SplayTree.cpp SplayTree.h)
add_executable(comp410Proj ${SOURCE_FILES})