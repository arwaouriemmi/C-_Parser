cmake_minimum_required(VERSION 3.9)
project(IEX_DEEP_HISTORICAL_DATA_PARSER VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Main file
add_executable(iex_deep_parser src/main.cpp)


