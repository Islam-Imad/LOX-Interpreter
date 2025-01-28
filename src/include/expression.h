#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <string>
#include <value.h>

class Expression;
class BinaryExpression;
class UnaryExpression;
class LiteralExpression;
class GroupingExpression;

class ExpressionVisitor
{
public:
    virtual void visit(const BinaryExpression &expression) = 0;
    virtual void visit(const UnaryExpression &expression) = 0;
    virtual void visit(const LiteralExpression &expression) = 0;
    virtual void visit(const GroupingExpression &expression) = 0;
};

class Expression
{
public:
    virtual void accept(ExpressionVisitor &visitor) const = 0;
};

class BinaryExpression : public Expression
{
public:
    std::unique_ptr<const Expression> left;
    std::unique_ptr<const Expression> right;
    std::string op;

    BinaryExpression(std::unique_ptr<const Expression> left, std::unique_ptr<const Expression> right, const std::string &op);
    void accept(ExpressionVisitor &visitor) const override;
};

class UnaryExpression : public Expression
{
public:
    std::unique_ptr<const Expression> right;
    std::string op;

    UnaryExpression(std::unique_ptr<const Expression> right, const std::string &op);
    void accept(ExpressionVisitor &visitor) const override;
};

class LiteralExpression : public Expression
{
public:
    Value value;

    LiteralExpression(const Value &value);
    void accept(ExpressionVisitor &visitor) const override;
};

class GroupingExpression : public Expression
{
public:
    std::unique_ptr<const Expression> expression;

    GroupingExpression(std::unique_ptr<const Expression> expression);
    void accept(ExpressionVisitor &visitor) const override;
};

#endif // EXPRESSION_H