#include <gtest/gtest.h>
#include "expression.h"

TEST(Expression, LiteralExpression)
{
    std::shared_ptr<Object> value = std::make_shared<Number>(1.0);
    LiteralExpression literal_expression(value);
}

TEST(Expression, BinaryExpression)
{
    std::unique_ptr<const Expression> left = std::make_unique<LiteralExpression>(std::make_shared<Number>(1.0));
    std::unique_ptr<const Expression> right = std::make_unique<LiteralExpression>(std::make_shared<Number>(2.0));
    BinaryExpression binary_expression(std::move(left), std::move(right), "+");
    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    operation_executor.set_binary_operator_strategy("+");
    operation_executor.execute(std::make_shared<Number>(1.0), std::make_shared<Number>(2.0));
}