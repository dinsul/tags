cmake_minimum_required(VERSION 3.5)

project(tags LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tags main.cpp game.cpp)
