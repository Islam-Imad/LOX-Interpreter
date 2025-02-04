#include "operator_strategy.h"
#include "object.h"
#include <stdexcept>
#include <cmath>
#include <unordered_map>

std::shared_ptr<Object> AddOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(l + r);
    }
    else if (left_type == ObjectType::STRING && right_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<String>(l + r);
    }
    else
    {
        throw std::runtime_error("Invalid types for addition");
    }
}

std::shared_ptr<Object> SubtractOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(l - r);
    }
    else
    {
        throw std::runtime_error("Invalid types for subtraction");
    }
}

std::shared_ptr<Object> MultiplyOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(l * r);
    }
    else
    {
        throw std::runtime_error("Invalid types for multiplication");
    }
}

std::shared_ptr<Object> ModulusOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        double q = floor(l / r);
        return std::make_unique<Number>(l - (q * r));
    }
    else
    {
        throw std::runtime_error("Invalid types for modulus");
    }
}

std::shared_ptr<Object> PowerOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(pow(l, r));
    }
    else
    {
        throw std::runtime_error("Invalid types for power");
    }
}

std::shared_ptr<Object> DivideOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(l / r);
    }
    else
    {
        throw std::runtime_error("Invalid types for division");
    }
}

std::shared_ptr<Object> FloorDivideOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(floor(l / r));
    }
    else
    {
        throw std::runtime_error("Invalid types for floor division");
    }
}

std::shared_ptr<Object> NegateOperatorStrategy::execute(const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (right_type == ObjectType::NUMBER)
    {
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Number>(-r);
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

std::shared_ptr<Object> NotOperatorStrategy::execute(const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (right_type == ObjectType::BOOLEAN)
    {
        bool r = casting.cast_to_boolean(right)->get_value();
        return std::make_unique<Boolean>(!r);
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

std::shared_ptr<Object> LogicalAndOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::BOOLEAN && right_type == ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left)->get_value();
        bool r = casting.cast_to_boolean(right)->get_value();
        return std::make_unique<Boolean>(l && r);
    }
    else
    {
        throw std::runtime_error("Invalid types for logical and");
    }
}

std::shared_ptr<Object> LogicalOrOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::BOOLEAN && right_type == ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left)->get_value();
        bool r = casting.cast_to_boolean(right)->get_value();
        return std::make_unique<Boolean>(l || r);
    }
    else
    {
        throw std::runtime_error("Invalid types for logical or");
    }
}

std::shared_ptr<Object> EqualOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type != right_type)
    {
        return std::make_unique<Boolean>(false);
    }
    else if (left_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Boolean>(l == r);
    }
    else if (left_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<Boolean>(l == r);
    }
    else if (left_type == ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left)->get_value();
        bool r = casting.cast_to_boolean(right)->get_value();
        return std::make_unique<Boolean>(l == r);
    }
    else
    {
        return std::make_unique<Boolean>(false);
    }
}

std::shared_ptr<Object> NotEqualOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    std::shared_ptr<Object> equal = EqualOperatorStrategy().execute(left, right);
    bool e = casting.cast_to_boolean(equal)->get_value();
    return std::make_unique<Boolean>(!e);
}

std::shared_ptr<Object> GreaterEqualOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Boolean>(l >= r);
    }
    else if (left_type == ObjectType::STRING && right_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<Boolean>(l >= r);
    }
    else
    {
        throw std::runtime_error("Invalid types for greater equal");
    }
}

std::shared_ptr<Object> GreaterOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Boolean>(l > r);
    }
    else if (left_type == ObjectType::STRING && right_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<Boolean>(l > r);
    }
    else
    {
        throw std::runtime_error("Invalid types for greater");
    }
}

std::shared_ptr<Object> LessEqualOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Boolean>(l <= r);
    }
    else if (left_type == ObjectType::STRING && right_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<Boolean>(l <= r);
    }
    else
    {
        throw std::runtime_error("Invalid types for less equal");
    }
}

std::shared_ptr<Object> LessOperatorStrategy::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    TypeCheckVisitor visitor;
    Casting casting;
    left->accept(visitor);
    ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    ObjectType right_type = visitor.get_type();

    if (left_type == ObjectType::NUMBER && right_type == ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left)->get_value();
        double r = casting.cast_to_number(right)->get_value();
        return std::make_unique<Boolean>(l < r);
    }
    else if (left_type == ObjectType::STRING && right_type == ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left)->get_value();
        std::string r = casting.cast_to_string(right)->get_value();;
        return std::make_unique<Boolean>(l < r);
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
    else if (op == "//")
    {
        return std::make_unique<FloorDivideOperatorStrategy>();
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
    else if (op == "&&" || op == "and")
    {
        return std::make_unique<LogicalAndOperatorStrategy>();
    }
    else if (op == "||" || op == "or")
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
    binary_operator_strategy = operator_factory.get_binary_operator_strategy(op);
}

void OperationExecutor::set_unary_operator_strategy(const std::string &op)
{
    unary_operator_strategy = operator_factory.get_unary_operator_strategy(op);
}

std::shared_ptr<Object> OperationExecutor::execute(const std::shared_ptr<Object> &left, const std::shared_ptr<Object> &right) const
{
    return binary_operator_strategy->execute(left, right);
}

std::shared_ptr<Object> OperationExecutor::execute(const std::shared_ptr<Object> &right) const
{
    return unary_operator_strategy->execute(right);
}

OperationExecutor OperationExecutor::clone() const
{
    return OperationExecutor(operator_factory);
}