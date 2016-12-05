cmake_minimum_required(VERSION 3.5)
project(Library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    admin.c
    admin.h
    main.c
    member.c
    member.h
    README.md clients.c clients.h books.c books.h borrows.c borrows.h)

add_executable(Library ${SOURCE_FILES})