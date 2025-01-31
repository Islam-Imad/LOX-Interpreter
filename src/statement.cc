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

void StatementTypeVisitor::visit(const ExpressionStatement &statement) { result = StatementType::EXPRESSION_STATEMENT; }

void StatementTypeVisitor::visit(const PrintStatement &statement) { result = StatementType::PRINT_STATEMENT; }

void StatementTypeVisitor::visit(const VarDeclarationStatement &statement) { result = StatementType::VAR_DECLARATION_STATEMENT; }

StatementType StatementTypeVisitor::get_result() const { return result; }