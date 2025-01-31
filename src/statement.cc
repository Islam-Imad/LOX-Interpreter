#include "statement.h"
#include "expression.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<const Expression> expression)
    : expression(std::move(expression)) {}

void ExpressionStatement::accept(StatementVisitor &visitor) { visitor.visit(*this); }

PrintStatement::PrintStatement(std::unique_ptr<const Expression> expression)
    : expression(std::move(expression)) {}

void PrintStatement::accept(StatementVisitor &visitor) { visitor.visit(*this); }

VarDeclarationStatement::VarDeclarationStatement(const std::string &name, std::unique_ptr<const Expression> expression)
    : name(name), expression(std::move(expression)) {}

void VarDeclarationStatement::accept(StatementVisitor &visitor) { visitor.visit(*this); }