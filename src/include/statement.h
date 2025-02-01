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
class WhileStatement;
class ForStatement;
class CompoundStatement;

enum StatementType
{
    EXPRESSION_STATEMENT,
    PRINT_STATEMENT,
    VAR_DECLARATION_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    COMPOUND_STATEMENT,
    FOR_STATEMENT
};

class StatementVisitor
{
public:
    virtual void visit(const ExpressionStatement &statement) = 0;
    virtual void visit(const PrintStatement &statement) = 0;
    virtual void visit(const VarDeclarationStatement &statement) = 0;
    virtual void visit(const IfStatement &statement) = 0;
    virtual void visit(const WhileStatement &statement) = 0;
    virtual void visit(const CompoundStatement &statement) = 0;
    virtual void visit(const ForStatement &statement) = 0;
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
    void visit(const WhileStatement &statement) override;
    void visit(const CompoundStatement &statement) override;
    void visit(const ForStatement &statement) override;
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
    std::unique_ptr<const Statement> block;
    std::unique_ptr<Statement> else_branch;

    void accept(StatementVisitor &visitor) const override;

    IfStatement(std::unique_ptr<const Expression> condition, std::unique_ptr<const Statement> block, std::unique_ptr<Statement> else_branch);
};

class WhileStatement : public Statement
{
public:
    std::unique_ptr<const Expression> condition;
    std::unique_ptr<const Statement> block;

    void accept(StatementVisitor &visitor) const override;

    WhileStatement(std::unique_ptr<const Expression> condition, std::unique_ptr<const Statement> block);
};

class CompoundStatement : public Statement
{
public:
    std::vector<std::unique_ptr<const Statement>> statements;

    void accept(StatementVisitor &visitor) const override;

    CompoundStatement(std::vector<std::unique_ptr<const Statement>> statements);
};

class ForStatement : public Statement
{
public:
    std::unique_ptr<const Statement> initializer;
    std::unique_ptr<const Expression> condition;
    std::unique_ptr<const Expression> update;
    std::unique_ptr<const Statement> block;

    void accept(StatementVisitor &visitor) const override;

    ForStatement(std::unique_ptr<const Statement> initializer, std::unique_ptr<const Expression> condition, std::unique_ptr<const Expression> update, std::unique_ptr<const Statement> block);
};

#endif // STATEMENT_H