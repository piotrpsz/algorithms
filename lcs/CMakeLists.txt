add_library(lcs action.cpp parser.cpp range.cpp shared.cpp token.cpp)
target_include_directories(lcs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
