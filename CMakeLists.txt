cmake_minimum_required(VERSION 3.22)
project(tema_lab2 C)

set(CMAKE_C_STANDARD 11 CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic")

add_executable(tema_lab2 main.c
        domain.c
        domain.h
        repository.h
        repository.c
        validator.h
        validator.c
        service.h
        service.c
        UI.c
        UI.h
)
