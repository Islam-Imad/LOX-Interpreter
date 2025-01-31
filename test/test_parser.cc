#include <gtest/gtest.h>
#include "parser.h"
#include "expression.h"
#include "token.h"
#include "value.h"
#include "scanner.h"

TEST(Parser, expressiont_statement)
{
    TokenUtilites token_utilites;
    std::string source = "1 + 2;";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::EXPRESSION_STATEMENT);
}

TEST(Parser, print_statement)
{
    TokenUtilites token_utilites;
    std::string source = "print 1 + 2;";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();
    ASSERT_EQ(statements.size(), 1);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::PRINT_STATEMENT);
}

TEST(Parser, var_declaration_statement)
{
    TokenUtilites token_utilites;
    std::string source = "var a = 1 + 2;";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::VAR_DECLARATION_STATEMENT);
    VarDeclarationStatement *var_declaration_statement = dynamic_cast<VarDeclarationStatement *>(statements[0].get());
    ASSERT_NE(var_declaration_statement, nullptr);
    ASSERT_EQ(var_declaration_statement->name, "a");
}

TEST(Parser, VAR_PRINT)
{
    TokenUtilites token_utilites;
    std::string source = "var a = 1 + 2; print a;";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();

    const int expected_statements = 2;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::VAR_DECLARATION_STATEMENT);
    VarDeclarationStatement *var_declaration_statement = dynamic_cast<VarDeclarationStatement *>(statements[0].get());
    ASSERT_NE(var_declaration_statement, nullptr);
    ASSERT_EQ(var_declaration_statement->name, "a");

    statements[1]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::PRINT_STATEMENT);
    PrintStatement *print_statement = dynamic_cast<PrintStatement *>(statements[1].get());
    ASSERT_NE(print_statement, nullptr);

    ExpressionTypeVisitor expression_visitor;
    print_statement->expression->accept(expression_visitor);
    ASSERT_EQ(expression_visitor.get_result(), ExpressionType::VARIABLE);
}