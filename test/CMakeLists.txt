find_package(GTest REQUIRED)
set(google_test GTest::GTest GTest::Main)
add_executable(
    test_scanner
    test_scanner.cc
)

add_executable(
    test_token
    test_token.cc
)

add_executable(
    test_value
    test_value.cc
)

add_executable(
    test_operator_strategy
    test_operator_strategy.cc
)

add_executable(
    test_expression
    test_expression.cc
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
    test_value
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

add_test(
    NAME test_scanner
    COMMAND test_scanner
)

add_test(
    NAME test_token
    COMMAND test_token
)

add_test(
    NAME test_value
    COMMAND test_value
)

add_test(
    NAME test_operator_strategy
    COMMAND test_operator_strategy
)

add_test(
    NAME test_expression
    COMMAND test_expression
)