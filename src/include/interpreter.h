#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include "statement.h"
#include "expression.h"
#include "operator_strategy.h"
#include "object.h"

#include <memory>

class Interpreter : public StatementVisitor, public ExpressionVisitor
{
private:
    ENV environment;
    OperationExecutor operation_executor;
    TypeCheckVisitor type_check_visitor;
    Casting casting;
public:

    std::shared_ptr<Object> result;
    Interpreter(OperationExecutor operation_executor, ENV &environment);
    void interpret(const std::vector<std::unique_ptr<const Statement>> &statements);

    void visit(const ExpressionStatement &statement) override;
    void visit(const PrintStatement &statement) override;
    void visit(const VarDeclarationStatement &statement) override;
    void visit(const IfStatement &statement) override;
    void visit(const WhileStatement &statement) override;
    void visit(const ForStatement &statement) override;
    void visit(const CompoundStatement &statement) override;
    void visit(const FunctionStatement &statement) override;
    void visit(const ReturnStatement &statement) override;

    void visit(const LiteralExpression &expression) override;
    void visit(const UnaryExpression &expression) override;
    void visit(const BinaryExpression &expression) override;
    void visit(const GroupingExpression &expression) override;
    void visit(const VariableExpression &expression) override;
    void visit(const AssignExpression &expression) override;
    void visit(const CallExpression &expression) override;
};

#endif // INTERPRETER_H