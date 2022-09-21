set(CMAKE_CXX_STANDARD 20)
add_library(strings rabin-karp.cpp)
target_include_directories(strings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})