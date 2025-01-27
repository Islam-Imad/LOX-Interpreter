
add_library(
    LOX_LIB
    scanner.cc
    token.cc
)

target_include_directories(
    LOX_LIB
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)