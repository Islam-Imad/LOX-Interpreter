#include <gtest/gtest.h>
#include "expression.h"
#include "value.h"
#include "operator_strategy.h"

TEST(Expression, BinaryExpression)
{
    std::unique_ptr<Expression> left = std::make_unique<LiteralExpression>(Value(1.0));
    std::unique_ptr<Expression> right = std::make_unique<LiteralExpression>(Value(2.0));
    BinaryExpression expression(std::move(left), std::move(right), "+");
    OperatorFactory factory = OperatorFactory();
    OperationExecutor operation_executor = OperationExecutor(factory);
    // ExpressionEvaluator evaluator(std::move(operation_executor));
    // expression.accept(evaluator);
    // Value result = evaluator.get_result();
    // ASSERT_EQ(result.get<double>(), 3.0);
}

TEST(Expression, BinaryExpression2)
{
    std::unique_ptr<Expression> left = std::make_unique<LiteralExpression>(Value(1.0));
    std::unique_ptr<Expression> right = std::make_unique<LiteralExpression>(Value(2.0));
    BinaryExpression expression(std::move(left), std::move(right), "-");
    OperatorFactory factory = OperatorFactory();
    OperationExecutor operation_executor = OperationExecutor(factory);
    // ExpressionEvaluator evaluator(std::move(operation_executor));
    // expression.accept(evaluator);
    // Value result = evaluator.get_result();
    // ASSERT_EQ(result.get<double>(), -1.0);
}

TEST(Expression, UnaryExpression)
{
    std::unique_ptr<Expression> right = std::make_unique<LiteralExpression>(Value(1.0));
    UnaryExpression expression(std::move(right), "-");
    OperatorFactory factory = OperatorFactory();
    OperationExecutor operation_executor = OperationExecutor(factory);
    // ExpressionEvaluator evaluator(std::move(operation_executor));
    // expression.accept(evaluator);
    // Value result = evaluator.get_result();
    // ASSERT_EQ(result.get<double>(), -1.0);
}

TEST(Expression, GroupingExpression)
{
    std::unique_ptr<Expression> expression = std::make_unique<LiteralExpression>(Value(1.0));
    GroupingExpression grouping_expression(std::move(expression));
    OperatorFactory factory = OperatorFactory();
    OperationExecutor operation_executor = OperationExecutor(factory);
    // ExpressionEvaluator evaluator(std::move(operation_executor));
    // grouping_expression.accept(evaluator);
    // Value result = evaluator.get_result();
    // ASSERT_EQ(result.get<double>(), 1.0);
}

