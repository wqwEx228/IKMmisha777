cmake_minimum_required(VERSION 3.20)
project(IKMmisha)

set(CMAKE_CXX_STANDARD 11)

add_executable(IKMmisha
        main.cpp
        phonebook.cpp
        validator.cpp
)

target_include_directories(IKMmisha PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})