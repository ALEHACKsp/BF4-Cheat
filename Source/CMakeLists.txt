cmake_minimum_required(VERSION 3.19)
project(BF4)

set(CMAKE_CXX_STANDARD 17)

add_library(BF4 SHARED main.cpp Offset.h Player.cpp Player.h Hack.cpp Hack.h Gun.cpp Gun.h)
