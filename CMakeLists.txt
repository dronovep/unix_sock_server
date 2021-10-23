cmake_minimum_required(VERSION 3.20)
project(unix_sock_server C)

set(CMAKE_C_STANDARD 99)

add_executable(unix_sock_server main.c)
