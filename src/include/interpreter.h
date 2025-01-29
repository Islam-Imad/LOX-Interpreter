#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include "statement.h"
#include "expression.h"
#include "operator_strategy.h"

class Interpreter : StatementVisitor
{
private:
    ExpressionEvaluator expression_evaluator;

public:
    Interpreter(ExpressionEvaluator expression_evaluator);
    void interpret(const std::vector<std::unique_ptr<Statement>> &statements);
    void visit(const ExpressionStatement &statement) override;
    void visit(const PrintStatement &statement) override;
};

#endif // INTERPRETER_H