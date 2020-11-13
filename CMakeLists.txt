cmake_minimum_required(VERSION 3.17)
project(Library_System)

set(CMAKE_C_STANDARD 11)

add_executable(Library_System main.c Basic.h Bookshelf.h Book.h View.h Controller.h User.h)