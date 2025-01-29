#include "interpreter.h"
#include "expression.h"

Interpreter::Interpreter(ExpressionEvaluator expression_evaluator) : expression_evaluator(std::move(expression_evaluator)) {}

void Interpreter::interpret(const std::vector<std::unique_ptr<Statement>> &statements)
{
    for (const auto &statement : statements)
    {
        statement->accept(*this);
    }
}

void Interpreter::visit(const ExpressionStatement &statement)
{
    statement.expression->accept(expression_evaluator);
}

void Interpreter::visit(const PrintStatement &statement)
{
    statement.expression->accept(expression_evaluator);
    std::cout << expression_evaluator.get_result().to_string();
}