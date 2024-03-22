cmake_minimum_required(VERSION 3.26)
project(DA_Proj_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DA_Proj_1
        src/FileManager.cpp
        src/FileManager.h
        src/Graph.h
        main.cpp
        src/GraphManager.h
        src/Node.h
        src/Node.cpp
        src/Pipe.h
        src/Pipe.cpp
        src/GraphManager.cpp)
