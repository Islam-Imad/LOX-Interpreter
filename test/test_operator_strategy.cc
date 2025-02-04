#include <gtest/gtest.h>
#include <operator_strategy.h>
#include <object.h>

TEST(OperatorStrategyTest, AddOperatorStrategy)
{
    Casting casting;
    AddOperatorStrategy add_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> result = add_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, 3.0);
}

TEST(OperatorStrategyTest, SubtractOperatorStrategy)
{
    Casting casting;
    SubtractOperatorStrategy subtract_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> result = subtract_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, -1.0);
}

TEST(OperatorStrategyTest, MultiplyOperatorStrategy)
{
    Casting casting;
    MultiplyOperatorStrategy multiply_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(3.0);
    std::shared_ptr<Object> result = multiply_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, 6.0);
}

TEST(OperatorStrategyTest, ModulusOperatorStrategy)
{
    Casting casting;
    ModulusOperatorStrategy modulus_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(5.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(3.0);
    std::shared_ptr<Object> result = modulus_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, 2.0);
}

TEST(OperatorStrategyTest, DivideOperatorStrategy)
{
    Casting casting;
    DivideOperatorStrategy divide_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(6.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(3.0);
    std::shared_ptr<Object> result = divide_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, 2.0);
}

TEST(OperatorStrategyTest, NegateOperatorStrategy)
{
    Casting casting;
    NegateOperatorStrategy negate_operator_strategy;
    std::shared_ptr<Object> right = std::make_shared<Number>(3.0);
    std::shared_ptr<Object> result = negate_operator_strategy.execute(right);
    double value = casting.cast_to_number(result)->get_value();
    ASSERT_EQ(value, -3.0);
}

TEST(OperatorStrategyTest, NotOperatorStrategy)
{
    Casting casting;
    NotOperatorStrategy not_operator_strategy;
    std::shared_ptr<Object> right = std::make_shared<Boolean>(true);
    std::shared_ptr<Object> result = not_operator_strategy.execute(right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, LogicalAndOperatorStrategy)
{
    Casting casting;
    LogicalAndOperatorStrategy logical_and_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Boolean>(true);
    std::shared_ptr<Object> right = std::make_shared<Boolean>(false);
    std::shared_ptr<Object> result = logical_and_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);

    left = std::make_shared<Boolean>(true);
    right = std::make_shared<Boolean>(true);
    result = logical_and_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, LogicalOrOperatorStrategy)
{
    Casting casting;
    LogicalOrOperatorStrategy logical_or_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Boolean>(true);
    std::shared_ptr<Object> right = std::make_shared<Boolean>(false);
    std::shared_ptr<Object> result = logical_or_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, EqualOperatorStrategy)
{
    Casting casting;
    EqualOperatorStrategy equal_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> result = equal_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);

    left = std::make_shared<Number>(1.0);
    right = std::make_shared<Number>(2.0);
    result = equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, NotEqualOperatorStrategy)
{
    Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> not_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("!=");
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> result = not_equal_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);

    left = std::make_shared<Number>(1.0);
    right = std::make_shared<Number>(2.0);
    result = not_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, GreaterOperatorStrategy)
{
    Casting casting;
    GreaterOperatorStrategy greater_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> result = greater_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);

    left = std::make_shared<Number>(1.0);
    right = std::make_shared<Number>(2.0);
    result = greater_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, GreaterEqualOperatorStrategy)
{
    Casting casting;
    GreaterEqualOperatorStrategy greater_equal_operator_strategy;
    std::shared_ptr<Object> left = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> result = greater_equal_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);

    left = std::make_shared<Number>(1.0);
    right = std::make_shared<Number>(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);

    left = std::make_shared<Number>(2.0);
    right = std::make_shared<Number>(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, LessOperatorStrategy)
{
    Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> less_operator_strategy = OperatorFactory().get_binary_operator_strategy("<");
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> result = less_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);

    left = std::make_shared<Number>(2.0);
    right = std::make_shared<Number>(1.0);
    result = less_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, LessEqualOperatorStrategy)
{
    Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> less_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("<=");
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> result = less_equal_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);

    left = std::make_shared<Number>(2.0);
    right = std::make_shared<Number>(1.0);
    result = less_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, false);

    left = std::make_shared<Number>(2.0);
    right = std::make_shared<Number>(2.0);
    result = less_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, InvalidOperator)
{
    OperatorFactory operator_factory;
    ASSERT_THROW(operator_factory.get_binary_operator_strategy("invalid"), std::runtime_error);
    ASSERT_THROW(operator_factory.get_unary_operator_strategy("invalid"), std::runtime_error);
}

TEST(OperatorStrategyTest, OperationExecutor)
{
    Casting casting;
    OperatorFactory operator_factory;
    OperationExecutor operation_executor(operator_factory);
    operation_executor.set_binary_operator_strategy("<=");
    std::shared_ptr<Object> left = std::make_shared<Number>(1.0);
    std::shared_ptr<Object> right = std::make_shared<Number>(2.0);
    std::shared_ptr<Object> result = operation_executor.execute(left, right);
    bool value = casting.cast_to_boolean(result)->get_value();
    ASSERT_EQ(value, true);
}
