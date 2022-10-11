set(CMAKE_CXX_STANDARD 20)
add_library(bloom bloom.cpp)
target_include_directories(bloom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})