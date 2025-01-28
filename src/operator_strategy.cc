#include "operator_strategy.h"
#include "value.h"
#include <stdexcept>
#include <cmath>
#include <unordered_map>

Value AddOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() + right.get<double>());
    }
    else if (left.is_type(ValueType::String) && right.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() + right.get<std::string>());
    }
    else
    {
        throw std::runtime_error("Invalid types for addition");
    }
}

Value SubtractOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() - right.get<double>());
    }
    else
    {
        throw std::runtime_error("Invalid types for subtraction");
    }
}

Value MultiplyOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() * right.get<double>());
    }
    else
    {
        throw std::runtime_error("Invalid types for multiplication");
    }
}

Value ModulusOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        double l = left.get<double>();
        double r = right.get<double>();
        double q = floor(l / r);
        return Value(l - (q * r));
    }
    else
    {
        throw std::runtime_error("Invalid types for modulus");
    }
}

Value PowerOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(pow(left.get<double>(), right.get<double>()));
    }
    else
    {
        throw std::runtime_error("Invalid types for power");
    }
}

Value DivideOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() / right.get<double>());
    }
    else
    {
        throw std::runtime_error("Invalid types for division");
    }
}

Value NegateOperatorStrategy::execute(const Value &right) const
{
    if (right.is_type(ValueType::Number))
    {
        return Value(-right.get<double>());
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

Value NotOperatorStrategy::execute(const Value &right) const
{
    if (right.is_type(ValueType::Boolean))
    {
        return Value(!right.get<bool>());
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

Value LogicalAndOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Boolean) && right.is_type(ValueType::Boolean))
    {
        return Value(left.get<bool>() && right.get<bool>());
    }
    else
    {
        throw std::runtime_error("Invalid types for logical and");
    }
}

Value LogicalOrOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Boolean) && right.is_type(ValueType::Boolean))
    {
        return Value(left.get<bool>() || right.get<bool>());
    }
    else
    {
        throw std::runtime_error("Invalid types for logical or");
    }
}

Value EqualOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.type() != right.type())
    {
        return Value(false);
    }
    else if (left.is_type(ValueType::Number))
    {
        return Value(left.get<double>() == right.get<double>());
    }
    else if (left.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() == right.get<std::string>());
    }
    else if (left.is_type(ValueType::Boolean))
    {
        return Value(left.get<bool>() == right.get<bool>());
    }
    else
    {
        return Value(false);
    }
}

Value NotEqualOperatorStrategy::execute(const Value &left, const Value &right) const
{
    return Value(!EqualOperatorStrategy().execute(left, right).get<bool>());
}

Value GreaterEqualOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() >= right.get<double>());
    }
    else if (left.is_type(ValueType::String) && right.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() >= right.get<std::string>());
    }
    else
    {
        throw std::runtime_error("Invalid types for greater equal");
    }
}

Value GreaterOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() > right.get<double>());
    }
    else if (left.is_type(ValueType::String) && right.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() > right.get<std::string>());
    }
    else
    {
        throw std::runtime_error("Invalid types for greater");
    }
}

Value LessEqualOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() <= right.get<double>());
    }
    else if (left.is_type(ValueType::String) && right.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() <= right.get<std::string>());
    }
    else
    {
        throw std::runtime_error("Invalid types for less equal");
    }
}

Value LessOperatorStrategy::execute(const Value &left, const Value &right) const
{
    if (left.is_type(ValueType::Number) && right.is_type(ValueType::Number))
    {
        return Value(left.get<double>() < right.get<double>());
    }
    else if (left.is_type(ValueType::String) && right.is_type(ValueType::String))
    {
        return Value(left.get<std::string>() < right.get<std::string>());
    }
    else
    {
        throw std::runtime_error("Invalid types for less");
    }
}

OperatorStrategyFactory &OperatorStrategyFactory::get_instance()
{
    static OperatorStrategyFactory instance;
    return instance;
}

OperatorStrategyFactory::OperatorStrategyFactory()
{
    binaryOperatorStrategies["+"] = std::make_unique<AddOperatorStrategy>();
    binaryOperatorStrategies["-"] = std::make_unique<SubtractOperatorStrategy>();
    binaryOperatorStrategies["*"] = std::make_unique<MultiplyOperatorStrategy>();
    binaryOperatorStrategies["/"] = std::make_unique<DivideOperatorStrategy>();
    binaryOperatorStrategies["%"] = std::make_unique<ModulusOperatorStrategy>();
    binaryOperatorStrategies["**"] = std::make_unique<PowerOperatorStrategy>();
    binaryOperatorStrategies["=="] = std::make_unique<EqualOperatorStrategy>();
    binaryOperatorStrategies["!="] = std::make_unique<NotEqualOperatorStrategy>();
    binaryOperatorStrategies[">="] = std::make_unique<GreaterEqualOperatorStrategy>();
    binaryOperatorStrategies[">"] = std::make_unique<GreaterOperatorStrategy>();
    binaryOperatorStrategies["<="] = std::make_unique<LessEqualOperatorStrategy>();
    binaryOperatorStrategies["<"] = std::make_unique<LessOperatorStrategy>();
    binaryOperatorStrategies["&&"] = std::make_unique<LogicalAndOperatorStrategy>();
    binaryOperatorStrategies["||"] = std::make_unique<LogicalOrOperatorStrategy>();

    unaryOperatorStrategies["-"] = std::make_unique<NegateOperatorStrategy>();
    unaryOperatorStrategies["!"] = std::make_unique<NotOperatorStrategy>();
}

std::unique_ptr<BinaryOperatorStrategy> OperatorStrategyFactory::get_binary_operator_strategy(const std::string &op) const
{
    return std::make_unique<BinaryOperatorStrategy>(*binaryOperatorStrategies.at(op));
}

std::unique_ptr<UnaryOperatorStrategy> OperatorStrategyFactory::get_unary_operator_strategy(const std::string &op) const
{
    return std::make_unique<UnaryOperatorStrategy>(*unaryOperatorStrategies.at(op));
}