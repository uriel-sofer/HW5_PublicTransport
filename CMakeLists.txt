cmake_minimum_required(VERSION 3.30)
project(HW5_PublicTransport)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW5_PublicTransport
        EdgeAlreadyExistsException.h
        EdgeNotFoundException.h
        Graph.h
        VertexNotFoundException.h
        main.cpp)
