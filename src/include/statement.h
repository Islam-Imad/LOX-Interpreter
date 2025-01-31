#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include <string>
#include "expression.h"

class Statement;
class ExpressionStatement;
class PrintStatement;
class VarDeclarationStatement;

enum StatementType
{
    EXPRESSION_STATEMENT,
    PRINT_STATEMENT,
    VAR_DECLARATION_STATEMENT
};

class StatementVisitor
{
public:
    virtual void visit(const ExpressionStatement &statement) = 0;
    virtual void visit(const PrintStatement &statement) = 0;
    virtual void visit(const VarDeclarationStatement &statement) = 0;
};

class StatementTypeVisitor : public StatementVisitor
{
private:
    StatementType result;

public:
    void visit(const ExpressionStatement &statement) override;
    void visit(const PrintStatement &statement) override;
    void visit(const VarDeclarationStatement &statement) override;
    StatementType get_result() const;
};

class Statement
{
public:
    virtual void accept(StatementVisitor &visitor) = 0;
};

class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) override;
    std::unique_ptr<const Expression> expression;
};

class PrintStatement : public Statement
{
public:
    PrintStatement(std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) override;
    std::unique_ptr<const Expression> expression;
};

class VarDeclarationStatement : public Statement
{
public:
    VarDeclarationStatement(const std::string &name, std::unique_ptr<const Expression> expression);
    void accept(StatementVisitor &visitor) override;
    std::string name;
    std::unique_ptr<const Expression> expression;
};

#endif // STATEMENT_H