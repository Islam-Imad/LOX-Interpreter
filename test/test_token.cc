#include <gtest/gtest.h>
#include "token.h"

TEST(TokenTest, TestToken)
{
    Token token(TokenType::LEFT_PAREN, 1, 0, 1);
    ASSERT_EQ(token.get_type(), TokenType::LEFT_PAREN);
    ASSERT_EQ(token.get_line(), 1);
    ASSERT_EQ(token.get_start(), 0);
    ASSERT_EQ(token.get_offset(), 1);
}