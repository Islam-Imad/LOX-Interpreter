find_package(GTest REQUIRED)

add_executable(
    test_scanner
    test_scanner.cc
)

add_executable(
    test_token
    test_token.cc
)

target_link_libraries(
    test_scanner
    LOX_LIB
    GTest::GTest
    GTest::Main
)

target_link_libraries(
    test_token
    LOX_LIB
    GTest::GTest
    GTest::Main
)

add_test(
    NAME test_scanner
    COMMAND test_scanner
)

add_test(
    NAME test_token
    COMMAND test_token
)
