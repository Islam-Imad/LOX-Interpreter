#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include "statement.h"
#include "expression.h"
#include "operator_strategy.h"
#include "environment.h"

class Interpreter : StatementVisitor , ExpressionVisitor
{
private:
    Environment environment;
    OperationExecutor operation_executor;
    Value result;

public:
    Interpreter(OperationExecutor operation_executor, Environment environment);
    void interpret(const std::vector<std::unique_ptr<const Statement>> &statements);
    
    void visit(const ExpressionStatement &statement) override;
    void visit(const PrintStatement &statement) override;
    void visit(const VarDeclarationStatement &statement) override;
    void visit(const IfStatement &statement) override;
    void visit(const WhileStatement &statement) override;
    void visit(const CompoundStatement &statement) override;
    
    void visit(const LiteralExpression &expression) override;
    void visit(const UnaryExpression &expression) override;
    void visit(const BinaryExpression &expression) override;
    void visit(const GroupingExpression &expression) override;
    void visit(const VariableExpression &expression) override;
    void visit(const AssignExpression &expression) override;
};

#endif // INTERPRETER_H