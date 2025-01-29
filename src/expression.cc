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

ExpressionEvaluator::ExpressionEvaluator(OperationExecutor operation_executor) : operation_executor(std::move(operation_executor)) {}

void ExpressionEvaluator::visit(const LiteralExpression &expression)
{
    result = expression.value;
}

void ExpressionEvaluator::visit(const UnaryExpression &expression)
{
    expression.right->accept(*this);
    Value right = result;
    operation_executor.set_unary_operator_strategy(expression.op);
    result = operation_executor.execute(right);
}

void ExpressionEvaluator::visit(const BinaryExpression &expression)
{
    expression.left->accept(*this);
    Value left = result;
    expression.right->accept(*this);
    Value right = result;
    operation_executor.set_binary_operator_strategy(expression.op);
    result = operation_executor.execute(left, right);
}

void ExpressionEvaluator::visit(const GroupingExpression &expression)
{
    expression.expression->accept(*this);
}

Value ExpressionEvaluator::get_result() const
{
    return result;
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