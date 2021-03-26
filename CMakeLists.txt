#------------------------------------------------------------------------------------------------------------------
#                                                 Allgemeines
#------------------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.17)

project(CppCommons LANGUAGES CXX)
cmake_policy(SET CMP0048 NEW)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

add_library(
    CppCommons
)