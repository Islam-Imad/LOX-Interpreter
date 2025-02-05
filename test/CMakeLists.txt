# Check if Google Test is installed
find_package(GTest QUIET)

if (NOT GTest_FOUND)
    message(STATUS "Google Test not found. Installing Google Test...")

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Set Google Test variables
set(google_test GTest::gtest GTest::gtest_main)

add_executable(
    test_scanner
    test_scanner.cc
)

add_executable(
    test_token
    test_token.cc
)


add_executable(
    test_operator_strategy
    test_operator_strategy.cc
)

add_executable(
    test_expression
    test_expression.cc
)

add_executable(
    test_parser
    test_parser.cc
)

add_executable(
    test_interpreter
    test_interpreter.cc
)

add_executable(
    test_environment
    test_environment.cc
)

add_executable(
    test_object
    test_object.cc
)

target_link_libraries(
    test_scanner
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_token
    LOX_LIB
    ${google_test}
)


target_link_libraries(
    test_operator_strategy
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_expression
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_parser
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_interpreter
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_environment
    LOX_LIB
    ${google_test}
)

target_link_libraries(
    test_object
    LOX_LIB
    ${google_test}
)

add_test(
    NAME test_scanner
    COMMAND test_scanner
)

add_test(
    NAME test_token
    COMMAND test_token
)

add_test(
    NAME test_operator_strategy
    COMMAND test_operator_strategy
)

add_test(
    NAME test_expression
    COMMAND test_expression
)

add_test(
    NAME test_parser
    COMMAND test_parser
)

add_test(
    NAME test_interpreter
    COMMAND test_interpreter
)

add_test(
    NAME test_environment
    COMMAND test_environment
)

add_test(
    NAME test_object
    COMMAND test_object
)