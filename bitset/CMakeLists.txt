set(CMAKE_CXX_STANDARD 20)
add_library(bitset bitset.cpp)
target_include_directories(hash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
