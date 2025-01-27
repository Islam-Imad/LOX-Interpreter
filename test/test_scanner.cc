#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "scanner.h"

TEST(ScannerTest, TestScanner)
{
    std::string source = "print   1 + 2;";
    TokenUtilites tu = TokenUtilites();
    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    ASSERT_EQ(tokens.size(), 5);
    ASSERT_EQ(tokens[0].get_type(), TokenType::PRINT);
    ASSERT_EQ(tokens[1].get_type(), TokenType::NUMBER);
    ASSERT_EQ(tokens[2].get_type(), TokenType::PLUS);
    ASSERT_EQ(tokens[3].get_type(), TokenType::NUMBER);
}