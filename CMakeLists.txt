cmake_minimum_required(VERSION 3.23)
project(Repulojegyek C)

set(CMAKE_C_STANDARD 99)

add_executable(Repulojegyek main.c admin.h menu.h menu.c jarat.h jarat.c admin.c utas.h utas.c segedFuggvenyek.c segedFuggvenyek.h)
