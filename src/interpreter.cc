#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "statement.h"
#include "object.h"
#include "function.h"

#include <memory>

Interpreter::Interpreter(OperationExecutor operation_executor, ENV &environment)
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
    std::shared_ptr<Object> left = result;
    expression.right->accept(*this);
    std::shared_ptr<Object> right = result;
    operation_executor.set_binary_operator_strategy(expression.op);
    result = operation_executor.execute(left, right);
}

void Interpreter::visit(const UnaryExpression &expression)
{
    expression.right->accept(*this);
    std::shared_ptr<Object> right = std::move(result);
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

void Interpreter::visit(const CallExpression &expression)
{
    std::vector<std::shared_ptr<Object>> args;
    for (const auto &arg : expression.arguments)
    {
        arg->accept(*this);
        args.push_back(result);
    }
    expression.callee->accept(*this);
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(ObjectType::FUNCTION) == false)
    {
        throw std::runtime_error("Invalid type for call expression");
    }
    std::shared_ptr<Callable> function = std::dynamic_pointer_cast<Callable>(result);
    if (function->get_arity() != args.size())
    {
        throw std::runtime_error("Invalid number of arguments");
    }
    result = function->call(args);
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
    std::shared_ptr<Object> init = nullptr;
    if (statement.expression != nullptr)
    {
        statement.expression->accept(*this);
        init = std::move(result);
    }
    else if (statement.expression == nullptr)
    {
        init = std::make_shared<Nil>();
    }
    environment.define(statement.name, init);
}

void Interpreter::visit(const CompoundStatement &statement)
{
    ENV new_environment(&this->environment);
    Interpreter interpreter(operation_executor.clone(), new_environment);
    interpreter.interpret(statement.statements);
}

void Interpreter::visit(const IfStatement &statement)
{
    statement.condition->accept(*this);
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(ObjectType::BOOLEAN) == false)
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
    if (type_check_visitor.mathces(ObjectType::BOOLEAN) == false)
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
    ENV for_environment(&this->environment);
    Interpreter for_interpreter(operation_executor.clone(), for_environment);
    if (statement.initializer != nullptr)
    {
        statement.initializer->accept(for_interpreter);
    }
    statement.condition->accept(for_interpreter);
    result->accept(type_check_visitor);
    if (type_check_visitor.mathces(ObjectType::BOOLEAN) == false)
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

void Interpreter::visit(const FunctionStatement &statemetn)
{
    ENV new_environment(&environment);
    std::shared_ptr<Callable> function = std::make_shared<Function>(statemetn.args, statemetn.body, new_environment);
    environment.define(statemetn.name, function);
}