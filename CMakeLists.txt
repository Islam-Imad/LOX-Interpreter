cmake_minimum_required(VERSION 3.5)

project("LOX Interpreter")

set(PROJECT_DESCRIPTION "Tree Walk Interpreter for Lox Language")
set(PROJECT_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    version.h.in
    version.h
)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

add_executable(
    lox
    main.cc
)

target_link_libraries(
    lox
    LOX_LIB
)

target_include_directories(
    lox
    PRIVATE
    ${CMAKE_BINARY_DIR}
)

enable_testing()
