#include <gtest/gtest.h>
#include "expression.h"

TEST(Expression, LiteralExpression)
{
    std::shared_ptr<OBJ::Object> value = std::make_shared<OBJ::Number>(1.0);
    LiteralExpression literal_expression(value);
}
