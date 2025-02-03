#include <gtest/gtest.h>
#include <operator_strategy.h>
#include <object.h>

TEST(OperatorStrategyTest, AddOperatorStrategy)
{
    OBJ::Casting casting;
    AddOperatorStrategy add_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> result = add_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, 3.0);
}

TEST(OperatorStrategyTest, SubtractOperatorStrategy)
{
    OBJ::Casting casting;
    SubtractOperatorStrategy subtract_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> result = subtract_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, -1.0);
}

TEST(OperatorStrategyTest, MultiplyOperatorStrategy)
{
    OBJ::Casting casting;
    MultiplyOperatorStrategy multiply_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(3.0);
    std::shared_ptr<OBJ::Object> result = multiply_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, 6.0);
}

TEST(OperatorStrategyTest, ModulusOperatorStrategy)
{
    OBJ::Casting casting;
    ModulusOperatorStrategy modulus_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(5.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(3.0);
    std::shared_ptr<OBJ::Object> result = modulus_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, 2.0);
}

TEST(OperatorStrategyTest, DivideOperatorStrategy)
{
    OBJ::Casting casting;
    DivideOperatorStrategy divide_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(6.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(3.0);
    std::shared_ptr<OBJ::Object> result = divide_operator_strategy.execute(left, right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, 2.0);
}

TEST(OperatorStrategyTest, NegateOperatorStrategy)
{
    OBJ::Casting casting;
    NegateOperatorStrategy negate_operator_strategy;
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(3.0);
    std::shared_ptr<OBJ::Object> result = negate_operator_strategy.execute(right);
    double value = casting.cast_to_number(result);
    ASSERT_EQ(value, -3.0);
}

TEST(OperatorStrategyTest, NotOperatorStrategy)
{
    OBJ::Casting casting;
    NotOperatorStrategy not_operator_strategy;
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Boolean>(true);
    std::shared_ptr<OBJ::Object> result = not_operator_strategy.execute(right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, LogicalAndOperatorStrategy)
{
    OBJ::Casting casting;
    LogicalAndOperatorStrategy logical_and_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Boolean>(true);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Boolean>(false);
    std::shared_ptr<OBJ::Object> result = logical_and_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);

    left = std::make_shared<OBJ::Boolean>(true);
    right = std::make_shared<OBJ::Boolean>(true);
    result = logical_and_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, LogicalOrOperatorStrategy)
{
    OBJ::Casting casting;
    LogicalOrOperatorStrategy logical_or_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Boolean>(true);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Boolean>(false);
    std::shared_ptr<OBJ::Object> result = logical_or_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, EqualOperatorStrategy)
{
    OBJ::Casting casting;
    EqualOperatorStrategy equal_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> result = equal_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);

    left = std::make_shared<OBJ::Number>(1.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, NotEqualOperatorStrategy)
{
    OBJ::Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> not_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("!=");
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> result = not_equal_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);

    left = std::make_shared<OBJ::Number>(1.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = not_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, GreaterOperatorStrategy)
{
    OBJ::Casting casting;
    GreaterOperatorStrategy greater_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> result = greater_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);

    left = std::make_shared<OBJ::Number>(1.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = greater_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, GreaterEqualOperatorStrategy)
{
    OBJ::Casting casting;
    GreaterEqualOperatorStrategy greater_equal_operator_strategy;
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> result = greater_equal_operator_strategy.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);

    left = std::make_shared<OBJ::Number>(1.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);

    left = std::make_shared<OBJ::Number>(2.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = greater_equal_operator_strategy.execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);
}

TEST(OperatorStrategyTest, LessOperatorStrategy)
{
    OBJ::Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> less_operator_strategy = OperatorFactory().get_binary_operator_strategy("<");
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> result = less_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);

    left = std::make_shared<OBJ::Number>(2.0);
    right = std::make_shared<OBJ::Number>(1.0);
    result = less_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);
}

TEST(OperatorStrategyTest, LessEqualOperatorStrategy)
{
    OBJ::Casting casting;
    std::unique_ptr<BinaryOperatorStrategy> less_equal_operator_strategy = OperatorFactory().get_binary_operator_strategy("<=");
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> result = less_equal_operator_strategy->execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);

    left = std::make_shared<OBJ::Number>(2.0);
    right = std::make_shared<OBJ::Number>(1.0);
    result = less_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, false);

    left = std::make_shared<OBJ::Number>(2.0);
    right = std::make_shared<OBJ::Number>(2.0);
    result = less_equal_operator_strategy->execute(left, right);
    value = casting.cast_to_boolean(result);
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
    OBJ::Casting casting;
    OperatorFactory operator_factory;
    OperationExecutor operation_executor(operator_factory);
    operation_executor.set_binary_operator_strategy("<=");
    std::shared_ptr<OBJ::Object> left = std::make_shared<OBJ::Number>(1.0);
    std::shared_ptr<OBJ::Object> right = std::make_shared<OBJ::Number>(2.0);
    std::shared_ptr<OBJ::Object> result = operation_executor.execute(left, right);
    bool value = casting.cast_to_boolean(result);
    ASSERT_EQ(value, true);
}
