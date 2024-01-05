cmake_minimum_required(VERSION 3.27)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        message.h
        ShannonNode.h
        Dictionary.h
        BinaryNode.h
        filesize.h
        BinarySearchTree.h
)
