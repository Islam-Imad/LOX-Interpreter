#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <gtest/gtest.h>
#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "token.h"
#include "value.h"
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
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());

    Interpreter interpreter(std::move(operation_executor));
    ASSERT_NO_THROW(interpreter.interpret(statements));
}

TEST(Interpreter, TestInterpreter2)
{
    std::string source = "var a = 1 + 2 ** 3 / 2;";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());

    Interpreter interpreter(std::move(operation_executor));
    ASSERT_NO_THROW(interpreter.interpret(statements));
}
