cmake_minimum_required(VERSION 3.24)

set(MATRIX_LIB "matrixlib")

project(Matrix_Library)

add_library(${MATRIX_LIB} INTERFACE matrix.hpp)

add_executable(LibTest matrix.cpp)

target_link_libraries(LibTest INTERFACE ${MATRIX_LIB})
