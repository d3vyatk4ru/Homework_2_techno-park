cmake_minimum_required(VERSION 3.16)
project(CountSymbols)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -Wall -Werror -O0 -ggdb ")

add_subdirectory(src)
add_subdirectory(tests)