cmake_minimum_required(VERSION 3.24)
project(lab5 C ASM)
set(CMAKE_C_STANDARD 11)

set(SOURCES src/index.c src/file.c src/header.c src/image.c src/utils.c)
set_property(SOURCE filter/pixel_transform.asm APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")

FILE(COPY input1.bmp DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(index ${SOURCES})
