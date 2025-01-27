#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "scanner.h"

TEST(ScannerTest, Test_01)
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

TEST(ScannerTest, Test_02)
{
    std::string source = "print   1 + 2;";
    TokenUtilites tu = TokenUtilites();
    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].get_type(), TokenType::PRINT);
    ASSERT_TRUE(tu.is_keyword(tokens[0].get_type()));

    ASSERT_EQ(tokens[1].get_type(), TokenType::NUMBER);
    ASSERT_TRUE(tu.is_literal(tokens[1].get_type()));

    ASSERT_EQ(tokens[2].get_type(), TokenType::PLUS);
    ASSERT_TRUE(tu.is_term(tokens[2].get_type()));

    ASSERT_EQ(tokens[3].get_type(), TokenType::NUMBER);
    ASSERT_TRUE(tu.is_literal(tokens[3].get_type()));

    ASSERT_EQ(tokens[4].get_type(), TokenType::SEMICOLON);
}

TEST(ScannerTest, Test_03)
{
    std::string source = "print   1 + 2;";
    TokenUtilites tu = TokenUtilites();
    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    ASSERT_EQ(tokens.size(), 5);

    ASSERT_EQ(tokens[0].get_type(), TokenType::PRINT);
    ASSERT_EQ(tokens[0].get_line(), 1);
    ASSERT_EQ(tokens[0].get_start(), 0);
    ASSERT_EQ(tokens[0].get_offset(), 5);

    ASSERT_EQ(tokens[1].get_type(), TokenType::NUMBER);
    ASSERT_EQ(tokens[1].get_line(), 1);
    ASSERT_EQ(tokens[1].get_start(), 8);
    ASSERT_EQ(tokens[1].get_offset(), 1);

    ASSERT_EQ(tokens[2].get_type(), TokenType::PLUS);
    ASSERT_EQ(tokens[2].get_line(), 1);
    ASSERT_EQ(tokens[2].get_start(), 10);
    ASSERT_EQ(tokens[2].get_offset(), 1);

    ASSERT_EQ(tokens[3].get_type(), TokenType::NUMBER);
    ASSERT_EQ(tokens[3].get_line(), 1);
    ASSERT_EQ(tokens[3].get_start(), 12);
    ASSERT_EQ(tokens[3].get_offset(), 1);

    ASSERT_EQ(tokens[4].get_type(), TokenType::SEMICOLON);
    ASSERT_EQ(tokens[4].get_line(), 1);
    ASSERT_EQ(tokens[4].get_start(), 13);
    ASSERT_EQ(tokens[4].get_offset(), 1);
}