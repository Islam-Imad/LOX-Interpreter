#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "statement.h"

Interpreter::Interpreter(OperationExecutor operation_executor, Environment environment)
    : operation_executor(std::move(operation_executor)), environment(environment) {}

void Interpreter::interpret(const std::vector<std::unique_ptr<const Statement>> &statements)
{
    for (const auto &statement : statements)
    {
        statement->accept(*this);
    }
}

void Interpreter::visit(const BinaryExpression &expression)
{
    expression.left->accept(*this);
    Value left = result;
    expression.right->accept(*this);
    Value right = result;
    operation_executor.set_binary_operator_strategy(expression.op);
    result = operation_executor.execute(left, right);
}

void Interpreter::visit(const UnaryExpression &expression)
{
    expression.right->accept(*this);
    Value right = result;
    operation_executor.set_unary_operator_strategy(expression.op);
    result = operation_executor.execute(right);
}

void Interpreter::visit(const LiteralExpression &expression)
{
    result = expression.value;
}

void Interpreter::visit(const GroupingExpression &expression)
{
    expression.expression->accept(*this);
}

void Interpreter::visit(const VariableExpression &expression)
{
    result = environment.get(expression.name);
}

void Interpreter::visit(const AssignExpression &expression)
{
    expression.expression->accept(*this);
    environment.assign(expression.name, result);
}

void Interpreter::visit(const ExpressionStatement &statement)
{
    statement.expression->accept(*this);
}

void Interpreter::visit(const PrintStatement &statement)
{
    statement.expression->accept(*this);
    std::cout << result.to_string() << std::endl;
}

void Interpreter::visit(const VarDeclarationStatement &statement)
{
    Value init;
    if (statement.expression != nullptr)
    {
        statement.expression->accept(*this);
        init = result;
    }
    environment.define(statement.name, init);
}

void Interpreter::visit(const CompoundStatement &statement)
{
    Interpreter interpreter(operation_executor.clone(), Environment(&environment));
    interpreter.interpret(statement.statements);
}

void Interpreter::visit(const IfStatement &statement)
{
    statement.condition->accept(*this);
    if (result.is_type(ValueType::Boolean) == false)
    {
        throw std::runtime_error("Invalid type for if condition");
    }
    if (result.get<bool>())
    {
        statement.block->accept(*this);
    }
    else if (statement.else_branch != nullptr)
    {
        statement.else_branch->accept(*this);
    }
}

void Interpreter::visit(const WhileStatement &statement)
{
    statement.condition->accept(*this);
    if (result.is_type(ValueType::Boolean) == false)
    {
        throw std::runtime_error("Invalid type for if condition");
    }
    while (result.get<bool>())
    {
        statement.block->accept(*this);
        statement.condition->accept(*this);
    }
}
