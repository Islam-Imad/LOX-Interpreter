#ifndef OPERATOR_STRATEGY_H
#define OPERATOR_STRATEGY_H

#include <memory>
#include <string>
#include <value.h>
#include <unordered_map>

class BinaryOperatorStrategy
{
public:
    virtual Value execute(const Value &left, const Value &right) const = 0;
};

class UnaryOperatorStrategy
{
public:
    virtual Value execute(const Value &right) const = 0;
};

class AddOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class SubtractOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class MultiplyOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class ModulusOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class PowerOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class DivideOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class NegateOperatorStrategy : public UnaryOperatorStrategy
{
public:
    Value execute(const Value &right) const override;
};

class NotOperatorStrategy : public UnaryOperatorStrategy
{
public:
    Value execute(const Value &right) const override;
};

class LogicalAndOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class LogicalOrOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class EqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class NotEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class GreaterOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class GreaterEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class LessOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class LessEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    Value execute(const Value &left, const Value &right) const override;
};

class OperatorFactory
{
public:
    std::unique_ptr<BinaryOperatorStrategy> get_binary_operator_strategy(const std::string &op) const;
    std::unique_ptr<UnaryOperatorStrategy> get_unary_operator_strategy(const std::string &op) const;
};

class OperationExecutor
{
private:
    std::unique_ptr<BinaryOperatorStrategy> binary_operator_strategy = nullptr;
    std::unique_ptr<UnaryOperatorStrategy> unary_operator_strategy = nullptr;
    OperatorFactory operator_factory;

public:
    OperationExecutor(OperatorFactory operator_factory);
    void set_binary_operator_strategy(const std::string &op);
    void set_unary_operator_strategy(const std::string &op);
    Value execute(const Value &left, const Value &right) const;
    Value execute(const Value &right) const;
};
#endif // OPERATOR_STRATEGY_H