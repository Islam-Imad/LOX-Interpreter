#include <gtest/gtest.h>
#include "parser.h"
#include "statement.h"
#include "expression.h"
#include "scanner.h"

TEST(Parser, expressiont_statement)
{
    TokenUtilites token_utilites;
    std::string source = "1 + 2;";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();
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
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();
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
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::VAR_DECLARATION_STATEMENT);
    const VarDeclarationStatement *var_declaration_statement = dynamic_cast<const VarDeclarationStatement *>(statements[0].get());
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
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 2;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::VAR_DECLARATION_STATEMENT);
    const VarDeclarationStatement *var_declaration_statement = dynamic_cast<const VarDeclarationStatement *>(statements[0].get());
    ASSERT_NE(var_declaration_statement, nullptr);
    ASSERT_EQ(var_declaration_statement->name, "a");

    statements[1]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::PRINT_STATEMENT);
    const PrintStatement *print_statement = dynamic_cast<const PrintStatement *>(statements[1].get());
    ASSERT_NE(print_statement, nullptr);

    ExpressionTypeVisitor expression_visitor;
    print_statement->expression->accept(expression_visitor);
    ASSERT_EQ(expression_visitor.get_result(), ExpressionType::VARIABLE);
}

TEST(Parser, if_statement)
{
    TokenUtilites token_utilites;
    std::string source = "if (1 < 2) { print 1; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::IF_STATEMENT);
    const IfStatement *if_statement = dynamic_cast<const IfStatement *>(statements[0].get());
    ASSERT_NE(if_statement, nullptr);
}

TEST(Parser, if_else_statemetn)
{
    TokenUtilites token_utilites;
    std::string source = "if (1 < 2) { print 1; } else { print 2; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::IF_STATEMENT);
    const IfStatement *if_statement = dynamic_cast<const IfStatement *>(statements[0].get());
    ASSERT_NE(if_statement, nullptr);
}

TEST(Parser, if_else_if_statement)
{
    TokenUtilites token_utilites;
    std::string source = "if (1 < 2) { print 1; } else if (2 < 3) { print 2; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::IF_STATEMENT);
    const IfStatement *if_statement = dynamic_cast<const IfStatement *>(statements[0].get());
    ASSERT_NE(if_statement, nullptr);
}

TEST(Parser, while_statement)
{
    TokenUtilites token_utilites;
    std::string source = "while (1 < 2) { print 1; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::WHILE_STATEMENT);
    const WhileStatement *while_statement = dynamic_cast<const WhileStatement *>(statements[0].get());
    ASSERT_NE(while_statement, nullptr);
}

TEST(Parser, for_statement)
{
    TokenUtilites token_utilites;
    std::string source = "for (var i = 0; i < 10; i = i + 1) { print i; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::FOR_STATEMENT);
    const ForStatement *for_statement = dynamic_cast<const ForStatement *>(statements[0].get());
    ASSERT_NE(for_statement, nullptr);
}

TEST(Parser, Basic_Function)
{
    TokenUtilites token_utilites;
    std::string source = "fun test() { print 1; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::FUNCTION_STATEMENT);
    const FunctionStatement *function_statement = dynamic_cast<const FunctionStatement *>(statements[0].get());
    ASSERT_NE(function_statement, nullptr);
}

TEST(Parser, Basic_Function_Call)
{
    TokenUtilites token_utilites;
    std::string source = "fun test() { print 1; } test();";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 2;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::FUNCTION_STATEMENT);
    const FunctionStatement *function_statement = dynamic_cast<const FunctionStatement *>(statements[0].get());
    ASSERT_NE(function_statement, nullptr);

    statements[1]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::EXPRESSION_STATEMENT);
    const ExpressionStatement *expression_statement = dynamic_cast<const ExpressionStatement *>(statements[1].get());
    ASSERT_NE(expression_statement, nullptr);
    const CallExpression *call_expression = dynamic_cast<const CallExpression *>(expression_statement->expression.get());
    ASSERT_NE(call_expression, nullptr);
}

TEST(Parser, return_statement)
{
    TokenUtilites token_utilites;
    std::string source = "fun test() { return 1; }";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 1;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::FUNCTION_STATEMENT);
    const FunctionStatement *function_statement = dynamic_cast<const FunctionStatement *>(statements[0].get());
    ASSERT_NE(function_statement, nullptr);
}

TEST(Parser, assign_return_statement)
{
    TokenUtilites token_utilites;
    std::string source = "fun test() { return 1; } var a = test();";
    Scanner scanner = Scanner(source, token_utilites);
    std::vector<Token> tokens = scanner.scan();

    Parser parser(tokens, token_utilites, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    const int expected_statements = 2;
    ASSERT_EQ(statements.size(), expected_statements);
    StatementTypeVisitor visitor;
    statements[0]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::FUNCTION_STATEMENT);
    const FunctionStatement *function_statement = dynamic_cast<const FunctionStatement *>(statements[0].get());
    ASSERT_NE(function_statement, nullptr);

    statements[1]->accept(visitor);
    ASSERT_EQ(visitor.get_result(), StatementType::VAR_DECLARATION_STATEMENT);
    const VarDeclarationStatement *var_declaration_statement = dynamic_cast<const VarDeclarationStatement *>(statements[1].get());
    ASSERT_NE(var_declaration_statement, nullptr);
    const CallExpression *call_expression = dynamic_cast<const CallExpression *>(var_declaration_statement->expression.get());
    ASSERT_NE(call_expression, nullptr);
}