#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <gtest/gtest.h>
#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "token.h"
#include "statement.h"
#include "parser.h"
#include "scanner.h"

TEST(Interpreter, TestInterpreter)
{
    std::string source = "print (true and false);";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, TestInterpreter2)
{
    std::string source = "var a = 1 + 2 ** 3 / 2;";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, For_statement)
{
    std::string source = "for (var i = 0; i < 10; i = i + 1) { print i; }";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, Function_statement)
{
    std::string source = "fun test() { print 1; } test();";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, If_statement)
{
    std::string source = "if (1 < 2) { print 1; } else if (2 < 3) { print 2; }";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, While_statement)
{
    std::string source = "var x = 1; while (x >= 0) { print 1; x = -1; }";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, Return_statement)
{
    std::string source = "fun test() { return 1; }";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, Assign_return_statement)
{
    std::string source = "fun test() { return 99; } var a = test(); print a;";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();

    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, Return_Function)
{
    std::string source = "fun test() { return 99; } fun test2() { return test(); } print test2();";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();

    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, closure)
{
    std::string source = "fun test() { var a = 1; fun test2() { print a; } return test2; } var x = test(); x();";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<const Statement>> statements = parser.parse();

    std::shared_ptr<ENV> environment = std::make_shared<ENV>();
    Interpreter interpreter(environment);
    ASSERT_NO_THROW(interpreter.interpret(statements));
}