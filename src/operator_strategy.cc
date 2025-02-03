#include "operator_strategy.h"
#include "object.h"
#include <stdexcept>
#include <cmath>
#include <unordered_map>

std::shared_ptr<OBJ::Object> AddOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(l + r);
    }
    else if (left_type == OBJ::ObjectType::STRING && right_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::String>(l + r);
    }
    else
    {
        throw std::runtime_error("Invalid types for addition");
    }
}

std::shared_ptr<OBJ::Object> SubtractOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(l - r);
    }
    else
    {
        throw std::runtime_error("Invalid types for subtraction");
    }
}

std::shared_ptr<OBJ::Object> MultiplyOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(l * r);
    }
    else
    {
        throw std::runtime_error("Invalid types for multiplication");
    }
}

std::shared_ptr<OBJ::Object> ModulusOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        double q = floor(l / r);
        return std::make_unique<OBJ::Number>(l - (q * r));
    }
    else
    {
        throw std::runtime_error("Invalid types for modulus");
    }
}

std::shared_ptr<OBJ::Object> PowerOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(pow(l, r));
    }
    else
    {
        throw std::runtime_error("Invalid types for power");
    }
}

std::shared_ptr<OBJ::Object> DivideOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(l / r);
    }
    else
    {
        throw std::runtime_error("Invalid types for division");
    }
}

std::shared_ptr<OBJ::Object> FloorDivideOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(floor(l / r));
    }
    else
    {
        throw std::runtime_error("Invalid types for floor division");
    }
}

std::shared_ptr<OBJ::Object> NegateOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (right_type == OBJ::ObjectType::NUMBER)
    {
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Number>(-r);
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

std::shared_ptr<OBJ::Object> NotOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (right_type == OBJ::ObjectType::BOOLEAN)
    {
        bool r = casting.cast_to_boolean(right);
        return std::make_unique<OBJ::Boolean>(!r);
    }
    else
    {
        throw std::runtime_error("Invalid type for negation");
    }
}

std::shared_ptr<OBJ::Object> LogicalAndOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::BOOLEAN && right_type == OBJ::ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left);
        bool r = casting.cast_to_boolean(right);
        return std::make_unique<OBJ::Boolean>(l && r);
    }
    else
    {
        throw std::runtime_error("Invalid types for logical and");
    }
}

std::shared_ptr<OBJ::Object> LogicalOrOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::BOOLEAN && right_type == OBJ::ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left);
        bool r = casting.cast_to_boolean(right);
        return std::make_unique<OBJ::Boolean>(l || r);
    }
    else
    {
        throw std::runtime_error("Invalid types for logical or");
    }
}

std::shared_ptr<OBJ::Object> EqualOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type != right_type)
    {
        return std::make_unique<OBJ::Boolean>(false);
    }
    else if (left_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Boolean>(l == r);
    }
    else if (left_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::Boolean>(l == r);
    }
    else if (left_type == OBJ::ObjectType::BOOLEAN)
    {
        bool l = casting.cast_to_boolean(left);
        bool r = casting.cast_to_boolean(right);
        return std::make_unique<OBJ::Boolean>(l == r);
    }
    else
    {
        return std::make_unique<OBJ::Boolean>(false);
    }
}

std::shared_ptr<OBJ::Object> NotEqualOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    std::shared_ptr<OBJ::Object> equal = EqualOperatorStrategy().execute(left, right);
    bool e = casting.cast_to_boolean(equal);
    return std::make_unique<OBJ::Boolean>(!e);
}

std::shared_ptr<OBJ::Object> GreaterEqualOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Boolean>(l >= r);
    }
    else if (left_type == OBJ::ObjectType::STRING && right_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::Boolean>(l >= r);
    }
    else
    {
        throw std::runtime_error("Invalid types for greater equal");
    }
}

std::shared_ptr<OBJ::Object> GreaterOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Boolean>(l > r);
    }
    else if (left_type == OBJ::ObjectType::STRING && right_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::Boolean>(l > r);
    }
    else
    {
        throw std::runtime_error("Invalid types for greater");
    }
}

std::shared_ptr<OBJ::Object> LessEqualOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Boolean>(l <= r);
    }
    else if (left_type == OBJ::ObjectType::STRING && right_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::Boolean>(l <= r);
    }
    else
    {
        throw std::runtime_error("Invalid types for less equal");
    }
}

std::shared_ptr<OBJ::Object> LessOperatorStrategy::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    OBJ::TypeCheckVisitor visitor;
    OBJ::Casting casting;
    left->accept(visitor);
    OBJ::ObjectType left_type = visitor.get_type();
    right->accept(visitor);
    OBJ::ObjectType right_type = visitor.get_type();

    if (left_type == OBJ::ObjectType::NUMBER && right_type == OBJ::ObjectType::NUMBER)
    {
        double l = casting.cast_to_number(left);
        double r = casting.cast_to_number(right);
        return std::make_unique<OBJ::Boolean>(l < r);
    }
    else if (left_type == OBJ::ObjectType::STRING && right_type == OBJ::ObjectType::STRING)
    {
        std::string l = casting.cast_to_string(left);
        std::string r = casting.cast_to_string(right);
        return std::make_unique<OBJ::Boolean>(l < r);
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

std::shared_ptr<OBJ::Object> OperationExecutor::execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const
{
    return binary_operator_strategy->execute(left, right);
}

std::shared_ptr<OBJ::Object> OperationExecutor::execute(const std::shared_ptr<OBJ::Object> &right) const
{
    return unary_operator_strategy->execute(right);
}

OperationExecutor OperationExecutor::clone() const
{
    return OperationExecutor(operator_factory);
}