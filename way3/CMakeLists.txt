set(CMAKE_CXX_STANDARD 20)
add_library(way3 way3.cpp)
target_include_directories(way3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
