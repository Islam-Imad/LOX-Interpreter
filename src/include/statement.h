#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include <string>
#include "expression.h"

class Statement;
class ExpressionStatement;
class PrintStatement;
class VarDeclarationStatement;
class IfStatement;

enum StatementType
{
    EXPRESSION_STATEMENT,
    PRINT_STATEMENT,
    VAR_DECLARATION_STATEMENT,
    IF_STATEMENT
};

class StatementVisitor
{
public:
    virtual void visit(const ExpressionStatement &statement) = 0;
    virtual void visit(const PrintStatement &statement) = 0;
    virtual void visit(const VarDeclarationStatement &statement) = 0;
    virtual void visit(const IfStatement &statement) = 0;
};

class StatementTypeVisitor : public StatementVisitor
{
private:
    StatementType result;

public:
    void visit(const ExpressionStatement &statement) override;
    void visit(const PrintStatement &statement) override;
    void visit(const VarDeclarationStatement &statement) override;
    void visit(const IfStatement &statement) override;
    StatementType get_result() const;
};

class Statement
{
public:
    virtual void accept(StatementVisitor &visitor) const = 0;
};

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) const override;
    std::unique_ptr<const Expression> expression;
};

class PrintStatement : public Statement
{
public:
    PrintStatement(std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) const override;
    std::unique_ptr<const Expression> expression;
};

class VarDeclarationStatement : public Statement
{
public:
    VarDeclarationStatement(const std::string &name, std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) const override;
    std::string name;
    std::unique_ptr<const Expression> expression;
};

class IfStatement : public Statement
{
public:
    std::unique_ptr<const Expression> condition;
    std::vector<std::unique_ptr<const Statement>> block;
    std::unique_ptr<Statement> else_branch;

    void accept(StatementVisitor &visitor) const override;

    IfStatement(std::unique_ptr<const Expression> condition, std::vector<std::unique_ptr<const Statement>> block, std::unique_ptr<Statement> else_branch);
};

#endif // STATEMENT_H