#include <vector>
#include "statement.h"
#include "expression.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<const Expression> expression)
    : expression(std::move(expression)) {}

void ExpressionStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

PrintStatement::PrintStatement(std::unique_ptr<const Expression> expression)
    : expression(std::move(expression)) {}

void PrintStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

VarDeclarationStatement::VarDeclarationStatement(const std::string &name, std::unique_ptr<const Expression> expression)
    : name(name), expression(std::move(expression)) {}

IfStatement::IfStatement(std::unique_ptr<const Expression> condition, std::unique_ptr<const Statement> block, std::unique_ptr<Statement> else_branch)
    : condition(std::move(condition))
    , block(std::move(block))
    , else_branch(std::move(else_branch)) {}

WhileStatement::WhileStatement(std::unique_ptr<const Expression> condition, std::unique_ptr<const Statement> block)
    : condition(std::move(condition))
    , block(std::move(block)) {}


CompoundStatement::CompoundStatement(std::vector<std::unique_ptr<const Statement>> statements)
    : statements(std::move(statements)) {}

void CompoundStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

void WhileStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

void IfStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

void VarDeclarationStatement::accept(StatementVisitor &visitor) const { visitor.visit(*this); }

void StatementTypeVisitor::visit(const ExpressionStatement &statement) { result = StatementType::EXPRESSION_STATEMENT; }

void StatementTypeVisitor::visit(const PrintStatement &statement) { result = StatementType::PRINT_STATEMENT; }

void StatementTypeVisitor::visit(const VarDeclarationStatement &statement) { result = StatementType::VAR_DECLARATION_STATEMENT; }

void StatementTypeVisitor::visit(const IfStatement &statement) { result = StatementType::IF_STATEMENT; }

void StatementTypeVisitor::visit(const WhileStatement &statement) { result = StatementType::WHILE_STATEMENT; }

void StatementTypeVisitor::visit(const CompoundStatement &statement) { result = StatementType::COMPOUND_STATEMENT; }

StatementType StatementTypeVisitor::get_result() const { return result; }
