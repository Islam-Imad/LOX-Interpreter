#include <gtest/gtest.h>
#include <operator_strategy.h>

TEST(OperatorStrategy, AddOperatorStrategy)
{
    AddOperatorStrategy add_operator_strategy;
    Value left(1.0);
    Value right(2.0);
    Value result = add_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<double>(), 3.0);
}

TEST(OperatorStrategy, SubtractOperatorStrategy)
{
    SubtractOperatorStrategy subtract_operator_strategy;
    Value left(1.0);
    Value right(2.0);
    Value result = subtract_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<double>(), -1.0);
}

TEST(OperatorStrategy, MultiplyOperatorStrategy)
{
    MultiplyOperatorStrategy multiply_operator_strategy;
    Value left(2.0);
    Value right(3.0);
    Value result = multiply_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<double>(), 6.0);
}

TEST(OperatorStrategy, ModulusOperatorStrategy)
{
    ModulusOperatorStrategy modulus_operator_strategy;
    Value left(5.0);
    Value right(3.0);
    Value result = modulus_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<double>(), 2.0);
}

TEST(OperatorStrategy, DivideOperatorStrategy)
{
    DivideOperatorStrategy divide_operator_strategy;
    Value left(6.0);
    Value right(3.0);
    Value result = divide_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<double>(), 2.0);
}

TEST(OperatorStrategy, NegateOperatorStrategy)
{
    NegateOperatorStrategy negate_operator_strategy;
    Value right(3.0);
    Value result = negate_operator_strategy.execute(right);
    ASSERT_EQ(result.get<double>(), -3.0);
}

TEST(OperatorStrategy, NotOperatorStrategy)
{
    NotOperatorStrategy not_operator_strategy;
    Value right(true);
    Value result = not_operator_strategy.execute(right);
    ASSERT_EQ(result.get<bool>(), false);
}

TEST(OperatorStrategy, LogicalAndOperatorStrategy)
{
    LogicalAndOperatorStrategy logical_and_operator_strategy;
    Value left(true);
    Value right(false);
    Value result = logical_and_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
    left = Value(true);
    right = Value(true);
    result = logical_and_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
}

TEST(OperatorStrategy, LogicalOrOperatorStrategy)
{
    LogicalOrOperatorStrategy logical_or_operator_strategy;
    Value left(true);
    Value right(false);
    Value result = logical_or_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
}

TEST(OperatorStrategy, EqualOperatorStrategy)
{
    EqualOperatorStrategy equal_operator_strategy;
    Value left(1.0);
    Value right(1.0);
    Value result = equal_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
    left = Value(1.0);
    right = Value(2.0);
    result = equal_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
}

TEST(OperatorStrategy, NotEqualOperatorStrategy)
{
    std::unique_ptr<BinaryOperatorStrategy> not_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("!=");
    Value left(1.0);
    Value right(1.0);
    Value result = not_equal_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
    left = Value(1.0);
    right = Value(2.0);
    result = not_equal_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
}

TEST(OperatorStrategy, GreaterOperatorStrategy)
{
    GreaterOperatorStrategy greater_operator_strategy;
    Value left(2.0);
    Value right(1.0);
    Value result = greater_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
    left = Value(1.0);
    right = Value(2.0);
    result = greater_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
}

TEST(OperatorStrategy, GreaterEqualOperatorStrategy)
{
    GreaterEqualOperatorStrategy greater_equal_operator_strategy;
    Value left(2.0);
    Value right(1.0);
    Value result = greater_equal_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
    left = Value(1.0);
    right = Value(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
    left = Value(2.0);
    right = Value(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
}

TEST(OperatorStrategy, LessOperatorStrategy)
{
    std::unique_ptr<BinaryOperatorStrategy> less_operator_strategy = OperatorFactory().get_binary_operator_strategy("<");
    Value left(1.0);
    Value right(2.0);
    Value result = less_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
    left = Value(2.0);
    right = Value(1.0);
    result = less_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
}

TEST(OperatorStrategy, LessEqualOperatorStrategy)
{
    std::unique_ptr<BinaryOperatorStrategy> less_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("<=");
    Value left(1.0);
    Value right(2.0);
    Value result = less_equal_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
    left = Value(2.0);
    right = Value(1.0);
    result = less_equal_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), false);
    left = Value(2.0);
    right = Value(2.0);
    result = less_equal_operator_strategy->execute(left, right);
    ASSERT_EQ(result.get<bool>(), true);
}

TEST(OperatorStrategy, InvalidOperator)
{
    OperatorFactory operator_factory;
    ASSERT_THROW(operator_factory.get_binary_operator_strategy("invalid"), std::runtime_error);
    ASSERT_THROW(operator_factory.get_unary_operator_strategy("invalid"), std::runtime_error);
}

TEST(OperationExecutorClass, LessEqualOperatorStrategy)
{
    OperatorFactory operator_factory = OperatorFactory();
    OperationExecutor operation_executor(operator_factory);
    operation_executor.set_binary_operator_strategy("<=");
    Value left(1.0);
    Value right(2.0);
    Value result = operation_executor.execute(left, right);
    ASSERT_EQ(result.is_type(ValueType::Boolean), true);
    ASSERT_EQ(result.get<bool>(), true);
}