add_library(
    LOX_LIB
    scanner.cc
    token.cc
    expression.cc
    operator_strategy.cc
    parser.cc
    statement.cc
    interpreter.cc
    object.cc
)

target_include_directories(
    LOX_LIB
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)