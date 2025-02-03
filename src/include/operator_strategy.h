#ifndef OPERATOR_STRATEGY_H
#define OPERATOR_STRATEGY_H

#include <memory>
#include <string>
#include "object.h"
#include <unordered_map>

class BinaryOperatorStrategy
{
public:
    virtual std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const = 0;
};

class UnaryOperatorStrategy
{
public:
    virtual std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &right) const = 0;
};

class AddOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class SubtractOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class MultiplyOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class ModulusOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class PowerOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class DivideOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class FloorDivideOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class NegateOperatorStrategy : public UnaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &right) const override;
};

class NotOperatorStrategy : public UnaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &right) const override;
};

class LogicalAndOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class LogicalOrOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class EqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class NotEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class GreaterOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class GreaterEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class LessOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
};

class LessEqualOperatorStrategy : public BinaryOperatorStrategy
{
public:
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const override;
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
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &left, const std::shared_ptr<OBJ::Object> &right) const;
    std::shared_ptr<OBJ::Object> execute(const std::shared_ptr<OBJ::Object> &right) const;

    OperationExecutor clone() const;
};
#endif // OPERATOR_STRATEGY_H