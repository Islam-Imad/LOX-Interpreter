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
    OperationExecutor &operation_executor = OperationExecutor::get_instance();
    operation_executor.set_binary_operator_strategy("+");
    operation_executor.execute(std::make_shared<Number>(1.0), std::make_shared<Number>(2.0));
}

TEST(Expression, UnaryExpression)
{
    std::unique_ptr<const Expression> right = std::make_unique<LiteralExpression>(std::make_shared<Number>(1.0));
    UnaryExpression unary_expression(std::move(right), "-");
    OperationExecutor &operation_executor = OperationExecutor::get_instance();
    operation_executor.set_unary_operator_strategy("-");
    operation_executor.execute(std::make_shared<Number>(1.0));
}

TEST(Expression, GroupingExpression)
{
    std::unique_ptr<const Expression> expression = std::make_unique<LiteralExpression>(std::make_shared<Number>(1.0));
    GroupingExpression grouping_expression(std::move(expression));
}

TEST(Expression, VariableExpression)
{
    VariableExpression variable_expression("a");
}