#include "expression.h"
#include "object.h"
#include "operator_strategy.h"
#include <string>
#include <memory>

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

LiteralExpression::LiteralExpression(const std::shared_ptr<Object> &value) : value(value) {}

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

CallExpression::CallExpression(std::unique_ptr<const Expression> callee, std::vector<std::unique_ptr<const Expression>> arguments)
    : callee(std::move(callee)), arguments(std::move(arguments)) {}

void CallExpression::accept(ExpressionVisitor &visitor) const
{
    visitor.visit(*this);
}

void ExpressionPrinter::visit(const LiteralExpression &expression)
{
    result = expression.value->str();
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

void ExpressionPrinter::visit(const VariableExpression &expression)
{
    result = expression.name;
}

void ExpressionPrinter::visit(const AssignExpression &expression)
{
    std::string sub = "";
    sub = "(" + expression.name + " = ";
    expression.expression->accept(*this);
    sub += get_result() + ")";
    result = sub;
}

void ExpressionPrinter::visit(const CallExpression &expression)
{
    std::string sub = "";
    sub = "(";
    expression.callee->accept(*this);
    sub += get_result() + "(";
    for (size_t i = 0; i < expression.arguments.size(); i++)
    {
        expression.arguments[i]->accept(*this);
        sub += get_result();
        if (i != expression.arguments.size() - 1)
        {
            sub += ", ";
        }
    }
    sub += "))";
    result = sub;
}

std::string ExpressionPrinter::get_result() const
{
    return result;
}

void ExpressionTypeVisitor::visit(const LiteralExpression &expression)
{
    result = ExpressionType::LITERAL;
}

void ExpressionTypeVisitor::visit(const UnaryExpression &expression)
{
    result = ExpressionType::UNARY;
}

void ExpressionTypeVisitor::visit(const BinaryExpression &expression)
{
    result = ExpressionType::BINARY;
}

void ExpressionTypeVisitor::visit(const GroupingExpression &expression)
{
    result = ExpressionType::GROUPING;
}

void ExpressionTypeVisitor::visit(const VariableExpression &expression)
{
    result = ExpressionType::VARIABLE;
}

void ExpressionTypeVisitor::visit(const AssignExpression &expression)
{
    result = ExpressionType::ASSIGN;
}

void ExpressionTypeVisitor::visit(const CallExpression &expression)
{
    result = ExpressionType::CALL;
}

ExpressionType ExpressionTypeVisitor::get_result() const
{
    return result;
}