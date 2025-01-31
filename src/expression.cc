#include "expression.h"
#include "value.h"
#include "operator_strategy.h"

BinaryExpression::BinaryExpression(
    std::unique_ptr<const Expression> left, std::unique_ptr<const Expression> right, const std::string &op)
    : left(std::move(left)), right(std::move(right)), op(op) {}

void BinaryExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

UnaryExpression::UnaryExpression(std::unique_ptr<const Expression> right, const std::string &op)
    : right(std::move(right)), op(op) {}

void UnaryExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

LiteralExpression::LiteralExpression(const Value &value) : value(value) {}

void LiteralExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

GroupingExpression::GroupingExpression(std::unique_ptr<const Expression> expression) : expression(std::move(expression)) {}

void GroupingExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

VariableExpression::VariableExpression(const std::string &name) : name(name) {}

void VariableExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

AssignExpression::AssignExpression(const std::string &name, std::unique_ptr<const Expression> expression)
    : name(name), expression(std::move(expression)) {}

void AssignExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}



void ExpressionPrinter::visit(const LiteralExpression &expression)
{
    Value value = expression.value;
    std::string sub = "";
    if (value.is_type(ValueType::Number))
    {
        sub = std::to_string(value.get<double>());
    }
    else if (value.is_type(ValueType::String))
    {
        sub = value.get<std::string>();
    }
    else if (value.is_type(ValueType::Boolean))
    {
        sub = value.get<bool>() ? "true" : "false";
    }
    else
    {
        sub = "nil";
    }
    result = sub;
}

void ExpressionPrinter::visit(const UnaryExpression &expression)
{
    std::string sub = "";
    sub = "(" + expression.op + " ";
    expression.right->accept(*this);
    sub += get_result() + ")";
    result = sub;
}

void ExpressionPrinter::visit(const BinaryExpression &expression)
{
    std::string sub = "";
    sub = "(";
    expression.left->accept(*this);
    sub += get_result() + " " + expression.op + " ";
    expression.right->accept(*this);
    sub += get_result() + ")";
    result = sub;
}

void ExpressionPrinter::visit(const GroupingExpression &expression)
{
    expression.expression->accept(*this);
}

std::string ExpressionPrinter::get_result() const
{
    return result;
}