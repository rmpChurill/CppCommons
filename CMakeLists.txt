#------------------------------------------------------------------------------------------------------------------
#                                                 Allgemeines
#------------------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)

project(CppCommons VERSION 0.0.1 LANGUAGES CXX)
cmake_policy(SET CMP0048 NEW)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

add_library(
    CppCommons

    src/
)