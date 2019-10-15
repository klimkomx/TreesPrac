cmake_minimum_required(VERSION 3.14)
project(TreesDrawer)

set(CMAKE_CXX_STANDARD 14)

add_executable(TreesDrawer main.cpp AvlTree.cpp AvlTree.h RedBlackTree.cpp RedBlackTree.h)