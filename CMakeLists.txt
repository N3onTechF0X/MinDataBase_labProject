cmake_minimum_required(VERSION 3.29)
project(minDataBase C)

set(CMAKE_C_STANDARD 11)

add_executable(minDataBase main.c contact.c config.c utils.c)