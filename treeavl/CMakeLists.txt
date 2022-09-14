add_library(treeavl node.cpp tree.cpp)
target_include_directories(treeavl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})