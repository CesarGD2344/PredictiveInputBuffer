
cmake_minimum_required(VERSION 3.21)

project(PredictiveInputBuffer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geode REQUIRED)

add_geode_mod(
    cesar.input-buffer
    src/main.cpp
)
