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