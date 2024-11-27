cmake_minimum_required(VERSION 3.30)
project(Nicole)

set(CMAKE_CXX_STANDARD 20)

add_executable(Nicole main.cpp
        BowlingGame.h
        BowlingGame.cpp
)
