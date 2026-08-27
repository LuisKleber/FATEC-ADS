cmake_minimum_required(VERSION 3.10)
project(Balanceamento C)

set(CMAKE_C_STANDARD 17)

add_executable(Balanceamento main.c
        Pilha.h
        Pilha.c)
