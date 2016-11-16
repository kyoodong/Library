cmake_minimum_required(VERSION 3.5)
project(Library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    admin.c
    admin.h
    file.c
    file.h
    list.c
    list.h
    main.c
    member.c
    member.h
    README.md)

add_executable(Library ${SOURCE_FILES})