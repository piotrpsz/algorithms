add_library(tree_avl node.cpp tree.cpp)
target_include_directories(tree_avl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})