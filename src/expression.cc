#include "expression.h"
#include "value.h"

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
