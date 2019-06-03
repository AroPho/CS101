cmake_minimum_required(VERSION 3.13)
project(pa5 C)

set(CMAKE_C_STANDARD 99)

add_executable(pa5 main.c Graph.c Graph.h List.c List.h GraphClient.c FindComponents.c)