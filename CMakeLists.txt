cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(algo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
# list(APPEND CMAKE_CXX_FLAGS "-O3")

add_subdirectory("lcs")
add_subdirectory("way3")
add_subdirectory("roman")
add_subdirectory("tree_avl")
add_subdirectory("strings")
add_executable(algo main.cpp)

target_link_libraries(algo PUBLIC
    lcs
    way3
    roman
    tree_avl
    strings)

target_include_directories(algo PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lcs"
                          )