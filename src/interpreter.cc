#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "statement.h"
#include "object.h"

#include <memory>


Interpreter::Interpreter(OperationExecutor operation_executor, OBJ::ENV &environment)
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
    std::shared_ptr<OBJ::Object> left = result;
    expression.right->accept(*this);
    std::shared_ptr<OBJ::Object> right = result;
    operation_executor.set_binary_operator_strategy(expression.op);
    result = operation_executor.execute(left, right);
}

void Interpreter::visit(const UnaryExpression &expression)
{
    expression.right->accept(*this);
    std::shared_ptr<OBJ::Object> right = std::move(result);
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
    std::shared_ptr<std::shared_ptr<OBJ::Object>> value = environment.get(expression.name);
    result = *value;
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
    std::cout << result->str() << std::endl;
}

void Interpreter::visit(const VarDeclarationStatement &statement)
{
    std::shared_ptr<OBJ::Object> init = nullptr;
    if (statement.expression != nullptr)
    {
        statement.expression->accept(*this);
        init = std::move(result);
    }
    environment.define(statement.name, std::move(init));
}

void Interpreter::visit(const CompoundStatement &statement)
{
    OBJ::ENV new_environment(&this->environment);
    Interpreter interpreter(operation_executor.clone(), new_environment);
    interpreter.interpret(statement.statements);
}

void Interpreter::visit(const IfStatement &statement)
{
    statement.condition->accept(*this);
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(OBJ::ObjectType::BOOLEAN) == false)
    {
        throw std::runtime_error("Invalid type for if condition");
    }
    if (casting.cast_to_boolean(result) == true)
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
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(OBJ::ObjectType::BOOLEAN) == false)
    {
        throw std::runtime_error("Invalid type for if condition");
    }
    while (casting.cast_to_boolean(result) == true)
    {
        statement.block->accept(*this);
        statement.condition->accept(*this);
    }
}

void Interpreter::visit(const ForStatement &statement)
{
    OBJ::ENV for_environment(&this->environment);
    Interpreter for_interpreter(operation_executor.clone(), for_environment);
    if (statement.initializer != nullptr)
    {
        statement.initializer->accept(for_interpreter);
    }
    statement.condition->accept(for_interpreter);
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(OBJ::ObjectType::BOOLEAN) == false)
    {
        throw std::runtime_error("Invalid type for condition");
    }
    while (for_interpreter.casting.cast_to_boolean(result) == true)
    {
        statement.block->accept(for_interpreter);
        if (statement.update != nullptr)
        {
            statement.update->accept(for_interpreter);
        }
        statement.condition->accept(for_interpreter);
    }
}
