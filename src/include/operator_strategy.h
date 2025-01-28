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

class OperatorStrategyFactory
{
    std::unordered_map<std::string, std::unique_ptr<BinaryOperatorStrategy>> binaryOperatorStrategies;
    std::unordered_map<std::string, std::unique_ptr<UnaryOperatorStrategy>> unaryOperatorStrategies;

    OperatorStrategyFactory() = default;
    OperatorStrategyFactory(const OperatorStrategyFactory &) = delete;
    OperatorStrategyFactory &operator=(const OperatorStrategyFactory &) = delete;

public:
    static OperatorStrategyFactory &get_instance();
    std::unique_ptr<BinaryOperatorStrategy> get_binary_operator_strategy(const std::string &op) const;
    std::unique_ptr<UnaryOperatorStrategy> get_unary_operator_strategy(const std::string &op) const;
    void register_binary_operator_strategy(const std::string &op, std::unique_ptr<BinaryOperatorStrategy> strategy);
    void register_unary_operator_strategy(const std::string &op, std::unique_ptr<UnaryOperatorStrategy> strategy);
};

void set_up_operator_strategy(OperatorStrategyFactory &factory);

#endif // OPERATOR_STRATEGY_H