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

std::unique_ptr<BinaryOperatorStrategy> OperatorFactory::get_binary_operator_strategy(const std::string &op) const
{
    if (op == "+")
    {
        return std::make_unique<AddOperatorStrategy>();
    }
    else if (op == "-")
    {
        return std::make_unique<SubtractOperatorStrategy>();
    }
    else if (op == "*")
    {
        return std::make_unique<MultiplyOperatorStrategy>();
    }
    else if (op == "/")
    {
        return std::make_unique<DivideOperatorStrategy>();
    }
    else if (op == "%")
    {
        return std::make_unique<ModulusOperatorStrategy>();
    }
    else if (op == "**")
    {
        return std::make_unique<PowerOperatorStrategy>();
    }
    else if (op == "==")
    {
        return std::make_unique<EqualOperatorStrategy>();
    }
    else if (op == "!=")
    {
        return std::make_unique<NotEqualOperatorStrategy>();
    }
    else if (op == ">=")
    {
        return std::make_unique<GreaterEqualOperatorStrategy>();
    }
    else if (op == ">")
    {
        return std::make_unique<GreaterOperatorStrategy>();
    }
    else if (op == "<=")
    {
        return std::make_unique<LessEqualOperatorStrategy>();
    }
    else if (op == "<")
    {
        return std::make_unique<LessOperatorStrategy>();
    }
    else if (op == "&&" or op == "and")
    {
        return std::make_unique<LogicalAndOperatorStrategy>();
    }
    else if (op == "||" or op == "or")
    {
        return std::make_unique<LogicalOrOperatorStrategy>();
    }
    else
    {
        throw std::runtime_error("Invalid operator");
    }
}

std::unique_ptr<UnaryOperatorStrategy> OperatorFactory::get_unary_operator_strategy(const std::string &op) const
{
    if (op == "-")
    {
        return std::make_unique<NegateOperatorStrategy>();
    }
    else if (op == "!")
    {
        return std::make_unique<NotOperatorStrategy>();
    }
    else
    {
        throw std::runtime_error("Invalid operator");
    }
}

OperationExecutor::OperationExecutor(OperatorFactory operator_factory) : operator_factory(operator_factory) {}

void OperationExecutor::set_binary_operator_strategy(const std::string &op)
{
    binary_operator_strategy = std::move(operator_factory.get_binary_operator_strategy(op));
}

void OperationExecutor::set_unary_operator_strategy(const std::string &op)
{
    unary_operator_strategy = std::move(operator_factory.get_unary_operator_strategy(op));
}

Value OperationExecutor::execute(const Value &left, const Value &right) const
{
    return binary_operator_strategy->execute(left, right);
}

Value OperationExecutor::execute(const Value &right) const
{
    return unary_operator_strategy->execute(right);
}
