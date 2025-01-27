#include <gtest/gtest.h>
#include "token.h"

TEST(TokenTest, Test1)
{
    Token token(TokenType::LEFT_PAREN, 1, 0, 1);
    ASSERT_EQ(token.get_type(), TokenType::LEFT_PAREN);
    ASSERT_EQ(token.get_line(), 1);
    ASSERT_EQ(token.get_start(), 0);
    ASSERT_EQ(token.get_offset(), 1);
}

TEST(TokenTest, Test2)
{
    Token token(TokenType::RIGHT_PAREN, 1, 0, 1);
    ASSERT_EQ(token.get_type(), TokenType::RIGHT_PAREN);
    ASSERT_EQ(token.get_line(), 1);
    ASSERT_EQ(token.get_start(), 0);
    ASSERT_EQ(token.get_offset(), 1);
}

TEST(TokenUtilitesTest, Test1)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_keyword(TokenType::AND));
    ASSERT_TRUE(tu.is_keyword("and"));
    ASSERT_FALSE(tu.is_keyword("foo"));
    ASSERT_TRUE(tu.is_keyword(TokenType::CLASS));
    ASSERT_TRUE(tu.is_keyword("class"));
}

TEST(TokenUtilitesTest, Test2)
{
    TokenUtilites tu;
    ASSERT_EQ(tu.string_to_token_type("and"), TokenType::AND);
    ASSERT_EQ(tu.string_to_token_type("class"), TokenType::CLASS);
}

TEST(TokenUtilitesTest, Test3)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_equality(TokenType::EQUAL_EQUAL));
    ASSERT_TRUE(tu.is_equality(TokenType::BANG_EQUAL));
    ASSERT_FALSE(tu.is_equality(TokenType::GREATER));
    ASSERT_FALSE(tu.is_equality(TokenType::LESS));
    ASSERT_TRUE(tu.is_keyword(tu.string_to_token_type("var")));
}

TEST(TokenUtilitesTest, Test4)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_comparison(TokenType::GREATER));
    ASSERT_TRUE(tu.is_comparison(TokenType::GREATER_EQUAL));
    ASSERT_TRUE(tu.is_comparison(TokenType::LESS));
    ASSERT_TRUE(tu.is_comparison(TokenType::LESS_EQUAL));
    ASSERT_FALSE(tu.is_comparison(TokenType::EQUAL_EQUAL));
    ASSERT_FALSE(tu.is_comparison(TokenType::BANG_EQUAL));
}

TEST(TokenUtilitesTest, Test5)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_term(TokenType::PLUS));
    ASSERT_TRUE(tu.is_term(TokenType::MINUS));
    ASSERT_FALSE(tu.is_term(TokenType::STAR));
    ASSERT_FALSE(tu.is_term(TokenType::SLASH));
}

TEST(TokenUtilitesTest, Test6)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_factor(TokenType::STAR));
    ASSERT_TRUE(tu.is_factor(TokenType::SLASH));
    ASSERT_FALSE(tu.is_factor(TokenType::PLUS));
    ASSERT_FALSE(tu.is_factor(TokenType::MINUS));
}

TEST(TokenUtilitesTest, Test7)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_unary(TokenType::BANG));
    ASSERT_TRUE(tu.is_unary(TokenType::MINUS));
    ASSERT_FALSE(tu.is_unary(TokenType::STAR));
    ASSERT_FALSE(tu.is_unary(TokenType::SLASH));
}

TEST(TokenUtilitesTest, Test8)
{
    TokenUtilites tu;
    ASSERT_TRUE(tu.is_literal(TokenType::STRING));
    ASSERT_TRUE(tu.is_literal(TokenType::NUMBER));
    ASSERT_TRUE(tu.is_literal(TokenType::BOOLEAN));
    ASSERT_FALSE(tu.is_literal(TokenType::IDENTIFIER));
}